#include "gamebtextures.h"

void RetrieveGameBTextureFiles(char** textureFiles)
{
    char* gameBTextures[] = {
    "D:/CFiles/FirstGame/models/obj/walls.png", //0
    "D:/CFiles/FirstGame/models/obj/walls_03.png", //1
    "D:/CFiles/FirstGame/models/obj/door.png", //2
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_idle_02.png", //3
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_highlighted_02.png", //4
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_submitted_02.png", //5
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_states_01.png", //6
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_error_01.png", //7
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_completed_02.png", //8
    "D:/CFiles/FirstGame/models/obj/dock.png"
    };

    LoopThroughFilesB(textureFiles, gameBTextures);
}

void LoopThroughFilesB(char** outputFiles, char** filesToRead)
{
    for (int i = 0; i < NUMBER_OF_TEXTURES_B; i++)
    {
	outputFiles[i] = filesToRead[i];
    }
}
