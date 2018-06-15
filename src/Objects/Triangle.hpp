
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <Scene/Object.hpp>


class Triangle : public Object
{

public:

	Triangle(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3);
	float Intersect(const Ray & ray) const;
	glm::vec3 CalculateNormal(glm::vec3 const & intersectionPoint) const;
	AABB ComputeBoundingBox() const;
	std::string GetObjectType() const;

protected:

	glm::vec3 v1, v2, v3;
	glm::vec3 normal;

};
