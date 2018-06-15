
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "Util.hpp"


std::ostream & operator << (std::ostream & stream, const glm::vec3 & vec)
{
	return stream << vec.x << " " << vec.y << " " << vec.z;
}

std::ostream & operator << (std::ostream & stream, const glm::vec4 & vec)
{
	return stream << vec.x << " " << vec.y << " " << vec.z << " " << vec.w;
}
