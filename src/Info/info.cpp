#include "info.h"

void Info::PrintProgramVersion() {
  std::cout << "[stardust-version]: v" << stardust_VERSION_MAJOR << '.'
            << stardust_VERSION_MINOR << '.' << stardust_VERSION_PATCH << '\n';
}

// Horrible
void Info::PrintHelp() {
  std::cout << "Usage: stardust <arguments> [project | filename(s) | "
               "breakthrough | "
               "artifact]\n\n"
               "List of arguments:\n"
            << "version" << std::setw(70) << "Print program version\n"
            << "help" << std::setw(67) << "Print this help\n"
            << "status" << std::setw(94)
            << "Print project information and current status\n"
            << "log" << std::setw(101)
            << "Print list of artifacts for current breakthrough\n"
            << "init" << std::setw(35) << "[project name]" << std::setw(50)
            << "Init project in current directory\n"
            << "add-breakthrough" << std::setw(28) << "[breakthrough name]"
            << std::setw(35) << "Create new breakthrough\n"
            << "remove-breakthrough" << std::setw(25) << "[breakthrough name]"
            << std::setw(31) << "Remove breakthrough\n"
            << "switch-breakthrough" << std::setw(25) << "[breakthrough name]"
            << std::setw(42) << "Switch to another breakthrough\n"
            << "create-artifact" << std::setw(19) << "[file(s)]"
            << std::setw(41) << "Create new artifact\n"
            << "revert-artifact" << std::setw(25) << "[artifact hash]"
            << std::setw(44) << "Revert content from artifact\n";
}