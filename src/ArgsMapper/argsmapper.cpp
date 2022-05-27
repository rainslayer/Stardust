#include "argsmapper.h"

void ArgsMapper::MapArgs(const int argc, const char *argv[]) {
  if (argv[1]) {
    const auto firstParameter = std::string(argv[1]);
    if (firstParameter == "init") {
      Config config;
      config.FindConfig();

      // If basePath not empty - project already initialized for this directory
      // and can't be reloaded
      if (!config.getBasePath().empty()) {
        throw std::runtime_error(std::string(Messages::PROJECT_ALREDY_EXISTS));
      }

      // If project name passed as 2nd argument - use it to initialize new
      // project
      if (argv[2]) {
        const auto project = std::make_unique<Project>(argv[2]);
        // Create interactively instead
      } else {
        const Project project;
      }
    } else if (firstParameter == "status") {
      Config config;
      config.LoadConfig();
      std::cout << config;
    } else if (firstParameter == "add-breakthrough") {
      if (!argv[2]) {
        throw std::runtime_error(std::string(Messages::SPECIFY_BREAKTHROUGH));
      }

      Breakthrough::CreateBreakthrough(argv[2]);
    } else if (firstParameter == "remove-breakthrough") {
      if (!argv[2]) {
        throw std::runtime_error(std::string(Messages::SPECIFY_BREAKTHROUGH));
      }

      Breakthrough::RemoveBreakthrough(argv[2]);
    } else if (firstParameter == "switch-breakthrough") {
      if (!argv[2]) {
        throw std::runtime_error(std::string(Messages::SPECIFY_BREAKTHROUGH));
      }

      Breakthrough::SwitchBreakthrough(argv[2]);
    } else if (firstParameter == "create-artifact") {
      if (!argv[2]) {
        throw std::runtime_error(std::string(Messages::SPECIFY_FILES));
      }
      Artifact::CreateArtifact(std::vector<std::string>(argv + 2, argv + argc));
    } else if (firstParameter == "log") {
      Artifact::PrintArtifactsLog();
    } else if (firstParameter == "revert-artifact") {
      if (!argv[2]) {
        throw std::runtime_error(std::string(Messages::SPECIFY_HASH));
      }
      Artifact::RevertArtifact(argv[2]);
    } else if (firstParameter == "version") {
      Info::PrintProgramVersion();
    } else {
      Info::PrintHelp();
    }
  } else {
    Info::PrintHelp();
  }
}
