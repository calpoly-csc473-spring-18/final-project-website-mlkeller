
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <RayTracer/RayTracer.hpp>


class Renderer
{

public:

	static void Draw(RayTracer * rayTracer);
	static void DrawThreaded(RayTracer * rayTracer, const int numThreads);

};
