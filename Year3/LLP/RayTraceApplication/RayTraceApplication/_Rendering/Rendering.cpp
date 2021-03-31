#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Timer.h"
#include "Defines.h"
#include "Tracing.h"
#include "Rendering.h"
#include "TimerManager.h"
#include "MethodProfiler.h"
#include "RTAParameters.h"

// Cheers mate :D  np haha

float Renderer::Angle = 0.0f;
float Renderer::FieldOfView = 0.0f;
float Renderer::AspectRatio = 0.0f;
float Renderer::InverseWidth = 0.0f;
float Renderer::InverseHeight = 0.0f;

void Renderer::Shutdown(void)
{
}
void Renderer::BaselineRender(const std::vector<Sphere>& spheres, int iteration)
{
	unsigned width = RTAParameters::ResolutionWidth;
	unsigned height = RTAParameters::ResolutionHeight;

	Vector3* image = new Vector3[width * height];
	Vector3* pixel = image;

	float invWidth = 1 / float(width);
	float invHeight = 1 / float(height);
	float fov = 30;
	float aspectratio = width / float(height);
	float angle = tan(M_PI * 0.5 * fov / 180.0);

	// Trace rays
	for (unsigned y = 0; y < height; ++y)
	{
		for (unsigned x = 0; x < width; ++x, ++pixel)
		{
			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;

			Vector3 raydir = Vector3(xx, yy, -1).Normalise();

			*pixel = Tracing::BaselineTrace(Vector3(0), raydir, spheres, 0);
		}
	}

	// Save result to a PPM image (keep these flags if you compile under Windows)
	std::stringstream ss;
	ss << RTAParameters::PPMOutputPath << RTAParameters::FilenameTemplate << iteration << ".ppm";
	std::string tempString = ss.str();
	char* filename = (char*)tempString.c_str();

	std::ofstream ofs(filename, std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (unsigned i = 0; i < width * height; ++i)
	{
		ofs << (unsigned char)(std::min(float(1), image[i].x) * 255) << (unsigned char)(std::min(float(1), image[i].y) * 255) << (unsigned char)(std::min(float(1), image[i].z) * 255);
	}

	ofs.close();

	delete[] image;
}
void Renderer::Render(Sphere* spheres[], int sphereCount, int iteration)
{
	MethodProfiler::StartTracking(std::string(__FUNCTION__), std::string("Render_" + std::to_string(iteration)), iteration);
	{
		unsigned width = RTAParameters::ResolutionWidth;
		unsigned height = RTAParameters::ResolutionHeight;

		Vector3* image = new Vector3[width * height];
		Vector3* pixel = image;

		float invWidth = 1 / float(width);
		float invHeight = 1 / float(height);
		float fov = 30;
		float aspectratio = width / float(height);
		float angle = tan(M_PI * 0.5 * fov / 180.0);

		TimerManager::Instance()->GetTimer("Frames")->StartTracking("Frame_" + std::to_string(iteration), iteration);
		{
			for (unsigned y = 0; y < height; ++y)
			{
				for (unsigned x = 0; x < width; ++x, ++pixel)
				{
					float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
					float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;

					Vector3 raydir = Vector3(xx, yy, -1).Normalise();

					*pixel = Tracing::Trace(Vector3(0), raydir, spheres, sphereCount, 0, iteration);
				}
			}
		}

		TimerManager::Instance()->GetTimer("Frames")->EndTracking("Frame_" + std::to_string(iteration));

		std::cout << ">> Frame " << iteration << ": Sequential Renderer complete - Execution Time: " << TimerManager::Instance()->GetTimer("Frames")->GetExecutionTime("Frame_" + std::to_string(iteration)) << std::endl;
		std::cout << ">> Writing " << RTAParameters::FilenameTemplate << iteration << ".ppm" << std::endl;

		//TimerManager::Instance()->GetTimer("FileIO")->StartTracking("Frame_" + std::to_string(iteration), iteration);

		{
			std::string fileString = RTAParameters::PPMOutputPath + RTAParameters::FilenameTemplate + std::to_string(iteration) + ".ppm";
			std::ofstream ofs(fileString.c_str(), std::ios::out | std::ios::binary);
			if (ofs.is_open())
			{
				ofs << "P6\n" << RTAParameters::ResolutionWidth << " " << RTAParameters::ResolutionHeight << "\n255\n";
				for (unsigned i = 0; i < RTAParameters::ResolutionWidth * RTAParameters::ResolutionHeight; ++i)
				{
					ofs << (unsigned char)(std::min(float(1), image[i].x) * 255) << (unsigned char)(std::min(float(1), image[i].y) * 255) << (unsigned char)(std::min(float(1), image[i].z) * 255);
				}
				ofs.close();
			}
			else
			{
				std::cout << fileString.c_str() << ": File IO FAILED!" << std::endl;
			}
			std::cout << ">> " << RTAParameters::FilenameTemplate << iteration << ".ppm file written" << std::endl << std::endl;
		}

		//TimerManager::Instance()->GetTimer("FileIO")->EndTracking("Frame_" + std::to_string(iteration));

		delete[] image;
	}
	MethodProfiler::EndTracking(std::string(__FUNCTION__), std::string("Render_" + std::to_string(iteration)));
}

void Renderer::ParallelRender(Sphere* spheres[], int sphereCount, int iteration, int threads)
{

	if (RTAParameters::MethodProfiling)
		MethodProfiler::StartTracking(std::string(__FUNCTION__), std::string("Render_" + std::to_string(iteration)), iteration);

	{
		Vector3* image = new Vector3[RTAParameters::ResolutionWidth * RTAParameters::ResolutionHeight];
		Vector3* pixel = image;

		InverseWidth = 1 / float(RTAParameters::ResolutionWidth);
		InverseHeight = 1 / float(RTAParameters::ResolutionHeight);
		FieldOfView = 30;
		AspectRatio = RTAParameters::ResolutionWidth / float(RTAParameters::ResolutionHeight);
		Angle = tan(M_PI * 0.5 * FieldOfView / 180.0);

		int startHeight = 0;
		int heightPerThread = (RTAParameters::ResolutionHeight) / threads;

		TimerManager::Instance()->GetTimer("Frames")->StartTracking("Frame_" + std::to_string(iteration), iteration);

		{
			std::thread* threadArray = new std::thread[threads - 1];
			for (int thread = 0; thread < threads - 1; thread++)
			{
#ifdef _DEBUG
				std::cout << ">> Executing Render Thread: " << thread + 1 << std::endl;
#endif

				int endHeight = startHeight + heightPerThread;
				threadArray[thread] = std::thread(RenderThread, thread + 1, startHeight, endHeight, pixel, spheres, sphereCount, iteration);

				startHeight = endHeight;
			}
#ifdef _DEBUG
			std::cout << ">> Executing Main Thread: " << std::endl;
#endif

			std::string threadTimerID = "RenderThread_0." + std::to_string(iteration);
			TimerManager::Instance()->GetTimer("RenderThreads")->StartTracking(threadTimerID, iteration);
			{
				for (unsigned y = 0; y < RTAParameters::ResolutionHeight; ++y)
				{
					for (unsigned x = 0; x < RTAParameters::ResolutionWidth; ++x, ++pixel)
					{
						if ((y >= startHeight) && (y < (startHeight + heightPerThread)))
						{
							float xx = (2 * ((x + 0.5) * InverseWidth) - 1) * Angle * AspectRatio;
							float yy = (1 - 2 * ((y + 0.5) * InverseHeight)) * Angle;

							Vector3 raydir = Vector3(xx, yy, -1).Normalise();

							*pixel = Tracing::Trace(Vector3(0), raydir, spheres, sphereCount, 0, iteration);
						}
					}
				}
			}
			TimerManager::Instance()->GetTimer("RenderThreads")->EndTracking(threadTimerID);

			for (int i = 0; i < threads - 1; i++)
			{
				threadArray[i].join();
			}
		}
		
		TimerManager::Instance()->GetTimer("Frames")->EndTracking("Frame_" + std::to_string(iteration));

		std::cout << ">> Frame " << iteration << ": Render Threads complete - Execution Time: " << TimerManager::Instance()->GetTimer("Frames")->GetExecutionTime("Frame_" + std::to_string(iteration)) << std::endl;
#ifdef _DEBUG
		std::cout << ">> Writing " << RTAParameters::FilenameTemplate << iteration << ".ppm" << std::endl;
#endif
		//TimerManager::Instance()->GetTimer("FileIO")->StartTracking("Frame_" + std::to_string(iteration), iteration);
		{
			std::string fileString = RTAParameters::PPMOutputPath + RTAParameters::FilenameTemplate + std::to_string(iteration) + ".ppm";
			std::ofstream ofs(fileString.c_str(), std::ios::out | std::ios::binary);
			if (ofs.is_open())
			{
				ofs << "P6\n" << RTAParameters::ResolutionWidth << " " << RTAParameters::ResolutionHeight << "\n255\n";
				for (unsigned i = 0; i < RTAParameters::ResolutionWidth * RTAParameters::ResolutionHeight; ++i)
				{
					ofs << (unsigned char)(std::min(float(1), image[i].x) * 255) << (unsigned char)(std::min(float(1), image[i].y) * 255) << (unsigned char)(std::min(float(1), image[i].z) * 255);
				}
				ofs.close();
			}
			else
			{
				std::cout << fileString.c_str() << ": File IO FAILED!" << std::endl;
			}
			std::cout << ">> " << RTAParameters::FilenameTemplate << iteration << ".ppm file written" << std::endl << std::endl;
		}
		//TimerManager::Instance()->GetTimer("FileIO")->EndTracking("Frame_" + std::to_string(iteration));

		delete[] image;
	}

	if (RTAParameters::MethodProfiling)
		MethodProfiler::EndTracking(std::string(__FUNCTION__), std::string("Render_" + std::to_string(iteration)));
}
void Renderer::RenderThread(int threadID, int start, int end, Vector3* pixel, Sphere* spheres[], int sphereCount, int iteration)
{
	std::string threadTimerID = "RenderThread_" + std::to_string(threadID) + "." + std::to_string(iteration);
	TimerManager::Instance()->GetTimer("RenderThreads")->StartTracking(threadTimerID, iteration);
	for (unsigned y = 0; y < RTAParameters::ResolutionHeight; ++y)
	{
		for (unsigned x = 0; x < RTAParameters::ResolutionWidth; ++x, ++pixel)
		{
			if ((y >= start) && (y < end))
			{
				float xx = (2 * ((x + 0.5) * InverseWidth) - 1) * Angle * AspectRatio;
				float yy = (1 - 2 * ((y + 0.5) * InverseHeight)) * Angle;

				Vector3 raydir = Vector3(xx, yy, -1).Normalise();

				*pixel = Tracing::Trace(Vector3(0), raydir, spheres, sphereCount, 0, iteration);
			}
		}
	}
	TimerManager::Instance()->GetTimer("RenderThreads")->EndTracking(threadTimerID);
//#ifdef _DEBUG
	std::cout << ">> RenderThread_" << threadID << ": Execution Time: " << TimerManager::Instance()->GetTimer("RenderThreads")->GetExecutionTime(threadTimerID) << std::endl;
//#endif
}

