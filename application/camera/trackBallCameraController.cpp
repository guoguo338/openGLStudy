//
// Created by ByteDance on 2024/6/16.
//

#include "trackBallCameraController.h"

TrackBallCameraController::TrackBallCameraController() {

}

TrackBallCameraController::~TrackBallCameraController() {

}

void TrackBallCameraController::onCursor(double xpos, double ypos) {
    if (mLeftMouseDown) {
        //adjust camera parameters
        float deltaX = (xpos - mCurrentX) * mSensitivity;
        float deltaY = (ypos - mCurrentY) * mSensitivity;

        pitch(-deltaY);
        yaw(-deltaX);
    } else if (mRightMouseDown) {
        //adjust camera parameters
        float deltaX = (xpos - mCurrentX) * mMovedSpeed;
        float deltaY = (ypos - mCurrentY) * mMovedSpeed;

        mCamera->mPosition += mCamera->mUp * deltaY;
        mCamera->mPosition -= mCamera->mRight * deltaX;
    }

    mCurrentX = xpos;
    mCurrentY = ypos;
}

void TrackBallCameraController::pitch(float angle) {
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
    mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f); // vec4 assigned to vec3, give xyz
    mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}

void TrackBallCameraController::yaw(float angle) {
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    mCamera->mUp = mat * mat * glm::vec4(mCamera->mUp, 0.0f);
    mCamera->mRight = mat * mat * glm::vec4(mCamera->mRight, 0.0f);
    mCamera->mPosition = mat * mat * glm::vec4(mCamera->mPosition, 1.0f);
}
