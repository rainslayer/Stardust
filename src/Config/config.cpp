#include "config.h"

Config::Config() {}

Config::Config(std::string projectName,
               std::string currentBranch,
               AvailableBranches availableBranches) : projectName(projectName), currentBranch(currentBranch),
                                                      availableBranches(availableBranches) {}

const std::string &Config::getBasePath() const {
    return this->basePath;
}

const std::string &Config::getCurrentBranch() const {
    return this->currentBranch;
}

void Config::setBasePath(const std::string &newBasePath) {
    this->basePath = newBasePath;
}

void Config::setCurrentBranch(const std::string &newBranch) {
    this->currentBranch = newBranch;
}

const AvailableBranches &Config::getAvailableBranches() const {
    return this->availableBranches;
}

void Config::setAvailableBranches(AvailableBranches branchesListUpdated) {
    this->availableBranches = std::move(branchesListUpdated);
}

void Config::FindConfig() {
    // Read the path from where the program was called
    auto searchPath{fs::current_path()};

    // Look for project config file in <= 10 upper directories
    for (size_t nestingIterator = 0, maxNesting = 10; nestingIterator <= maxNesting; ++nestingIterator) {
        // Iterate over all content of current directory
        for (const auto &dir_iterator: fs::directory_iterator{searchPath}) {
            // .stardust is a service directory, if found and wasn't created by user manually - found root path of project
            if (dir_iterator.path().string().ends_with(".stardust")) {
                // Write path to config to class field and break loop over directory content
                this->setBasePath(searchPath.string() + "/.stardust");
                break;
            }
        }
        // If basePath was found - break outer loop
        if (this->basePath.empty()) {
            searchPath = searchPath.parent_path();
        } else {
            break;
        }
    }
}

void Config::LoadConfig() {
    this->FindConfig();

    if (this->basePath.empty()) {
        throw "stardust-error: Could not find stardust project\n"
              "Make sure you are in right directory or use\n"
              "<stardust init> to initialize new project\n";
    }

    // Deserialize data from config file and write it into class fields
    {
        std::ifstream configFile{this->basePath + "/.config"};
        cereal::BinaryInputArchive iarchive(configFile);

        iarchive(this->projectName, this->currentBranch,
                 this->availableBranches);
    }
    // ================================================================
}

// For now argument is only passed when initializing project.
// In all further operations we are going to use basePath deduced by Config class itself.
void Config::WriteConfig(std::string basePath) const {
    if (basePath.empty()) {
        basePath = this->basePath;
    }
    // Write config data to file
    std::ofstream projectConfig{basePath + "/.config"};
    cereal::BinaryOutputArchive oarchive(projectConfig);
    oarchive(this->projectName, this->currentBranch, this->availableBranches);
}

std::ostream &operator<<(std::ostream &output, const Config &config) {
    std::stringstream availableBranches;
    availableBranches << '[';

    // Read std::vector content into string stream to be able to cout it
    // std::prev used to ignore last element of vector to prevent delimiter to be inserted in the end of the string
    std::copy(config.availableBranches.begin(), std::prev(config.availableBranches.end()),
              std::ostream_iterator<std::string>(availableBranches, ", "));

    // After that - writes last value to stream
    availableBranches << config.availableBranches.back();

    availableBranches << ']';

    output << "Project: " << config.projectName << '\n' <<
           "On branch: " << config.currentBranch << '\n' <<
           "Branches available: " << availableBranches.str() << "\n";
    return output;
}