#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "../Config/config.h"
#include "cereal/archives/binary.hpp"

namespace fs = std::filesystem;

class Project {
private:
    std::string projectName{};
    const std::string defaultBranch{"main"};
    const std::string basePath{".stardust/"};
    const fs::path defaultBranchPath{this->basePath + "branches/" + this->defaultBranch};

    void InitProject();

    void GenerateProjectFiles() const;

public:
    Project();

    explicit Project(const std::string &projectName);
};



