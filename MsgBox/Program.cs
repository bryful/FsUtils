namespace MsgBox
{
	internal static class Program
	{
		public const string Id = "MsgBox"; // GUID�Ȃǃ��j�[�N�Ȃ���
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
				//�N�����Ă��Ȃ�
				//�@�ʏ�N��
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
				//�N�����Ă���
				//MessageBox.Show("���łɋN�����Ă��܂�",
				//				Id,
				//				MessageBoxButtons.OK, MessageBoxIcon.Hand);

				PipeData pd = new PipeData(args, PIPECALL.DoubleExec);
				F_Pipe.Client(Id, pd.ToJson()).Wait();
			}
		}
	}
}