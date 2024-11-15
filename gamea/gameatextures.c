#include "gameatextures.h"

void RetrieveGameATextureFiles(char** textureFiles)
{
    char* gameATextures[] = {
    "D:/CFiles/FirstGame/models/obj/walls.png", //0
    "D:/CFiles/FirstGame/models/obj/walls_03.png", //1
    "D:/CFiles/FirstGame/models/obj/buttonHighlighted.png", //2
    "D:/CFiles/FirstGame/models/obj/buttonIdle.png", //3
    "D:/CFiles/FirstGame/models/obj/buttonSelected.png", //4
    "D:/CFiles/FirstGame/models/obj/button_off.png", //5
    "D:/CFiles/FirstGame/models/obj/button_highlighted_lines_up.png", //6
    "D:/CFiles/FirstGame/models/obj/button_idle_lines_up.png", //7
    "D:/CFiles/FirstGame/models/obj/button_selected_lines_up.png", //8
    "D:/CFiles/FirstGame/models/obj/button_off.png", //9
    "D:/CFiles/FirstGame/models/obj/button_highlighted_lines_lr.png", //10
    "D:/CFiles/FirstGame/models/obj/button_idle_lines_lr.png", //11
    "D:/CFiles/FirstGame/models/obj/button_selected_lines_lr.png", //12
    "D:/CFiles/FirstGame/models/obj/button_highlighted_lines_ddl.png", //13
    "D:/CFiles/FirstGame/models/obj/button_idle_lines_ddl.png", //14
    "D:/CFiles/FirstGame/models/obj/button_selected_lines_ddl.png", //15
    "D:/CFiles/FirstGame/models/obj/door.png" //16
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