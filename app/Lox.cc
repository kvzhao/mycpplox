
#include <cstring>  // std::strerror
#include <fstream>  // readFile
#include <iostream> // std::getline
#include <string>
#include <vector>

#include "error.hpp"
#include "scanner.hpp"
#include "token.hpp"

std::string ReadFile(std::string_view path) {
  std::ifstream file{path.data(),
                     std::ios::in | std::ios::binary | std::ios::ate};
  if (!file) {
    std::cerr << "Failed to open file " << path << ": " << std::strerror(errno)
              << "\n";
    std::exit(74);
  }

  std::string contents;
  contents.resize(file.tellg());

  file.seekg(0, std::ios::beg);
  file.read(contents.data(), contents.size());

  return contents;
}

void Run(std::string_view source) {
  Scanner scanner{source};
  std::vector<Token> tokens = scanner.ScanTokens();

  for (const auto &t : tokens) {
    std::cout << t.ToString() << "\n";
  }
}

void RunPrompt() {
  for (;;) {
    std::cout << "> ";
    std::string line;
    if (!std::getline(std::cin, line))
      break;
    Run(line);
  }
}

void RunFile(std::string_view path) {
  std::string contents = ReadFile(path);

  Run(contents);

  if (hadError) {
    std::exit(65);
  }
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::cout << "Usage: jlox [script]\n";
    std::exit(64);
  } else if (argc == 2) {
    RunFile(argv[1]);
  } else {
    RunPrompt();
  }
}