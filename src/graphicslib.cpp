#include <iostream>
#include <fstream>
#include <string>
#include <vector>


//#include <glm/vec2.hpp>
//#include <glm/vec3.hpp>
//#include <glm/vec4.hpp>
//#include <glm/mat4x4.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <SOIL/SOIL.h>
//#include <../include/SOIL.h>
//#include <../external/SOIL.h>


#include <graphicslib.hpp>
#include <utils.hpp>

namespace graphicslib {

    Window::Window(int windowWidth, int windowHeight){
        //init glfw
        glfwInit();

        //set some window options
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); //make window resizable
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //compatibility to mac os users

        mWindowWidth = windowWidth;
        mWindowHeight = windowHeight;
        mWindow = NULL;
        mCoreProgram = 0;
    }

    Window::~Window(){
        //end of program
        if(mWindow){
            glfwDestroyWindow(mWindow);
        }
        //delete program
        if(mCoreProgram){
            glDeleteProgram(mCoreProgram);
        }
        glfwTerminate();
    }


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


    Vertex vertices[] = {
        glm::vec3(-0.5f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),   glm::vec2(1.f, 1.f),
        glm::vec3(-0.5f, -0.5f, 0.f),   glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 1.f),
        glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(0.f, 0.f, 1.f),   glm::vec2(0.f, 1.f),
        glm::vec3(0.5f, 0.5f, 0.f),     glm::vec3(1.f, 1.f, 0.f),   glm::vec2(1.f, 1.f)
    };
    unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

    GLuint indices[] = {
        0, 1, 2, //triangle 1
        0, 2, 3 //triangle 2
    };
    unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);


    void Window::run(){
        //TODO create a function to draw some vertices

        //model

        //vertex array object
        GLuint VAO;
        //create a vertex arrays in the VAO
        glCreateVertexArrays(1, &VAO);
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
        //position
        //GLuint positionAttribLocation = glGetAttribLocation(core_program, "vertex_location");
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

        //bind vao 0
        glBindVertexArray(0);


        while(!glfwWindowShouldClose(mWindow)){
            //update input
            glfwPollEvents();

            //update
            updateInput(mWindow);

            //draw
            //clear
            glClearColor(0.f, 0.f, 0.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            //use a program
            glUseProgram(mCoreProgram);


            //bind vertex array object
            glBindVertexArray(VAO);

            //draw
            //glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);
            glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

            //end draw
            glfwSwapBuffers(mWindow);
            glFlush();

            glBindVertexArray(0);
            glUseProgram(0);
        }

    }

    //callback function to execute when the window is resized
    void Window::framebufferResizeCallback(GLFWwindow* window, int fbWidth, int fbHeight){
        glViewport(0, 0, fbWidth, fbHeight);
    }

    //update the user input
    void Window::updateInput(GLFWwindow *window){
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
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
