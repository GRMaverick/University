using System;
using System.Windows.Forms;

using Unity;
using RTAVisualiser.App;

namespace RTAVisualiser
{
    static class Program
    {
        private readonly static IUnityContainer appBuilder = AppBuilder.Configure();
        
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(appBuilder.Resolve<Form>("MainForm"));
        }
    }
}
