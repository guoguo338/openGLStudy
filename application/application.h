#pragma once
#include <iostream>

using namespace std;

#define app Application::getInstance()

class GLFWwindow;

using ResizeCallback = void(*)(int width, int height);

class Application {
public:
    ~Application();

    static Application* getInstance();

    bool init(const int &width = 800, const int &height = 600);

    bool update();

    void destroy();

    void setResizeCallback(ResizeCallback callback) {mResizeCallback = callback;}

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

    uint32_t getWidth() const {return mWidth;}
    uint32_t getHeight() const {return mHeight;}
private:
    static Application *mInstance;

    uint32_t mWidth{0};
    uint32_t mHeight{0};
    GLFWwindow *mWindow{nullptr};

    ResizeCallback mResizeCallback;
    Application();
};