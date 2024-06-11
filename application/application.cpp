#include "application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <wrapper/checkError.h>

Application* Application::mInstance = nullptr;

Application* Application::getInstance() {
    if (mInstance == nullptr)
    {
        mInstance = new Application();
    }
    return mInstance;
}

Application::Application() {}

Application::~Application() {
    delete mInstance;
    mInstance = nullptr;
}

bool Application::init(const int &width, const int &height) {
    mWidth = width;
    mHeight = height;

    glfwInit();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    /* Create a windowed mode window and its OpenGL context */
    mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGLStudy", NULL, NULL);
    if (mWindow == NULL){
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(mWindow);

    // Load all openGL functions of current version
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        cout << "Failed to initialize GLAD" << endl;
        return false;
    }

    glfwSetWindowUserPointer(mWindow, this);

    glfwSetFramebufferSizeCallback(mWindow, framebufferSizeCallback);
    glfwSetKeyCallback(mWindow, keyCallback);

    return true;
}

bool Application::update() {
    if (glfwWindowShouldClose(mWindow)) {
        return false;
    }

    /* Poll for and process events */
    glfwPollEvents();

    glfwSwapBuffers(mWindow);

    return true;
}

void Application::destroy() {
    // Clean up and exit
    glfwDestroyWindow(mWindow);
    mWindow = nullptr;
    glfwTerminate();
}

void Application::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    Application *self = (Application *)glfwGetWindowUserPointer(window);
    if (self->mResizeCallback != nullptr) {
        self->mResizeCallback(width, height);
    }
}

void Application::keyCallback(GLFWwindow *window, int key, int scancode, int action, int modes) {
    Application *self = (Application *)glfwGetWindowUserPointer(window);
    if (self->mKeyCallBack != nullptr) {
        self->mKeyCallBack(key, action, modes);
    }
}