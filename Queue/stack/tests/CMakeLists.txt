find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

set(COMMON_FLAGS -Wall -Wextra -Werror)

function(compile_test EXEC SRC)
    target_sources(${EXEC} PRIVATE ./${SRC})
    target_compile_options(${EXEC} PRIVATE ${COMMON_FLAGS})
    add_dependencies(${EXEC} Stack)
    target_link_libraries(${EXEC} Stack GTest::Main)
endfunction()

set(STACK_TEST_EXEC unit-test-stack)
set(STACK_TEST_SRC stack-test.cc)
add_executable(${STACK_TEST_EXEC})

compile_test(${STACK_TEST_EXEC} ${STACK_TEST_SRC})

enable_testing()

add_custom_target(test_stack
		  COMMENT "Running tests"
		  COMMAND ./${STACK_TEST_EXEC})

if(SANITIZERS)
    target_compile_options(${STACK_TEST_EXEC} PUBLIC -fsanitize=address -fsanitize=undefined -g)
    set_target_properties(${STACK_TEST_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address")

endif()
