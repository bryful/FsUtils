using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
namespace SelectFolder
{
	public partial class ListBoxEX : ListBox
	{

		public List<DInfo> DInfoItems = new List<DInfo> ();
		public int Count
		{
			get { return DInfoItems.Count; }
		}
		public void AddRange(List<DInfo> lst, bool IsDrive= false)
		{
			string[] a = new string[lst.Count];
			for(int i=0; i< lst.Count;i++)
			{
				if (IsDrive)
				{
					a[i] = lst[i].Info;
				}
				else
				{
					a[i] = lst[i].Name;
				}
			}
			DInfoItems.Clear();
			DInfoItems.AddRange(lst);
			this.Items.Clear();
			this.Items.AddRange(a);
		}
		public void Clear()
		{
			this.Items.Clear();
			DInfoItems.Clear();
		}
		private Color m_SelectedColor=Color.FromArgb(200,200,200);
		public Color SelectedColor
		{
			get { return m_SelectedColor; }
			set { m_SelectedColor = value; }
		}
		public ListBoxEX()
		{
			InitializeComponent();
			this.DrawMode = DrawMode.OwnerDrawFixed;
			this.DrawItem += new DrawItemEventHandler(DrawItems);
			this.ItemHeight = 20;

		}
		private void DrawItems(object? sender, System.Windows.Forms.DrawItemEventArgs e)
		{
			ListBoxEX? lb = (ListBoxEX?)sender;
			using (SolidBrush sb = new SolidBrush(this.BackColor))
			
			{
				e.DrawBackground();

				if ((lb != null) && (e.Index > -1) && (lb.Items.Count > 0)&&(e.Font !=null))
				{
					if (DInfoItems[e.Index].IsParetn)
					{
						sb.Color = this.ForeColor;
						Rectangle r = new Rectangle(e.Bounds.Left, e.Bounds.Top, e.Bounds.Width - 16, e.Bounds.Height);
						e.Graphics.DrawString("../", e.Font, sb, r);
					}
					else
					{
						if ((e.State & DrawItemState.Selected) == DrawItemState.Selected)
						{
							sb.Color = m_SelectedColor;
							e.Graphics.FillRectangle(sb, e.Bounds);
						}
						if (DInfoItems.Count > e.Index)
						{
							Image? Ii = DInfoItems[e.Index].IconImage();
							if (Ii != null)
							{
								e.Graphics.DrawImage(Ii, e.Bounds.Left, e.Bounds.Top);
								Ii.Dispose();
							}
						}
						//文字列の取得
						string? txt = lb.Items[e.Index].ToString();
						if (txt != null)
						{
							if (txt.IndexOf("..\\") >= 0) txt = "<to Parent>";
							//文字列の描画
							sb.Color = this.ForeColor;
							Rectangle r = new Rectangle(e.Bounds.Left + 16, e.Bounds.Top, e.Bounds.Width - 16, e.Bounds.Height);
							e.Graphics.DrawString(txt, e.Font, sb, r);
						}
					}
				}

			}
			//背景を描画する
		}

	}
}
