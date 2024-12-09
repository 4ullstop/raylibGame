#include "texture.h"
#include <stdio.h>
#include <stdlib.h>

void LoadAllTextures(Texture2D** allTextures, enum Gametype gametype)
{
    if (gametype == EGT_A)
    {
        LoadGameAModels(allTextures);
    }
    else
    {
	LoadGameBModels(allTextures);
    }
}

void LoadGameAModels(Texture2D** allTextures)
{
    char* gameATextures[NUMBER_OF_TEXTURES_A];
    RetrieveGameATextureFiles(gameATextures);
    for (int i = 0; i < NUMBER_OF_TEXTURES_A; i++)
    {
        printf("gameATexturesLoc: %s\n", gameATextures[i]);
    }
    for (int i = 0; i < NUMBER_OF_TEXTURES_A; i++)
    {
        Image image = LoadImage(gameATextures[i]);
        Texture2D* texture = malloc(sizeof(Texture2D));
        *texture = LoadTextureFromImage(image);
        allTextures[i] = texture;
    }
}

void LoadGameBModels(Texture2D** allTextures)
{
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
	*texture = LoadTextureFromImage(image);
	allTextures[i] = texture;
    }
}
