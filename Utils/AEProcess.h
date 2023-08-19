#pragma once
#pragma warning(disable : 4996) 
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
#include <vector>
#include <iostream>
#include <regex>
#include <sstream>
#include <system_error>
#include <winuser.h>

#include "FsUtil.h"

#ifndef AEFX_CLR_STRUCT
#define AEFX_CLR_STRUCT(STRUCT) memset(&(STRUCT), 0, sizeof(STRUCT));
#endif


typedef struct PCell
{
	HWND	hWnd=0;
	DWORD	Pid=0;
	std::string ProcessName;
	std::string	Title;
	std::string	Path;
	BOOL	IsZoomed=false;
	BOOL	IsWindow = false;
	BOOL	IsIconic = false;
} PCell;

int encode_uri(char* const src, char** dest);
int decode_uri(char* const src, char** dest);

int listup(void);
std::vector<PCell> AEProcessList(BOOL IsUTF8);
std::string ProcessList(bool IsUTF8,bool isLn);

std::string listupAEProcess(BOOL IsUTF8);
void AEShowWindow(int idx);
void AEShowWindow(HWND hWnd, int idx);

