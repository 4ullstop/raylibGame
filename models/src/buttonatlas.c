#include "buttonatlas.h"
#include <stdio.h>

void AssignButtonTextCoord(Model* model, enum TextureCoordinateLocations textureLocation)
{
    const float uvWidth = 1.0f / 8.0f;
    const float uvHeight = 1.0f / 8.0f;

    

    float scaleX = uvWidth;
    float scaleY = uvHeight;

    float offsetY = 0, offsetX = 0;
    offsetY = (float)((textureLocation - 1) / 8) * uvHeight;
    offsetX = (float)((textureLocation - 1) % 8) * uvWidth;
    
    bool uvsModified = false;
    for (int i = 0; i < model->meshes[0].vertexCount; i++)
    {
        float u = model->meshes[0].texcoords[i * 2 + 0];
        float v = model->meshes[0].texcoords[i * 2 + 1];


        float newU = offsetX + u * uvWidth;
        float newV = offsetY + v * uvHeight;

        if (newU != u || newV != v)
        {
            model->meshes[0].texcoords[i * 2 + 0] = newU;
            model->meshes[0].texcoords[i * 2 + 1] = newV;
            uvsModified = true;
        }

        printf("button uvs, u: %f, v: %f\n", newU, newV);
    }
    
    if (uvsModified == true)
    {
        UnloadMesh(model->meshes[0]);
        UploadMesh(&model->meshes[0], true);
    }
    
    
}