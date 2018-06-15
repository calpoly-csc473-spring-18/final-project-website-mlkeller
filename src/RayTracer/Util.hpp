
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <ostream>
#include <glm/glm.hpp>

std::ostream & operator << (std::ostream & stream, const glm::vec3 & vec);
std::ostream & operator << (std::ostream & stream, const glm::vec4 & vec);
