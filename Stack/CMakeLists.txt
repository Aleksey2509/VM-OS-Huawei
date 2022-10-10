#Minimum cmake version
cmake_minimum_required(VERSION 3.17)
#Project info
project(stack VERSION 0.5)
#Choose language
enable_language(CXX)
#Add options

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(STACK_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(STACK_BOOL_SRC stack-bool.cc)
set(STACK_BOOL_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

add_library(Stack INTERFACE)

target_include_directories(Stack INTERFACE ${STACK_INCLUDES})
target_sources(Stack PUBLIC ${STACK_BOOL_SRC_DIR}/${STACK_BOOL_SRC})

option(TRY_MAKE_TARGET "Making clang-tidy check as a target" ON)

if(TRY_MAKE_TARGET)
    find_program(CLANG_TIDY "clang-tidy")
    if (CLANG_TIDY)

        add_custom_target(clang-tidy
        COMMAND clang-tidy ${STACK_BOOL_SRC_DIR}/${STACK_BOOL_SRC} ${STACK_INCLUDES}/Stack.hh --format-style=file -- -I${STACK_INCLUDES}
        -I/usr/local/Cellar/arm-none-eabi-gcc/10.3-2021.07/gcc/arm-none-eabi/include/c++/10.3.1
        -I/usr/local/Cellar/arm-none-eabi-gcc/10.3-2021.07/gcc/arm-none-eabi/include/c++/10.3.1/arm-none-eabi
        -I/usr/local/Cellar/arm-none-eabi-gcc/10.3-2021.07/gcc/arm-none-eabi/include/
        )

        message(STATUS "clang-tidy target ON")

        else()
        message(STATUS "clang-tidy target OFF")

    endif()
else()
    if (ENABLE_TIDY)
        set(CMAKE_CXX_CLANG_TIDY
            clang-tidy;
            --header-filter=.*;
            --format-style=file;
            )
            message(STATUS "clang-tidy ON")

    else()
            message(STATUS "clang-tidy OFF")

    endif()
endif()


file(GLOB_RECURSE ALL_SOURCE_FILES *.cc *.hh)
    add_custom_target(
        format
        COMMAND clang-tidy
        -style=file
        -i
        ${ALL_SOURCE_FILES}
    )
    message(STATUS "clang-format target ON")


add_subdirectory(tests)
