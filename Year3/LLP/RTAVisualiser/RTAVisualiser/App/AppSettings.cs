using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using RTAVisualiser.Interfaces;

namespace RTAVisualiser.App
{
    public class AppSettings : IAppSettings
    {
        public string RootReportDirectory { get; set; } = null;
        public string RepositoryLastAccess { get; set; } = null;
        public string RTAppExecutablePath { get; set; } = null;
        public string BackendConfigDirectory { get; set; } = null;
    }
}
