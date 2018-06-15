
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <glm/glm.hpp>
#include <Scene/Object.hpp>


struct SurfaceVectors
{
	glm::vec3 light;
	glm::vec3 view;
	glm::vec3 normal;
};

class BRDF
{

public:

	virtual glm::vec3 CalculateDiffuse(Material const & material, const SurfaceVectors & surface) const = 0;
	virtual glm::vec3 CalculateSpecular(Material const & material, const SurfaceVectors & surface) const = 0;

};
