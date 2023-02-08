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

    custom_containers::HashTable<Key, T> table1;
    custom_containers::HashTable<Key, T> table2;


    constexpr static size_t VALUES_SIZE = 6;

    std::array<T, VALUES_SIZE> values = {static_cast<T>(0), static_cast<T>(2), static_cast<T>(6),
                                                static_cast<T>(3), static_cast<T>(9), static_cast<T>(7)};

};


// using TestedTypes = ::testing::Types<PairIntType<uint32_t>>;
using TestedTypes = ::testing::Types<PairIntType<uint8_t>, PairIntType <uint16_t>, PairIntType<uint32_t>,
                                     PairIntType<float>, PairIntType<double>>;


TYPED_TEST_SUITE(HashTableFixture, TestedTypes);

TYPED_TEST(HashTableFixture, HashTableDefaultCtor)
{
    ASSERT_EQ(this->table1.Size(), 0);
    ASSERT_EQ(this->table1.Empty(), true);
}


TYPED_TEST(HashTableFixture, HashTablePrimitiveInsertion)
{
    // std::cout << "before:" << std::endl;
    // for (auto&& iter : this->table1.node_list_)
    // {
    //     std::cout << iter.key << " " << iter.elem << " ";
    // }
    // std::cout << std::endl;

    for (size_t i = 0; i < this->values.size(); ++i)
    {
        this->table1.insert(this->values[i], this->values[this->values.size() - i - 1]);
    }

    // for (auto&& iter : this->table1.node_list_)
    // {
    //     std::cout << "{" << iter.key << ", " << iter.elem << "} ";
    // }
    // std::cout << "ended printing" << std::endl;

    for (size_t i = 0; i < this->values.size(); ++i)
    {
        EXPECT_EQ(this->table1[this->values[i]], this->values[this->values.size() - i - 1]);
    }
}