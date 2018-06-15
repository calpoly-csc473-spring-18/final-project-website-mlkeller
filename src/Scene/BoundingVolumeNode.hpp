
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <string>
#include <glm/glm.hpp>

#include "AABB.hpp"
#include "Object.hpp"


class BoundingVolumeNode
{

public:

	BoundingVolumeNode() = default;
	BoundingVolumeNode(const std::vector<const Object *> & objects);

	static AABB ComputeBoundingBox(const std::vector<const Object *> & objects);
	void SortObjects(const int axis);
	void BuildTree(const int axis);

	bool Intersect(const Ray & ray, float & outIntersect, const Object * & outObject) const;
	void PrintTree(const std::string & name) const;

protected:

	AABB box;

	std::vector<BoundingVolumeNode *> children;
	std::vector<const Object *> objects;


};
