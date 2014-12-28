#pragma once

#ifndef _INC_WINDIR
#define _INC_WINDIR

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include "Structs.h"
#pragma comment(lib, "User32.lib")

extern componentSave components;
void DisplayErrorBox(LPTSTR lpszFunction);
int listDir(componentType_e _componentType);

#endif