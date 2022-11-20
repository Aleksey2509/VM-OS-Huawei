cmake_minimum_required(VERSION 3.16)

project(queue VERSION 0.5)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

find_package(benchmark REQUIRED)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QUEUE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${QUEUE_INCLUDES})

add_library(Queue INTERFACE)

target_include_directories(Queue INTERFACE ${QUEUE_INCLUDES})
target_link_libraries(Queue INTERFACE Stack)

add_subdirectory(list)
add_subdirectory(stack)
add_subdirectory(tests)
add_subdirectory(benchmark)
add_dependencies(Queue Stack List)
