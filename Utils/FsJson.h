#pragma once

#define WINDOWS_IGNORE_PACKING_MISMATCH


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
#include <iostream>

using string = std::string;
string FromAEJson(string src);
string ToAEJson(string src);

// *********************************************************************************************
