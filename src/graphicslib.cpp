#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <graphicslib.hpp>
#include <utils.hpp>
#include <matrixlib.hpp>

namespace graphicslib {

    //init glfw stuff
    Window::Window(int windowWidth, int windowHeight){
        //init glfw
        glfwInit();

        //set some window options
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); //make window resizable
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //compatibility to mac os users

        mWindowWidth = windowWidth;
        mWindowHeight = windowHeight;
        mWindow = NULL;
        mCoreProgram = 0;
        spaceReleased = true;
    }

    //destroy everything
    Window::~Window(){
        //destroy window
        if(mWindow){
            glfwDestroyWindow(mWindow);
        }
        //delete program
        if(mCoreProgram){
            glDeleteProgram(mCoreProgram);
        }
        glfwTerminate();
    }


    //create the window, load glad, load shaders
    void Window::createWindow() {
        //create window
        mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, "WINDMILL", NULL, NULL);

        if(mWindow == NULL) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            this->~Window();
            return;
        }

        //set callback function to call when resize
        glfwSetFramebufferSizeCallback(mWindow, framebufferResizeCallback);

        //make context current
        glfwMakeContextCurrent(mWindow); //IMPORTANT!!

        //enable vsync
        glfwSwapInterval(1);

        //glad: load all OpenGL function pointers
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cerr << "Failed to initialize GLAD" << std::endl;
            this->~Window();
            return;
        }

        //opengl options
        //make possible using 3d
        glEnable(GL_DEPTH_TEST);

        //remove what is behind some object and can't be seen
        glEnable(GL_CULL_FACE);
        //choose to cull the back of the objects
        glCullFace(GL_BACK);
        //count counter-clockwise and define the front face
        glFrontFace(GL_CCW);

        //enable blending of colors
        glEnable(GL_BLEND);
        //setting of how to blend
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //tell how opengl will fill the polygons
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        //shader init
        if(!loadShaders(mCoreProgram, (char *) "src/vertex_core.glsl", (char *) "src/fragment_core.glsl")){
            std::cerr << "Failed to load shaders" << std::endl;
            this->~Window();
            return;
        }

    }

    //main loop
    void Window::run(){

        Vertex vertices[] = {
            //central vertex
            0.f, 0.f, 0.f,    1.f, 0.f, 0.f,   1.f, 1.f,
            //right
            0.25f, 0.f, 0.f,    0.f, 1.f, 0.f,   1.f, 1.f,
            //top right
            0.25f, 0.25f, 0.f,    0.f, 0.f, 1.f,   1.f, 1.f,
            //top
            0.f, 0.25f, 0.f,    0.f, 1.f, 0.f,   1.f, 1.f,
            //top left
            -0.25f, 0.25f, 0.f,    0.f, 0.f, 1.f,   1.f, 1.f,
            //left
            -0.25f, 0.f, 0.f,    0.f, 1.f, 0.f,   1.f, 1.f,
            //bottom left
            -0.25f, -0.25f, 0.f,    0.f, 0.f, 1.f,   1.f, 1.f,
            //bottom
            0.f, -0.25f, 0.f,    0.f, 1.f, 0.f,   1.f, 1.f,
            //bottom right
            0.25f, -0.25f, 0.f,    0.f, 0.f, 1.f,   1.f, 1.f
        } ;

        GLuint indices[] = {
            //top triangle
            0,2,3,
            //left triangle
            0,4,5,
            //bottom triangle
            0,6,7,
            //right triangle
            0,8,1
        };

        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);


        //model

        //vertex array object
        GLuint VAO;
        //create a vertex arrays in the VAO
        glGenVertexArrays(1, &VAO);
        //bind the vertex array to use
        glBindVertexArray(VAO);

        //gen vbo, bind and send data
        //vertex buffer object
        GLuint VBO;
        //generate the vbo
        glGenBuffers(1, &VBO);
        //bind the vbo to the vao in the attach point array_buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //create a buffer data from the vertices data
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //gen ebo, bind and send data
        //element buffer object
        GLuint EBO;
        //generate the ebo
        glGenBuffers(1, &EBO);
        //bind the ebo to the vao in the attach point element_array_buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //create a buffer data from the indices data
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        //set vertexAttribPointers and enable (input assembly)
        //define an array of generic vertex attribute data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, position));
        //enable the created array
        glEnableVertexAttribArray(0);


        //color
        //define an array of generic vertex attribute data
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, color));
        //enable the created array
        glEnableVertexAttribArray(1);

        //texcoord
        //define an array of generic vertex attribute data
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texcoord));
        //enable the created array
        glEnableVertexAttribArray(2);

        //unbind the vertex array and all buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


        ml::matrix<float> position(0.f, 3, 1);
        float angle = 0.f;
        ml::matrix<float> scale(1.f, 3, 1);

        float previousAngularVelocity = 0.f;
        float angularVelocity = -0.01f;

        ml::matrix<float> modelMatrix(4, 4, true);
        modelMatrix = utils::translate(modelMatrix, position);
        modelMatrix = utils::rotateZ(modelMatrix, angle);
        modelMatrix = utils::scale(modelMatrix, scale);
        modelMatrix = modelMatrix.transpose();

        glUseProgram(mCoreProgram);

        glUniformMatrix4fv(glGetUniformLocation(mCoreProgram, "modelMatrix"), 1, GL_FALSE, *(modelMatrix.getMatrix()));

        glUseProgram(0);


        while(!glfwWindowShouldClose(mWindow)){
            //update input
            glfwPollEvents();

            //update
            updateInput(mWindow, position, scale, previousAngularVelocity, angularVelocity);

            //draw
            //clear
            glClearColor(0.f, 0.f, 0.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            //use a program
            glUseProgram(mCoreProgram);

            angle += angularVelocity;

            modelMatrix = ml::matrix<float>(4, 4, true);
            modelMatrix = utils::translate(modelMatrix, position);
            modelMatrix = utils::rotateZ(modelMatrix, angle);
            modelMatrix = utils::scale(modelMatrix, scale);
            modelMatrix = modelMatrix.transpose();

            glUniformMatrix4fv(glGetUniformLocation(mCoreProgram, "modelMatrix"), 1, GL_FALSE, *(modelMatrix.getMatrix()));


            //bind vertex array and element array objects
            glBindVertexArray(VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            //draw
            glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

            //end draw
            glfwSwapBuffers(mWindow);
            glFlush();

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glUseProgram(0);
        }

    }

    //callback function to execute when the window is resized
    void Window::framebufferResizeCallback(GLFWwindow* window, int fbWidth, int fbHeight){
        glViewport(0, 0, fbWidth, fbHeight);
    }

    //update the user input
    void Window::updateInput(GLFWwindow *window, ml::matrix<float> &position, ml::matrix<float> &scale,
                             float &previousAngularVelocity, float &angularVelocity){
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            position[1][0] += 0.01f;
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            position[1][0] -= 0.01f;
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            position[0][0] += 0.01f;
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            position[0][0] -= 0.01f;
        }
        if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
            angularVelocity += 0.001f;
        }
        if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            angularVelocity -= 0.001f;
        }
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
            // prevents this block to be executed simultaneously when
            // the user holds the space key
            if(spaceReleased)
            {
                if(angularVelocity != 0.f){
                    previousAngularVelocity = angularVelocity;
                    angularVelocity = 0.f;
                }else{
                    angularVelocity = previousAngularVelocity;
                }
            }
            spaceReleased = false;
        }
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
            spaceReleased = true;
    }


    bool Window::loadShaders(GLuint &program, char* vertexShaderFile, char* fragmentShaderFile){
        //success of the function
        bool loadSuccess = true;
        //variables for error logging
        int logLength = 512;
        char infoLog[logLength];
        //auxiliary variable
        GLint success;

        std::string src = "";

        //vertex shader

        //copy file content to outputString
        if(!utils::fileToString(vertexShaderFile, src)){
            std::cerr << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE" << std::endl;
            loadSuccess = false;
        }


        //compile vertexShader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* vertSrc = src.c_str();
        glShaderSource(vertexShader, 1, &vertSrc, NULL);
        glCompileShader(vertexShader);

        //check success of shader compilation
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(vertexShader, logLength, NULL, infoLog);
            std::cerr << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_VERTEX_SHADER" << std::endl;
            std::cerr << infoLog << std::endl;
            loadSuccess = false;
        }

        //clear shader source code
        src.clear();

        //fragment shader

        //copy file content to outputString
        if(!utils::fileToString(fragmentShaderFile, src)){
            std::cerr << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << std::endl;
            loadSuccess = false;
        }

        //compile fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar* fragSrc = src.c_str();
        glShaderSource(fragmentShader, 1, &fragSrc, NULL);
        glCompileShader(fragmentShader);

        //check success of shader compilation
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(fragmentShader, logLength, NULL, infoLog);
            std::cerr << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_FRAGMENT_SHADER" << std::endl;
            std::cerr << infoLog << std::endl;
            loadSuccess = false;
        }

        //link program
        program = glCreateProgram();

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        //check success of program linking
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(program, logLength, NULL, infoLog);
            std::cerr << "ERROR::LOADSHADERS::COULD_NOT_LINK_PROGRAM" << std::endl;
            std::cerr << infoLog << std::endl;
            loadSuccess = false;
        }

        //End
        //reset step
        glUseProgram(0);
        //delete shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return loadSuccess;
    }

}
