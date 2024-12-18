#include "controller.h"
#include <stdio.h>


void PollPlayerInput(PlayerCam* pcam, double deltaTime, FPSPlayer* player, CollisionPacket* colPacket, modelInfo** models, int numOfModels)
{
    /*
        This is the implementation of an accumulated velocity movement system
        Rather than splitting everything up with separate key presses, this 
        system takes all of the inputs and inputs their velocities into one 
        vector that is used to direct the player for a new location
    */
    float moveSpeed = 10.0f;
    Vector3 inputVelocity = {0.0f, 0.0f, 0.0f};
    bool keyPressed = false;
    if (IsKeyDown(KEY_W))
    {
        Vector3 forward = GetCameraForwardVector(pcam);
        forward.y = 0;
        forward = Vector3Normalize(forward);
        inputVelocity = Vector3Add(inputVelocity, Vector3Scale(forward, moveSpeed));
        keyPressed = true;
    }
    if (IsKeyDown(KEY_S))
    {
        Vector3 backward = GetCameraForwardVector(pcam);
        backward.y = 0;
        backward = Vector3Normalize(backward);
        inputVelocity = Vector3Add(inputVelocity, Vector3Scale(backward, -moveSpeed));
        keyPressed = true;
    }

    //Left and right movement
    if (IsKeyDown(KEY_A))
    {
        Vector3 left = GetCameraRightVector(pcam);
        left.y = 0;
        left = Vector3Normalize(left);
        inputVelocity = Vector3Add(inputVelocity, Vector3Scale(left, -moveSpeed));
        keyPressed = true;
    }
    if (IsKeyDown(KEY_D))
    {
        Vector3 right = GetCameraRightVector(pcam);
        right.y = 0;
        right = Vector3Normalize(right);
        inputVelocity = Vector3Add(inputVelocity, Vector3Scale(right, moveSpeed));
        keyPressed = true;
    }

    if (keyPressed == true)
    {
        if (player->firstInput == true)
        {
            player->playerHUD[0]->startHide = true;
        }
    }

    player->playerLookForward = GetCameraForwardVector(pcam);
    //Scale by delta time to ensure a consistent movement speed
    inputVelocity = Vector3Scale(inputVelocity, deltaTime);

    //Apply the accumulated velocity to the player's current velocity
    player->velocity = inputVelocity;
    
    CollideAndSlide(colPacket, player, deltaTime, models, numOfModels);

    CalculatePlayerVelocity(player, deltaTime);
}

void PollPlayerSecondaryInputs(FPSPlayer* player, Raycast* interactRay, QueryBox** areaBoxes, enum Gamemode* mode, Interactable* interactedItem, int numOfAreaQueryBoxes)
{
    if (IsKeyPressed(KEY_E))
    {
        /*
            Ok... guess I'm making my own raycast system
        */
        printf("interact button pressed\n");
        interactRay->closestBox = NULL;
        interactRay->foundCollision = false;
        Vector3 forward = GetCameraForwardVector(player->attachedCam);
        for (int i = 0; i < numOfAreaQueryBoxes; i++)
        {
            
            if (IsPointInColBox(areaBoxes[i]->areaBox, player->location))
            {
                for (int j = 0; j < areaBoxes[i]->numberOfInteractables; j++)
                {
                    printf("Interactable index: %i\n", j);
                    printf("Interactable index of j: %i\n", areaBoxes[i]->associatedInteractables[j]->id);
                    bool hit = CastRayLine(player, forward, interactRay, areaBoxes[i]->associatedInteractables[j]->colBox, mode, j);
                    printf("rolling\n");
                }
                if (interactRay->foundCollision)
                {
                    if (interactRay->closestBox == NULL)
                    {
                        printf("ERROR CLOSEST BOX IS NULL\n");
                        return;
                    }
                    if (areaBoxes[i]->associatedInteractables[interactRay->associatedIndex]->associatedPuzzle->puzzleState == EPS_inactive)
                    {
                        printf("PUZZLE IS INACTIVE, INTERACTION CANCELLED\n");
                        return;
                    }
                    printf("closestbox id: %i\n", interactRay->closestBox->id);

                    interactRay->closestBox->interact(player, interactRay->closestBox);
                    *interactedItem = *areaBoxes[i]->associatedInteractables[interactRay->associatedIndex];
                    interactedItem->associatedPuzzle->shouldReadTick = true;
                    LerpPlayer(player, interactedItem->associatedPuzzle);
                    *mode = EGM_Puzzle;
                    
                }
            }
        }
    }
    if (IsKeyPressed(KEY_F))
    {
        *mode = EGM_Inactive;
        ShowCursor();
    }
}

void LerpPlayer(FPSPlayer* player, ButtonMaster* puzzle)
{
    float distance = Vector3Distance(player->location, puzzle->location);
    if (distance <= 5.0f)
    {
        printf("distance is checked\n");
        
        player->a = player->location;
        Vector3 normalStart = Vector3Add(puzzle->puzzleNormalDirection, puzzle->location);
        Vector3 normalEnd = Vector3Add(puzzle->location, Vector3Scale(puzzle->puzzleNormalDirection, 2.0f));
        player->b = normalEnd;
        	
	player->lookAtLoc = puzzle->location;
	player->lerpAmount = 0.0f;
	
        player->shouldTickPlayer = true;
        printf("player should start ticking\n");
        
    }
}

void PollPlayerPuzzleInputs(Interactable* interactedItem, enum Gamemode* mode)
{
    if (interactedItem->associatedPuzzle->player->puzzleInputType == EPIT_Disabled) return;
    bool directionalKeyPressed = false;
    if (interactedItem->associatedPuzzle->player->puzzleInputEnabled == false) return;

    if (IsKeyPressed(KEY_R))
    {
        MoveCursor(ED_Reset, interactedItem, mode);
    }
    
    if (interactedItem->associatedPuzzle->player->puzzleInputType == EPIT_ResetOnly) return;
    if (IsKeyPressed(KEY_LEFT))
    {
        MoveCursor(ED_Left, interactedItem, mode);
        directionalKeyPressed = true;
    }
    if (IsKeyPressed(KEY_UP))
    {
        MoveCursor(ED_Up, interactedItem, mode);
        directionalKeyPressed = true;
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
        MoveCursor(ED_Right, interactedItem, mode);
        directionalKeyPressed = true;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        MoveCursor(ED_Down, interactedItem, mode);
        directionalKeyPressed = true;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        MoveCursor(ED_Enter, interactedItem, mode);
    }

    if (IsKeyPressed(KEY_E))
    {
        *mode = EGM_Normal;
        interactedItem->associatedPuzzle = NULL;
        interactedItem = NULL;
    }

    if (directionalKeyPressed == true)
    {
        if (interactedItem->showsArrowKeyHint == true && interactedItem->id == 2)
        {
            interactedItem->associatedPuzzle->player->playerHUD[3]->hidden = true;
            interactedItem->showsArrowKeyHint = false;
        }
        interactedItem->associatedPuzzle->shouldBlinkCursor = true;
    }
}

void CalculatePlayerVelocity(FPSPlayer* player, double deltaTime)
{
    
    float x = (player->lastPos.x - player->location.x) / deltaTime;
    float y = (player->lastPos.y - player->location.y) / deltaTime;
    float z = (player->lastPos.z - player->location.z) / deltaTime;

    
    Vector3 vel = {x, y, z};
    player->velocity = Vector3Scale(vel, deltaTime);
    player->lastPos = player->location;
    
}

void DetectPlayerLookInput(PlayerCam* pcam)
{
    Vector2 mouseDelta = GetMouseDelta();

    InputCamPitch(pcam, -mouseDelta.y*0.003f, true, false);
    InputCamYaw(pcam, -mouseDelta.x*0.003f);
}

//Get Camera Vectors
Vector3 GetCameraForwardVector(PlayerCam* camera)
{
    return Vector3Normalize(Vector3Subtract(camera->target, camera->position));
}

Vector3 GetCameraUpVector(PlayerCam* pcam)
{
    return Vector3Normalize(pcam->up);
}

Vector3 GetCameraRightVector(PlayerCam* pcam)
{
    Vector3 forward = GetCameraForwardVector(pcam);
    Vector3 up = GetCameraUpVector(pcam);

    return Vector3CrossProduct(forward, up);
}


//Pitch and  yaw inputs
void InputCamYaw(PlayerCam* pcam, float angle)
{
    Vector3 up = GetCameraUpVector(pcam);

    Vector3 targetPosition = Vector3Subtract(pcam->target, pcam->position);

    targetPosition = Vector3RotateByAxisAngle(targetPosition, up, angle);

    pcam->target = Vector3Add(pcam->position, targetPosition);
}

void InputCamPitch(PlayerCam* pcam, float angle, bool lockView, bool rotateUp)
{
    Vector3 up = GetCameraUpVector(pcam);

    Vector3 targetPosition = Vector3Subtract(pcam->target, pcam->position);

    if (lockView)
    {
        float maxAngleUp = Vector3Angle(up, targetPosition);
        maxAngleUp -= 0.001f;
        if(angle > maxAngleUp) angle = maxAngleUp;

        float maxAngleDown = Vector3Angle(Vector3Negate(up), targetPosition);
        maxAngleDown *= -1.0f;
        maxAngleDown += 0.001f;
        if(angle < maxAngleDown) angle = maxAngleDown;
    }

    Vector3 right = GetCameraRightVector(pcam);
    
    targetPosition = Vector3RotateByAxisAngle(targetPosition, right, angle);

    pcam->target = Vector3Add(pcam->position, targetPosition);

    if (rotateUp)
    {
        pcam->up = Vector3RotateByAxisAngle(pcam->up, right, angle);
    }
}

void CollideAndSlide(CollisionPacket* colPacket, FPSPlayer* player, double deltaTime, modelInfo** models, int numberOfModels)
{
    //colPacket->R3Position = player->location;
    colPacket->R3Position = colPacket->eRadius.y > 1.0f ?
	(Vector3){player->location.x, colPacket->eRadius.y + player->location.y, player->location.z} :
	player->location;
    colPacket->R3Velocity = player->velocity;

    Vector3 eSpacePosition = Vector3Divide(colPacket->R3Position, colPacket->eRadius);
    Vector3 eSpaceVelocity = Vector3Divide(colPacket->R3Velocity, colPacket->eRadius);

    colPacket->collisionRecursionDepth = 0;

    Vector3 finalPosition = CollideWithWorld(colPacket, eSpacePosition, eSpaceVelocity, models, numberOfModels);
    player->location = finalPosition;

    Vector3 gravity = (Vector3){0.0, -9.81 * deltaTime, 0.0};

    //Gravity 
    //colPacket->R3Position = Vector3Multiply(finalPosition, colPacket->eRadius);
    colPacket->R3Velocity = gravity;
    
    eSpaceVelocity = Vector3Divide(gravity, colPacket->eRadius);

    colPacket->collisionRecursionDepth = 0;

    finalPosition = CollideWithWorld(colPacket, Vector3Divide(player->location, colPacket->eRadius), eSpaceVelocity, models, numberOfModels);

    //converting back to r3
    finalPosition = Vector3Multiply(finalPosition, colPacket->eRadius);

    player->location = finalPosition;
    player->attachedCam->position = player->location;

    player->attachedCam->target = Vector3Add(player->attachedCam->target, player->velocity);
}

Vector3 CollideWithWorld(CollisionPacket* colPacket, Vector3 pos, Vector3 vel, modelInfo** models, int numberOfModels)
{
    float unitScale = 100.f / 100.f;
    float veryCloseDistance = 0.005f * unitScale;

    
    if (colPacket->collisionRecursionDepth > 5)
    {
        return pos;
    }



    colPacket->velocity = vel;
    colPacket->normalizedVelocity = vel;
    colPacket->normalizedVelocity = Vector3Normalize(colPacket->normalizedVelocity);
    colPacket->basePoint = pos;
    colPacket->foundCollision = false;
    //check for collision
    for (int i = 0; i < numberOfModels; i++)
    {
        if (models[i]->collisionDisabled == true) continue;
        PollCollision(colPacket, models[i]->model.meshes, models[i]->modelLocation);
    }

    //if no collision move along the velocity
    if (colPacket->foundCollision == false)
    {
        
        return Vector3Add(pos, vel);
    }

    /*
        Collision has occured
    */

    //the original destination point
    Vector3 destPoint = Vector3Add(pos, vel);
    Vector3 newBasePoint = pos;

    /*
        Only update if we are not already very close
        and if so we only move very close to intersection not
        to the exact spot
    */
    if (colPacket->nearestDistance>=veryCloseDistance)
    {
        Vector3 v = vel;
        v = Vector3Scale(Vector3Normalize(v), colPacket->nearestDistance - veryCloseDistance);
        newBasePoint = Vector3Add(colPacket->basePoint, v);

        /*
            Adjust the polygon intersetion point so sliding the plane
            will be unaffected by the fact that we move slightly less
            than collision tells us
        */
        v = Vector3Normalize(v);
        colPacket->intersectionPoint = Vector3Subtract(colPacket->intersectionPoint, Vector3Scale(v, veryCloseDistance));
    }

    Vector3 slidePlaneOrigin = colPacket->intersectionPoint;
    Vector3 slidePlaneNormal = Vector3Normalize(Vector3Subtract(newBasePoint, colPacket->intersectionPoint));


    CPlane slidingPlane = {0};
    ConstructCPlane(&slidingPlane, slidePlaneOrigin, slidePlaneNormal);

    Vector3 newDestinationPoint = Vector3Subtract(destPoint, Vector3Scale(slidePlaneNormal, SignedDistanceToPlane(&slidingPlane, destPoint)));
    
    //Generate teh slide vector which will become our velocity vector on the next iteration
    Vector3 newVelocityVector = Vector3Subtract(newDestinationPoint, colPacket->intersectionPoint);

    //Recurse:

    if (Vector3Length(newVelocityVector) < veryCloseDistance)
    {
        return newBasePoint;
    }

    colPacket->collisionRecursionDepth++;
    return CollideWithWorld(colPacket, newBasePoint, newVelocityVector, models, numberOfModels);
}




void PollDebugInputs(bool* hideHideableObjects)
{
    if (IsKeyPressed(KEY_H))
    {
        *hideHideableObjects = !*hideHideableObjects;
    }
}
