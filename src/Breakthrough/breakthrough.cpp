#include "breakthrough.h"

void Breakthrough::CreateBreakthrough(const std::string &breakthroughName) {
  Config config;
  config.LoadConfig();

  auto breakthroughs = config.getAvailableBreakthroughs();

  if (std::count(breakthroughs.begin(), breakthroughs.end(),
                 breakthroughName)) {
    throw std::runtime_error(
        std::string(Messages::BREAKTHROUGH_ALREADY_EXISTS));
  }

  breakthroughs.push_back(breakthroughName);
  fs::create_directories(config.getBasePath().string() + "/breakthroughs/" +
                         breakthroughName + "/artifacts");
  config.setAvailableBreakthrough(breakthroughs);
  config.WriteConfig();

  std::cout << "[stardust-success]: Breakthrough " << breakthroughName
            << " created\n";
}

void Breakthrough::RemoveBreakthrough(const std::string &breakthroughName) {
  Config config;
  config.LoadConfig();
  auto breakthroughs = config.getAvailableBreakthroughs();

  if (breakthroughs.size() == 1) {
    throw std::runtime_error(
        std::string(Messages::ATTEMPT_TO_REMOVE_SINGLE_EXISTING_BREAKTHROUGH));
  }

  if (config.getCurrentBreakthrough() == breakthroughName) {
    throw std::runtime_error(
        std::string(Messages::ATTEMPT_TO_REMOVE_WORKING_BREAKTHROUGH));
  }

  if (!std::count(breakthroughs.begin(), breakthroughs.end(),
                  breakthroughName)) {
    throw std::runtime_error(std::string(Messages::BREAKTHROUGH_DOESNT_EXISTS));
  }

  char userAnswer{};
  std::cout << "[stardust-warning]: This operation will remove ALL data stored "
               "in selected breakthrough.\n"
               "This may result in the loss of important data\n"
               "Do you want to proceed? (y/n): ";

  std::cin.get(userAnswer);

  if (userAnswer == 'y') {
    breakthroughs.erase(std::remove(breakthroughs.begin(), breakthroughs.end(),
                                    breakthroughName),
                        breakthroughs.end());
    fs::remove_all(config.getBasePath().string() + "/breakthroughs/" +
                   breakthroughName);

    config.setAvailableBreakthrough(breakthroughs);
    config.WriteConfig();

    std::cout << "[stardust-success]: Breakthrough " << breakthroughName
              << " removed\n";
  } else {
    std::cout << "[stardust-info]: Aborting...\n";
  }
}

void Breakthrough::SwitchBreakthrough(const std::string &breakthroughName) {
  Config config;
  config.LoadConfig();

  auto breakthroughs = config.getAvailableBreakthroughs();

  if (!std::count(breakthroughs.begin(), breakthroughs.end(),
                  breakthroughName) ||
      !fs::exists(config.getBasePath().string() + "/breakthroughs/" +
                  breakthroughName)) {
    throw std::runtime_error(std::string(Messages::BREAKTHROUGH_DOESNT_EXISTS));
  }

  config.setCurrentBreakthrough(breakthroughName);
  config.WriteConfig();

  std::cout << "[stardust-success]: Breakthrough " << breakthroughName
            << " set as working\n";
}