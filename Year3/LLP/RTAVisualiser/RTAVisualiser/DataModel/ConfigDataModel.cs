using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RTAVisualiser.DataModel
{
    public class ConfigDataModel
    {
        public int ResolutionWidth { get; set; } = 0;
        public int ResolutionHeight { get; set; } = 0;
        public int MaxFrames { get; set; } = 0;
        public int FramesPerSecond { get; set; } = 0;
        public int Threads { get; set; } = 0;

        public bool Parallel { get; set; } = false;
        public bool Physics { get; set; } = false;
        public bool MethodProfiling { get; set; } = false;

        public string MP4OutputPath { get; set; } = null;
        public string PPMOutputPath { get; set; } = null;
        public string ReportPath { get; set; } = null;
        public string FilenameTemplate { get; set; } = null;
    }
}
