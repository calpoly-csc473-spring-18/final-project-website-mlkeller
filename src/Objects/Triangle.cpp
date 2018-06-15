
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "Triangle.hpp"


Triangle::Triangle(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
}

float Triangle::Intersect(const Ray & ray) const
{
	const glm::vec3 abc = v1 - v2;
	const glm::vec3 def = v1 - v3;
	const glm::vec3 ghi = ray.direction;
	const glm::vec3 jkl = v1 - ray.origin;

	const float ei_hf = def.y * ghi.z - ghi.y * def.z;
	const float gf_di = ghi.x * def.z - def.x * ghi.z;
	const float dh_eg = def.x * ghi.y - def.y * ghi.x;

	const float denom = abc.x * ei_hf + abc.y * gf_di + abc.z * dh_eg;

	if (denom == 0.f)
		return -1;

	const float beta = (jkl.x * ei_hf + jkl.y * gf_di + jkl.z * dh_eg) / denom;

	if (beta < 0 || beta > 1)
		return -1;

	const float ak_jb = abc.x * jkl.y - jkl.x * abc.y;
	const float jc_al = jkl.x * abc.z - abc.x * jkl.z;
	const float bl_kc = abc.y * jkl.z - jkl.y * abc.z;

	const float gamma = (ghi.z * ak_jb + ghi.y * jc_al + ghi.x * bl_kc) / denom;

	if (gamma < 0 || gamma > 1 - beta)
		return -1;

	const float t = (-def.z * ak_jb + -def.y * jc_al + -def.x * bl_kc) / denom;

	if (t < 0)
		return -1;

	return t;
}

glm::vec3 Triangle::CalculateNormal(glm::vec3 const & intersectionPoint) const
{
	return normal;
}

AABB Triangle::ComputeBoundingBox() const
{
	AABB aabb;
	aabb.Reset(v1);
	aabb.AddPoint(v2);
	aabb.AddPoint(v3);
	return aabb;
}

std::string Triangle::GetObjectType() const
{
	return "Triangle";
}
