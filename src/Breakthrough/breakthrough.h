#pragma once

#include "../Config/config.h"
#include "../Utils/Messages/messages.h"
#include <algorithm>
#include <exception>
#include <filesystem>
#include <iostream>
#include <string>

class Breakthrough {
  public:
  static void CreateBreakthrough(const std::string &breakthroughName);
  static void RemoveBreakthrough(const std::string &breakthroughName);
  static void SwitchBreakthrough(const std::string &breakthroughName);

  private:
  Breakthrough() = default;
};