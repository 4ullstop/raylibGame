#pragma once

#ifndef EXIT_CODE
#define EXIT_CODE
typedef struct ExitCode
{
    int returnCode;
    char* gameVersion;
    char* extraReturnInfo;
} ExitCode;
#endif
