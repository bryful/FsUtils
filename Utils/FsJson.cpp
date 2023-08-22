#include "FsJson.h"


// ********************************************************************************************************
/*
	
*/
// ********************************************************************************************************
/*
* idxの位置から文字列ブロックなら最後のindexを返す。
*	"AAA\\bbb"
*	0123456789
	0なら9が返る
*/
bool IsStringBlock(string src, int idx,int* result)
{
	*result = -1;
	if ((idx < 0) || (idx >= src.size())) return false;
	char c = src[idx];
	if (c != '\"') return false;
	size_t cntMax = src.size();
	int index = idx+1;
	while (index < cntMax)
	{
		c = src[index];
		if (c == '\"')
		{
			if (index > idx)
			{
				if (src[index - 1] != '\\')
				{
					*result = index;
					return true;;
				}
			}
		}
		index++;
	}
	return false;
}
// ********************************************************************************************************
/*
* idxの位置から文字列ブロックなら最後のindexを返す。
*	"{AAA:1234"
*	0123456789
	5なら2が返る
*/
bool IsNameBlock(string src, int idx, int* result)
{
	*result = -1;
	if ((idx < 1) || (idx >= src.size())) return false;
	char c = src[idx];
	if (c != ':') return false;
	size_t cntMax = src.size();
	int index = idx - 1;
	int ret = -1;
	bool spFlag = false;
	while (index >= 0)
	{
		c = src[index];
		if ((c == ' ') || (c == '\t') || (c == '\r') || (c == '\n'))
		{
			if (spFlag == false)
			{
				index--;
				continue;
			}
			else {
				ret = index;
				break;
			}
		}
		if ((c == '{') || (c == '}') || (c == ','))
		{
			ret = index;
			break;
		}
		index--;
	}
	if (ret == -1) return ret;

	ret += 1;
	*result = ret;
	return true;

}
string FromAEJson(string src)
{
	string ret = "";
	if (src.empty() == true) return ret;
	size_t cntMax = src.size();
	int idx = 0;
	int idxtmp = -1;

	std::string block;
	while (idx < cntMax)
	{
		char c = src[idx];
		if (IsStringBlock(src, idx, &idxtmp) == true)
		{
			int ii = idx;
			if (block != "")
			{
				ret += block;
			}
			for (int i = ii; i <= idxtmp; i++)
			{
				block += src[i];
				idx++;
			}
		}
		else if (IsNameBlock(src,idx,&idxtmp) == true)
		{
			ret += "\"" + block+ "\":";
			block = "";
			idx++;
		}
		else if ((c == '(') && (idx + 1 < cntMax) && (src[idx + 1] == '{'))
		{
			ret += "{";
			idx++;
			idx++;
		}
		else if ((c == '}') && (idx + 1 < cntMax) && (src[idx + 1] == ')'))
		{
			ret += "}";
			idx++;
			idx++;
		}
		else if ((c == ',')|| (c == '[') || (c == ']'))
		{
			ret += block;
			block = "";
			ret += c;
			idx++;
		}
		else {
			if ((c != ' ') && (c != '\t') && (c != '\r') && (c != '\n'))
			{
				block += c;
			}
			idx++;
		}

	}



	return ret;
}
string ToAEJson(string src)
{
	string ret = "";
	if (src.empty() == true) return ret;
	size_t cntMax = src.size();
	int idx = 0;
	int idxtmp = -1;

	std::string block;
	while (idx < cntMax)
	{
		char c = src[idx];
		if (IsStringBlock(src, idx, &idxtmp) == true)
		{
			if (block.empty() == false)
			{
				ret += block;
				block = "";
			}
			int ii = idx;
			for (int i = ii; i <= idxtmp; i++)
			{
				block += src[i];
				idx++;
			}
		}
		else if (c==':')
		{
			if (block.size() >= 2) {
				if (block[0] == '\"')
				{
					block = block.substr(1);
				}
				if (block[block.size() - 1] == '\"')
				{
					block = block.substr(0, block.size() - 1);
				}
			}
			ret += block + ":";
			block = "";
			idx++;
		}
		else if (c == '{')
		{
			ret += "({";
			idx++;
		}
		else if (c == '}')
		{
			ret += "})";
			idx++;
		}
		else if ((c == ',') || (c == '[') || (c == ']'))
		{
			ret += block;
			block = "";
			ret += c;
			idx++;
		}
		else {
			if ((c != ' ') && (c != '\t') && (c != '\r') && (c != '\n'))
			{
				block += c;
			}
			idx++;
		}

	}



	return ret;
}