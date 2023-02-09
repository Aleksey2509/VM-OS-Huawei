cmake_minimum_required(VERSION 3.16)

project(dictionary VERSION 0.5)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

find_package(benchmark REQUIRED)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIST_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/list/include)
set(HASHMAP_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/hashmap/include)

file(GLOB_RECURSE ALL_SOURCE_FILES ./include/*.hh */include/*.hh */source/*.cc)

find_program(CLANG_TIDY "clang-tidy")
if (CLANG_TIDY)

    add_custom_target(
        clang_tidy
        COMMAND clang-tidy ${ALL_SOURCE_FILES} --format-style=file
        -I${LIST_INCLUDES} -I${HASHMAP_INCLUDES}
    )

    message(STATUS "clang-tidy target ON")

else()
    message(STATUS "clang-tidy target OFF")

endif()

find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
        add_custom_target(
            format
            COMMAND clang-format
            -style=file
            -i
            ${ALL_SOURCE_FILES}
        )
        message(STATUS "clang-format target ON")
endif()

add_subdirectory(list)
add_subdirectory(hashtable)
#add_dependencies(dictionary List)
