namespace SelectFolder
{
	partial class SelectFolder
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SelectFolder));
			driveListBox1 = new DriveListBox();
			directoryListBox1 = new DirectoryListBox();
			ToDeskTop = new Button();
			tbDir = new TextBox();
			dirFileListBox1 = new DirFileListBox();
			tbTargetDir = new TextBox();
			btnDoc = new Button();
			btnParent = new Button();
			btnRoot = new Button();
			btnUser = new Button();
			splitContainer1 = new SplitContainer();
			splitContainer2 = new SplitContainer();
			btnCancel = new Button();
			btnOK = new Button();
			((System.ComponentModel.ISupportInitialize)splitContainer1).BeginInit();
			splitContainer1.Panel1.SuspendLayout();
			splitContainer1.Panel2.SuspendLayout();
			splitContainer1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)splitContainer2).BeginInit();
			splitContainer2.Panel1.SuspendLayout();
			splitContainer2.Panel2.SuspendLayout();
			splitContainer2.SuspendLayout();
			SuspendLayout();
			// 
			// driveListBox1
			// 
			driveListBox1.BackColor = Color.FromArgb(64, 64, 64);
			driveListBox1.BorderStyle = BorderStyle.FixedSingle;
			driveListBox1.DirectoryListBox = directoryListBox1;
			driveListBox1.DirectoryName = "C:\\";
			driveListBox1.Dock = DockStyle.Fill;
			driveListBox1.DrawMode = DrawMode.OwnerDrawFixed;
			driveListBox1.Drives = new string[] { "C:\\", "D:\\", "E:\\", "F:\\", "G:\\", "K:\\", "M:\\", "N:\\", "O:\\", "P:\\", "Q:\\", "S:\\", "T:\\", "X:\\", "Y:\\", "Z:\\" };
			driveListBox1.Font = new Font("Yu Gothic UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
			driveListBox1.ForeColor = Color.FromArgb(230, 230, 230);
			driveListBox1.FormattingEnabled = true;
			driveListBox1.ItemHeight = 20;
			driveListBox1.Items.AddRange(new object[] { "C (Windows)", "D (Recovery Image)", "E (ボリューム)", "F (HDCZ-UT)", "G (Google Drive)", "K (DCst-Other)", "M (DCst-SEED)", "N (DCst-ZEP)", "O (DCst-GOR_Public)", "P (DCst-FLD)", "Q (DCst-TAB)", "S (DCst-SDS)", "T (DCst-IKS)", "X (DCst-USERS)", "Y (DCst-BS_3D)", "Z (DCst-Setting)" });
			driveListBox1.Location = new Point(0, 0);
			driveListBox1.Name = "driveListBox1";
			driveListBox1.SelectedColor = SystemColors.WindowFrame;
			driveListBox1.Size = new Size(199, 402);
			driveListBox1.TabIndex = 0;
			// 
			// directoryListBox1
			// 
			directoryListBox1.BackColor = Color.FromArgb(64, 64, 64);
			directoryListBox1.BorderStyle = BorderStyle.FixedSingle;
			directoryListBox1.CurrentPath = "C:\\";
			directoryListBox1.DesktopBtn = ToDeskTop;
			directoryListBox1.DirectryTextBox = tbDir;
			directoryListBox1.DirFileListBox = dirFileListBox1;
			directoryListBox1.DocBtn = btnDoc;
			directoryListBox1.Dock = DockStyle.Fill;
			directoryListBox1.DrawMode = DrawMode.OwnerDrawFixed;
			directoryListBox1.DriveListBox = driveListBox1;
			directoryListBox1.Font = new Font("Yu Gothic UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
			directoryListBox1.ForeColor = Color.FromArgb(230, 230, 230);
			directoryListBox1.FormattingEnabled = true;
			directoryListBox1.ItemHeight = 20;
			directoryListBox1.Items.AddRange(new object[] { "AITEMP", "Autodesk", "Bin", "BluetoothExchangeFolder", "cert", "ESD", "inetpub", "MoTemp", "PerfLogs", "Program Files", "Program Files (x86)", "Quarantine", "SWSETUP", "SymCache", "Temp", "tmp", "Users", "Windows", "Windows10Upgrade" });
			directoryListBox1.Location = new Point(0, 0);
			directoryListBox1.Name = "directoryListBox1";
			directoryListBox1.ParentBtn = btnParent;
			directoryListBox1.RootBtn = btnRoot;
			directoryListBox1.SelectedColor = SystemColors.WindowFrame;
			directoryListBox1.Size = new Size(311, 402);
			directoryListBox1.TabIndex = 0;
			directoryListBox1.UserBtn = btnUser;
			// 
			// ToDeskTop
			// 
			ToDeskTop.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
			ToDeskTop.FlatStyle = FlatStyle.Flat;
			ToDeskTop.ForeColor = Color.FromArgb(230, 230, 230);
			ToDeskTop.Location = new Point(35, 512);
			ToDeskTop.Name = "ToDeskTop";
			ToDeskTop.Size = new Size(96, 25);
			ToDeskTop.TabIndex = 4;
			ToDeskTop.Text = "to Desktop";
			ToDeskTop.UseVisualStyleBackColor = true;
			// 
			// tbDir
			// 
			tbDir.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			tbDir.BackColor = Color.FromArgb(64, 64, 64);
			tbDir.BorderStyle = BorderStyle.None;
			tbDir.Font = new Font("Yu Gothic UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
			tbDir.ForeColor = Color.FromArgb(230, 230, 230);
			tbDir.Location = new Point(24, 31);
			tbDir.Name = "tbDir";
			tbDir.ReadOnly = true;
			tbDir.Size = new Size(514, 22);
			tbDir.TabIndex = 0;
			tbDir.Text = "C:\\";
			tbDir.TextAlign = HorizontalAlignment.Right;
			// 
			// dirFileListBox1
			// 
			dirFileListBox1.BackColor = Color.FromArgb(64, 64, 64);
			dirFileListBox1.BorderStyle = BorderStyle.FixedSingle;
			dirFileListBox1.CurrentPath = "C:\\Autodesk";
			dirFileListBox1.DirectoryListBox = directoryListBox1;
			dirFileListBox1.DirTextBox = tbTargetDir;
			dirFileListBox1.Dock = DockStyle.Fill;
			dirFileListBox1.DrawMode = DrawMode.OwnerDrawFixed;
			dirFileListBox1.Font = new Font("Yu Gothic UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
			dirFileListBox1.ForeColor = Color.FromArgb(230, 230, 230);
			dirFileListBox1.FormattingEnabled = true;
			dirFileListBox1.ItemHeight = 20;
			dirFileListBox1.Location = new Point(0, 0);
			dirFileListBox1.Name = "dirFileListBox1";
			dirFileListBox1.SelectedColor = SystemColors.WindowFrame;
			dirFileListBox1.Size = new Size(257, 402);
			dirFileListBox1.TabIndex = 0;
			// 
			// tbTargetDir
			// 
			tbTargetDir.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			tbTargetDir.BackColor = Color.FromArgb(64, 64, 64);
			tbTargetDir.BorderStyle = BorderStyle.None;
			tbTargetDir.Font = new Font("Yu Gothic UI", 14.25F, FontStyle.Regular, GraphicsUnit.Point);
			tbTargetDir.ForeColor = Color.FromArgb(230, 230, 230);
			tbTargetDir.Location = new Point(24, 467);
			tbTargetDir.Name = "tbTargetDir";
			tbTargetDir.ReadOnly = true;
			tbTargetDir.Size = new Size(707, 26);
			tbTargetDir.TabIndex = 3;
			tbTargetDir.Text = "C:\\Autodesk";
			tbTargetDir.TextAlign = HorizontalAlignment.Right;
			// 
			// btnDoc
			// 
			btnDoc.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
			btnDoc.FlatStyle = FlatStyle.Flat;
			btnDoc.ForeColor = Color.FromArgb(230, 230, 230);
			btnDoc.Location = new Point(137, 512);
			btnDoc.Name = "btnDoc";
			btnDoc.Size = new Size(96, 25);
			btnDoc.TabIndex = 5;
			btnDoc.Text = "to Document";
			btnDoc.UseVisualStyleBackColor = true;
			// 
			// btnParent
			// 
			btnParent.Anchor = AnchorStyles.Top | AnchorStyles.Right;
			btnParent.FlatStyle = FlatStyle.Flat;
			btnParent.ForeColor = Color.FromArgb(230, 230, 230);
			btnParent.Location = new Point(703, 32);
			btnParent.Name = "btnParent";
			btnParent.Size = new Size(96, 23);
			btnParent.TabIndex = 2;
			btnParent.Text = "to Parent";
			btnParent.UseVisualStyleBackColor = true;
			// 
			// btnRoot
			// 
			btnRoot.Anchor = AnchorStyles.Top | AnchorStyles.Right;
			btnRoot.FlatStyle = FlatStyle.Flat;
			btnRoot.ForeColor = Color.FromArgb(230, 230, 230);
			btnRoot.Location = new Point(601, 32);
			btnRoot.Name = "btnRoot";
			btnRoot.Size = new Size(96, 23);
			btnRoot.TabIndex = 1;
			btnRoot.Text = "to Root";
			btnRoot.UseVisualStyleBackColor = true;
			// 
			// btnUser
			// 
			btnUser.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
			btnUser.FlatStyle = FlatStyle.Flat;
			btnUser.ForeColor = Color.FromArgb(230, 230, 230);
			btnUser.Location = new Point(239, 512);
			btnUser.Name = "btnUser";
			btnUser.Size = new Size(96, 25);
			btnUser.TabIndex = 6;
			btnUser.Text = "to UserFolder";
			btnUser.UseVisualStyleBackColor = true;
			// 
			// splitContainer1
			// 
			splitContainer1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			splitContainer1.Location = new Point(24, 59);
			splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			splitContainer1.Panel1.Controls.Add(driveListBox1);
			// 
			// splitContainer1.Panel2
			// 
			splitContainer1.Panel2.Controls.Add(splitContainer2);
			splitContainer1.Size = new Size(775, 402);
			splitContainer1.SplitterDistance = 199;
			splitContainer1.TabIndex = 6;
			// 
			// splitContainer2
			// 
			splitContainer2.Dock = DockStyle.Fill;
			splitContainer2.Location = new Point(0, 0);
			splitContainer2.Name = "splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			splitContainer2.Panel1.Controls.Add(directoryListBox1);
			// 
			// splitContainer2.Panel2
			// 
			splitContainer2.Panel2.Controls.Add(dirFileListBox1);
			splitContainer2.Size = new Size(572, 402);
			splitContainer2.SplitterDistance = 311;
			splitContainer2.TabIndex = 0;
			// 
			// btnCancel
			// 
			btnCancel.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			btnCancel.DialogResult = DialogResult.Cancel;
			btnCancel.FlatStyle = FlatStyle.Flat;
			btnCancel.ForeColor = Color.FromArgb(230, 230, 230);
			btnCancel.Location = new Point(579, 512);
			btnCancel.Name = "btnCancel";
			btnCancel.Size = new Size(96, 30);
			btnCancel.TabIndex = 7;
			btnCancel.Text = "Cancel";
			btnCancel.UseVisualStyleBackColor = true;
			// 
			// btnOK
			// 
			btnOK.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			btnOK.DialogResult = DialogResult.OK;
			btnOK.FlatStyle = FlatStyle.Flat;
			btnOK.ForeColor = Color.FromArgb(230, 230, 230);
			btnOK.Location = new Point(681, 512);
			btnOK.Name = "btnOK";
			btnOK.Size = new Size(96, 30);
			btnOK.TabIndex = 8;
			btnOK.Text = "OK";
			btnOK.UseVisualStyleBackColor = true;
			// 
			// SelectFolder
			// 
			AcceptButton = btnOK;
			AutoScaleDimensions = new SizeF(7F, 15F);
			AutoScaleMode = AutoScaleMode.Font;
			CancelButton = btnCancel;
			ClientSize = new Size(817, 554);
			Controls.Add(btnParent);
			Controls.Add(btnRoot);
			Controls.Add(btnUser);
			Controls.Add(btnDoc);
			Controls.Add(btnOK);
			Controls.Add(btnCancel);
			Controls.Add(splitContainer1);
			Controls.Add(ToDeskTop);
			Controls.Add(tbTargetDir);
			Controls.Add(tbDir);
			Icon = (Icon)resources.GetObject("$this.Icon");
			MinimumSize = new Size(600, 360);
			Name = "SelectFolder";
			Text = "";
			TopMost = true;
			splitContainer1.Panel1.ResumeLayout(false);
			splitContainer1.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)splitContainer1).EndInit();
			splitContainer1.ResumeLayout(false);
			splitContainer2.Panel1.ResumeLayout(false);
			splitContainer2.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)splitContainer2).EndInit();
			splitContainer2.ResumeLayout(false);
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private DriveListBox driveListBox1;
		private DirectoryListBox directoryListBox1;
		private DirFileListBox dirFileListBox1;
		private TextBox tbDir;
		private TextBox tbTargetDir;
		private Button ToDeskTop;
		private SplitContainer splitContainer1;
		private SplitContainer splitContainer2;
		private Button btnCancel;
		private Button btnOK;
		private Button btnDoc;
		private Button btnUser;
		private Button btnRoot;
		private Button btnParent;
	}
}