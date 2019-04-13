#ifndef GRAPHICSLIB_HPP
#define GRAPHICSLIB_HPP


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


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

        //callback function to execute when the window is resized
        static void framebufferResizeCallback(GLFWwindow* window, int fbWidth, int fbHeight);
        void updateInput(GLFWwindow *window, glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale,
                         glm::vec3 &previousAngularVelocity, glm::vec3 &angularVelocity);
        bool loadShaders(GLuint &program, char* vertexShaderFile, char* fragmentShaderFile);

    public:

        //TODO refactor these comments
        /// Instantiates glfw environment
        Window(int windowWidth, int windowHeight);

        /// Finalizes glfw environment
        ~Window();

        /// Create single window of 800x600 size
        void createWindow();

        /// Run the application in a loop.
        void run();
    };
}


#endif
