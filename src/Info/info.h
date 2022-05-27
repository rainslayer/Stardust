#pragma once

#include "stardust.h"
#include <iomanip>
#include <iostream>
#include <string_view>

class Info {
private:
  Info();

public:
  static void PrintHelp();
  static void PrintProgramVersion();
};
