#include "config.h"

Config::Config() {}

Config::Config(const std::string &projectName,
               const std::string &currentBreakthrough,
               const AvailableBreakthroughs &availableBreakthroughs)
    : projectName(projectName), currentBreakthrough(currentBreakthrough),
      availableBreakthroughs(availableBreakthroughs) {}

const std::string Config::getProjectName() const { return projectName; }

const fs::path Config::getBasePath() const { return this->basePath; }

const std::string Config::getCurrentBreakthrough() const {
  return this->currentBreakthrough;
}

void Config::setBasePath(const fs::path &newBasePath) {
  this->basePath = newBasePath;
}

void Config::setCurrentBreakthrough(const std::string &newBreakthrough) {
  this->currentBreakthrough = newBreakthrough;
}

const AvailableBreakthroughs Config::getAvailableBreakthroughs() const {
  return this->availableBreakthroughs;
}

void Config::setAvailableBreakthrough(
    const AvailableBreakthroughs &breakthroughsListUpdated) {
  this->availableBreakthroughs = std::move(breakthroughsListUpdated);
}

void Config::FindConfig() {
      if (fs::exists(".stardust/")) {
        setBasePath(fs::current_path().string() + "/.stardust");
      }
}

void Config::LoadConfig() {
  this->FindConfig();

  if (this->basePath.empty()) {
    throw std::runtime_error(std::string(Messages::PROJECT_NOT_FOUND));
  }

  // Deserialize data from config file and write it into class fields
  {
    std::ifstream configFile{this->basePath.string() + "/.config"};
    cereal::BinaryInputArchive iarchive(configFile);

    iarchive(this->projectName, this->currentBreakthrough,
             this->availableBreakthroughs);
  }
  // ================================================================
}

// For now argument is only passed when initializing project.
// In all further operations we are going to use basePath deduced by Config
// class itself.
void Config::WriteConfig(std::string basePath) const {
  if (basePath.empty()) {
    basePath = this->basePath;
  }
  // Write config data to file
  std::ofstream projectConfig{basePath + "/.config"};
  cereal::BinaryOutputArchive oarchive(projectConfig);
  oarchive(this->projectName, this->currentBreakthrough,
           this->availableBreakthroughs);
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
