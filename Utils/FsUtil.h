#pragma once

#define WINDOWS_IGNORE_PACKING_MISMATCH


#include "FsFile.h"
#include "FsProcess.h"

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

// *********************************************************************************************
/*
	クリップボード
*/
// *********************************************************************************************
BOOL SetTextClipboard(LPCTSTR lpString);
LPCTSTR GetTextClipboard();

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
void  BeepPlay(int v);
BOOL PlayResource(HANDLE hInst, int id);
BOOL PlayWave(LPSTR lpName);
void PlayAESound(int v);
void SoundPlay(char* s);

// *********************************************************************************************
bool IsModifierkey(char* key);
bool IsModifierkey(int v);
bool IsShiftKey();
bool IsControlKey();
bool IsAltKey();

// *********************************************************************************************
std::string get_env(const char* environment_name);
bool set_env(const char* environment_name, std::string v);
