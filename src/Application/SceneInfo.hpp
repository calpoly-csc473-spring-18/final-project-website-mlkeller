
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <parser/Parser.hpp>
#include <string>


class SceneInfo
{

public:

	static void RunCommand(const std::string & fileName);
	static void PrintInfo(const parser::Parser & p);

};
