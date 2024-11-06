#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "../libs/drawingstructs.h"
#include "../gameplay/gameplaystructs.h"
#include "../ui/src/uistructs.h"
#endif 

#define NUMBER_OF_MODELS 12
#define NUMBER_OF_INTERACTABLES 3
#define NUMBER_OF_AREA_QUERY_BOXES 1
#define NUMBER_OF_PUZZLES 2
#define NUMBER_OF_OVERLAP_BOXES_A 1

#ifndef E_GAMEMODE
#define E_GAMEMODE
enum Gamemode
{
    EGM_Normal,
    EGM_Puzzle,
    EGM_Inactive
};
#endif

#ifndef E_GAMETYPE
#define E_GAMETYPE
enum Gametype
{
    EGT_A,
    EGT_B
};
#endif

#ifndef E_DIRECTION
#define E_DIRECTION
enum Direction
{
    ED_Up,
    ED_Down,
    ED_Left,
    ED_Right,
    ED_Enter
};
#endif

#ifndef VECTOR_2_INT
#define VECTOR_2_INT
typedef struct 
{
    int x;
    int y;
} Vector2Int;
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

    Vector3 playerLookForward;

    Vector3 lastPos;
    Vector3 currPos;

    float lastTime;
    float currTime;

    Vector3 finalPos;

    PlayerCam* attachedCam; 

    bool isPlayerGrounded;

    bool firstInput;

    UIElements** playerHUD;

    enum Gamemode* gamemode;
} FPSPlayer;
#endif

#ifndef MODEL_INFO
#define MODEL_INFO
typedef struct modelInfo
{
    Model model;
    Texture2D texture;

    Vector3 modelLocation;

    int lastModelIndex;

    //always set this on creation otherwise you could get a value greater than 0 which would mean true which could cause unwanted behavior
    bool collisionDisabled;
    
} modelInfo;
#endif

#ifndef BUTTON
#define BUTTON
typedef struct Button
{
    Vector3 location;
    bool solutionButton;
    bool highlighted;
    bool submitted;

    Vector2Int buttonVectorLocation;

    modelInfo* model;

    //n(direction) (aka neighbor(direction))
    struct Button* nLeft;
    struct Button* nRight;
    struct Button* nAbove;
    struct Button* nBelow;
} Button;
#endif

#ifndef MASTER_OF_BUTTONS
#define MASTER_OF_BUTTONS
typedef struct ButtonMaster
{
    Button** childButtons;
    
    unsigned int rows;
    unsigned int columns;

    Vector2Int highlightLocation;
    unsigned int totalButtons;
    bool solved;

    Vector3 location;

    float buttonSpread;
    Vector2Int* solutionLocations;
    int numberOfSolutions;
    //Interactable* associatedBox;

    bool hasBoxAssigned;

    int id;
    FPSPlayer* player;
    void (*OnPuzzleSolved)(struct ButtonMaster* master);
} ButtonMaster;
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
    void (*interact)(FPSPlayer* player, struct ColBox* box);


    //debug
    bool showDebug;
    Vector3* randDirectionDebug;
    
    Vector3* cubeVertsDebug;
    int cubeVertsSize;
    int randDirectionSize;

    int id;

} ColBox;
#endif

#ifndef INTERACTABLE_TYPE
#define INTERACTABLE_TYPE
enum InteractableType
{
    ITT_Unassigned,
    ITT_Puzzle
};
#endif


#ifndef INTERACTABLE
#define INTERACTABLE
typedef struct 
{
    Vector3 Location;
    Model model;
    ColBox* colBox;

    bool hasBeenUsed;

    enum InteractableType type;

    float width;
    float height;
    float length;

    ButtonMaster* associatedPuzzle;

    int id;

    bool showsArrowKeyHint;
} Interactable;
#endif

#ifndef INTERACT_INFO
#define INTERACT_INFO
typedef struct
{
    enum Gamemode gamemode;
    Interactable* interactable;
} InteractInfo;
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

#ifndef BOX_OVERLAP
#define BOX_OVERLAP
typedef struct OverlapBox
{
    ColBox* collisionBox;
    float width;
    float height;
    float length;
    Vector3 location;
    
    int id;

    void (*OnOverlap)(FPSPlayer* player, struct OverlapBox* box);

    struct OverlapBox* next;

    bool shouldDetect;
} OverlapBox;
#endif



