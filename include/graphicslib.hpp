#ifndef GRAPHICSLIB_HPP
#define GRAPHICSLIB_HPP


#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    class Window {
    private:
        int mWindowWidth;
        int mWindowHeight;
        GLFWwindow* mWindow;
        GLuint mCoreProgram;

        //callback function to execute when the window is resized
        static void framebufferResizeCallback(GLFWwindow* window, int fbWidth, int fbHeight);
        void updateInput(GLFWwindow *window, ml::matrix<float> &position, ml::matrix<float> &scale,
                             float &previousAngularVelocity, float &angularVelocity, bool &spaceReleased);
        bool loadShaders(GLuint &program, char* vertexShaderFile, char* fragmentShaderFile);
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
