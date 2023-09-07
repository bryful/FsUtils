using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace SelectFolder
{

	
	public partial class DriveListBox : ListBoxEX
	{
		//private DInfo[] m_drives = new DInfo[0];
		public string[] Drives
		{
			get
			{
				string[] ret = new string[DInfoItems.Count];
				if(DInfoItems.Count > 0)
				{
					for(int i = 0; i < DInfoItems.Count; i++)
					{
						ret[i] = DInfoItems[i].FullName;
					}
				}
				return ret;
			}
			set
			{
				if(value.Length>0)
				{
					for(int i=0; i<value.Length; i++)
					{
						DirectoryInfo d = new DirectoryInfo(value[i]);
						if (d.Exists == false) continue;
						DInfo di = new DInfo(d);
						for (int j = 0; j < DInfoItems.Count;j++)
						{
							if (DInfoItems[j].DriveLetter==di.DriveLetter)
							{
								DInfoItems[j].FullName =di.FullName;
								break;
							}
						}
						for (int j = 0; j < DInfoItems.Count; j++) 
							DInfoItems[i].Chk();
					}

				}
			}
		}
		public string DirectoryName
		{
			get 
			{
				int idx = SelectedIndex;
				if((idx>=0)&&(idx< DInfoItems.Count))
				{
					return DInfoItems[idx].FullName;
				}
				else
				{
					return "";			
				}
			}
			set
			{
				int idx = SetDirectoryName(value);
				if(idx>=0)
				{
					if (SelectedIndex != idx) SelectedIndex = idx;
				}
			}
		}
		private bool m_IsSelectedEvent = true;
		public int SetDirectoryName(string p)
		{
			int ret = -1;
			if (p == "") return ret;
			DirectoryInfo d = new DirectoryInfo(p);
			if (d.Exists == false) return ret;
			DInfo di = new DInfo(d);
			if (DInfoItems.Count > 0)
			{
				for (int i = 0; i < DInfoItems.Count; i++)
				{
					if (DInfoItems[i].DriveLetter == di.DriveLetter)
					{
						ret = i;
						DInfoItems[i].FullName = di.FullName;
						DInfoItems[i].Caption = di.Caption;
						if (SelectedIndex != i)
						{
							m_IsSelectedEvent = false;
							SelectedIndex = i;
							m_IsSelectedEvent = true;
						}
						break;
					}
				}
			}
			return ret;
		}
		public DriveListBox()
		{
			InitializeComponent();
		}
		
		protected override void InitLayout()
		{
			base.InitLayout();
			base.Clear();
			Listup();
		}
		
		private void Listup()
		{

			string[] drives = Environment.GetLogicalDrives();
			List<DInfo> dirs = new List<DInfo>();
			foreach (string drive in drives)
			{
				DirectoryInfo d = (new DirectoryInfo(drive));
				if (d.Exists) {
					DInfo di = new DInfo(d, false, true);
					if (di.Exists)
					{
						dirs.Add(di);
					}
				}
			}
			base.Clear();
			AddRange(dirs, true);
			if ((this.SelectedIndex < 0) && (DInfoItems.Count > 0)) this.SelectedIndex = 0;			
		}
		protected override void OnSelectedIndexChanged(EventArgs e)
		{
			if(m_IsSelectedEvent==false) return;
			try
			{
				if ((SelectedIndex >= 0) && (SelectedIndex < DInfoItems.Count))
				{

					if (m_DirectoryListBox != null)
					{
						m_DirectoryListBox.SetCurrentPath(DirectoryName, false);
					}
				}
				else
				{
					base.OnSelectedIndexChanged(e);
				}
			}
			catch { }
		}

		private DirectoryListBox? m_DirectoryListBox = null;
		public DirectoryListBox? DirectoryListBox
		{
			get { return m_DirectoryListBox; }
			set
			{
				m_DirectoryListBox = value;
			}
		}
	
	}
	public class DirChangedArg : EventArgs
	{
		public string Dir;
		public DirChangedArg(string v)
		{
			Dir = v;
		}
	}
}
