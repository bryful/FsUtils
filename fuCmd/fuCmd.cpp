#include "..\Utils\FsUtil.h"
#include "..\Utils\FsFile.h"
#include "..\Utils\AEProcess.h"
#include "..\Utils\FsProcess.h"
#include "..\Utils\FsJson.h"
#include "..\Utils\FsTempData.h"
#include "..\Utils\CmdArg.h"
#include "resource.h"

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

std::string ExePath()
{
	const size_t sz = 2048;
	char szModulePath[sz];
	HMODULE  hModule = GetModuleHandle("fuCmd.exe");
	char  szModuleFileName[sz] = { 0 };
	ZeroMemory(szModuleFileName, sz);
	GetModuleFileName(hModule, szModuleFileName, sz);
	std::string ret = std::string(szModuleFileName);
	int path_i = ret.find_last_of("\\") + 1;
	std::string pathname = ret.substr(0, path_i);

	return pathname;
}
static int Edit(char* src)
{
	int ret = 0;
	std::string parent = ExePath();
	std::string cmd;
	cmd = parent + "Edit.exe";
	if (ExistFile(cmd) == false) {
		std::cout << "Exists Err";
		std::cout << "\r\n";
		return ret;
	}
	FsTempData td;
	td.Data = std::string(src);
	td.SaveInput();

	cmd = "\"" + cmd + "\"" + " -tmp";
	Popen(cmd,"");

	if (td.Load() == true)
	{
		std::cout << td.Data << std::endl;
	}
	else {
		std::cout << "null" << std::endl;
	}

}




// *****************************************************************************************
static void Usage(CmdArg arg)
{
	std::string ret = "";
	std::string exe = "fuCmd.exe";
	ret = "[" + exe + "] FsUtils.dll動作確認用コマンド\n\n";
	ret += arg.OptionList();
	std::cout << ret << std::endl;
}
// *****************************************************************************************
int SetClip(std::vector<std::string> op)
{
	int ret = 0;
	if (op.size() > 0) {
		if (SetTextClipboard(op[0], false))
		{
			ret = 1;
		}
	}
	return ret;
}
// *****************************************************************************************
int GetClip(std::vector<std::string> op)
{
	int ret = 0;
	std::string clip = GetTextClipboard(false);
	if (clip.empty()==false)
	{
		std::cout << clip << std::endl;
		ret = 1;
	}
	return ret;
}
int SplitPath(std::vector<std::string> op)
{
	int ret = 0;
	if (op.size() > 0) 
	{
		std::cout << std::endl;
		std::cout << "          parent : " << GetDir(op[0]) << std::endl;
		std::cout << "            name : " << GetName(op[0]) << std::endl;
		std::cout << "  nameWithoutExt : " << GetNameWithoutExt(op[0]) << std::endl;
		std::cout << "           Frame : " << GetFrame(op[0]) << std::endl;
		std::cout << "nameWithoutFrame : " << GetNameWithoutFrame(op[0]) << std::endl;
		std::cout << "             ext : " << GetExt(op[0]) << std::endl;
		ret = 1;
	}
	return ret;
}
int Beep(std::vector<std::string> op)
{
	int ret = 0;
	if (op.size() > 0)
	{
		std::string dir = ExePath();
		

		HMODULE  hModule = GetModuleHandle("fuCmd.exe");
		PlayBeep(dir,op[0]);
		ret = 1;
	}
	return ret;
}
int Screens(std::vector<std::string> op)
{
	int ret = 0;
	std::vector<MONITORINFOEX> rr = ScreenInfo();
	if (rr.size() > 0)
	{
		for each (MONITORINFOEX r in rr)
		{
			std::string info = "-----------\n";
			info = "M:"+RECTtoStr(r.rcMonitor) + "\n";
			info += "W:"+RECTtoStr(r.rcWork) + "\n";
			info += std::to_string(r.dwFlags == MONITORINFOF_PRIMARY) + "\n";
			//info += std::string(r.szDevice, sizeof r.szDevice) + "\n";
			std::cout << info;
		}
		ret = 1;
	}

	return ret;
}
// *****************************************************************************************
int main(int argc, char* argv[])
{
	WNDCLASSEX wcx;
	HINSTANCE hInstance = GetModuleHandle("fuCmd.exe");
	wcx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcx.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	CmdArg arg(argc, argv);

	CmdArgItem k({ "setclipboard","setclip","setc" }, 1, "クリップボードに文字列をセットします");
	k.CmdExec = SetClip;
	arg.AddOption(k);
	CmdArgItem k2({ "getclipboard","getclip","getc" }, 0, "クリップボードから文字列を獲得します");
	k2.CmdExec = GetClip;
	arg.AddOption(k2);
	CmdArgItem k3({ "splitpath","spath","sp" }, 1, "パスを分割します");
	k3.CmdExec = SplitPath;
	arg.AddOption(k3);
	CmdArgItem k4({ "beep","wav" }, 1, "Beep音");
	k4.CmdExec = Beep;
	arg.AddOption(k4);
	CmdArgItem k5({ "screensizes","scr"}, 0, "スクリーンサイズの獲得");
	k5.CmdExec = Screens;
	arg.AddOption(k5);



	//PlayWave("135.wav");


	

	FsJson fj;
	double v = 10;
	fj.SetValue("Int", v);
	double v2 = 0;
	if (fj.Value("Int", v2))
	{
		std::cout << v2 << std::endl;
	}
	//std::vector<std::string> sa = {string( ShiftJistoUtf8("ああ")),string(ShiftJistoUtf8("bbb"))};
	std::vector<std::string> sa = { string("ああ"),string("bbb") };
	fj.SetValue("vs", sa);
	std::vector<std::string> sa2;
	if (fj.Value("vs", sa2))
	{
		std::cout << Join(sa2,",") << std::endl;
	}
	std::cout << Join(fj.Keys(), ",") << std::endl;
	std::cout << fj.ToJson() << std::endl;

	fj.Save("json.txt");

	if (arg.Exec() == 0)
	{
		Usage(arg);
		return 0;
	}
	return 1;

}
