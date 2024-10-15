#include "C:\raylib\raylib\src\raylib.h"
#include "models/src/model.h"

#define NUMBER_OF_MODELS 1

void CallAllPolls(float dTime, Model* inModel);

void Draw(Model* cubeModel, modelInfo** models, int modelSize);

void InitializeModel(Model* cube, Texture2D* text);
