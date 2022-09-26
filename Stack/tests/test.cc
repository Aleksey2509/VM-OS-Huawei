#include <gtest/gtest.h>

#include "Stack.hh"

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