
#include "scanner.hpp"
#include "error.hpp"
#include <iostream>

Scanner::Scanner(std::string_view source)
  : source(source) {}

std::vector<Token> Scanner::scanTokens() {
  // TODO
  while (!isAtEnd()) {
    scanToken();
  }
  return tokens;
}

bool Scanner::isAtEnd() {
  return current >= source.length();
}

char Scanner::peek() {
  if (current + 1 >= source.length()) {
    return '\0';
  }
  return source[current];
}

char Scanner::advance() {
  return source[current++];
}

void Scanner::scanToken() {
  char c = advance();

  switch(c) {
    case '(' :
      addToken(RIGHT_PAREN);
      break;

    default:
      error(line, "Unexpected character.");
      break;
  }
}

void Scanner::addToken(TokenType type, std::any literal) {
  std::string text{source.substr(start, current - start)};

  tokens.emplace_back(
    Token(type, std::move(text), std::move(literal), line)
  );

}

void Scanner::addToken(TokenType type) {
  addToken(type, nullptr);
}