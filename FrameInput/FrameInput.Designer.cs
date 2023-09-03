namespace FrameInput
{
	partial class FrameInput
	{
		/// <summary>
		///  Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		///  Clean up any resources being used.
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
		///  Required method for Designer support - do not modify
		///  the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			components = new System.ComponentModel.Container();
			btnCancel = new Button();
			btnOK = new Button();
			contextMenuStrip1 = new ContextMenuStrip(components);
			fps24Menu = new ToolStripMenuItem();
			fps30Menu = new ToolStripMenuItem();
			frameEdit1 = new FrameEdit();
			label1 = new Label();
			contextMenuStrip1.SuspendLayout();
			SuspendLayout();
			// 
			// btnCancel
			// 
			btnCancel.DialogResult = DialogResult.Cancel;
			btnCancel.FlatStyle = FlatStyle.Flat;
			btnCancel.Font = new Font("MS UI Gothic", 14.25F, FontStyle.Regular, GraphicsUnit.Point);
			btnCancel.ForeColor = SystemColors.ActiveBorder;
			btnCancel.Location = new Point(91, 111);
			btnCancel.Name = "btnCancel";
			btnCancel.Size = new Size(100, 30);
			btnCancel.TabIndex = 5;
			btnCancel.Text = "Cancel";
			btnCancel.UseVisualStyleBackColor = true;
			btnCancel.Click += btnCancel_Click;
			// 
			// btnOK
			// 
			btnOK.FlatStyle = FlatStyle.Flat;
			btnOK.Font = new Font("MS UI Gothic", 14.25F, FontStyle.Regular, GraphicsUnit.Point);
			btnOK.ForeColor = SystemColors.ActiveBorder;
			btnOK.Location = new Point(197, 111);
			btnOK.Name = "btnOK";
			btnOK.Size = new Size(100, 30);
			btnOK.TabIndex = 6;
			btnOK.Text = "OK";
			btnOK.UseVisualStyleBackColor = true;
			btnOK.Click += btnOK_Click;
			// 
			// contextMenuStrip1
			// 
			contextMenuStrip1.Items.AddRange(new ToolStripItem[] { fps24Menu, fps30Menu });
			contextMenuStrip1.Name = "contextMenuStrip1";
			contextMenuStrip1.Size = new Size(103, 48);
			// 
			// fps24Menu
			// 
			fps24Menu.Name = "fps24Menu";
			fps24Menu.Size = new Size(102, 22);
			fps24Menu.Text = "fps24";
			// 
			// fps30Menu
			// 
			fps30Menu.Name = "fps30Menu";
			fps30Menu.Size = new Size(102, 22);
			fps30Menu.Text = "fps30";
			// 
			// frameEdit1
			// 
			frameEdit1.BackColor = Color.FromArgb(64, 64, 64);
			frameEdit1.BorderStyle = BorderStyle.FixedSingle;
			frameEdit1.Font = new Font("Yu Gothic UI", 14.25F, FontStyle.Regular, GraphicsUnit.Point);
			frameEdit1.ForeColor = Color.FromArgb(230, 230, 230);
			frameEdit1.ImeMode = ImeMode.Disable;
			frameEdit1.Location = new Point(33, 58);
			frameEdit1.Name = "frameEdit1";
			frameEdit1.ShortcutsEnabled = false;
			frameEdit1.Size = new Size(264, 33);
			frameEdit1.TabIndex = 10;
			// 
			// label1
			// 
			label1.AutoSize = true;
			label1.Font = new Font("Yu Gothic UI", 14.25F, FontStyle.Regular, GraphicsUnit.Point);
			label1.Location = new Point(33, 30);
			label1.Name = "label1";
			label1.Size = new Size(86, 25);
			label1.TabIndex = 11;
			label1.Text = "Duration";
			// 
			// FrameInput
			// 
			AcceptButton = btnOK;
			AllowDrop = true;
			AutoScaleDimensions = new SizeF(7F, 15F);
			AutoScaleMode = AutoScaleMode.Font;
			BackColor = Color.FromArgb(64, 64, 64);
			CancelButton = btnCancel;
			CanResize = false;
			ClientSize = new Size(335, 156);
			ContextMenuStrip = contextMenuStrip1;
			Controls.Add(label1);
			Controls.Add(frameEdit1);
			Controls.Add(btnOK);
			Controls.Add(btnCancel);
			Name = "FrameInput";
			ShowIcon = false;
			Text = "FrameInput";
			Load += FrameInput_Load;
			contextMenuStrip1.ResumeLayout(false);
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion
		private Button btnCancel;
		private Button btnOK;
		private ContextMenuStrip contextMenuStrip1;
		private ToolStripMenuItem fps24Menu;
		private ToolStripMenuItem fps30Menu;
		private FrameEdit frameEdit1;
		private Label label1;
	}
}