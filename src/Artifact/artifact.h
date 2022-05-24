#pragma once

#include "../Config/config.h"
#include "Tarfful/src/tarfful.h"
#include <algorithm>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class Artifact {
private:
  Artifact();

public:
  static std::string GenHash();

  static void CreateArtifact(const std::vector<std::string> &filenames);

  static void PrintArtifactsLog();

  static void RevertArtifact(const std::string &hash);
};