#pragma once

#ifndef _INC_WINDIR
#define _INC_WINDIR

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include "Structs.h"
#include "globalData.h"

#pragma comment(lib, "User32.lib")

void DisplayErrorBox(LPTSTR lpszFunction);
std::vector<std::string> listDir(componentType_e _componentType);

#endif