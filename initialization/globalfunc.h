#pragma once
#ifndef GLOBAL_FUNC_HEADER
#define GLOBAL_FUNC_HEADER
#include "enginestructs.h"
#endif

void ReportError(ExitCode* exitCode);

void CheckForErrors(ExitCode* exitCode);

void EditReturnCodeInfo(int returnCode, char* extraInfo, ExitCode* exitCode);

void HandleEarlyExit(int returnCode);
