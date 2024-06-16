#pragma once

#include "cameraControl.h"

class GameCameraControl : public CameraControl {
public:
    GameCameraControl();
    ~GameCameraControl();

    void onCursor(double xpos, double ypos) override;

private:
    void pitch(float angle);
    void yaw(float angle);

private:
    float mPitch{0.0f};
};