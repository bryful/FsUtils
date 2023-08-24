namespace LineEdit
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
			textEdit = new TextBox();
			btnCancel = new Button();
			btnOK = new Button();
			SuspendLayout();
			// 
			// textEdit
			// 
			textEdit.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			textEdit.BackColor = Color.FromArgb(64, 64, 64);
			textEdit.BorderStyle = BorderStyle.FixedSingle;
			textEdit.Font = new Font("Yu Gothic UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
			textEdit.ForeColor = Color.FromArgb(230, 230, 230);
			textEdit.Location = new Point(34, 30);
			textEdit.Name = "textEdit";
			textEdit.ScrollBars = ScrollBars.Both;
			textEdit.Size = new Size(441, 29);
			textEdit.TabIndex = 0;
			// 
			// btnCancel
			// 
			btnCancel.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			btnCancel.DialogResult = DialogResult.Cancel;
			btnCancel.FlatStyle = FlatStyle.Flat;
			btnCancel.ForeColor = SystemColors.ActiveBorder;
			btnCancel.Location = new Point(313, 69);
			btnCancel.Name = "btnCancel";
			btnCancel.Size = new Size(75, 23);
			btnCancel.TabIndex = 1;
			btnCancel.Text = "Cancel";
			btnCancel.UseVisualStyleBackColor = true;
			btnCancel.Click += btnCancel_Click;
			// 
			// btnOK
			// 
			btnOK.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			btnOK.FlatStyle = FlatStyle.Flat;
			btnOK.ForeColor = SystemColors.ActiveBorder;
			btnOK.Location = new Point(400, 69);
			btnOK.Name = "btnOK";
			btnOK.Size = new Size(75, 23);
			btnOK.TabIndex = 2;
			btnOK.Text = "OK";
			btnOK.UseVisualStyleBackColor = true;
			btnOK.Click += btnOK_Click;
			// 
			// MainForm
			// 
			AcceptButton = btnOK;
			AllowDrop = true;
			AutoScaleDimensions = new SizeF(7F, 15F);
			AutoScaleMode = AutoScaleMode.Font;
			BackColor = Color.FromArgb(64, 64, 64);
			CancelButton = btnCancel;
			ClientSize = new Size(500, 100);
			Controls.Add(btnOK);
			Controls.Add(btnCancel);
			Controls.Add(textEdit);
			MaximumSize = new Size(2000, 100);
			MinimumSize = new Size(200, 100);
			Name = "MainForm";
			ShowIcon = false;
			Text = "LineEdit";
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private TextBox textEdit;
		private Button btnCancel;
		private Button btnOK;
	}
}