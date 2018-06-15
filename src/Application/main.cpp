
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "Application.hpp"


int main(int argc, char ** argv)
{
	Application app;
	app.ReadArguments(argc, argv);

	return app.Run();
}
