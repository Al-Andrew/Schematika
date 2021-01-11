#pragma once
#include "blocks.hpp"
#include "helpers.hpp"
#include "config.hpp"
#include "string"
#include <algorithm>
#include <stdlib.h>

/// <summary>
/// Used for the run button
/// Interprets the schema
/// </summary>
/// <author>Andrei</author>
void interpret(std::vector<Block> blocks);

/// <summary>
/// Used for code button
/// Translates the schema into c++ code
/// </summary>
/// <author>Andrei</author>
std::string translate(std::vector<Block> blocks);
