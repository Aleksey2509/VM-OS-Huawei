set(TEXTHANDLER_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TEXTHANDLER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEXTHANDLER_SRC texthandler.cc)

add_library(TextHandler STATIC ${TEXTHANDLER_SRC_DIR}/${TEXTHANDLER_SRC})

set (DATA_BASE_FILE ${CMAKE_SOURCE_DIR}/data_base)

target_include_directories(TextHandler PUBLIC ${TEXTHANDLER_INCLUDES})
add_compile_definitions(STANDART_DATA_BASE="${DATA_BASE_FILE}")

add_dependencies(TextHandler Corrector)

add_subdirectory(tests)
