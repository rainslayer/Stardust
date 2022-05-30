#include "project.h"

Project::Project() { InitProject(); }

// Use 2nd program argument if passed as name for new project
Project::Project(const std::string &projectName) : projectName{projectName} {
  InitProject();
}

void Project::InitProject() {
  // Interactively initialize project if not passed by user
  if (projectName.empty()) {
    do {
      std::cout << "Enter project name: ";
      std::getline(std::cin, projectName);
    } while (projectName.empty());
  }
  GenerateProjectFiles();
}

void Project::GenerateProjectFiles() const {
  fs::create_directories(defaultBreakthroughPath.string() + "/artifacts");
  Config config(projectName, defaultBreakthrough, {defaultBreakthrough});
  config.WriteConfig(basePath);

  std::ofstream ignoreFile(".stardust-ignore");

  std::cout << "Initialized project: " << projectName << '\n'
            << "Working breakthrough: " << defaultBreakthrough << "\n";
}
