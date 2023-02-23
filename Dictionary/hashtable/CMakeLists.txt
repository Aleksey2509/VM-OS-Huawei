set(HASHTABLE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(HashTable INTERFACE)

target_include_directories(HashTable INTERFACE ${HASHTABLE_INCLUDES})

add_subdirectory(tests)
