find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

set(COMMON_FLAGS -Wall -Wextra -Werror)

function(compile_test EXEC SRC)
    target_sources(${EXEC} PRIVATE ./${SRC})
    target_compile_options(${EXEC} PRIVATE ${COMMON_FLAGS})
    add_dependencies(${EXEC} Hashmap)
    target_link_libraries(${EXEC} Hashmap GTest::Main)
endfunction()

set(HASHMAP_TEST_EXEC unit-test-Hashmap)
set(HASHMAP_TEST_SRC hashmap-test.cc)
add_executable(${HASHMAP_TEST_EXEC})

enable_testing()

compile_test(${HASHMAP_TEST_EXEC} ${HASHMAP_TEST_SRC})

add_custom_target(test_hashmap
COMMENT "Running tests"
COMMAND ./${HASHMAP_TEST_EXEC})

if(SANITIZERS)
    target_compile_options(${HASHMAP_TEST_EXEC} PUBLIC -fsanitize=address -fsanitize=undefined -g)
    set_target_properties(${HASHMAP_TEST_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif()
