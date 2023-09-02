using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FrameInput
{
	public partial class FrameEdit : TextBox
	{
		public FrameEdit()
		{
			InitializeComponent();
			ImeMode = ImeMode.Disable;
			ShortcutsEnabled = false;
		}

		protected override void OnKeyPress(KeyPressEventArgs e)
		{
			Debug.WriteLine(e.KeyChar);
			if (e.KeyChar == '\b') return;

			if (e.KeyChar == '+')
			{
				if (this.Text.IndexOf('+')>=0)
				{
					e.Handled = true;
				}
			}
			else if ((e.KeyChar < '0' || '9' < e.KeyChar))
			{
				e.Handled = true;
			}
		}

	}
}
