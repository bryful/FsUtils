using System.CodeDom;
using System.Diagnostics;
using System.Diagnostics.Eventing.Reader;
using System.Text;

namespace FrameInput
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
			//Rectangle? rect = pf.GetBounds();
			//object? v = null;
			//v = pf.JsonFile.ValueAuto("Multiline", typeof(Boolean).Name);
			//if (v != null) IsMultiline = (bool)v;

		}
		// **********************************************************
		private void LastSettings()
		{
			PrefFile pf = new PrefFile(this);
			pf.SetBounds();
			//pf.JsonFile.SetValue("Multiline", IsMultiline);
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
			string[] cmdLines = cmd.CommandWithoutOptin();


			if (cmd.Options.Length > 0)
			{
				ArgItem? c0 = cmd.FindOption(new string[] { "temp", "tmp" });
				if (c0 != null)
				{
					FsTempData td = new FsTempData();
					if (td.Load())
					{
						//SetText(td.Data);
						InOutMode = InOutMode.FileFile;
					}
				}
				ArgItem? c1 = cmd.FindOption(new string[] { "cmdfile", "commandfile" });
				if (c1 != null)
				{
					string s = "";
					if (cmdLines.Length > 0)
					{
						s = ChkDecode(cmdLines[0]);
					}
					//SetText(s);
					InOutMode = InOutMode.CmdFile;
				}
				ArgItem? c2 = cmd.FindOption(new string[] { "cmd", "command" });
				if (c2 != null)
				{
					string s = "";
					if (cmdLines.Length > 0)
					{
						s = ChkDecode(cmdLines[0]);
					}
					//SetText(s);
					InOutMode = InOutMode.CmdCmd;
				}
			}
			else
			{
				string s = "";
				if (cmdLines.Length > 0)
				{
					s = ChkDecode(cmdLines[0]);
				}
				//SetText(s);
				InOutMode = InOutMode.CmdNone;
			}
		}

		private string ChkDecode(string s)
		{
			s = s.Replace("\\r", "\r").Replace("\\n", "\n").Replace("\\t", "\t").Replace("\\\"", "\"").Replace("\\\\", "\\");

			return s;
		}
		private string ChkEncode(string s)
		{
			s = s.Replace("\\", "\\\\").Replace("\"", "\\\"").Replace("\r", "\\r").Replace("\n", "\\n").Replace("\t", "\\t");

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
			switch (InOutMode)
			{
				case InOutMode.CmdFile:
				case InOutMode.FileFile:
					//td.Data = textEdit.Text;
					noerr = td.Save(isOK);
					break;
				case InOutMode.CmdCmd:
					F_W.SettupConsole();
					//td.Data = ChkEncode(textEdit.Text);
					Console.WriteLine(td.DataT(isOK));
					noerr = true;
					F_W.EndConsole();
					break;
				default:
					noerr = true;
					break;

			}
			if (noerr == true)
			{
				Application.Exit();
			}
		}

		private void contextMenuStrip1_Opening(object sender, System.ComponentModel.CancelEventArgs e)
		{

		}
	}
	public enum InOutMode
	{
		None = 0,
		FileFile,
		CmdCmd,
		CmdFile,
		CmdNone
	}

}