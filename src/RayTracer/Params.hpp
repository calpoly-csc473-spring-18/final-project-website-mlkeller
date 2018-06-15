
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <glm/glm.hpp>


struct Params
{
	glm::ivec2 imageSize;

	bool useShading = true;
	bool useShadows = true;
	bool useCookTorrance = false;
	bool useSoftShadows = true;

	bool useReflections = true;
	bool useRefractions = true;
	bool useFresnel = false;
	bool useBeers = false;
	bool useGI = false;

	int recursiveDepth = 6;
	int superSampling = 1;
	int shadowSample = 64;
	float lightRadius = 16;

	bool useSpatialDataStructure = false;

	bool debugNormals = false;
};
