
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "RayInfo.hpp"

#include <iostream>
#include <vector>
#include <map>

#include <RayTracer/PixelContext.hpp>


void RayInfo::FirstHit(RayTracer * rayTracer, Scene * scene, const int x, const int y)
{
	const Ray ray = scene->GetCamera().GetPixelRay(glm::ivec2(x, y), rayTracer->GetParams().imageSize);
	const RayHitResults results = scene->GetRayHitResults(scene->GetCamera().GetPixelRay(glm::ivec2(x, y), rayTracer->GetParams().imageSize));
	const float intersection = results.t;
	const Object * const object = results.object;

	std::cout << "Pixel: [" << x << ", " << y << "] Ray: " << ray  << std::endl;

	if (object)
	{
		std::cout << "T = " << intersection << std::endl;
		std::cout << "Object Type: " << object->GetObjectType() << std::endl;
		std::cout << "Color: " << object->GetMaterial().color << std::endl;
	}
	else
	{
		std::cout << "No Hit" << std::endl;
	}
}

void RayInfo::PixelColor(RayTracer * rayTracer, Scene * scene, const int x, const int y)
{
	const Pixel pixel = rayTracer->CastRaysForPixel(glm::ivec2(x, y));
	const Ray ray = scene->GetCamera().GetPixelRay(glm::ivec2(x, y), rayTracer->GetParams().imageSize);
	const RayHitResults results = scene->GetRayHitResults(scene->GetCamera().GetPixelRay(glm::ivec2(x, y), rayTracer->GetParams().imageSize));
	const float intersection = results.t;
	const Object * const object = results.object;

	std::cout << "Pixel: [" << x << ", " << y << "] Ray: " << ray << std::endl;

	if (object)
	{
		std::cout << "T = " << intersection << std::endl;
		std::cout << "Object Type: " << object->GetObjectType() << std::endl;
		std::cout << "BRDF: " << "Blinn-Phong" << std::endl;
		std::cout << "Color: " << pixel << std::endl;
	}
	else
	{
		std::cout << "No Hit" << std::endl;
	}
}

void RayInfo::DiagnosticTrace(RayTracer * rayTracer, Scene * scene, const int x, const int y, const bool decoration)
{
	// Cast rays with context to gather info
	PixelContext context;
	rayTracer->SetDebugContext(& context);
	const Pixel color = rayTracer->CastRaysForPixel(glm::ivec2(x, y));

	std::cout << "Pixel: [" << x << ", " << y << "] Color: " << color << std::endl;

	// Extract tree from context iterations
	std::map<PixelContext::Iteration *, IterationTreeNode *> nodeMap;

	IterationTreeNode * rootNode = new IterationTreeNode();
	nodeMap[nullptr] = rootNode;

	for (PixelContext::Iteration * Iteration : context.iterations)
	{
		IterationTreeNode * node = new IterationTreeNode();
		node->iteration = Iteration;

		nodeMap[Iteration] = node;
		nodeMap[Iteration->parent]->children.push_back(node);
	}

	// Print rays
	for (IterationTreeNode * node : rootNode->children)
	{
		RecursiveIterationPrint("", node, decoration, decoration);
	}

	std::cout << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;
}

void RayInfo::PrintTree(Scene * scene)
{
	if (scene->GetSpatialDataStructure())
	{
		scene->GetSpatialDataStructure()->PrintTree("root");
	}
	else
	{
		std::cerr << "Cannot print bvh without -sds argument." << std::endl;
	}
}

void RayInfo::RecursiveIterationPrint(const std::string & parentPrefix, const IterationTreeNode * const node, const bool decoration, const bool verbose)
{
	PixelContext::Iteration * iteration = node->iteration;

	std::string firstLinePrefix, otherLinePrefix;
	if (decoration)
	{
		firstLinePrefix = "o - ";
		otherLinePrefix = "|   ";
	}

	std::string p = parentPrefix + firstLinePrefix;

	if (! decoration)
	{
		std::cout << parentPrefix << "----" << std::endl;
	}

	std::cout << p << "  Iteration type: ";

	p = parentPrefix + otherLinePrefix;

	if (iteration->type == PixelContext::IterationType::Primary)
		std::cout << "Primary";
	if (iteration->type == PixelContext::IterationType::Reflection)
		std::cout << "Reflection";
	if (iteration->type == PixelContext::IterationType::Refraction)
		std::cout << "Refraction";
	std::cout << std::endl;

	std::cout << p << "             Ray: " << iteration->ray << std::endl;

	if (iteration->hitObject)
	{
		std::cout << p << "      Hit Object: (ID #" << iteration->hitObject->GetID() << " - " << iteration->hitObject->GetObjectType() << ")" << std::endl;
		std::cout << p << "    Intersection: {" << iteration->results.intersectionPoint << "} at T = " << iteration->hitTime << std::endl;
		std::cout << p << "          Normal: {" << iteration->hitNormal << "}" << std::endl;

		std::cout << p << "     Final Color: {" << iteration->results.ToColor() << "}" << std::endl;
		std::cout << p << "         Ambient: {" << iteration->results.ambient << "}" << std::endl;
		std::cout << p << "         Diffuse: {" << iteration->results.diffuse << "}" << std::endl;
		std::cout << p << "        Specular: {" << iteration->results.specular << "}" <<std:: endl;
		std::cout << p << "      Reflection: {" << iteration->results.reflection << "}" << std::endl;
		std::cout << p << "      Refraction: {" << iteration->results.refraction << "}" << std::endl;
		std::cout << p << "   Contributions: " << iteration->contributions.x << " Local, " << iteration->contributions.y << " Reflection, " << iteration->contributions.z << " Transmission" << std::endl;

		if (verbose)
		{
			int i = 0;
			for (const PixelContext::ShadowInfo & shadowInfo : iteration->shadowRays)
			{
				std::cout << p << "   ShadowRay [" << (i++) << "]: " << shadowInfo.ray << (shadowInfo.hit ? " (in shadow)" : "") << std::endl;
			}
		}
	}
	else
	{
		std::cout << p << "  No intersection." << std::endl;
	}

	if (iteration->extraInfo.length())
	{
		std::cout << p << "      Extra Info:" << iteration->extraInfo << std::endl;
	}

	if (node->children.size())
	{
		if (decoration)
		{
			std::cout << parentPrefix << "|" << std::endl;
		}

		std::string childPrefix, otherPrefix;
		if (decoration)
		{
			childPrefix = "| ";
			otherPrefix = "  ";
		}

		for (IterationTreeNode * child : node->children)
		{
			if (child != node->children.back())
			{
				if (decoration)
				{
					std::cout << parentPrefix << "|\\" << std::endl;
				}
				RecursiveIterationPrint(parentPrefix + childPrefix, child, decoration, verbose);
			}
			else
			{
				if (decoration)
				{
					std::cout << parentPrefix << " \\" << std::endl;
				}
				RecursiveIterationPrint(parentPrefix + otherPrefix, child, decoration, verbose);
			}
		}
	}
	else
	{
		if (decoration)
		{
			std::cout << parentPrefix << "|----" << std::endl;
		}
		std::cout << parentPrefix << std::endl;
	}
}
