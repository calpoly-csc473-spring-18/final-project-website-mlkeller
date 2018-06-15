
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "Renderer.hpp"

#include <atomic>
#include <thread>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>


void Renderer::Draw(RayTracer * rayTracer)
{
	glm::ivec2 const imageSize = rayTracer->GetParams().imageSize;
	unsigned char * imageBuffer = new unsigned char[imageSize.x * imageSize.y * 4]();

	for (int x = 0; x < imageSize.x; ++ x)
	{
		for (int y = 0; y < imageSize.y; ++ y)
		{
			Pixel p = rayTracer->CastRaysForPixel(glm::ivec2(x, y));
			imageBuffer[x * 4 + (imageSize.y - 1 - y) * 4 * imageSize.x + 0] = p.red;
			imageBuffer[x * 4 + (imageSize.y - 1 - y) * 4 * imageSize.x + 1] = p.green;
			imageBuffer[x * 4 + (imageSize.y - 1 - y) * 4 * imageSize.x + 2] = p.blue;
			imageBuffer[x * 4 + (imageSize.y - 1 - y) * 4 * imageSize.x + 3] = 255;
		}
	}

	stbi_write_png("output.png", imageSize.x, imageSize.y, 4, imageBuffer, imageSize.x * 4);
	delete[] imageBuffer;
}

void Renderer::DrawThreaded(RayTracer * rayTracer, const int numThreads)
{
	glm::ivec2 const imageSize = rayTracer->GetParams().imageSize;
	unsigned char * imageBuffer = new unsigned char[imageSize.x * imageSize.y * 4]();

	int const pixelCount = imageSize.x * imageSize.y;

	std::atomic<int> doneCount;
	std::atomic<int> currentPixel;

	doneCount = 0;
	currentPixel = 0;

	auto RenderKernel = [&](int const threadIndex)
	{
		while (true)
		{
			int pixel = currentPixel ++;

			if (pixel >= pixelCount)
			{
				break;
			}

			int const x = pixel / imageSize.y;
			int const y = pixel % imageSize.y;

			Pixel p = rayTracer->CastRaysForPixel(glm::ivec2(x, y));
			imageBuffer[x * 4 + (imageSize.y - 1 - y) * 4 * imageSize.x + 0] = p.red;
			imageBuffer[x * 4 + (imageSize.y - 1 - y) * 4 * imageSize.x + 1] = p.green;
			imageBuffer[x * 4 + (imageSize.y - 1 - y) * 4 * imageSize.x + 2] = p.blue;
			imageBuffer[x * 4 + (imageSize.y - 1 - y) * 4 * imageSize.x + 3] = 255;
		}

		doneCount ++;

		if (threadIndex == 0)
		{
			while (doneCount < numThreads)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	};

	std::vector<std::thread> threads;
	for (int i = 0; i < numThreads; ++ i)
	{
		threads.push_back(std::thread(RenderKernel, i));
	}
	for (int i = 0; i < numThreads; ++ i)
	{
		threads[i].join();
	}

	stbi_write_png("output.png", imageSize.x, imageSize.y, 4, imageBuffer, imageSize.x * 4);
	delete[] imageBuffer;
}
