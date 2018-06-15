
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <Scene/Object.hpp>
#include <Scene/AABB.hpp>


class Box : public Object
{

public:

	Box(const glm::vec3 & min, const glm::vec3 & max);
	float Intersect(const Ray & ray) const;
	glm::vec3 CalculateNormal(glm::vec3 const & intersectionPoint) const;
	AABB ComputeBoundingBox() const;
	std::string GetObjectType() const;

protected:

	AABB aabb;

};
