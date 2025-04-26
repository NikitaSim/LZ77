#pragma once

#include <string>
#include <vector>
#include "Token_class.h"

std::vector<Token> encode(const std::string&);
std::string decode(const std::vector<Token>&);

void print_tokens(const std::vector<Token>&);