#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "application/application.h">
#include "wrapper/checkError.h"

using namespace std;

// declear a function to respond window resize
void onResize(int width, int height)
{
    cout << "onResize" << endl;
    GL_CALL(glViewport(0, 0, width, height));
}

// declear a keyboard response function
void onKey(int key, int action, int modes)
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

void prepareVBO() {
    GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));
    GL_CALL(glDeleteBuffers(1, &vbo));

    GLuint vboArr[] = {0, 0, 0};
    GL_CALL(glGenBuffers(3, vboArr));
    GL_CALL(glDeleteBuffers(3, vboArr));
}

void prepare() {
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.0f, 0.5f, 0.0f
    };

    GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
}

int main(void)
{
    if (!app->init(800, 600)) {
        return -1;
    }
    app->setResizeCallback(onResize);
    app->setKeyCallBack(onKey);

    // Set openGL view port and clear color
    GL_CALL(glViewport(0, 0, 800, 600));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 10.f));

    prepare();

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