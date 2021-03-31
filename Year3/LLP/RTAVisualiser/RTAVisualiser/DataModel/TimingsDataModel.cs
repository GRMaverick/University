using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RTAVisualiser.DataModel
{
    public class TimingsDataModel
    {
        public string Name { get; set; } = string.Empty;
        public int Frame { get; set; } = 0;
        public double Duration { get; set; } = 0.0;
    }
}
