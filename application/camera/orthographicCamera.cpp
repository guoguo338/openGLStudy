#include "orthographicCamera.h"

OrghographicCamera::OrghographicCamera(float l, float r, float t, float b, float n, float f) {
    mLeft = l;
    mRight = r;
    mTop = t;
    mBottom = b;
    mNear = n;
    mFar = f;
}

OrghographicCamera::~OrghographicCamera() {

}

glm::mat4 OrghographicCamera::getProjectionMatrix() {
    float scale = std::pow(2.0f, mScale);
    return glm::ortho(mLeft * scale, mRight * scale, mBottom * scale, mTop * scale, mNear, mFar);
}

void OrghographicCamera::scale(float deltaScale) {
    mScale += deltaScale;
}