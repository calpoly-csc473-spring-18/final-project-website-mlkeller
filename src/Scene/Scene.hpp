
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <glm/glm.hpp>

#include "Object.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "BoundingVolumeNode.hpp"

#include <RayTracer/PixelContext.hpp>


struct RayHitResults
{
	float t = 0;
	glm::vec3 point;
	glm::vec3 normal;
	const Object * object = nullptr;
};

class Scene
{

	// non-copyable
	Scene(const Scene &) = delete;
	Scene & operator =(const Scene &) = delete;

public:

	Scene() = default;

	Object * AddObject(Object * object);
	Light * AddLight(Light * light);

	const std::vector<Object *> & GetObjects() const;
	const std::vector<Light *> & GetLights() const;

	const Camera & GetCamera() const;
	Camera & GetCamera();

	bool IsLightOccluded(const glm::vec3 & point, const glm::vec3 & lightPosition, PixelContext::Iteration * currentIteration = nullptr) const;
	RayHitResults GetRayHitResults(const Ray & ray) const;
	void BuildSpatialDataStructure();
	BoundingVolumeNode * GetSpatialDataStructure();

protected:

	Camera camera;

	std::vector<Object *> objects;
	std::vector<Light *> lights;

	BoundingVolumeNode * spatialDataStructure = nullptr;

};
