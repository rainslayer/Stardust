cmake_minimum_required(VERSION 3.10)

project(stardust VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}_build")
add_compile_options(-Wall -Wextra -Werror -pedantic -O2)

configure_file(stardust.in stardust.h)

add_executable(stardust stardust.cxx
        src/Info/info.cpp src/Info/info.h
        src/Project/project.cpp src/Project/project.h
        src/ArgsMapper/argsmapper.cpp src/ArgsMapper/argsmapper.h
        src/Config/config.cpp src/Config/config.h
        src/Breakthrough/breakthrough.cpp src/Breakthrough/breakthrough.h
        src/Artifact/artifact.cpp src/Artifact/artifact.h
        )

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/cereal/include")