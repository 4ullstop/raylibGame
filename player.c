#include "player.h"
#include <stdio.h>

void PlayerSetup(FPSPlayer* player, PlayerCam* cam)
{
    player->location = (Vector3){0.0f, 2.0f, 4.0f};
    player->currPos = player->location;
    player->lastPos = player->location;
    player->velocity = (Vector3){0.0f, 0.0f, 0.0f};
    player->attachedCam = cam;
}

void PollPlayer(float deltaTime, PlayerCam* pcam, FPSPlayer* player, CollisionPacket* colPacket, Mesh* mesh)
{
    DetectPlayerMoveInput(pcam, deltaTime, player);
    DetectPlayerLookInput(pcam);
    CollideAndSlide(colPacket, player, mesh, deltaTime);
}

void DrawPlayerCollisionCapsule(Vector3 location)
{
    DrawCapsuleWires((Vector3){location.x, location.y + 1.0f, location.z}, (Vector3){location.x, location.y - 1.0f, location.z}, 1.0f, 8, 8, VIOLET);
}



