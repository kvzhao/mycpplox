
#include "scanner.hpp"
#include "error.hpp"

#include <iostream>

const std::unordered_map<std::string, TokenType> Scanner::keywords = {
    {"and", TokenType::AND},       {"class", TokenType::CLASS},
    {"else", TokenType::ELSE},     {"false", TokenType::FALSE},
    {"fun", TokenType::FUN},       {"for", TokenType::FOR},
    {"if", TokenType::IF},         {"nil", TokenType::NIL},
    {"or", TokenType::OR},         {"print", TokenType::PRINT},
    {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
    {"this", TokenType::THIS},     {"ture", TokenType::TRUE},
    {"var", TokenType::VAR},       {"while", TokenType::WHILE}};

Scanner::Scanner(std::string_view source) : source(source) {}

std::vector<Token> Scanner::ScanTokens() {

  while (!IsAtEnd()) {
    start = current;
    ScanToken();
  }

  tokens.emplace_back(Token(END_OF_FILE, "", nullptr, line));

  return tokens;
}

bool Scanner::IsAtEnd() { return current >= source.length(); }

bool Scanner::IsDigit(char c) { return c >= '0' && c <= '9'; }

bool Scanner::IsAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

bool Scanner::IsAlphaNumeric(char c) { return IsDigit(c) || IsAlpha(c); }

char Scanner::Peek() {
  if (IsAtEnd())
    return '\0';
  return source[current];
}

char Scanner::PeekNext() {
  if (current + 1 >= source.length()) {
    return '\0';
  }
  return source[current + 1];
}

char Scanner::Advance() { return source[current++]; }

bool Scanner::Match(char expected) {
  if (IsAtEnd())
    return false;
  if (source[current] != expected)
    return false;
  ++current;
  return true;
}

void Scanner::Number() {
  while (IsDigit(Peek()))
    Advance();

  // fraction
  if (Peek() == '.' && IsDigit(PeekNext())) {
    Advance();
    while (IsDigit(Peek()))
      Advance();
  }

  AddToken(NUMBER,
           std::stod(std::string{source.substr(start, current - start)}));
}

void Scanner::String() {
  while (Peek() != '"' && !IsAtEnd()) {
    if (Peek() == '\n')
      ++line;
    Advance();
  }

  if (IsAtEnd()) {
    Error(line, "Unterminated string");
    return;
  }
  // closing the string
  Advance();

  std::string value{source.substr(start + 1, current - start - 2)};

  AddToken(STRING, value);
}

void Scanner::Identifier() {

  while (IsAlphaNumeric(Peek()))
    Advance();

  std::string text = std::string{source.substr(start, current - start)};

  TokenType type;
  auto match = keywords.find(text);

  if (match == keywords.end()) {
    type = IDENTIFIER;
  } else {
    type = match->second;
  }

  AddToken(type);
}

void Scanner::ScanToken() {
  char c = Advance();

  switch (c) {
  case '(':
    AddToken(LEFT_PAREN);
    break;
  case ')':
    AddToken(RIGHT_PAREN);
    break;
  case '{':
    AddToken(LEFT_BRACE);
    break;
  case '}':
    AddToken(RIGHT_BRACE);
    break;
  case ',':
    AddToken(COMMA);
    break;
  case '.':
    AddToken(DOT);
    break;
  case '-':
    AddToken(MINUS);
    break;
  case '+':
    AddToken(PLUS);
    break;
  case ';':
    AddToken(SEMICOLON);
    break;
  case '*':
    AddToken(STAR);
    break;

  case '!':
    AddToken(Match('=') ? BANG_EQUAL : BANG);
    break;

  case '=':
    AddToken(Match('=') ? EQUAL_EQUAL : EQUAL);
    break;

  case '>':
    AddToken(Match('=') ? GREATER_EQUAL : GREATER);
    break;

  case '<':
    AddToken(Match('=') ? LESS_EQUAL : LESS);
    break;

  case '/':
    if (Match('/')) {
      while (Peek() != '\n' && !IsAtEnd())
        Advance();
    } else {
      AddToken(SLASH);
    }
    break;

  case '\n':
    ++line;
    break;
  case ' ':
  case '\r':
  case '\t':
    break;

  case '"':
    String();
    break;

  default:
    if (IsDigit(c)) {
      Number();
    } else if (IsAlpha(c)) {
      Identifier();
    } else {
      Error(line, "Unexpected character: " + std::to_string(c));
    }
    break;
  }
}

void Scanner::AddToken(TokenType type, std::any literal) {
  std::string text{source.substr(start, current - start)};

  tokens.emplace_back(Token(type, std::move(text), std::move(literal), line));
}

void Scanner::AddToken(TokenType type) { AddToken(type, nullptr); }