
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <vector>
#include <string>

/// This is basically just an iterator for traversing the array of tokenized
/// strings, with some helper functions to make it easier to do some common
/// operations, such as checking whether the top token matches a requirement
/// and formating a token as a number.
class TokenStream
{

public:

	TokenStream() = default;
	TokenStream(const std::vector<std::string> & tokens);
	void reset(const std::vector<std::string> & tokens);

	/// Check whether there are any tokens remaining to read
	bool empty() const;

	/// Return the current token in the stream
	std::string top() const;

	/// Return the current token and move the iterator forward
	std::string pop();

	/// Return the current token formatted as a float, move the iterator forward
	/// Throws an exception if the string is not parsable as a float
	float pop_numeric();

	/// Checks whether the top token matches an expected string, then moves the iterator forward
	void require(std::string const & expectedToken);

protected:

	std::vector<std::string> Tokens;
	size_t i = 0;

};
