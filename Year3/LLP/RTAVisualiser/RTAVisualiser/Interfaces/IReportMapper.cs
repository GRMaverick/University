using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LiveCharts;
using LiveCharts.Wpf;
using LiveCharts.Defaults;
using LiveCharts.WinForms;

namespace RTAVisualiser.Interfaces
{
    public interface IReportMapper
    {
        void Update();

        SeriesCollection InitialiseFrameTimeCollection();
        SeriesCollection InitialiseThreadTimeCollection();

        SeriesCollection InitialiseMemoryCollection();
        SeriesCollection InitialiseAllMethodsCollection();
    }
}
