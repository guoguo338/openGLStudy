#pragma once

#include "glFramework/core.h"

class Camera {
public:
    Camera();
    ~Camera();

    glm::mat4 getViewMatrix();
    virtual glm::mat4 getProjectionMatrix();
public:
    glm::vec3 mPosition{0.0f, 0.0f, 4.0f};
    glm::vec3 mUp{0.0f, 1.0f, 0.0f};
    glm::vec3 mRight{1.0f, 1.0f, 0.0f};
};