find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

set(COMMON_FLAGS -Wall -Wextra)

set(STACK_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test.cc)
set(STACK_TEST_EXEC stackTests)
add_executable(${STACK_TEST_EXEC} ${STACK_TEST_SRC})

target_link_libraries(${STACK_TEST_EXEC} Stack GTest::Main)
target_compile_options(${STACK_TEST_EXEC} PRIVATE ${COMMON_FLAGS})

add_custom_target(test_stack
		  COMMENT "Running tests"
		  COMMAND ./${STACK_TEST_EXEC})

add_dependencies(${STACK_TEST_EXEC} Stack)

if(SANITIZERS)
    message("-- Build with sanitizers")
    target_compile_options(${STACK_TEST_EXEC} PUBLIC -fsanitize=address -g)
    set_target_properties(${STACK_TEST_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()