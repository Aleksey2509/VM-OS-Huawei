
set(STACK_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(STACK_BOOL_SRC stack-bool.cc)
set(STACK_BOOL_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

add_library(Stack STATIC ${STACK_BOOL_SRC_DIR}/${STACK_BOOL_SRC})

target_include_directories(Stack PUBLIC ${STACK_INCLUDES})
