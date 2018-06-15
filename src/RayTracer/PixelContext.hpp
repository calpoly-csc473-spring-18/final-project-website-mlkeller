
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "RayTraceResults.hpp"


struct PixelContext
{
	enum class IterationType
	{
		Primary = 0,
		Reflection = 1,
		Refraction = 2
	};

	struct ShadowInfo
	{
		Ray ray;
		bool hit = false;
	};

	struct Iteration
	{
		Ray ray;
		IterationType type = IterationType::Primary;

		const Object * hitObject = nullptr;
		glm::vec3 hitNormal;
		float hitTime = 0;

		RayTraceResults results;

		std::vector<ShadowInfo> shadowRays;

		glm::vec3 contributions;
		std::string extraInfo;

		Iteration * parent = nullptr;
	};

	std::vector<Iteration *> iterations;

};
