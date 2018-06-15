
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <Shading/BRDF.hpp>

#include <Scene/Object.hpp>
#include <Scene/Camera.hpp>
#include <Scene/Light.hpp>
#include <Scene/Scene.hpp>

#include "PixelContext.hpp"
#include "Params.hpp"
#include "Pixel.hpp"
#include "PixelContext.hpp"
#include "RayTraceResults.hpp"



struct LightingResults
{
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class RayTracer
{

public:

	RayTracer(Scene * scene);

	void SetDebugContext(PixelContext * context);
	void SetParams(const Params & params);
	const Params & GetParams() const;


	Pixel CastRaysForPixel(const glm::ivec2 & Pixel) const;
	RayTraceResults CastRay(const Ray & ray, const int depth, const int bounce) const;
	glm::vec3 GetAmbientResults(const Object * const HhtObject, const glm::vec3 & point, const glm::vec3 & normal, const int depth, const int bounce, const glm::vec3 point1) const;
	LightingResults GetLightingResults(const Light * const light, const Material & Material, const glm::vec3 & point, const glm::vec3 & view, const glm::vec3 & normal) const;
	glm::vec3 GetReflectionResults(int bounce, const glm::vec3 & point, const glm::vec3 & reflection, const int depth, PixelContext::Iteration * currentIteration = nullptr) const;
	glm::vec3 GetRefractionResults(int bounce, const Material & material, const glm::vec3 & point, const glm::vec3 & transmissionVector, const bool entering, const int depth, PixelContext::Iteration * currentIteration = nullptr) const;
	std::vector<glm::vec3> Generate_Hemisphere_Sample_Points(int reccount,const glm::vec3 & normal) const;
	glm::vec3 Generate_Cosine_Weighted_Point(const float u, const float v) const;
	glm::vec3 AlignSampleVector(glm::vec3 sample, glm::vec3 up, const glm::vec3 & normal) const;

	static glm::vec3 CalculateRefractionVector(const glm::vec3 & view, glm::vec3 normal, const float ior);

protected:

	Params params;
	Scene * scene = nullptr;
	BRDF * brdf = nullptr;

	PixelContext * context = nullptr;

	const float reflectionEpsilon = 0.001f;
	const float refractionEpsilon = 0.001f;

};
