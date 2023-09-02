#pragma once

#define WINDOWS_IGNORE_PACKING_MISMATCH

#pragma comment(lib, "Shlwapi.lib")

#include "FsUtil.h"
#include "FsProcess.h"

#include <vector>
#include <windows.h>
#include <winbase.h>
#include <winuser.h>
#include <Shlobj_core.h>
#include <direct.h>
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
std::string ae_sound_fail();
std::string ae_sound_okay();
std::string ae_sound_snap();

// *********************************************************************************************
/*
	ファイルパス文字の処理
*/
// *********************************************************************************************
bool ExistFile(char* path);
bool ExistFile(const char* path);
bool ExistFile(std::string path);

bool ExistDirectory(char* path);
bool ExistDirectory(const char* path);
bool ExistDirectory(std::string  path);


std::string GetTempFolder();
std::string GetTempDataFile();
std::string GetAppDataFolder();
std::string GetAppDataFile(std::string name, std::string productname);

// *********************************************************************************************
/*
	ファイルパス文字の処理
*/
// *********************************************************************************************
std::string GetDir(std::string str);
std::string GetName(std::string str);
std::string GetNameWithoutExt(std::string str);
std::string GetExt(std::string str);
BOOL SplitName(std::string str, std::string& dir, std::string& name, std::string& ext);

int IndexOfFrameNumber(std::string src);
std::string GetFrame(std::string src);
std::string GetNameWithoutFrame(std::string src);


std::string PathToWinFromJS(std::string str);
std::string PathToJSFromWin(std::string str);


LPTSTR  GetName(LPTSTR  str);
//char* GetNameWithoutExt(char* str);
//char* GetExt(char* str);
//char* GetParent(char* str);
//char* CombinePath(char* s0, char* s1);
std::string CombinePath(std::string str1, std::string str2);

std::string DllPath();

BOOL LoadPref(std::string fname, std::string dname, std::string productName, std::string& data);
BOOL SavePref(std::string fname, std::string dname, std::string productName, std::string data);


