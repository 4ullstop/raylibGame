#pragma once
#ifndef GLOBAL_FUNC_HEADER
#define GLOBAL_FUNC_HEADER
#include "enginestructs.h"
#include <stdbool.h>
#endif

void ReportError(ExitCode* exitCode);

bool CheckForErrors(ExitCode* exitCode, enum DestructionLocations* destructionLocations);

void EditReturnCodeInfo(int returnCode, char* extraInfo, ExitCode* exitCode);

void HandleEarlyExit(int returnCode, enum DestructionLocations* destructionLocations);
