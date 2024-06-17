#include <iostream>
#include "glFramework/core.h"
#include "glFramework/shader.h"
#include "glFramework/texture.h"
#include "application/application.h"
#include "wrapper/checkError.h"
#include "application/camera/perspectiveCamera.h"
#include "application/camera/trackBallCameraController.h"
#include "glFramework/geometry.h"

using namespace std;

Geometry* geometry = nullptr;
Shader *shader = nullptr;
Texture *texture = nullptr;
glm::mat4 transformMatrix(1.0);

PerspectiveCamera* camera = nullptr;
TrackBallCameraController* cameraControl = nullptr;

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

void prepareCamera() {
    camera = new PerspectiveCamera(60.0f, (float)app->getWidth() / (float)app->getHeight(), 0.1f, 1000.0f);
    cameraControl = new TrackBallCameraController();
    cameraControl->setCamera(camera);
}

void prepareShader() {
    shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareTexture() {
    texture = new Texture("assets/textures/earth.jpg", 0);
}

void prepareState() {
    GL_CALL(glEnable(GL_DEPTH_TEST));
    GL_CALL(glDepthFunc(GL_LESS));
}

void prepareVAO() {
    geometry = Geometry::createSphere(6);
}

void render() {
    // clear buffer
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    // 1. bind current program
    shader->begin();
    shader->setInt("caoshenSampler", 0);
    shader->setMarix4x4("transform", transformMatrix);
    shader->setMarix4x4("viewMatrix", camera->getViewMatrix());
    shader->setMarix4x4("projectionMatrix", camera->getProjectionMatrix());

    // 2. bind current vao
    GL_CALL(glBindVertexArray(geometry->getVao()));

    // 3. send draw call
    GL_CALL(glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0));

    // 4. unbind
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
    app->setMouseCallBack(onMouse);
    app->setCursorCallBack(onCursor);
    app->setScrollCallBack(onScroll);

    // Set openGL view port and clear color
    GL_CALL(glViewport(0, 0, 800, 600));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    prepareTexture();
    prepareVAO();
    prepareShader();
    prepareCamera();
    prepareState();

    /* Loop until the user closes the window */
    while (app->update())
    {
        cameraControl->update();
        // render
        render();
    }

    app->destroy();
    delete shader;
    delete texture;
    return 0;
}