namespace MsgBox
{
	internal static class Program
	{
		public const string Id = "MsgBox"; // GUIDなどユニークなもの
		private static System.Threading.Mutex _mutex = new System.Threading.Mutex(false, Id);
		/// <summary>
		///  The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			bool IsRunning = (_mutex.WaitOne(0, false)) == false;

			if (IsRunning == false)
			{
				//起動していない
				//　通常起動
				// To customize application configuration such as set high DPI settings or default font,
				// see https://aka.ms/applicationconfiguration.
				ApplicationConfiguration.Initialize();
				MsgBox mf = new MsgBox();
				mf.StartServer(Id);
				Application.Run(mf);
				mf.StopServer();
			}
			else
			{
				//起動している
				//MessageBox.Show("すでに起動しています",
				//				Id,
				//				MessageBoxButtons.OK, MessageBoxIcon.Hand);

				PipeData pd = new PipeData(args, PIPECALL.DoubleExec);
				F_Pipe.Client(Id, pd.ToJson()).Wait();
			}
		}
	}
}