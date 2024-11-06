#include "player.h"
#include <stdio.h>

void PlayerSetup(FPSPlayer* player, PlayerCam* cam, UIElements** hud, enum Gamemode* mode)
{
    player->location = (Vector3){0.0, 5.0, 4.0};
    player->currPos = player->location;
    player->lastPos = player->location;
    player->velocity = (Vector3){0.0f, 0.0f, 0.0f};
    player->attachedCam = cam;
    player->firstInput = true;
    player->playerHUD = hud;
    player->gamemode = mode;
}

void PollPlayer(float deltaTime, PlayerCam* pcam, FPSPlayer* player, CollisionPacket* colPacket, modelInfo** models)
{
    //DetectPlayerMoveInput(pcam, deltaTime, player, mesh, colPacket);
    
    PollPlayerInput(pcam, deltaTime, player, colPacket, models);
    DetectPlayerLookInput(pcam);
}

void PollPlayerSecondary(FPSPlayer* player, Raycast* interactRay, QueryBox** areaBoxes, enum Gamemode* mode, Interactable* interactedItem)
{
    PollPlayerSecondaryInputs(player, interactRay, areaBoxes, mode, interactedItem);
}

void DrawPlayerCollisionCapsule(Vector3 location)
{
    DrawCapsuleWires((Vector3){location.x, location.y + 1.0f, location.z}, (Vector3){location.x, location.y - 1.0f, location.z}, 1.0f, 8, 8, VIOLET);
}

void PollPlayerPuzzle(Interactable* interactedItem, enum Gamemode* mode)
{
    PollPlayerPuzzleInputs(interactedItem, mode);
}

void PollPlayerOverlaps(OverlapBox** queryList, FPSPlayer* player)
{
    PollOverlaps(queryList, player);
}
