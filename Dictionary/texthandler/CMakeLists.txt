set(TEXTHANDLER_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TEXTHANDLER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEXTHANDLER_SRC texthandler.cc)

add_library(TextHandler STATIC ${TEXTHANDLER_SRC_DIR}/${TEXTHANDLER_SRC})

target_include_directories(TextHandler PUBLIC ${TEXTHANDLER_INCLUDES})

add_subdirectory(tests)
