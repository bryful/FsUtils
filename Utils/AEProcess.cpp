#include "AEProcess.h"


// スキャン用のグローバル変数。
std::vector<PCell> pCell;
BOOL m_IsUtf8 = true;
#define OPEN_PROCESS  (PROCESS_QUERY_INFORMATION | PROCESS_VM_READ)


//https://sayahamitt.net/cpp%E3%81%A7url%E3%82%A8%E3%83%B3%E3%82%B3%E3%83%BC%E3%83%80%E4%BD%9C%E3%81%A3%E3%81%9F/


// EnumWindowsのコールバック関数
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	TCHAR   szTitle[1024];
	memset(szTitle, '\0', 1024);
	INT* lpCount = (INT*)lParam;
	DWORD	processId;
	TCHAR	processName[MAX_PATH];
	memset(processName, '\0', MAX_PATH);
	TCHAR   szFile[1024] = { 0 };
	memset(szFile, '\0', 1024);
	HMODULE Module[1024] = { 0 };
	DWORD	dwSize;

	*lpCount += 1;                                      // カウントの加算
	GetWindowText(hWnd, szTitle, sizeof(szTitle));    // キャプションの取得
	//タイトル無かったら辞める
	if (strlen(szTitle)<=0) return TRUE;
	GetWindowThreadProcessId(hWnd, &processId);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (NULL != hProcess) {
		// プロセスハンドルからプロセス名を取得します。
		GetModuleBaseName(hProcess, NULL, processName, _countof(processName));
		if (EnumProcessModules(hProcess, Module, sizeof(Module), &dwSize)) {
			GetModuleFileNameEx(hProcess, Module[0], szFile, sizeof(szFile));
		}
		// プロセスハンドルのクローズ
		CloseHandle(hProcess);
		//プロセス名がなかったらおわる
		if (strlen(processName) <= 0) return TRUE;
	}


	PCell pcl;
	pcl.hWnd = hWnd;
	pcl.Title = szTitle;
	if ((pcl.Title.empty() == false)&&(std::strcmp(pcl.Title.c_str(), "Default IME") != 0))
	{
		pcl.Path = std::string(szFile);
		pcl.IsZoomed = IsZoomed(hWnd);
		pcl.IsIconic = IsIconic(hWnd);
		pcl.IsWindow = IsWindow(hWnd);
		pcl.ProcessName = std::string(processName);
		pcl.Pid = processId;
		pCell.push_back(pcl);
	}
	return TRUE;
}

BOOL CALLBACK EnumWindowsAEProc(HWND hWnd, LPARAM lParam)
{
	TCHAR   szTitle[1024];
	memset(szTitle, '\0', 1024);
	INT*	lpCount = (INT*)lParam;
	DWORD	processId;
	TCHAR	processName[MAX_PATH];
	memset(processName, '\0', MAX_PATH);
	TCHAR   szFile[1024] = { 0 };
	memset(szFile, '\0', 1024);
	HMODULE Module[1024] = { 0 };
	DWORD	dwSize;

	*lpCount += 1;                                      // カウントの加算
	GetWindowText(hWnd, szTitle, sizeof(szTitle));    // キャプションの取得
	size_t idx = -1;
	std::string s = std::string(szTitle);
	if (s.empty() == false) {
		idx = s.find("Adobe After Effects");
	}
	if (idx != 0) return TRUE;
	GetWindowThreadProcessId(hWnd, &processId);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (NULL != hProcess) {
		// プロセスハンドルからプロセス名を取得します。
		GetModuleBaseName(hProcess, NULL, processName, _countof(processName));
		idx  = std::strcmp(processName, "AfterFX.exe");
		if ( idx == 0)
		{
			if (EnumProcessModules(hProcess, Module, sizeof(Module), &dwSize))
			{
				GetModuleFileNameEx(hProcess, Module[0], szFile, sizeof(szFile));
			}
		}
		// プロセスハンドルのクローズ
		CloseHandle(hProcess);
		if (idx != 0) return TRUE;
	}

	PCell pcl;
	AEFX_CLR_STRUCT(pcl);

	pcl.hWnd = hWnd;
	pcl.ProcessName = std::string(processName);
	pcl.Title = std::string(szTitle);
	pcl.Path = std::string(szFile);
	pcl.IsZoomed = IsZoomed(hWnd);
	pcl.IsIconic = IsIconic(hWnd);
	pcl.IsWindow = IsWindow(hWnd);
	pcl.Pid = processId;
	pCell.push_back(pcl);

	return TRUE;
}


#pragma warning(disable : 4996) 

// URLエンコードはここのを使ってます。
//https://gist.github.com/sasairc/20ffb55dbe225dbd6a8258f7a2f92a38
#ifndef DEFAULT_BUFSIZE
#define DEFAULT_BUFSIZE 1024
/* DEFAULT_BUFSIZE */
#endif

int encode_uri(char* const src, char** dest)
{
	int     status = 0;

	size_t  bufsiz = DEFAULT_BUFSIZE,
		current = 0;    /* dest のオフセット */

	char* p = src;  /* src をなめる */

	/* エンコード後の文字列を格納するメモリ領域の確保 */
	if ((*dest = (char*)
		malloc(sizeof(char) * bufsiz)) == NULL) {
		status = -1; goto ERR;
	}
	else {
		/* 確保された領域の初期化 */
		memset(*dest, '\0', bufsiz);
	}

	/* ヌル文字 '\0' が出現するまでぐるぐる回す */
	while (*p != '\0') {
		/* エンコード後の文字列を格納するメモリ領域の再確保 */
		if ((current + 3) >= bufsiz) {
			bufsiz += DEFAULT_BUFSIZE;
			if ((*dest = (char*)
				realloc(*dest, sizeof(char) * bufsiz)) == NULL) {
				status = -2; goto ERR;
			}
			else {
				/* 再確保された領域の初期化 */
				memset(*dest + current, '\0', DEFAULT_BUFSIZE);
			}
		}
		/*
		 * true:  アドレス p が指す領域の値は変換対象
		 * false: アドレス p が指す領域の値は変換対象外
		 */
		if (
			(*p >= 0x20 && *p <= 0x39) ||  /* [0-9] */
			(*p >= 0x41 && *p <= 0x5A) ||  /* [A-Z] */
			(*p >= 0x61 && *p <= 0x7A) ||  /* [a-z] */
			(*p == 0x2E) ||  /* . */
			(*p == 0x2F) ||  /* / */
			(*p == 0x3A)                    /* : */
			) {
			/* アドレス p が指す領域の値をそのまま代入 */
			*(*(dest)+current) = *p;
			/* dest のオフセットを加算 */
			current++;
		}
		else {
			/*
			 * アドレス p が指す領域の値を、二桁の16進数へ変換
			 * 途中、暗黙のキャストにより 4byte へ拡張され出力されてしまうので、
			 * ビットへのAND操作により、下位 8bit (1byte) ぶんを取り出す
			 */
			current += sprintf(*dest + current, "%%%02X",
				*p & 0x000000FF);
		}
		/* アドレスを加算 */
		p++;
	}

	return 0;

ERR:
	/* エラー処理 */
	switch (status) {
	case    -1:
	case    -2:
		fprintf(stderr, "%s\n",
			strerror(errno));
		break;
	}

	return status;
}
int decode_uri(char* const src, char** dest)
{
	int     status = 0;

	size_t  bufsiz = DEFAULT_BUFSIZE,
		current = 0;    /* dest のオフセット */

	char* p = src;  /* src を舐める */

	/* デコード後の文字列を格納するメモリ領域の確保 */
	if ((*dest = (char*)
		malloc(sizeof(char) * bufsiz)) == NULL) {
		status = -1; goto ERR;
	}
	else {
		/* 確保された領域の初期化 */
		memset(*dest, '\0', bufsiz);
	}

	/* ヌル文字 '\0' が出現するまでぐるぐる回す */
	while (*p != '\0') {
		/* デコード後の文字列を格納するメモリ領域の再確保 */
		if ((current + 2) >= bufsiz) {
			bufsiz += DEFAULT_BUFSIZE;
			if ((*dest = (char*)
				realloc(*dest, sizeof(char) * bufsiz)) == NULL) {
				status = -2; goto ERR;
			}
			else {
				/* 再確保された領域の初期化 */
				memset(*dest + current, '\0', DEFAULT_BUFSIZE);
			}
		}
		/*
		 * true:  *p == '%' なので変換対象
		 * false: その他は変換対象外
		 */
		if (*p == '%') {
			/* アドレスを加算 (%を飛ばす) */
			p++;
			/* 二桁 (文字なので2byte) の16進数をデコードし、 *(dest) + current へ代入 */
			sscanf(p, "%2X", *(dest)+current);
			/* アドレスを加算 (XXを飛ばす) */
			p += 2;
		}
		else {
			/* アドレス p が指す領域の値をそのまま代入 */
			*(*(dest)+current) = *p;
			/* アドレスを加算 */
			p++;
		}
		/* dest のオフセットを加算 */
		current++;
	}

	return 0;

ERR:
	/* エラー処理 */
	switch (status) {
	case    -1:
	case    -2:
		fprintf(stderr, "%s\n",
			strerror(errno));
		break;
	}

	return status;
}



std::string BoolToString(BOOL b)
{
	if (b) {
		return std::string("true");
	}
	else {
		return std::string("false");
	}
}

std::string ToPathString(std::string s)
{
	std::string ss = s;
	ReplaceAll(ss, std::string("\\"), std::string("\\\\"));
	
	if (m_IsUtf8 == false)
	{
		return ss;
	}
	else {
		std::string ss2 = multi_to_utf8_winapi(ss);
		char* src = (char*)(ss2.c_str());
		char* dst = NULL;
		encode_uri(src, &dst);
		return std::string(dst);
	}
}
std::string PCellToString(PCell p)
{
	std::string str;

	str = "hWND:" + std::to_string((long)p.hWnd);
	str += ",";
	str += "processID:" + std::to_string(p.Pid);
	str += ",";
	str += "processName:\"" + ToPathString(p.ProcessName) + "\"";
	str += ",";
	str += "title:\"" + ToPathString(p.Title) + "\"";
	str += ",";
	str += "path:\"" + ToPathString(p.Path) + "\"";
	str += ",";
	str += "isWindow:" + BoolToString(p.IsWindow);
	str += ",";
	str += "isZoomed:" + BoolToString(p.IsZoomed);
	str += ",";
	str += "isIconic:" + BoolToString(p.IsIconic);

	str = "({" + str + "})";
	return str;
}

std::string ProcessList(bool IsUTF8, bool isLn)
{
	m_IsUtf8 = IsUTF8;
	pCell.clear();
	INT nCount = 0;
	std::string ret;
	// 全ウインドウの列挙
	EnumWindows(EnumWindowsProc, (LPARAM)&nCount);
	if (pCell.size() > 0)
	{
		for (int i = 0; i < pCell.size(); i++)
		{
			std::string s = PCellToString(pCell[i]);
			if (ret.empty() == false) 
			{
				ret += ",";
				if (isLn) ret += "\n";
			}
			ret += s;
		}
		ret = "[" + ret + "]";
	}
	return ret;
}


std::vector<PCell> AEProcessList(BOOL IsUTF8)
{
	std::vector<PCell> result;
	m_IsUtf8 = IsUTF8;
	INT nCount = 0;
	pCell.clear();
	// 全ウインドウの列挙
	EnumWindows(EnumWindowsAEProc, (LPARAM)&nCount);
	if (pCell.size() > 0)
	{
		for (int i = 0; i < pCell.size(); i++)
		{
			PCell ps;
			ps.hWnd = pCell[i].hWnd;
			ps.Pid = pCell[i].Pid;
			ps.IsIconic = pCell[i].IsIconic;
			ps.IsWindow = pCell[i].IsWindow;
			ps.IsZoomed = pCell[i].IsZoomed;
			ps.ProcessName = pCell[i].ProcessName;
			ps.Title = pCell[i].Title;
			ps.Path = pCell[i].Path;
			result.push_back( ps);
		}
	}
	return result;

}
std::string listupAEProcess(BOOL IsUTF8)
{
	std::string ret;
	std::vector<PCell> list = AEProcessList(IsUTF8);
	if (list.size() > 0)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (ret.empty() == FALSE) ret += ",";
			ret += PCellToString(list[i]);;
		}
	}
	ret = "[" + ret + "]";
	return ret;
}

void AEShowWindow(int idx)
{
	ShowWindow(MyWindowHandle(), idx);
	/*
	std::vector<PCell> list = AEProcessList(true);
	if (list.size() > 0)
	{
		for (int i = 0; i < list.size(); i++)
		{
		}
	}
	*/
}
void AEShowWindow(HWND hWnd, int idx)
{
	ShowWindow(hWnd, idx);
}
HWND GetWindowHandle(	// 戻り値: 成功 望みのHWND / 失敗 NULL
	const DWORD TargetID)	// プロセスID
{
	TCHAR   szTitle[1024];
	memset(szTitle, '\0', 1024);
	HWND hWnd = GetTopWindow(NULL);
	do {
		if (GetWindowLong(hWnd, -8) != 0 || !IsWindowVisible(hWnd))
			continue;
		DWORD ProcessID;
		GetWindowThreadProcessId(hWnd, &ProcessID);
		if (TargetID == ProcessID) {
			GetWindowText(hWnd, szTitle, sizeof(szTitle));
			std::string s = std::string(szTitle);
			if (s.empty() == false) {
				if (s.find("Adobe After Effects ") == 0)
				{
					return hWnd;
				}
			}
		}
	} while ((hWnd = GetNextWindow(hWnd, GW_HWNDNEXT)) != NULL);

	return NULL;
}
HWND MyWindowHandle()
{
	DWORD pid = GetCurrentProcessId();
	return GetWindowHandle(pid);
}
