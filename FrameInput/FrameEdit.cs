using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FrameInput
{
	public enum FPS
	{
		f24 = 24,
		f30 = 30
	}
	public partial class FrameEdit : TextBox
	{
		bool refFlag = false;
		private FPS m_fps = FPS.f24;
		public FPS fps
		{
			get { return m_fps;}
		}
		public void SetFps(FPS fps)
		{
			if (m_fps != fps)
			{
				m_fps = fps;
				DurationToText();
				InfoToLabel();
			}
		}
		private double m_Duration = 0;
		public double Duration
		{
			get { return m_Duration; }
		}
		public void SetDuration(double b)
		{
			m_Duration = b;
			if (m_Duration < 0) m_Duration = 0;
			DurationToText();
			InfoToLabel();
		}
		public int Frame
		{
			get
			{
				return (int)(m_Duration * (double)m_fps);
			}
		}
		public void SetFrame(int f)
		{
			SetDuration(  (double)f / (double)m_fps );
		}
		private Label? m_Label = null;
		public Label? Label
		{
			get { return this.m_Label; }
			set
			{
				m_Label = value;
				InfoToLabel();
			}
		}
		public FrameEdit()
		{
			InitializeComponent();
			ImeMode = ImeMode.Disable;
			ShortcutsEnabled = false;
			this.TextChanged += (sender, e) =>
			{

				TextToDuration();
				InfoToLabel();

			};
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
		private string InfoString()
		{
			int f = (int)(m_Duration * (double)m_fps);
			int s = f / (int)m_fps;
			int k = f % (int)m_fps;
			return $"fps:{(int)m_fps}, Frame:{f}, ({s}+{k})";
		}
		private void InfoToLabel()
		{
			if(m_Label!=null)
			{
				m_Label.Text = InfoString();
			}
		}
		private void DurationToText()
		{
			if (refFlag == true) return;
			refFlag = true;

			int f = (int)(m_Duration * (double)m_fps);
			int idx = this.Text.IndexOf("+");
			if(idx <0)
			{
				this.Text = $"{f}";
			}
			else
			{
				int sec = f / (int)m_fps;
				int koma = f % (int)m_fps;
				this.Text = $"{sec}+{koma}";
			}

			refFlag = false;
		}
		private void TextToDuration()
		{
			if(refFlag == true) return;
			refFlag = true;
			string s = this.Text;
			if ((s == "")||(s=="0")||(s == "00"))
			{
				m_Duration = 0;
				return;
			}

			if(s.IndexOf("+")<0)
			{
				m_Duration = ((double)ToInt(s) / (double)m_fps);
			}
			else
			{
				string[] sa = s.Split('+');
				int sec = (ToInt(sa[0]));
				int k = (ToInt(sa[1]));
				m_Duration = (double)sec + (double)k / (double)m_fps;

			}
			refFlag = false;
		}
		protected override void OnKeyPress(KeyPressEventArgs e)
		{
			//Debug.WriteLine(e.KeyChar);
			if (e.KeyChar == '\b')
			{
				
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
