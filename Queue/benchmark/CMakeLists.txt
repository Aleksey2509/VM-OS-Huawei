function(compile_bench EXEC SRC)
    target_sources(${EXEC} PRIVATE ./${SRC})
    add_dependencies(${EXEC} Queue List Stack)
    target_link_libraries(${EXEC} Queue List Stack benchmark::benchmark)
endfunction()

set(QUEUE_BENCH_LIST_WINS_EXEC bench-for-list)
set(QUEUE_BENCH_LIST_WINS_SRC queue-bench-list-wins.cc)
set(QUEUE_BENCH_STACK_WINS_EXEC bench-for-stack)
set(QUEUE_BENCH_STACK_WINS_SRC queue-bench-stack-wins.cc)
add_executable(${QUEUE_BENCH_STACK_WINS_EXEC})
add_executable(${QUEUE_BENCH_LIST_WINS_EXEC})

compile_bench(${QUEUE_BENCH_STACK_WINS_EXEC} ${QUEUE_BENCH_STACK_WINS_SRC})
compile_bench(${QUEUE_BENCH_LIST_WINS_EXEC} ${QUEUE_BENCH_LIST_WINS_SRC})

add_custom_target(bench_queue_for_stack
COMMENT "Running benchmark, where stack queue is better"
COMMAND ./${QUEUE_BENCH_STACK_WINS_EXEC})

add_custom_target(bench_queue_for_list
COMMENT "Running benchmark, where list queue is better"
COMMAND ./${QUEUE_BENCH_LIST_WINS_EXEC})

if(SANITIZERS)
    target_compile_options(${QUEUE_BENCH_STACK_WINS_EXEC} PUBLIC -fsanitize=address -fsanitize=undefined -g)
    set_target_properties(${QUEUE_BENCH_STACK_WINS_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address")
    target_compile_options(${QUEUE_BENCH_LIST_WINS_EXEC} PUBLIC -fsanitize=address -fsanitize=undefined -g)
    set_target_properties(${QUEUE_BENCH_LIST_WINS_EXEC} PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()