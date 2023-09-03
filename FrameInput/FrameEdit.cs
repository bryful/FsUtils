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
		bool refFlag = false;
		private FPS m_fps = FPS.f24;
		public FPS fps
		{
			get { return m_fps;}
			set
			{
				if (m_fps != value) 
				{
					m_fps = value;
					if (this.Text!="")
					{
						refFlag = true;
						int f = (int)(m_Duration * (int)m_fps);
						if (this.Text.IndexOf('+')>=0)
						{
							this.Text = $"{f / (int)m_fps}+{f % (int)m_fps}";
						}
						else
						{
							this.Text = $"{f}"; 
						}
						refFlag = false;
					}
				}
			}
		}
		private void DispSec()
		{
			if (refFlag) return;
			refFlag = true;
			int f = (int)(m_Duration * (int)m_fps);
			if (this.Text.IndexOf('+') >= 0)
			{
				this.Text = $"{f / (int)m_fps}+{f % (int)m_fps}";
			}
			else
			{
				this.Text = $"{f}";
			}
			refFlag = false;
		}
		private double m_Duration = 0;
		public double Duration
		{
			get { return m_Duration; }
			set
			{

			}
		}
		public FrameEdit()
		{
			InitializeComponent();
			ImeMode = ImeMode.Disable;
			ShortcutsEnabled = false;
		}
		private int ToInt(string s)
		{
			int ret = 0;
			if (s !="")
			{
				if (int.TryParse(s, out ret)==false)
				{
					ret = 0;
				}
			}
			return ret;
		}
		private void Calc()
		{
			m_Duration = 0;
			string s = this.Text;
			if (s == "")
			{
				m_Duration = 0;
				return;
			}
			string [] sa = s.Split('+');
			if(sa.Length == 0 ) 
			{
				m_Duration = 0;
				return;
			}else if (sa.Length == 1 )
			{
				m_Duration = (double)(ToInt(sa[0]))/(double)m_fps;
			}
			else
			{
				int sec = (ToInt(sa[0]));
				int k = (ToInt(sa[1]));
				m_Duration = (double)sec + (double)k/(double)m_fps;
			}
		}
		protected override void OnKeyPress(KeyPressEventArgs e)
		{
			Debug.WriteLine(e.KeyChar);
			if (e.KeyChar == '\b')
			{
				Calc();
				return;
			}

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
