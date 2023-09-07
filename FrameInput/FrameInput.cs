using System.CodeDom;
using System.Diagnostics;
using System.Diagnostics.Eventing.Reader;
using System.Text;
using BRY;

namespace FrameInput
{

	public partial class FrameInput : BaseForm
	{
		public double Duration
		{
			get
			{
				return frameEdit1.Duration;
			}
		}
		public void SetDuration(double b)
		{
			frameEdit1.SetDuration(b);
		}
		public int Frame
		{
			get
			{
				return frameEdit1.Frame;
			}
		}
		public void SetFrame(int f)
		{
			frameEdit1.SetFrame(f);
		}
		public FPS Fps
		{
			get { return frameEdit1.fps; }
		}
		public void SetFps(FPS fps)
		{
			frameEdit1.SetFps(fps);
		}
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
		public FrameInput()
		{
			//this.AllowDrop = true;
			InitializeComponent();
			this.FormClosed += (sender, e) => { LastSettings(); };
			StartSettings();

			fps24Menu.Click += (sender, e) => { frameEdit1.SetFps(FPS.f24); };
			fps30Menu.Click += (sender, e) => { frameEdit1.SetFps(FPS.f30); };

			Command(Environment.GetCommandLineArgs().Skip(1).ToArray(), PIPECALL.StartupExec);
			ToCenter();
		}
		// **********************************************************

		// **********************************************************
		// **********************************************************
		private void StartSettings()
		{
			PrefFile pf = new PrefFile(this,"FsUtils","FrameInput");
			pf.Load();
			object? v = null;
			v = pf.JsonFile.ValueAuto("TopMost", typeof(Boolean).Name);
			if (v != null) this.TopMost = (bool)v;

		}
		// **********************************************************
		private void LastSettings()
		{
			PrefFile pf = new PrefFile(this, "FsUtils", "FrameInput");
			pf.SetBounds();
			pf.JsonFile.SetValue("TopMost", this.TopMost);
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
			CmdArgv ca = new CmdArgv(args);
			string[] cmds;
			SetDuration(0);
			SetFps(FPS.f24);
			int idx = ca.FindKeys(new string[] { "fps", "framerate" });
			if (idx >= 0)
			{
				cmds = ca.KeyCmd(idx);
				if (cmds.Length > 0)
				{
					double dd = double.Parse(cmds[0]);
					if ((dd == 30) || (dd == 29.97))
					{
						SetFps(FPS.f30);
					}
				}
			}
			idx = ca.FindKeys(new string[] { "frame", "f" });
			if (idx >= 0)
			{
				cmds = ca.KeyCmd(idx);
				if (cmds.Length > 0)
				{
					int f;
					if (int.TryParse(cmds[0], out f))
					{
						SetFrame(f);
					}
				}
			}
			idx = ca.FindKeys(new string[] { "duration", "d" });
			if (idx >= 0)
			{
				cmds = ca.KeyCmd(idx);
				if (cmds.Length > 0)
				{
					double f2;
					if (double.TryParse(cmds[0], out f2))
					{
						SetDuration(f2);
					}
				}
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
		/*
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
		*/

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
			F_W.SettupConsole();
			if (isOK)
			{
				Console.WriteLine($"{Duration}");
			}
			else
			{
				Console.WriteLine("-1");
			}
			noerr = true;
			F_W.EndConsole();
			/*
			FsTempData td = new FsTempData();
			td.Data = $"{frameEdit1.Duration}";
			noerr = td.Save(isOK);
			*/
			if (noerr == true)
			{
				Application.Exit();
			}
		}

		private void contextMenuStrip1_Opening(object sender, System.ComponentModel.CancelEventArgs e)
		{
			bool b = (Fps == FPS.f24);
			fps24Menu.Checked = b;
			fps30Menu.Checked = !b;
		}

		private void FrameInput_Load(object sender, EventArgs e)
		{

		}
		public void ToCenter()
		{
			Rectangle r = Screen.PrimaryScreen.Bounds;
			this.Location = new Point((r.Width - this.Width) / 2, (r.Height - this.Height) / 2);
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