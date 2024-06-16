#include <iostream>
#include "glFramework/core.h"
#include "glFramework/shader.h"
#include "glFramework/texture.h"
#include "application/application.h"
#include "wrapper/checkError.h"
#include "application/camera/perspectiveCamera.h"
#include "application/camera/trackBallCameraController.h"
#include "application/camera/orthographicCamera.h"
#include "application/camera/gameCameraController.h"

using namespace std;

GLuint vao = 0;
Shader *shader = nullptr;
Texture *grassTexture = nullptr;
Texture *landTexture = nullptr;
Texture *noiseTexture = nullptr;
Texture *caoshenTexture = nullptr;
glm::mat4 transformMatrix(1.0);

PerspectiveCamera* camera = nullptr;
//OrghographicCamera* camera = nullptr;
//TrackBallCameraController* cameraControl = nullptr;
GameCameraControl* cameraControl = nullptr;

// declear a function to respond window resize
void onResize(int width, int height)
{
    cout << "onResize" << endl;
    GL_CALL(glViewport(0, 0, width, height));
}

// declear a keyboard response function
void onKey(int key, int action, int modes)
{
    cameraControl->onKey(key, action, modes);
}

void onMouse(int button, int action, int modes) {
    double x, y;
    app->getCursorPosition(&x, &y);
    cameraControl->onMouse(button, action, x, y);
}

void onCursor(double xpos, double ypos) {
    cameraControl->onCursor(xpos, ypos);
}

void onScroll(double offset) {
    cameraControl->onScroll(offset);
}

void doRotationTransform() {
    // splin along with Z-axis by 45 degrees
    transformMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
}

void doTranslationTransform() {
    transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
}

void doScaleTransform() {
    transformMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 1.0));
}

void preTransform() {
//    transformMatrix = glm::scale(transformMatrix, glm::vec3(0.5, 0.5, 1.0));
}

void doTransform() {
//    float angle = 0.25f;
//    transformMatrix = glm::rotate(transformMatrix, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));

//    float angle = 45.0f;
//    transformMatrix = glm::rotate(transformMatrix, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
//    transformMatrix = glm::translate(transformMatrix, glm::vec3(0.001f, 0.0f, 0.0f));
//    transformMatrix = glm::translate(transformMatrix, glm::vec3(0.001f, 0.0f, 0.0f));
}

void prepareCamera() {
    camera = new PerspectiveCamera(60.0f, (float)app->getWidth() / (float)app->getHeight(), 0.1f, 1000.0f);
//    float size = 6.0f;
//    camera = new OrghographicCamera(-size, size, size, -size, size, -size);
//    cameraControl = new TrackBallCameraController();
    cameraControl = new GameCameraControl();
    cameraControl->setCamera(camera);
}


float angle = 0.0f;
void doRotation() {
    angle += 0.5f;
    // each frame, refresh another rotate matrix
    glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
    transformMatrix = rotateMat;
}

void prepareSingleBuffer() {
//    float positions[] = {
//            -0.5f, -0.5f, 0.0f,
//            0.5f, -0.5f, 0.0f,
//            -0.5f, 0.5f, 0.0f,
//            0.5f, 0.5f,0.05f,
//    };
    float positions[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f,1.0f,
    };

    float colors[] = {
            1.0f,   0.0f,   0.0f,
            0.0f,   1.0f,   0.0f,
            0.0f,   0.0f,   1.0f,
            0.5f,  0.5f,  0.5f
    };

    float uvs[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 1, 3
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
    grassTexture = new Texture("assets/textures/grass.jpg", 0);
    landTexture = new Texture("assets/textures/land.jpeg", 1);
    noiseTexture = new Texture("assets/textures/noise.jpg", 2);
    caoshenTexture = new Texture("assets/textures/caoshen.jpeg", 3);
}

void render() {
    // clear buffer
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    // 1. bind current program
    shader->begin();

    float color[] = {0.9, 0.3, 0.25};
    shader->setVector3("uColor", color);

    shader->setInt("grassSampler", 0);
    shader->setInt("landSampler", 1);
    shader->setInt("noiseSampler", 2);
    shader->setInt("caoshenSampler", 3);

    shader->setMarix4x4("transform", transformMatrix);
    shader->setMarix4x4("viewMatrix", camera->getViewMatrix());
    shader->setMarix4x4("projectionMatrix", camera->getProjectionMatrix());

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
    // Vector
    glm::vec2 v0(0);
    glm::vec3 v1(0);
    glm::vec4 v2(0);

    glm::vec4 vadd = v2 + glm::vec4(0);
    auto mul = vadd * v2;  // multiply each element and put to corresponding position
    auto dotRes = glm::dot(vadd, v2);
    glm::vec3 vt0, vt1;
    auto crossRes = glm::cross(vt0, vt1);

    // matrix
    glm::mat4 m0(1.0);
    glm::mat4 m1 = glm::identity<glm::mat4>();
    glm::mat2 mm2(1.0);
    glm::mat3 mm3(1.0);
    glm::mat2x3 mm4(1.0);

    auto madd = m0 + m1;
    auto mmulti = m0 * m1;
    auto res = m0 * v2;

    // transpose
    auto transMat = glm::transpose(madd);

    // inverse
    auto inverseMat = glm::inverse(madd);

    cout << glm::to_string(mm4) << endl;

    if (!app->init(800, 600)) {
        return -1;
    }
    app->setResizeCallback(onResize);
    app->setKeyCallBack(onKey);
    app->setMouseCallBack(onMouse);
    app->setCursorCallBack(onCursor);
    app->setScrollCallBack(onScroll);

    // Set openGL view port and clear color
    GL_CALL(glViewport(0, 0, 800, 600));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    prepareTexture();
    prepareSingleBuffer();
    prepareShader();
    prepareCamera();

    /* Loop until the user closes the window */
    preTransform();
    while (app->update())
    {
        doTransform();
        cameraControl->update();
        // render
        render();
    }

    app->destroy();
    delete shader;
    delete grassTexture;
    delete landTexture;
    delete noiseTexture;
    delete caoshenTexture;
    return 0;
}