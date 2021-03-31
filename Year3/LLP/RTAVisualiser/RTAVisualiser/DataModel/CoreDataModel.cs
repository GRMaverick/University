using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RTAVisualiser.DataModel
{
    public class CoreDataModel
    {
        public string Name { get; set; } = "";
        public ConfigDataModel Configuration { get; set; } = null;

        public List<TimingsDataModel> FrameTimes { get; set; } = new List<TimingsDataModel>();
        public List<TimingsDataModel> ThreadTimes { get; set; } = new List<TimingsDataModel>();

        public List<MemoryDataModel> Memory { get; set; } = new List<MemoryDataModel>();
    }
}
