using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FrameInput
{
	public class PrefFile
	{
		private Form? m_form = null;
		public JsonFile JsonFile { get; set; } = new JsonFile();
		// *********************************
		private string m_AppName = "";
		public string AppName { get { return m_AppName; } }
		// *********************************
		private string m_AppDataPath = "";
		public string AppDataPath { get { return m_AppDataPath; } }
		private string m_AppDataDirectory = "";
		public string AppDataDirectory { get { return m_AppDataDirectory; } }
		// ****************************************************
		public PrefFile(Form fm)
		{
			m_form = fm;
			m_AppName = Path.GetFileNameWithoutExtension(Application.ExecutablePath);
			m_AppDataDirectory = GetAppDataPath();
			m_AppDataPath = Path.Combine(m_AppDataDirectory, m_AppName + ".json");

		}
		// ****************************************************
		public bool SetBounds()
		{
			if (m_form == null) return false;
			JsonFile.SetValue("Bouns", m_form.Bounds);
			return true;
		}
		// ****************************************************
		public Rectangle? GetBounds()
		{
			Rectangle? ret = null;
			if (m_form == null) return ret;
			Rectangle? rct = JsonFile.ValueRectangle("Bouns");
			bool isIn = false;
			if (rct != null)
			{
				foreach (System.Windows.Forms.Screen s in System.Windows.Forms.Screen.AllScreens)
				{
					//ディスプレイのデバイス名を表示
					//Console.WriteLine("デバイス名:{0}", s.DeviceName);
					//ディスプレイの左上の座標を表示
					//Console.WriteLine("X:{0} Y:{1}", s.Bounds.X, s.Bounds.Y);
					//ディスプレイの大きさを表示
					//Console.WriteLine("高さ:{0} 幅:{1}", s.Bounds.Height, s.Bounds.Width);
					if (IsInRect(s.Bounds, (Rectangle)rct))
					{
						isIn = true;
					}
				}



			}
			if ((isIn == false) || (rct == null))
			{
				m_form.StartPosition = FormStartPosition.Manual;
				m_form.WindowState = FormWindowState.Normal;
				Rectangle ff = Screen.PrimaryScreen.Bounds;
				Point point = new Point(ff.Left + (ff.Width - m_form.Width) / 2, ff.Top + (ff.Height - m_form.Height) / 2);
				m_form.Location = point;
			}
			else
			{
				m_form.Bounds = (Rectangle)rct;
			}

			return ret;
		}
		// ****************************************************
		public bool Save(string s = "")
		{
			if (s == "") s = m_AppDataPath;

			return JsonFile.Save(s);
		}
		// ****************************************************
		public bool Load(string s = "")
		{
			if (s == "") s = m_AppDataPath;

			return JsonFile.Load(s);
		}
		// ****************************************************
		static public string GetAppDataPath()
		{
			return GetFileSystemPath(Environment.SpecialFolder.ApplicationData);
		}
		// ****************************************************
		static public string GetFileSystemPath(Environment.SpecialFolder folder)
		{
			// パスを取得
			string path = $"{Environment.GetFolderPath(folder)}\\"
				+ $"{Application.CompanyName}\\"
				+ $"{Application.ProductName}";

			// パスのフォルダを作成
			lock (typeof(Application))
			{
				if (!Directory.Exists(path))
				{
					Directory.CreateDirectory(path);
				}
			}
			return path;
		}
		// ****************************************************
		static public bool IsInRect(Rectangle scr, Rectangle b)
		{
			bool ret = true;

			if ((scr.Left > b.Left + b.Width) || (scr.Left + scr.Width < b.Left))
			{
				ret = false;
			}
			if ((scr.Top > b.Top + b.Height) || (scr.Top + scr.Height < b.Top))
			{
				ret = false;
			}
			return ret;
		}
		// ****************************************************
		static public bool ScreenIn(Rectangle? rct)
		{
			bool ret = false;
			if (rct == null) return ret;
			foreach (Screen s in Screen.AllScreens)
			{
				Rectangle r = s.WorkingArea;
				if (IsInRect(r, (Rectangle)rct))
				{
					ret = true;
					break;
				}
			}
			return ret;
		}
		// ****************************************************
		static public Rectangle NowScreen(Form fm)
		{
			return Screen.FromControl(fm).WorkingArea;
		}
		// ****************************************************
		static public bool ScreenIn(Point p, Size sz)
		{
			return ScreenIn(new Rectangle(p, sz));
		}

	}
}
