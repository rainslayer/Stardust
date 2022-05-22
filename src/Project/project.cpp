#include "project.h"

Project::Project() { this->InitProject(); }

// Use 2nd program argument if passed as name for new project
Project::Project(const std::string &projectName) : projectName{projectName} {
  this->InitProject();
}

void Project::InitProject() {
  // Interactively initialize project if not passed by user
  if (this->projectName.empty()) {
    do {
      std::cout << "Enter project name: ";
      std::getline(std::cin, this->projectName);
    } while (this->projectName.empty());
  }
  this->GenerateProjectFiles();
}

void Project::GenerateProjectFiles() const {
  fs::create_directories(defaultBreakthroughPath.string() + "/artifacts");
  Config config(projectName, defaultBreakthrough, {defaultBreakthrough});
  config.WriteConfig(basePath);

  std::cout << "Initialized project: " << projectName << '\n'
            << "Working breakthrough: " << defaultBreakthrough << "\n";
}
