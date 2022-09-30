#include <gtest/gtest.h>

#include "Stack.hh"

template <typename T>
using Stack = custom_containers::Stack<T>;

TEST(StackT, ConstructTest)
{
    Stack<int> test(10);
    test.push(15);
    test.push(9);
    test.push(8);

    EXPECT_EQ(test.size(), 3);

}


TEST(StackT, CopyConstructTest)
{
    Stack<float> test(10);
    test.push(15);
    test.push(9);
    test.push(8);

    Stack<float> testCopy{test};

    EXPECT_EQ(test == testCopy, true);

}

TEST(StackBool, EqualityTest)
{
    Stack<bool> test1(8);
    test1.push(true);
    test1.push(true);
    test1.push(false);

    Stack<bool> test2(8);
    test2.push(true);
    test2.push(true);
    test2.push(false);

    EXPECT_EQ(test1 == test2, true);

}

TEST(StackBool, CopyConstructTest)
{
    Stack<bool> test(10);
    test.push(true);
    test.push(true);
    test.push(false);

    Stack<bool> testCopy{test};

    EXPECT_EQ(test == testCopy, true);

}

TEST(StackBool, MoveConstructTest)
{
    Stack<bool> test(10);
    test.push(true);
    test.push(true);
    test.push(false);

    Stack<bool> testCopy{test};

    Stack<bool> testMove{test};

    EXPECT_EQ(testMove == testCopy, true);

}

TEST(StackBool, EmptyFuncTest)
{
    Stack<bool> test(0);

    EXPECT_EQ(test.empty(), true);

    for (int i = 0; i < 8; i++)
        test.push(true);

    EXPECT_EQ(test.empty(), false);
}

TEST(StackBool, SizeFuncTest)
{
    Stack<bool> test(0);

    for (int i = 0; i < 2; i++)
        test.push(true);

    EXPECT_EQ(test.size(), 2);

    for (int i = 0; i < 6; i++)
        test.push(true);

    EXPECT_EQ(test.size(), 8);
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