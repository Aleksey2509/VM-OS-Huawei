set(LIST_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(List INTERFACE)

include_directories(${LIST_INCLUDES})

target_include_directories(List INTERFACE ${LIST_INCLUDES})

add_subdirectory(tests)
