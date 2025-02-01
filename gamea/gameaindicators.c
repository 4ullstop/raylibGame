#include "gameaindicators.h"
#include "../gameplay/gameplay_elements/indicator.h"
#include <stdio.h>

void ConstructGameAIndicators(modelInfo** dynamicModels, Texture2D** gameATextures, int* lastModelIndex, Indicator** allIndicators, ExitCode* exitCode)
{
    float zHeight = -0.1;
    Vector3 lighthouseIndicators = (Vector3){3.0f, -0.1f, -1.0f};
    printf("About to construct indicators\n");
    int lastIndicatorIndex = 0;
    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_01.obj",
			     lighthouseIndicators,
			     13,
			     101,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_02.obj",
			     lighthouseIndicators,
			     13,
			     102,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_03.obj",
			     lighthouseIndicators,
			     13,
			     103,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_04.obj",
			     lighthouseIndicators,
			     13,
			     104,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_05.obj",
			     lighthouseIndicators,
			     13,
			     105,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_06.obj",
			     lighthouseIndicators,
			     13,
			     106,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_07.obj",
			     lighthouseIndicators,
			     13,
			     107,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_09.obj",
			     lighthouseIndicators,
			     13,
			     108,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_10.obj",
			     (Vector3){0.0f, -1.2f, 0.0f},
			     13,
			     109,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);

    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_11.obj",
			     (Vector3){0.0f, -1.2f, 0.0f},
			     13,
			     110,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);
}
   
