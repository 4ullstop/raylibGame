#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "camera.h"
#include "detectcollision.h"  
#include "collisionplane.h"
#endif

void DetectPlayerMoveInput(PlayerCam* pcam, double deltaTime, FPSPlayer* player);

void DetectPlayerLookInput(PlayerCam* pcam);

void PlayerCamMoveForward(PlayerCam* pcam, float distance, FPSPlayer* player);

void PlayerCamMoveRight(PlayerCam* pcam, float distance, FPSPlayer* player);

Vector3 GetCameraForwardVector(PlayerCam* camera);

void InputCamYaw(PlayerCam* pcam, float angle);

void InputCamPitch(PlayerCam* pcam, float angle, bool lockView, bool rotateUp);

Vector3 GetCameraUpVector(PlayerCam* pcam);

Vector3 GetCameraRightVector(PlayerCam* pcam);

void CalculatePlayerVelocity(FPSPlayer* player, double deltaTime);

void CollideAndSlide(CollisionPacket* colPacket, FPSPlayer* player, Mesh* mesh, double deltaTime);

Vector3 CollideWithWorld(CollisionPacket* colPacket, Vector3 pos, Vector3 vel, Mesh* mesh);

