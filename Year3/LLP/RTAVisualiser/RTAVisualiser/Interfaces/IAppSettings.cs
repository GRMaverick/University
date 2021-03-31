using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RTAVisualiser.Interfaces
{
    public interface IAppSettings
    {
        string RootReportDirectory { get; set; }
        string RTAppExecutablePath { get; set; }
        string BackendConfigDirectory { get; set; }
        string RepositoryLastAccess { get; set; }
    }
}
