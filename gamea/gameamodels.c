#include "gameamodels.h"
#include "../models/src/modelinit.h"
#include <stdlib.h>
#include <stdio.h>

void CreateModelsForGameA(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, ExitCode* exitCode)
{
    //room 1
    Vector3 lighthouseLoc = (Vector3){3.0f, -0.3f, -1.0f};

    //10.0f 15.0f
    // 3.0f, -1.0f
    //-7.0f, -16.0f
    
    exitCode->numOfLoadedItems = 0;

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/ground.obj",
		      false,
		      true,
		      (Vector3){0.0f, 0.0f, 0.0f},
		      11);
    
    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/dock_01.obj",
		      false,
		      true,
		      (Vector3){0.0f, 2.0f, 0.0f},
		      9);
    
    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/dock_02.obj",
		      false,
		      true,
		      (Vector3){-1.0f, 2.0f, 0.0f},
		      9);
    
    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/scaleref.obj",
		      false,
		      true,
		      (Vector3){0.0f, 0.0f, 5.0f},
		      9);

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/lighthouse.obj",
		      true,
		      true,
		      lighthouseLoc,
		      12);   

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/lighthouseStairs_02.obj",
		      false,
		      true,
		      (Vector3){lighthouseLoc.x, 0.0f, lighthouseLoc.y},
		      0);   

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/boat.obj",
		      false,
		      true,
		      (Vector3){0.0f, 2.8f, 0.0f},
		      9);   
    
    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/water.obj",
		      false,
		      true,
		      (Vector3){0.0f, 0.0f, 0.0f},
		      10);

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/fence.obj",
		      true,
		      true,
		      (Vector3){0.0f, 0.0f, 0.0f},
		      9);

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/fencecollision.obj",
		      false,
		      false,
		      (Vector3){0.0f, 0.0f, 0.0f},
		      0);

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/lighthousecol_01.obj",
		      false,
		      false,
		      lighthouseLoc,
		      12);

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/dock_collision.obj",
		      true,
		      false,
		      (Vector3){0.0f, 3.0f, 0.0f},
		      0);

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/dockExtCol.obj",
		      false,
		      false,
		      (Vector3){0.0f, -0.2f, 0.0f},
		      0);

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/shed.obj",
		      false,
		      true,
		      (Vector3){-20.0f, 0.0f, -10.0f},
		      12);
		      

}
