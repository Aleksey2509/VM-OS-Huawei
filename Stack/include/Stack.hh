#ifndef STACK_HH
#define STACK_HH

#include <algorithm>
#include <bitset>
#include <climits>
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
    Stack (Stack&& other);

    void push(T elem);
    void pop();
    bool empty() const;
    size_t size() const;
    T& top();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other);

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;


    ~Stack();

    static constexpr size_t DEFAULT_CAPACITY = 10;

private:
    static constexpr unsigned int EXPANSION_FACTOR = 2;

    size_t capacity_ = DEFAULT_CAPACITY;
    size_t size_ = 0;

    T* data_ = nullptr;
    void print();
};


template <>
class Stack<bool>
{
public:

    Stack();
    explicit Stack(size_t capacity);
    Stack(const Stack& other);
    Stack (Stack&& other);

    void push(bool elem);
    void pop();
    bool empty() const;
    size_t size() const;
    bool top();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other);

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;


    ~Stack();

    static constexpr size_t MIN_SIZE = CHAR_BIT;

private:

    inline  size_t getActualCapacity() const;
    inline  size_t getActualSize() const;

    static constexpr unsigned int EXPANSION_FACTOR = 2;
    size_t capacity_ = MIN_SIZE;
    size_t size_ = 0;

    unsigned char* data_ = nullptr;
    void print();
};

} // namespace custom_containers


namespace custom_containers
{

// Stack <T> implementation

template <typename T>
Stack<T>::Stack() : data_(new T[DEFAULT_CAPACITY])
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
Stack<T>::Stack (Stack&& other)
{
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
}

template <typename T>
void Stack<T>::push(T elem)
{
    if (size_ == capacity_)
    {
        T* tmpData = new T[EXPANSION_FACTOR * capacity_];
        std::copy(data_, data_ + size_, tmpData);
        delete[] data_;
        data_ = tmpData;
        capacity_ *= EXPANSION_FACTOR;
    }

    data_[size_] = elem;
    size_++;
}

template <typename T>
void Stack<T>::pop()
{
    if (size_ != 0)
        size_--;
}

template <typename T>
bool Stack<T>::empty() const
{
    return size_ == 0;
}

template <typename T>
size_t Stack<T>::size() const
{
    return size_;
}

template <typename T>
T& Stack<T>::top()
{
    if (!size_) // top() called on empty stack is undefined, so anything can be returned
        return false;

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
Stack<T>& Stack<T>::operator=(Stack<T>&& other)
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
    if ((size_ != other.size_) || (capacity_ != other.capacity_))
        return false;

    T* it = data_;
    T* otherIt = other.data_;
    for (; it != data_ + size_; ++it, ++otherIt)
    {
        if (*it != *otherIt)
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
void Stack<T>::print()
{
    for (auto it = data_; it != data_ + size_; ++it)
        std::cout << *it << " ";

    std::cout << std::endl;
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] data_;
}

} // namespace custom_containers



namespace custom_containers
{

// Stack <bool> implementation

Stack<bool>::Stack() : data_(new unsigned char[static_cast<size_t>(std::ceil(static_cast<double>(capacity_) / CHAR_BIT))])
{ }


Stack<bool>::Stack(size_t capacity) : capacity_(capacity),
                                      data_(new unsigned char[static_cast<size_t>(std::ceil(static_cast<double>(capacity_) / CHAR_BIT))])
{ }



Stack<bool>::Stack(const Stack& other)
{
    data_ = new unsigned char[other.getActualCapacity()];
    size_ = other.size_;
    capacity_ = other.capacity_;

    std::copy(other.data_, other.data_ + getActualSize(), data_);
}
    

Stack<bool>::Stack (Stack&& other)
{
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
}


void Stack<bool>::push(bool elem)
{

    if (size_ == capacity_)
    {
        unsigned char* tmpData = new unsigned char[EXPANSION_FACTOR * getActualCapacity()];
        std::copy(data_, data_ + getActualCapacity(), tmpData);
        delete[] data_;
        data_ = tmpData;
        capacity_ = EXPANSION_FACTOR * getActualCapacity() * CHAR_BIT;
    }

    if (elem)
    {
        data_[size_ / CHAR_BIT] |= (elem << (size_ % CHAR_BIT));
    }
    else
    {
        data_[size_ / CHAR_BIT] &= ~(elem << (size_ % CHAR_BIT));
    }

    size_++;

}


void Stack<bool>::pop()
{
    if (size_ != 0)
        size_--;
}


bool Stack<bool>::empty() const
{
    return size_ == 0;
}


size_t Stack<bool>::size() const
{
    return size_;
}


bool Stack<bool>::top()
{
    if (size_ == 0) // top() called on empty stack is undefined, so anything can be returned
        return false;

    return data_[getActualSize() - 1] & (1 << (((size_ - 1) % CHAR_BIT)));
}


Stack<bool>& Stack<bool>::operator=(const Stack& other)
{
    if (this != std::addressof(other))
    {
        delete[] data_;
        data_ = new unsigned char[other.getActualCapacity()];
        size_ = other.size_;
        capacity_ = other.capacity_;

        std::copy(other.data_, other.data_ + getActualSize(), data_);
    }

    return *this;
}


Stack<bool>& Stack<bool>::operator=(Stack&& other)
{
    if (this != std::addressof(other))
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    return *this;
}


bool Stack<bool>::operator==(const Stack& other) const
{
    if ((size_ != other.size_) || (capacity_ != other.capacity_))
    return false;

    unsigned char* it = data_;
    unsigned char* otherIt = other.data_;
    unsigned char* itEnd = data_ + getActualSize();

    for (; (it - 1) != itEnd; ++it, ++otherIt)
    {
        if (*it != *otherIt)
            return false;
    }

    if (!(size_ % CHAR_BIT))
    {
        if (*it != *otherIt)
            return false;
    }
    else
    {
        if ((*it & (0xFF >> (CHAR_BIT - size_ % CHAR_BIT))) != (*otherIt & (0xFF >> (CHAR_BIT - size_ % CHAR_BIT))) )
            return false;
    }

    return true;
}


bool Stack<bool>::operator!=(const Stack& other) const
{
    return !((*this) == other);
}

void Stack<bool>::print()
{
    for (auto it = data_; it != data_ + getActualSize(); ++it)
        std::cout << std::bitset<CHAR_BIT>(*it) << " ";

    std::cout << std::endl;
}

Stack<bool>::~Stack()
{
    delete[] data_;
}

inline size_t Stack<bool>::getActualCapacity() const
{
    return static_cast<size_t>(std::ceil(static_cast<double>(capacity_) / CHAR_BIT));
}

inline size_t Stack<bool>::getActualSize() const
{
    return static_cast<size_t>(std::ceil(static_cast<double>(size_) / CHAR_BIT));
}

} // namespace custom_containers


#endif