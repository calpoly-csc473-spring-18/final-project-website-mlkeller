
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "Object.hpp"


void Object::SetID(int const id)
{
	this->id = id;
}

int Object::GetID() const
{
	return id;
}

Material & Object::GetMaterial()
{
	return material;
}

Material const & Object::GetMaterial() const
{
	return material;
}

void Object::SetModelMatrix(glm::mat4 const & modelMatrix)
{
	this->modelMatrix = modelMatrix;
	inverseModelMatrix = glm::inverse(modelMatrix);
	normalMatrix = glm::transpose(inverseModelMatrix);
}

float Object::IntersectTransformed(Ray const & ray) const
{
	return Intersect(ray * inverseModelMatrix);
}

glm::vec3 Object::CalculateNormalTransformed(glm::vec3 const & intersectionPoint) const
{
	const glm::vec3 objectSpaceIntersection = glm::vec3(inverseModelMatrix * glm::vec4(intersectionPoint, 1.f));
	const glm::vec3 objectSpaceNormal = CalculateNormal(objectSpaceIntersection);

	return glm::normalize(glm::vec3(normalMatrix * glm::vec4(objectSpaceNormal, 0.f)));
}

const AABB & Object::GetBoundingBox() const
{
	return boundingBox;
}

void Object::StoreBoundingBox()
{
	boundingBox = ComputeBoundingBox();
	boundingBox.Transform(modelMatrix);
}
