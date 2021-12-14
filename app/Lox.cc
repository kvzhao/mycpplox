
#include <cstring>      // std::strerror
#include <fstream>      // readFile
#include <iostream>     // std::getline
#include <string>
#include <vector>

#include "token.hpp"
#include "scanner.hpp"
#include "error.hpp"


void run(std::string_view source) {
  Scanner scanner{source};
  std::vector<Token> tokens = scanner.scanTokens();

  for (const auto& t : tokens) {
    std::cout << t.toString() << "\n";
  }

}

void runPrompt() {
  for(;;) {
    std::cout << "> ";
    std::string line;
    if (!std::getline(std::cin, line)) break;
    run(line);
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

  std::cout << "exit jlox\n";
}