#include "cameraControl.h"
#include <iostream>

CameraControl::CameraControl() {}
CameraControl::~CameraControl() {}

void CameraControl::onMouse(int button, int action, double xpos, double ypos) {
    std::cout << "onMouse" << std::endl;
    bool pressed = action == GLFW_PRESS;

    if (pressed) {
        mCurrentX = xpos;
        mCurrentY = ypos;
    }

    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            mLeftMouseDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            mRightMouseDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            mMiddleMouseDown = pressed;
            break;
    }

}

void CameraControl::onCurcor(double xpos, double ypos) {
    std::cout << "onCurcor" << std::endl;
}

void CameraControl::onKey(int key, int action, int mods) {
    std::cout << "onKey" << std::endl;
    if (action == GLFW_REPEAT) {
        return;
    }

    bool pressed = action == GLFW_PRESS;

    mKeyMap[key] = pressed;
}

void CameraControl::update() {
}