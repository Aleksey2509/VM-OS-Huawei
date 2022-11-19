function(compile_bench EXEC SRC)
    target_sources(${EXEC} PRIVATE ./${SRC})
    add_dependencies(${EXEC} Queue List Stack)
    target_link_libraries(${EXEC} Queue List Stack benchmark::benchmark)
endfunction()

set(QUEUE_BENCH_EXEC benchmark-queue)
set(QUEUE_BENCH_SRC queue-bench.cc)
add_executable(${QUEUE_BENCH_EXEC})

compile_bench(${QUEUE_BENCH_EXEC} ${QUEUE_BENCH_SRC})

add_custom_target(bench_queue
COMMENT "Running benchmark"
COMMAND ./${QUEUE_BENCH_EXEC})