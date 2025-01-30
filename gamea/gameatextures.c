#include "gameatextures.h"

void RetrieveGameATextureFiles(char** textureFiles)
{
    char* gameATextures[] = {
    "D:/CFiles/FirstGame/models/obj/walls.png", //0
    "D:/CFiles/FirstGame/models/obj/walls_03.png", //1
    "D:/CFiles/FirstGame/models/obj/door.png", //2
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_idle_02.png", //3
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_highlighted_02.png", //4
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_submitted_02.png", //5
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_states_01.png", //6
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_error_01.png", //7
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_completed_02.png", //8
    "D:/CFiles/FirstGame/models/obj/dock.png", //9
    "D:/CFiles/FirstGame/models/obj/water.png", //10
    "D:/CFiles/FirstGame/models/obj/ground.png", //11
    "D:/CFiles/FirstGame/models/obj/lighthouseuv.png", //12
    "D:/CFiles/FirstGame/models/obj/indicators/indicatoruv.png" //13
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
