find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

set(COMMON_FLAGS -Wall -Wextra -Werror)

function(compile_test EXEC SRC)
    target_sources(${EXEC} PRIVATE ./${SRC})
    target_compile_options(${EXEC} PRIVATE ${COMMON_FLAGS})
    add_dependencies(${EXEC} TextHandler)
    target_link_libraries(${EXEC} TextHandler GTest::Main)
    set (TEST_TEXT ${CMAKE_CURRENT_SOURCE_DIR}/test_text)
    set (TEST_TEXT2 ${CMAKE_CURRENT_SOURCE_DIR}/test_text2)
    add_compile_definitions(TEST_FILE="${TEST_TEXT}")
    add_compile_definitions(TEST_FILE2="${TEST_TEXT2}")
endfunction()

set(TEXTHANDLER_TEST_EXEC unit-test-texthandler)
set(TEXTHANDLER_TEST_SRC texthandlers-test.cc)
add_executable(${TEXTHANDLER_TEST_EXEC})

enable_testing()

compile_test(${TEXTHANDLER_TEST_EXEC} ${TEXTHANDLER_TEST_SRC})

add_custom_target(test_texthandlers
COMMENT "Running tests"
COMMAND ./${TEXTHANDLER_TEST_EXEC})

if(SANITIZERS)
    target_compile_options(${TEXTHANDLER_TEST_EXEC} PUBLIC -fsanitize=address -fsanitize=undefined -g)
    set_target_properties(${TEXTHANDLER_TEST_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif()
