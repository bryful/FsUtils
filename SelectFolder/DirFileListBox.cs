using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace SelectFolder
{
	public partial class DirFileListBox : ListBoxEX
	{
		/*
		public delegate void DirChangedHandler(object sender, DirChangedArg e);
		public event DirChangedHandler DirChanged;
		protected virtual void OnDirChanged(DirChangedArg e)
		{
			if (DirChanged != null)
			{
				DirChanged(this, e);
			}
		}
		*/
		private DirectoryInfo? m_Current = new DirectoryInfo(Directory.GetCurrentDirectory());
		public DirectoryInfo? Current
		{
			get { return m_Current; }
			set
			{
				m_Current = value;
				Listup();
			}
		}
		public string CurrentPath
		{
			get
			{
				if (m_Current == null)
				{
					return "";
				}
				else
				{
					return m_Current.FullName;
				}
			}
			set
			{
				if((value!=null)&&(value!=""))
				{
					Current = new DirectoryInfo(value);
				}
				else
				{
					Clear();
				}
			}
		}

		public new void Clear()
		{
			base.Clear();
			m_Current = null;
			if (m_DirTextBox != null)
			{
				m_DirTextBox.Text = "";
			}
		}
		public DirFileListBox()
		{
			InitializeComponent();
			Listup();
		}
		protected override void InitLayout()
		{
			base.InitLayout();
			this.Items.Clear();
			Listup();
		}
		private void Listup(bool IsEvent=true)
		{
			if ((m_Current==null)||(m_Current.Exists == false))
			{
				Clear();
				return;
			}
			base.Clear();
			if (m_DirTextBox != null)
			{
				m_DirTextBox.Text = "";
			}
			List<DInfo> lst = new List<DInfo>();
			try
			{
				IEnumerable<string> files = Directory.EnumerateFiles(m_Current.FullName, "*", SearchOption.TopDirectoryOnly);
				foreach (string s in files)
				{
					FileInfo fi = new FileInfo(s);
					if ((fi == null) || (fi.Exists == false)) continue;
					if ((fi.Attributes & FileAttributes.Hidden) != 0) continue;
					string e = Path.GetExtension(s).ToLower();
					if((e==".json")|| (e == ".ardj") || (e == ".ard")|| (e == ".aep")|| (e == ".jpg") || (e == ".jpeg") || (e == ".tga") || (e == ".txt") || (e == ".psd") || (e == ".ai"))
					{
						lst.Add(new DInfo(fi));
					}
				}
			}
			catch { }
			if (lst.Count > 0)
			{
				this.AddRange(lst);

			}
			if (IsEvent)
			{
				if (m_DirTextBox != null)
				{
					m_DirTextBox.Text = m_Current.FullName;
				}
				if (m_DirectoryListBox != null)
				{
					DirectoryInfo? di = m_Current.Parent;
					if ((di != null) && (di.Exists))
					{
						if (m_DirectoryListBox.CurrentPath != di.FullName)
						{
							m_DirectoryListBox.Current = di;
						}
					}
				}
			}

		}
		protected override void OnMouseDoubleClick(MouseEventArgs e)
		{
			if ((SelectedIndex >= 0) && (SelectedIndex < this.Items.Count))
			{
				if(DInfoItems[SelectedIndex].DInfoType == DInfoType.Dir)
				{
					if(m_DirectoryListBox!=null)
					{
						m_DirectoryListBox.SetCurrentParent(new DirectoryInfo(DInfoItems[SelectedIndex].FullName));
					}
				}
			}
			else
			{
				base.OnMouseDoubleClick(e);
			}
		}
		private TextBox? m_DirTextBox = null;
		public TextBox? DirTextBox
		{
			get { return m_DirTextBox; }
			set
			{
				m_DirTextBox = value;
			}
		}
		private DirectoryListBox? m_DirectoryListBox = null;
		public DirectoryListBox? DirectoryListBox
		{
			get { return m_DirectoryListBox; }
			set { m_DirectoryListBox = value; }
		}
	}
}
