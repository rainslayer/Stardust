#include "config.h"

Config::Config() {}

Config::Config(const std::string &projectName,
               const std::string &currentBreakthrough,
               const AvailableBreakthroughs &availableBreakthroughs)
    : projectName(projectName), currentBreakthrough(currentBreakthrough),
      availableBreakthroughs(availableBreakthroughs) {}

const std::string Config::getProjectName() const { return projectName; }

const fs::path Config::getBasePath() const { return basePath; }

const std::string Config::getCurrentBreakthrough() const {
  return currentBreakthrough;
}

void Config::setBasePath(const fs::path &newBasePath) {
  basePath = newBasePath;
}

void Config::setCurrentBreakthrough(const std::string &newBreakthrough) {
  currentBreakthrough = newBreakthrough;
}

const AvailableBreakthroughs Config::getAvailableBreakthroughs() const {
  return availableBreakthroughs;
}

void Config::setAvailableBreakthrough(
        const AvailableBreakthroughs &breakthroughsListUpdated) {
  availableBreakthroughs = breakthroughsListUpdated;
}

void Config::FindConfig() {
  if (fs::exists(".stardust/")) {
    setBasePath(fs::current_path().string() + "/.stardust");
  }
}

void Config::LoadConfig() {
  FindConfig();

  if (basePath.empty()) {
    throw std::runtime_error(std::string(Messages::PROJECT_NOT_FOUND));
  }

  // Deserialize data from config file and write it into class fields
  {
    std::ifstream configFile{basePath.string() + "/.config"};
    cereal::BinaryInputArchive iarchive(configFile);

    iarchive(projectName, currentBreakthrough,
             availableBreakthroughs);
  }
  // ================================================================
}

// For now argument is only passed when initializing project.
// In all further operations we are going to use basePath deduced by Config
// class itself.
void Config::WriteConfig(std::string path) const {
  if (path.empty()) {
    path = basePath;
  }
  // Write config data to file
  std::ofstream projectConfig{path + "/.config"};
  cereal::BinaryOutputArchive oarchive(projectConfig);
  oarchive(projectName, currentBreakthrough,
           availableBreakthroughs);
}

std::ostream &operator<<(std::ostream &output, const Config &config) {
  std::stringstream availableBreakthroughs;
  availableBreakthroughs << '[';

  // Read std::vector content into string stream to be able to cout it
  // std::prev used to ignore last element of vector to prevent delimiter to be
  // inserted in the end of the string
  std::copy(config.availableBreakthroughs.begin(),
            std::prev(config.availableBreakthroughs.end()),
            std::ostream_iterator<std::string>(availableBreakthroughs, ", "));

  // After that - writes last value to stream
  availableBreakthroughs << config.availableBreakthroughs.back();

  availableBreakthroughs << ']';

  output << "Project: " << config.projectName << '\n'
         << "Working directory: " << config.getBasePath().parent_path().string()
         << '\n'
         << "Working breakthrough: " << config.currentBreakthrough << '\n'
         << "Breakthroughs available: " << availableBreakthroughs.str() << "\n";
  return output;
}
