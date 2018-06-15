
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <vector>
#include <string>


/// Takes an input string and returns an array of tokenized substrings
///
/// A token consists of any:
/// - Contiguous block of alpha characters [a-zA-Z] or underscores
/// - Contiguous block of numeric characters [0-9] or dot `.` or minus sign `-`
/// - Individual symbol (e.g. `{{` tokenizes to two tokens, both `{`)
///
/// All comment lines (anything between `//` and a newline character), non-printing characters,
/// or whitespace are removed.
///
/// ASCII files are assumed.
class Tokenizer
{

public:

	static std::vector<std::string> Tokenize(const std::string & source);

};
