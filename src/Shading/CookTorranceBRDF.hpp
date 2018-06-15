
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <glm/glm.hpp>
#include "BRDF.hpp"


class CookTorranceBRDF : public BRDF
{

public:

	static float ChiPositive(float const x);
	static float G_GGX_Partial(glm::vec3 const & v, glm::vec3 const & g, glm::vec3 const & m, float const alpha);

	static float NDF_Beckmann(glm::vec3 const & H, glm::vec3 const & N, float const alpha);
	static float NDF_GGX(glm::vec3 const & H, glm::vec3 const & N, float const alpha);
	static float G_CookTorrance(glm::vec3 const & H, glm::vec3 const & N, glm::vec3 const & V, glm::vec3 const & L);
	static float G_GGX(glm::vec3 const & H, glm::vec3 const & N, glm::vec3 const & V, glm::vec3 const & L, float const alpha);
	static float F_Schlick(glm::vec3 const & H, glm::vec3 const & V, float const IOR);

	virtual glm::vec3 CalculateDiffuse(const Material & material, const SurfaceVectors & surface) const;
	virtual glm::vec3 CalculateSpecular(const Material & material, const SurfaceVectors & surface) const;

};
