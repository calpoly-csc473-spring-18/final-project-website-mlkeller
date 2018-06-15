
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <Scene/Object.hpp>


class Sphere : public Object
{

public:

	Sphere(const glm::vec3 & c, const float r);
	float Intersect(const Ray & ray) const;
	glm::vec3 CalculateNormal(glm::vec3 const & intersectionPoint) const;
	AABB ComputeBoundingBox() const;
	std::string GetObjectType() const;

protected:

	float radius;
	glm::vec3 center;

};
