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
void onResize(int width, int height)
{
    cout << "onResize" << endl;
    GL_CALL(glViewport(0, 0, width, height));
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
    if (!app->init(800, 600)) {
        return -1;
    }
    app->setResizeCallback(onResize);

//    /* set current keyboard listener */
//    glfwSetKeyCallback(window, keyCallBack);

    // Set openGL view port and clear color
    GL_CALL(glViewport(0, 0, 800, 600));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 10.f));

    /* Loop until the user closes the window */
    while (app->update())
    {
        // clear buffer
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        // render
    }

    app->destroy();
    return 0;
}


