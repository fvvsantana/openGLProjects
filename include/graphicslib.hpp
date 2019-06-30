#ifndef GRAPHICSLIB_HPP
#define GRAPHICSLIB_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define MAX_LIGHT_NUMBER 100


namespace ml{
    template<class T>
        class matrix;
}

namespace graphicslib {
    struct Vertex {
        float position[3];
        float color[3];
        float texcoord[2];
    };

    struct ModelCoordinates{
        float position[3];
        float rotation[3];
        float scale[3];
    };


    //point light structure for the rendering of the lights
    struct PointLightForBuffer{
        //light position
        glm::vec3 position;
        //light color
        glm::vec3 color;
    };


    //point light structure that holds all the information about the point light
    struct PointLight {
        //light position
        glm::vec3 position;

        //light attenuation
        float constant;
        float linear;
        float quadratic;

        //light components
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    //All the light information in the scene
    struct LightingInformation{
        //array of point lights for rendering
        PointLightForBuffer bufferOfPointLights[MAX_LIGHT_NUMBER];
        //array of point lights that holds all the information
        PointLight pointLights[MAX_LIGHT_NUMBER];

        //number of point lights in the scene
        int numberOfPointLights;
    };

    //responds to mouse movements via callback (argument to glfw)
    void mouseCallback(GLFWwindow* window, double xpos, double ypos);

    class Window {
    private:
        //Temporary cube just to see the shader effects clearly
        float cubeVertices[216] = {
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

        int mWindowWidth;
        int mWindowHeight;
        GLFWwindow* mWindow;
        GLuint mCoreProgram;

        ModelCoordinates modelCoord;
        //vector used to store the initial position of multiple models
        std::vector<ModelCoordinates> modelCoordVector;

        // perspective type
        bool mPhong;
        bool mPReleased;

        // timing
        float mDeltaTime;
        float mLastFrame;

        //struct to keep all the lighting information
        LightingInformation lightingInformation;

        unsigned int loadCubeVAO();
        unsigned int loadPointLightsVAO();

        //callback function to execute when the window is resized
        static void framebufferResizeCallback(GLFWwindow* window, int fbWidth, int fbHeight);

        void updateInput(GLFWwindow *window);

        static void glfwErrorCallback(int error, const char* description);

    public:

        //init glfw stuff
        Window(int windowWidth, int windowHeight);

        //destroy everything
        ~Window();

        //create the window, load glad, load shaders
        void createWindow();

        //main loop
        void run();
    };
}


#endif
