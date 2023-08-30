#include "FsFile.h"


// ********************************************************************************************************
/*
	ファイルがあるか確認
*/
// ********************************************************************************************************
bool ExistFile(std::string path)
{
	return ExistFile((const char*)path.c_str());
}
bool ExistDirectory(std::string path)
{
	return ExistDirectory((const char*)path.c_str());
}


bool ExistFile(char* path)
{
	return ExistFile((const char*)path);
}
bool ExistDirectory(char* path)
{
	return ExistDirectory((const char*)path);
}
bool ExistFile(const char* path)
{
	return PathFileExists((LPCSTR)path);
}
bool ExistDirectory(const char* path)
{
	return PathIsDirectory((LPCSTR)path);
}

// ********************************************************************************************************
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
std::string GetTempDataFile()
{
	return GetTempFolder() + "fuTemp.txt";
}

std::string GetAppDataFolder()
{
	TCHAR waFolderPath[MAX_PATH];
	SHGetSpecialFolderPath(NULL, waFolderPath, CSIDL_APPDATA, 0);
	return std::string(waFolderPath);
}
std::string GetAppDataFolder(std::string name,std::string productname)
{
	TCHAR waFolderPath[MAX_PATH];
	SHGetSpecialFolderPath(NULL, waFolderPath, CSIDL_APPDATA, 0);
	std::string rr = "";
	if (productname.size() > 0) {
		rr = CombinePath(std::string(waFolderPath), productname);
		if (ExistDirectory(rr) == false)
		{
			_mkdir(rr.c_str());
		}
	}
	else {
		rr = std::string(waFolderPath);
	}
	if (name.size() > 0)
	{
		rr = CombinePath(rr, name);
		if (ExistDirectory(rr) == false)
		{
			_mkdir(rr.c_str());
		}
	}
	return rr;
}

// ********************************************************************************************************
std::string AEPath1 = "C:\\Program Files\\Adobe\\Adobe After Effects";
std::string AEPath2[] = {
	" CC 2018",
	" CC 2019",
	" 2020",
	" 2021",
	" 2022",
	" 2023",
	" 2024",
	" 2025",
	" 2026",
};
std::string AEPath3 = "\\Support Files\\AfterFX.exe";

std::string snd0 = "\\Support Files\\sounds\\rnd_fail.wav";
std::string snd1 = "\\Support Files\\sounds\\rnd_okay.wav";
std::string snd2 = "\\Support Files\\sounds\\snap.wav";

std::string ae_sound_fail()
{
	for (int i = 0; i < AEPath2->size(); i++)
	{
		std::string p = AEPath1 + AEPath2[i] + snd0;
		if (ExistFile((char*)p.c_str()) == true)
		{
			return p;
		}
	}
	return { 0 };
}
std::string ae_sound_okay()
{
	for (int i = 0; i < AEPath2->size(); i++)
	{
		std::string p = AEPath1 + AEPath2[i] + snd1;
		if (ExistFile((char *)p.c_str()) == true)
		{
			return p;
		}
	}
	return { 0 };
}
std::string ae_sound_snap()
{
	for (int i = 0; i < AEPath2->size(); i++)
	{
		std::string p = AEPath1 + AEPath2[i] + snd2;
		if (ExistFile((char*)p.c_str()) == true)
		{
			return p;
		}
	}
	return { 0 };
}

std::vector< std::string> InstalledAFX()
{
	std::vector< std::string> ret;

	ret.reserve(10);
	for (int i = 0; i < AEPath2->size(); i++)
	{
		std::string p = AEPath1 + AEPath2[i] + AEPath3;
		if (ExistFile((char*)p.c_str()) == true)
		{
			ret.push_back(p);
		}
	}
	return ret;
}

char* InstalledAFXAS()
{
	std::vector< std::string> list ;
	list = InstalledAFX();
	std::string ret;
	if (list.size() > 0)
	{
		for(int i=0; i< list.size();i++)
		{
			if (ret.empty() == false) ret += ",";
			std::string c = list[i];
			ReplaceAll(c, "\\", "\\\\");
			c = "new File(\"" + c + "\")";
			ret += c;
		}
	}
	ret = "[" + ret + "]";

	return getNewBuffer(ret);
}

bool IsInstalledESTK()
{
	const char*  ESTKPath = "C:\\Program Files (x86)\\Adobe\\Adobe ExtendScript Toolkit CC\\ExtendScript Toolkit.exe";

	return ExistFile((char*)ESTKPath);
}
std::string PathToWinFromJS(std::string str)
{
	std::string ret = "";
	if (str.size() < 3) return str;

	str = ReplaceAll(str, "/", "\\");
	BOOL isJS = false;
	if ((str[0] == '\\') && (str[2] == '\\'))
	{
		char c = str[1];
		if ((c >= 'a') && (c <= 'z'))
		{
			isJS = true;
			str[1] = str[1] + 'A' - 'a';
		}
		else if ((c >= 'A') && (c <= 'Z'))
		{
			isJS = true;
		}
	}
	if (isJS == false)
	{
		ret = str;
	}
	else {
		ret = str.substr(1, 1) + ":" + str.substr(2);
	}
	return ret;
}
std::string PathToJSFromWin(std::string str)
{
	std::string ret = "";
	if (str.size() < 3) return str;

	str = ReplaceAll(str, "\\", "/");
	BOOL isWin = false;
	if ((str[1] == ':') && (str[2] == '/'))
	{
		char c = str[0];
		if ((c >= 'a') && (c <= 'z'))
		{
			isWin = true;
		}
		else if ((c >= 'A') && (c <= 'Z'))
		{
			str[0] = str[0] - ('A' - 'a');
			isWin = true;
		}
	}
	if (isWin == false)
	{
		ret = str;
	}
	else {
		// A:\aaa
		// /a/aaa
		ret =  "/" + str.substr(0, 1)  + str.substr(2);
	}
	return ret;
}
std::string GetExt(std::string str)
{
	std::string ret = "";
	if (str.size() <= 0) return ret;
	int idx = str.find_last_of(".");
	if (idx != std::string::npos)
	{
		ret = str.substr(idx);
	}
	return ret;
}
std::string GetFileName(std::string str)
{
	std::string ret = "";
	if (str.size() <= 0) return ret;
	int idx = str.find_last_of("\\");
	if (idx != std::string::npos)
	{
		idx = str.find_last_of("/");
	}
	if (idx != std::string::npos)
	{
		ret = str.substr(idx);
	}
	return ret;
}
std::string GetFileNameWithoutExt(std::string str)
{
	std::string ret = "";
	if (str.size() <= 0) return ret;
	int idx = str.find_last_of("\\");
	if (idx != std::string::npos)
	{
		idx = str.find_last_of("/");
	}
	if (idx != std::string::npos)
	{
		std::string n = str.substr(idx);
		int idx2 = str.find_last_of(".");
		if (idx2 != std::string::npos)
		{
			ret = n.substr(0, idx2);
		}
		else {
			ret = n;
		}
	}
	return ret;
}
std::string CombinePath(std::string str1, std::string str2)
{
	std::string ret = "";
	if (str1.size() <= 0) return str2;
	if (str2.size() <= 0) return str1;

	str1 = TrimTailSepa(str1);
	str2 = TrimHeadSepa(str2);

	ret = str1 + "\\" + str2;
	return ret;
}
std::string GetDir(std::string str)
{
	std::string ret = "";
	if (str.size() <= 0) return ret;
	int idx = str.find_last_of("\\");
	if (idx != std::string::npos)
	{
		idx = str.find_last_of("/");
	}
	if (idx != std::string::npos)
	{
		ret = str.substr(0,idx);
	}
	return ret;
}
BOOL SplitFileName(std::string str, std::string& dir, std::string& name, std::string& ext )
{
	BOOL ret = FALSE;
	dir = "";  name = ""; ext = "";
	if (str.size() <= 0) return ret;
	int didx = str.find_last_of("\\");
	if (didx == std::string::npos)
	{
		didx = str.find_last_of("/");
	}
	std::string n = "";
	//dir
	if (didx != std::string::npos)
	{
		dir = str.substr(0, didx);
		n = str.substr(didx+1);
	}
	else {
		n = str;
	}
	int eidx = n.find_last_of(".");
	if (eidx != std::string::npos)
	{
		ext = n.substr(eidx);
		name = n.substr(0, eidx);
	}
	return TRUE;
}
char* GetExt(char* str)
{
	char* ret = "\0";
	if (lstrlen(str) <= 0)
	{
		return ret;
	}

	const char* ext = strrchr(str, '.');
	if (ext != NULL)
	{
		const auto length = strlen(ext) + 1;
		ret = (char*)malloc(length);
		lstrcpy(ret, ext);
	}
	return ret;
}
LPTSTR  GetName(LPTSTR  str)
{
	LPTSTR  ret = "\0";
	if (lstrlen(str) <= 0)
	{
		return ret;
	}
	const char* par = strrchr(str, '\\');
	if (par == NULL)
	{
		par = strrchr(str, '/');
	}
	if (par != NULL)
	{
		par++;
	}
	else {
		par = str;
	}
	const auto length = strlen(str) + 1;
	ret = (char*)malloc(length);
	lstrcpy(ret, par);
	return ret;
}
char* GetNameWithoutExt(char* str)
{
	char* ret = "\0";
	if (lstrlen(str) <= 0)
	{
		return ret;
	}
	// 元文字列のポインター
	char* moto = str;

	// ファイル名のスタート
	const char* par = strrchr(moto, '\\');
	if (par == NULL)
	{
		par = strrchr(moto, '/');
	}
	if (par != NULL)
	{
		// 先頭の/の位置なので補正する
		par++;

	}
	else {
		//NULLならば親ディレクトリ文字列は無い
		par = moto;
		// この段階でparはNULLじゃなくなる
	}
	// 拡張子ののスタート
	const char* ext = strrchr(par, '.');
	//ab/aaa.tga
	//0123456789
	if (ext != NULL)
	{
		const auto len = ext - par;
		ret = (char*)malloc(len + 1);
		memcpy(ret, par, len);
		ret[len] = '\0';
	}
	else {
		const auto len2 = strlen(par);
		ret = (char*)malloc(len2 + 1);
		memcpy(ret, par, len2);
	}

	return ret;
}
char* CombinePath(char* s0, char* s1)
{

	const auto l0 = strlen(s0);
	const auto l1 = strlen(s1);

	char* ret;
	if ((l0 <= 0) && (l1 <= 0))
	{
		return { 0 };
	}
	else if ((l0 <= 0) && (l1 > 0))
	{
		ret = s1;
	}
	else if ((l0 > 0) && (l1 <= 0))
	{
		ret = s0;
	}
	else {
		std::cout << "3\n";
		std::string p0 = std::string(s0);
		std::string p1 = std::string(s1);

		if (p0[p0.size() - 1] == '\\')
		{
			p0.pop_back();
		}
		if (p1[0] == '\\')
		{
			p1.erase(p1.begin());
		}
		std::string c = p0 +"\\" + p1;

		ret = getNewBuffer(c);		
	}

	return ret;
}
std::string DllPath()
{
	const size_t sz = 2048;
	char szModulePath[sz];
	HMODULE  hModule = GetModuleHandle("fu.dll");
	char  szModuleFileName[sz] = { 0 };
	ZeroMemory(szModuleFileName, sz);
	GetModuleFileName(hModule, szModuleFileName, sz);
	std::string ret = std::string(szModuleFileName);
	int path_i = ret.find_last_of("\\") + 1;
	std::string pathname = ret.substr(0, path_i);

	return pathname;
}

BOOL SavePref(std::string fname, std::string dname, std::string productName, std::string data)
{
	std::string ap = GetAppDataFolder(dname,productName);
	std::string filename = CombinePath(ap, fname);
	std::ofstream writing_file;
	BOOL ret = false;

	if (ExistFile(filename) == true) DeleteFile((LPCSTR)filename.c_str());

	writing_file.open(filename, std::ios::app);
	writing_file << data << std::endl;
	ret = ExistFile(filename);
	writing_file.close();

	return ret;
}
BOOL LoadPref(std::string fname, std::string dname, std::string productName, std::string& data)
{
	std::string ap = GetAppDataFolder(dname,productName);
	std::string filename = CombinePath(ap, fname);
	std::ofstream writing_file;
	BOOL ret = false;

	if (ExistFile(filename) == true)
	{
		std::ifstream ifs(filename);
		std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		data = str;
		ret = true;
	}
	return ret;
}