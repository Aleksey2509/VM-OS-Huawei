#include <gtest/gtest.h>

#include "corrector.hh"
#include <algorithm>

TEST(LevDistanceTest, ZeroDistanceTest)
{
    size_t expected_distance = 0;

    EXPECT_EQ(corrector::lev_distance("correct", "correct"), expected_distance);
    EXPECT_EQ(corrector::lev_distance("cat", "cat"), expected_distance);
    EXPECT_EQ(corrector::lev_distance("snore", "snore"), expected_distance);
}

TEST(LevDistanceTest, SingleDistanceTest)
{
    size_t expected_distance = 1;

    EXPECT_EQ(corrector::lev_distance("corrct", "correct"), expected_distance);
    EXPECT_EQ(corrector::lev_distance("correct", "corrct"), expected_distance);

    EXPECT_EQ(corrector::lev_distance("carrect", "correct"), expected_distance);
    EXPECT_EQ(corrector::lev_distance("correct", "carrect"), expected_distance);
}

TEST(LevDistanceTest, DoubleDistanceTest)
{
    size_t expected_distance = 2;

    EXPECT_EQ(corrector::lev_distance("corrcet", "correct"), expected_distance);
    EXPECT_EQ(corrector::lev_distance("correct", "corrcet"), expected_distance);

    EXPECT_EQ(corrector::lev_distance("book", "back"), expected_distance);
    EXPECT_EQ(corrector::lev_distance("back", "book"), expected_distance);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}