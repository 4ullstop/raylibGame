#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "../libs/drawingstructs.h"
#endif 

#define NUMBER_OF_MODELS 3
#define NUMBER_OF_INTERACTABLES 1
#define NUMBER_OF_AREA_QUERY_BOXES 1

#ifndef CAMERA_STRUCT
#define CAMERA_STRUCT
typedef struct PlayerCam3D
{
    Vector3 position;
    Vector3 target;
    Vector3 up;
    float fov;
} PlayerCam;
#endif

#ifndef PLAYER_STRUCT
#define PLAYER_STRUCT
typedef struct 
{
    Vector3 location;
    Vector3 forwardVector;
    Vector3 velocity;

    Vector3 lastPos;
    Vector3 currPos;

    float lastTime;
    float currTime;

    Vector3 finalPos;

    PlayerCam* attachedCam; 

    bool isPlayerGrounded;
} FPSPlayer;
#endif

#ifndef MODEL_INFO
#define MODEL_INFO
typedef struct modelInfo
{
    Model model;
    Texture2D texture;

    Vector3 modelLocation;
    
} modelInfo;
#endif




#ifndef COLBOX
#define COLBOX
typedef struct ColBox
{
    //Basic setup info
    float* verts;
    unsigned short* indices;
    int vertsNum;
    Vector3 location;

    //The interact function
    void (*interact)(void);


    //debug
    bool showDebug;
    Vector3* randDirectionDebug;
    Vector3 debugPoint;
    Vector3* cubeVertsDebug;
    int cubeVertsSize;
    int randDirectionSize;

} ColBox;
#endif

#ifndef INTERACTABLE
#define INTERACTABLE
typedef struct 
{
    Vector3 Location;
    Model model;
    ColBox* colBox;

    

} Interactable;
#endif

#ifndef AREA_QUERY_BOX
#define AREA_QUERY_BOX
typedef struct 
{
    ColBox* areaBox;
    Interactable* associatedInteractables[NUMBER_OF_INTERACTABLES];

    Vector3 location;
    float height;
    float width;
    float length;

    int numberOfInteractables;

} QueryBox;
#endif

#ifndef RAYCAST
#define RAYCAST
typedef struct 
{
    Vector3 hitLocation;
    float rayLength;
    

    float nearestCollision;
    bool foundCollision;

    bool showDebugLines;

    Drawline* linesToDraw;
} Raycast;
#endif