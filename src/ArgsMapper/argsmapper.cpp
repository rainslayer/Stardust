#include "argsmapper.h"

ArgsMapper::ArgsMapper(char *argv[]) {
    if (argv[1]) {
        const auto firstParameter = static_cast<const std::string>(argv[1]);
        if (firstParameter == "init") {

            Config config;
            config.FindConfig();

            // If basePath not empty - project already initialized for this directory and can't be reloaded
            if (!config.getBasePath().empty()) {
                throw "stardust-error: Project already exists for current path\n";
            }

            // If project name passed as 2nd argument - use it to initialize new project
            if (argv[2]) {
                const Project project(static_cast<const std::string>(argv[2]));
                // Create interactively instead
            } else {
                const Project project;
            }
        } else if (firstParameter == "status") {
            Config config;
            config.LoadConfig();
            std::cout << config;
        } else if (firstParameter == "add-branch") {
            if (!argv[2]) {
                throw "stardust-error: Please, specify branch name\n";
            }

            Branch::CreateBranch(static_cast<const std::string>(argv[2]));
        } else if (firstParameter == "remove-branch") {
            if (!argv[2]) {
                throw "stardust-error: Please, specify branch name\n";
            }

            Branch::RemoveBranch(static_cast<const std::string>(argv[2]));
        } else if (firstParameter == "switch-branch") {
            if (!argv[2]) {
                throw "stardust-error: Please, specify branch name\n";
            }

            Branch::SwitchBranch(static_cast<const std::string>(argv[2]));
        } else {
            const Info info(firstParameter);
        }
    } else {
        const Info info;
    }
}
