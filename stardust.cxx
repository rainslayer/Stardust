#include "src/ArgsMapper/argsmapper.h"
#include <exception>
#include <iostream>

int main(const int argc, const char *argv[]) {

  try {
    ArgsMapper::MapArgs(argc, argv);
  } catch (const std::exception &ex) {
    std::cerr << ex.what();
  }

  return 0;
}
