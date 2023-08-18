#pragma once

#define WINDOWS_IGNORE_PACKING_MISMATCH

#pragma comment(lib, "Shlwapi.lib")

#include "FsUtil.h"

#include <vector>
#include <windows.h>
#include <winbase.h>
#include <winuser.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <atlstr.h>
#include <psapi.h>
#include <tchar.h>
#include <system_error>
#include <Shlwapi.h>
#include <iostream>


// *********************************************************************************************
std::vector< std::string> InstalledAFX();
char* InstalledAFXAS();
bool IsInstalledESTK();

// *********************************************************************************************
/*
	ファイルパス文字の処理
*/
// *********************************************************************************************
bool ExistFile(const char* path);
bool ExistDirectory(const char* path);

// *********************************************************************************************
/*
	ファイルパス文字の処理
*/
// *********************************************************************************************
LPTSTR  GetName(LPTSTR  str);
char* GetNameWithoutExt(char* str);
char* GetExt(char* str);
char* GetParent(char* str);
char* CombinePath(char* s0, char* s1);
