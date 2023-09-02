namespace FrameInput
{
	partial class MainForm
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
			multilineMenu = new ToolStripMenuItem();
			radioButton3 = new RadioButton();
			radioButton4 = new RadioButton();
			numericUpDown1 = new NumericUpDown();
			numericUpDown2 = new NumericUpDown();
			numericUpDown3 = new NumericUpDown();
			contextMenuStrip1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)numericUpDown1).BeginInit();
			((System.ComponentModel.ISupportInitialize)numericUpDown2).BeginInit();
			((System.ComponentModel.ISupportInitialize)numericUpDown3).BeginInit();
			SuspendLayout();
			// 
			// btnCancel
			// 
			btnCancel.DialogResult = DialogResult.Cancel;
			btnCancel.FlatStyle = FlatStyle.Flat;
			btnCancel.Font = new Font("MS UI Gothic", 12F, FontStyle.Regular, GraphicsUnit.Point);
			btnCancel.ForeColor = SystemColors.ActiveBorder;
			btnCancel.Location = new Point(141, 116);
			btnCancel.Name = "btnCancel";
			btnCancel.Size = new Size(75, 30);
			btnCancel.TabIndex = 1;
			btnCancel.Text = "Cancel";
			btnCancel.UseVisualStyleBackColor = true;
			btnCancel.Click += btnCancel_Click;
			// 
			// btnOK
			// 
			btnOK.FlatStyle = FlatStyle.Flat;
			btnOK.Font = new Font("MS UI Gothic", 12F, FontStyle.Regular, GraphicsUnit.Point);
			btnOK.ForeColor = SystemColors.ActiveBorder;
			btnOK.Location = new Point(222, 116);
			btnOK.Name = "btnOK";
			btnOK.Size = new Size(75, 30);
			btnOK.TabIndex = 2;
			btnOK.Text = "OK";
			btnOK.UseVisualStyleBackColor = true;
			btnOK.Click += btnOK_Click;
			// 
			// contextMenuStrip1
			// 
			contextMenuStrip1.Items.AddRange(new ToolStripItem[] { multilineMenu });
			contextMenuStrip1.Name = "contextMenuStrip1";
			contextMenuStrip1.Size = new Size(122, 26);
			// 
			// multilineMenu
			// 
			multilineMenu.Name = "multilineMenu";
			multilineMenu.Size = new Size(121, 22);
			multilineMenu.Text = "Multiline";
			// 
			// radioButton3
			// 
			radioButton3.AutoSize = true;
			radioButton3.Checked = true;
			radioButton3.Font = new Font("MS UI Gothic", 12F, FontStyle.Regular, GraphicsUnit.Point);
			radioButton3.Location = new Point(26, 39);
			radioButton3.Name = "radioButton3";
			radioButton3.Size = new Size(68, 20);
			radioButton3.TabIndex = 24;
			radioButton3.TabStop = true;
			radioButton3.Text = "Frame";
			radioButton3.UseVisualStyleBackColor = true;
			// 
			// radioButton4
			// 
			radioButton4.AutoSize = true;
			radioButton4.Font = new Font("MS UI Gothic", 12F, FontStyle.Regular, GraphicsUnit.Point);
			radioButton4.Location = new Point(26, 77);
			radioButton4.Name = "radioButton4";
			radioButton4.Size = new Size(89, 20);
			radioButton4.TabIndex = 25;
			radioButton4.Text = "SecKoma";
			radioButton4.UseVisualStyleBackColor = true;
			// 
			// numericUpDown1
			// 
			numericUpDown1.BackColor = Color.FromArgb(64, 64, 64);
			numericUpDown1.BorderStyle = BorderStyle.FixedSingle;
			numericUpDown1.Font = new Font("MS UI Gothic", 12F, FontStyle.Regular, GraphicsUnit.Point);
			numericUpDown1.ForeColor = Color.FromArgb(230, 230, 230);
			numericUpDown1.Location = new Point(121, 36);
			numericUpDown1.Name = "numericUpDown1";
			numericUpDown1.Size = new Size(176, 23);
			numericUpDown1.TabIndex = 26;
			// 
			// numericUpDown2
			// 
			numericUpDown2.BackColor = Color.FromArgb(64, 64, 64);
			numericUpDown2.BorderStyle = BorderStyle.FixedSingle;
			numericUpDown2.Font = new Font("MS UI Gothic", 12F, FontStyle.Regular, GraphicsUnit.Point);
			numericUpDown2.ForeColor = Color.FromArgb(230, 230, 230);
			numericUpDown2.Location = new Point(121, 76);
			numericUpDown2.Name = "numericUpDown2";
			numericUpDown2.Size = new Size(79, 23);
			numericUpDown2.TabIndex = 27;
			// 
			// numericUpDown3
			// 
			numericUpDown3.BackColor = Color.FromArgb(64, 64, 64);
			numericUpDown3.BorderStyle = BorderStyle.FixedSingle;
			numericUpDown3.Font = new Font("MS UI Gothic", 12F, FontStyle.Regular, GraphicsUnit.Point);
			numericUpDown3.ForeColor = Color.FromArgb(230, 230, 230);
			numericUpDown3.Location = new Point(225, 76);
			numericUpDown3.Name = "numericUpDown3";
			numericUpDown3.Size = new Size(72, 23);
			numericUpDown3.TabIndex = 28;
			// 
			// MainForm
			// 
			AcceptButton = btnOK;
			AllowDrop = true;
			AutoScaleDimensions = new SizeF(7F, 15F);
			AutoScaleMode = AutoScaleMode.Font;
			BackColor = Color.FromArgb(64, 64, 64);
			CancelButton = btnCancel;
			ClientSize = new Size(322, 156);
			ContextMenuStrip = contextMenuStrip1;
			Controls.Add(numericUpDown3);
			Controls.Add(numericUpDown2);
			Controls.Add(numericUpDown1);
			Controls.Add(radioButton4);
			Controls.Add(radioButton3);
			Controls.Add(btnOK);
			Controls.Add(btnCancel);
			Name = "MainForm";
			ShowIcon = false;
			Text = "FrameInput";
			contextMenuStrip1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)numericUpDown1).EndInit();
			((System.ComponentModel.ISupportInitialize)numericUpDown2).EndInit();
			((System.ComponentModel.ISupportInitialize)numericUpDown3).EndInit();
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion
		private Button btnCancel;
		private Button btnOK;
		private ContextMenuStrip contextMenuStrip1;
		private ToolStripMenuItem multilineMenu;
		private RadioButton radioButton3;
		private RadioButton radioButton4;
		private NumericUpDown numericUpDown1;
		private NumericUpDown numericUpDown2;
		private NumericUpDown numericUpDown3;
	}
}