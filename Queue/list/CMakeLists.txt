set(LIST_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(List INTERFACE ${LIST_INCLUDES})

include_directories(${LIST_INCLUDES})

add_subdirectory(tests)