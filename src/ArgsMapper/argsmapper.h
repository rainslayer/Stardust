#pragma once

#include "../Artifact/artifact.h"
#include "../Breakthrough/breakthrough.h"
#include "../Config/config.h"
#include "../Info/info.h"
#include "../Project/project.h"
#include "../Utils/Messages/messages.h"
#include "argsmapper.h"
#include <exception>
#include <string>

class ArgsMapper {
private:
  ArgsMapper();

public:
  static void MapArgs(const int argc, const char *argv[]);
};
