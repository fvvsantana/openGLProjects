#ifndef GRAPHICSLIB_HPP
#define GRAPHICSLIB_HPP


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace ml{
    template<class T>
        class matrix;
}

namespace graphicslib {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texcoord;
    };

    class Window {
    private:
        int mWindowWidth;
        int mWindowHeight;
        GLFWwindow* mWindow;
        GLuint mCoreProgram;
        bool spaceReleased;

        //callback function to execute when the window is resized
        static void framebufferResizeCallback(GLFWwindow* window, int fbWidth, int fbHeight);
        void updateInput(GLFWwindow *window, ml::matrix<float> &position, ml::matrix<float> &scale,
                             float &previousAngularVelocity, float &angularVelocity);
        bool loadShaders(GLuint &program, char* vertexShaderFile, char* fragmentShaderFile);

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
