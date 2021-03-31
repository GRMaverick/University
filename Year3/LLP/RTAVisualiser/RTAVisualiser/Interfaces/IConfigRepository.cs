using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using RTAVisualiser.DataModel;

namespace RTAVisualiser.Interfaces
{
    public interface IConfigRepository
    {
        void SetConfiguration(ConfigDataModel cdm);
        ConfigDataModel GetConfiguration();
    }
}
