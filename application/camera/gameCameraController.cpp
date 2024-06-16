//
// Created by ByteDance on 2024/6/16.
//

#include "gameCameraController.h"

GameCameraControl::GameCameraControl(){}
GameCameraControl::~GameCameraControl(){}

void GameCameraControl::onCursor(double xpos, double ypos) {
    float deltaX = (xpos - mCurrentX) * mSensitivity;
    float deltaY = (ypos - mCurrentY) * mSensitivity;

    if (mRightMouseDown) {
        pitch(deltaY);
        yaw(deltaX);
    }

    mCurrentX = xpos;
    mCurrentY = ypos;
}

void GameCameraControl::pitch(float angle) {
    mPitch += angle;
    if (mPitch > 89.0f || mPitch < -89.0f) {
        mPitch -= angle;
        return;
    }
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
    mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);

}

void GameCameraControl::yaw(float angle) {
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
    mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
}
