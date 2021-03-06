#pragma once

#include <iostream>
#include <string_view>

inline bool hadError = false;

static void Report(int line, std::string_view where, std::string_view message) {

  std::cerr << "[line " << line << "] Error " << where << ": " << message
            << "\n";
  hadError = true;
}

static void Error(int line, std::string_view message) {
  Report(line, "", message);
}