#include "FsUtil.h"

// ******************************************************************
char* getNewBuffer(std::string s)
{
	char* buff = new char[1 + s.size()];
	memset(buff, 0, s.size() + 1);
	lstrcpy(buff, s.c_str());

	return buff;
}
char* getNewBuffer(char* s)
{
	const auto length = strlen(s) + 1;
	char* str = new char[1 + strlen(s)];
	lstrcpy(str, s);
	return str;
}

std::string getNewString(char* s)
{
	const auto length = strlen(s) + 1;
	char* str = new char[1 + strlen(s)];
	lstrcpy(str, s);
	return std::string(str);
}


// ******************************************************************
std::string ReplaceAll(std::string& stringreplace, const std::string& origin, const std::string& dest)
{
	size_t pos = 0;
	size_t offset = 0;
	size_t len = origin.length();
	while ((pos = stringreplace.find(origin, offset)) != std::string::npos) {
		stringreplace.replace(pos, len, dest);
		offset = pos + dest.length();
	}
	return stringreplace;
}
std::vector<std::string> Split(const std::string& s, const std::string& delim)
{

	std::vector<std::string> result;
	result.clear();
	using string = std::string;
	string::size_type pos = 0;

	while (pos != string::npos)
	{
		string::size_type p = s.find(delim, pos);

		if (p == string::npos)
		{
			result.push_back(s.substr(pos));
			break;
		}
		else {
			result.push_back(s.substr(pos, p - pos));
		}

		pos = p + delim.size();
	}
	return result;
}
std::string Join(const std::vector<std::string>& v, std::string delim) {
	std::string s;
	if (!v.empty()) {
		s += v[0];
		for (decltype(v.size()) i = 1, c = v.size(); i < c; ++i) {
			if (delim.empty()==false) s += delim;
			s += v[i];
		}
	}
	return s;
}
std::string Trim(const std::string& string)

{
	const char* trimCharacterList = " \t\v\r\n";
	std::string result;
	std::string::size_type left = string.find_first_not_of(trimCharacterList);
	if (left != std::string::npos)
	{
		std::string::size_type right = string.find_last_not_of(trimCharacterList);
		result = string.substr(left, right - left + 1);
	}
	return result;

}
std::string TrimTailSepa(const std::string& string)

{
	const char* trimCharacterList = " \\/";
	std::string result;
	//aaa00
	//01234
	std::string::size_type right = string.find_last_not_of(trimCharacterList);
	result = string.substr(0, right+1);
	return result;

}
std::string TrimHeadSepa(const std::string& string)

{
	const char* trimCharacterList = " \\/";
	std::string result;
	//aaa00
	//01234
	std::string::size_type left = string.find_first_not_of(trimCharacterList);
	result = string.substr(left);
	return result;

}
std::vector<std::string> CammaSplit(const std::string& s)
{

	std::vector<std::string> result;
	result.clear();
	int cnt = s.size();
	if (cnt <= 0) return result;
	std::string block =  "";

	int idx = 0;
	while (idx<cnt)
	{
		std::string c = s.substr(idx,1);
		if (c == "\"")
		{
			int idx2 = -1;
			for (int i = idx + 1; i < cnt; i++)
			{
				std::string c2 = s.substr(i, 1);
				if (c2 == "\"")
				{
					if (s[i-1]=='\\') continue;
					idx2 = i;
					break;
				}
			}
			//   "000000"
			//   01234567
			if (idx2 > 0)
			{
				block += s.substr(idx, idx2 - idx + 1);
				idx = idx2+1;
			}
			else {
				block += s.substr(idx);
				idx = cnt;
			}
		}else if (c == ",")
		{
			result.push_back(block);
			block = "";
			idx++;
		}
		else {
			block += c;
			idx++;

		}
	}
	if (block.empty()==false) result.push_back(block);
	return result;
}
std::string ToLowwer(std::string s)
{
	if (s.size() <= 0) return std::string("");
	transform(s.begin(), s.end(), s.begin(), tolower);
	return s;
}
std::string ToUpper(std::string s)
{
	if (s.size() <= 0) return std::string("");
	transform(s.begin(), s.end(), s.begin(), toupper);
	return s;
}
// ******************************************************************
BOOL SetTextClipboard(LPCTSTR lpString,bool IsU)
{
    if (!OpenClipboard(NULL)) return false;
	LPTSTR c;
	if (IsU) {
		c = Utf8toShiftJis((LPTSTR)lpString);
	}
	else {
		c = (LPTSTR)lpString;
	}

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
// ******************************************************************
BOOL SetTextClipboard(std::string str, bool IsU)
{
	return SetTextClipboard((LPCTSTR)str.c_str(), IsU);
}
LPCTSTR GetTextClipboard(bool IsU)
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
		if (IsU)
		{
			strText = ShiftJistoUtf8(strText);
		}
	}
    return strText;
}
std::string GetTextClipboardStr(bool IsU)
{
	
	return std::string(GetTextClipboard(IsU));
}
// ******************************************************************
// ******************************************************************
/*
https://nekko1119.hatenablog.com/entry/2017/01/02/054629
Visual C++における文字コード変換
*/
std::wstring utf8_to_wide_winapi(std::string const& src)
{
	auto const dest_size = ::MultiByteToWideChar(CP_UTF8, 0U, src.data(), -1, nullptr, 0U);
	std::vector<wchar_t> dest(dest_size, L'\0');
	if (::MultiByteToWideChar(CP_UTF8, 0U, src.data(), -1, dest.data(), dest.size()) == 0) {
		throw std::system_error{static_cast<int>(::GetLastError()), std::system_category()};
	}
	dest.resize(std::char_traits<wchar_t>::length(dest.data()));
	dest.shrink_to_fit();
	return std::wstring(dest.begin(), dest.end());
}
std::wstring multi_to_wide_winapi(std::string const& src)
{
	auto const dest_size = ::MultiByteToWideChar(CP_ACP, 0U, src.data(), -1, nullptr, 0U);
	std::vector<wchar_t> dest(dest_size, L'\0');
	if (::MultiByteToWideChar(CP_ACP, 0U, src.data(), -1, dest.data(), dest.size()) == 0) {
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
	if (::WideCharToMultiByte(CP_UTF8, 0U, src.data(), -1, dest.data(), dest.size(), nullptr, nullptr) == 0) {
		throw std::system_error{static_cast<int>(::GetLastError()), std::system_category()};
	}
	dest.resize(std::char_traits<char>::length(dest.data()));
	dest.shrink_to_fit();
	return std::string(dest.begin(), dest.end());
}
std::string wide_to_multi_winapi(std::wstring const& src)
{
	auto const dest_size = ::WideCharToMultiByte(CP_ACP, 0U, src.data(), -1, nullptr, 0, nullptr, nullptr);
	std::vector<char> dest(dest_size, '\0');
	if (::WideCharToMultiByte(CP_ACP, 0U, src.data(), -1, dest.data(), dest.size(), nullptr, nullptr) == 0) {
		throw std::system_error{static_cast<int>(::GetLastError()), std::system_category()};
	}
	dest.resize(std::char_traits<char>::length(dest.data()));
	dest.shrink_to_fit();
	return std::string(dest.begin(), dest.end());
}
// ******************************************************************
std::string multi_to_utf8_winapi(std::string const& src)
{
	auto const wide = multi_to_wide_winapi(src);
	return wide_to_utf8_winapi(wide);
}
// ******************************************************************
std::string utf8_to_multi_winapi(std::string const& src)
{
	auto const wide = utf8_to_wide_winapi(src);
	return wide_to_multi_winapi(wide);
}
// ******************************************************************
// ******************************************************************
/*
http://www.lab.its55.com/?p=32
C++でShift-JISをUTF-8に変換する
*/
BOOL ConvSJistoUtf8(char* pSource, char* pDist, int* pSize)
{
	*pSize = 0;

	//ShiftJISからUTF-16へ変換
	const int nSize = ::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)
		pSource, -1, NULL, 0);

	char* buffUtf16 = new char[nSize * 2 + 2];
	::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pSource, -1, (LPWSTR)
		buffUtf16, nSize);

	//UTF-16からShift-JISへ変換
	const int nSizeUtf8 = ::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)
		buffUtf16, -1, NULL, 0, NULL, NULL);
	if (!pDist) {
		*pSize = nSizeUtf8;
		delete buffUtf16;
		return TRUE;
	}

	char* buffUtf8 = new char[nSizeUtf8 * 2];
	ZeroMemory(buffUtf8, nSizeUtf8 * 2);
	::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)buffUtf16, -1, (LPSTR)
		buffUtf8, nSizeUtf8, NULL, NULL);

	*pSize = lstrlen((char*)buffUtf8);
	memcpy(pDist, buffUtf8, *pSize);

	delete buffUtf16;
	delete buffUtf8;

	return TRUE;
}
char* ShiftJistoUtf8(char* src)
{
	int nSize = 0;
	ConvSJistoUtf8(src, NULL, &nSize);
	char* dst = new char[nSize + 1];
	ZeroMemory(dst, nSize + 1);
	ConvSJistoUtf8(src, dst, &nSize);
	return dst;
}
// ******************************************************************
/*
http://www.lab.its55.com/?p=33
C++でUTF-8をShift-JISに変換する
*/

BOOL ConvUtf8toSJis(char* pSource, char* pDist, int* pSize)
{
	*pSize = 0;

	//UTF-8からUTF-16へ変換
	const int nSize = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pSource, -1, NULL, 0);

	char* buffUtf16 = new char[nSize * 2 + 2];
	::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pSource, -1, (LPWSTR)buffUtf16, nSize);

	//UTF-16からShift-JISへ変換
	const int nSizeSJis = ::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)buffUtf16, -1, NULL, 0, NULL, NULL);
	if (!pDist) {
		*pSize = nSizeSJis;
		delete buffUtf16;
		return TRUE;
	}

	char* buffSJis = new char[nSizeSJis * 2];
	ZeroMemory(buffSJis, nSizeSJis * 2);
	::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)buffUtf16, -1, (LPSTR)buffSJis, nSizeSJis, NULL, NULL);

	*pSize = lstrlen((char*)buffSJis);
	memcpy(pDist, buffSJis, *pSize);

	delete buffUtf16;
	delete buffSJis;

	return TRUE;
}
// ******************************************************************

char* Utf8toShiftJis(char* src)
{
	int nSize = 0;
	ConvUtf8toSJis(src, NULL, &nSize);
	char* dst = new char[nSize + 1];
	ZeroMemory(dst, nSize + 1);

	ConvUtf8toSJis(src, dst, &nSize);
	return dst;

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

BOOL PlayBeep(std::string dir, std::string num)
{
	std::string cmd = "\"" + CombinePath(dir, "beep.exe") + "\"";
	std::string arg = "res " + num;

	CallCommand(cmd,arg);
	return true;

}
BOOL PlayWave(std::string dir, std::string name)
{
	std::string cmd = "\"" + CombinePath(dir, "beep.exe") + "\"";
	std::string arg = "file ";
	arg += "\"" + name + "\"";
	
	CallCommand(cmd,arg);
	return true;
}

void PlayAESound(std::string dir, int v)
{

	switch (v)
	{
	case 1:
		PlayWave(dir, ae_sound_okay());
		break;
	case 2:
		PlayWave(dir, ae_sound_snap());
		break;
	case 0:
	default:
		PlayWave(dir, ae_sound_fail());
		break;
	}

}

// **********************************************************************************
bool IsModifierKey(int v)
{
	if ((GetAsyncKeyState(v)& 1) )
	{
		return true;
	}
	else {
		return false;
	}
}
bool IsControlCKey()
{
	bool ret = false;
	if (GetAsyncKeyState(VK_CONTROL) & 1)
	{
		ret = (GetAsyncKeyState('C') & 1);
	}
	return ret;
}
bool IsModifierKey(char * key)
{
	std::string k = std::string(getNewBuffer(key));
	if (k.empty() == true) return false;
	transform(k.begin(), k.end(), k.begin(), tolower);

	if (k.compare(std::string("lbutton")) == 0)
	{
		return IsModifierKey(VK_LBUTTON);
	}
	else if (k.compare(std::string("rbutton")) == 0)
	{
		return IsModifierKey(VK_RBUTTON);
	}
	else if (k.compare(std::string("mbutton")) == 0)
	{
		return IsModifierKey(VK_MBUTTON);
	}
	else if (k.compare(std::string("back")) == 0)
	{
		return IsModifierKey(VK_BACK);
	}
	else if (k.compare(std::string("tab")) == 0)
	{
		return IsModifierKey(VK_TAB);
	}
	else if (k.compare(std::string("help")) == 0)
	{
		return IsModifierKey(VK_HELP);
	}
	else if (k.compare(std::string("shift")) == 0)
	{
		return IsModifierKey(VK_SHIFT);
	}
	else if (k.compare(std::string("control")) == 0)
	{
		return IsModifierKey(VK_CONTROL);
	}
	else if (k.compare(std::string("alt")) == 0)
	{
		return IsModifierKey(VK_MENU);
	}
	else if (k.compare(std::string("escape")) == 0)
	{
		return IsModifierKey(VK_ESCAPE);
	}
	else if (k.compare(std::string("space")) == 0)
	{
		return IsModifierKey(VK_SPACE);
	}
	else if (k.compare(std::string("left")) == 0)
	{
		return IsModifierKey(VK_LEFT);
	}
	else if (k.compare(std::string("right")) == 0)
	{
		return IsModifierKey(VK_RIGHT);
	}
	else if (k.compare(std::string("up")) == 0)
	{
		return IsModifierKey(VK_UP);
	}
	else if (k.compare(std::string("down")) == 0)
	{
		return IsModifierKey(VK_DOWN);
	}
	else {
		char c = k[0];
		if (((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'z')))
		{
			return IsModifierKey((int)c);
		}
	}


	return false;
}

bool IsShiftKey()
{
	return IsModifierKey(VK_SHIFT);
}
bool IsControlKey()
{
	return IsModifierKey(VK_CONTROL);
}
bool IsAltKey()
{
	return IsModifierKey(VK_MENU);
}
std::string get_env(const char* environment_name)
{
	std::string ret = "";
	DWORD buf = GetEnvironmentVariable(environment_name, nullptr,0);
	if (buf == 0) return ret;
	std::string buffer;
	buffer.resize(buf + 1);//reserve

	GetEnvironmentVariable(environment_name , &buffer[0], buffer.size() );

	buffer = std::string(ShiftJistoUtf8((char*)buffer.c_str()));
	
	ReplaceAll(buffer, "%3D", "=");
	ReplaceAll(buffer, "//r", "/r");
	ReplaceAll(buffer, "//n", "/n");
	ReplaceAll(buffer, "//t", "/t");
	//ReplaceAll(buffer, "///"", "/"");
	ReplaceAll(buffer, "//", "////");

	buffer.resize(std::strlen(buffer.c_str()));//resize
	return buffer;
}
bool set_env(const char* environment_name,std::string v)
{
	bool ret = false;
	if (v.empty()==false) {
		ReplaceAll(v, "=", "%3D");
		ReplaceAll(v, "/r", "//r");
		ReplaceAll(v, "/n", "//n");
		ReplaceAll(v, "/t", "//t");
		//ReplaceAll(v, "///"", "/"");
		ReplaceAll(v, "////", "//");
		if (SetEnvironmentVariable(environment_name, v.c_str()) != 0)
		{
			ret = true;
		}
	}
	else {
		if (SetEnvironmentVariable(environment_name, nullptr) != 0)
		{
			ret = true;
		}

	}
	return ret;
}

BOOL IsUTF8(char* bytes)
{
	int len = strlen(bytes);
	if (len < 2) {
		// 短すぎると判別不可能、Shift-jis とみなすことにする
		return false;
	}
	else if ((bytes[0] == 0xEF) && (bytes[1] == 0xBB) && (bytes[2] == 0xBF)) {
		// BOM 付き UTF-8
		return true;
	}
	int sjis = 0;
	for (int i = 0; i < len - 2; i++) {
		char b1 = bytes[i];
		char b2 = bytes[i + 1];
		if (((0x81 <= b1 && b1 <= 0x9F) || (0xE0 <= b1 && b1 <= 0xFC)) &&
			((0x40 <= b2 && b2 <= 0x7E) || (0x80 <= b2 && b2 <= 0xFC))) {
			sjis += 2;
			i++;
		}
	}
	int utf8 = 0;
	for (int i = 0; i < len - 2; i++) {
		int b1 = bytes[i];
		int b2 = bytes[i + 1];
		if ((0xC0 <= b1 && b1 <= 0xDF) &&
			(0x80 <= b2 && b2 <= 0xBF)) {
			utf8 += 2;
			i++;
		}
		else if (i < len - 2) {
			int b3 = bytes[i + 2];
			if ((0xE0 <= b1 && b1 <= 0xEF) &&
				(0x80 <= b2 && b2 <= 0xBF) &&
				(0x80 <= b3 && b3 <= 0xBF)) {
				utf8 += 3;
				i += 2;
			}
		}
	}
	if (sjis > utf8) {
		return false;
	}
	else if (utf8 > sjis) {
		return true;
	}
	else {
		return false;
	}
}
BOOL IsUTF8(std::string s) { return IsUTF8((char*)s.c_str()); }

// *******************************************************************
std::string LoginUserName()
{
	std::string ret = "";
	TCHAR user[1024];
	DWORD dwUserSize; // 取得したユーザ名の文字列の長さ
	if (GetUserName(user, &dwUserSize)) {

		ret = std::string(user);
	}
	return ret;
}
std::string ComputerName()
{
	std::string ret = "";
	TCHAR buf[1024];
	DWORD dwSize; // 取得したユーザ名の文字列の長さ
	if (GetComputerName(buf, &dwSize))
	{
		ret = std::string(buf);
	}
	return ret;
}
