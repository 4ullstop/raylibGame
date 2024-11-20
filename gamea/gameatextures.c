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
    "D:/CFiles/FirstGame/models/obj/door.png", //16
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_highlighted_02.png", //17
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_highlighted_03.png", //18
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_highlighted_04.png", //19
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_highlighted_05.png", //20
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_highlighted_06.png", //21
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_highlighted_07.png", //22
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_highlighted_08.png", //23
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_idle_02.png", //24
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_idle_03.png", //25
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_idle_04.png", //26
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_idle_05.png", //27
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_idle_06.png", //28
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_idle_07.png", //29
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_idle_08.png", //30
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_selected_02.png", //31
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_selected_03.png", //32
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_selected_04.png", //33
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_selected_05.png", //34
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_selected_06.png", //35
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_selected_07.png", //36
    "D:/CFiles/FirstGame/models/obj/Button_Mats/button_selected_08.png", //37
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_idle_01.png", //38
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_highlighted_01.png", //39
    "D:/CFiles/FirstGame/models/obj/Button_Mats/buttonTextureAtlas_submitted_01.png" //40
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