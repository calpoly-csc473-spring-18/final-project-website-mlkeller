
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <ostream>
#include <glm/glm.hpp>

#include "Util.hpp"


class Ray
{

public:

	glm::vec3 origin;
	glm::vec3 direction;

	Ray()
	{
		this->origin = glm::vec3(0);
		this->direction = glm::vec3(0, 0, 1);
	}

	Ray(glm::vec3 const & origin, glm::vec3 const & direction)
	{
		this->origin = origin;
		this->direction = direction;
	}

	glm::vec3 GetPoint(const float time) const
	{
		return origin + time * direction;
	}

	Ray operator * (glm::mat4 const & m) const
	{
		Ray r;
		r.origin = glm::vec3(m * glm::vec4(origin, 1.f));
		r.direction = glm::vec3(m * glm::vec4(direction, 0.f));
		return r;
	}

	bool operator == (Ray const & other) const
	{
		return origin == other.origin && direction == other.direction;
	}

	bool operator != (Ray const & other) const
	{
		return origin != other.origin && direction != other.direction;
	}

	friend std::ostream & operator << (std::ostream & stream, Ray const & ray)
	{
		return stream << "{" << ray.origin << "} -> {" << ray.direction << "}";
	}

};
