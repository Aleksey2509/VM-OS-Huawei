set(CORRECTOR_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CORRECTOR_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CORRECTOR_SRC corrector.cc)

add_library(Corrector STATIC ${CORRECTOR_SRC_DIR}/${CORRECTOR_SRC})

target_include_directories(Corrector PUBLIC ${CORRECTOR_INCLUDES})

add_dependencies(Corrector HashTable)

# add_subdirectory(tests)
