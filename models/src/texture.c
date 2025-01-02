#include "texture.h"
#include <stdio.h>
#include <stdlib.h>

void LoadAllTextures(Texture2D** allTextures, enum Gametype gametype, ExitCode* exitCode)
{
    if (gametype == EGT_A)
    {
        LoadGameAModels(allTextures, exitCode);
    }
    else
    {
	LoadGameBModels(allTextures, exitCode);
    }

    
}



void LoadGameAModels(Texture2D** allTextures, ExitCode* exitCode)
{
    exitCode->numOfLoadedItems = 0;
    char* gameATextures[NUMBER_OF_TEXTURES_A];
    RetrieveGameATextureFiles(gameATextures);
    for (int i  = 0; i < NUMBER_OF_TEXTURES_A; i++)
    {
	printf("gameBTexturesLoc: %s\n", gameATextures[i]);
    }
    for (int i = 0; i < NUMBER_OF_TEXTURES_A; i++)
    {
	Image image = LoadImage(gameATextures[i]);
	Texture2D* texture = malloc(sizeof(Texture2D));
	if (texture == NULL)
	{
	    EditReturnCodeInfo(10, "Failed To allocate memory for textures", exitCode);
	    return;
	}
	*texture = LoadTextureFromImage(image);
	allTextures[i] = texture;
	exitCode->numOfLoadedItems = exitCode->numOfLoadedItems + 1;
    }
}


void LoadGameBModels(Texture2D** allTextures, ExitCode* exitCode)
{
    exitCode->numOfLoadedItems = 0;
    char* gameBTextures[NUMBER_OF_TEXTURES_B];
    RetrieveGameBTextureFiles(gameBTextures);
    for (int i  = 0; i < NUMBER_OF_TEXTURES_B; i++)
    {
	printf("gameBTexturesLoc: %s\n", gameBTextures[i]);
    }
    for (int i = 0; i < NUMBER_OF_TEXTURES_B; i++)
    {
	Image image = LoadImage(gameBTextures[i]);
	Texture2D* texture = malloc(sizeof(Texture2D));
	if (texture == NULL)
	{
	    EditReturnCodeInfo(10, "Failed To allocate memory for textures", exitCode);
	    return;
	}
	*texture = LoadTextureFromImage(image);
	allTextures[i] = texture;
	exitCode->numOfLoadedItems = exitCode->numOfLoadedItems + 1;
    }
}
