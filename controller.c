#include "controller.h"
#include <stdio.h>


void DetectPlayerMoveInput(PlayerCam* pcam, double deltaTime, FPSPlayer* player, Mesh* mesh, CollisionPacket* colPacket)
{
    //fwd, bwd, l, r
    float moveDistance = 10.0f*deltaTime;
    if (IsKeyDown(KEY_W))
    {   
        PlayerCamMoveForward(pcam, moveDistance, player, colPacket, mesh);
    }
    if (IsKeyDown(KEY_A))
    {
        PlayerCamMoveRight(pcam, -moveDistance, player);
    }
    if (IsKeyDown(KEY_S))
    {
        PlayerCamMoveForward(pcam, -moveDistance, player, colPacket, mesh);
    }
    if (IsKeyDown(KEY_D))
    {
        PlayerCamMoveRight(pcam, moveDistance, player);
    }
    
    
    //You'll probably throw the collide and slide here
    CalculatePlayerVelocity(player, deltaTime);
    CollideAndSlide(colPacket, player, mesh, deltaTime);
}

void PollPlayerInput(PlayerCam* pcam, double deltaTime, FPSPlayer* player, Mesh* mesh, CollisionPacket* colPacket)
{
    /*
        This is the implementation of an accumulated velocity movement system
        Rather than splitting everything up with separate key presses, this 
        system takes all of the inputs and inputs their velocities into one 
        vector that is used to direct the player for a new location
    */
    float moveSpeed = 10.0f;
    Vector3 inputVelocity = {0.0f, 0.0f, 0.0f};

    if (IsKeyDown(KEY_W))
    {
        Vector3 forward = GetCameraForwardVector(pcam);
        forward.y = 0;
        forward = Vector3Normalize(forward);
        inputVelocity = Vector3Add(inputVelocity, Vector3Scale(forward, moveSpeed));
    }
    if (IsKeyDown(KEY_S))
    {
        Vector3 backward = GetCameraForwardVector(pcam);
        backward.y = 0;
        backward = Vector3Normalize(backward);
        inputVelocity = Vector3Add(inputVelocity, Vector3Scale(backward, -moveSpeed));
    }

    //Left and right movement
    if (IsKeyDown(KEY_A))
    {
        Vector3 left = GetCameraRightVector(pcam);
        left.y = 0;
        left = Vector3Normalize(left);
        inputVelocity = Vector3Add(inputVelocity, Vector3Scale(left, -moveSpeed));
    }
    if (IsKeyDown(KEY_D))
    {
        Vector3 right = GetCameraRightVector(pcam);
        right.y = 0;
        right = Vector3Normalize(right);
        inputVelocity = Vector3Add(inputVelocity, Vector3Scale(right, moveSpeed));
    }

    //Scale by delta time to ensure a consistent movement speed
    inputVelocity = Vector3Scale(inputVelocity, deltaTime);

    //Apply the accumulated velocity to the player's current velocity
    player->velocity = inputVelocity;
    

    CollideAndSlide(colPacket, player, mesh, deltaTime);

    CalculatePlayerVelocity(player, deltaTime);

    
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

//Movement
void PlayerCamMoveForward(PlayerCam* pcam, float distance, FPSPlayer* player, CollisionPacket* colPacket, Mesh* mesh)
{
    Vector3 forwardVector = GetCameraForwardVector(pcam);

    forwardVector.y = 0;
    forwardVector = Vector3Normalize(forwardVector);

    forwardVector = Vector3Scale(forwardVector, distance);

    
    
    
    player->location = Vector3Add(pcam->position, forwardVector);

    pcam->position = player->location;
    pcam->target = Vector3Add(pcam->target, forwardVector);
    
    
}

void PlayerCamMoveRight(PlayerCam* pcam, float distance, FPSPlayer* player)
{
    Vector3 right = GetCameraRightVector(pcam);

    right.y = 0;
    right = Vector3Normalize(right);

    right = Vector3Scale(right, distance);
    player->location = Vector3Add(pcam->position, right);
    
    pcam->position = player->location;
    pcam->target = Vector3Add(pcam->target, right);
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

void CollideAndSlide(CollisionPacket* colPacket, FPSPlayer* player, Mesh* mesh, double deltaTime)
{
    colPacket->R3Position = player->location;
    colPacket->R3Velocity = player->velocity;

    Vector3 eSpacePosition = Vector3Divide(colPacket->R3Position, colPacket->eRadius);
    Vector3 eSpaceVelocity = Vector3Divide(colPacket->R3Velocity, colPacket->eRadius);

    colPacket->collisionRecursionDepth = 0;

    Vector3 finalPosition = CollideWithWorld(colPacket, eSpacePosition, eSpaceVelocity, mesh);

    //converting back to r3
    finalPosition = Vector3Multiply(finalPosition, colPacket->eRadius);

    player->location = finalPosition;
    // player->location.x = finalPosition.x;
    // player->location.z = finalPosition.z;
    // player->location.y = 2.0f;
    player->attachedCam->position = player->location;

    //Vector3 adjustedTarget = Vector3Add(player->attachedCam->target, player->velocity);
    //player->attachedCam->target = Vector3Add(finalPosition, adjustedTarget);

    player->attachedCam->target = Vector3Add(player->attachedCam->target, player->velocity);

    // if (colPacket->foundCollision && finalPosition.x != 0.0f && finalPosition.y != 0.0f && finalPosition.z != 0.0f)
    // {
    //     player->location = Vector3Add(player->attachedCam->position, finalPosition);
    //     player->attachedCam->position = player->location;
    //     Vector3 target = Vector3Multiply(colPacket->velocity, colPacket->eRadius);
    //     player->attachedCam->target = Vector3Add(player->attachedCam->target, target);
    // }
    
    //player->location = finalPosition;
}

Vector3 CollideWithWorld(CollisionPacket* colPacket, Vector3 pos, Vector3 vel, Mesh* mesh)
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
    //printf("%f, %f, %f\n", colPacket->normalizedVelocity.x, colPacket->normalizedVelocity.y, colPacket->normalizedVelocity.z);
    colPacket->basePoint = pos;
    colPacket->foundCollision = false;

    //check for collision
    PollCollision(colPacket, mesh);

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
    //Vector3Multiply(Vector3SubtractValue(destPoint, SignedDistanceToPlane(&slidingPlane, destPoint)), slidePlaneNormal);
    
    //Generate teh slide vector which will become our velocity vector on the next iteration
    Vector3 newVelocityVector = Vector3Subtract(newDestinationPoint, colPacket->intersectionPoint);

    //Recurse:

    if (Vector3Length(newVelocityVector) < veryCloseDistance)
    {
        return newBasePoint;
    }

    colPacket->collisionRecursionDepth++;
    return CollideWithWorld(colPacket, newBasePoint, newVelocityVector, mesh);
}