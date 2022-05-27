#pragma once

#include <string_view>

namespace Messages {
constexpr std::string_view BREAKTHROUGH_ALREADY_EXISTS =
    "[stardust-error]: Breakthrough already exists\n";

constexpr std::string_view ATTEMPT_TO_REMOVE_SINGLE_EXISTING_BREAKTHROUGH =
    "[stardust-error]: Unable to remove a single existing "
    "breakthrough.\nIf you "
    "want "
    "to remove it - create new breakthrough and merge data into it.\nAfter "
    "that "
    "you will be able to remove the source breakthrough.\n";

constexpr std::string_view ATTEMPT_TO_REMOVE_WORKING_BREAKTHROUGH =
    "[stardust-error]: Unable to remove working breakthrough.\n"
    "Please, switch to different breakthrough and try again\n";

constexpr std::string_view BREAKTHROUGH_DOESNT_EXISTS =
    "[stardust-error]: Breakthrough doesn't exists\n";

constexpr std::string_view PROJECT_NOT_FOUND =
    "[stardust-error]: Could not find stardust project\n"
    "Make sure you are in project root directory or use\n"
    "<stardust init> to initialize new project\n";

constexpr std::string_view PROJECT_ALREDY_EXISTS =
    "[stardust-error]: Project already exists for current path\n";

constexpr std::string_view SPECIFY_BREAKTHROUGH =
    "[stardust-error]: Please, specify breakthrough name\n";

constexpr std::string_view SPECIFY_FILES =
    "[stardust-error]: Please, specify at least one path to be stored in "
    "artifact\n";

constexpr std::string_view SPECIFY_HASH =
    "[stardust-error]: Please, enter artifact hash\n";

constexpr std::string_view ARTIFACT_NOT_FOUND =
    "[stardust-error]: Artifact not found. Please enter the correct hash\n";
} // namespace Messages
