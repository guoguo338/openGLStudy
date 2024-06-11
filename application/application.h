#pragma once
#include <iostream>

using namespace std;

#define app Application::getInstance()

class GLFWwindow;

class Application {
public:
    ~Application();

    static Application* getInstance();

    bool init(const int &width = 800, const int &height = 600);

    bool update();

    void destroy();

    uint32_t getWidth() const {return mWidth;}
    uint32_t getHeight() const {return mHeight;}
private:
    static Application *mInstance;

    uint32_t mWidth{0};
    uint32_t mHeight{0};
    GLFWwindow *mWindow{nullptr};

    Application();
};