#pragma once
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
#include <Shlwapi.h>
#include <iostream>
#include <regex>


class SequenceFile
{
private:
	bool m_IsJSPath = false;
	bool m_IsSequenceStyle = false;
	std::string m_Dir;
	std::string m_Org;
	std::string m_Node;
	std::string m_Frame;
	std::string m_Ext;
	bool IsNum(char c) { return ((s[i] >= '0') && (s[i] <= '9')); }
	int LastIndexOfFrame(std::string s)
	{
		int ret = -1;
		int sz = s.size();
		if (sz<=0) return ret;
		int idx = -1;
		for (int i = sz - 1; i >= 0; i--)
		{
			if (IsNum(s[i])==false)
			{
				idx = i;
				break;
			}
		}
		if (idx == sz - 1)
		{
			if (s[sz - 1] == ']')
			{
				int idx1 = s.find_last_of("[",);
				if (idx1 != std::string::npos)
				{
					std::string ss = s.substr(idx1+1,s.size()-2);
				}
			}
			// êîéöñ≥Çµ
			ret = -1;
		}
		else
		{
			ret = idx + 1;
		}
		return ret;
	}
public:
	std::string Dir() { return m_Dir; }
	std::string Org() { return m_Org; }
	std::string Node() { return m_Node; }
	std::string Frame() { return m_Frame; }
	std::string Ext() { return m_Ext; }
	void Clear()
	{
		m_IsJSPath = false;
		m_IsSequenceStyle = false;
		m_Dir = "";
		m_Org = "";
		m_Node = "";
		m_Frame = "";
		m_Ext = "";

	}
	void SetFileName(std::string p)
	{

		if (std::regex_match(s, m, std::regex(R"([^[\\|/}]+?)?$") {
		}

		// C:\\aaa\\bbb.txt
		// 0123456789ABCDEF
		// /c/aaa/bbb.txt
		// 0123456789ABCDEF
		Clear();
		if (p.empty() == true) return;
		int path_i = p.find_last_of("\\");
		if (path_i == std::string::npos)
		{
			path_i = p.find_last_of("/");
			if (path_i != std::string::npos) m_IsJSPath = true;
		}
		std::string n="";
		if (path_i != std::string::npos)
		{
			m_Dir = p.substr(0, path_i);
			n = p.substr(path_i);
		}
		else {
			n = p;
		}
		int ext_i = n.find_last_of(".");
		if (ext_i != std::string::npos)
		{
			m_Ext = n.substr(ext_i);
			n = n.substr(0,ext_i);
			if (n.empty() == false)
			{
				int idx = LastIndexOfFrame(n);
				if (idx < 0)
				{
					m_Node = n;
				}
				else {
					m_Node = n.substr(0, idx);
					m_Frame = n.substr(idx);
				}

			}
		}
		else {
			m_Node = n;
		}
	}

	SequenceFile()
	{

	}
};