
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <glm/glm.hpp>
#include <vector>


namespace parser
{

	struct Finish
	{
		float ambient = 0;
		float diffuse = 0;
		float specular = 0;

		float roughness = 1;
		float reflection = 0;
		float ior = 1;
	};

	struct Transform
	{
		enum class Type
		{
			Translate,
			Scale,
			Rotate
		};

		glm::vec3 quantity;
		Type type;
	};

	struct Attributes
	{
		glm::vec4 pigment;
		Finish finish;
		std::vector<Transform> transforms;
	};

	struct Object
	{
		enum class Type
		{
			Sphere,
			Plane,
			Triangle,
			Box,
			Cone
		};

		Type type;
		glm::vec3 v1, v2, v3;
		float s1 = 0, s2 = 0;
		Attributes attributes;
	};

	struct Camera
	{
		glm::vec3 up, right, look_at, location;
	};

	struct Light
	{
		glm::vec3 position;
		glm::vec4 color;
	};

}
