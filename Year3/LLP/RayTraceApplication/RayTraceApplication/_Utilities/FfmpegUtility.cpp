#include <sstream>
#include <iostream>

#include "RTAParameters.h"
#include "FFMPEGUtility.h"

void FfmpegUtility::ExecuteCompression(void)
{
	std::stringstream commandString;

	commandString << "ffmpeg -r " << RTAParameters::FramesPerSecond << " ";
	commandString << "-f image2 -s " << RTAParameters::ResolutionWidth << "x" << RTAParameters::ResolutionHeight << " ";
	commandString << "-i \"" << RTAParameters::PPMOutputPath << RTAParameters::FilenameTemplate << "%d.ppm\"";
	commandString << " -vcodec libx264 -crf 25 -pix_fmt yuv420p \"" << RTAParameters::MP4OutputPath << "VideoOutputFile.mp4\"";

#ifdef _DEBUG
	std::cout << commandString.str() << std::endl;
#endif

	std::system(commandString.str().c_str());
}