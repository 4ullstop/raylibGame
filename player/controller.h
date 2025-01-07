#ifndef CONTROLLER_HEADER
#define CONTROLLER_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "camera.h"
#include "../collision/detectcollision.h"  
#include "../collision/collisionplane.h"
#include "../collision/raycasting.h"
#include "../externmath/externmath.h"
#include "../gameplay/masterbuttons.h"
#include "../shared/memory_setup.h"
#include "../shared/sharedstructs.h"
#include "../shared/sharedpuzzle.h"
#endif

void DetectPlayerLookInput(PlayerCam* pcam);

Vector3 GetCameraForwardVector(PlayerCam* camera);

void InputCamYaw(PlayerCam* pcam, float angle);

void InputCamPitch(PlayerCam* pcam, float angle, bool lockView, bool rotateUp);

Vector3 GetCameraUpVector(PlayerCam* pcam);

Vector3 GetCameraRightVector(PlayerCam* pcam);

void CalculatePlayerVelocity(FPSPlayer* player, double deltaTime);

void CollideAndSlide(CollisionPacket* colPacket, FPSPlayer* player, double deltaTime, modelInfo** models, int numberOfModels);

Vector3 CollideWithWorld(CollisionPacket* colPacket, Vector3 pos, Vector3 vel, modelInfo** models, int numberOfModels);

void PollPlayerInput(PlayerCam* pcam, double deltaTime, FPSPlayer* player, CollisionPacket* colPacket, modelInfo** models, int numOfModels, bool gameA);

void PollPlayerSecondaryInputs(FPSPlayer* player, Raycast* interactRay, QueryBox** areaBoxes, enum Gamemode* mode, Interactable* interactedItem, int numOfAreaQueryBoxes, OpenSharedValues* openSharedValues, enum Gametype gameType);

void PollPlayerPuzzleInputs(Interactable* interactedItem, enum Gamemode* mode, OpenSharedValues* openSharedValues, bool isPlayerSharingPuzzle, enum Gametype gametype);

void PollDebugInputs(bool* hideHideableObjects);

void LerpPlayer(FPSPlayer* player, ButtonMaster* puzzle);
