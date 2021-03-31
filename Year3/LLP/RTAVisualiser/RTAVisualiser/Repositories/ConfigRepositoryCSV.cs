using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using RTAVisualiser.Interfaces;
using RTAVisualiser.DataModel;

namespace RTAVisualiser.Repositories
{
    public class ConfigRepositoryCSV : IConfigRepository
    {
        public IAppSettings AppSettings { get; set; } = null;

        public ConfigRepositoryCSV(IAppSettings settings)
        {
            AppSettings = settings;
        }

        public void SetConfiguration(ConfigDataModel cdm)
        {
            try
            {
                System.IO.StreamWriter configWriter = new System.IO.StreamWriter(AppSettings.BackendConfigDirectory + "BackendConfiguration.txt");
                configWriter.WriteLine($"ResolutionWidth\t{cdm.ResolutionWidth}");
                configWriter.WriteLine($"ResolutionHeight\t{cdm.ResolutionHeight}");
                configWriter.WriteLine($"FPS\t{cdm.FramesPerSecond}");
                configWriter.WriteLine($"MaxFrames\t{cdm.MaxFrames}");
                configWriter.WriteLine($"MP4OutputPath\t{cdm.MP4OutputPath}");
                configWriter.WriteLine($"PPMOutputPath\t{cdm.PPMOutputPath}");
                configWriter.WriteLine($"ReportPath\t{cdm.ReportPath}");
                configWriter.WriteLine($"FilenameTemplate\t{cdm.FilenameTemplate}");
                configWriter.WriteLine($"Parallel\t{cdm.Parallel}");
                configWriter.WriteLine($"Threads\t{cdm.Threads}");
                configWriter.WriteLine($"Physics\t{cdm.Physics}");
                configWriter.WriteLine($"MethodProfiling\t{cdm.MethodProfiling}");
                configWriter.Close();

                System.IO.StreamWriter configPreviewWriter = new System.IO.StreamWriter(AppSettings.BackendConfigDirectory + "PreviewBackendConfiguration.txt");
                configPreviewWriter.WriteLine($"ResolutionWidth\t{cdm.ResolutionWidth}");
                configPreviewWriter.WriteLine($"ResolutionHeight\t{cdm.ResolutionHeight}");
                configPreviewWriter.WriteLine($"FPS\t{cdm.FramesPerSecond}");
                configPreviewWriter.WriteLine($"MaxFrames\t1");
                configPreviewWriter.WriteLine($"MP4OutputPath\t{cdm.MP4OutputPath}");
                configPreviewWriter.WriteLine($"PPMOutputPath\t{cdm.PPMOutputPath}");
                configPreviewWriter.WriteLine($"ReportPath\t{cdm.ReportPath}");
                configPreviewWriter.WriteLine($"FilenameTemplate\t{cdm.FilenameTemplate}");
                configPreviewWriter.WriteLine($"Parallel\tFalse");
                configPreviewWriter.WriteLine($"Threads\t1");
                configPreviewWriter.WriteLine($"Physics\t{cdm.Physics}");
                configPreviewWriter.WriteLine($"MethodProfiling\t{cdm.MethodProfiling}");
                configPreviewWriter.Close();
            }
            catch(Exception ex)
            {
                Console.WriteLine($"ConfigRepositoryCSV Writing FAILED: {ex.Message} \n {ex.StackTrace}");
                return;
            }
        }
        public ConfigDataModel GetConfiguration()
        {
            try
            {
                ConfigDataModel cdm = new ConfigDataModel();
                using (System.IO.StreamReader reader = new System.IO.StreamReader(AppSettings.BackendConfigDirectory + "BackendConfiguration.txt"))
                {
                    string line = reader.ReadLine();
                    while (line != null)
                    {
                        //Console.WriteLine(line);
                        string[] columns = line.Split('\t');

                        if(columns[0] == "ResolutionWidth")
                        {
                            cdm.ResolutionWidth = Convert.ToInt32(columns[1]);
                        }
                        else if (columns[0] == "ResolutionHeight")
                        {
                            cdm.ResolutionHeight = Convert.ToInt32(columns[1]);
                        }
                        else if (columns[0] == "FPS")
                        {
                            cdm.FramesPerSecond = Convert.ToInt32(columns[1]);
                        }
                        else if (columns[0] == "MaxFrames")
                        {
                            cdm.MaxFrames = Convert.ToInt32(columns[1]);
                        }
                        else if (columns[0] == "MP4OutputPath")
                        {
                            cdm.MP4OutputPath = columns[1];
                        }
                        else if (columns[0] == "PPMOutputPath")
                        {
                            cdm.PPMOutputPath = columns[1];
                        }
                        else if (columns[0] == "ReportPath")
                        {
                            cdm.ReportPath = columns[1];
                        }
                        else if (columns[0] == "FilenameTemplate")
                        {
                            cdm.FilenameTemplate = columns[1];
                        }
                        else if (columns[0] == "Parallel")
                        {
                            cdm.Parallel = Convert.ToBoolean(columns[1]);
                        }
                        else if (columns[0] == "Threads")
                        {
                            cdm.Threads = Convert.ToInt32(columns[1]);
                        }
                        else if (columns[0] == "Physics")
                        {
                            cdm.Physics = Convert.ToBoolean(columns[1]);
                        }
                        else if (columns[0] == "MethodProfiling")
                        {
                            cdm.MethodProfiling = Convert.ToBoolean(columns[1]);
                        }

                        line = reader.ReadLine();
                    }

                    reader.Close();
                }
                return cdm;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"ConfigRepositoryCSV Reading FAILED: {ex.Message} \n {ex.StackTrace}");
                return null;
            }
        }
    }
}
