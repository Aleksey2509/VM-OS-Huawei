find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

set(COMMON_FLAGS -Wall -Wextra -Werror)

function(compile_test EXEC SRC)
    target_sources(${EXEC} PRIVATE ./${SRC})
    target_compile_options(${EXEC} PRIVATE ${COMMON_FLAGS})
    add_dependencies(${EXEC} HashTable)
    target_link_libraries(${EXEC} HashTable GTest::Main)
endfunction()

set(HASHTABLE_TEST_EXEC unit-test-hashtable)
set(HASHTABLE_TEST_SRC hashtable-test.cc)
add_executable(${HASHTABLE_TEST_EXEC})

enable_testing()

compile_test(${HASHTABLE_TEST_EXEC} ${HASHTABLE_TEST_SRC})

add_custom_target(test_hashtable
COMMENT "Running tests"
COMMAND ./${HASHTABLE_TEST_EXEC})

if(SANITIZERS)
    target_compile_options(${HASHTABLE_TEST_EXEC} PUBLIC -fsanitize=address -fsanitize=undefined -g)
    set_target_properties(${HASHTABLE_TEST_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif()
