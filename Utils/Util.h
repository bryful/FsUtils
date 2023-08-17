#pragma once

#define WINDOWS_IGNORE_PACKING_MISMATCH

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

// *********************************************************************************************
/*
	�N���b�v�{�[�h
*/
// *********************************************************************************************
BOOL SetTextClipboard(LPCTSTR lpString);
LPCTSTR GetTextClipboard();

// *********************************************************************************************
/*
	�����R�[�h�̕ϊ�
*/
// *********************************************************************************************
LPTSTR SjisToUTF8(LPTSTR srcSjis);
LPTSTR UTF8ToSjis(LPTSTR srcUTF8);
std::string multi_to_utf8_winapi(std::string const& src);
std::string utf8_to_multi_winapi(std::string const& src);

// *********************************************************************************************
/*
	�t�@�C���p�X�����̏���
*/
// *********************************************************************************************
LPTSTR  GetName(LPTSTR  str);
char* GetNameWithoutExt(char* str);
char* GetExt(char* str);
char* GetParent(char* str);

