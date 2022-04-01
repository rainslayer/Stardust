cmake_minimum_required(VERSION 3.10)

project(stardust VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}_build")
add_compile_options(-Wall -Wextra -pedantic -O2 )

configure_file(stardust.in stardust.h)

add_executable(stardust stardust.cxx
        src/Info/info.cpp src/Info/info.h
        src/Project/project.cpp src/Project/project.h
        src/ArgsMapper/argsmapper.cpp src/ArgsMapper/argsmapper.h
        src/Config/config.cpp src/Config/config.h
        src/Branch/branch.cpp src/Branch/branch.h)


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

