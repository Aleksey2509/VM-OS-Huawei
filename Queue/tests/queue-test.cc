#include <gtest/gtest.h>
#include <iostream>


#include "queue.hh"

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

template <typename T>
class QueueFixture : public ::testing::Test
{
public:
    using ValueType = typename T::Type;
    using ContType = typename T::Cont;

    custom_containers::Queue<ValueType, ContType> queue;
    custom_containers::Queue<ValueType, ContType> queue2;

    constexpr static size_t VALUES_SIZE = 6;

    std::array<ValueType, VALUES_SIZE> values = {static_cast<ValueType>(0), static_cast<ValueType>(2), static_cast<ValueType>(5),
                                                static_cast<ValueType>(3), static_cast<ValueType>(0), static_cast<ValueType>(5)};

};


using TestedTypes = ::testing::Types<PairListType<bool>, PairListType<uint8_t>, PairListType<uint16_t>, PairListType<uint32_t>, PairListType<uint64_t>,
                                     PairListType<int8_t>, PairListType<int16_t>, PairListType<int32_t>, PairListType<int64_t>,
                                     PairListType<float>, PairListType<double>,
                                     PairStackType<bool>, PairStackType<uint8_t>, PairStackType<uint16_t>, PairStackType<uint32_t>, PairStackType<uint64_t>,
                                     PairStackType<int8_t>, PairStackType<int16_t>, PairStackType<int32_t>, PairStackType<int64_t>,
                                     PairStackType<float>, PairStackType<double>>;

TYPED_TEST_SUITE(QueueFixture, TestedTypes);

TYPED_TEST(QueueFixture, QueueDefaultCtor)
{
    ASSERT_EQ(this->queue.size(), 0);
    ASSERT_EQ(this->queue.empty(), true);
}

TYPED_TEST(QueueFixture, QueuePushBackPopFront)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.push(this->values[i]);
        EXPECT_EQ(this->queue.size(), i + 1);
        EXPECT_EQ(this->queue.back(), this->values[i]);
        EXPECT_EQ(this->queue.front(), this->values[0]);
    }
    

    for (size_t i = 0; i < this->values.size() - 1; ++i)
    {
        this->queue.pop();
        EXPECT_EQ(this->queue.size(), this->values.size() - i - 1);
        EXPECT_EQ(this->queue.back(), this->values[this->values.size() - 1]);
        EXPECT_EQ(this->queue.front(), this->values[i + 1]);
    }

    this->queue.pop();
    EXPECT_EQ(this->queue.size(), 0);
}

TYPED_TEST(QueueFixture, equalityOperator)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.push(this->values[i]);
        this->queue2.push(this->values[i]);
    }

    EXPECT_EQ(this->queue == this->queue2, true);

    this->queue.pop();

    EXPECT_EQ(this->queue != this->queue2, true);

}

TYPED_TEST(QueueFixture, copyCtor)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.push(this->values[i]);
    }

    custom_containers::Queue<typename TestFixture::ValueType, typename TestFixture::ContType> to_copy_to{this->queue};

    EXPECT_EQ(this->queue == to_copy_to, true);

    this->queue.pop();

    EXPECT_EQ(this->queue != to_copy_to, true);
}

TYPED_TEST(QueueFixture, copyAssignOperator)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.push(this->values[i]);
    }

    this->queue2 = this->queue;

    EXPECT_EQ(this->queue == this->queue2, true);

    this->queue.pop();

    EXPECT_EQ(this->queue != this->queue2, true);
}

TYPED_TEST(QueueFixture, Front)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.push(this->values[i]);
        this->queue2.push(this->values[i]);
    }

    ASSERT_EQ(this->queue == this->queue2, true);

    auto&& front = this->queue.front();
    auto&& front2 = this->queue2.front();
    front = this->values.back();
    front2 = this->values.front();

    if(std::is_same_v<bool, typename TestFixture::ValueType> &&
       !std::is_same_v<custom_containers::List<bool>, typename TestFixture::ContType>)
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
        this->queue.push(this->values[i]);
        this->queue2.push(this->values[i]);
    }

    ASSERT_EQ(this->queue == this->queue2, true);

    auto&& back = this->queue.back();
    auto&& back2 = this->queue2.back();
    back = this->values.front();
    back2 = this->values.back();

    if(std::is_same_v<bool, typename TestFixture::ValueType> &&
       !std::is_same_v<custom_containers::List<bool>, typename TestFixture::ContType>)
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
        this->queue.push(this->values[i]);
        this->queue2.push(this->values[i]);
    }

    custom_containers::Queue<typename TestFixture::ValueType, typename TestFixture::ContType> to_move_to{std::move(this->queue)};

    EXPECT_EQ(this->queue2 == to_move_to, true);

    this->queue2.pop();


    EXPECT_EQ(this->queue2 != to_move_to, true);
}

TYPED_TEST(QueueFixture, moveAssignOperator)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->queue.push(this->values[i]);
    }

    custom_containers::Queue<typename TestFixture::ValueType, typename TestFixture::ContType> to_move{this->queue};

    this->queue2 = std::move(to_move);

    EXPECT_EQ(this->queue == this->queue2, true);

    this->queue.pop();

    EXPECT_EQ(this->queue != this->queue2, true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
