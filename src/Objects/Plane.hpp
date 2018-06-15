
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <Scene/Object.hpp>


class Plane : public Object
{

public:

	Plane(const glm::vec3 & n, const float d);
	float Intersect(const Ray & ray) const;
	glm::vec3 CalculateNormal(glm::vec3 const & intersectionPoint) const;
	AABB ComputeBoundingBox() const;
	std::string GetObjectType() const;

protected:

	glm::vec3 normal;
	float distance;

};
