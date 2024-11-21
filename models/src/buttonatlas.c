#include "buttonatlas.h"
#include <stdio.h>
#include <stdlib.h>

void AssignButtonTextCoord(Model* model, enum TextureCoordinateLocations textureLocation)
{
    const float uvWidth = 1.0f / 8.0f;
    const float uvHeight = 1.0f / 8.0f;

    Mesh tempMesh = model->meshes[0];

    
    

    float scaleX = uvWidth;
    float scaleY = uvHeight;

    float offsetY = 0, offsetX = 0;
    offsetY = (float)((textureLocation - 1) / 8) * uvHeight;
    offsetX = (float)((textureLocation - 1) % 8) * uvWidth;
    
    bool uvsModified = false;
    for (int i = 0; i < tempMesh.vertexCount; i++)
    {
        float u = model->meshes[0].texcoords[i * 2 + 0];
        float v = model->meshes[0].texcoords2[i * 2 + 1];


        float newU = offsetX + u * uvWidth;
        float newV = offsetY + v * uvHeight;

        if (newU != u || newV != v)
        {
            tempMesh.texcoords2[i * 2 + 0] = newU;
            tempMesh.texcoords2[i * 2 + 1] = newV;
            uvsModified = true;
        }

        printf("button uvs, u: %f, v: %f\n", newU, newV);
    }
    
    if (uvsModified == true)
    {
        
        
        UploadMesh(&tempMesh, true);
        model->meshes[0] = tempMesh;
    }
    
}

void AssignAndUpdateTextRecForAtlas(Button* button, enum TextureCoordinateLocations textureLocation)
{
    const float uvWidth = 1.0f / 8.0f;
    const float uvHeight = 1.0f / 8.0f;
    
    float offsetY = (float)((textureLocation - 1) / 8) * uvHeight;
    float offsetX = (float)((textureLocation - 1) % 8) * uvWidth;


    
    Rectangle frameRec = {0.0f, 0.0f, offsetX, offsetY};
    UpdateTextureRec(button->buttonTextures->highlighted, frameRec, &WHITE);
    UpdateTextureRec(button->buttonTextures->idle, frameRec, &WHITE);
    UpdateTextureRec(button->buttonTextures->selected, frameRec, &WHITE);
}

void UpdateShaderForButtonAtlas(Button* button, enum TextureCoordinateLocations textureLocation)
{
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