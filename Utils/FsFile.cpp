#include "FsFile.h"


// ********************************************************************************************************
/*
	ファイルがあるか確認
*/
// ********************************************************************************************************
bool ExistFile(const char* path)
{
	if ((PathFileExists(path) != 0))
	{
		return true;
	}
	else {
		return false;
	}
}
bool ExistDirectory(const char* path)
{
	if ((PathIsDirectory(path) != 0))
	{
		return true;
	}
	else {
		return false;
	}
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
		if (ExistFile(p.c_str()) == true)
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
		if (ExistFile(p.c_str()) == true)
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
		if (ExistFile(p.c_str()) == true)
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
		if (ExistFile(p.c_str()) == true)
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

	return ExistFile(ESTKPath);
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
