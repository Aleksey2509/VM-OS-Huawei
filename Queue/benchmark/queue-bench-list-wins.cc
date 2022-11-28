#include <benchmark/benchmark.h>
#include "queue.hh"
#include <vector>

constexpr size_t RANGE_MULTIPLIER = 2;

constexpr size_t HEAVY_RANGE_START = 1 << 11;
constexpr size_t HEAVY_RANGE_FINISH = 1 << 14;

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
static void QueueHeavyPushing(benchmark::State& state)
{
    using TestType = typename PairContType::Type;
    using QueueType = typename PairContType::QueueType;

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

BENCHMARK(QueueHeavyPushing<PairQueueListType<std::list<double>>>)
    ->RangeMultiplier(RANGE_MULTIPLIER)->Range(HEAVY_RANGE_START, HEAVY_RANGE_FINISH)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(QueueHeavyPushing<PairQueueStackType<std::list<double>>>)
    ->RangeMultiplier(RANGE_MULTIPLIER)->Range(HEAVY_RANGE_START, HEAVY_RANGE_FINISH)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();