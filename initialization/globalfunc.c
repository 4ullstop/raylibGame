#include "globalfunc.h"
#include "enginestructs.h"
#include <stdio.h>

void ReportError(ExitCode* exitCode)
{
    printf("GAME %s, exited with code: %i\n", exitCode->gameVersion, exitCode->returnCode);
    printf("%s\n", exitCode->extraReturnInfo);
}

