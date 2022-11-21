find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

set(COMMON_FLAGS -Wall -Wextra -Werror)

function(compile_test EXEC SRC)
    target_sources(${EXEC} PRIVATE ./${SRC})
    target_compile_options(${EXEC} PRIVATE ${COMMON_FLAGS})
    add_dependencies(${EXEC} List)
    target_link_libraries(${EXEC} List GTest::Main)
endfunction()

set(LIST_TEST_EXEC unit-test-list)
set(LIST_TEST_SRC list-test.cc)
add_executable(${LIST_TEST_EXEC})

enable_testing()

compile_test(${LIST_TEST_EXEC} ${LIST_TEST_SRC})

add_custom_target(test_list
COMMENT "Running tests"
COMMAND ./${LIST_TEST_EXEC})

if(SANITIZERS)
    target_compile_options(${LIST_TEST_EXEC} PUBLIC -fsanitize=address -fsanitize=undefined -g)
    set_target_properties(${LIST_TEST_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif()
