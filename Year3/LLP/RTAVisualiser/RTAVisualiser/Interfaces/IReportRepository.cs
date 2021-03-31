using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using RTAVisualiser.DataModel;

namespace RTAVisualiser.Interfaces
{
    public interface IReportRepository
    {
        void Fetch();

        CoreDataModel GetLastRender();
        List<CoreDataModel> GetHistoricalData();
    }
}
