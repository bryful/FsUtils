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


BOOL SetTextClipboard(LPCTSTR lpString);
LPCTSTR GetTextClipboard();

LPTSTR SjisToUTF8(LPTSTR srcSjis);
LPTSTR UTF8ToSjis(LPTSTR srcUTF8);

char* GetName(char* str);
char* GetNameWithoutExt(char* str);
char* GetExt(char* str);
char* GetParent(char* str);

