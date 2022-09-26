find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

set(STACK_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test.cc)
set(STACK_TEST_EXECUTABLE stackTests)
add_executable(${STACK_TEST_EXECUTABLE} ${STACK_TEST_SRC})

target_link_libraries(${STACK_TEST_EXECUTABLE} Stack GTest::Main)

add_custom_target(test_stack
		  COMMENT "Running tests"
		  COMMAND ./${STACK_TEST_EXECUTABLE})

add_dependencies(${STACK_TEST_EXECUTABLE} Stack)
