#include "FsUtil.h"

// ******************************************************************
char* getNewBuffer(std::string s)
{
	char* buff = new char[1 + s.size()];

	memset(buff, 0, s.size() + 1);
	lstrcpy(buff, s.c_str());

	return buff;
}

// ******************************************************************
void ReplaceAll(std::string& stringreplace, const std::string& origin, const std::string& dest)
{
	size_t pos = 0;
	size_t offset = 0;
	size_t len = origin.length();
	// 指定文字列が見つからなくなるまでループする
	while ((pos = stringreplace.find(origin, offset)) != std::string::npos) {
		stringreplace.replace(pos, len, dest);
		offset = pos + dest.length();
	}
}
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

    if (SetClipboardData(CF_TEXT, hg) != 0)
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

std::wstring multi_to_wide_winapi(std::string const& src)
{
	auto const dest_size = ::MultiByteToWideChar(CP_ACP, 0U, src.data(), -1, nullptr, 0U);
	std::vector<wchar_t> dest(dest_size, L'\0');
	if (::MultiByteToWideChar(CP_ACP, 0U, src.data(), -1, dest.data(), (int)dest.size()) == 0) {
		throw std::system_error{static_cast<int>(::GetLastError()), std::system_category()};
	}
	dest.resize(std::char_traits<wchar_t>::length(dest.data()));
	dest.shrink_to_fit();
	return std::wstring(dest.begin(), dest.end());
}
std::string wide_to_multi_winapi(std::wstring const& src)
{
	auto const dest_size = ::WideCharToMultiByte(CP_ACP, 0U, src.data(), -1, nullptr, 0, nullptr, nullptr);
	std::vector<char> dest(dest_size, '\0');
	if (::WideCharToMultiByte(CP_ACP, 0U, src.data(), -1, dest.data(), (int)dest.size(), nullptr, nullptr) == 0) {
		throw std::system_error{static_cast<int>(::GetLastError()), std::system_category()};
	}
	dest.resize(std::char_traits<char>::length(dest.data()));
	dest.shrink_to_fit();
	return std::string(dest.begin(), dest.end());
}
std::wstring utf8_to_wide_winapi(std::string const& src)
{
	auto const dest_size = ::MultiByteToWideChar(CP_UTF8, 0U, src.data(), -1, nullptr, 0U);
	std::vector<wchar_t> dest(dest_size, L'\0');
	if (::MultiByteToWideChar(CP_UTF8, 0U, src.data(), -1, dest.data(), (int)dest.size()) == 0) {
		throw std::system_error{static_cast<int>(::GetLastError()), std::system_category()};
	}
	dest.resize(std::char_traits<wchar_t>::length(dest.data()));
	dest.shrink_to_fit();
	return std::wstring(dest.begin(), dest.end());
}
std::string wide_to_utf8_winapi(std::wstring const& src)
{
	auto const dest_size = ::WideCharToMultiByte(CP_UTF8, 0U, src.data(), -1, nullptr, 0, nullptr, nullptr);
	std::vector<char> dest(dest_size, '\0');
	if (::WideCharToMultiByte(CP_UTF8, 0U, src.data(), -1, dest.data(), (int)dest.size(), nullptr, nullptr) == 0) {
		throw std::system_error{static_cast<int>(::GetLastError()), std::system_category()};
	}
	dest.resize(std::char_traits<char>::length(dest.data()));
	dest.shrink_to_fit();
	return std::string(dest.begin(), dest.end());
}
std::string multi_to_utf8_winapi(std::string const& src)
{
	auto const wide = multi_to_wide_winapi(src);
	return wide_to_utf8_winapi(wide);
}
std::string utf8_to_multi_winapi(std::string const& src)
{
	auto const wide = utf8_to_wide_winapi(src);
	return wide_to_multi_winapi(wide);
}
// ******************************************************************
BOOL ConvUtf8toSJis( BYTE* pSource, BYTE* pDist, int* pSize )
{
   *pSize = 0;
 
   //UTF-8からUTF-16へ変換
   const int nSize = ::MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)pSource, -1, NULL, 0 );
 
   BYTE* buffUtf16 = new BYTE[ nSize * 2 + 2 ];
   ::MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)pSource, -1, (LPWSTR)buffUtf16, nSize );
 
   //UTF-16からShift-JISへ変換
   const int nSizeSJis = ::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)buffUtf16, -1, NULL, 0, NULL, NULL );
   if( !pDist ){
       *pSize = nSizeSJis;
       delete buffUtf16;
       return TRUE;
   }
 
   BYTE* buffSJis = new BYTE[ nSizeSJis * 2 ];
   ZeroMemory( buffSJis, nSizeSJis * 2 );
   ::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)buffUtf16, -1, (LPSTR)buffSJis, nSizeSJis, NULL, NULL );
 
   *pSize = lstrlen( (char*)buffSJis );
   memcpy( pDist, buffSJis, *pSize );
 
   delete buffUtf16;
   delete buffSJis;
 
   return TRUE;
}
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
POINT GetMousePos()
{
	POINT ret;
	ret.x = 0;
	ret.y = 0;
	if ((GetCursorPos(&ret) == 0))
	{
		ret.x = 0;
		ret.y = 0;
	}
	return ret;
}
std::string GetMousePosString()
{
	std::string ret;
	POINT  p = GetMousePos();
	ret = "({x:";
	ret += std::to_string(p.x);
	ret += ",y:";
	ret += std::to_string(p.y);
	ret += "})";
	return ret;
}
void SetMousePos(int x, int y)
{
	SetCursorPos(x, y);
}
void  BeepPlay(int v)
{
	UINT ch = MB_OK;
	switch (v)
	{
	case 1:ch = MB_OKCANCEL; break;
	case 2:ch = MB_ABORTRETRYIGNORE; break;
	case 3:ch = MB_YESNOCANCEL; break;
	case 4:ch = MB_YESNO; break;
	case 5:ch = MB_RETRYCANCEL; break;
	case 6:ch = MB_CANCELTRYCONTINUE; break;
	case 0:
	default:
		ch = MB_OK;
		break;
	}
	MessageBeep(ch);
}

BOOL PlayResource(HANDLE hInst, int id)
{

	BOOL bRtn;
	LPSTR lpRes;
	HANDLE hResInfo, hRes;

	// Find the WAVE resource. 

	char NUM[20];
	memset(NUM, '\0', 20);
	 sprintf_s(NUM,20,"#%d", 100 + id);

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
	else
		bRtn = 0;

	// Free the WAVE resource and return success or failure. 

	FreeResource(hRes);
	return bRtn;
}
BOOL PlayWave(LPSTR lpName)
{
	BOOL bRtn;


	bRtn = PlaySound(TEXT(lpName),  NULL, (SND_SYNC | SND_FILENAME| SND_NODEFAULT));
	return bRtn;
}

void PlayAESound(int v)
{

	switch (v)
	{
	case 1:
		PlayWave((LPSTR)(getNewBuffer( ae_sound_okay())));
		break;
	case 2:
		PlayWave((LPSTR)(getNewBuffer(ae_sound_snap())));
		break;
	case 0:
	default:
		PlayWave((LPSTR)(getNewBuffer(ae_sound_fail())));
		break;
	}

}
void SoundPlay(char * s)
{
	PlayWave((LPSTR)s);
}