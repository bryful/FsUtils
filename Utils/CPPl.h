#pragma once

#pragma comment(lib, "Shlwapi.lib")

#include <windows.h>
#include <winbase.h>
#include <winuser.h>
#include <Shlobj_core.h>
#include <direct.h>
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
#include <vector>

class CPPl
{
private:
	char* buf = nullptr;
	long long int bufSize = 0;
public:
	// **********************************************************************
	CPPl()
	{

	}
	CPPl(std::string p)
	{
		Load(p);
	}
	~CPPl()
	{
		BufFree();
	}
	// **********************************************************************
	void BufFree()
	{
		if (buf != nullptr)
		{
			free(buf);
			buf = nullptr;
			bufSize = 0;
		}
	}
	// **********************************************************************
	BOOL Load(std::string p)
	{
		BOOL ret = false;

		if (PathFileExists((LPCSTR)(p.c_str())) == false) return ret;

		//ファイル名からバイナリファイルで読み込む
		std::ifstream ifs(p, std::ios::binary);

		//読込サイズを調べる。
		ifs.seekg(0, std::ios::end);
		long long int size = ifs.tellg();
		ifs.seekg(0);

		BufFree();
		if (size > 0) 
		{
			buf = (char*)malloc(size);
			ifs.read(buf, size);
			bufSize = size;
		}
		ifs.close();

		return ret;
	}
	long long int FindCPPl(std::string tag, long long int start)
	{
		long long int ret = -1;
		if (start < 0)start = 0;
		if ((buf == nullptr) || (bufSize <= 0)||(tag.size()<=0)) return ret;

		long long int cnt = bufSize - tag.size();
		if (start >= cnt) return ret;

		for (long long int i = start; i < cnt; i++)
		{
			if ((buf[i] == tag[0])
				&& (buf[i + 1] == tag[1])
				&& (buf[i + 2] == tag[2])
				&& (buf[i + 3] == tag[3]))
			{
				ret = i;
				break;
			}
		}
		return ret;
	}
};

