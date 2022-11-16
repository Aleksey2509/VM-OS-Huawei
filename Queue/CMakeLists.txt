cmake_minimum_required(VERSION 3.16)

project(queue VERSION 0.5)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QUEUE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(QUEUE_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(QUEUE_SOURCE_FILES queue.cc)
set(QUEUE_SOURCES ${QUEUE_SOURCES_DIR}/${QUEUE_SOURCE_FILES})

add_library(Queue STATIC ${QUEUE_SOURCES})

target_include_directories(Queue PUBLIC ${QUEUE_INCLUDES})
target_link_libraries(Queue PUBLIC Stack List)

add_dependencies(Queue Stack List)
add_subdirectory(list)
add_subdirectory(stack)
#add_subdirectory(tests)