#include <gtest/gtest.h>

#include "Stack.hh"
#include <array>
#include <numeric>
#include <ctime>

template <typename T>
using Stack = custom_containers::Stack<T>;

template <typename T>
class StackFixture : public ::testing::Test
{
public:
    custom_containers::Stack<T> first_stk;
    custom_containers::Stack<T> second_stk;

    using ValueType = T;

    static constexpr size_t VALUES_SIZE = 100;
    std::array<T, VALUES_SIZE> values = {static_cast<T>(0), static_cast<T>(2), static_cast<T>(5),
                                                static_cast<T>(3), static_cast<T>(0), static_cast<T>(5)};

    static constexpr size_t ACTION_AMOUNT = 1e6;
    std::array<T, ACTION_AMOUNT> stress_test;

};

using TestedTypes = ::testing::Types<bool, uint8_t, uint16_t, uint32_t, uint64_t,
                                     int8_t, int16_t, int32_t, int64_t, float, double>;

TYPED_TEST_SUITE(StackFixture, TestedTypes);

TYPED_TEST(StackFixture, DefaultConstructTest)
{
    EXPECT_EQ(this->first_stk.Size(), 0);
    EXPECT_EQ(this->second_stk.Size(), 0);
}

TYPED_TEST(StackFixture, EqualityTest)
{
    for (const auto& iter : this->values)
    {
        this->first_stk.Push(iter);
        this->second_stk.Push(iter);
    }

    EXPECT_EQ(this->first_stk, this->second_stk);
}

TYPED_TEST(StackFixture, CopyConstructTest)
{
    for (const auto& iter : this->values)
    {
        this->first_stk.Push(iter);
    }

    using TestedType  = typename TestFixture::ValueType;

    custom_containers::Stack<TestedType> to_copy_to{this->first_stk};

    EXPECT_EQ(to_copy_to, this->first_stk);
}

TYPED_TEST(StackFixture, MoveConstructTest)
{
    for (const auto& iter : this->values)
    {
        this->first_stk.Push(iter);
        this->second_stk.Push(iter);
    }

    using TestedType  = typename TestFixture::ValueType;

    custom_containers::Stack<TestedType> to_move_to{std::move(this->first_stk)};

    EXPECT_EQ(to_move_to, this->second_stk);
}




TYPED_TEST(StackFixture, CopyAssignTest)
{
    for (const auto& iter : this->values)
    {
        this->first_stk.Push(iter);
    }

    this->second_stk = this->first_stk;

    EXPECT_EQ(this->second_stk, this->first_stk);
}

TYPED_TEST(StackFixture, MoveAssignTest)
{
    for (const auto& iter : this->values)
    {
        this->first_stk.Push(iter);
        this->second_stk.Push(iter);
    }

    using TestedType  = typename TestFixture::ValueType;

    custom_containers::Stack<TestedType> to_move_to{};

    to_move_to = std::move(this->second_stk);

    EXPECT_EQ(to_move_to, this->first_stk);
}



TYPED_TEST(StackFixture, SizeTest)
{
    for (const auto& iter : this->values)
    {
        this->first_stk.Push(iter);
    }

    size_t stk_size = this->first_stk.Size();
    size_t expected_size = this->values.size();

    EXPECT_EQ(stk_size, expected_size);
    
}

TYPED_TEST(StackFixture, EmptyTest)
{
    EXPECT_EQ(this->first_stk.Empty(), true);
}


TYPED_TEST(StackFixture, PushPopTop)
{
    for (const auto& iter : this->values)
    {
        this->first_stk.Push(iter);
    }

    EXPECT_EQ(this->first_stk.Top(), this->values[this->values.size() - 1]);
    EXPECT_EQ(this->first_stk.Size(), this->values.size());

    this->first_stk.Pop();
    this->first_stk.Pop();

    EXPECT_EQ(this->first_stk.Top(), this->values[this->values.size() - 3]);
    EXPECT_EQ(this->first_stk.Size(), this->values.size() - 2);
}


TYPED_TEST(StackFixture, StressTest)
{
    for (const auto& iter : this->stress_test)
    {
        this->first_stk.Push(iter);
        this->first_stk.Pop();
    }
}