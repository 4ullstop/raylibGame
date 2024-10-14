#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#endif

#ifndef CAMERA_STRUCT
typedef struct PlayerCam3D
{
    Vector3 position;
    Vector3 target;
    Vector3 up;
    float fov;
} PlayerCam;
#endif

#ifndef PLAYER_STRUCT
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
} FPSPlayer;
#endif