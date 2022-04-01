#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/archives/binary.hpp"

namespace fs = std::filesystem;
using AvailableBranches = std::vector<std::string>;

class Config {
private:
    std::string projectName{};
    std::string currentBranch{};
    std::string basePath{};
    AvailableBranches availableBranches{};

public:
    Config();

    explicit Config(std::string projectName,
                    std::string currentBranch,
                    AvailableBranches availableBranches);

    const std::string &getBasePath() const;

    const std::string &getCurrentBranch() const;

    void setBasePath(const std::string &newBasePath);

    void setCurrentBranch(const std::string &newBranch);

    const AvailableBranches &getAvailableBranches() const;

    void setAvailableBranches(AvailableBranches branchesListUpdated);

    void FindConfig();

    void LoadConfig();

    void WriteConfig(std::string basePath = "") const;

    // Required for serialization of class fields
    template<class Archive>
    void serialize(Archive &archive) {
        archive(this->projectName, this->currentBranch,
                this->availableBranches);
    }

    friend std::ostream &operator<<(std::ostream &output, const Config &config);
};

std::ostream &operator<<(std::ostream &output, const Config &config);


