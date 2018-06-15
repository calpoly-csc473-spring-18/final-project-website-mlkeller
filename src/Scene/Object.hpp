
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <glm/glm.hpp>
#include <parser/Objects.hpp>
#include <RayTracer/Ray.hpp>

#include "AABB.hpp"


struct Material
{
	parser::Finish finish;
	glm::vec3 color;
	float filter = 0;
};

class Object
{

public:

	Object() = default;

	void SetID(int const id);
	int GetID() const;

	Material & GetMaterial();
	Material const & GetMaterial() const;

	void SetModelMatrix(glm::mat4 const & modelMatrix);
	float IntersectTransformed(Ray const & ray) const;
	glm::vec3 CalculateNormalTransformed(glm::vec3 const & intersectionPoint) const;

	const AABB & GetBoundingBox() const;
	void StoreBoundingBox();

	virtual float Intersect(Ray const & ray) const = 0;
	virtual glm::vec3 CalculateNormal(glm::vec3 const & intersectionPoint) const = 0;
	virtual AABB ComputeBoundingBox() const = 0;
	virtual std::string GetObjectType() const = 0;

protected:

	Material material;
	glm::mat4 modelMatrix;
	glm::mat4 inverseModelMatrix;
	glm::mat4 normalMatrix;
	int id = -1;
	AABB boundingBox;

};
