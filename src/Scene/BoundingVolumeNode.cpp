
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "BoundingVolumeNode.hpp"

#include <iostream>
#include <algorithm>


BoundingVolumeNode::BoundingVolumeNode(const std::vector<const Object *> & objects)
{
	this->objects = objects;
	this->box = ComputeBoundingBox(objects);
}

AABB BoundingVolumeNode::ComputeBoundingBox(const std::vector<const Object *> & objects)
{
	AABB box;

	for (const Object * object : objects)
	{
		box.AddBox(object->GetBoundingBox());
	}

	return box;
}

void BoundingVolumeNode::SortObjects(const int axis)
{
	struct Sorter
	{

		static bool ByX(const Object * b1, const Object * b2)
		{
			return b1->GetBoundingBox().GetCenter().x < b2->GetBoundingBox().GetCenter().x;
		};

		static bool ByY(const Object * b1, const Object * b2)
		{
			return b1->GetBoundingBox().GetCenter().y < b2->GetBoundingBox().GetCenter().y;
		};

		static bool ByZ(const Object * b1, const Object * b2)
		{
			return b1->GetBoundingBox().GetCenter().z < b2->GetBoundingBox().GetCenter().z;
		};

	};

	switch (axis)
	{
	default:
	case 0:
		std::sort(objects.begin(), objects.end(), Sorter::ByX);
		break;

	case 1:
		std::sort(objects.begin(), objects.end(), Sorter::ByY);
		break;

	case 2:
		std::sort(objects.begin(), objects.end(), Sorter::ByZ);
		break;
	}
}

void BoundingVolumeNode::BuildTree(const int axis)
{
	if (objects.size() <= 1)
		return;

	SortObjects(axis);

	children.push_back(new BoundingVolumeNode(std::vector<const Object *>(
		objects.begin(),
		objects.begin() + objects.size() / 2)));
	children.push_back(new BoundingVolumeNode(std::vector<const Object *>(
		objects.begin() + objects.size() / 2,
		objects.end())));
	
	objects.clear();

	for (BoundingVolumeNode * child : children)
	{
		child->BuildTree((axis + 1) % 3);
	}
}

bool BoundingVolumeNode::Intersect(const Ray & ray, float & outIntersect, const Object * & outObject) const
{
	if (box.Intersect(ray) < 0)
	{
		return false;
	}

	for (const BoundingVolumeNode * child : children)
	{
		float newT;
		const Object * newObject = nullptr;

		if (child->Intersect(ray, newT, newObject))
		{
			if (outObject == nullptr || newT < outIntersect)
			{
				outObject = newObject;
				outIntersect = newT;
			}
		}
	}

	for (const Object * object : objects)
	{
		float t = object->IntersectTransformed(ray);
		if (t >= 0)
		{
			if (outObject == nullptr || t < outIntersect)
			{
				outObject = object;
				outIntersect = t;
			}
		}
	}

	return outObject != nullptr;
}

void BoundingVolumeNode::PrintTree(const std::string & name) const
{
	std::cout << name << ":" << std::endl;
	std::cout << "- min: " << box.min << std::endl;
	std::cout << "- max: " << box.max << std::endl;
	if (objects.size())
	{
		std::cout << "- leaf" << std::endl;

		for (const Object * object : objects)
		{
			std::cout << "- object #" << object->GetID() << " (" << object->GetObjectType() << ")" << std::endl;
		}
	}
	else
	{
		std::cout << "- branch" << std::endl;
	}
	std::cout << std::endl;


	if (children.size() > 0)
	{
		children[0]->PrintTree(name + "->left");
	}
	if (children.size() > 1)
	{
		children[1]->PrintTree(name + "->right");
	}
}
