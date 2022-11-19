#include <benchmark/benchmark.h>
#include "queue.hh"
#include <vector>
#include <algorithm>
#include <limits>

constexpr size_t RangeMultiplier = 2;
constexpr size_t RangeStart = 1 << 15;
constexpr size_t RangeFinish = 1 << 20;

template <typename T>
struct PairListType
{
    using Type = T;
    using Cont = custom_containers::List<T>;
};

template <typename T>
struct PairStackType
{
    using Type = T;
    using Cont = custom_containers::Stack<T>;
};


template <class PairContType> 
static void QueuePushing(benchmark::State& state)
{
    using TestType = typename PairContType::Type;
    using ContType = typename PairContType::Cont;

    for (auto _ : state)
    {
        custom_containers::Queue<TestType, ContType> queue;
        for (size_t i = 0; i < state.range(); i++)
        {
            queue.push(i);
            auto&& front = queue.front();
            front = i + 1;
            auto&& back = queue.back();
            back = i - 1;
        }
    }
}

BENCHMARK(QueuePushing<PairListType<double>>)
    ->RangeMultiplier(RangeMultiplier)->Range(RangeStart, RangeFinish)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(QueuePushing<PairStackType<double>>)
    ->RangeMultiplier(RangeMultiplier)->Range(RangeStart, RangeFinish)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();