using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using RTAVisualiser.Interfaces;
using RTAVisualiser.DataModel;

namespace RTAVisualiser.Mapper
{
    public class ConfigDomain : IConfigDomain
    {
        private ConfigDataModel Configuration { get; set; } = null;
        private IConfigRepository Repository { get; set; } = null;

        public ConfigDomain(IConfigRepository repo)
        {
            Repository = repo;
            Configuration = Repository.GetConfiguration();
        }
        private void Push()
        {
            Repository.SetConfiguration(Configuration);
        }

        public void SetResolutionWidth(int width)
        {
            Configuration.ResolutionWidth = width;
            Repository.SetConfiguration(Configuration);
        }
        public void SetResolutionHeight(int height)
        {
            Configuration.ResolutionHeight = height;
            Repository.SetConfiguration(Configuration);
        }
        public void SetMaxFrames(int maxFrames)
        {
            Configuration.MaxFrames = maxFrames;
            Repository.SetConfiguration(Configuration);
        }
        public void SetFramesPerSecond(int fps)
        {
            Configuration.FramesPerSecond = fps;
            Repository.SetConfiguration(Configuration);
        }
        public void SetThreads(int threads)
        {
            Configuration.Threads = threads;
            Repository.SetConfiguration(Configuration);
        }
        public void SetParallel(bool isConcurrent)
        {
            Configuration.Parallel = isConcurrent;
            Repository.SetConfiguration(Configuration);
        }
        public void SetPhysics(bool isAnimated)
        {
            Configuration.Physics = isAnimated;
            Repository.SetConfiguration(Configuration);
        }
        public void SetMethodProfiling(bool isProfiling)
        {
            Configuration.MethodProfiling = isProfiling;
            Repository.SetConfiguration(Configuration);
        }
        public void SetMP4OutputPath(string path)
        {
            Configuration.MP4OutputPath = path;
            Repository.SetConfiguration(Configuration);
        }
        public void SetPPMOutputPath(string path)
        {
            Configuration.PPMOutputPath = path;
            Repository.SetConfiguration(Configuration);
        }
        public void SetReportPath(string path)
        {
            Configuration.ReportPath = path;
            Repository.SetConfiguration(Configuration);
        }
        public void SetFilenameTemplate(string filename)
        {
            Configuration.FilenameTemplate = filename;
            Repository.SetConfiguration(Configuration);
        }



        public int GetResolutionWidth()
        {
            return Configuration.ResolutionWidth;
        }
        public int GetResolutionHeight()
        {
            return Configuration.ResolutionHeight;
        }
        public int GetMaxFrames()
        {
            return Configuration.MaxFrames;
        }
        public int GetFramesPerSecond()
        {
            return Configuration.FramesPerSecond;
        }
        public int GetThreads()
        {
            return Configuration.Threads;
        }
        public bool GetParallel()
        {
            return Configuration.Parallel;
        }
        public bool GetPhysics()
        {
            return Configuration.Physics;
        }
        public bool GetMethodProfiling()
        {
            return Configuration.MethodProfiling;
        }
        public string GetMP4OutputPath()
        {
            return Configuration.MP4OutputPath;
        }
        public string GetPPMOutputPath()
        {
            return Configuration.PPMOutputPath;
        }
        public string GetReportPath()
        {
            return Configuration.ReportPath;
        }
        public string GetFilenameTemplate()
        {
            return Configuration.FilenameTemplate;
        }
    }
}
