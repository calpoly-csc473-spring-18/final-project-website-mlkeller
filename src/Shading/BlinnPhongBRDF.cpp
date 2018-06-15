
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "BlinnPhongBRDF.hpp"


glm::vec3 BlinnPhongBRDF::CalculateDiffuse(const Material & material, const SurfaceVectors & surface) const
{
	return glm::vec3(glm::clamp(glm::dot(surface.normal, surface.light), 0.f, 1.f));
}

glm::vec3 BlinnPhongBRDF::CalculateSpecular(const Material & material, const SurfaceVectors & surface) const
{
	const glm::vec3 half = glm::normalize(surface.light + surface.view);
	const float power = (2.f / (material.finish.roughness * material.finish.roughness) - 2.f);

	return glm::vec3(glm::pow(glm::clamp(glm::dot(surface.normal, half), 0.f, 1.f), power));
}
