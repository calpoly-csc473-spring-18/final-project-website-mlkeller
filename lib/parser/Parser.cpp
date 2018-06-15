
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "Parser.hpp"
#include "Tokenizer.hpp"
#include "parse_error.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;


namespace parser
{

	void Parser::Parse(const std::string & fileName)
	{
		std::ifstream file;
		file.open(fileName);

		if (! file.is_open())
		{
			std::cerr << "Failed to open file '" << fileName << "'\n" << std::endl;
			throw std::runtime_error("povray scene file could not be opened");
		}

		std::string Contents{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()}; // inefficient

		try
		{
			TokenStream ts = Tokenizer::Tokenize(Contents);
			Parse(ts);
		}
		catch (const std::exception & e)
		{
			std::cerr << "exception: " << e.what() << std::endl;
			throw std::runtime_error("povray scene could not be parsed");
		}
	}

	void Parser::Parse(TokenStream & tokens)
	{
		while (! tokens.empty())
		{
			const string token = tokens.pop();

			if (token == "camera")
			{
				camera = ParseCamera(tokens);
			}
			else if (token == "light_source")
			{
				lights.push_back(ParseLightSource(tokens));
			}
			else if (token == "sphere")
			{
				objects.push_back(ParseSphere(tokens));
			}
			else if (token == "triangle")
			{
				objects.push_back(ParseTriangle(tokens));
			}
			else if (token == "box")
			{
				objects.push_back(ParseBox(tokens));
			}
			else if (token == "cone")
			{
				objects.push_back(ParseCone(tokens));
			}
			else if (token == "plane")
			{
				objects.push_back(ParsePlane(tokens));
			}
			else
			{
				throw parse_error("unexpected top-level object", token);
			}
		}
	}

	glm::vec3 Parser::ParseVector3(TokenStream & tokens)
	{
		glm::vec3 v;
		tokens.require("<");
		v.x = tokens.pop_numeric();
		tokens.require(",");
		v.y = tokens.pop_numeric();
		tokens.require(",");
		v.z = tokens.pop_numeric();
		tokens.require(">");
		return v;
	}

	glm::vec4 Parser::ParseVector4(TokenStream & tokens)
	{
		glm::vec4 v;
		tokens.require("<");
		v.x = tokens.pop_numeric();
		tokens.require(",");
		v.y = tokens.pop_numeric();
		tokens.require(",");
		v.z = tokens.pop_numeric();
		tokens.require(",");
		v.w = tokens.pop_numeric();
		tokens.require(">");
		return v;
	}


	glm::vec4 Parser::ParseColor(TokenStream & tokens)
	{
		glm::vec4 color;

		tokens.require("color");
		string type = tokens.pop();

		if (type == "rgb")
		{
			glm::vec3 v = ParseVector3(tokens);
			color.x = v.x;
			color.y = v.y;
			color.z = v.z;
		}
		else if (type == "rgbf")
		{
			color = ParseVector4(tokens);
		}
		else
		{
			throw parse_error("unexpected color type", type);
		}

		return color;
	}

	glm::vec4 Parser::ParsePigment(TokenStream & tokens)
	{
		glm::vec4 pigment;

		tokens.require("{");
		pigment = ParseColor(tokens);
		tokens.require("}");

		return pigment;
	}

	Finish Parser::ParseFinish(TokenStream & tokens)
	{
		Finish f;

		tokens.require("{");

		while (! tokens.empty())
		{
			string token = tokens.pop();

			if (token == "ambient")
				f.ambient = tokens.pop_numeric();
			else if (token == "diffuse")
				f.diffuse = tokens.pop_numeric();
			else if (token == "specular")
				f.specular = tokens.pop_numeric();
			else if (token == "roughness")
				f.roughness = tokens.pop_numeric();
			else if (token == "ior")
				f.ior = tokens.pop_numeric();
			else if (token == "reflection")
				f.reflection = tokens.pop_numeric();
			else if (token == "refraction")
				tokens.pop_numeric();
			else if (token == "}")
				break;
			else
				throw parse_error("unexpected finish property", token);
		}

		return f;
	}

	Attributes Parser::ParseAttributes(TokenStream & tokens)
	{
		Attributes a;

		while (! tokens.empty())
		{
			string token = tokens.pop();

			if (token == "pigment")
			{
				a.pigment = ParsePigment(tokens);
			}
			else if (token == "finish")
			{
				a.finish = ParseFinish(tokens);
			}
			else if (token == "translate")
			{
				Transform t;
				t.quantity = ParseVector3(tokens);
				t.type = Transform::Type::Translate;
				a.transforms.push_back(t);
			}
			else if (token == "rotate")
			{
				Transform t;
				t.quantity = ParseVector3(tokens);
				t.type = Transform::Type::Rotate;
				a.transforms.push_back(t);
			}
			else if (token == "scale")
			{
				Transform t;
				t.quantity = ParseVector3(tokens);
				t.type = Transform::Type::Scale;
				a.transforms.push_back(t);
			}
			else if (token == "}")
			{
				break;
			}
			else
			{
				throw parse_error("unexpected object attribute", token);
			}
		}

		return a;
	}


	Camera Parser::ParseCamera(TokenStream & tokens)
	{
		Camera c;

		tokens.require("{");

		while (! tokens.empty())
		{
			string token = tokens.pop();

			if (token == "location")
				c.location = ParseVector3(tokens);
			else if (token == "look_at")
				c.look_at = ParseVector3(tokens);
			else if (token == "up")
				c.up = ParseVector3(tokens);
			else if (token == "right")
				c.right = ParseVector3(tokens);
			else if (token == "}")
				break;
			else
				throw parse_error("unexpected camera attribute", token);
		}

		return c;
	}

	Light Parser::ParseLightSource(TokenStream & tokens)
	{
		Light l;

		tokens.require("{");
		l.position = ParseVector3(tokens);
		l.color = ParseColor(tokens);
		tokens.require("}");

		return l;
	}


	Object Parser::ParseSphere(TokenStream & tokens)
	{
		Object s;
		s.type = Object::Type::Sphere;

		tokens.require("{");
		s.v1 = ParseVector3(tokens);
		tokens.require(",");
		s.s1 = tokens.pop_numeric();

		s.attributes = ParseAttributes(tokens);

		return s;
	}

	Object Parser::ParsePlane(TokenStream & tokens)
	{
		Object p;
		p.type = Object::Type::Plane;

		tokens.require("{");
		p.v1 = ParseVector3(tokens);
		tokens.require(",");
		p.s1 = tokens.pop_numeric();

		p.attributes = ParseAttributes(tokens);

		return p;
	}

	Object Parser::ParseTriangle(TokenStream & tokens)
	{
		Object t;
		t.type = Object::Type::Triangle;

		tokens.require("{");
		t.v1 = ParseVector3(tokens);
		tokens.require(",");
		t.v2 = ParseVector3(tokens);
		tokens.require(",");
		t.v3 = ParseVector3(tokens);

		t.attributes = ParseAttributes(tokens);

		return t;
	}

	Object Parser::ParseBox(TokenStream & tokens)
	{
		Object b;
		b.type = Object::Type::Box;

		tokens.require("{");
		b.v1 = ParseVector3(tokens);
		tokens.require(",");
		b.v2 = ParseVector3(tokens);

		b.attributes = ParseAttributes(tokens);

		return b;
	}

	Object Parser::ParseCone(TokenStream & tokens)
	{
		Object c;
		c.type = Object::Type::Cone;

		tokens.require("{");
		c.v1 = ParseVector3(tokens);
		tokens.require(",");
		c.s1 = tokens.pop_numeric();
		tokens.require(",");
		c.v2 = ParseVector3(tokens);
		tokens.require(",");
		c.s2 = tokens.pop_numeric();

		c.attributes = ParseAttributes(tokens);

		return c;
	}

}
