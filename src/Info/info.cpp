#include "info.h"

Info::Info() {
    Info::printHelp();
}

Info::Info(const std::string_view programArgument) {
    if (programArgument == "version") {
        std::cout << "stardust-version: v" << stardust_VERSION_MAJOR << "." << stardust_VERSION_MINOR << '\n';
    } else if (programArgument == "help") {
        Info::printHelp();
    } else {
        Info::printHelp();
    }
}

void Info::printHelp() const {
    std::cout << help;
}