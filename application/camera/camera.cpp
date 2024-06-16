#include "camera.h"

Camera::Camera() {
}

Camera::~Camera() {
}

glm::mat4 Camera::getViewMatrix() {
    //lookat
    //~eye: position of camera
    //~center: center point
    //~top: top (replaced with mUP)
    glm::vec3 front = glm::cross(mUp, mRight);
    glm::vec3 center = mPosition + front;

    return glm::lookAt(mPosition, center, mUp);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::identity<glm::mat4>();
}

void Camera::scale(float deltaScale) {
}
