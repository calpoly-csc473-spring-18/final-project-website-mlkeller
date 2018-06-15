
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <vector>
#include <string>

#include <Scene/Scene.hpp>
#include <RayTracer/Params.hpp>


class RayTracer;

class Application
{

public:


	void ReadArguments(int argc, char ** argv);
	int Run();

protected:

	void PrintUsage();
	void RunCommands();
	void ParseExtraParams(size_t const StartIndex);

	static Scene * LoadPovrayScene(const std::string & fileName);

	std::vector<std::string> commandArguments;

	Scene * scene = nullptr;
	RayTracer * rayTracer = nullptr;

	Params params;
	std::string fileName;

};
