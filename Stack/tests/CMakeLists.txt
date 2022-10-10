find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

set(COMMON_FLAGS -Wall -Wextra)

set(STACK_TEST_EXEC unit_test_stack)
set(STACK_SPEED_TEST_EXEC speed_test_stack)

add_executable(${STACK_TEST_EXEC})
add_executable(${STACK_SPEED_TEST_EXEC})

set(STACK_TESTING 
    ${STACK_TEST_EXEC} 
    ${STACK_SPEED_TEST_EXEC})

set(STACK_TESTING_SRC 
    test.cc
    speed-test.cc)

foreach(EXEC SRC IN ZIP_LISTS STACK_TESTING STACK_TESTING_SRC)
    target_sources(${EXEC} PRIVATE ./${SRC})
    target_compile_options(${EXEC} PRIVATE ${COMMON_FLAGS})
    add_dependencies(${EXEC} Stack)
    target_link_libraries(${EXEC} Stack)
endforeach()

target_link_libraries(${STACK_TEST_EXEC} GTest::Main)

add_custom_target(test_stack
		  COMMENT "Running tests"
		  COMMAND ./${STACK_TEST_EXEC})

add_custom_target(speed_test
		  COMMENT "Running test on speed of execution"
		  COMMAND ./${STACK_SPEED_TEST_EXEC})

if(SANITIZERS)
    message("-- Build with sanitizers")
    foreach(FILE IN LISTS STACK_TESTING)
        target_compile_options(${FILE} PUBLIC -fsanitize=address -g)
        set_target_properties(${FILE} PROPERTIES LINK_FLAGS "-fsanitize=address")
    endforeach()

endif()