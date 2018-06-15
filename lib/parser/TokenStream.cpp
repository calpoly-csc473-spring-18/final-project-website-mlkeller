
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "TokenStream.hpp"
#include "parse_error.hpp"

#include <sstream>
#include <limits>
using namespace std;


TokenStream::TokenStream(vector<string> const & tokens)
: Tokens(tokens)
{}

void TokenStream::reset(const std::vector<std::string> & tokens)
{
	i = 0;
	Tokens = tokens;
}

bool TokenStream::empty() const
{
	return i >= Tokens.size();
}

string TokenStream::top() const
{
	if (i >= Tokens.size())
	{
		throw parse_error("unexpected end-of-file");
	}

	return Tokens[i];
}

string TokenStream::pop()
{
	if (i >= Tokens.size())
	{
		throw parse_error("unexpected end-of-file");
	}

	return Tokens[i ++];
}

float TokenStream::pop_numeric()
{
	if (i >= Tokens.size())
	{
		throw parse_error("unexpected end-of-file");
	}

	try
	{
		float value = stof(Tokens[i]);
		i ++;
		return value;
	}
	catch (const std::invalid_argument & e)
	{
		throw parse_error("expected number, found", Tokens[i]);
	}

	return numeric_limits<float>::max();
}

void TokenStream::require(string const & expectedToken)
{
	if (i >= Tokens.size())
	{
		throw parse_error("unexpected end-of-file");
	}

	if (Tokens[i] != expectedToken)
	{
		stringstream s;
		s << "expected token '" << expectedToken << "', found '" << Tokens[i] << "'";
		throw parse_error(s.str());
	}

	i ++;
}


