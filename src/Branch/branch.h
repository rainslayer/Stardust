#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include "../Config/config.h"

class Branch {
public:
    static void CreateBranch(const std::string branchName);
    static void RemoveBranch(const std::string branchName);
    static void SwitchBranch(const std::string branchName);

private:
    Branch();
};