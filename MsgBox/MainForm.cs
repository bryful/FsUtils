namespace MsgBox
{
	public partial class MainForm : BaseForm
	{
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
			bool isClear = false;
			bool? istopmost = null;
			string isText = "";
			if (args.Length > 0)
			{
				foreach (string arg in args)
				{

					if ((arg[0] == '-') || (arg[0] == '/'))
					{
						string opt = arg.Substring(1).ToLower().Trim();
						if ((opt == "clr") || (opt == "cls") || (opt == "clear"))
						{
							isClear = true;
						}
						else if ((opt == "topmoston") || (opt == "ton"))
						{
							istopmost = true;
						}
						else if ((opt == "topmostoff") || (opt == "toff"))
						{
							istopmost = false;
						}
					}
					if (File.Exists(arg))
					{
						isText += arg + "\r\n";
						string e = Path.GetExtension(arg).ToLower();
						if ((e == ".txt") || (e == ".json") || (e == ".ardj") || (e == ".xml"))
						{
							string s = File.ReadAllText(arg);
							if (s != "")
							{
								isText += s + "\r\n";
							}
						}
					}
					else if (isClear == false)
					{
						string s2 = arg.Replace("\\\\", "\\");
						s2 = s2.Replace("\\r", "\r").Replace("\\n", "\n").Replace("\\t", "\t");
						isText += s2;

					}
				}
			}
			if (isClear)
			{
				tbConsole.Text = "";
			}
			if (istopmost != null)
			{
				this.TopMost = (bool)istopmost;
			}
			if (isText != "")
				tbConsole.AppendText(isText);
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
	}
}