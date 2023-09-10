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
#include <fileapi.h>

#include "FsUtil.h"
#include "FsFile.h"


int CallCommand(std::string command, std::string arguments);
std::string Popen(const std::string command, const std::string arguments);
