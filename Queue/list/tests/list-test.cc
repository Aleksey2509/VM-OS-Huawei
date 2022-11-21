#include <gtest/gtest.h>

#include "list.hh"


template <typename T>
class ListFixture : public ::testing::Test
{
public:
    custom_containers::List<T> lst;
    custom_containers::List<T> lst2;

    using ValueType = T;

    constexpr static size_t VALUES_SIZE = 6;

    std::array<T, VALUES_SIZE> values = {static_cast<T>(0), static_cast<T>(2), static_cast<T>(5),
                                                static_cast<T>(3), static_cast<T>(0), static_cast<T>(5)};

};


using TestedTypes = ::testing::Types<bool, uint8_t,  uint16_t, uint32_t, uint64_t,
                                     int8_t, int16_t, int32_t, int64_t, float, double>;


TYPED_TEST_SUITE(ListFixture, TestedTypes);

TYPED_TEST(ListFixture, ListDefaultCtor)
{
    ASSERT_EQ(this->lst.Size(), 0);
    ASSERT_EQ(this->lst.Empty(), true);
}


TYPED_TEST(ListFixture, ListPushBackPopFront)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->lst.PushBack(this->values[i]);
        EXPECT_EQ(this->lst.Size(), i + 1);
        EXPECT_EQ(this->lst.Back(), this->values[i]);
        EXPECT_EQ(this->lst.Front(), this->values[0]);
    }
    

    for (size_t i = 0; i < this->values.size() - 1; ++i)
    {
        this->lst.PopFront();
        EXPECT_EQ(this->lst.Size(), this->values.size() - i - 1);
        EXPECT_EQ(this->lst.Back(), this->values[this->values.size() - 1]);
        EXPECT_EQ(this->lst.Front(), this->values[i + 1]);
    }

    this->lst.PopFront();
    EXPECT_EQ(this->lst.Size(), 0);
}

TYPED_TEST(ListFixture, ListPushFrontPopBack)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->lst.PushFront(this->values[i]);
        EXPECT_EQ(this->lst.Size(), i + 1);
        EXPECT_EQ(this->lst.Front(), this->values[i]);
        EXPECT_EQ(this->lst.Back(), this->values[0]);
    }
    

    for (size_t i = 0; i < this->values.size() - 1; ++i)
    {
        this->lst.PopBack();
        EXPECT_EQ(this->lst.Size(), this->values.size() - i - 1);
        EXPECT_EQ(this->lst.Back(), this->values[i + 1]);
        EXPECT_EQ(this->lst.Front(), this->values[this->values.size() - 1]);
    }

    this->lst.PopBack();
    EXPECT_EQ(this->lst.Size(), 0);
}

TYPED_TEST(ListFixture, equalityOperator)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->lst.PushFront(this->values[i]);
        this->lst2.PushFront(this->values[i]);
    }

    EXPECT_EQ(this->lst == this->lst2, true);

    this->lst.PopBack();

    EXPECT_EQ(this->lst != this->lst2, true);

}

TYPED_TEST(ListFixture, copyCtor)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->lst.PushFront(this->values[i]);
    }

    const custom_containers::List<typename TestFixture::ValueType> to_copy_to{this->lst};

    EXPECT_EQ(this->lst == to_copy_to, true);

    this->lst.PopBack();

    EXPECT_EQ(this->lst != to_copy_to, true);
}

TYPED_TEST(ListFixture, copyAssignOperator)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->lst.PushFront(this->values[i]);
    }

    this->lst2 = this->lst;

    EXPECT_EQ(this->lst == this->lst2, true);

    this->lst.PopBack();

    EXPECT_EQ(this->lst != this->lst2, true);
}

TYPED_TEST(ListFixture, moveCtor)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->lst.PushFront(this->values[i]);
        this->lst2.PushFront(this->values[i]);
    }

    const custom_containers::List<typename TestFixture::ValueType> to_move_to{std::move(this->lst)};

    EXPECT_EQ(this->lst2 == to_move_to, true);

    this->lst2.PopBack();

    EXPECT_EQ(this->lst2 != to_move_to, true);
}

TYPED_TEST(ListFixture, moveAssignOperator)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->lst.PushFront(this->values[i]);
    }

    const custom_containers::List<typename TestFixture::ValueType> to_move{this->lst};

    this->lst2 = std::move(to_move);

    EXPECT_EQ(this->lst == this->lst2, true);

    this->lst.PopBack();

    EXPECT_EQ(this->lst != this->lst2, true);
}

TYPED_TEST(ListFixture, Front)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->lst.PushFront(this->values[i]);
        this->lst2.PushFront(this->values[i]);
    }

    ASSERT_EQ(this->lst == this->lst2, true);

    auto&& front = this->lst.Front();
    front = this->values.front();

    EXPECT_EQ(this->lst == this->lst2, false);
}

TYPED_TEST(ListFixture, Back)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->lst.PushFront(this->values[i]);
        this->lst2.PushFront(this->values[i]);
    }

    ASSERT_EQ(this->lst == this->lst2, true);

    auto&& back = this->lst.Back();
    back = this->values.back();

    EXPECT_EQ(this->lst == this->lst2, false);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}