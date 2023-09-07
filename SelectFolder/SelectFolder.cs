using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using BRY;

namespace SelectFolder
{
	public partial class SelectFolder : BaseForm
	{

		// ********************************************************************
		public string[] DriveList
		{
			get { return driveListBox1.Drives; }
			set { driveListBox1.Drives = value; }
		}
		private string m_FileName = "";
		public string FileName
		{
			get { return Path.Combine(dirFileListBox1.CurrentPath); }
			set
			{
				m_FileName = value;
				if (m_FileName != "")
				{
					dirFileListBox1.CurrentPath = m_FileName;
				}
			}
		}
		private static string GetFileSystemPath(Environment.SpecialFolder folder)
		{
			// パスを取得
			string path = String.Format(@"{0}\{1}",//\{2}
			  Environment.GetFolderPath(folder),  // ベース・パス
												  //Application.CompanyName,            // 会社名
			  Application.ProductName
			  );           // 製品名

			// パスのフォルダを作成
			lock (typeof(Application))
			{
				if (!Directory.Exists(path))
				{
					Directory.CreateDirectory(path);
				}
			}
			return path;
		}

		public SelectFolder()
		{
			InitializeComponent();

			btnOK.Click += (sender, e) => { ExitWork(true); };
			btnCancel.Click += (sender, e) => { ExitWork(false); };

		}
		public void SavePref()
		{
			PrefFile pf = new PrefFile(this, "FsUtils", "SelectFolder");
			pf.SetBounds();
			pf.JsonFile.SetValue("s1", splitContainer1.SplitterDistance);
			pf.JsonFile.SetValue("s2", splitContainer2.SplitterDistance);
			pf.JsonFile.SetValue("drives", driveListBox1.Drives);
			pf.JsonFile.SetValue("directoryName", dirFileListBox1.CurrentPath);
			pf.Save();
		}
		public void LoadPref()
		{
			//設定ファイルの読み込み
			PrefFile pf = new PrefFile(this, "FsUtils", "SelectFolder");
			pf.Load();
			Rectangle? rect = pf.GetBounds();
			object? v = null;
			v = pf.JsonFile.ValueAuto("TopMost", typeof(Boolean).Name);
			if (v != null) this.TopMost = (bool)v;
			int? s1 = (int?)pf.JsonFile.ValueAuto("s1", (typeof(Int32).Name));
			int? s2 = (int?)pf.JsonFile.ValueAuto("s2", (typeof(Int32).Name));

			if ((s1 != null) && (s2 != null) && (s1 > 0) && (s2 > 0))
			{
				splitContainer1.SplitterDistance = (int)s1;
				splitContainer2.SplitterDistance = (int)s2;
			}
			string[]? a = (string[]?)pf.JsonFile.ValueAuto("drives", (typeof(string[]).Name));
			if (a != null) driveListBox1.Drives = (string[])a;

			if (m_FileName == "")
			{
				string? s = (string?)pf.JsonFile.ValueAuto("directoryName", (typeof(string).Name));
				if ((s != null) && (s != "") && (Directory.Exists(s) == true))
				{
					DirectoryInfo di = new DirectoryInfo(s);
					directoryListBox1.SetCurrentParent(di);
				}
			}

		}
		protected override void OnLoad(EventArgs e)
		{
			//base.OnLoad(e);
			LoadPref();
			string[] sa = Environment.GetCommandLineArgs().Skip(1).ToArray();
			if (sa.Length>0)
			{
				foreach (string s in sa)
				{
					if(Directory.Exists(s))
					{
						m_FileName = s;
						break;
					}
				}
			}
			if (m_FileName != "")
			{
				DirectoryInfo di = new DirectoryInfo(m_FileName);
				if (di.Exists)
				{
					directoryListBox1.SetCurrentParent(di);
				}

			}
		}
		protected override void OnResize(EventArgs e)
		{
			base.OnResize(e);
			this.Refresh();
		}
		// **********************************************************
		private void ExitWork(bool isOK)
		{
			bool noerr = false;
			F_W.SettupConsole();
			if (isOK)
			{
				Console.WriteLine($"{FileName}");
			}
			else
			{
				Console.WriteLine("");
			}
			noerr = true;
			F_W.EndConsole();
			if (noerr == true)
			{
				SavePref();
				Application.Exit();
			}
		}
	}
}
