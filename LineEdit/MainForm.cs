using System.CodeDom;
using System.Diagnostics.Eventing.Reader;

namespace LineEdit
{
	public partial class MainForm : BaseForm
	{
		private InOutMode InOutMode = InOutMode.None;
		private string m_TargetFile = string.Empty;
		// ********************************************************************
		private F_Pipe m_Server = new F_Pipe();
		public void StartServer(string pipename)
		{
			m_Server.Server(pipename);
			m_Server.Reception += (sender, e) =>

			{
				this.Invoke((Action)(() =>
				{
					PipeData pd = new PipeData(e.Text);
					string[] sa = pd.Args;
					Command(sa, PIPECALL.PipeExec);
					this.Activate();
				}));
			};
		}
		// ********************************************************************
		public void StopServer()
		{
			m_Server.StopServer();
		}
		public MainForm()
		{
			this.AllowDrop = true;
			InitializeComponent();
			this.FormClosed += (sender, e) => { LastSettings(); };
			StartSettings();
			Command(Environment.GetCommandLineArgs().Skip(1).ToArray(), PIPECALL.StartupExec);
		}
		// **********************************************************
		private void StartSettings()
		{
			PrefFile pf = new PrefFile(this);
			pf.Load();
			Rectangle? rect = pf.GetBounds();
		}
		// **********************************************************
		private void LastSettings()
		{
			PrefFile pf = new PrefFile(this);
			pf.SetBounds();
			pf.Save();
		}

		// **********************************************************
		/// <summary>
		/// コマンド解析
		/// </summary>
		/// <param name="args">コマンド配列</param>
		/// <param name="IsPipe">起動時かダブルクリック時か判別</param>
		public void Command(string[] args, PIPECALL IsPipe = PIPECALL.StartupExec)
		{
			Args cmd = new Args(args);
			if (cmd.Count <= 0) return;
			ArgItem[] cmdLines = cmd.ItemsWithoutOptin();

			if (cmd.Options.Length > 0)
			{
				ArgItem? c3 = cmd.FindOption(new string[] { "command", "cmd" });
				if (c3 != null)
				{
					if (cmd.CmdCount > 0)
					{
						string s = "";
						foreach (ArgItem s2 in cmdLines)
						{
							if (s2.Text != "") s += "\\r\\n";
							s += s2.Text;
						}
						SetText(s);
						InOutMode = InOutMode.None;
						return;
					}
				}
				ArgItem? c2 = cmd.FindOption(new string[] { "clipboard", "clip", "clp" });
				if (c2 != null)
				{
					if (GetClipboard() == true)
					{
						return;
					}
				}
				ArgItem? c1 = cmd.FindOption(new string[] { "file", "ld", "load" });
				if (c1 != null)
				{
					if (cmd.CmdCount > 0)
					{
						if (GetFile(cmdLines[0].Text) == true)
						{
							return;
						}
					}
				}
			}
			else
			{
				ArgItem[] items = cmd.ItemsWithoutOptin();

				if (items.Length > 0)
				{
					foreach (var item in items)
					{
						SetText(item.Text);
						if (textEdit.Text != "")
						{
							InOutMode = InOutMode.None;
							break;
						}
					}
				}
			}

		}
		private void SetText(string s)
		{
			textEdit.Text = ChkDecode(s);
			if (textEdit.Text != "")
			{
				textEdit.SelectionLength = 0;
				textEdit.SelectionStart = textEdit.Text.Length;
			}
		}
		private string ChkDecode(string s)
		{
			s = s.Replace("\\r", "\r").Replace("\\n", "\n").Replace("\\t", "\t").Replace("\\\\", "\\");

			return s;
		}
		private string ChkEncode(string s)
		{
			s = s.Replace("\\", "\\\\").Replace("\r", "\\r").Replace("\n", "\\n").Replace("\t", "\\t");

			return s;
		}
		protected override void OnDragEnter(DragEventArgs drgevent)
		{
			if ((drgevent != null) && (drgevent.Data != null))
			{
				if (drgevent.Data.GetDataPresent(DataFormats.FileDrop))
				{
					drgevent.Effect = DragDropEffects.Copy;
				}
			}
			else
			{
				base.OnDragEnter(drgevent);
			}
		}
		protected override void OnDragDrop(DragEventArgs drgevent)
		{
			if ((drgevent != null) && (drgevent.Data != null))
			{
				if (drgevent.Data.GetDataPresent(DataFormats.FileDrop))
				{

					// ドラッグ中のファイルやディレクトリの取得
					string[] drags = (string[])drgevent.Data.GetData(DataFormats.FileDrop);
					Command(drags);
				}
			}
			else
			{
				base.OnDragDrop(drgevent);
			}
		}

		// **********************************************************
		private void btnOK_Click(object sender, EventArgs e)
		{
			ExitWork(true);
		}

		private void btnCancel_Click(object sender, EventArgs e)
		{
			ExitWork(false);
		}
		// **********************************************************
		private void ExitWork(bool isOK)
		{
			bool noerr = false;
			if (isOK)
			{
				switch (InOutMode)
				{
					case InOutMode.Clip:
						noerr = SetClipboard();
						break;
					case InOutMode.File:
						noerr = SetFile();
						break;
					case InOutMode.None:
						noerr = true;
						break;
				}
			}
			else
			{
				switch (InOutMode)
				{
					case InOutMode.Clip:
						noerr = SetClipboardCancel();
						break;
					case InOutMode.File:
						noerr = SetFileCancel();
						break;
					case InOutMode.None:
						noerr = true;
						break;
				}
			}
			if (noerr == true)
			{
				Application.Exit();
			}
		}
		// **********************************************************
		private bool GetClipboard()
		{
			bool ret = false;
			if (Clipboard.ContainsText(TextDataFormat.Text))
			{
				string s = ChkDecode(Clipboard.GetText());
				if (s != "")
				{
					s = ChkTextHeader(s);
					if (s != "")
					{
						textEdit.Text = s;
						textEdit.SelectionLength = 0;
						textEdit.SelectionStart = textEdit.Text.Length;
						InOutMode = InOutMode.Clip;
						ret = true;
					}
				}
			}
			return ret;
		}
		// **********************************************************
		private bool SetClipboard()
		{
			bool ret = false;
			try
			{
				string s = ChkEncode(textEdit.Text);
				s = AddTextHeader(s);
				Clipboard.SetText(s);
				ret = true;
			}
			catch
			{
				ret = false;
			}
			return ret;
		}
		// **********************************************************
		private bool SetClipboardCancel()
		{
			bool ret = false;
			try
			{
				Clipboard.SetText(TextCancelHeader());
				ret = true;
			}
			catch
			{
				ret = false;
			}
			return ret;
		}
		// **********************************************************
		private string ChkTextHeader(string s)
		{
			if (s == "") return s;
			string key = "#fuIn:";
			int idx = s.IndexOf(key);
			if (idx != 0) return s;
			return s.Substring(key.Length).Trim();
		}
		// **********************************************************
		private string AddTextHeader(string s)
		{
			return "#fuOut:" + s;
		}
		// **********************************************************
		private string TextCancelHeader()
		{
			return "#fuCancel:";
		}
		// **********************************************************
		private bool GetFile(string p)
		{
			bool ret = false;
			if (File.Exists(p) == true)
			{
				try
				{
					string s = File.ReadAllText(p);
					s = ChkTextHeader(s);
					if (s != "")
					{
						m_TargetFile = p;
						InOutMode = InOutMode.File;
						SetText(s);
						ret = true;
					}
				}
				catch
				{
					m_TargetFile = "";
					InOutMode = InOutMode.None;
					ret = false;
				}
			}
			return ret;
		}
		private bool SetFile()
		{
			bool ret = false;
			if (m_TargetFile == "") return ret;
			try
			{
				if (File.Exists(m_TargetFile) == true) File.Delete(m_TargetFile);
				File.WriteAllText(m_TargetFile, AddTextHeader(textEdit.Text));
				ret = File.Exists(m_TargetFile);
			}
			catch
			{
				ret = false;
			}

			return ret;
		}
		private bool SetFileCancel()
		{
			bool ret = false;
			if (m_TargetFile == "") return ret;
			try
			{
				if (File.Exists(m_TargetFile) == true) File.Delete(m_TargetFile);
				File.WriteAllText(m_TargetFile, TextCancelHeader());
				ret = File.Exists(m_TargetFile);
			}
			catch
			{
				ret = false;
			}

			return ret;
		}
	}
	public enum InOutMode
	{
		None = 0,
		Clip,
		File
	}

}