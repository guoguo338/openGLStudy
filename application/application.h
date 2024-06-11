#pragma once
#include <iostream>

using namespace std;

#define app Application::getInstance()

class Application {
public:
    ~Application();
    static Application* getInstance();
    void test()
    {
        std::cout << "App test"<<endl;
    }
private:
    static Application *mInstance;
    Application();
};