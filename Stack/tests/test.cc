#include <gtest/gtest.h>

#include "Stack.hh"
#include <vector>

template <typename T>
using Stack = custom_containers::Stack<T>;

TEST(StackT, ConstructTest)
{
    Stack<int> test(10);
    test.Push(15);
    test.Push(9);
    test.Push(8);

    EXPECT_EQ(test.Size(), 3);
}

TEST(StackT, EqualityTest)
{
    Stack<int> test1(8);
    test1.Push(2);
    test1.Push(3);
    test1.Push(5);

    Stack<int> test2(8);
    test2.Push(2);
    test2.Push(3);
    test2.Push(5);

    EXPECT_EQ(test1 == test2, true);

}


TEST(StackT, CopyConstructTest)
{
    Stack<float> test(10);
    test.Push(15);
    test.Push(9);
    test.Push(8);

    Stack<float> test_copy{test};

    EXPECT_EQ(test == test_copy, true);

}

TEST(StackBool, EqualityTest)
{
    Stack<bool> test1(8);
    test1.Push(true);
    test1.Push(true);
    test1.Push(false);

    Stack<bool> test2(8);
    test2.Push(true);
    test2.Push(true);
    test2.Push(false);

    EXPECT_EQ(test1 == test2, true);

}

TEST(StackBool, CopyConstructTest)
{
    Stack<bool> test(10);
    test.Push(true);
    test.Push(true);
    test.Push(false);

    Stack<bool> test_copy{test};

    EXPECT_EQ(test == test_copy, true);

}

TEST(StackBool, MoveConstructTest)
{
    Stack<bool> test(10);
    test.Push(true);
    test.Push(true);
    test.Push(false);

    Stack<bool> test_copy{test};

    Stack<bool> test_move{test};

    EXPECT_EQ(test_move == test_copy, true);

}

TEST(StackBool, EmptyFuncTest)
{
    Stack<bool> test(0);

    EXPECT_EQ(test.Empty(), true);

    for (int i = 0; i < 8; i++)
        test.Push(true);

    EXPECT_EQ(test.Empty(), false);
}

TEST(StackBool, SizeFuncTest)
{
    Stack<bool> test(0);

    for (int i = 0; i < 2; i++)
        test.Push(true);

    EXPECT_EQ(test.Size(), 2);

    for (int i = 0; i < 6; i++)
        test.Push(true);

    EXPECT_EQ(test.Size(), 8);
}

TEST(StackBool, TopFuncTest)
{
    Stack<bool> test(8);

     for (int i = 0; i < 7; i++)
        test.Push(true);

    EXPECT_EQ(test.Top(), true);

    test.Push(false);

    EXPECT_EQ(test.Top(), false);

}