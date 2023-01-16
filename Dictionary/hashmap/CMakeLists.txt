set(HASHMAP_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Hashmap INTERFACE)

include_directories(${HASHMAP_INCLUDES})

target_include_directories(Hashmap INTERFACE ${HASHMAP_INCLUDES})

add_subdirectory(tests)
