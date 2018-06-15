
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <stdexcept>


/// Exception thrown by Parser and TokenStream when a parse-related error
/// is encountered.
class parse_error : public std::domain_error
{

public:

	parse_error() = default;
	parse_error(const std::string & what_arg) : std::domain_error(what_arg) {}
	parse_error(const char * what_arg) : std::domain_error(what_arg) {}

	parse_error(const std::string & what, const std::string & expression)
	: std::domain_error(what + " '" + expression + "'")
	{}

};
