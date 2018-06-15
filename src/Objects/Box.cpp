
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "Box.hpp"

#include <glm/gtc/epsilon.hpp>


Box::Box(const glm::vec3 & a, const glm::vec3 & b)
	: aabb(a, b)
{}

float Box::Intersect(const Ray & ray) const
{
	return aabb.Intersect(ray);
}

glm::vec3 Box::CalculateNormal(glm::vec3 const & intersectionPoint) const
{
	static const float epsilon = 0.001f;

	glm::vec3 normal;

	if (glm::epsilonEqual(intersectionPoint.x, aabb.min.x, epsilon))
		normal = glm::vec3(-1, 0, 0);
	else if (glm::epsilonEqual(intersectionPoint.x, aabb.max.x, epsilon))
		normal = glm::vec3(1, 0, 0);
	else if (glm::epsilonEqual(intersectionPoint.y, aabb.min.y, epsilon))
		normal = glm::vec3(0, -1, 0);
	else if (glm::epsilonEqual(intersectionPoint.y, aabb.max.y, epsilon))
		normal = glm::vec3(0, 1, 0);
	else if (glm::epsilonEqual(intersectionPoint.z, aabb.min.z, epsilon))
		normal = glm::vec3(0, 0, -1);
	else if (glm::epsilonEqual(intersectionPoint.z, aabb.max.z, epsilon))
		normal = glm::vec3(0, 0, 1);

	return normal;
}

AABB Box::ComputeBoundingBox() const
{
	return aabb;
}

std::string Box::GetObjectType() const
{
	return "Box";
}
