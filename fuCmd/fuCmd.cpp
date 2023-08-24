﻿#include "..\Utils\FsUtil.h"
#include "..\Utils\FsFile.h"
#include "..\Utils\AEProcess.h"
#include "..\Utils\FsProcess.h"
#include "..\Utils\FsJson.h"

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
#include <cstdlib>
#include <algorithm>

// *****************************************************************************************
static void Usage(char *ex)
{
	std::string ret = "";
	std::string exe = std::string((char*)GetName(ex));
	ret = "[" + exe + "] FsUtils.dll動作確認用コマンド\r\n";
	ret += "\n";
	ret += "\t" + exe + " getClip\r\n";
	ret += "\t" + exe + " setClip string\r\n";
	ret += "\t" + exe + " GetParent '文字列'\r\n";
	ret += "\t" + exe + " GetName '文字列'\r\n";
	ret += "\t" + exe + " GetNameWithoutExt '文字列'\r\n";
	ret += "\t" + exe + " GetExt '文字列'\r\n";
	ret += "\t" + exe + " processAEList\r\n";
	ret += "\t" + exe + " processList\r\n";
	ret += "\t" + exe + " showWindow  ウィンドウハンドル sw\r\n";
	ret += "\t" + exe + " windowMax\r\n";
	ret += "\t" + exe + " windowMin\r\n";
	ret += "\t" + exe + " windowNormal\r\n";
	ret += "\t" + exe + " getMousePos\r\n";
	ret += "\t" + exe + " setMousePos x y\r\n";
	ret += "\t" + exe + " beep num\r\n";
	ret += "\t" + exe + " installedAE\r\n";
	ret += "\t" + exe + " isInstalledESTK\r\n";
	ret += "\t" + exe + " aePlaySound num\r\n";
	ret += "\t" + exe + " PlaySound num\r\n";
	ret += "\t" + exe + " callCommand args\r\n";
	ret += "\t" + exe + " callCommandWait args\r\n";
	ret += "\t" + exe + " callCommandResult args\r\n";

	//



	std::cout << ret;
}
// *****************************************************************************************
static int Command(int argc, char* argv[])
{
	int ret = 0;
	if (argc <= 1) return ret;
	if (argc >= 2)
	{

		std::string key = std::string(argv[1]);
		transform(key.begin(), key.end(), key.begin(), tolower);
		if ((key == "getclip") || (key == "gc"))
		{
			std::cout << GetTextClipboard();
			std::cout << "\n";
			ret = 1;
		}
		else if ((key == "setclip") || (key == "sc"))
		{
			if (argc >= 3) {
				SetTextClipboard(argv[2]);
				std::cout << "SetTextClipboard() ok\n";
				ret = 1;
			}
		}
		else if ((key == "pathgetparent") || (key == "getparent"))
		{
			if (argc >= 3) {
				char* s = GetParent(argv[2]);
				std::cout << s;
				std::cout << "\n";
				ret = 1;
			}
		}
		else if ((key == "pathgetname") || (key == "getname"))
		{
			if (argc >= 3) {
				char* s = GetName(argv[2]);
				std::cout << s;
				std::cout << "\n";
				ret = 1;
			}
		}
		else if ((key == "pathgetnamewithoutext") || (key == "getnamewithoutext"))
		{
			if (argc >= 3) {
				char* s = GetNameWithoutExt(argv[2]);
				std::cout << s;
				std::cout << "\n";
				ret = 1;
			}
		}
		else if ((key == "pathgetext") || (key == "getext"))
		{
			if (argc >= 3) {
				char* s = GetExt(argv[2]);
				std::cout << s;
				std::cout << "\n";
				ret = 1;
			}
		}
		else if ((key == "processaelist") || (key == "plist") || (key == "aps"))
		{
			if (argc >= 3) {
				std::cout << listupAEProcess(false);
				std::cout << "\n";
				ret = 1;
			}
		}
		else if ((key == "showwindow") || (key == "shw"))
		{
			if (argc >= 4) {
				HWND hWND = (HWND)atoi(argv[2]);
				int sw = atoi(argv[3]);
				int ff = ShowWindow(hWND, sw);
				std::cout << "ShowWindow : ";
				std::cout << ff;
				std::cout << "\n";
				ret = ff;
			}
		}
		else if ((key == "aeshowwindow") || (key == "aeshow"))
		{
			if (argc >= 3)
			{
				int sw = (int)atoi(argv[2]);
				AEShowWindow(sw);
				std::cout << "AEShowWindow:";
				std::cout << argv[2];
				std::cout << "\n";
				ret = 1;
			}
		}
		else if ((key == "windowmax") || (key == "wmax"))
		{
			AEShowWindow(3);
			std::cout << "WindowMin\n";
			ret = 1;
		}
		else if ((key == "windowmin") || (key == "wmin"))
		{
			AEShowWindow(2);
			std::cout << "WindowMin\n";
			ret = 1;
		}
		else if ((key == "windownormal") || (key == "wnormal"))
		{
			AEShowWindow(1);
			std::cout << "WindowNormal\n";
			ret = 1;
		}
		else if ((key == "getmousepos") || (key == "getmp"))
		{
			std::cout << GetMousePosString();
			std::cout << "\n";
			ret = 1;
		}
		else if ((key == "setmousepos") || (key == "setmp"))
		{
			if (argc >= 4)
			{
				int x = atoi(argv[2]);
				int y = atoi(argv[3]);
				SetMousePos(x, y);
				std::cout << "SetMousePos()\n";
				ret = 1;
			}
		}
		else if ((key == "beep") || (key == "bp"))
		{
			HINSTANCE hInst= NULL;
			if (argc >= 2)hInst = GetModuleHandle("FsUtils.exe");
			if (argc >= 3)
			{
				int v = atoi(argv[2]);
				if (v < 1) v = 1;
				else if (v > 52) v = 1;
				PlayResource(hInst, v);
				ret = 1;
			}
			else if (argc >= 2)
			{
				PlayResource(hInst, 1);
				ret = 1;
			}
		}
		else if ((key == "installedae") || (key == "iae"))
		{
			std::string ss = InstalledAFXAS();
			std::cout << ss;
			std::cout << "\n";
			ret = 1;
		}
		else if ((key == "isInstalledestk") || (key == "ieskt"))
		{
			bool ss = IsInstalledESTK();
			std::cout << ss;
			std::cout << "\n";
			ret = 1;
		}
		else if ((key == "processlist") || (key == "ps"))
		{
			std::string ss = ProcessList(false,true);
			std::cout << ss;
			std::cout << "\n";
			ret = 1;
		}
		else if ((key == "aeplaysound") || (key == "apsnd"))
		{
			if (argc >= 3)
			{
				int v = atoi(argv[2]);
				if (v < 0) v = 0;
				else if (v > 2) v = 2;
				PlayAESound(v);
				ret = 1;
			}
			else if (argc >= 2)
			{
				PlayAESound(0);
				ret = 1;
			}
		}
		else if ((key == "playsound") || (key == "psnd"))
		{
			if (argc >= 3)
			{
				SoundPlay(argv[2]);
				ret = 1;
			}
		}
		else if ((key == "callcommand") || (key == "callc"))
		{
			if (argc >= 3)
			{
				ret = CallCommand(argv[2]);
			}
		}
		else if ((key == "callcommandwait") || (key == "callcw"))
		{
			if (argc >= 3)
			{
				ret = CallCommandWait(argv[2]);
			}
		}
	}
	return ret;
}
// *****************************************************************************************
int main(int argc, char* argv[])
{

	int ret = Command(argc, argv);
	if (ret == 0)
	{
		Usage(argv[0]);
	}
	//HINSTANCE hInst = GetModuleHandle("FsUtils.exe");
	//PlayResource(hInst, 52);
	//PlayAESound(0);
	//SoundPlay("C:\\Windows\\Media\\Windows Logon.wav");
	//CallCommand("C:\\Users\\bryfu\\Source\\Repos\\FsUtils\\ChkForm\\bin\\Release\\net6.0-windows\\publish\\ChkForm.exe");
	//CallCommandWait("ChkForm.exe");
	//ret = CallCommand("ChkForm.exe");

	/*
	char js[] = "({aaa:12,bbb:\"aaa\\bbb\\\"\",cc:[12,23,({ddd:12,eee:\"eee\"})]})";
	
	std::string jss = std::string(js);
	std::string jss2 = FromAEJson(jss);
	std::string jss3 = ToAEJson(jss2);

	std::cout << jss;
	std::cout << "\n";
	std::cout << jss2;
	std::cout << "\n";
	std::cout << jss3;
	std::cout << "\n";
	*/

	std::string sss = "あああD/E愛してるEE.tgaあなたの名前はなる丸です";
	
	std::vector< std::string> sa = Split(sss, "/");

	std::string  sa2 = Join(sa, "@@");
	std::cout << sa2;
	std::cout << "\n";

	char* ff =  ShiftJistoUtf8((char*)sss.c_str());

	if (IsUTF8(ff))
	{
		std::cout << "utf-8";
	}
	else {
		std::cout << "sjis";
	}
	std::cout << "\n";

	return ret;
}