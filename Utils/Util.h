#pragma once

#define WINDOWS_IGNORE_PACKING_MISMATCH

#include <windows.h>
#include <winbase.h>
#include <winuser.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <atlstr.h>

BOOL SetTextClipboard(LPCTSTR lpString);
LPCTSTR GetTextClipboard();

LPTSTR Sjis2UTF8(LPTSTR srcSjis);
LPTSTR UTF82Sjis(LPTSTR srcUTF8);


