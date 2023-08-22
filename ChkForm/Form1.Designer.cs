namespace ChkForrm
{
	partial class Form1
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
			listBox1 = new ListBox();
			button1 = new Button();
			button2 = new Button();
			textBox1 = new TextBox();
			SuspendLayout();
			// 
			// listBox1
			// 
			listBox1.FormattingEnabled = true;
			listBox1.ItemHeight = 15;
			listBox1.Location = new Point(10, 7);
			listBox1.Name = "listBox1";
			listBox1.Size = new Size(556, 244);
			listBox1.TabIndex = 0;
			// 
			// button1
			// 
			button1.Location = new Point(481, 264);
			button1.Name = "button1";
			button1.Size = new Size(75, 23);
			button1.TabIndex = 1;
			button1.Text = "Close";
			button1.UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			button2.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			button2.Location = new Point(345, 264);
			button2.Name = "button2";
			button2.Size = new Size(109, 23);
			button2.TabIndex = 2;
			button2.Text = "ConsoleWrite";
			button2.UseVisualStyleBackColor = true;
			button2.Click += button2_Click;
			// 
			// textBox1
			// 
			textBox1.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			textBox1.Location = new Point(10, 264);
			textBox1.Name = "textBox1";
			textBox1.Size = new Size(328, 23);
			textBox1.TabIndex = 3;
			// 
			// Form1
			// 
			AllowDrop = true;
			AutoScaleDimensions = new SizeF(7F, 15F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(578, 299);
			Controls.Add(textBox1);
			Controls.Add(button2);
			Controls.Add(button1);
			Controls.Add(listBox1);
			Name = "Form1";
			Text = "Form1";
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private ListBox listBox1;
		private Button button1;
		private Button button2;
		private TextBox textBox1;
	}
}