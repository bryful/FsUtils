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
#include <array>  // array
#include <cstdio>    // _popen
#include <iostream>  // cout
#include <memory>    // shared_ptr
#include <fstream>

#include "FsUtil.h"
#include "FsFile.h"

#ifndef AEFX_CLR_STRUCT
#define AEFX_CLR_STRUCT(STRUCT) memset(&(STRUCT), 0, sizeof(STRUCT));
#endif

int CallCommand(char* cmd);
int CallCommandWait(char* cmd);
int CallCommandGetResult(const char* cmd, char* buf, DWORD size);
//int CallCommandGetResult(std::string cmd, std::string& result);

