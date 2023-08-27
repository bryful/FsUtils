using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.IO.MemoryMappedFiles;

namespace LineEdit
{
	public class FsSharedMemory
	{
		private const int shared_memory_size_ = 65536 + 8;
		private string shared_memory_name = "FsSharedMemory";
		MemoryMappedFile? share_mem = null;
		MemoryMappedViewAccessor? accessor = null; 
		public bool Enabled
		{
			get { return accessor != null; }
		}
		public FsSharedMemory()
		{
			try
			{
				share_mem = MemoryMappedFile.OpenExisting(shared_memory_name);
				accessor = share_mem.CreateViewAccessor();
			}
			catch
			{
				MessageBox.Show("FsSharedMemory err");
				share_mem = null;
				accessor = null;
			}

		}
		public char[] Read()
		{
			if (accessor == null) return new char[0];
			int size = accessor.ReadInt32(0);
			if (size <= 0) return new char[0];
			int status2 = accessor.ReadInt32(sizeof(Int32));
			FSSM status = (FSSM)status2;

			if (status != FSSM.Input) return new char[0];

			char[] data = new char[size+1];
			int readsize = accessor.ReadArray<char>(sizeof(Int32)*2, data, 0, size+1);
			//for(int i = 0;i<size;i++)
			//{
				//data[i] = accessor.ReadChar(sizeof(Int32) * 2 + i);
			//}
			//data[size] = '\0';
			//MessageBox.Show($"r size{size} status:{status} ");
			if (readsize != size + 1) 
			{
				/*
				for(int i=0; i < readsize;i++)
				{
					byte c = (byte)data[i];
					c = (byte)((int)c & 0xFF);
					data[i] =  (char)c;
				}
				*/
				return new char[0];
			}
			else
			{
				return data;
			}
		}
		public void Write(char[] data,FSSM mode)
		{
			if (accessor == null) return;
			for (int i = 0; i < shared_memory_size_; i++) accessor.Write(i, '\0');
			accessor.Write(0, (Int32)data.Length);
			accessor.Write(sizeof(Int32), (Int32)mode);
			if (mode == FSSM.ResultOK)
			{
				for (int i = 0; i < data.Length; i++)
				{
					accessor.Write(sizeof(Int32) * 2 + i, data[i]);
				}

				//accessor.WriteArray<char>(sizeof(Int32) * 2, data, 0, data.Length);
			}
		}
	}
	public enum FSSM
	{
		SizeError = 0,
		Input,
		ResultOK,
		ResultCancel,
	};
}
