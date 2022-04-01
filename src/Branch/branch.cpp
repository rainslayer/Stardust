#include "branch.h"

void Branch::CreateBranch(const std::string branchName) {
    Config config;
    config.LoadConfig();

    auto branches = config.getAvailableBranches();

    if (std::count(branches.begin(), branches.end(), branchName)) {
        throw "stardust-error: Branch already exists\n";
    }

    branches.push_back(branchName);
    fs::create_directory(config.getBasePath() + "/branches/" + branchName);
    config.setAvailableBranches(branches);
    config.WriteConfig();

    std::cout << "stardust-success: Branch " << branchName << " created\n";
}

void Branch::RemoveBranch(const std::string branchName) {
    Config config;
    config.LoadConfig();
    auto branches = config.getAvailableBranches();

    if (branches.size() == 1) {
        throw "stardust-error: Unable to remove a single existing branch.\nIf you want to remove it - create new branch "
              "and merge data into it.\nAfter that you will be able to remove the source branch.\n";
    }

    if (config.getCurrentBranch() == branchName) {
        throw "stardust-error: Unable to remove working branch.\n"
              "Please, switch to different branch and try again\n";
    }

    if (!std::count(branches.begin(), branches.end(), branchName)) {
        throw "stardust-error: Branch doesn't exists\n";
    }

    char userAnswer{};
    std::cout << "stardust-warning: This operation will remove ALL data stored in selected branch.\n"
                 "This may result in the loss of important data\n"
                 "Do you want to proceed? (y/n): ";

    std::cin.get(userAnswer);

    if (userAnswer == 'y') {
        branches.erase(std::remove(branches.begin(), branches.end(), branchName), branches.end());
        fs::remove_all(config.getBasePath() + "/branches/" + branchName);

        config.setAvailableBranches(branches);
        config.WriteConfig();

        std::cout << "stardust-success: Branch " << branchName << " removed\n";
    } else {
        throw "stardust-info: Aborting...\n";
    }
}

void Branch::SwitchBranch(const std::string branchName) {
    Config config;
    config.LoadConfig();

    auto branches = config.getAvailableBranches();

    if (!std::count(branches.begin(), branches.end(), branchName) ||
        !fs::exists(config.getBasePath() + "/branches/" + branchName)) {
        throw "stardust-error: Branch doesn't exists\n";
    }

    config.setCurrentBranch(branchName);
    config.WriteConfig();

    std::cout << "stardust-success: Branch " << branchName << " set as working\n";
}