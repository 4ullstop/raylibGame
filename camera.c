#include "camera.h"
#include <stdio.h>


//sets up default items for camera and returns the camera mode
void PlayerCamSetup(PlayerCam* pcam)
{
    DisableCursor();
    pcam->position = (Vector3){0.0f, 2.0f, 4.0f};
    pcam->target = (Vector3){0.0f, 2.0f, 0.0f};
    pcam->up = (Vector3){0.0f, 1.0f, 0.0f};
    pcam->fov = 60.0f;
}

void StartMode3D(PlayerCam pcam)
{
    rlDrawRenderBatchActive();

    rlMatrixMode(RL_PROJECTION);
    rlPushMatrix();
    rlLoadIdentity();

    float aspect = (float)800/(float)450;

    double  top = RL_CULL_DISTANCE_NEAR*tan(pcam.fov*0.5*DEG2RAD);
    double  right = top*aspect;

    rlFrustum(-right, right, -top, top, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);

    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();

    Matrix matView = MatrixLookAt(pcam.position, pcam.target, pcam.up);
    rlMultMatrixf(MatrixToFloat(matView));

    rlEnableDepthTest();
}

void Complete3DMode(void)
{
    rlDrawRenderBatchActive();

    rlMatrixMode(RL_PROJECTION);
    rlPopMatrix();

    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();

    float scaleRatio = (float)800/(float)450;

    Matrix screenScale = MatrixIdentity();
    rlMultMatrixf(MatrixToFloat(screenScale));

    rlDisableDepthTest();

}