find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

set(COMMON_FLAGS -Wall -Wextra -Werror)

function(compile_test EXEC SRC)
    target_sources(${EXEC} PRIVATE ./${SRC})
    target_compile_options(${EXEC} PRIVATE ${COMMON_FLAGS})
    add_dependencies(${EXEC} Queue List Stack)
    target_link_libraries(${EXEC} Queue List Stack GTest::Main)
endfunction()

set(QUEUE_TEST_EXEC unit-test-queue)
set(QUEUE_TEST_SRC queue-test.cc)
add_executable(${QUEUE_TEST_EXEC})

compile_test(${QUEUE_TEST_EXEC} ${QUEUE_TEST_SRC})

enable_testing()

add_custom_target(test_queue
COMMENT "Running tests"
COMMAND ./${QUEUE_TEST_EXEC})

if(SANITIZERS)
    message("-- Build with sanitizers")
    target_compile_options(${QUEUE_TEST_EXEC} PUBLIC -fsanitize=address -fsanitize=undefined -g)
    set_target_properties(${QUEUE_TEST_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()