find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

set(COMMON_FLAGS -Wall -Wextra -Werror)

function(compile_test EXEC SRC)
    target_sources(${EXEC} PRIVATE ./${SRC})
    target_compile_options(${EXEC} PRIVATE ${COMMON_FLAGS})
    add_dependencies(${EXEC} Corrector)
    target_link_libraries(${EXEC} Corrector GTest::Main)
endfunction()

set(LEV_DISTANCE_TEST_EXEC unit-test-lev-distance)
set(LEV_DISTANCE_TEST_SRC lev-distance-test.cc)
add_executable(${LEV_DISTANCE_TEST_EXEC})

enable_testing()

compile_test(${LEV_DISTANCE_TEST_EXEC} ${LEV_DISTANCE_TEST_SRC})

add_custom_target(test_lev_distance
COMMENT "Running tests"
COMMAND ./${LEV_DISTANCE_TEST_EXEC})

if(SANITIZERS)
    target_compile_options(${LEV_DISTANCE_TEST_EXEC} PUBLIC -fsanitize=address -fsanitize=undefined -g)
    set_target_properties(${LEV_DISTANCE_TEST_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif()
