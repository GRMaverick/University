using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RTAVisualiser.DataModel
{
    public class MemoryDataModel
    {
        public string Name { get; set; } = string.Empty;
        public int Frame { get; set; } = 0;
        public int SizeUtilised { get; set; } = 0;
        public int SizeAllocated { get; set; } = 0;
        public int PeakSizeUtilised { get; set; } = 0;
        public int NumberOfAllocations { get; set; } = 0;
    }
}
