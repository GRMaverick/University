using Unity;

using Newtonsoft.Json;

using RTAVisualiser.Forms;
using RTAVisualiser.Mapper;
using RTAVisualiser.Interfaces;
using RTAVisualiser.Repositories;

using System;
using System.Windows.Forms;

namespace RTAVisualiser.App
{
    public static class AppBuilder
    {
        public static IUnityContainer Configure()
        {
            UnityContainer container = new UnityContainer();

            container.RegisterType<IReportRepository, ReportRepositoryCSV>()
                .RegisterType<Form, MainForm>("MainForm")
                .RegisterType<IConfigDomain, ConfigDomain>()
                .RegisterType<IReportMapper, ReportMapper>()
                .RegisterType<IConfigRepository, ConfigRepositoryCSV>()
                .RegisterType<ITerminalInstruction, Raytracer>("Raytracer")
                .RegisterType<ITerminalInstruction, MagickImageProcessor>("Magick")
                .RegisterInstance<IAppSettings>(GetAppSettings());

            return container;
        }
        public static IAppSettings GetAppSettings()
        {
            try
            {
                string data = null;
                using (System.IO.StreamReader appSettingsFile = new System.IO.StreamReader(@"Config\AppSettings.json"))
                {
                    data = appSettingsFile.ReadToEnd();
                    appSettingsFile.Close();
                }
                return JsonConvert.DeserializeObject<AppSettings>(data);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"CSVRepository FAILED: {ex.Message} \n {ex.StackTrace}");
                return null;
            }
        }
    }
}
