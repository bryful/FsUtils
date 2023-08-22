using BRY;
namespace ChkForrm
{
	public partial class Form1 : Form
	{
		private string TempPath = string.Empty;
		public Form1()
		{
			InitializeComponent();

			AllowDrop = true;
			button1.Click += (sender, e) =>
			{
				Application.Exit();
			};
			this.DragEnter += (sender, e) =>
			{
				if (e.Data != null)
				{
					if (e.Data.GetDataPresent(DataFormats.FileDrop))
						//ドラッグされたデータ形式を調べ、ファイルのときはコピーとする
						e.Effect = DragDropEffects.Copy;
					else
						//ファイル以外は受け付けない
						e.Effect = DragDropEffects.None;
				}
			};
			this.DragDrop += (sender, e) =>
			{
				if (e.Data != null)
				{
					string[] fileName = (string[])e.Data.GetData(DataFormats.FileDrop, false);
					GetCommand(fileName);
				}
			};


			GetCommand(System.Environment.GetCommandLineArgs());

		}
		public void GetCommand(string[] cmds)
		{

			listBox1.Items.Clear();
			if (cmds.Length > 0)
			{
				int idx = 0;
				foreach (string cmd in cmds)
				{
					listBox1.Items.Add(cmd);
					if (idx==1)
					{
						TempPath = cmd;
					}
					idx++;
				}
			}

		}

		private void button2_Click(object sender, EventArgs e)
		{
			string s = textBox1.Text;
			if (s=="")
			{
				s = "No Text";
			}
			if (TempPath!="")
			{
				if (File.Exists(TempPath))
				{
					File.Delete(TempPath);
				}
				File.WriteAllText(TempPath, s);	
			}
			Application.Exit();	
		}
	}
}