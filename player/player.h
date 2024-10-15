#ifndef RAYLIB_CAMERA_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "controller.h"
#endif

void PollPlayer(float deltaTime, PlayerCam* pcam, FPSPlayer* player, CollisionPacket* colPacket, Mesh* mesh, modelInfo** models);

void DrawPlayerCollisionCapsule(Vector3 location);

void PlayerSetup(FPSPlayer* player, PlayerCam* cam);




