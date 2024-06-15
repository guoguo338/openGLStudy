#pragma once

#include "camera.h"

class OrghographicCamera: public Camera{
public:
    OrghographicCamera(float l, float r, float t, float b, float n, float f);
    ~OrghographicCamera();

    glm::mat4 getProjectionMatrix() override;

private:
    float mLeft = 0.0f;
    float mRight = 0.0f;
    float mTop = 0.0f;
    float mBottom = 0.0f;
    float mNear = 0.0f;
    float mFar = 0.0f;
};