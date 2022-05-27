#pragma once

#include "../Utils/Messages/messages.h"
#include "cereal/archives/binary.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include <exception>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>

namespace fs = std::filesystem;
using AvailableBreakthroughs = std::vector<std::string>;

class Config {
private:
  std::string projectName;
  std::string currentBreakthrough;
  fs::path basePath;
  AvailableBreakthroughs availableBreakthroughs;

public:
  Config();

  explicit Config(const std::string &projectName,
                  const std::string &currentBreakthrough,
                  const AvailableBreakthroughs &availableBreakthrough);

  const std::string getProjectName() const;

  const fs::path getBasePath() const;

  const std::string getCurrentBreakthrough() const;

  void setBasePath(const fs::path &newBasePath);

  void setCurrentBreakthrough(const std::string &newBreakthrough);

  const AvailableBreakthroughs getAvailableBreakthroughs() const;

  void setAvailableBreakthrough(
      const AvailableBreakthroughs &breakthroughsListUpdated);

  void FindConfig();

  void LoadConfig();

  void WriteConfig(std::string basePath = "") const;

  // Required for serialization of class fields
  template <class Archive> void serialize(const Archive &archive) {
    archive(this->projectName, this->currentBreakthrough,
            this->availableBreakthroughs);
  }

  friend std::ostream &operator<<(std::ostream &output, const Config &config);
};

std::ostream &operator<<(std::ostream &output, const Config &config);
