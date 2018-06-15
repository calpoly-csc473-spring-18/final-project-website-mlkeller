
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "Application.hpp"
#include "SceneInfo.hpp"
#include "Renderer.hpp"
#include "RayInfo.hpp"

#include <RayTracer/RayTracer.hpp>
#include <Scene/Scene.hpp>

#include <Objects/Sphere.hpp>
#include <Objects/Plane.hpp>
#include <Objects/Triangle.hpp>
#include <Objects/Box.hpp>

#include <parser/Tokenizer.hpp>
#include <parser/Parser.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdexcept>


void Application::ReadArguments(int argc, char ** argv)
{
	for (int i = 0; i < argc; ++ i)
	{
		commandArguments.push_back(argv[i]);
	}
}

int Application::Run()
{
	try
	{
		RunCommands();
		return 0;
	}
	catch (std::exception const & e)
	{
		std::cout << e.what() << std::endl;
		PrintUsage();
		return 1;
	}
}

void Application::PrintUsage()
{
	if (! commandArguments.size())
	{
		printf("No command arguments found.\n");
		printf("usage: raytracer <command> <file_name> [arguments ...]\n");
		return;
	}

	if (commandArguments.size() < 2)
	{
		printf("usage: %s <command> <file_name> [arguments ...]\n", commandArguments[0].c_str());
		return;
	}

	const std::string programName = commandArguments[0];
	std::string command = commandArguments[1];

	if (command == "help" && commandArguments.size() > 2)
	{
		command = commandArguments[2];
	}

	bool showParamOptions = false;

	if (command == "render" || command == "raycast")
	{
		printf("usage: %s %s <file_name> <width> <height> [arguments ...]\n", programName.c_str(), command.c_str());
		showParamOptions = true;
	}
	else if (command == "sceneinfo")
	{
		printf("usage: %s sceneinfo <file_name>\n", programName.c_str());
	}
	else if (command == "pixelray" || command == "firsthit" || command == "printrays" || command == "pixeltrace")
	{
		printf("usage: %s %s <file_name> <width> <height> <x> <y> [arguments ...]\n", programName.c_str(), command.c_str());
		showParamOptions = true;
	}
	else if (command == "help")
	{
		printf("usage: raytracer <command> <file_name> [arguments ...]\n");
		printf("    supported commands:\n");
		printf("        raycast      render an image using a simple raycast\n");
		printf("        render       render a full, shaded raytrace\n");
		printf("        sceneinfo    simply print the objects found in the given scene description file\n");
		printf("        pixelray     print the camera-generated ray for the given pixel\n");
		printf("        firsthit     print the first object hit for the given pixel\n");
		printf("        printrays    print all recursively generated rays for the given pixel\n");
		printf("        pixeltrace   print all recursively generated rays for the given pixel, with fancy formatting\n");
	}
	else
	{
		printf("unknown command: %s\n", command.c_str());
	}

	if (showParamOptions)
	{
		printf("    possible arguments:\n");
		printf("        -altbrdf    use Cook-Torrance instead of Blinn-Phong BRDF\n");
		printf("        -normals    display surface normals instead of any shading\n");
	}
}

void Application::RunCommands()
{
	if (commandArguments.size() < 2)
	{
		throw std::invalid_argument("Insufficient arguments.");
	}

	const std::string command = commandArguments[1];

	if (command == "help")
	{
		PrintUsage();
		return;
	}

	if (commandArguments.size() < 3)
	{
		throw std::invalid_argument("Insufficient arguments.");
	}

	fileName = commandArguments[2];

	std::cout << std::setiosflags(std::ios::fixed);
	std::cout << std::setprecision(4);


	/////////////////////
	// Simple Commands //
	/////////////////////

	if (command == "sceneinfo")
	{
		SceneInfo::RunCommand(fileName);
		return;
	}

	scene = LoadPovrayScene(fileName);
	rayTracer = new RayTracer(scene);

	if (command == "printbvh")
	{
		ParseExtraParams(3);
		rayTracer->SetParams(params);
		RayInfo::PrintTree(scene);
		return;
	}


	///////////////////
	// Draw Commands //
	///////////////////


	if (commandArguments.size() < 5)
	{
		throw std::invalid_argument("Insufficient arguments.");
	}

	params.imageSize.x = std::stoi(commandArguments[3]);
	params.imageSize.y = std::stoi(commandArguments[4]);

	params.useShading = true;
	params.useShadows = true;

	if (command == "render" || command == "raycast")
	{
		if (command == "render")
		{
		}
		else if (command == "raycast")
		{
			params.useShading = false;
			params.useShadows = false;
		}

		ParseExtraParams(5);
		rayTracer->SetParams(params);
		Renderer::Draw(rayTracer);

		return;
	}


	////////////////////
	// Pixel Commands //
	////////////////////

	if (commandArguments.size() < 7)
	{
		throw std::invalid_argument("Insufficient arguments.");
	}

	const int x = std::stoi(commandArguments[5]);
	const int y = std::stoi(commandArguments[6]);

	ParseExtraParams(7);
	rayTracer->SetParams(params);

	if (command == "pixelray")
	{
		Ray const ray = scene->GetCamera().GetPixelRay(glm::ivec2(x, y), rayTracer->GetParams().imageSize);

		std::cout << "Pixel: [" << x << ", " << y << "] Ray: " << ray << std::endl;
		return;
	}
	else if (command == "firsthit")
	{
		RayInfo::FirstHit(rayTracer, scene, x, y);
		return;
	}
	else if (command == "pixelcolor")
	{
		RayInfo::PixelColor(rayTracer, scene, x, y);
		return;
	}
	else if (command == "printrays")
	{
		RayInfo::DiagnosticTrace(rayTracer, scene, x, y, false);
		return;
	}
	else if (command == "pixeltrace")
	{
		RayInfo::DiagnosticTrace(rayTracer, scene, x, y, true);
		return;
	}

	throw std::invalid_argument("Unknown command.");
}

bool StringBeginsWith(const std::string & s, const std::string & prefix, std::string & remainder)
{
	if (s.size() < prefix.size())
	{
		return false;
	}

	if (s.substr(0, prefix.size()) == prefix)
	{
		remainder = s.substr(prefix.size());
		return true;
	}

	return false;
}

void Application::ParseExtraParams(size_t const StartIndex)
{
	for (size_t i = StartIndex; i < commandArguments.size(); ++ i)
	{
		std::string const & argument = commandArguments[i];
		std::string remainder;

		if (argument == "-altbrdf")
		{
			params.useCookTorrance = true;
		}
		else if (argument == "-normals")
		{
			params.debugNormals = true;
		}
		else if (argument == "-fresnel")
		{
			params.useFresnel = true;
		}
		else if (argument == "-beers")
		{
			params.useBeers = true;
		}
		else if (StringBeginsWith(argument, "-ss=", remainder))
		{
			params.superSampling = std::stoi(remainder);
		}
		else if (StringBeginsWith(argument, "-N=", remainder))
		{
			params.shadowSample = std::stoi(remainder);
		}
		else if (StringBeginsWith(argument, "-radius=", remainder))
		{
			params.lightRadius = std::stof(remainder);
		}
		else if (argument == "-sds")
		{
			params.useSpatialDataStructure = true;
		}
		else if (argument == "-gi")
		{
			params.useGI = true;
		}
		else if (argument == "-sosh") {
			params.useSoftShadows = true;
		}
	}
}

Scene * Application::LoadPovrayScene(const std::string & fileName)
{
	Scene * scene = new Scene();

	parser::Parser p;
	p.Parse(fileName);

	scene->GetCamera().SetPosition(p.camera.location);
	scene->GetCamera().SetLookAt(p.camera.look_at);
	scene->GetCamera().SetUpVector(p.camera.up);
	scene->GetCamera().SetRightVector(p.camera.right);

	for (const parser::Object & o : p.objects)
	{
		Object * object = nullptr;

		switch (o.type)
		{
		case parser::Object::Type::Sphere:
			object = new Sphere(o.v1, o.s1);
			break;

		case parser::Object::Type::Plane:
			object = new Plane(o.v1, o.s1);
			break;

		case parser::Object::Type::Triangle:
			object = new Triangle(o.v1, o.v2, o.v3);
			break;

		case parser::Object::Type::Box:
			object = new Box(o.v1, o.v2);
			break;

		case parser::Object::Type::Cone:
			std::cerr << "Cone objects not supported." << std::endl;
			break;
		}

		if (object)
		{
			glm::mat4 transform = glm::mat4(1.f);

			for (const parser::Transform & t : o.attributes.transforms)
			{
				switch (t.type)
				{
				case parser::Transform::Type::Translate:
					transform = glm::translate(glm::mat4(1.f), t.quantity) * transform;
					break;

				case parser::Transform::Type::Scale:
					transform = glm::scale(glm::mat4(1.f), t.quantity) * transform;
					break;

				case parser::Transform::Type::Rotate:
				{
					glm::mat4 rotation;

					rotation = glm::rotate(glm::mat4(1.f), glm::radians(t.quantity.z), glm::vec3(0, 0, 1)) * rotation;
					rotation = glm::rotate(glm::mat4(1.f), glm::radians(t.quantity.y), glm::vec3(0, 1, 0)) * rotation;
					rotation = glm::rotate(glm::mat4(1.f), glm::radians(t.quantity.x), glm::vec3(1, 0, 0)) * rotation;

					transform = rotation * transform;
				}
				}
			}

			object->SetModelMatrix(transform);
			object->GetMaterial().finish = o.attributes.finish;
			object->GetMaterial().color = glm::vec3(o.attributes.pigment.x, o.attributes.pigment.y, o.attributes.pigment.z);
			object->GetMaterial().filter = o.attributes.pigment.w;
			object->StoreBoundingBox();
			scene->AddObject(object);
		}
	}

	for (const parser::Light & l : p.lights)
	{
		Light * light = new Light();
		light->color = glm::vec3(l.color.x, l.color.y, l.color.z);
		light->position = l.position;
		scene->AddLight(light);
	}

	return scene;
}
