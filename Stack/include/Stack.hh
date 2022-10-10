#ifndef STACK_HH
#define STACK_HH

#include <algorithm>
#include <bitset>
#include <climits>
#include <limits>
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

    static constexpr size_t START_SIZE = std::numeric_limits<unsigned char>::digits;
    static constexpr size_t BITS_IN_CHAR = START_SIZE;


    static constexpr unsigned int EXPANSION_FACTOR = 2;
private:

    size_t GetActualCapacity() const;
    size_t GetActualSize() const;

    size_t capacity_ = START_SIZE;
    size_t size_ = 0;

    unsigned char* data_ = nullptr;
};

template <typename T>
Stack<T>::Stack() : data_(new T[START_SIZE])
    {}


template <typename T>
Stack<T>::Stack(size_t capacity) : capacity_(capacity), data_(new T[capacity_])
    {}

template <typename T>
Stack<T>::Stack(const Stack& other)
{
    data_ = new T[other.capacity_];
    size_ = other.size_;
    capacity_ = other.capacity_;

    std::copy(other.data_, other.data_ + size_, data_);
}

template <typename T>
Stack<T>::Stack (Stack&& other) noexcept
{
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
}

template <typename T>
void Stack<T>::Push(T elem)
{
    if (size_ == capacity_)
    {
        T* tmp_data = new T[EXPANSION_FACTOR * capacity_];
        std::copy(data_, data_ + size_, tmp_data);
        delete[] data_;
        data_ = tmp_data;
        capacity_ *= EXPANSION_FACTOR;
    }

    data_[size_] = elem;
    size_++;
}

template <typename T>
void Stack<T>::Pop()
{
    if (size_ != 0)
        size_--;
}

template <typename T>
bool Stack<T>::Empty() const
{
    return size_ == 0;
}

template <typename T>
size_t Stack<T>::Size() const
{
    return size_;
}

template <typename T>
size_t Stack<T>::Capacity() const
{
    return capacity_;
}

template <typename T>
T& Stack<T>::Top()
{
    return data_[size_ - 1];
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if (this != std::addressof(other))
    {
        delete[] data_;
        data_ = new T[other.capacity_];
        size_ = other.size_;
        capacity_ = other.capacity_;

        std::copy(other.data_, other.data_ + size_, data_);
    }

    return *this;
}


template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
{
    if (this != std::addressof(other))
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    return *this;
}

template <typename T>
bool Stack<T>::operator==(const Stack& other) const
{
    if (size_ != other.size_)
        return false;

    T* iter = data_;
    T* other_it = other.data_;
    for (; iter != data_ + size_; ++iter, ++other_it)
    {
        if (*iter != *other_it)
            return false;
    }

    return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack& other) const
{
    return !((*this) == other);
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] data_;
}

} // namespace custom_containers

#endif