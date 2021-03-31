using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using RTAVisualiser.DataModel;

namespace RTAVisualiser.Interfaces
{
    public interface IConfigDomain
    {
        void SetResolutionWidth(int width);
        void SetResolutionHeight(int height);
        void SetMaxFrames(int maxFrames);
        void SetFramesPerSecond(int fps);
        void SetThreads(int threads);
        void SetParallel(bool isConcurrent);
        void SetPhysics(bool isAnimated);
        void SetMethodProfiling(bool isAnimated);
        void SetMP4OutputPath(string path);
        void SetPPMOutputPath(string path);
        void SetReportPath(string path);
        void SetFilenameTemplate(string filename);

        int GetResolutionWidth();
        int GetResolutionHeight();
        int GetMaxFrames();
        int GetFramesPerSecond();
        int GetThreads();
        bool GetParallel();
        bool GetPhysics();
        bool GetMethodProfiling();
        string GetMP4OutputPath();
        string GetPPMOutputPath();
        string GetReportPath();
        string GetFilenameTemplate();
    }
}
