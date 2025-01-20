#pragma once

#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "../libs/drawingstructs.h"
#include "../gameplay/gameplaystructs.h"
#include "../ui/src/uistructs.h"
#include "../models/src/textcoordhelpers.h"
#include "enginestructs.h"
#include "globalfunc.h"
#endif 

/*
    assocaitedInteractables in areaQueryBoxes is a set number that could need changes
    if there are more than the amount of interactables in the world than there are in the intialized list
    The current size of this array is : 48
    The current size of AssociatedDoors in GameplayElements is: 48
*/
#define NUMBER_OF_MODELS_A 205//45
#define NUMBER_OF_MODELS_B 101 //24

#define NUMBER_OF_TEXTURES_A 11 //this will always be one more than what is in the file
#define NUMBER_OF_TEXTURES_B 9
#define NUMBER_OF_INTERACTABLES_A 15 //9
#define NUMBER_OF_INTERACTABLES_B 8

#define NUMBER_OF_AREA_QUERY_BOXES_A 1
#define NUMBER_OF_AREA_QUERY_BOXES_B 1

#define NUMBER_OF_PUZZLES_A 15 //9
#define NUMBER_OF_PUZZLES_B 8

#define NUMBER_OF_OVERLAP_BOXES_A 1
#define NUMBER_OF_OVERLAP_BOXES_B 1

#define NUMBER_OF_DOORS_A 2
#define NUMBER_OF_DOORS_B 0

#ifndef E_BUTTON_SIZES
#define E_BUTTON_SIZES
enum ButtonTextureSizes
{
    EBTS_01,
    EBTS_02,
    EBTS_03,
    EBTS_04,
    EBTS_05,
    EBTS_06,
    EBTS_07,
    EBTS_08
};
#endif

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
    ED_NULL,
    ED_Up,
    ED_Down,
    ED_Left,
    ED_Right,
    ED_Enter,
    ED_Reset,
    ED_Direction
};
#endif

#ifndef PUZZLE_TYPE
#define PUZZLE_TYPE
enum PuzzleType
{
    EPT_Free,
    EPT_OnOff
};
#endif

#ifndef PUZZLE_ONOFF_DIRECTION
#define PUZZLE_ONOFF_DIRECTION
enum PuzzleOnOffDirection
{
    POOD_BottomUp,
    POOD_TopDown,
    POOD_DUL, //diagonal up left
    POOD_DUR, //diagonal up right
    POOD_DDL, //diagonal down left
    POOD_DRL, //diagonal down right
    POOD_RightLeft,
    POOD_LeftRight
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

#ifndef PUZZLE_INPUT_TYPE
#define PUZZLE_INPUT_TYPE
enum PuzzleInputType
{
    EPIT_Enabled,
    EPIT_Disabled,
    EPIT_ResetOnly
};
#endif

#ifndef CAMERA_PERSPECTIVE
#define CAMERA_PERSPECTIVE
enum CameraPerspective
{
    CMP_Perspective,
    CMP_Orthographic
};
#endif

#ifndef CAMERA_STRUCT
#define CAMERA_STRUCT
typedef struct PlayerCam3D
{
    Vector3 position;
    Vector3 target;
    Vector3 up;
    float fov;

    enum CameraPerspective cameraPerspective;

    float nearCullDist;
} PlayerCam;
#endif

#ifndef PLAYER_STRUCT
#define PLAYER_STRUCT
typedef struct FPSPlayer
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

    bool showPlayerLocation;

    bool puzzleInputEnabled;

    Vector3 a;
    Vector3 b;

    Vector3 lookAtLoc;
    
    bool shouldTickPlayer;

    float lerpAmount;

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

    bool modelVisible;
    
} modelInfo;
#endif

#ifndef DOOR_TYPE
#define DOOR_TYPE
enum DoorType
{
    DT_NULL,
    DT_Vertical,
    DT_Hinged
};
#endif

#ifndef DOOR_ENTITY
#define DOOR_ENTITY
typedef struct Door
{
    modelInfo doorModel;
    Vector3 location;
    int id;

    enum DoorType doorType;

    Vector3 openPosition;
    Vector3 closedPosition;
    float speed;
    bool isLowering;

    Vector3 hingeOffset;
    float desiredAngle;
    float currAngle;
} Door;
#endif

#ifndef GAMPLAY_ELEMENTS
#define GAMPLAY_ELEMENTS
typedef struct GameplayElements
{
    Door* doors[48];
    int numOfDoors;

    Door* associatedDoor;

} GameplayElements;
#endif

#ifndef PUZZLE_TEXTURE_COMB
#define PUZZLE_TEXTURE_COMB
typedef struct
{
    Texture2D highlighted;
    Texture2D idle;
    Texture2D selected;
    Texture2D off;
    Texture2D error;
    Texture2D completed;
} PuzzleTexture;
#endif

#ifndef BUTTON_STATE
#define BUTTON_STATE
enum ButtonState
{
    EBS_idle,
    EBS_highlighted,
    EBS_selected,
    EBS_off
};
#endif

#ifndef PUZZLE_STATE
#define PUZZLE_STATE
enum PuzzleState
{
    EPS_active,
    EPS_inactive
};
#endif

#ifndef TOGGLE_RULE
#define TOGGLE_RULE
typedef struct ToggleRule
{
    enum PuzzleOnOffDirection puzzleOODirection;
    
    //assign these on construction
    int columns;
    int rows;

    bool hasBeenToggled;
} ToggleRule;
#endif

#ifndef MOVE_RULE
#define MOVE_RULE
typedef struct MoveRule
{
    enum Direction direction;
    int movementUnits;
} MoveRule;
#endif

#ifndef BUTTON_RULES
#define BUTTON_RULES
typedef struct ButtonRules
{
    ToggleRule* toggleRule;
    MoveRule* moveRule;
    
} ButtonRules;
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

    enum ButtonState buttonState;

    //n(direction) (aka neighbor(direction))
    struct Button* nLeft;
    struct Button* nRight;
    struct Button* nAbove;
    struct Button* nBelow;

    bool isAboveEdge;
    bool isBelowEdge;
    bool isLeftEdge;
    bool isRightEdge;


    PuzzleTexture* buttonTextures;
    enum PuzzleType puzzleType;
    //to use a simulated ButtonMaster, use the neighbor buttons if needed

    ButtonRules* buttonRules;
    void (*ButtonSelected)(struct Button* button);

    
    bool isBeingAssessed;

    int id;

    int buttonSolutionIndex;
    

    enum ButtonTextureSizes textureSizes;

    Shader* loadedShader;
    bool shouldStayPoweredOff;

    enum TextureCoordinateLocations buttonTextureLocation;

    bool wasFlippedIncorrectly;

    bool shouldStaySubmitted;
} Button;
#endif

#ifndef ERROR_BUTTONS
#define ERROR_BUTTONS
typedef struct ErrorButtons 
{
    Button* button;
    struct ErrorButtons* next;
} ErrorButtons;
#endif

#ifndef SOLVED_BUTTONS
#define SOLVED_BUTTONS
typedef struct SolvedButtons
{
    enum ButtonTextureSizes textureSizes;
    struct SolvedButtons* next;
} SolvedButtons;
#endif

#ifndef PLAIN_BUTTONS_SUBMITTED
#define PLAIN_BUTTONS_SUBMITTED
typedef struct PlainSubmittedButtons
{
    Button* button;
    struct PlainSubmittedButtons* next;
} PlainSubmittedButtons;
#endif

#ifndef REACH_WINDOW_LOCATION
#define REACH_WINDOW_LOCATION
enum ReachWindowLocation
{
    RWL_RightSide,
    RWL_LeftSide,
    RWL_TopSide,
    RWL_BottomSide
};
#endif

#ifndef SHARED_REACH
#define SHARED_REACH
typedef struct
{
    Button* currCursoredButton;
    
    enum ReachWindowLocation reachWindowLocation;
} SharedReach;
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

    GameplayElements* associatedGameplayElements;

    struct ButtonMaster* puzzleToPowerOn;

    Vector2Int highlightStartLoc;
    bool hasHighlightStartLoc;

    enum PuzzleState puzzleState;

    Button** solutionButtons;

    Button* cursoredButton;

    int* correctOrder;

    enum ButtonTextureSizes* textureSizes;

    bool shouldReadTick;
    bool puzzleUnSolved;
    bool shouldBlinkCursor;

    ErrorButtons* errorButtons;

    Vector3 puzzleNormalDirection;

    SolvedButtons* solvedButtons;

    int numOfSolved;
    int numOfSelected;

    enum PuzzleInputType puzzleInputType;

    PlainSubmittedButtons* plainSubmittedButtons;
    int numOfPlainSubmittedButtons;
    int plainSubmittedButtonsMax;

    SharedReach* sharedReach;

    bool sharedPuzzle;

    bool gameAPuzzle;

    int sharedPuzzleId;

    Vector3 puzzleLerpOffset;

    bool lerpRotPuzzle;

    float originalAngle;
    float targetAngle;
    float tempAngle;

    bool isCursorOnScreen;

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
    Interactable* associatedInteractables[48];

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

    ColBox* closestBox;

    int associatedIndex;
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


#ifndef COLLATERAL_POWER
#define COLLATERAL_POWER
typedef struct CollateralPower
{
    Button* poweredButton;
    bool hasBeenToggled;
    struct CollateralPower* next;
} CollateralPower;
#endif

#ifndef TICK_NODE
#define TICK_NODE
typedef struct TickNode
{
    int frameCounter;
    double frameSpeed;

    int iterations;
    bool a;
} TickNode;
#endif

#ifndef SPECIAL_TEXTURE_INFO
#define SPECIAL_TEXUTRE_INFO
typedef struct 
{
    Vector2Int loc;
    enum TextureCoordinateLocations texLoc;
    
} GameButtonTextures;
#endif
