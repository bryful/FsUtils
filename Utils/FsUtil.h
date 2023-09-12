#pragma once

#define WINDOWS_IGNORE_PACKING_MISMATCH


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
#include <mmsystem.h>
#include <vector>

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

#pragma comment(lib, "winmm.lib")

#include "FsFile.h"
#include "FsProcess.h"
#include "AEProcess.h"


// *********************************************************************************************
char* getNewBuffer(char * s);
char* getNewBuffer(std::string s);
std::string getNewString(char* s);

// *********************************************************************************************
std::string  ReplaceAll(std::string& stringreplace, const std::string& origin, const std::string& dest);
std::vector<std::string> Split(const std::string& s, const std::string& delim);
std::string Join(const std::vector<std::string>& v, std::string delim);
std::string Trim(const std::string& string);
std::string TrimTailSepa(const std::string& string);
std::string TrimHeadSepa(const std::string& string);
std::vector<std::string> CammaSplit(const std::string& s);
std::string ToLowwer(std::string s);
std::string ToUpper(std::string s);

// *********************************************************************************************
/*
	クリップボード
*/
// *********************************************************************************************
BOOL SetTextClipboard(LPCTSTR lpString, bool IsU);
BOOL SetTextClipboard(std::string str, bool IsU);
LPCTSTR GetTextClipboard(bool IsU);
std::string GetTextClipboardStr(bool IsU);


// *********************************************************************************************
/*
	文字コードの変換
*/
// *********************************************************************************************
BOOL IsUTF8(char* bytes);
BOOL IsUTF8(std::string s);

char* ShiftJistoUtf8(char* src);
char* Utf8toShiftJis(char* src);
std::string multi_to_utf8_winapi(std::string const& src);
std::string utf8_to_multi_winapi(std::string const& src);

// *********************************************************************************************
POINT GetMousePos();
std::string GetMousePosString();
void SetMousePos(int x, int y);
// *********************************************************************************************
BOOL PlayBeep(std::string dir, std::string num);
BOOL PlayWave(std::string dir, std::string name);
void PlayAESound(std::string dir, int v);

// *********************************************************************************************
bool IsModifierKey(char* key);
bool IsModifierKey(int v);
bool IsShiftKey();
bool IsControlKey();
bool IsAltKey();
bool IsControlCKey();

// *********************************************************************************************
std::string get_env(const char* environment_name);
bool set_env(const char* environment_name, std::string v);
std::string LoginUserName();
std::string ComputerName();

// *********************************************************************************************
std::vector<MONITORINFOEX> ScreenInfo();

std::vector<RECT> ScreenSizes();
std::vector<RECT> ScreenWorkSizes();

std::string RECTtoStr(RECT r);
RECT GetAEWinodwRect(HWND hwnd);
BOOL SetAEWindowRect(HWND hwnd, int x, int y, int x1, int y1);
RECT InScreen(HWND hwnd);
