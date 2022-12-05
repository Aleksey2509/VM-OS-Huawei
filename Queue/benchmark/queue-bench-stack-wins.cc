#include <benchmark/benchmark.h>
#include "queue.hh"
#include <vector>

constexpr size_t RANGE_MULTIPLIER = 2;
constexpr size_t RANGE_START = 1 << 17;
constexpr size_t RANGE_FINISH = 1 << 20;

template <class QueueType> 
static void QueuePushing(benchmark::State& state)
{
    for (auto _ : state) // NOLINT
    {
        QueueType queue;
        for (size_t i = 0; i < state.range(); i++)
        {
            queue.Push(i);
            auto&& front = queue.Front();
            front = i + 1;
            auto&& back = queue.Back();
            back = i - 1;
        }

        for (size_t i = 0; i < state.range() - 1; i++)
        {
            queue.Pop();
            auto&& front = queue.Front();
            front = i + 1;
            auto&& back = queue.Back();
            back = i - 1;
        }

        queue.Pop();
    }
}

BENCHMARK(QueuePushing<custom_containers::QueueList<double>>)
    ->RangeMultiplier(RANGE_MULTIPLIER)->Range(RANGE_START, RANGE_FINISH)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(QueuePushing<custom_containers::QueueStack<double>>)
    ->RangeMultiplier(RANGE_MULTIPLIER)->Range(RANGE_START, RANGE_FINISH)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();