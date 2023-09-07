using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Nodes;
using System.Threading.Tasks;
using BRY;

namespace SelectFolder
{
	partial class BaseForm
	{
		public virtual JsonObject? ToJson()
		{
			JsonFile jf = new JsonFile();
			//jf.SetValue(nameof(Name), (String)Name);//System.String
			jf.SetValue(nameof(IsShowTopMost), (bool)IsShowTopMost);//System.String
			jf.SetValue(nameof(Text), (String)Text);//System.String
			jf.SetValue(nameof(CloseAction), (int)CloseAction);//Hypowered.CloseAction
			jf.SetValue(nameof(Font), (Font)Font);//System.Drawing.Font
			jf.SetValue(nameof(IsAnti), (bool)IsAnti);//System.Drawing.Font
			jf.SetValue(nameof(StartPosition), (int)StartPosition);//System.Windows.Forms.FormStartPosition
			jf.SetValue(nameof(Size), (Size)Size);//System.Drawing.Size
			jf.SetValue(nameof(CanResize), (Boolean)CanResize);//System.Boolean
			jf.SetValue(nameof(MaximumSize), (Size)MaximumSize);//System.Drawing.Size
			jf.SetValue(nameof(MinimumSize), (Size)MinimumSize);//System.Drawing.Size
			jf.SetValue(nameof(Padding), (Padding)Padding);//System.Windows.Forms.Padding
			jf.SetValue(nameof(TopMost), (Boolean)TopMost);//System.Boolean
			jf.SetValue(nameof(BarHeight), (Int32)BarHeight);//System.Int32
			jf.SetValue(nameof(BarBackColor), (Color)BarBackColor);//System.Drawing.Color
			jf.SetValue(nameof(ForeColor), (Color)ForeColor);//System.Drawing.Color
			jf.SetValue(nameof(BackColor), (Color)BackColor);//System.Drawing.Color
			jf.SetValue(nameof(Opacity), (Double)Opacity);//System.Double
			jf.SetValue(nameof(DoubleBuffered), (Boolean)DoubleBuffered);//System.Boolean
			jf.SetValue(nameof(AllowTransparency), (Boolean)AllowTransparency);//System.Boolean
			jf.SetValue(nameof(TabIndex), (Int32)TabIndex);//System.Int32
			jf.SetValue(nameof(TabStop), (Boolean)TabStop);//System.Boolean
			jf.SetValue(nameof(AllowDrop), (Boolean)AllowDrop);//System.Boolean
			jf.SetValue(nameof(Margin), (Padding)Margin);//System.Windows.Forms.Padding
			jf.SetValue(nameof(KeyPreview), (Boolean)KeyPreview);//System.Boolean
			jf.SetValue(nameof(WindowState), (int)WindowState);//System.Windows.Forms.FormWindowState
			jf.SetValue(nameof(Anchor), (int)Anchor);//System.Windows.Forms.AnchorStyles


			jf.SetValue(nameof(AutoScaleBaseSize), (Size)AutoScaleBaseSize);//System.Drawing.Size
			jf.SetValue(nameof(AutoScroll), (Boolean)AutoScroll);//System.Boolean
			jf.SetValue(nameof(AutoSize), (Boolean)AutoSize);//System.Boolean
			jf.SetValue(nameof(AutoSizeMode), (int)AutoSizeMode);//System.Windows.Forms.AutoSizeMode
			jf.SetValue(nameof(AutoValidate), (int)AutoValidate);//System.Windows.Forms.AutoValidate
			jf.SetValue(nameof(ShowInTaskbar), (Boolean)ShowInTaskbar);//System.Boolean
			jf.SetValue(nameof(ShowIcon), (Boolean)ShowIcon);//System.Boolean
			jf.SetValue(nameof(SizeGripStyle), (int)SizeGripStyle);//System.Windows.Forms.SizeGripStyle
			jf.SetValue(nameof(TopLevel), (Boolean)TopLevel);//System.Boolean
			jf.SetValue(nameof(TransparencyKey), (Color)TransparencyKey);//System.Drawing.Color
			jf.SetValue(nameof(AutoScaleDimensions), (SizeF)AutoScaleDimensions);//System.Drawing.SizeF
			jf.SetValue(nameof(AutoScaleMode), (int)AutoScaleMode);//System.Windows.Forms.AutoScaleMode
			jf.SetValue(nameof(AutoScrollMargin), (Size)AutoScrollMargin);//System.Drawing.Size
			jf.SetValue(nameof(AutoScrollPosition), (Point)AutoScrollPosition);//System.Drawing.Point
			jf.SetValue(nameof(AutoScrollMinSize), (Size)AutoScrollMinSize);//System.Drawing.Size
			jf.SetValue(nameof(AutoScrollOffset), (Point)AutoScrollOffset);//System.Drawing.Point
			jf.SetValue(nameof(Capture), (Boolean)Capture);//System.Boolean
			jf.SetValue(nameof(CausesValidation), (Boolean)CausesValidation);//System.Boolean
			jf.SetValue(nameof(Dock), (int)Dock);//System.Windows.Forms.DockStyle
			jf.SetValue(nameof(IsAccessible), (Boolean)IsAccessible);//System.Boolean
			jf.SetValue(nameof(RightToLeft), (int)RightToLeft);//System.Windows.Forms.RightToLeft
			jf.SetValue(nameof(UseWaitCursor), (Boolean)UseWaitCursor);//System.Boolean
			jf.SetValue(nameof(ImeMode), (int)ImeMode);//System.Windows.Forms.ImeMode

			return jf.Obj;
		}
		// ****************************************************************************
		public virtual void FromJson(JsonObject jo)
		{
			JsonFile jf = new JsonFile(jo);
			object? v = null;
			v = jf.ValueAuto("IsShowTopMost", typeof(bool).Name);
			if (v != null) IsShowTopMost = (bool)v;

			v = jf.ValueAuto("Size", typeof(Size).Name);
			if (v != null) Size = (Size)v;
			v = jf.ValueAuto("Text", typeof(String).Name);
			if (v != null) Text = (String)v;
			v = jf.ValueAuto("CloseAction", typeof(Int32).Name);
			if (v != null) CloseAction = (CloseAction)v;
			v = jf.ValueAuto("Font", typeof(Font).Name);
			if (v != null) Font = (Font)v;
			v = jf.ValueAuto("IsAnti", typeof(Boolean).Name);
			if (v != null) IsAnti = (Boolean)v;

			v = jf.ValueAuto("StartPosition", typeof(int).Name);
			if (v != null) StartPosition = (FormStartPosition)v;
			v = jf.ValueAuto("CanResize", typeof(Boolean).Name);
			if (v != null) CanResize = (Boolean)v;
			v = jf.ValueAuto("MaximumSize", typeof(Size).Name);
			if (v != null) MaximumSize = (Size)v;
			v = jf.ValueAuto("MinimumSize", typeof(Size).Name);
			if (v != null) MinimumSize = (Size)v;
			v = jf.ValueAuto("Padding", typeof(Padding).Name);
			if (v != null) Padding = (Padding)v;
			v = jf.ValueAuto("TopMost", typeof(Boolean).Name);
			if (v != null) TopMost = (Boolean)v;
			v = jf.ValueAuto("BarHeight", typeof(Int32).Name);
			if (v != null) BarHeight = (Int32)v;
			v = jf.ValueAuto("BarBackColor", typeof(Color).Name);
			if (v != null) BarBackColor = (Color)v;
			v = jf.ValueAuto("ForeColor", typeof(Color).Name);
			if (v != null) ForeColor = (Color)v;
			v = jf.ValueAuto("BackColor", typeof(Color).Name);
			if (v != null) BackColor = (Color)v;
			v = jf.ValueAuto("Opacity", typeof(Double).Name);
			if (v != null) Opacity = (Double)v;
			v = jf.ValueAuto("DoubleBuffered", typeof(Boolean).Name);
			if (v != null) DoubleBuffered = (Boolean)v;
			v = jf.ValueAuto("AllowTransparency", typeof(Boolean).Name);
			if (v != null) AllowTransparency = (Boolean)v;

			v = jf.ValueAuto("AutoScaleBaseSize", typeof(Size).Name);
			if (v != null) AutoScaleBaseSize = (Size)v;
			v = jf.ValueAuto("AutoScroll", typeof(Boolean).Name);
			if (v != null) AutoScroll = (Boolean)v;
			v = jf.ValueAuto("AutoSize", typeof(Boolean).Name);
			if (v != null) AutoSize = (Boolean)v;
			v = jf.ValueAuto("AutoSizeMode", typeof(int).Name);
			if (v != null) AutoSizeMode = (AutoSizeMode)v;
			v = jf.ValueAuto("AutoValidate", typeof(int).Name);
			if (v != null) AutoValidate = (AutoValidate)v;
			v = jf.ValueAuto("FormBorderStyle", typeof(int).Name);
			if (v != null) FormBorderStyle = (FormBorderStyle)v;
			v = jf.ValueAuto("KeyPreview", typeof(Boolean).Name);
			if (v != null) KeyPreview = (Boolean)v;
			v = jf.ValueAuto("MaximizeBox", typeof(Boolean).Name);
			v = jf.ValueAuto("ShowInTaskbar", typeof(Boolean).Name);
			if (v != null) ShowInTaskbar = (Boolean)v;
			v = jf.ValueAuto("ShowIcon", typeof(Boolean).Name);
			if (v != null) ShowIcon = (Boolean)v;
			v = jf.ValueAuto("SizeGripStyle", typeof(int).Name);
			if (v != null) SizeGripStyle = (SizeGripStyle)v;
			v = jf.ValueAuto("TabIndex", typeof(Int32).Name);
			if (v != null) TabIndex = (Int32)v;
			v = jf.ValueAuto("TabStop", typeof(Boolean).Name);
			if (v != null) TabStop = (Boolean)v;
			v = jf.ValueAuto("TopLevel", typeof(Boolean).Name);
			if (v != null) TopLevel = (Boolean)v;
			v = jf.ValueAuto("TransparencyKey", typeof(Color).Name);
			if (v != null) TransparencyKey = (Color)v;
			v = jf.ValueAuto("WindowState", typeof(int).Name);
			if (v != null) WindowState = (FormWindowState)v;
			v = jf.ValueAuto("AutoScaleDimensions", typeof(SizeF).Name);
			if (v != null) AutoScaleDimensions = (SizeF)v;
			v = jf.ValueAuto("AutoScaleMode", typeof(int).Name);
			if (v != null) AutoScaleMode = (AutoScaleMode)v;
			v = jf.ValueAuto("AutoScrollMargin", typeof(Size).Name);
			if (v != null) AutoScrollMargin = (Size)v;
			v = jf.ValueAuto("AutoScrollPosition", typeof(Point).Name);
			if (v != null) AutoScrollPosition = (Point)v;
			v = jf.ValueAuto("AutoScrollMinSize", typeof(Size).Name);
			if (v != null) AutoScrollMinSize = (Size)v;
			v = jf.ValueAuto("AllowDrop", typeof(Boolean).Name);
			if (v != null) AllowDrop = (Boolean)v;
			v = jf.ValueAuto("Anchor", typeof(int).Name);
			if (v != null) Anchor = (AnchorStyles)v;
			v = jf.ValueAuto("AutoScrollOffset", typeof(Point).Name);
			if (v != null) AutoScrollOffset = (Point)v;
			v = jf.ValueAuto("Capture", typeof(Boolean).Name);
			if (v != null) Capture = (Boolean)v;
			v = jf.ValueAuto("CausesValidation", typeof(Boolean).Name);
			if (v != null) CausesValidation = (Boolean)v;
			v = jf.ValueAuto("Dock", typeof(int).Name);
			if (v != null) Dock = (DockStyle)v;
			v = jf.ValueAuto("IsAccessible", typeof(Boolean).Name);
			if (v != null) IsAccessible = (Boolean)v;
			v = jf.ValueAuto("RightToLeft", typeof(int).Name);
			if (v != null) RightToLeft = (RightToLeft)v;
			v = jf.ValueAuto("UseWaitCursor", typeof(Boolean).Name);
			if (v != null) UseWaitCursor = (Boolean)v;
			v = jf.ValueAuto("ImeMode", typeof(int).Name);
			if (v != null) ImeMode = (ImeMode)v;

			v = jf.ValueAuto("Margin", typeof(Padding).Name);
			if (v != null) Margin = (Padding)v;
		}
	}
}