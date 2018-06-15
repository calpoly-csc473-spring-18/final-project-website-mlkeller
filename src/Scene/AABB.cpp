
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "AABB.hpp"


AABB::AABB()
{
	min = glm::vec3(std::numeric_limits<float>::max());
	max = glm::vec3(std::numeric_limits<float>::lowest());
}

AABB::AABB(const glm::vec3 & pt)
{
	min = max = pt;
}

AABB::AABB(const glm::vec3 & min, const glm::vec3 & max)
{
	this->min = min;
	this->max = max;
}

void AABB::Reset(const::glm::vec3 & pt)
{
	min = max = pt;
}

void AABB::AddPoint(const::glm::vec3 & pt)
{
	min.x = glm::min(min.x, pt.x);
	min.y = glm::min(min.y, pt.y);
	min.z = glm::min(min.z, pt.z);
	max.x = glm::max(max.x, pt.x);
	max.y = glm::max(max.y, pt.y);
	max.z = glm::max(max.z, pt.z);
}

void AABB::AddBox(const AABB & other)
{
	min.x = glm::min(min.x, other.min.x);
	min.y = glm::min(min.y, other.min.y);
	min.z = glm::min(min.z, other.min.z);
	max.x = glm::max(max.x, other.max.x);
	max.y = glm::max(max.y, other.max.y);
	max.z = glm::max(max.z, other.max.z);
}

float AABB::Intersect(const Ray & ray) const
{
	float largestMin = std::numeric_limits<float>::lowest();
	float smallestMax = std::numeric_limits<float>::max();

	for (int i = 0; i < 3; ++ i)
	{
		if (ray.direction[i] == 0)
		{
			if (ray.origin[i] < min[i] || ray.origin[i] > max[i])
			{
				return -1;
			}
		}
		else
		{
			float tmin = (min[i] - ray.origin[i]) / ray.direction[i];
			float tmax = (max[i] - ray.origin[i]) / ray.direction[i];

			if (tmin > tmax)
				std::swap(tmin, tmax);

			largestMin = glm::max(tmin, largestMin);
			smallestMax = glm::min(tmax, smallestMax);
		}
	}

	if (largestMin > smallestMax)
		return -1;

	if (smallestMax < 0)
		return -1;

	if (largestMin > 0)
		return largestMin;
	else
		return smallestMax;
}

glm::vec3 AABB::GetCenter() const
{
	return (max + min) / 2.f;
}

void AABB::Transform(const glm::mat4 & m)
{
	glm::vec3 vertices[8] =
	{
		glm::vec3(min.x, min.y, min.z),
		glm::vec3(max.x, min.y, min.z),
		glm::vec3(min.x, max.y, min.z),
		glm::vec3(max.x, max.y, min.z),
		glm::vec3(min.x, min.y, max.z),
		glm::vec3(max.x, min.y, max.z),
		glm::vec3(min.x, max.y, max.z),
		glm::vec3(max.x, max.y, max.z)
	};

	for (int i = 0; i < 8; ++ i)
	{
		vertices[i] = glm::vec3(m * glm::vec4(vertices[i], 1.f));
	}

	Reset(vertices[0]);
	for (int i = 1; i < 8; ++ i)
	{
		AddPoint(vertices[i]);
	}
}
