#Minimum cmake version
cmake_minimum_required(VERSION 3.11)
#Project info
project(stack VERSION 0.1)
#Choose language
enable_language(CXX)
#Add options
add_compile_options(-Wall -g -ggdb)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TIDY_ENABLED "Enable clang-tidy" ON)

if (TIDY_ENABLED)
set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    --format-style=file;
    --header-filter=.*;
    )
    message(STATUS "clang-tidy ON")

endif()

option(FORMAT_ENABLED "Enable clang-format" ON)

if (FORMAT_ENABLED)
    file(GLOB_RECURSE ALL_SOURCE_FILES *.cc *.hh)
        add_custom_target(
            format
            COMMAND clang-tidy
            -style=file
            -i
            ${ALL_SOURCE_FILES}
        )
        message(STATUS "clang-format ON")

endif()

set(STACK_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Stack INTERFACE)

target_include_directories(Stack INTERFACE ${STACK_INCLUDES})

add_subdirectory(tests)