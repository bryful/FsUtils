namespace MsgBox
{
	partial class MsgBox
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MsgBox));
			tbConsole = new TextBox();
			SuspendLayout();
			// 
			// tbConsole
			// 
			tbConsole.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			tbConsole.BackColor = Color.FromArgb(64, 64, 64);
			tbConsole.BorderStyle = BorderStyle.FixedSingle;
			tbConsole.ForeColor = Color.FromArgb(230, 230, 230);
			tbConsole.Location = new Point(12, 37);
			tbConsole.Multiline = true;
			tbConsole.Name = "tbConsole";
			tbConsole.ReadOnly = true;
			tbConsole.ScrollBars = ScrollBars.Both;
			tbConsole.Size = new Size(575, 209);
			tbConsole.TabIndex = 0;
			// 
			// MsgBox
			// 
			AllowDrop = true;
			AutoScaleDimensions = new SizeF(7F, 15F);
			AutoScaleMode = AutoScaleMode.Font;
			BackColor = Color.FromArgb(64, 64, 64);
			ClientSize = new Size(598, 258);
			Controls.Add(tbConsole);
			Icon = (Icon)resources.GetObject("$this.Icon");
			Name = "MsgBox";
			Text = "MsgBox";
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private TextBox tbConsole;
	}
}