#include "player.h"
#include <stdio.h>

void PlayerSetup(FPSPlayer* player, PlayerCam* cam, UIElements** hud, enum Gamemode* mode)
{
    player->location = (Vector3){0.0, 5.0, -21.0};
    //player->location = (Vector3){6.0, 5.0, 2.0};
    player->currPos = player->location;
    player->lastPos = player->location;
    player->velocity = (Vector3){0.0f, 0.0f, 0.0f};
    player->attachedCam = cam;
    player->firstInput = true;
    player->playerHUD = hud;
    player->gamemode = mode;
    player->showPlayerLocation = true;
}

void PollPlayer(float deltaTime, PlayerCam* pcam, FPSPlayer* player, CollisionPacket* colPacket, modelInfo** models, int numOfModels)
{
    PollPlayerInput(pcam, deltaTime, player, colPacket, models, numOfModels);
    DetectPlayerLookInput(pcam);

    
    //printf("%f, %f, %f\n", pcam->position.x, pcam->position.y, pcam->position.z);
    
}

void PollPlayerSecondary(FPSPlayer* player, Raycast* interactRay, QueryBox** areaBoxes, enum Gamemode* mode, Interactable* interactedItem, int numOfAreaQueryBoxes)
{
    PollPlayerSecondaryInputs(player, interactRay, areaBoxes, mode, interactedItem, numOfAreaQueryBoxes);
    
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
