#include <iostream>
#include "glFramework/core.h"
#include "glFramework/shader.h"
#include "application/application.h"
#include "wrapper/checkError.h"
#define STB_IMAGE_IMPLEMENTATION
#include "application/stb_image.h"

using namespace std;

GLuint vao = 0;
GLuint texture;
Shader *shader = nullptr;

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

void prepareSingleBuffer() {
    float positions[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.0f, 0.5f, 0.0f,
            0.5f, 0.5f,0.0f,
    };

    float colors[] = {
            1.0f, 0.0f, 0.0f,
            0.0f,   1.0f,   0.0f,
            0.0f,   0.0f,   1.0f
    };

    float uvs[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.5f, 1.0f,
    };

    unsigned int indices[] = {
            0, 1, 2,
    };

    // VBO
    GLuint vboIndex = 0;
    GL_CALL(glGenBuffers(1, &vboIndex));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vboIndex));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    GLuint vboColor = 0;
    GL_CALL(glGenBuffers(1, &vboColor));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vboColor));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

    GLuint vboUV = 0;
    glGenBuffers(1, &vboUV);
    glBindBuffer(GL_ARRAY_BUFFER, vboUV);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    // EBO
    GLuint ebo = 0;
    GL_CALL(glGenBuffers(1, &ebo));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // VAO
    GL_CALL(glGenVertexArrays(1, &vao));
    GL_CALL(glBindVertexArray(vao));

    // VAO bidings
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vboIndex));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vboColor));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vboUV));
    GL_CALL(glEnableVertexAttribArray(2));
    GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    // unbind vao
    GL_CALL(glBindVertexArray(0));
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

void prepareShader() {
    shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareTexture() {
    // stbimage read picture
    int width, height, channels;

    // reverse y-axis
    stbi_set_flip_vertically_on_load(true);
    unsigned char * data = stbi_load("assets/textures/caoshen.jpeg", &width, &height, &channels, STBI_rgb_alpha);

    // generate texture and activate unit
    GL_CALL(glGenTextures(1, &texture));
    // activate texture unit
    GL_CALL(glActiveTexture(GL_TEXTURE0));
    // bind texture object
    GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
    // transfer texture data
    if (data) {
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
        // generate mipmap
        GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }

    // release data
    stbi_image_free(data);

    // Set texture filter pattern
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    // Set texture package pattern
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));
}

void render() {
    // clear buffer
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    // 1. bind current program
    shader->begin();

    shader->setFloat("time", glfwGetTime());
    shader->setFloat("speed", 1.0);

    float color[] = {0.9, 0.3, 0.25};
    shader->setVector3("uColor", color);

    shader->setInt("sampler", 0);

    // 2. bind current vao
    GL_CALL(glBindVertexArray(vao));

    // 3. send draw call
//    GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    GL_CALL(glBindVertexArray(0));

    shader->end();
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

    prepareTexture();
    prepareSingleBuffer();
    prepareShader();

    /* Loop until the user closes the window */
    while (app->update())
    {
        // render
        render();
    }

    app->destroy();
    return 0;
}