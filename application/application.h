#pragma once
#include <iostream>

using namespace std;

#define app Application::getInstance()

class GLFWwindow;

using ResizeCallback = void(*)(int width, int height);
using KeyCallBack = void(*)(int key, int action, int modes);
using MouseCallBack = void(*)(int button, int action, int modes);
using CursorCallBack = void(*)(double xpos, double ypos);

class Application {
public:
    ~Application();

    static Application* getInstance();

    bool init(const int &width = 800, const int &height = 600);

    bool update();

    void destroy();

    void setResizeCallback(ResizeCallback callback) {mResizeCallback = callback;}
    void setKeyCallBack(KeyCallBack callback) {mKeyCallBack = callback;}
    void setMouseCallBack(MouseCallBack callback) {mMouseCallBack = callback;}
    void setCursorCallBack(CursorCallBack callback) {mCursorCallBack = callback;}

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int modes);
    static void mouseCallback(GLFWwindow *window, int button, int action, int modes);
    static void cursorCallback(GLFWwindow *window, double xpos, double ypos);

    uint32_t getWidth() const {return mWidth;}
    uint32_t getHeight() const {return mHeight;}
    void getCursorPosition(double* x, double* y);

private:
    static Application *mInstance;

    uint32_t mWidth{0};
    uint32_t mHeight{0};
    GLFWwindow *mWindow{nullptr};

    ResizeCallback mResizeCallback;
    KeyCallBack mKeyCallBack;
    MouseCallBack mMouseCallBack;
    CursorCallBack mCursorCallBack;
    Application();
};