#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <graphicslib.hpp>
#include <utils.hpp>
#include <matrixlib.hpp>
#include <shader.hpp>
#include <model.hpp>
#include <camera.hpp>

#define FILE "scene.txt"

#include <glm/gtc/type_ptr.hpp>


namespace graphicslib {

    // camera
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    float lastX;
    float lastY;
    float firstMouse = true;

    // lighting
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    //initialize glfw stuff
    Window::Window(int windowWidth, int windowHeight){
        //listen for errors generated by glfw
        glfwSetErrorCallback(glfwErrorCallback);

        //initialize glfw
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


        lastX = windowWidth/2.0f;
        lastY = windowHeight/2.0f;

        mOrthogonalProjection = true;
        mPReleased = true;

        // timing
        mDeltaTime = 0.0f;
        mLastFrame = 0.0f;
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
        mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, "Camera View", NULL, NULL);

        if(mWindow == NULL) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            this->~Window();
            return;
        }

        //make context current
        glfwMakeContextCurrent(mWindow); //IMPORTANT!!

        //set callback function to call when resize
        glfwSetFramebufferSizeCallback(mWindow, framebufferResizeCallback);
        glfwSetCursorPosCallback(mWindow, mouseCallback);

        // tell GLFW to capture our mouse
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

        //allow us to change the size of a point
        glEnable(GL_PROGRAM_POINT_SIZE);

    }


    void Window::run(){

        /*

        std::ifstream modelsFile(FILE);
        std::string line;
        int i = 0;
        // build and compile shaders
        Shader shader("src/model.vs", "src/model.fs");

        //delta is the distance between the origin of the coordinate system and the center of the i model
        std::vector<float> delta;
        delta.push_back(0);

        std::vector<Model> models;
        //previousModelSize is the half the x-axis size of the model on the left of the current model
        //it is used to obtain the delta value for the current model
        float previousModelSize = 0;
        // load models
        while(std::getline(modelsFile, line)){
                
            Model model(line);

            // calculate the bounding box of the model
            model.calcBoundingBox();

            // size of the biggest dimension of the model
            float size = model.biggestDimensionSize();

            // initial rotation
            modelCoord.rotation[0] = 0.f;
            modelCoord.rotation[1] = 0.f;
            modelCoord.rotation[2] = 0.f;

            // initial scale
            modelCoord.scale[0] = 2.f/size;
            modelCoord.scale[1] = 2.f/size;
            modelCoord.scale[2] = 2.f/size;

            modelCoord.position[0] = -(model.boundingBox.x.center);
            modelCoord.position[1] = -(model.boundingBox.y.center);
            modelCoord.position[2] = -(model.boundingBox.z.center);

            //to set the delta distance, we need the delta of the previous model, half of its size, half of the 
            //size of the current model and a constant value (so the models won't be rendered too close to each other)
            if(i != 0) {
                delta.push_back(delta[i - 1] + previousModelSize + modelCoord.scale[0]*model.boundingBox.x.size/2 + 0.25);
            }
            previousModelSize = modelCoord.scale[0]*model.boundingBox.x.size/2;

            i++;
            modelCoordVector.push_back(modelCoord);           
            models.push_back(model);                
        }

        float currentFrame;
        ml::matrix<float> projection(4, 4);
        */

        // build and compile our shader zprogram
            // ------------------------------------
        Shader phongShader("src/phong.vs", "src/phong.fs");
        Shader lampShader("src/lamp.vs", "src/lamp.fs");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        // configure the cube's VAO (and VBO)
        unsigned int VBO, cubeVAO;
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(cubeVAO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        float lightPoint[] = {
            0.3f, 0.3f, 1.f
        };

        // configure the lightPoint's VAO (and VBO)
        unsigned int lightPointVBO, lightPointVAO;
        glGenVertexArrays(1, &lightPointVAO);
        glGenBuffers(1, &lightPointVBO);

        glBindBuffer(GL_ARRAY_BUFFER, lightPointVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(lightPoint), lightPoint, GL_STATIC_DRAW);

        glBindVertexArray(lightPointVAO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


        float currentFrame;
        ml::matrix<float> projection(4, 4);
        ml::matrix<float> view(4, 4);
        ml::matrix<float> modelMatrix(4, 4, true);

        // render loop
        while(!glfwWindowShouldClose(mWindow)){
            // per-frame time logic
            currentFrame = glfwGetTime();
            mDeltaTime = currentFrame - mLastFrame;
            mLastFrame = currentFrame;

            // input
            updateInput(mWindow);

            // render
            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // be sure to activate shader when setting uniforms/drawing objects
            phongShader.use();
            phongShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
            phongShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
            phongShader.setVec3("lightPos", glm::make_vec3(lightPoint));
            phongShader.setVec3("viewPos", camera.Position);


            // view/projection transformations
            projection = utils::perspectiveMatrix();
            phongShader.setMat4("projection", projection.getMatrix());
            view = camera.GetViewMatrix();
            phongShader.setMat4("view", view.getMatrix());
            modelMatrix = modelMatrix.transpose();
            phongShader.setMat4("model", modelMatrix.getMatrix());

            // render the cube
            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);



            lampShader.use();
            // view/projection transformations
            lampShader.setMat4("projection", projection.getMatrix());
            lampShader.setMat4("view", view.getMatrix());
            lampShader.setMat4("model", modelMatrix.getMatrix());

            //draw the lightPoint
            glBindVertexArray(lightPointVAO);
            glDrawArrays(GL_POINTS, 0, 1);

            /*
            //enable shader
            shader.use();

            if(mOrthogonalProjection){
                //use orthogonal projection
                projection = utils::orthogonalMatrix();
            }else{
                //use perspective projection
                projection = utils::perspectiveMatrix();
            }

            // view/projection transformations
            shader.setMat4("projection", projection.getMatrix());
            ml::matrix<float> view = camera.GetViewMatrix();
            shader.setMat4("view", view.getMatrix());

            i = 0;
            // render the loaded models
            for(auto model : models){

                //translate the current model to the side of the previous model
                ml::matrix<float> modelMatrix(4, 4, true);
                //tmp is the array used to translate the model using its assigned delta value
                float tmp[3] = {delta[i], 0, 0};
                modelMatrix = utils::translate(modelMatrix, tmp);

                // apply rotation
                modelMatrix = utils::rotateX(modelMatrix, modelCoordVector[i].rotation[0]);
                modelMatrix = utils::rotateY(modelMatrix, modelCoordVector[i].rotation[1]);
                modelMatrix = utils::rotateZ(modelMatrix, modelCoordVector[i].rotation[2]);

                // apply scale
                modelMatrix = utils::scale(modelMatrix, modelCoordVector[i].scale);

                // apply translation to the origin
                modelMatrix = utils::translate(modelMatrix, modelCoordVector[i].position);


                //transpose the matrix
                modelMatrix = modelMatrix.transpose();

                //pass the model matrix to the shader
                shader.setMat4("model", modelMatrix.getMatrix());
                model.Draw(shader);

                i++;
            }         
            */

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            glfwSwapBuffers(mWindow);
            glfwPollEvents();
        }

    }

    //callback function to execute when the window is resized
    void Window::framebufferResizeCallback(GLFWwindow* window, int fbWidth, int fbHeight){
        glViewport(0, 0, fbWidth, fbHeight);
    }


    //update the user input
    void Window::updateInput(GLFWwindow *window){
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }

        bool shiftIsPressed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

        if(shiftIsPressed){
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
                camera.ProcessKeyboard(UP, mDeltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
                camera.ProcessKeyboard(DOWN, mDeltaTime);
            }
        }else{
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
                camera.ProcessKeyboard(FORWARD, mDeltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
                camera.ProcessKeyboard(BACKWARD, mDeltaTime);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            camera.ProcessKeyboard(LEFT, mDeltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            camera.ProcessKeyboard(RIGHT, mDeltaTime);
        }

        if(mPReleased){
            if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
                mOrthogonalProjection = !mOrthogonalProjection;
            }
            mPReleased = false;
        }
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE){
            mPReleased = true;
        }

    }

    // glfw: whenever the mouse moves, this callback is called
    void mouseCallback(GLFWwindow* window, double xpos, double ypos)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        // yoffset reversed since y-coordinates go from bottom to top
        float yoffset = lastY - ypos; 

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }

    void Window::glfwErrorCallback(int error, const char* description) {
        std::cerr << "GLFW error code " << error << ". Description: " << description << std::endl;
    }

}
