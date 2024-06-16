#pragma once

#include "cameraControl.h"

class TrackBallCameraController : public CameraControl{
public:
    TrackBallCameraController();
    ~TrackBallCameraController();

    void onCursor(double xpos, double ypos) override;
    void pitch(float angle);
    void yaw(float angle);
    void onScroll(float offset);

private:
    float mMovedSpeed = 0.04f;
};