#include "Util.h"

// ******************************************************************
BOOL SetTextClipboard(LPCTSTR lpString)
{
    if (!OpenClipboard(NULL)) return false;
	LPTSTR c = UTF8ToSjis((LPTSTR)lpString);

    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GHND | GMEM_SHARE, lstrlen(lpString)+1);
    LPTSTR strMem = (LPTSTR)GlobalLock(hg);
    lstrcpy(strMem, c);
    GlobalUnlock(hg);

    if (SetClipboardData(CF_TEXT, hg) == false)
    {

    }

    CloseClipboard();
    return true;
}
LPCTSTR GetTextClipboard()
{
    HGLOBAL hg;
    LPTSTR strText = '\0';
    LPTSTR strClip = '\0';
    if (OpenClipboard(NULL) && (hg = GetClipboardData(CF_TEXT))) {
        strText = (PTSTR)malloc(GlobalSize(hg));
        strClip = (PTSTR)GlobalLock(hg);
        lstrcpy(strText, strClip);

        GlobalUnlock(hg);
        CloseClipboard();

		strText = SjisToUTF8(strText);
		//std::string cc = SjistoUTF8((std::string)strText);
		//strText = (PTSTR)(cc.c_str());
	}
    return strText;
}
// ******************************************************************
LPTSTR SjisToUTF8(LPTSTR srcSjis)
{
	//Unicodeへ変換後の文字列長を得る
	int lenghtUnicode = MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis, lstrlen(srcSjis) + 1, NULL, 0);

	//必要な分だけUnicode文字列のバッファを確保
	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];

	//ShiftJISからUnicodeへ変換
	MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis, lstrlen(srcSjis) + 1, bufUnicode, lenghtUnicode);


	//UTF8へ変換後の文字列長を得る
	int lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, NULL, 0, NULL, NULL);

	//必要な分だけUTF8文字列のバッファを確保
	char* bufUTF8 = new char[lengthUTF8];

	//UnicodeからUTF8へ変換
	WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenghtUnicode - 1, bufUTF8, lengthUTF8, NULL, NULL);

	LPTSTR s = bufUTF8;

	delete bufUnicode;

	return s;
}
LPTSTR UTF8ToSjis(LPTSTR srcUTF8)
{
	//Unicodeへ変換後の文字列長を得る
	int lenghtUnicode = MultiByteToWideChar(CP_UTF8, 0, srcUTF8, lstrlen(srcUTF8) + 1, NULL, 0);

	//必要な分だけUnicode文字列のバッファを確保
	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];

	//UTF8からUnicodeへ変換
	MultiByteToWideChar(CP_UTF8, 0, srcUTF8, lstrlen(srcUTF8) + 1, bufUnicode, lenghtUnicode);

	//ShiftJISへ変換後の文字列長を得る
	int lengthSJis = WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, NULL, 0, NULL, NULL);

	//必要な分だけShiftJIS文字列のバッファを確保
	char* bufShiftJis = new char[lengthSJis];

	//UnicodeからShiftJISへ変換
	WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, lenghtUnicode + 1, bufShiftJis, lengthSJis, NULL, NULL);

	std::string strSJis(bufShiftJis);

	delete bufUnicode;

	return (LPTSTR)bufShiftJis;
}
// ******************************************************************
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
		//ret = dynamic_cast<char*>(malloc(length));
		lstrcpy(ret, ext);
	}
	return ret;
}
char* GetName(char* str)
{
	char* ret = "\0";
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


char* GetParent(char* str)
{
	char* moto = str;
	char* ret = "\0";
	const char* par = strrchr(moto, '\\');
	if (par == NULL)
	{
		par = strrchr(moto, '/');
	}
	if (par != NULL)
	{
		//abcde/aaa
		//012345678
		const auto len = par - moto;
		ret = (char*)malloc(len + 1);
		memcpy(ret, moto, len);
		ret[len] = '\0';
	}
	return ret;
}
/*
char* AEProcessList()
{
	char* ret = "\0";
	DWORD allProc[1024];
	DWORD cbNeeded;
	int nProc;
	int i;
	
	// PID一覧を取得
	if (!EnumProcesses(allProc, sizeof(allProc), &cbNeeded)) {
		return "([])";
	}

	nProc = cbNeeded / sizeof(DWORD);

	for (i = 0; i < nProc; i++) {
		TCHAR procName[MAX_PATH] = TEXT("<unknown>");

		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, allProc[i]);

		// プロセス名を取得
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;

			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
				&cbNeeded)) {
				GetModuleBaseName(hProcess, hMod, procName,
					sizeof(procName) / sizeof(TCHAR));
			}
		}
		if (strcmp(procName, "AfterFX") == 0)
		{
			if (strlen(ret) == 0) ret = strcat(ret, ",");
			char* line = "({";
			char sss[20];
			sprintf(sss, "({pid:%d,hdl:%d", allProc[i]);
			line = strcat(line, sss);
		}

		// プロセス名とPIDを表示
		_tprintf(TEXT("%s  (PID: %u)\n"), procName, allProc[i]);

		CloseHandle(hProcess);
	}
}
*/