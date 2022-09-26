#Minimum cmake version
cmake_minimum_required(VERSION 3.11)
#Project info
project(stack VERSION 0.1)
#Choose language
enable_language(CXX)
#Add options
add_compile_options(-Wall -g -ggdb)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(STACK_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Stack INTERFACE)

target_include_directories(Stack INTERFACE ${STACK_INCLUDES})

add_subdirectory(tests)