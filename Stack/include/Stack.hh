#ifndef STACK_HH
#define STACK_HH

#include <algorithm>
#include <bitset>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <iostream>

namespace custom_containers
{

template <typename T>
class Stack
{
public:

    Stack();
    explicit Stack(size_t capacity);
    Stack(const Stack& other);
    Stack (Stack&& other) noexcept;

    void Push(T elem);
    void Pop();
    bool Empty() const;
    size_t Size() const;
    size_t Capacity() const;
    T& Top();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

    ~Stack();

    static constexpr size_t START_SIZE = 10;

    static constexpr unsigned int EXPANSION_FACTOR = 2;
private:
    size_t capacity_ = START_SIZE;

    size_t size_ = 0;

    T* data_ = nullptr;
};


template <>
class Stack<bool>
{
public:

    Stack();
    explicit Stack(size_t capacity);
    Stack(const Stack& other);
    Stack (Stack&& other) noexcept;

    void Push(bool elem);
    void Pop();
    bool Empty() const;
    size_t Size() const;
    size_t Capacity() const;
    bool Top();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;


    ~Stack();

    static constexpr size_t START_SIZE = CHAR_BIT;

    static constexpr unsigned int EXPANSION_FACTOR = 2;
private:

    size_t GetActualCapacity() const;
    size_t GetActualSize() const;

    size_t capacity_ = START_SIZE;
    size_t size_ = 0;

    unsigned char* data_ = nullptr;
};

} // namespace custom_containers

#include "Stack-impl.hh"

#endif