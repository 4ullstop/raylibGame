#ifndef CONTROLLER_HEADER
#define CONTROLLER_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "camera.h"
#include "../collision/detectcollision.h"  
#include "../collision/collisionplane.h"
#include "../collision/raycasting.h"
//#include "../collision/interactionbox.h"
#endif

void DetectPlayerLookInput(PlayerCam* pcam);

Vector3 GetCameraForwardVector(PlayerCam* camera);

void InputCamYaw(PlayerCam* pcam, float angle);

void InputCamPitch(PlayerCam* pcam, float angle, bool lockView, bool rotateUp);

Vector3 GetCameraUpVector(PlayerCam* pcam);

Vector3 GetCameraRightVector(PlayerCam* pcam);

void CalculatePlayerVelocity(FPSPlayer* player, double deltaTime);

void CollideAndSlide(CollisionPacket* colPacket, FPSPlayer* player, double deltaTime, modelInfo** models);

Vector3 CollideWithWorld(CollisionPacket* colPacket, Vector3 pos, Vector3 vel, modelInfo** models);

void PollPlayerInput(PlayerCam* pcam, double deltaTime, FPSPlayer* player, CollisionPacket* colPacket, modelInfo** models);

void PollPlayerSecondaryInputs(FPSPlayer* player, Raycast* interactRay, ColBox* localBox);