
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <ostream>
#include <glm/glm.hpp>

#include <RayTracer/Util.hpp>
#include <RayTracer/Ray.hpp>


class AABB
{

public:

	AABB();
	AABB(const glm::vec3 & pt);
	AABB(const glm::vec3 & min, const glm::vec3 & max);

	void Reset(const glm::vec3 & pt);
	void AddPoint(const glm::vec3 & pt);
	void AddBox(const AABB & other);

	float Intersect(const Ray & ray) const;
	glm::vec3 GetCenter() const;

	void Transform(const glm::mat4 & m);

	glm::vec3 min, max;

};
