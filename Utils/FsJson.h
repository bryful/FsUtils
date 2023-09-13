#pragma once

#define WINDOWS_IGNORE_PACKING_MISMATCH
#include "FsUtil.h"

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
#include <nlohmann/json.hpp>

using string = std::string;
using json = nlohmann::json;
// *********************************************************************************************
string FromAEJson(string src);
string ToAEJson(string src);
// *********************************************************************************************

class FsJson
{
private:
	json Obj;
public:
	BOOL IsShiftJis = true;
	FsJson(BOOL isSHiftJis = true)
	{
		IsShiftJis = isSHiftJis;

		Obj = json::object();
	}
	std::vector<std::string> Keys()
	{
		std::vector<std::string> ret;
		for (auto& el : Obj.items()) 
		{
			ret.push_back(el.key());
		}
		return ret;
	}
	// *************************************
	void SetValue(string key, int v)
	{
		Obj[key] = (double)v;
	}
	BOOL Value(string key, int& v)
	{
		BOOL ret = false;
		if (Obj.find(key) != Obj.end())
		{
			if (Obj[key].is_number())
			{
				v = (int)Obj[key].get<double>();
				ret = true;
			}
		}
		return ret;
	}
	// *************************************
	void SetValue(string key, std::vector<int> v)
	{
		json ja = json::array();
		if (v.size() > 0)
		{
			for each (int vv in v)
			{
				ja.push_back((double)vv);
			}
		}
		Obj[key] = ja;
	}
	BOOL Value(string key, std::vector<int>& v)
	{
		BOOL ret = false;
		v.clear();
		if (Obj.find(key) != Obj.end())
		{
			if (Obj[key].is_array())
			{
				json ja = Obj[key];
				if (ja.size() > 0)
				{
					for each (auto j in ja)
					{
						if (j.is_number())
						{
							v.push_back((int)j.get<double>());
						}
					}
				}
				ret = true;
			}
		}
		return ret;
	}
	// *************************************
	void SetValue(string key, double v)
	{
		Obj[key] = v;
	}
	BOOL Value(string key, double& v)
	{
		BOOL ret = false;
		if (Obj.find(key) != Obj.end())
		{
			if (Obj[key].is_number())
			{
				v = Obj[key].get<double>();
				ret = true;
			}
		}
		return ret;
	}
	// *************************************
	void SetValue(string key, std::vector<double> v)
	{
		json ja = json::array();
		if (v.size() > 0)
		{
			for each (double vv in v)
			{
				ja.push_back(vv);
			}
		}
		Obj[key] = ja;
	}
	BOOL Value(string key, std::vector<double>& v)
	{
		BOOL ret = false;
		v.clear();
		if (Obj.find(key) != Obj.end())
		{
			if (Obj[key].is_array())
			{
				json ja = Obj[key];
				if (ja.size() > 0)
				{
					for each (auto j in ja)
					{
						if (j.is_number())
						{
							v.push_back(j.get<double>());
						}
					}
				}
				ret = true;
			}
		}
		return ret;
	}
	// *************************************
	void SetValue(string key, bool v)
	{
		Obj[key] = v;
	}
	BOOL Value(string key, bool& v)
	{
		BOOL ret = false;
		if (Obj.find(key) != Obj.end())
		{
			if (Obj[key].is_boolean())
			{
				v = Obj[key].get<bool>();
				ret = true;
			}
		}
		return ret;
	}
	// *************************************
	void SetValue(string key, std::vector<bool> v)
	{
		json ja = json::array();
		if (v.size() > 0)
		{
			for each (bool vv in v)
			{
				ja.push_back(vv);
			}
		}
		Obj[key] = ja;
	}
	BOOL Value(string key, std::vector<bool>& v)
	{
		BOOL ret = false;
		v.clear();
		if (Obj.find(key) != Obj.end())
		{
			if (Obj[key].is_array())
			{
				json ja = Obj[key];
				if (ja.size() > 0)
				{
					for each (auto j in ja)
					{
						if (j.is_boolean())
						{
							v.push_back(j.get<bool>());
						}
					}
				}
				ret = true;
			}
		}
		return ret;
	}
	// *************************************
	void SetValue(string key, string v)
	{
		if (IsShiftJis) {
			Obj[key] = string(ShiftJistoUtf8((char*)v.c_str()));
		}else{
			Obj[key] = v;
		}
	}
	BOOL Value(string key, string& v)
	{
		BOOL ret = false;
		if (Obj.find(key) != Obj.end())
		{
			if (Obj[key].is_string())
			{
				v = Obj[key].get<string>();
				if (IsShiftJis)
				{
					v = string(Utf8toShiftJis((char*)v.c_str()));
				}
				ret = true;
			}
		}
		return ret;
	}
	// *************************************
	void SetValue(string key, std::vector<string> v)
	{
		json ja = json::array();
		if (v.size() > 0)
		{
			for each (string vv in v)
			{
				if (IsShiftJis)
				{
					vv = string(ShiftJistoUtf8((char*)vv.c_str()));
				}
				ja.push_back(vv);
			}
		}
		Obj[key] = ja;
	}
	// *************************************
	BOOL Value(string key, std::vector<string>& v)
	{
		BOOL ret = false;
		v.clear();
		if (Obj.find(key) != Obj.end())
		{
			if (Obj[key].is_array())
			{
				json ja = Obj[key];
				if (ja.size() > 0)
				{
					for each (auto j in ja)
					{
						if (j.is_string())
						{
							string s = j.get<string>();
							if (IsShiftJis)
							{
								s = string(Utf8toShiftJis((char*)s.c_str()));
							}
							v.push_back(s);
						}
					}
				}
				ret = true;
			}
		}
		return ret;
	}
	// *************************************
	// *************************************
	string ToJson()
	{
		string s = Obj.dump();
		if (IsShiftJis)
		{
			s = string(Utf8toShiftJis((char*)s.c_str()));
		}
		return s;
	}
	// *************************************
	BOOL Save(string p)
	{
		BOOL ret = false;
		if (ExistFile(p)) DeleteFile(p.c_str());
		std::ofstream writing_file;
		writing_file.open(p, std::ios::app);
		writing_file << ToJson() << std::endl;
		ret = ExistFile(p);
		writing_file.close();
		return ret;
	}
};
// *********************************************************************************************
