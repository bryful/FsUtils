namespace ChkForrm
{
	public partial class Form1 : Form
	{
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
						//�h���b�O���ꂽ�f�[�^�`���𒲂ׁA�t�@�C���̂Ƃ��̓R�s�[�Ƃ���
						e.Effect = DragDropEffects.Copy;
					else
						//�t�@�C���ȊO�͎󂯕t���Ȃ�
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
				foreach (string cmd in cmds)
				{
					listBox1.Items.Add(cmd);
				}
			}

		}

	}
}