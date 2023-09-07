using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace SelectFolder
{
	public enum fuStatus
	{
		Error = 0,
		Input,
		OK,
		Cancel
	}
	public class FsTempData
	{
		public const string fuOK = "#fuOK:";
		public const string fuCancel = "#fuCancel:";
		public const string fuInput = "#fuInput:";
		private string m_filePath = "";
		public string Data = "";

		public bool Exists
		{
			get { return File.Exists(m_filePath); }
		}

		public FsTempData(string name = "")
		{
			Data = "";
			if (name == "")
			{
				m_filePath = Path.Combine(Path.GetTempPath(), "fuTemp.txt");
			}
			else
			{
				m_filePath = Path.Combine(Path.GetTempPath(), name);
			}
		}
		public bool Delete()
		{
			if (Exists)
			{
				File.Delete(m_filePath);
			}
			return !Exists;
		}
		public bool Load()
		{
			bool ret = false;
			Data = "";
			if (Exists)
			{
				string s = File.ReadAllText(m_filePath);
				if (s.IndexOf(fuInput) == 0)
				{
					Data = s.Substring(fuInput.Length);
					ret = true;
				}

			}
			return ret;
		}
		public bool Save(bool ok)
		{
			if (Exists) { Delete(); }
			File.WriteAllText(m_filePath, DataT(ok));
			return Exists;
		}
		public string DataT(bool isOK)
		{
			string dd = "";
			if (isOK)
			{
				dd = fuOK + Data;
			}
			else
			{
				dd = fuCancel + Data;
			}
			return dd;
		}

	}
}
