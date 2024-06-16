//
// Created by ByteDance on 2024/6/15.
//

#include "perspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far) {
    mFovy = fovy;
    mAspect = aspect;
    mNear = near;
    mFar = far;
}

PerspectiveCamera::~PerspectiveCamera() {
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() {
    return glm::perspective(glm::radians(mFovy), mAspect, mNear, mFar);
}
