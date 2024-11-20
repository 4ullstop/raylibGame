#include "buttonatlas.h"

void AssignButtonTextCoord(Model* model, enum TextureCoordinateLocations textureLocation)
{
    const float uvWidth = 1.0f / 8;
    const float uvHeight = 1.0f / 8;

    float scaleX = 1.0f / uvWidth;
    float scaleY = 1.0f / uvHeight;

    int offsetY = 0, offsetX = 0;
    if (textureLocation < 8)
    {
        offsetY = 1;
        offsetX = textureLocation;
    }
    else
    {
        offsetY = ceil((float)textureLocation / 8.0f);
        offsetX =  textureLocation - (8 * offsetY - 1);
    }

    for (int i = 0; i < model->meshes[0].vertexCount; i++)
    {
        float u = model->meshes[0].texcoords[i * 2 + 0];
        float v = model->meshes[0].texcoords[i * 2 + 1];

        u = offsetX + u * scaleX;
        v = offsetY + v * scaleY;

        model->meshes[0].texcoords[i * 2 + 0] = u;
        model->meshes[0].texcoords[i * 2 + 1] = v; 
    }
    UploadMesh(&model->meshes[0], true);
}