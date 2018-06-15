
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "Sphere.hpp"


Sphere::Sphere(const glm::vec3 & c, const float r)
 : center(c), radius(r)
{}

float Sphere::Intersect(const Ray & ray) const
{
	const glm::vec3 offset = ray.origin - center;

	const float a = glm::dot(ray.direction, ray.direction);
	const float b = 2.f * glm::dot(ray.direction, offset);
	const float c = glm::dot(offset, offset) - radius*radius;

	const float discriminant = b * b - 4.f * a * c;

	if (discriminant >= 0.f)
	{
		const float sqrtDiscriminant = sqrt(discriminant);

		float numerator = -b - sqrtDiscriminant;

		if (numerator < 0)
		{
			numerator = -b + sqrtDiscriminant;
		}

		const float t = numerator / (2.f * a);

		if (t >= 0.f)
		{
			return t;
		}
	}

	return -1;
}

glm::vec3 Sphere::CalculateNormal(glm::vec3 const & intersectionPoint) const
{
	return glm::normalize(intersectionPoint - center);
}

AABB Sphere::ComputeBoundingBox() const
{
	return AABB(center - glm::vec3(radius), center + glm::vec3(radius));
}

std::string Sphere::GetObjectType() const
{
	return "Sphere";
}
