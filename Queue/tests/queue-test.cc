#include <gtest/gtest.h>

#include "queue.hh"

template <typename T>
class QueueFixture : public ::testing::Test
{
public:
    custom_containers::Queue<T> queue;
    custom_containers::Queue<T> queue2;

    using ValueType = T;

    constexpr static size_t VALUES_SIZE = 6;

    std::array<T, VALUES_SIZE> values = {static_cast<T>(0), static_cast<T>(2), static_cast<T>(5),
                                                static_cast<T>(3), static_cast<T>(0), static_cast<T>(5)};

    static constexpr size_t STRESS_TEST_ACTION_AMOUNT = 1e6;

};


using TestedTypes = ::testing::Types<bool, uint8_t,  uint16_t, uint32_t, uint64_t,
                                     int8_t, int16_t, int32_t, int64_t, float, double>;


TYPED_TEST_SUITE(QueueFixture, TestedTypes);

TYPED_TEST(QueueFixture, QueueDefaultCtor)
{
    ASSERT_EQ(this->queue.size(), 0);
    ASSERT_EQ(this->queue.empty(), true);
}


TYPED_TEST(QueueFixture, QueueMoveCtor)
{
    this->queue.push(this->values[0]);
    this->queue.push(this->values[1]);

    this->queue2.push(this->values[0]);
    this->queue2.push(this->values[1]);

    custom_containers::Queue<typename TestFixture::ValueType> test_subj = std::move(this->queue);

    EXPECT_EQ(this->queue2 == test_subj, true);
}
