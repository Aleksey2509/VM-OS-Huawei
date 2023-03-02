cmake_minimum_required(VERSION 3.16)

project(dictionary VERSION 0.5)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

find_package(benchmark REQUIRED)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIST_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/list/include)
set(HASHTABLE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/hashtable/include)
set(CORRECTOR_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/corrector/include)
set(TEXTHANDLER_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/texthandler/include)
set(LOGGER_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/logger/include)

include_directories(${HASHTABLE_INCLUDES} ${CORRECTOR_INCLUDES} ${LIST_INCLUDES}
                    ${TEXTHANDLER_INCLUDES} ${LOGGER_INCLUDES})

set (DATA_BASE_FILE ${CMAKE_SOURCE_DIR}/data_base)
add_compile_definitions(STANDART_DATA_BASE="${DATA_BASE_FILE}")

set (DEF_LOG_FILE_NAME ${CMAKE_SOURCE_DIR}/replacement_log)
add_compile_definitions(DEFAULT_LOG_FILE_NAME="${DEF_LOG_FILE_NAME}")

file(GLOB_RECURSE ALL_SOURCE_FILES ./include/*.hh */include/*.hh */source/*.cc)

find_program(CLANG_TIDY "clang-tidy")
if (CLANG_TIDY)

    add_custom_target(
        clang_tidy
        COMMAND clang-tidy ${ALL_SOURCE_FILES} --format-style=file
        -I${HASHTABLE_INCLUDES}
    )

    message(STATUS "clang-tidy target ON")

else()
    message(STATUS "clang-tidy target OFF")

endif()

find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
        add_custom_target(
            format
            COMMAND clang-format
            -style=file
            -i
            ${ALL_SOURCE_FILES}
        )
        message(STATUS "clang-format target ON")
endif()

if (SANITIZERS)
    message(STATUS "Sanitizers ON")
else()
    message(STATUS "Sanitizers OFF")
endif()

add_subdirectory(list)
add_subdirectory(hashtable)
add_subdirectory(corrector)
add_subdirectory(texthandler)
#add_dependencies(dictionary List)
