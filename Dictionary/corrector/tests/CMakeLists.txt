find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

set(COMMON_FLAGS -Wall -Wextra -Werror)

function(compile_test EXEC SRC)
    target_sources(${EXEC} PRIVATE ./${SRC})
    target_compile_options(${EXEC} PRIVATE ${COMMON_FLAGS})
    add_dependencies(${EXEC} Corrector)
    target_link_libraries(${EXEC} Corrector TextHandler GTest::Main)
endfunction()

set(LEV_DISTANCE_TEST_EXEC unit-test-lev-distance)
set(LEV_DISTANCE_TEST_SRC lev-distance-test.cc)
add_executable(${LEV_DISTANCE_TEST_EXEC})

set(CORRECTOR_TEST_EXEC unit-test-corrector)
set(CORRECTOR_TEST_SRC corrector-test.cc)
add_executable(${CORRECTOR_TEST_EXEC})

set (TEST_LEARN ${CMAKE_CURRENT_SOURCE_DIR}/test_learn)
add_compile_definitions(TEST_LEARN_FILE="${TEST_LEARN}")

set (TEST_WRONG ${CMAKE_CURRENT_SOURCE_DIR}/test_wrong)
add_compile_definitions(TEST_WRONG_FILE="${TEST_WRONG}")

set (TEST_DATA_BASE ${CMAKE_CURRENT_SOURCE_DIR}/test_data_base)
add_compile_definitions(TEST_DATA_BASE_FILE="${TEST_DATA_BASE}")

enable_testing()

compile_test(${LEV_DISTANCE_TEST_EXEC} ${LEV_DISTANCE_TEST_SRC})
compile_test(${CORRECTOR_TEST_EXEC} ${CORRECTOR_TEST_SRC})

add_custom_target(test_lev_distance
COMMENT "Running tests"
COMMAND ./${LEV_DISTANCE_TEST_EXEC})

add_custom_target(test_corrector
COMMENT "Running tests"
COMMAND ./${CORRECTOR_TEST_EXEC})

if(SANITIZERS)
    target_compile_options(${LEV_DISTANCE_TEST_EXEC} PUBLIC -fsanitize=address -fsanitize=undefined -g)
    set_target_properties(${LEV_DISTANCE_TEST_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif()


if(SANITIZERS)
    target_compile_options(${CORRECTOR_TEST_EXEC} PUBLIC -fsanitize=address -fsanitize=undefined -g)
    set_target_properties(${CORRECTOR_TEST_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif()

