#Minimum cmake version
cmake_minimum_required(VERSION 3.11)
#Project info
project(stack VERSION 0.5)
#Choose language
enable_language(CXX)
#Add options

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(STACK_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Stack INTERFACE)

target_include_directories(Stack INTERFACE ${STACK_INCLUDES})

if (ENABLE_TIDY)
set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    --header-filter=include/*;
    --format-style=file;
    )
    message(STATUS "clang-tidy ON")

else()
    message(STATUS "clang-tidy OFF")

endif()


file(GLOB_RECURSE ALL_SOURCE_FILES *.cc *.hh)
    add_custom_target(
        format
        COMMAND clang-tidy
        -style=file
        -i
        ${ALL_SOURCE_FILES}
    )
    message(STATUS "clang-format target ON")


add_subdirectory(tests)