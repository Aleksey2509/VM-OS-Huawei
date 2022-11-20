#include <benchmark/benchmark.h>
#include "queue.hh"

constexpr size_t RangeMultiplier = 2;
constexpr size_t RangeStart = 1 << 15;
constexpr size_t RangeFinish = 1 << 20;

template <typename T>
struct PairQueueListType
{
    using Type = T;
    using QueueType = custom_containers::QueueList<T>;
};

template <typename T>
struct PairQueueStackType
{
    using Type = T;
    using QueueType = custom_containers::QueueStack<T>;
};


template <class PairContType> 
static void QueuePushing(benchmark::State& state)
{
    using TestType = typename PairContType::Type;
    using QueueType = typename PairContType::QueueType;

    for (auto _ : state)
    {
        QueueType queue;
        for (size_t i = 0; i < state.range(); i++)
        {
            queue.push(i);
            auto&& front = queue.front();
            front = i + 1;
            auto&& back = queue.back();
            back = i - 1;
        }

        for (size_t i = 0; i < state.range() - 1; i++)
        {
            queue.pop();
            auto&& front = queue.front();
            front = i + 1;
            auto&& back = queue.back();
            back = i - 1;
        }

        queue.pop();
    }
}

BENCHMARK(QueuePushing<PairQueueListType<double>>)
    ->RangeMultiplier(RangeMultiplier)->Range(RangeStart, RangeFinish)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(QueuePushing<PairQueueStackType<double>>)
    ->RangeMultiplier(RangeMultiplier)->Range(RangeStart, RangeFinish)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();