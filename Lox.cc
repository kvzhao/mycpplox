
#include <cstring>      // std::strerror
#include <fstream>      // readFile
#include <iostream>     // std::getline
#include <string>
#include <vector>

#include "token.hpp"


int main(int argc, char* argv[]) {
  if (argc > 2) {
    std::cout << "Usage: jlox [script]\n";
    std::exit(64);
  } else if (argc == 2) {
  } else {
  }

  Token t;


  std::cout << "exit jlox\n";
}