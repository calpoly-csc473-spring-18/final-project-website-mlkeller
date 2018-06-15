
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <Scene/Scene.hpp>
#include <RayTracer/RayTracer.hpp>


class RayInfo
{

public:

	static void FirstHit(RayTracer * rayTracer, Scene * scene, const int x, const int y);
	static void PixelColor(RayTracer * rayTracer, Scene * scene, const int x, const int y);
	static void DiagnosticTrace(RayTracer * rayTracer, Scene * scene, const int x, const int y, const bool decoration);
	static void PrintTree(Scene * scene);

protected:

	struct IterationTreeNode
	{
		PixelContext::Iteration * iteration = nullptr;
		std::vector<IterationTreeNode *> children;
	};

	static void RecursiveIterationPrint(const std::string & parentPrefix, const IterationTreeNode * const node, const bool decoration, const bool verbose);

};
