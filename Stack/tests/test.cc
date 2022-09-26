#include <gtest/gtest.h>

#include "Stack.hh"
#include "Stack-impl.hh"

using namespace custom_containers;

TEST(StackInt, ConstructTest)
{
    Stack<int> test(10);
    test.push(15);
    test.push(9);
    test.push(8);

    EXPECT_EQ(test.size(), 3);

}


TEST(StackInt, CopyConstructTest)
{
    Stack<int> test(10);
    test.push(15);
    test.push(9);
    test.push(8);

    Stack<int> test2{test};

    EXPECT_EQ(test == test2, true);

}


TEST(StackBool, TopFuncTest)
{
    Stack<bool> test(8);

    for (int i = 0; i < 7; i++)
        test.push(true);

    EXPECT_EQ(test.top(), true);

    test.push(false);

    EXPECT_EQ(test.top(), false);
    EXPECT_EQ(test.size(), 8);

    test.push(false);
    test.push(false);
    test.push(true);
    test.push(true);
    test.push(false);
    test.push(true);
    test.push(true);
    test.push(true);

    EXPECT_EQ(test.top(), true);
    // EXPECT_EQ(test.size(), 9);
}