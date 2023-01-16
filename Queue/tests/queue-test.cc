#include <gtest/gtest.h>

#include "queue.hh"
#include <type_traits>
#include <vector>
#include <numeric>

template <typename T>
struct PairQueueListType
{
    using Type = T;
    using Cont = custom_containers::QueueList<T>;
};

template <typename T>
struct PairQueueStackType
{
    using Type = T;
    using Cont = custom_containers::QueueStack<T>;
};

template <typename T>
class QueueFixture : public ::testing::Test
{
public:
    using ValueType = typename T::Type;
    using QueueType = typename T::Cont;

    QueueType queue;
    QueueType queue2;

    constexpr static size_t VALUES_SIZE = 6;

    std::array<ValueType, VALUES_SIZE> values = {static_cast<ValueType>(0), static_cast<ValueType>(2), static_cast<ValueType>(5),
                                                static_cast<ValueType>(3), static_cast<ValueType>(0), static_cast<ValueType>(5)};

};


using TestedTypes = ::testing::Types<PairQueueListType<bool>,    PairQueueListType<uint8_t>, PairQueueListType<uint16_t>, PairQueueListType<uint32_t>,
                                     PairQueueListType<uint64_t>,PairQueueListType<int8_t>,  PairQueueListType<int16_t>, PairQueueListType<int32_t>,
                                     PairQueueListType<int64_t>, PairQueueListType<float>,   PairQueueListType<double>, PairQueueListType<std::vector<double>>,
                                     PairQueueStackType<bool>,   PairQueueStackType<uint8_t>, PairQueueStackType<uint16_t>, PairQueueStackType<uint32_t>,
                                     PairQueueStackType<uint64_t>,PairQueueStackType<int8_t>, PairQueueStackType<int16_t>, PairQueueStackType<int32_t>,
                                     PairQueueStackType<int64_t>, PairQueueStackType<float>,  PairQueueStackType<double>, PairQueueStackType<std::vector<double>>>;

TYPED_TEST_SUITE(QueueFixture, TestedTypes);

TYPED_TEST(QueueFixture, QueueDefaultCtor)
{
    ASSERT_EQ(this->queue.Size(), 0);
    ASSERT_EQ(this->queue.Empty(), true);
}

TYPED_TEST(QueueFixture, QueuePushBackPopFront)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.Push(this->values[i]);
        EXPECT_EQ(this->queue.Size(), i + 1);
        EXPECT_EQ(this->queue.Back(), this->values[i]);
        EXPECT_EQ(this->queue.Front(), this->values[0]);
    }
    

    for (size_t i = 0; i < this->values.size() - 1; ++i)
    {
        this->queue.Pop();
        EXPECT_EQ(this->queue.Size(), this->values.size() - i - 1);
        EXPECT_EQ(this->queue.Back(), this->values[this->values.size() - 1]);
        EXPECT_EQ(this->queue.Front(), this->values[i + 1]);
    }

    this->queue.Pop();
    EXPECT_EQ(this->queue.Size(), 0);
}

TYPED_TEST(QueueFixture, equalityOperator)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.Push(this->values[i]);
        this->queue2.Push(this->values[i]);
    }

    EXPECT_EQ(this->queue == this->queue2, true);

    this->queue.Pop();

    EXPECT_EQ(this->queue != this->queue2, true);

}

TYPED_TEST(QueueFixture, copyCtor)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.Push(this->values[i]);
    }

    const typename TestFixture::QueueType to_copy_to{this->queue};

    EXPECT_EQ(this->queue == to_copy_to, true);

    this->queue.Pop();

    EXPECT_EQ(this->queue != to_copy_to, true);
}

TYPED_TEST(QueueFixture, copyAssignOperator)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.Push(this->values[i]);
    }

    this->queue2 = this->queue;

    EXPECT_EQ(this->queue == this->queue2, true);

    this->queue.Pop();

    EXPECT_EQ(this->queue != this->queue2, true);
}

TYPED_TEST(QueueFixture, Front)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.Push(this->values[i]);
        this->queue2.Push(this->values[i]);
    }

    ASSERT_EQ(this->queue == this->queue2, true);

    auto&& front = this->queue.Front();
    auto&& front2 = this->queue2.Front();
    front = this->values.back();
    front2 = this->values.front();

    if(std::is_same<bool, typename TestFixture::ValueType>::value)
    {
        EXPECT_EQ(this->queue == this->queue2, true);
    }
    else
    {
        EXPECT_EQ(this->queue == this->queue2, false);
    }
}

TYPED_TEST(QueueFixture, Back)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.Push(this->values[i]);
        this->queue2.Push(this->values[i]);
    }

    ASSERT_EQ(this->queue == this->queue2, true);

    auto&& back = this->queue.Back();
    auto&& back2 = this->queue2.Back();
    back = this->values.front();
    back2 = this->values.back();

    if(std::is_same<bool, typename TestFixture::ValueType>::value)
    {
        EXPECT_EQ(this->queue == this->queue2, true);
    }
    else
    {
        EXPECT_EQ(this->queue == this->queue2, false);
    }
}

TYPED_TEST(QueueFixture, moveCtor)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.Push(this->values[i]);
        this->queue2.Push(this->values[i]);
    }

    const typename TestFixture::QueueType to_move_to{std::move(this->queue)};

    EXPECT_EQ(this->queue2 == to_move_to, true);

    this->queue2.Pop();


    EXPECT_EQ(this->queue2 != to_move_to, true);
}

TYPED_TEST(QueueFixture, moveAssignOperator)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.Push(this->values[i]);
    }

    typename TestFixture::QueueType to_move{this->queue};

    this->queue2 = std::move(to_move);

    EXPECT_EQ(this->queue == this->queue2, true);

    this->queue.Pop();

    EXPECT_EQ(this->queue != this->queue2, true);
}


TYPED_TEST(QueueFixture, hugeTest)
{
    size_t vec_size = 1e4;

    using VectorType = typename TestFixture::ValueType;
    std::vector<VectorType> to_push;
    for (size_t i = 0; i < vec_size; i++)
    {
        to_push.push_back(static_cast<VectorType>(i));
    }

    for (auto&& iter : to_push)
    {
        this->queue.Push(iter);
    }

    for (auto&& iter = to_push.begin(); iter != to_push.end(); iter++)
    {
        ASSERT_EQ(*iter == this->queue.Front(), true);
        this->queue.Pop();
    }

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
