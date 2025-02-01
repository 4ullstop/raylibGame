#include "gameaindicators.h"
#include "../gameplay/gameplay_elements/indicator.h"
#include <stdio.h>

void ConstructGameAIndicators(modelInfo** dynamicModels, Texture2D** gameATextures, int* lastModelIndex, Indicator** allIndicators, ExitCode* exitCode)
{
    float zHeight = -0.1;
    printf("About to construct indicators\n");
    int lastIndicatorIndex = 0;
    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_01.obj",
			     (Vector3){10.0f, zHeight, 15.0f},
			     13,
			     101,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_02.obj",
			     (Vector3){10.0f, zHeight, 15.0f},
			     13,
			     102,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_03.obj",
			     (Vector3){10.0f, zHeight, 15.0f},
			     13,
			     103,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_04.obj",
			     (Vector3){10.0f, zHeight, 15.0f},
			     13,
			     104,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_05.obj",
			     (Vector3){10.0f, zHeight, 15.0f},
			     13,
			     105,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_06.obj",
			     (Vector3){10.0f, zHeight, 15.0f},
			     13,
			     106,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_07.obj",
			     (Vector3){10.0f, zHeight, 15.0f},
			     13,
			     107,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_09.obj",
			     (Vector3){10.0f, zHeight, 15.0f},
			     13,
			     108,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);
}
   
