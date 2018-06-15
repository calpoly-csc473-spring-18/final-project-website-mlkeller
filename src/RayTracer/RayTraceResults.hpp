
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <glm/vec3.hpp>


struct RayTraceResults
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 reflection;
	glm::vec3 refraction;
	glm::vec3 intersectionPoint;

	glm::vec3 ToColor() const
	{
		return ambient + diffuse + specular + reflection + refraction;
	}
};
