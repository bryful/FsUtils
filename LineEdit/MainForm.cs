using System.CodeDom;
using System.Text;
using System.Diagnostics.Eventing.Reader;

namespace LineEdit
{
	public partial class MainForm : BaseForm
	{
		private InOutMode InOutMode = InOutMode.None;
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
				ArgItem? c0 = cmd.FindOption(new string[] { "temp", "tmp" });
				if (c0 != null)
				{
					FsTempData td = new FsTempData();
					if (td.Load())
					{
						SetText( td.Data);
						InOutMode = InOutMode.File;
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
						if(item.Text!="")
						{
							SetText(item.Text);
							InOutMode = InOutMode.Cmd;
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
			FsTempData td = new FsTempData();
			td.Data = textEdit.Text;
			switch (InOutMode)
			{
				case InOutMode.File:
					noerr = td.Save(isOK);
					break;
				case InOutMode.Cmd:
					F_W.SettupConsole();
					Console.WriteLine(td.DataT(isOK));
					F_W.EndConsole(); 
					break;
			}
			if (noerr == true)
			{
				Application.Exit();
			}
		}
	}
	public enum InOutMode
	{
		None = 0,
		File,
		Cmd
	}

}