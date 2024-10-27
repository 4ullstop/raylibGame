#include "C:\raylib\raylib\src\raylib.h"
#include "models/src/model.h"
#include "libs/drawingstructs.h"

void CallAllPolls(float dTime, modelInfo** models, Interactable* interactable);

void Draw(modelInfo** models, ColBox* box, Raycast* ray, QueryBox** queryBoxes);

void InitializeModel(Model* cube, Texture2D* text);

