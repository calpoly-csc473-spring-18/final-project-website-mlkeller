
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file

#include "SceneInfo.hpp"
#include <RayTracer/Util.hpp>

#include <parser/Tokenizer.hpp>

#include <iostream>
#include <fstream>
#include <iomanip>


void SceneInfo::RunCommand(const std::string & fileName)
{
	parser::Parser p;
	p.Parse(fileName);

	PrintInfo(p);
}

void SceneInfo::PrintInfo(const parser::Parser & p)
{
	std::cout << std::setiosflags(std::ios::fixed);
	std::cout << std::setprecision(4);

	std::cout << "Camera:" << std::endl;
	std::cout << "- Location: {" << p.camera.location << "}" << std::endl;
	std::cout << "- Up: {" << p.camera.up << "}" << std::endl;
	std::cout << "- Right: {" << p.camera.right << "}" << std::endl;
	std::cout << "- Look at: {" << p.camera.look_at << "}" << std::endl;
	std::cout << std::endl;
	std::cout << "---" << std::endl;
	std::cout << std::endl;

	std::cout << p.lights.size() << " light(s)" << std::endl;
	for (size_t i = 0; i < p.lights.size(); ++ i)
	{
		std::cout << std::endl;
		std::cout << "Light[" << i << "]:" << std::endl;
		std::cout << "- Location: {" << p.lights[i].position << "}" << std::endl;
		std::cout << "- Color: {" <<
			p.lights[i].color.x << " " <<
			p.lights[i].color.y << " " <<
			p.lights[i].color.z << "}" << std::endl;
	}

	std::cout << std::endl;
	std::cout << "---" << std::endl;
	std::cout << std::endl;

	std::cout << p.objects.size() << " object(s)" << std::endl;
	for (size_t i = 0; i < p.objects.size(); ++ i)
	{
		const parser::Object & o = p.objects[i];

		std::cout << std::endl;
		std::cout << "Object[" << i << "]:" << std::endl;

		switch (o.type)
		{
		case parser::Object::Type::Sphere:
			std::cout << "- Type: Sphere" << std::endl;
			std::cout << "- Center: {" << o.v1 << "}" << std::endl;
			std::cout << "- Radius: " << o.s1 << std::endl;
			break;

		case parser::Object::Type::Plane:
			std::cout << "- Type: Plane" << std::endl;
			std::cout << "- Normal: {" << o.v1 << "}" << std::endl;
			std::cout << "- Distance: " << o.s1 << std::endl;
			break;

		case parser::Object::Type::Triangle:
			std::cout << "- Type: Triangle" << std::endl;
			std::cout << "- Vertices[0]: {" << o.v1 << "}" << std::endl;
			std::cout << "- Vertices[1]: {" << o.v2 << "}" << std::endl;
			std::cout << "- Vertices[2]: {" << o.v3 << "}" << std::endl;
			break;

		case parser::Object::Type::Box:
			std::cout << "- Type: Box" << std::endl;
			std::cout << "- Min: {" << o.v1 << "}" << std::endl;
			std::cout << "- Max: {" << o.v2 << "}" << std::endl;
			break;

		case parser::Object::Type::Cone:
			std::cout << "- Type: Cone" << std::endl;
			std::cout << "- Center 1: {" << o.v1 << "}" << std::endl;
			std::cout << "- Radius 1: " << o.s1 << std::endl;
			std::cout << "- Center 2: {" << o.v2 << "}" << std::endl;
			std::cout << "- Radius 2: " << o.s2 << std::endl;
			break;
		}

		// if (o.attributes.pigment.w)
		// 	cout << "- Color: {" << o.attributes.pigment << "}" << std::endl;
		// else
			std::cout << "- Color: {" <<
				o.attributes.pigment.x << " " <<
				o.attributes.pigment.y << " " <<
				o.attributes.pigment.z << "}" << std::endl;
		std::cout << "- Material:" << std::endl;
		std::cout << "  - Ambient: " << o.attributes.finish.ambient << std::endl;
		std::cout << "  - Diffuse: " << o.attributes.finish.diffuse << std::endl;
		// if (o.attributes.finish.specular)
		// 	cout << "  - Specular: " << o.attributes.finish.diffuse << std::endl;
		// if (o.attributes.finish.reflection)
		// 	cout << "  - Reflection: " << o.attributes.finish.diffuse << std::endl;
	}
}
