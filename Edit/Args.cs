using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LineEdit
{
	public class ArgItem
	{
		private int _Index = -1;
		public int Index { get { return Index; } }
		private string _Text = "";
		public string Text { get { return _Text; } }
		private string _Option = "";
		public string Option { get { return _Option; } }

		private bool m_IsOption = false;
		public bool IsOption { get { return m_IsOption; } }
		public string[] Cmd = new string[0];

		public ArgItem(string s,int idx)
		{
			_Text = s.Trim();
			_Index = idx;
			if (_Text.Length > 0)
			{
				m_IsOption = ((_Text[0] == '-') || (_Text[0] == '/'));
				if (m_IsOption)
				{
					_Option = _Text.Substring(1);
				}
			}
		}
		public bool MatchOption(string key)
		{
			if (m_IsOption==true)
			{
				return (string.Compare(_Option, key, true) == 0);
			}
			else
			{
				return false;
			}
		}

	}

	public class Args
	{
		public int Count { get { return _args.Length; } }
		public int OptionCount { get { return _OptionTable.Length; } }
		public int CmdCount { get { return _args.Length - _OptionTable.Length; } }

		private ArgItem[] _args = new ArgItem[0];
		public ArgItem[] Items { get { return _args; } }
		private int [] _OptionTable = new int[0];
		public int[] OptionTable { get { return _OptionTable; } }
		public ArgItem[] Options
		{
			get
			{
				if (_OptionTable.Length <= 0) return new ArgItem[0];
				ArgItem[] ret = new ArgItem[_OptionTable.Length];
				for (int i=0; i<_OptionTable.Length; i++)
				{
					ret[i] = _args[_OptionTable[i]];
				}
				return ret;
			}
		}

		// ******************************************
		public ArgItem? this[int idx]
		{
			get
			{
				if ((idx >= 0) && (idx < _args.Length))
				{
					return _args[idx];
				}
				else
				{
					return null;
				}
			}

		}
		// ******************************************
		public Args()
		{

		}
		// ******************************************
		public Args(string[] sa)
		{
			SetArgs(sa);
		}
		// ******************************************
		public void SetArgs(string[] sa)
		{
			List<ArgItem> list = new List<ArgItem>();
			List<int> optlist = new List<int>();
			if (sa.Length > 0)
			{
				int cnt = 0;
				for (int i = 0; i < sa.Length; i++)
				{
					if (sa[i] != "")
					{
						ArgItem arg = new ArgItem(sa[i],i);
						list.Add(arg);
						if (arg.IsOption) optlist.Add(cnt);
						cnt++;
					}
				}
			}
			_OptionTable = optlist.ToArray();
			_args = list.ToArray();

		}
		// ******************************************
		public new string ToString()
		{
			string ret = "";
			if (_args.Length > 0)
			{
				foreach (ArgItem a in _args)
				{

					if (ret != "") ret += ",";
					ret += a.Text;
				}
			}
			return ret;
		}
		public ArgItem? FindOption(string [] keys)
		{
			ArgItem? ret = null;
			if (_args.Length<=0) return ret;
			if (keys.Length<=0) return ret;
			foreach(ArgItem a in _args)
			{
				foreach (string key in keys)
				{
					if (ret != null) break;
					if (a.MatchOption(key))
					{
						ret = a;
						break;
					}
				}
				if (ret != null) break;
			}
			return ret;
		}

		public ArgItem[]ItemsWithoutOptin()
		{
			List<ArgItem> list = new List<ArgItem>();
			if (_args.Length>0)
			{
				foreach(ArgItem a in _args)
				{
					if (a.IsOption==false)
					{
						list.Add(a);
					}
				}
			}
			return list.ToArray();
		}
		public string[] CommandWithoutOptin()
		{
			List<string> list = new List<string>();
			if (_args.Length > 0)
			{
				foreach (ArgItem a in _args)
				{
					if (a.IsOption == false)
					{
						list.Add(a.Text);
					}
				}
			}
			return list.ToArray();
		}
	}
}
