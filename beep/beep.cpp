// beep.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

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
#include <system_error>
#include <mmsystem.h>
#include <vector>
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

#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <Mmsystem.h>

#pragma comment(lib, "winmm.lib")

BOOL PlayResource(HANDLE hInst, int id)
{

	BOOL bRtn = false;
	LPSTR lpRes;
	HANDLE hResInfo, hRes;

	// Find the WAVE resource. 

	char NUM[20];
	memset(NUM, '\0', 20);
	sprintf_s(NUM, 20, "#%d", 100 + id);

	hResInfo = FindResource((HMODULE)hInst, NUM, "WAVE");

	if (hResInfo == NULL)
		return FALSE;

	// Load the WAVE resource. 

	hRes = LoadResource((HMODULE)hInst, (HRSRC)hResInfo);
	if (hRes == NULL)
		return FALSE;

	// Lock the WAVE resource and play it. 

	lpRes = (LPSTR)LockResource(hRes);// 
	if (lpRes != NULL) {
		bRtn = sndPlaySound(lpRes, SND_MEMORY | SND_SYNC | SND_NODEFAULT);
		//bRtn = PlaySound(lpRes, (HMODULE)hInst, SND_MEMORY | SND_ASYNC);
		UnlockResource(hRes);
	}
	else {
		bRtn = 0;
	}

	// Free the WAVE resource and return success or failure. 

	FreeResource(hRes);
	return bRtn;
}
BOOL PlayWave(std::string nm)
{
	BOOL bRtn;


	bRtn = PlaySound(TEXT(nm.c_str()), NULL, (SND_SYNC | SND_FILENAME | SND_NODEFAULT));
	//bRtn = PlaySound(TEXT(lpName), NULL, (SND_ASYNC | SND_FILENAME ));
	return bRtn;
}


int main(int argc, char* argv[])
{
	int ret = 0;
	if (argc >= 3)
	{
		std::string s1 = std::string(argv[1]);
		std::string s2 = std::string(argv[2]);
		if (s1 == "file")
		{
			ret = PlayWave(s2);
		}
		else if (s1 == "res")
		{
			HMODULE  hModule = GetModuleHandle("beep.exe");
			int idx = 1;
			try {
				idx = std::stoi(s2);
			}
			catch (...)
			{

			}
			ret = PlayResource(hModule, idx);

		}

	}

	return 1;
}
