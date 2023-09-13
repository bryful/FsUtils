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
#include "FsUtil.h"

class SequenceFile
{
private:
	std::string m_Dir = "";
	std::string m_Org = "";
	std::string m_Node = "";
	std::string m_Ext = "";
	std::vector<std::string> m_FrameList;
	int m_startFrame = 65536;
	int m_endFrame = 0;

public:
	BOOL empty()
	{
		return (m_Org.empty() && m_Node.empty() && m_Ext.empty());
	}
	std::string Dir() { return m_Dir; }
	std::string Org() { return m_Org; }
	std::string Node() { return m_Node; }
	std::string Frame() { return m_Frame; }
	std::string Name()
	{
		if (m_FrameList.size() > 0)
		{
			return m_Node + m_FrameList.at(0);
		}
		else {
			return m_Node;
		}
	}
	std::string FullName()
	{
		if (m_FrameList.size() > 0)
		{
			return CombinePath(m_dir, m_Node + m_FrameList.at(0)+ m_Ext);
		}
		else {
			return CombinePath(m_dir, m_Node + m_Ext);
		}
	}
	std::string CaptionName()
	{
		if (m_FrameList.size() > 0)
		{
			return m_Node + "[" + m_FrameList.begin() + "-" + m_FrameList.end() + "]" + m_Ext;
		}
		else {
			return m_Node + m_Ext;
		}
	}
	std::string Ext() { return m_Ext; }
	std::string Temp[4]{ "" , "", "", "" };
	void Clear()
	{
		m_Dir = "";
		m_Org = "";
		m_Node = "";
		m_Ext = "";
		m_FrameList.clear();
		m_startFrame = 65536;
		m_endFrame = 0;
	}
	BOOL Add(std::string p)
	{
		BOOL ret = false;
		Temp[0] = GetDir(p);
		Temp[1] = GetNameWithoutFrame(p);
		Temp[2] = GetFrame(p);
		Temp[3] = GetExt(p);
		if (empty())
		{
			ret = true;
		}
		else {
			if ((m_Dir == Temp[0]) && (m_Node == Temp[1]) && (ow[2]!="") && (m_Ext == Temp[3]))
			{
				ret = true;
			}
		}
		if (ret)
		{
			m_Dir = Temp[0];
			m_Node = Temp[1];
			m_FrameList.push_back(Temp[2]);
			m_Ext = Temp[3];
			if (Temp[2] != "") {
				int f = stoi(Temp[2]);
				if (m_startFrame > f)m_startFrame = f;
				if (m_endFrame < f)m_endFrame = f;
			}
		}
		return ret;
	}
	SequenceFile();
	SequenceFile(std::string s)
	{
		Clear();
		Add(s);
	}
	SequenceFile(std::string dir, std::string node, std::string frame, std::string ext )
	{
		SetValeu(dir, node, frame, ext);
	}
	SequenceFile(std::string s[])
	{
		SetValeu(s);
	}
	void SetValeu(std::string s)
	{
		Clear();
		Add(s);
	}
	void SetValeu(std::string s[])
	{
		if (s->size() >= 4)
		{
			m_Dir = s[0];
			m_Node = s[1];
			m_FrameList.push_back(s[2]);
			m_Ext = s[3];
			int f = stoi(s[2]);
			if (m_startFrame > f)m_startFrame = f;
			if (m_endFrame < f)m_endFrame = f;
		}
	}
	void SetValeu(std::string dir, std::string node, std::string frame, std::string ext)
	{
		m_Dir = dir;
		m_Node = node;
		m_FrameList.push_back(frame);
		m_Ext = ext;
		int f = stoi(frame);
		if (m_startFrame > f)m_startFrame = f;
		if (m_endFrame < f)m_endFrame = f;
	}

	std::string ToObjStr()
	{
		std::string isSwqStr = "false";
		if (m_FrameList.size() > 0) isSwqStr = "true";
		std::string lengthStr = std::to_string(m_FrameList.size());

		return "(" 
			+ "length:" + lengthStr + ","
			+ "isSequence:\"" + isSwqStr + "\","
			+ "caption:\"" + CaptionName() + "\","

			+ "file:new File(\"" + FullName() + "\")"
			+ ")";
	}
};