using BRY;

namespace FrameInput
{
	internal static class Program
	{
		public const string Id = "LineEdit"; // GUIDÇ»Ç«ÉÜÉjÅ[ÉNÇ»Ç‡ÇÃ
		private static System.Threading.Mutex _mutex = new System.Threading.Mutex(false, Id);
		/// <summary>
		///  The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{

			ApplicationConfiguration.Initialize();
			FrameInput mf = new FrameInput();
			Application.Run(mf);

		}
	}
}