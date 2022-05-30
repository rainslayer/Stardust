#pragma once

#include "../Config/config.h"
#include "cereal/archives/binary.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

class Project {
  private:
  std::string projectName = "";
  const std::string defaultBreakthrough = "main";
  const std::string basePath = ".stardust/";
  const fs::path defaultBreakthroughPath =
          basePath + "breakthroughs/" + defaultBreakthrough;

  void InitProject();

  void GenerateProjectFiles() const;

  public:
  Project();

  explicit Project(const std::string &projectName);
};
