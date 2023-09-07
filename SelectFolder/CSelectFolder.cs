using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SelectFolder
{
	public partial class CSelectFolder : Form
	{
		private string m_FileName="";
		public CSelectFolder()
		{
			InitializeComponent();
		}

		public string [] DriveList
		{
			get { return driveListBox1.Drives; }
			set { driveListBox1.Drives = value; }
		}
		public string FileName
		{
			get { return Path.Combine(dirFileListBox1.CurrentPath); }
			set
			{
				m_FileName = value;
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
		public void SavePref()
		{
			/*
			//設定ファイルの保存
			PrefFile pref = new PrefFile(this, "csc_Calc");
			pref.SetBounds();
			pref.JsonFile.SetValue("s1", splitContainer1.SplitterDistance);
			pref.JsonFile.SetValue("s2", splitContainer2.SplitterDistance);
			pref.JsonFile.SetValue("drives", driveListBox1.Drives);
			pref.JsonFile.SetValue("directoryName", dirFileListBox1.CurrentPath);
			pref.Save();
			*/

		}
		public void LoadPref()
		{
			//設定ファイルの読み込み
			/*
			PrefFile pref = new PrefFile(this, "csc_DropFolder");
			pref.Load();
			Rectangle? rct = pref.GetBounds();

			int? s1 = (int?)pref.JsonFile.ValueAuto("s1", (typeof(Int32).Name));
			int? s2 = (int?)pref.JsonFile.ValueAuto("s2", (typeof(Int32).Name));

			if ((s1!=null)&& (s2 != null) && (s1 > 0) && (s2 > 0))
			{
				splitContainer1.SplitterDistance = (int)s1;
				splitContainer2.SplitterDistance = (int)s2;
			}
			string[]? a = (string[]?)pref.JsonFile.ValueAuto("drives", (typeof(string[]).Name));
			if (a!=null) driveListBox1.Drives = (string[])a;

			if (m_FileName == "")
			{
				string? s = (string?)pref.JsonFile.ValueAuto("directoryName", (typeof(string).Name));
				if ((s != null) && (s != "") && (Directory.Exists(s) == true))
				{
					DirectoryInfo di = new DirectoryInfo(s);
					directoryListBox1.SetCurrentParent(di);
				}
			}
			*/
		}
		protected override void OnLoad(EventArgs e)
		{
			base.OnLoad(e);
			LoadPref();
			if(m_FileName != "")
			{
				DirectoryInfo di = new DirectoryInfo(m_FileName);
				if(di.Exists)
				{
					directoryListBox1.SetCurrentParent(di);
				}

			}
		}
		protected override void OnFormClosed(FormClosedEventArgs e)
		{
			SavePref();
			base.OnFormClosed(e);
		}
	}
}
