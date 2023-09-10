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
#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "FsUtil.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;




class CmdArgItem
{
private:
	int m_Index = -1;
public:
	int(*CmdExec)(std::vector<std::string> op)  = nullptr;
	int exec()
	{
		int ret = 0;
		if (CmdExec != nullptr)
		{
			ret = CmdExec(options);
		}
		return ret;
	}
	int Index() { return m_Index; }
	std::vector<std::string> Keys;
	int argc = 0;
	std::string Comment;
	std::vector<std::string> options;
	CmdArgItem( std::vector<std::string> ks, int c, std::string com)
	{
		Keys = ks;
		argc = c;
		Comment = com;
	}
	void SetIndex(int idx)
	{
		m_Index = idx;
	}
};

class CmdArg
{
private:
	json jobj;
public:
	std::vector<CmdArgItem> Options;

	std::string ToJson()
	{
		return jobj.dump();
	}
	// ***********************************************************
	void SetArg(int c, char* vs[])
	{
		jobj.clear();
		if (c > 0)
		{
			jobj["path"] = vs[0];
		}
		if (c > 1)
		{
			json n = json::array();
			int idx = 1;
			while (idx < c)
			{
				std::string vv = std::string(vs[idx]);
				BOOL b = ((vv[0] == '-') || (vv[0] == '/'));
				if (b == false)
				{
					n.push_back(vv);
					idx++;
					continue;
				}
				std::string k = ToLowwer(vv.substr(1));
				json aj = json::array();
				idx++;
				while (idx < c)
				{
					vv = std::string(vs[idx]);
					BOOL b2 = ((vv[0] == '-') || (vv[0] == '/'));
					if (b2) break;
					aj.push_back(vv);
					idx++;
				}
				jobj[k] = aj;
			}
			jobj["none"] = n;
		}
	}
	// ***********************************************************
	//
	CmdArg()
	{
	}
	CmdArg(int c, char* vs[])
	{
		SetArg(c, vs);
	}

	// ***********************************************************
	std::vector<std::string> FindArg(std::vector<std::string> Keys)
	{
		std::vector<std::string> ret;
		
		if (Keys.size() <= 0) return ret;

		for (int i = 0; i < Keys.size();i++)
		{
			if (jobj.find(Keys[i]) != jobj.end())
			{
				ret.push_back(Keys[0]);
				for (auto& element : jobj[Keys[i]])
				{
					ret.push_back(element.get<std::string>());
				}
			}
		}
		return ret;
	}
	// ***********************************************************
	CmdArgItem AddOption(CmdArgItem ai)
	{
		ai.SetIndex(Options.size());
		Options.push_back(ai);
		return ai;
	}
	// ***********************************************************
	CmdArgItem AddOption(std::vector<std::string> k,int count,std::string com)
	{
		CmdArgItem ai(k, count, com);
		ai.SetIndex(Options.size());
		Options.push_back(ai);
		return ai;
	}
	// ***********************************************************
	std::string  OptionList()
	{
		std::string ret = "";
		if (Options.size() <= 0) return ret;
		for each (CmdArgItem itm in Options)
		{
			std::string line = "";

			for each (std::string ss in itm.Keys)
			{
				if (line.empty() == false) line += " or ";
				line += "-" + ss;
			}
			if (itm.argc > 0)
			{
				std::string cc = "";
				for (int i = 0; i < itm.argc; i++)
				{
					cc += " <arg" + std::to_string(i) + ">";
				}
				line += cc;
			}
			ret += "  *" + itm.Comment + "\n";
			ret += "    " + line + "\n";

		}
		return ret;
	}
	// ***********************************************************
	std::vector<CmdArgItem> GetOptions()
	{
		std::vector<CmdArgItem> ret;

		std::vector<std::string> vvn = FindArg({"none"});
		if (vvn.size() > 1)
		{
			CmdArgItem  aa({ "none" }, 0, "");
			vvn.erase(vvn.begin());
			aa.options = vvn;
			ret.push_back(aa);
		}

		if (Options.size() > 0)
		{
			for each (CmdArgItem ai in Options)
			{
				std::vector<std::string> vv = FindArg(ai.Keys);
				if (vv.size() > 0)
				{
					vv.erase(vv.begin());
					if (ai.argc <= vv.size())
					{
						ai.options = vv;
						ret.push_back(ai);
					}
				}
			}
		}
		return ret;
	}

	int Exec()
	{
		std::vector<CmdArgItem> list = GetOptions();
		if (list.size() > 0)
		{
			for each (CmdArgItem ai in list)
			{
				return ai.exec();
			}
		}
		return 0;
	}

};


