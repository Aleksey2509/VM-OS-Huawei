#include <gtest/gtest.h>

#include "list.hh"


template <typename T>
class ListFixture : public ::testing::Test
{
public:
    custom_containers::List<T> lst;

    using ValueType = T;

    constexpr static size_t VALUES_SIZE = 6;

    std::array<T, VALUES_SIZE> values = {static_cast<T>(0), static_cast<T>(2), static_cast<T>(5),
                                                static_cast<T>(3), static_cast<T>(0), static_cast<T>(5)};

    static constexpr size_t STRESS_TEST_ACTION_AMOUNT = 1e6;

};


using TestedTypes = ::testing::Types<bool, uint8_t,  uint16_t, uint32_t, uint64_t,
                                     int8_t, int16_t, int32_t, int64_t, float, double>;


TYPED_TEST_SUITE(ListFixture, TestedTypes);

TYPED_TEST(ListFixture, ListDefaultCtor)
{
    EXPECT_EQ(this->lst.size(), 0);
}


TYPED_TEST(ListFixture, ListPushBack)
{
    this->lst.push_back(this->values[0]);
    EXPECT_EQ(this->lst.size(), 1);
    EXPECT_EQ(this->lst.front(), this->values[0]);
    EXPECT_EQ(this->lst.back(), this->values[0]);

    this->lst.pop_front();
    EXPECT_EQ(this->lst.size(), 0);

    this->lst.push_back(this->values[0]);
    this->lst.pop_front();
    EXPECT_EQ(this->lst.size(), 0);
}
