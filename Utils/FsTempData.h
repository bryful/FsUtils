#pragma once

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
#include <Shlwapi.h>
#include <iostream>
#include <fstream>

typedef enum fuStatus
{
	Error = 0,
	Input,
	OK,
	Cancel
}fuStatus;
class FsTempData
{
private:
	std::string m_filePath = "";
	BOOL m_OK = false;
	const std::string fuOK = std::string("#fuOK:");
	const std::string fuCancel = std::string("#fuCancel:");
	const std::string fuInput = std::string("#fuInput:");
public:
	std::string Data = "";

	std::string GetTempFolder()
	{
		DWORD sz = GetTempPath(0, nullptr);
		LPSTR lpBuffer = (LPSTR)malloc(sz + 1);
		if (GetTempPath(sz, lpBuffer) == 0)
		{
			free(lpBuffer);
			return std::string("");
		}
		return std::string(lpBuffer);

	}
	BOOL Exists()
	{
		return PathFileExists((LPCSTR)m_filePath.c_str());
	}
	BOOL Delete()
	{
		BOOL ret = false;
		if (Exists() == true)
		{
			ret = DeleteFile((LPCSTR)m_filePath.c_str());
		}
		return ret;
	}
	BOOL Load()
	{
		BOOL ret = false;
		Data = "";
		m_OK = false;
		if (Exists() == true)
		{
			std::ifstream ifs(m_filePath);
			if (ifs.fail() == false) {
				std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
				size_t idx = str.find_first_of(fuOK);
				if ( idx == 0) {
					Data = str.substr(fuOK.size());
					ret = true;
				}
			}
		}
		return ret;
	}
	std::string DataT(BOOL ok)
	{
		std::string dd = "";
		if (ok)
		{
			dd = fuOK + Data;
		}
		else
		{
			dd = fuCancel + Data;
		}
		return dd;
	}
	BOOL SaveInput()
	{
		if (Exists() == true) Delete();
		std::ofstream writing_file;
		writing_file.open(m_filePath, std::ios::out);
		std::string dd = fuInput + Data;
		writing_file << dd << std::endl;
		writing_file.close();
		return Exists();
	}
	BOOL Save(BOOL ok)
	{
		if (Exists() == true) Delete();
		std::ofstream writing_file;
		writing_file.open(m_filePath, std::ios::out);
		writing_file << DataT(ok) << std::endl;
		writing_file.close();
		return Exists();
	}
	FsTempData()
	{
		m_filePath = GetTempFolder() + "fuTemp.txt";
	}
};

