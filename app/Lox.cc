
#include <cstring>      // std::strerror
#include <fstream>      // readFile
#include <iostream>     // std::getline
#include <string>
#include <vector>

#include "token.hpp"
#include "scanner.hpp"
#include "error.hpp"


void runPrompt() {
  for(;;) {
    std::cout << "> ";
    std::string line;
    if (!std::getline(std::cin, line)) break;
    std::cout << line << "\n";
  }
}


int main(int argc, char* argv[]) {
  if (argc > 2) {
    std::cout << "Usage: jlox [script]\n";
    std::exit(64);
  } else if (argc == 2) {
  } else {
    runPrompt();
  }

  Token t;
  Scanner s("var l = a");

  std::cout << "exit jlox\n";
}