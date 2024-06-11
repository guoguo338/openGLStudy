#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "application/application.h"
#include "wrapper/checkError.h"

using namespace std;

GLuint program = 0, vao = 0;

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

void prepareInterleavedBuffer() {
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GL_CALL(glGenVertexArrays(1, &vao));
    GL_CALL(glBindVertexArray(vao));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0));

    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float))));

    // unbind vao
    GL_CALL(glBindVertexArray(0));
}

void prepareShader(){
    const char* vertexShaderSource =
            "#version 410 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

    const char* fragmentShaderSource =
            "#version 410 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

    // create shader program (vs、fs)
    GLuint vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    // input shader code
    GL_CALL(glShaderSource(vertex, 1, &vertexShaderSource, NULL));
    GL_CALL(glShaderSource(fragment, 1, &fragmentShaderSource, NULL));

    int success = 0;
    char infoLog[1024];
    // compile shader code
    GL_CALL(glCompileShader(vertex));
    GL_CALL(glGetShaderiv(vertex, GL_COMPILE_STATUS, &success));
    if (!success) {
        GL_CALL(glGetShaderInfoLog(vertex, 1024, NULL, infoLog));
        cout << "Error: SHADER COMPILE ERROR --VERTEX" << "\n" << infoLog << endl;
    }

    GL_CALL(glCompileShader(fragment));
    GL_CALL(glGetShaderiv(fragment, GL_COMPILE_STATUS, &success));
    if (!success) {
        GL_CALL(glGetShaderInfoLog(fragment, 1024, NULL, infoLog));
        cout << "Error: SHADER COMPILE ERROR --FRAGMENT" << "\n" << infoLog << endl;
    }

    // create a program
    program = glCreateProgram();

    // put the compiled result of vs & fs to program
    GL_CALL(glAttachShader(program, vertex));
    GL_CALL(glAttachShader(program, fragment));

    // execute program, and create the executable shader
    GL_CALL(glLinkProgram(program));
    GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &success));
    if (!success) {
        GL_CALL(glGetProgramInfoLog(program, 1024, NULL, infoLog));
        cout << "Error: SHADER LINK ERROR " << "\n" << infoLog << endl;
    }

    // clean up
    GL_CALL(glDeleteShader(vertex));
    GL_CALL(glDeleteShader(fragment));
}

void render() {
    // clear buffer
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    // 1. bind current program
    GL_CALL(glUseProgram(program));

    // 2. bind current vao
    GL_CALL(glBindVertexArray(vao));

    // 3. send draw call
    GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
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
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    prepareShader();
    prepareInterleavedBuffer();

    /* Loop until the user closes the window */
    while (app->update())
    {
        // render
        render();
    }

    app->destroy();
    return 0;
}