using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FrameInput
{
	public class CmdArgv
	{
		private string[] m_Argv = new string[0];
		private bool[] m_ArgvB = new bool[0];
		public CmdArgv(string[] argv)
		{
			SetArgv(argv);
		}
		public void SetArgv(string[] argv)
		{
			if(argv.Length<=0) return;
			List<string> list = new List<string>();
			List<bool> blist = new List<bool>();

			for(int i = 0; i < argv.Length; i++)
			{
				if ((argv[i][0] == '/') || (argv[i][0] == '-'))
				{
					blist.Add(true);
					list.Add(argv[i].ToLower().Substring(1));
				}
				else
				{
					list.Add(argv[i]);
					blist.Add(false);
				}
			}
			m_Argv = list.ToArray();
			m_ArgvB = blist.ToArray();
		}

		public int FindKeys(string[] keys)
		{
			int ret = -1;
			if ((keys.Length<=0)||(m_Argv.Length<=0)) return ret;

			string [] keys2 = new string[keys.Length];
			for(int idx =0; idx< keys.Length;idx++)
			{
				keys2[idx] = keys[idx].ToLower();	
			}

			for (int i = 0; i < m_Argv.Length; i++)
			{
				if(m_ArgvB[i]==false) continue;
				string s = m_Argv[i];
				for (int k = 0; k < keys.Length; k++)
				{
					if (s == keys2[k])
					{
						ret = i;
						break;
					}
				}
			}
			return ret;	
		}
		public string[] KeyCmd(int idx)
		{
			List<string> list = new List<string>();
			if (idx + 1 < m_Argv.Length)
			{
				for (int i = idx + 1; i < m_Argv.Length; i++)
				{
					if (m_ArgvB[i]==true)
					{
						break;
					}
					list.Add(m_Argv[i]);
				}
			}
			return list.ToArray();
		}
	}
}
