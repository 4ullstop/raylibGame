#include "gameaindicators.h"
#include "../gameplay/gameplay_elements/indicator.h"
#include <stdio.h>

void ConstructGameAIndicators(modelInfo** dynamicModels, Texture2D** gameATextures, int* lastModelIndex, Indicator** allIndicators, ExitCode* exitCode)
{
    printf("About to construct indicators\n");
    int lastIndicatorIndex = 0;
    ConstructSingleIndicator(dynamicModels,
			     gameATextures,
			     allIndicators,
			     "D:/CFiles/FirstGame/models/obj/indicators/indicator_01.obj",
			     (Vector3){10.0f, 0.3f, 15.0f},
			     13,
			     101,
			     &lastIndicatorIndex,
			     lastModelIndex,
			     exitCode);
			     
}
   
