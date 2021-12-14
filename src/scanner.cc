
#include "scanner.hpp"
#include "error.hpp"
#include <iostream>

Scanner::Scanner(std::string_view source)
  : source(source) {}

std::vector<Token> Scanner::scanTokens() {

  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.emplace_back(
    Token(END_OF_FILE, "", nullptr, line));

  return tokens;
}

bool Scanner::isAtEnd() {
  return current >= source.length();
}

bool Scanner::isDigit(char c) {
  return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
         (c == '_');
}

char Scanner::peek() {
  if (isAtEnd()) return '\0';
  return source[current];
}

char Scanner::peekNext() {
  if (current + 1 >= source.length()) {
    return '\0';
  }
  return source[current + 1];
}

char Scanner::advance() {
  return source[current++];
}


bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  if (source[current] != expected) return false;
  ++current;
  return true;
}

void Scanner::number() {
  while(isDigit(peek())) advance();

  // fraction
  if (peek() == '.' && isDigit(peekNext())) {
    advance();
    while(isDigit(peek())) advance();
  }

  addToken(NUMBER,
    std::stod(std::string{source.substr(start, current - start)})
  );
}

void Scanner::scanToken() {
  char c = advance();

  switch(c) {
    case '(' :
      addToken(LEFT_PAREN);
      break;
    case ')':
      addToken(RIGHT_PAREN);
      break;
    case '{':
      addToken(LEFT_BRACE);
      break;
    case '}':
      addToken(RIGHT_BRACE);
      break;
    case ',':
      addToken(COMMA);
      break;
    case '.':
      addToken(DOT);
      break;
    case '-':
      addToken(MINUS);
      break;
    case '+':
      addToken(PLUS);
      break;
    case ';':
      addToken(SEMICOLON);
      break;
    case '*':
      addToken(STAR);
      break;

    case '/':
      if(match('/')) {
        while(peek() != '\n' && !isAtEnd()) advance();
      } else {
        addToken(SLASH);
      }
      break;

    case '\n':
      ++line;
      break;
    case ' ':
    case '\r':
    case '\t':
      break;

    default:
      if (isDigit(c)) {
        number();
      }
      else if (isAlpha(c)) {
        //TODO
      } else {
        error(line, "Unexpected character: " + std::to_string(c));
      }
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