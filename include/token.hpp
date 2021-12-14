#pragma once

#include <string>
#include <vector>
#include <any>

#include "token_type.hpp"

class Token {

public:
  Token() {};

  Token(TokenType type, std::string lexeme, std::any literal, int line);

};