using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Text.Unicode;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MsgBox
{
	public class JsonFile
	{
		// *********************************************************************************************************
		public JsonObject? Obj = null;
		// *********************************************************************************************************
		public JsonFile(JsonObject? obj = null)
		{
			Obj = obj;
			if (Obj == null) Obj = new JsonObject();

		}
		// *********************************

		// ****************************************************
		public string? ToJson()
		{
			if (Obj != null)
			{
				var options = new JsonSerializerOptions
				{
					Encoder = JavaScriptEncoder.Create(UnicodeRanges.All),
					WriteIndented = true
				};
				return Obj.ToJsonString(options);
			}
			else
			{
				return null;
			}

		}
		// ****************************************************
		public void FromJson(string? js)
		{
			try
			{
				if ((js == null) || (js == "")) return;
				var doc = JsonNode.Parse(js);
				if (doc != null)
				{
					Obj = (JsonObject)doc;
				}
			}
			catch
			{
				Obj = new JsonObject();
			}
		}
		// ****************************************************
		public bool Save(string p)
		{
			bool ret = false;
			try
			{
				string? js = ToJson();
				if (js != null)
				{
					File.WriteAllText(p, js);
					ret = true;
				}
			}
			catch
			{
				ret = false;
			}
			return ret;
		}

		// ****************************************************
		public bool Load(string p)
		{
			bool ret = false;

			try
			{
				if (File.Exists(p) == true)
				{
					string str = File.ReadAllText(p);
					if (str != "")
					{
						FromJson(str);
						ret = true;
					}
				}
			}
			catch
			{
				Obj = new JsonObject();
				ret = false;
			}
			return ret;
		}
		public JsonArray ColorToJson(Color c)
		{
			JsonArray ja = new JsonArray();
			ja.Add(c.A);
			ja.Add(c.R);
			ja.Add(c.G);
			ja.Add(c.B);
			return ja;
		}
		// *********************************************************************************************************
		public Color? ColorFromJson(JsonNode? jo)
		{
			Color? ret = null;
			if (jo == null) return ret;
			JsonArray? ja = jo.AsArray();
			if (ja != null)
			{
				int? a = 255;
				int? r = 255;
				int? g = 255;
				int? b = 255;
				if (ja.Count >= 4)
				{
					a = ja[0].GetValue<int?>();
					r = ja[1].GetValue<int?>();
					g = ja[2].GetValue<int?>();
					b = ja[3].GetValue<int?>();
				}
				else if (ja.Count == 3)
				{
					r = ja[0].GetValue<int>();
					g = ja[1].GetValue<int>();
					b = ja[2].GetValue<int>();
				}
				else
				{
					return ret;
				}
				if ((a != null) && (r != null) && (g != null) && (b != null))
				{
					return Color.FromArgb((int)a, (int)r, (int)g, (int)b);
				}
				else
				{
					return ret;
				}
			}
			else
			{
				return ret;
			}
		}
		// *****************************************************************
		static public JsonArray RectangleToJsonArray(Rectangle sz)
		{
			JsonArray arr = new JsonArray();
			arr.Add(sz.Left);
			arr.Add(sz.Top);
			arr.Add(sz.Width);
			arr.Add(sz.Height);
			return arr;
		}
		static public Rectangle? RectangleFromJson(JsonNode? jo)
		{
			Rectangle? ret = null;
			JsonArray? ar = jo.AsArray();
			if (ar == null) return ret;
			if (ar.Count >= 4)
			{
				ret = new Rectangle(
					ar[0].GetValue<int>(),
					ar[1].GetValue<int>(),
					ar[2].GetValue<int>(),
					ar[3].GetValue<int>()
					);
			}
			return ret;
		}
		static public JsonArray PaddingToJson(Padding p)
		{
			JsonArray arr = new JsonArray();
			arr.Add(p.Left);
			arr.Add(p.Top);
			arr.Add(p.Right);
			arr.Add(p.Bottom);
			return arr;
		}
		static public Padding? PaddingFromJson(JsonNode? jo)
		{
			Padding? ret = null;
			JsonArray ar = jo.AsArray();
			if (ar == null) return ret;
			if (ar.Count >= 4)
			{
				ret = new Padding(
					ar[0].GetValue<int>(),
					ar[1].GetValue<int>(),
					ar[2].GetValue<int>(),
					ar[3].GetValue<int>()
					);
			}
			return ret;
		}
		// *********
		static public JsonArray PointToJson(Point p)
		{
			JsonArray arr = new JsonArray();
			arr.Add(p.X);
			arr.Add(p.Y);
			return arr;
		}
		static public Point? PointFromJson(JsonNode? jo)
		{
			Point? ret = null;
			if (jo == null) return ret;
			JsonArray ar = jo.AsArray();
			if (ar == null) return ret;
			if (ar.Count >= 2)
			{
				ret = new Point(
					ar[0].GetValue<int>(),
					ar[1].GetValue<int>()

					);
			}
			return ret;
		}
		// *********
		static public JsonArray SizeToJson(Size p)
		{
			JsonArray arr = new JsonArray();
			arr.Add(p.Width);
			arr.Add(p.Height);
			return arr;
		}
		static public JsonArray SizeToJson(SizeF p)
		{
			JsonArray arr = new JsonArray();
			arr.Add(p.Width);
			arr.Add(p.Height);
			return arr;
		}
		static public Size? SizeFromJson(JsonNode? jo)
		{
			Size? ret = null;
			if (jo == null) return ret;
			JsonArray ar = jo.AsArray();
			if (ar == null) return ret;
			if (ar.Count >= 2)
			{
				ret = new Size(
					ar[0].GetValue<int>(),
					ar[1].GetValue<int>()
					);
			}
			return ret;
		}
		static public SizeF? SizeFFromJson(JsonNode? jo)
		{
			SizeF? ret = null;
			if (jo == null) return ret;
			JsonArray ar = jo.AsArray();
			if (ar == null) return ret;
			if (ar.Count >= 2)
			{
				ret = new SizeF(
					ar[0].GetValue<float>(),
					ar[1].GetValue<float>()
					);
			}
			return ret;
		}
		// *********************************************************************************************************
		public void SetValue(string key, JsonNode? value)
		{
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					Obj[key] = value;
				}
				else
				{
					Obj.Add(key, value);
				}
			}
		}
		public void SetValue(string key, JsonArray? value)
		{
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					Obj[key] = value;
				}
				else
				{
					Obj.Add(key, value);
				}
			}
		}
		public void SetValue(string key, Color c)
		{
			if (Obj == null) return;
			JsonArray ja = ColorToJson(c);
			if (Obj.ContainsKey(key))
			{
				Obj[key] = ja;
			}
			else
			{
				Obj.Add(key, ja);
			}
		}
		public void SetValue(string key, Color[] c)
		{
			if (Obj == null) return;
			JsonArray ja = new JsonArray();
			if (c.Length > 0)
			{
				for (int i = 0; i < c.Length; i++)
				{
					JsonArray ja1 = ColorToJson(c[i]);
					ja.Add(ja1);
				}
			}
			if (Obj.ContainsKey(key))
			{
				Obj[key] = ja;

			}
			else
			{
				Obj.Add(key, ja);
			}
		}

		public void SetValue(string key, Point p)
		{
			if (Obj == null) return;
			JsonArray ja = PointToJson(p);
			if (Obj.ContainsKey(key))
			{
				Obj[key] = ja;

			}
			else
			{
				Obj.Add(key, ja);
			}
		}

		public void SetValue(string key, Size sz)
		{
			if (Obj == null) return;
			JsonArray ja = SizeToJson(sz);
			if (Obj.ContainsKey(key))
			{
				Obj[key] = ja;

			}
			else
			{
				Obj.Add(key, ja);
			}
		}
		public void SetValue(string key, SizeF sz)
		{
			if (Obj == null) return;
			JsonArray ja = SizeToJson(sz);
			if (Obj.ContainsKey(key))
			{
				Obj[key] = ja;

			}
			else
			{
				Obj.Add(key, ja);
			}
		}
		// ****************

		public void SetValue(string key, StringAlignment sa)
		{
			if (Obj == null) return;

			if (Obj.ContainsKey(key))
			{
				Obj[key] = (int)sa;

			}
			else
			{
				Obj.Add(key, (int)sa);
			}
		}
		// ****************
		public void SetValue(string key, string s)
		{
			if (Obj == null) return;

			/*
			if(s!="")
			{
				s = s.Replace('\\','/');
			}
			*/
			if (Obj.ContainsKey(key))
			{
				Obj[key] = (string)s;

			}
			else
			{
				Obj.Add(key, (string)s);
			}
		}
		public void SetValue(string key, AnchorStyles sa)
		{
			if (Obj == null) return;

			if (Obj.ContainsKey(key))
			{
				Obj[key] = (int)sa;

			}
			else
			{
				Obj.Add(key, (int)sa);
			}
		}
		public void SetValue(string key, DockStyle sa)
		{
			if (Obj == null) return;

			if (Obj.ContainsKey(key))
			{
				Obj[key] = (int)sa;

			}
			else
			{
				Obj.Add(key, (int)sa);
			}
		}

		public void SetValue(string key, ImeMode sa)
		{
			if (Obj == null) return;

			if (Obj.ContainsKey(key))
			{
				Obj[key] = (int)sa;

			}
			else
			{
				Obj.Add(key, (int)sa);
			}
		}
		public void SetValue(string key, Padding p)
		{
			if (Obj == null) return;
			JsonArray ja = PaddingToJson(p);
			if (Obj.ContainsKey(key))
			{
				Obj[key] = ja;

			}
			else
			{
				Obj.Add(key, ja);
			}
		}
		public void SetValue(string key, Rectangle p)
		{
			if (Obj == null) return;
			JsonArray ja = RectangleToJsonArray(p);
			if (Obj.ContainsKey(key))
			{
				Obj[key] = ja;

			}
			else
			{
				Obj.Add(key, ja);
			}
		}
		public void SetValue(string key, Font p)
		{
			if (Obj == null) return;
			JsonObject jo = new JsonObject();
			jo.Add("Name", p.Name);
			jo.Add("Size", p.Size);
			jo.Add("Style", (int)p.Style);
			if (Obj.ContainsKey(key))
			{
				Obj[key] = jo;

			}
			else
			{
				Obj.Add(key, jo);
			}
		}
		public void SetValue(string key, StringCollection sc)
		{
			if (Obj == null) return;
			JsonArray ja = new JsonArray();
			if (sc.Count > 0)
			{
				foreach (var s in sc)
				{
					if (s != null)
					{
						ja.Add(s);
					}
				}
			}

			if (Obj.ContainsKey(key))
			{
				Obj[key] = ja;

			}
			else
			{
				Obj.Add(key, ja);
			}
		}

		public void SetValue(string key, ListBox.ObjectCollection sc)
		{
			if (Obj == null) return;
			JsonArray ja = new JsonArray();
			if (sc.Count > 0)
			{
				foreach (var s in sc)
				{
					if (s != null)
					{
						ja.Add(s.ToString());
					}
				}
			}

			if (Obj.ContainsKey(key))
			{
				Obj[key] = ja;

			}
			else
			{
				Obj.Add(key, ja);
			}
		}
		// *********************************
		// *********************************
		public void SetValue(string key, string[] ary)
		{
			if (Obj == null) return;
			JsonArray ja = new JsonArray();
			if (ary.Length > 0)
			{
				foreach (string s in ary)
				{
					ja.Add(s);
				}
			}


			if (Obj.ContainsKey(key))
			{
				Obj[key] = ja;

			}
			else
			{
				Obj.Add(key, ja);
			}
		}
		public void SetValue(string key, FormBorderStyle fbs)
		{
			if (Obj == null) return;


			if (Obj.ContainsKey(key))
			{
				Obj[key] = (int)fbs;

			}
			else
			{
				Obj.Add(key, (int)fbs);
			}
		}
		// *****************************************************************************************
		//SizeGripStyle
		// *****************************************************************************************
		// *****************************************************************************************
		public object? ValueAuto(string key, string typeN)
		{
			object? ret = null;
			if (Obj == null) return ret;
			if (Obj.ContainsKey(key))
			{
				switch (typeN)
				{
					case "Color":
						ret = ValueColor(key);
						break;
					case "Point":
						ret = ValuePoint(key);
						break;
					case "Rectangle":
						ret = ValueRectangle(key);
						break;
					case "Padding":
						ret = ValuePadding(key);
						break;
					case "Size"://
						ret = ValueSize(key);
						break;
					case "SizeF"://
						ret = ValueSizeF(key);
						break;
					case "Font"://
						ret = ValueFont(key);
						break;
					case "StringCollection":
						ret = ValueStringCollection(key);
						break;
					case "HpdType":
					case "Int":
					case "Int16":
					case "Int32":
					case "ImeMode":
					case "DockStyle":
					case "StringAlignment":
					case "FormBorderStyle":
						ret = Obj[key].GetValue<int?>();
						break;
					case "Int32[]":
					case "Int32 []":
						ret = ValueIntArray(key);
						break;
					case "Double":
						ret = Obj[key].GetValue<double?>();
						break;
					case "Double[]":
					case "Double []":
						ret = ValueDoubleArray(key);
						break;
					case "Float":
						ret = Obj[key].GetValue<float?>();
						break;
					case "Float[]":
					case "Float []":
						ret = ValueFloatArray(key);
						break;
					case "String":
					case "string":
						ret = ValueStr(key);
						break;
					case "String[]":
					case "String []":
						ret = ValueStrArray(key);
						break;
					case "Boolean":
					case "Bool":
						ret = Obj[key].GetValue<bool?>();
						break;
					case "Boolean[]":
					case "Boolean []":
					case "Bool[]":
					case "Bool []":
						ret = ValueBoolArray(key);
						break;
				}

			}

			return ret;
		}
		// *****************************************************************************************
		// *****************************************************************************************
		// *****************************************************************************************
		public JsonObject? ValueObject(string key)
		{
			JsonObject? ary = null;
			if (Obj == null) return ary;
			if (Obj.ContainsKey(key))
			{
				ary = Obj[key].AsObject();
			}
			return ary;
		}       // *****************************************************************************************
		public JsonArray? ValueArray(string key)
		{
			JsonArray? ary = null;
			if (Obj == null) return ary;
			if (Obj.ContainsKey(key))
			{
				if (Obj[key] is JsonArray)
				{
					ary = Obj[key].AsArray();
				}
			}
			return ary;
		}
		public string? ValueStr(string key)
		{
			string? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					ret = Obj[key].GetValue<string?>();
				}
			}
			/*
			if((ret!=null)&&(ret!=""))
			{
				ret = ret.Replace('/', '\\');
			}
			*/
			return ret;
		}
		public string[]? ValueStrArray(string key)
		{
			string[]? ret = null;
			if (Obj != null)
			{
				JsonArray? ary = ValueArray(key);
				if ((ary != null) && (ary.Count > 0))
				{
					List<string> list = new List<string>();
					foreach (var s in ary)
					{
						string? ss = s.GetValue<string?>();
						if (ss != null)
						{
							list.Add((string)ss);
						}
						else
						{
							list.Add("");
						}
					}
					ret = list.ToArray();
				}
			}
			return ret;
		}
		public int? ValueInt(string key)
		{
			int? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					ret = Obj[key].GetValue<int?>();
				}
			}
			return ret;
		}
		public StringAlignment? ValueStringAlignment(string key)
		{
			StringAlignment? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					int? v = Obj[key].GetValue<int?>();
					if (v != null)
					{
						ret = (StringAlignment?)v;
					}
				}
			}
			return ret;
		}
		public int[]? ValueIntArray(string key)
		{
			int[]? ret = null;
			if (Obj != null)
			{
				JsonArray? ary = ValueArray(key);
				if ((ary != null) && (ary.Count > 0))
				{
					List<int> list = new List<int>();
					foreach (var s in ary)
					{
						int? ss = s.GetValue<int?>();
						if (ss != null)
						{
							list.Add((int)ss);
						}
					}
					ret = list.ToArray();
				}
			}
			return ret;
		}
		public float? ValueFloat(string key)
		{
			float? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					ret = Obj[key].GetValue<float?>();
				}
			}
			return ret;
		}
		public float[]? ValueFloatArray(string key)
		{
			float[]? ret = null;
			if (Obj != null)
			{
				JsonArray? ary = ValueArray(key);
				if ((ary != null) && (ary.Count > 0))
				{
					List<float> list = new List<float>();
					foreach (var s in ary)
					{
						float? ss = s.GetValue<float?>();
						if (ss != null)
						{
							list.Add((float)ss);
						}
					}
					ret = list.ToArray();
				}
			}
			return ret;
		}
		public double? ValueDouble(string key)
		{
			double? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					ret = Obj[key].GetValue<double?>();
				}
			}
			return ret;
		}

		public double[]? ValueDoubleArray(string key)
		{
			double[]? ret = null;
			if (Obj != null)
			{
				JsonArray? ary = ValueArray(key);
				if ((ary != null) && (ary.Count > 0))
				{
					List<double> list = new List<double>();
					foreach (var s in ary)
					{
						double? ss = s.GetValue<double?>();
						if (ss != null)
						{
							list.Add((double)ss);
						}
					}
					ret = list.ToArray();
				}
			}
			return ret;
		}
		public bool? ValueBool(string key)
		{
			bool? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					ret = Obj[key].GetValue<bool?>();
				}
			}
			return ret;
		}
		public bool[]? ValueBoolArray(string key)
		{
			bool[]? ret = null;
			if (Obj != null)
			{
				JsonArray? ary = ValueArray(key);
				if ((ary != null) && (ary.Count > 0))
				{
					List<bool> list = new List<bool>();
					foreach (var s in ary)
					{
						bool? ss = s.GetValue<bool?>();
						if (ss != null)
						{
							list.Add((bool)ss);
						}
					}
					ret = list.ToArray();
				}
			}
			return ret;
		}
		public Color? ValueColor(string key)
		{
			Color? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					JsonArray? ja = Obj[key].AsArray();
					ret = ColorFromJson(ja);
				}
			}
			return ret;
		}
		public Color[]? GetValueColorArray(string key)
		{
			Color[]? ret = null;
			if (Obj == null) return ret;
			if (Obj.ContainsKey(key))
			{
				JsonArray? ja = Obj[key].AsArray();
				if ((ja != null) && (ja.Count > 0))
				{
					List<Color> result = new List<Color>();
					foreach (var o in ja)
					{
						if ((o != null) && (o is JsonArray))
						{
							Color? cc = ColorFromJson(o);
							if (cc != null)
							{
								result.Add((Color)cc);
							}

						}
					}
					ret = result.ToArray();
				}
			}
			return ret;
		}
		// ****************************************************
		public Point? ValuePoint(string key)
		{
			Point? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					JsonArray? jo = Obj[key].AsArray();
					ret = PointFromJson(jo);

				}
			}
			return ret;
		}
		// ****************************************************
		public Size? ValueSize(string key)
		{
			Size? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					JsonArray? jo = Obj[key].AsArray();
					ret = SizeFromJson(jo);

				}
			}
			return ret;
		}
		public SizeF? ValueSizeF(string key)
		{
			SizeF? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					JsonArray? jo = Obj[key].AsArray();
					ret = SizeFFromJson(jo);

				}
			}
			return ret;
		}
		// ****************************************************
		public Padding? ValuePadding(string key)
		{
			Padding? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					JsonArray? jo = Obj[key].AsArray();
					ret = PaddingFromJson(jo);
				}
			}
			return ret;
		}
		// ****************************************************
		public Rectangle? ValueRectangle(string key)
		{
			Rectangle? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					JsonArray? jo = Obj[key].AsArray();
					ret = RectangleFromJson(jo);
				}
			}
			return ret;
		}
		// ****************************************************
		public Font? ValueFont(string key)
		{
			Font? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					JsonObject? jo = Obj[key].AsObject();
					string? n = null;
					float? sz = null;
					FontStyle? fs = null;
					string Key = "Name";
					if (jo.ContainsKey(Key))
					{
						n = jo[Key].GetValue<string?>();
					}
					Key = "Size";
					if (jo.ContainsKey(Key))
					{
						sz = jo[Key].GetValue<float?>();
					}
					Key = "Style";
					if (jo.ContainsKey(Key))
					{
						fs = (FontStyle?)jo[Key].GetValue<int?>();
					}
					if ((n != null) && (sz != null) && (fs != null))
					{
						ret = new Font(n, (float)sz, (FontStyle)fs);
					}
				}
			}
			return ret;
		}

		// ****************************************************
		public AnchorStyles? ValueAnchorStyles(string key)
		{
			AnchorStyles? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					uint? v = Obj[key].GetValue<uint?>();
					if (v != null)
					{
						ret = (AnchorStyles?)v;
					}
				}
			}
			return ret;
		}
		public DockStyle? ValueDockStyle(string key)
		{
			DockStyle? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					uint? v = Obj[key].GetValue<uint?>();
					if (v != null)
					{
						ret = (DockStyle?)v;
					}
				}
			}
			return ret;
		}
		public ImeMode? ValueImeMode(string key)
		{
			ImeMode? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					uint? v = Obj[key].GetValue<uint?>();
					if (v != null)
					{
						ret = (ImeMode?)v;
					}
				}
			}
			return ret;
		}
		public StringCollection? ValueStringCollection(string key)
		{
			StringCollection? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					JsonArray? ja = Obj[key].AsArray();
					ret = new StringCollection();
					if ((ja != null) && (ja.Count > 0))
					{
						foreach (var s in ja)
						{
							string? ss = (string?)s;
							if (s != null)
							{
								ret.Add(ss);
							}
						}
					}
				}
			}
			return ret;
		}
		public string[]? ValueObjectCollection(string key)
		{
			string[]? ret = null;
			if (Obj != null)
			{
				if (Obj.ContainsKey(key))
				{
					JsonArray? ja = Obj[key].AsArray();
					List<string> list = new List<string>();
					if ((ja != null) && (ja.Count > 0))
					{
						foreach (var s in ja)
						{
							string? ss = (string?)s;
							if (ss != null)
							{
								list.Add(ss);
							}
						}
					}
					ret = list.ToArray();
				}
			}
			return ret;
		}
		// ****************************************************

		// ****************************************************
		public JsonObject? keyValue(string key)
		{
			JsonObject? ret = null;
			if (key == "") return ret;
			try
			{
				if (Obj.ContainsKey(key))
				{
					ret = Obj[key].AsObject();
				}
			}
			catch
			{
				ret = null;
			}
			return ret;
		}


		/*
		static public void JsonSave(string path,object o)
		{
			// 自分自身をシリアライズ
			var jsonStr = JsonSerializer.Serialize(o);

			// エンコードを指定して保存
			var encoding = Encoding.GetEncoding("utf-8");
			using (var writer = new StreamWriter(path, false, encoding))
			{
				writer.WriteLine(jsonStr);
			}
		}
		*/
	}
}
