#include "Stack.hh"


namespace custom_containers
{


Stack<bool>::Stack() : data_(new unsigned char[static_cast<size_t>(std::ceil(static_cast<double>(capacity_) / BITS_IN_CHAR))])
{ }


Stack<bool>::Stack(size_t capacity) : capacity_(capacity),
                                      data_(new unsigned char[static_cast<size_t>(std::ceil(static_cast<double>(capacity_) / BITS_IN_CHAR))])
{ }



Stack<bool>::Stack(const Stack& other)
{
    data_ = new unsigned char[other.GetActualCapacity()];
    size_ = other.size_;
    capacity_ = other.capacity_;

    std::copy(other.data_, other.data_ + GetActualSize(), data_);
}
    

Stack<bool>::Stack (Stack&& other) noexcept
{
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
}


void Stack<bool>::Push(bool elem)
{

    if (size_ == capacity_)
    {
        auto* tmp_data = new unsigned char[EXPANSION_FACTOR * GetActualCapacity()];
        std::copy(data_, data_ + GetActualCapacity(), tmp_data);
        delete[] data_;
        data_ = tmp_data;
        capacity_ = EXPANSION_FACTOR * GetActualCapacity() * BITS_IN_CHAR;
    }

    if (elem)
    {
        data_[size_ / BITS_IN_CHAR] |= static_cast<unsigned char>(1 << (size_ % BITS_IN_CHAR));
    }
    else
    {
        data_[size_ / BITS_IN_CHAR] &= ~static_cast<unsigned char>(1 << (size_ % BITS_IN_CHAR));
    }

    size_++;

}


void Stack<bool>::Pop()
{
    if (size_ != 0)
        size_--;
}


bool Stack<bool>::Empty() const
{
    return size_ == 0;
}


size_t Stack<bool>::Size() const
{
    return size_;
}

size_t Stack<bool>::Capacity() const
{
    return capacity_;
}

bool Stack<bool>::Top()
{
    return data_[GetActualSize() - 1] & (1 << (((size_ - 1) % BITS_IN_CHAR)));
}


Stack<bool>& Stack<bool>::operator=(const Stack& other)
{
    if (this != std::addressof(other))
    {
        delete[] data_;
        data_ = new unsigned char[other.GetActualCapacity()];
        size_ = other.size_;
        capacity_ = other.capacity_;

        std::copy(other.data_, other.data_ + GetActualSize(), data_);
    }

    return *this;
}


Stack<bool>& Stack<bool>::operator=(Stack&& other) noexcept
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
    if (size_ != other.size_)
        return false;

    if (Empty())
        return true;

    unsigned char* iter = data_;
    unsigned char* other_it = other.data_;
    unsigned char* it_end = data_ + GetActualSize();


    for (; iter != (it_end - 1); ++iter, ++other_it)
    {
        if (*iter != *other_it)
            return false;
    }

    if (!(size_ % BITS_IN_CHAR))
    {
        if (*iter != *other_it)
            return false;
    }
    else
    {
        size_t max_char_value = 1 << BITS_IN_CHAR;
        if ((*iter & (max_char_value >> (BITS_IN_CHAR - size_ % BITS_IN_CHAR))) !=
            (*other_it & (max_char_value >> (BITS_IN_CHAR - size_ % BITS_IN_CHAR))) )
        {
            return false;
        }
    }

    return true;
}


bool Stack<bool>::operator!=(const Stack& other) const
{
    return !((*this) == other);
}

Stack<bool>::~Stack()
{
    delete[] data_;
}

size_t Stack<bool>::GetActualCapacity() const
{
    return static_cast<size_t>(std::ceil(static_cast<double>(capacity_) / BITS_IN_CHAR));
}

size_t Stack<bool>::GetActualSize() const
{
    return static_cast<size_t>(std::ceil(static_cast<double>(size_) / BITS_IN_CHAR));
}

} // namespace custom_containers