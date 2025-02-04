#include "buttonatlas.h"
#include <stdio.h>
#include <stdlib.h>

void UpdateShaderForButtonAtlas(Button* button, enum TextureCoordinateLocations textureLocation)
{
    button->buttonTextureLocation = textureLocation;

    if (textureLocation == TCL_Window)
    {
	printf("\n");
	printf("\n");
	printf("texture location: %i\n", textureLocation);
	printf("\n");
	printf("\n");
    }
        
    if (button->buttonState == EBS_off) return;
    const float uvWidth = 1.0f / 8.0f;
    const float uvHeight = 1.0f / 8.0f;

    Shader* shader = malloc(sizeof(Shader)); 
    *shader = LoadShader(0, "D:/CFiles/FirstGame/shaders/buttonatlas.fs");

    float offsetY = (float)((textureLocation - 1) / 8) * uvHeight;
    float offsetX = (float)((textureLocation - 1) % 8) * uvWidth;

    SetShaderValue(*shader, GetShaderLocation(*shader, "uvOffset"), (float[2]){offsetX, offsetY}, SHADER_UNIFORM_VEC2);
    SetShaderValue(*shader, GetShaderLocation(*shader, "uvScale"), (float[2]){1.0f, 1.0f}, SHADER_UNIFORM_VEC2);
    button->model->model.materials[0].shader = *shader;
    button->loadedShader = shader;
}
