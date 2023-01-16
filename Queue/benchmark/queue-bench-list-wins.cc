#include <benchmark/benchmark.h>
#include "queue.hh"
#include <vector>
#include <list>

constexpr size_t RANGE_MULTIPLIER = 2;

constexpr size_t HEAVY_RANGE_START = 1 << 11;
constexpr size_t HEAVY_RANGE_FINISH = 1 << 14;

template <class QueueType> 
static void QueueHeavyPushing(benchmark::State& state)
{
    const size_t push_vec_size = 1e2;
    const size_t assign_vec_size = 1e2;

    const std::list<double> to_push(push_vec_size);
    const std::list<double> to_assign(assign_vec_size);

    for (auto _ : state) // NOLINT
    {
        QueueType queue;
        for (size_t i = 0; i < state.range(); i++)
        {
            queue.Push(to_push);
            auto&& front = queue.Front();
            front = to_assign;
            auto&& back = queue.Back();
            back = to_assign;
        }

        for (size_t i = 0; i < state.range() - 1; i++)
        {
            queue.Pop();
            auto&& front = queue.Front();
            front = to_assign;
            auto&& back = queue.Back();
            back = to_assign;
        }

        queue.Pop();
    }
}

BENCHMARK(QueueHeavyPushing<custom_containers::QueueList<std::list<double>>>)
    ->RangeMultiplier(RANGE_MULTIPLIER)->Range(HEAVY_RANGE_START, HEAVY_RANGE_FINISH)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(QueueHeavyPushing<custom_containers::QueueStack<std::list<double>>>)
    ->RangeMultiplier(RANGE_MULTIPLIER)->Range(HEAVY_RANGE_START, HEAVY_RANGE_FINISH)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();