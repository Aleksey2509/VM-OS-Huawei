#include <benchmark/benchmark.h>
#include "queue.hh"
#include <vector>

constexpr size_t RangeMultiplier = 2;
constexpr size_t RangeStart = 1 << 15;
constexpr size_t RangeFinish = 1 << 20;

constexpr size_t HeavyRangeStart = 1 << 12;
constexpr size_t HeavyRangeFinish = 1 << 15;

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

template <class PairContType> 
static void QueueHeavyPushing(benchmark::State& state)
{
    using TestType = typename PairContType::Type;
    using ContType = typename PairContType::Cont;

    size_t push_vec_size = 1e3;
    size_t assign_vec_size = 1e3;

    std::vector<double> to_push(push_vec_size);
    std::vector<double> to_assign(assign_vec_size);

    for (auto _ : state)
    {
        custom_containers::Queue<TestType, ContType> queue;
        for (size_t i = 0; i < state.range(); i++)
        {
            queue.push(to_push);
            auto&& front = queue.front();
            front = to_assign;
            auto&& back = queue.back();
            back = to_assign;
        }

        for (size_t i = 0; i < state.range() - 1; i++)
        {
            queue.pop();
            auto&& front = queue.front();
            front = to_assign;
            auto&& back = queue.back();
            back = to_assign;
        }

        queue.pop();
    }
}

BENCHMARK(QueuePushing<PairListType<double>>)
    ->RangeMultiplier(RangeMultiplier)->Range(RangeStart, RangeFinish)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(QueuePushing<PairStackType<double>>)
    ->RangeMultiplier(RangeMultiplier)->Range(RangeStart, RangeFinish)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(QueueHeavyPushing<PairListType<std::vector<double>>>)
    ->RangeMultiplier(RangeMultiplier)->Range(HeavyRangeStart, HeavyRangeFinish)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(QueueHeavyPushing<PairStackType<std::vector<double>>>)
    ->RangeMultiplier(RangeMultiplier)->Range(HeavyRangeStart, HeavyRangeFinish)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();