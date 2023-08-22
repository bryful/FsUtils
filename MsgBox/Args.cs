using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MsgBox
{
	public class ArgItem
	{
		public int Index { get; set; } = -1;
		public string Text { get; set; } = "";
		public ArgItem(string s)
		{
			Text = s;
			if (s.Length > 0)
			{
				m_IsOption = ((s[0] == '-') || (s[0] == '/'));
			}
		}
		public string[] Cmd = new string[0];
		private bool m_IsOption = false;
		public bool IsOption { get { return m_IsOption; } }
	}

	public class Args
	{
		private int m_OpCount = 0;
		public int OpCount { get { return m_OpCount; } }
		private ArgItem[] _args = new ArgItem[0];
		public int Count { get { return _args.Length; } }
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
			if (sa.Length > 0)
			{
				int op = 0;
				int cnt = 0;
				for (int i = 0; i < sa.Length; i++)
				{
					if (sa[i] != "")
					{
						ArgItem arg = new ArgItem(sa[i]);
						arg.Index = cnt; cnt++;
						if (arg.IsOption) { op++; }
						list.Add(arg);
					}
				}
				m_OpCount = op;
			}
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
	}
}
