#include "player.h"
#include <stdio.h>

void PlayerSetup(FPSPlayer* player, PlayerCam* cam, UIElements** hud, enum Gamemode* mode)
{
    //player->location = (Vector3){0.0, 5.0, -21.0};
    player->location = (Vector3){6.0, 5.0, 2.0};
    player->currPos = player->location;
    player->lastPos = player->location;
    player->velocity = (Vector3){0.0f, 0.0f, 0.0f};
    player->attachedCam = cam;
    player->firstInput = true;
    player->playerHUD = hud;
    player->gamemode = mode;
    player->showPlayerLocation = true;
    player->puzzleInputEnabled = true;
    player->shouldTickPlayer = false;
}

void PollPlayer(float deltaTime, PlayerCam* pcam, FPSPlayer* player, CollisionPacket* colPacket, modelInfo** models, int numOfModels)
{
    PollPlayerInput(pcam, deltaTime, player, colPacket, models, numOfModels);
    DetectPlayerLookInput(pcam);

    
    //printf("%f, %f, %f\n", pcam->position.x, pcam->position.y, pcam->position.z);
}

void PollPlayerSecondary(FPSPlayer* player, Raycast* interactRay, QueryBox** areaBoxes, enum Gamemode* mode, Interactable* interactedItem, int numOfAreaQueryBoxes, bool* hideHideableObjects, float deltaTime)
{
    PollPlayerSecondaryInputs(player, interactRay, areaBoxes, mode, interactedItem, numOfAreaQueryBoxes);
    PollDebugInputs(hideHideableObjects);    
}

void DrawPlayerCollisionCapsule(Vector3 location)
{
    DrawCapsuleWires((Vector3){location.x, location.y + 1.0f, location.z}, (Vector3){location.x, location.y - 1.0f, location.z}, 1.0f, 8, 8, VIOLET);
}

void PollPlayerPuzzle(FPSPlayer* player, float deltaTime, Interactable* interactedItem, enum Gamemode* mode)
{
    PollPlayerPuzzleInputs(interactedItem, mode);

    if (player->shouldTickPlayer == true)
    {
        LerpPlayerToLoc(player, deltaTime);
    }
}

void PollPlayerOverlaps(OverlapBox** queryList, FPSPlayer* player)
{
    PollOverlaps(queryList, player);
}

void LerpPlayerToLoc(FPSPlayer* player, float deltaTime)
{
    bool turnedHead = TurnPlayerHead(player, deltaTime); 
    bool movedEntirely = false;
    if (Vector3Distance(player->location, player->b) > 0.01f)
    {
        Vector3 direction = Vector3Normalize(Vector3Subtract(player->b, player->location));
        direction  = (Vector3){direction.x, 0.0f, direction.z};
	
	player->location = Vector3Add(player->location, Vector3Scale(direction, 4.0f * deltaTime));

	Vector3 offset = Vector3Subtract(player->attachedCam->target, player->attachedCam->position);
        player->attachedCam->position = player->location;
	player->attachedCam->target = Vector3Add(player->attachedCam->position, offset);
    }
    else
    {
        player->location = player->b;
        player->attachedCam->position = player->location;
	movedEntirely = true;
    }

    if (turnedHead == true && movedEntirely == true)
    {
	player->shouldTickPlayer = false;
    }
    
}

bool TurnPlayerHead(FPSPlayer* player, float deltaTime)	
{
    if (player->lerpAmount >= 1.0f)
    {
	return true;
    }

    player->lerpAmount += 0.1 * deltaTime;
    
    Vector3 updatedLoc = Vector3Lerp(player->attachedCam->target, player->lookAtLoc, player->lerpAmount);
    player->attachedCam->target = updatedLoc;
    return false;
}
