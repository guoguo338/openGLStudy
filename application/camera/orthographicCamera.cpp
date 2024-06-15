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
    return glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
}