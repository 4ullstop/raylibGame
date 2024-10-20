#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#endif

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

#define NUMBER_OF_MODELS 3


#ifndef COLBOX
#define COLBOX
typedef struct 
{
    float* verts;
    unsigned short* indices;
    int vertsNum;

    Vector3 location;
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