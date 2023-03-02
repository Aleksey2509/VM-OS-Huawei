#include <gtest/gtest.h>

#include "hashtable.hh"
#include <string>
#include <algorithm>
#include <iostream>

template <typename T>
struct PairIntType
{
    using KeyType = int;
    using ValueType = T;
};

template <typename T>
struct StringIntType
{
    using KeyType = std::string;
    using ValueType = T;
};

template <typename TypePair>
class HashTableFixture : public ::testing::Test
{
public:
    using Key = typename TypePair::KeyType;
    using T   = typename TypePair::ValueType;

    custom_containers::HashTable<Key, T> table1{};
    custom_containers::HashTable<Key, T> table2{};


    constexpr static size_t VALUES_SIZE = 6;

    std::array<T, VALUES_SIZE> values = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(6),
                                                static_cast<T>(3), static_cast<T>(9), static_cast<T>(7)};

};


using TestedTypes = ::testing::Types<PairIntType <int16_t>, PairIntType<int32_t>,
                                     PairIntType<float>, PairIntType<double>>;


TYPED_TEST_SUITE(HashTableFixture, TestedTypes);

TYPED_TEST(HashTableFixture, HashTableDefaultCtor)
{
    ASSERT_EQ(this->table1.Size(), 0);
    ASSERT_EQ(this->table1.Empty(), true);
}


TYPED_TEST(HashTableFixture, PrimitiveInsertion)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->table1.insert(this->values[i], this->values[this->values.size() - i - 1]);
    }

    for (size_t i = 0; i < this->values.size(); ++i)
    {
        EXPECT_EQ(this->table1[this->values[i]], this->values[this->values.size() - i - 1]);
    }
}

TYPED_TEST(HashTableFixture, EqualityOperator)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->table1.insert(this->values[i], this->values[this->values.size() - i - 1]);
        this->table2.insert(this->values[i], this->values[this->values.size() - i - 1]);
    }

    EXPECT_EQ(this->table1, this->table2);

    this->table2[this->values[0]] = 15;

    EXPECT_EQ(this->table1 == this->table2, false);

}

TYPED_TEST(HashTableFixture, CopyCtor)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->table1.insert(this->values[i], this->values[this->values.size() - i - 1]);
    }

    custom_containers::HashTable<typename TestFixture::Key, typename TestFixture::T> to_copy_to{this->table1};

    EXPECT_EQ(this->table1 == to_copy_to, true);

    auto&& tmp = to_copy_to[this->values[0]];
    tmp = 5;

    EXPECT_EQ(to_copy_to[this->values[0]], 5);
    EXPECT_EQ(this->table1[this->values[0]] == 5, false);

    EXPECT_EQ(this->table1 == to_copy_to, false);
}

TYPED_TEST(HashTableFixture, MoveCtor)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->table1.insert(this->values[i], this->values[this->values.size() - i - 1]);
        this->table2.insert(this->values[i], this->values[this->values.size() - i - 1]);
    }

    custom_containers::HashTable<typename TestFixture::Key, typename TestFixture::T> to_move_to{std::move(this->table1)};

    EXPECT_EQ(this->table2 == to_move_to, true);

    auto&& tmp = to_move_to[this->values[0]];
    tmp = 5;

    EXPECT_EQ(to_move_to[this->values[0]], 5);

    EXPECT_EQ(this->table2 == to_move_to, false);
}

TYPED_TEST(HashTableFixture, CopyAssign)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->table1.insert(this->values[i], this->values[this->values.size() - i - 1]);
    }

    this->table2 = this->table1;

    EXPECT_EQ(this->table1 == this->table2, true);

    auto&& tmp = this->table2[this->values[0]];
    tmp = 5;

    EXPECT_EQ(this->table2[this->values[0]], 5);
    EXPECT_EQ(this->table1[this->values[0]] == 5, false);

    // this->table1.Clear();

    EXPECT_EQ(this->table1 == this->table2, false);
}

TYPED_TEST(HashTableFixture, MoveAssign)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->table1.insert(this->values[i], this->values[this->values.size() - i - 1]);
        this->table2.insert(this->values[i], this->values[this->values.size() - i - 1]);
    }

    custom_containers::HashTable<typename TestFixture::Key, typename TestFixture::T> to_move_to{};
    to_move_to = std::move(this->table1);

    EXPECT_EQ(this->table2 == to_move_to, true);

    auto&& tmp = to_move_to[this->values[0]];
    tmp = 5;

    EXPECT_EQ(to_move_to[this->values[0]], 5);

    EXPECT_EQ(this->table2 == to_move_to, false);
}

TYPED_TEST(HashTableFixture, Find)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->table1.insert(this->values[i], this->values[this->values.size() - i - 1]);
    }

    auto&& iter1 = this->table1.find(this->values[0]);
    EXPECT_EQ(iter1->second, this->values[this->values.size() - 1]);

    auto&& iter2 = this->table1.find(111);
    EXPECT_EQ(iter2 == this->table1.end(), true);
}

TYPED_TEST(HashTableFixture, Contains)
{
    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->table1.insert(this->values[i], this->values[this->values.size() - i - 1]);
    }

    auto&& contains1 = this->table1.contains(this->values[0]);
    EXPECT_EQ(contains1, true);

    auto&& contains2 = this->table1.contains(111);
    EXPECT_EQ(contains2, false);
}