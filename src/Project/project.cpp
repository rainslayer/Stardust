#include "project.h"

Project::Project() {
    this->InitProject();
}

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
        this->GenerateProjectFiles();
    } else {
        this->GenerateProjectFiles();
    }
}

void Project::GenerateProjectFiles() const {
    std::filesystem::create_directories(this->defaultBranchPath);
    Config config(this->projectName, this->defaultBranch, {this->defaultBranch});
    config.WriteConfig(this->basePath);

    std::cout << "Initialized project: " << this->projectName << '\n' <<
              "Currently in branch: " << this->defaultBranch << "\n";
}
