#include "gameatextures.h"

void RetrieveGameATextureFiles(char** textureFiles)
{
    char* gameATextures[] = {
    "D:/CFiles/FirstGame/models/obj/walls.png", //0
    "D:/CFiles/FirstGame/models/obj/walls_03.png", //1
    "D:/CFiles/FirstGame/models/obj/door.png", //2
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_idle_01.png", //3
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_highlighted_01.png", //4
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_submitted_01.png", //5
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_states_01.png" //6
    };

    LoopThroughFiles(textureFiles, gameATextures);
}

void LoopThroughFiles(char** outputFiles, char* filesToRead[])
{
    for (int i = 0; i < NUMBER_OF_TEXTURES_A; i++)
    {
        outputFiles[i] = filesToRead[i];
    }
}