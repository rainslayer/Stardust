#pragma once

#include <iostream>
#include <string_view>
#include "stardust.h"

class Info {
private:
    const std::string_view help{
            "Usage: stardust <arguments> [project | filename(s)]\n\n"
            "List of arguments:\n"
            "version \t\t\t Print program version\n"
            "help \t\t\t\t Print this help\n"
            "status \t\t\t\t Print project information and current status\n"
            "init          [project name]\t Init project in current directory\n"
            "add-branch    [branch name]\t Create new branch\n"
            "remove-branch [branch name]\t Remove branch\n"
            "switch-branch [branch name]\t Switch to another branch\n"
    };

    void printHelp() const;

public:
    Info();
    explicit Info(const std::string_view programArgument);
};



