#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "application/application.h">
#include "wrapper/checkError.h"

using namespace std;

void printGLFWError() {
    const char* description;
    int error_code = glfwGetError(&description);
    if (error_code != GLFW_NO_ERROR) {
        fprintf(stderr, "GLFW error (%d): %s\n", error_code, description);
    }
}

// declear a function to respond window resize
void frameBuffferSizeCallback(GLFWwindow * window, int width, int height)
{
//    cout << "window current size : " << width << ", " << height << endl;
    glViewport(0, 0, width, height);
}

// declear a keyboard response function
void keyCallBack(GLFWwindow * window, int key, int scancode, int action, int modes)
{
    if (key == GLFW_KEY_W) {
        cout << "pressed: " << "w" << endl;
    }
    if (action == GLFW_PRESS)
    {
        cout << "key pressed: " << endl;
    }
    if (action == GLFW_RELEASE)
    {
        cout << "key released: " << endl;
    }
    if (modes == GLFW_MOD_CONTROL)
    {
        cout << "key control pressed: " << endl;
    }
}

int main(void)
{
    app->test();

    GLFWwindow* window;

    /* Initialize the library */
    if (glfwInit() == GLFW_FALSE)
    {
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OpenGLStudy", NULL, NULL);
    if (!window)
    {
        printGLFWError();
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* set current window size chagne listener */
    glfwSetFramebufferSizeCallback(window, frameBuffferSizeCallback);

    /* set current keyboard listener */
    glfwSetKeyCallback(window, keyCallBack);

    // Load all openGL functions of current version
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // Set openGL view port and clear color
    GL_CALL(glViewport(0, 0, 800, 600));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 10.f));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();

        // clear buffer
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        glfwSwapBuffers(window);
    }

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


