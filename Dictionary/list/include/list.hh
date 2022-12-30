#ifndef LIST_HH
#define LIST_HH
#include <cstdlib>
#include <utility>
#include <list>
#include <iostream>

namespace custom_containers
{

template <typename T>
class List final
{
public:
    List() = default;
    List(const List& other);
    List(List&& other) noexcept;

    const T& Front() const&;
    const T& Back() const&;

    T& Front () &;
    T& Back () &;

    bool Empty() const;
    size_t Size() const;

    void PushFront(const T& elem);
    void PushBack(const T& elem);

    void PopFront();
    void PopBack();

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;

    bool operator==(const List& other) const;
    bool operator!=(const List& other) const;

    ~List();

    struct iterator;
    struct const_iterator;

    iterator begin();
    iterator end();

    const_iterator cbegin();
    const_iterator cend();

private:

    size_t size_ = 0;

    struct Node
    {
        Node* prev = nullptr;
        Node* next = nullptr;
        T data{};
    };

    Node* front_ = nullptr;
    Node* back_ = nullptr;

    void PushEmpty(const T& elem);
    void PopLast();
};

template <typename T>
struct List<T>::iterator final
{
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;

    explicit iterator(Node* pointer = nullptr);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    bool operator==(const iterator& rhs) const;
    bool operator!=(const iterator& rhs) const;
    T& operator*();
    T* operator->();


    Node* ptr = nullptr;
};

template <typename T>
struct List<T>::const_iterator final
{
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;


    explicit const_iterator(Node* pointer = nullptr);
    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);
    bool operator==(const const_iterator& rhs) const;
    bool operator!=(const const_iterator& rhs) const;
    const T& operator*();
    const T* operator->();


    Node* ptr = nullptr;
};

template <typename T>
List<T>::iterator::iterator(Node* pointer) : ptr(pointer)
{}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
    ptr = ptr->next;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    List<T>::iterator old_iter{*this};
    ++(*this);
    return old_iter;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
    ptr = ptr->prev;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    List<T>::iterator old_iter{*this};
    --(*this);
    return old_iter;
}

template <typename T>
bool List<T>::iterator::operator==(const iterator& rhs) const
{
    return ptr == rhs.ptr;
}

template <typename T>
bool List<T>::iterator::operator!=(const iterator& rhs) const
{
    return ptr != rhs.ptr;
}

template <typename T>
T& List<T>::iterator::operator*()
{
    return ptr->data;
}

template <typename T>
T* List<T>::iterator::operator->()
{
    return &(ptr->data);
}



template <typename T>
List<T>::const_iterator::const_iterator(Node* pointer) : ptr(pointer)
{}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
    ptr = ptr->next;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
    List<T>::const_iterator old_iter{*this};
    ++(*this);
    return old_iter;
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
    ptr = ptr->prev;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
    List<T>::iterator old_iter{*this};
    --(*this);
    return old_iter;
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator& rhs) const
{
    return ptr == rhs.ptr;
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator& rhs) const
{
    return ptr != rhs.ptr;
}

template <typename T>
const T& List<T>::const_iterator::operator*()
{
    return ptr->data;
}

template <typename T>
const T* List<T>::const_iterator::operator->()
{
    return &(ptr->data);
}



template <typename T>
List<T>::List(const List& other) : size_(other.size_)
{
    if (other.front_)
    {
        front_ = new Node;
        front_->data = other.front_->data;
    }

    back_ = front_;

    for(auto other_iter = other.front_->next; other_iter; other_iter = other_iter->next)
    {
        back_->next = new Node;
        back_->next->prev = back_;
        back_ = back_->next;

        back_->data = other_iter->data;
    }

}
template <typename T>
List<T>::List(List&& other) noexcept
{
    std::swap(this->front_, other.front_);
    std::swap(this->back_, other.back_);
    std::swap(this->size_, other.size_);
}

template <typename T>
T& List<T>::Front() &
{
    return front_->data;
}

template <typename T>
const T& List<T>::Front() const&
{
    return front_->data;
}

template <typename T>
T& List<T>::Back () &
{
    return back_->data;
}

template <typename T>
const T& List<T>::Back() const&
{
    return back_->data;
}

template <typename T>
bool List<T>::Empty() const
{
    return size_ == 0;
}

template <typename T>
size_t List<T>::Size() const
{
    return size_;
}

template <typename T>
void List<T>::PushEmpty(const T& elem)
{
    front_ = new Node;
    front_->data = elem;
    back_ = front_;
    size_++;
}

template <typename T>
void List<T>::PushFront(const T& elem)
{
    if (Empty())
    {
        PushEmpty(elem);
        return;
    }

    front_->prev = new Node;
    front_->prev->next = front_;
    front_ = front_->prev;
    front_->data = elem;

    size_++;
}

template <typename T>
void List<T>::PushBack(const T& elem)
{
    if (Empty())
    {
        PushEmpty(elem);
        return;
    }

    back_->next = new Node;
    back_->next->prev = back_;
    back_ = back_->next;
    back_->data = elem;

    size_++;
}

template <typename T>
void List<T>::PopLast()
{
    delete front_;
    front_ = nullptr;
    back_ = nullptr;
    size_--;
}

template <typename T>
void List<T>::PopFront()
{
    if (size_ == 1)
    {
        PopLast();
        return;
    }

    front_ = front_->next;
    delete front_->prev;
    front_->prev = nullptr;
    size_--;
}

template <typename T>
void List<T>::PopBack()
{
    if (size_ == 1)
    {
        PopLast();
        return;
    }

    back_ = back_->prev;
    delete back_->next;
    back_->next = nullptr;
    size_--;
}

template <typename T>
List<T>& List<T>::operator=(const List& other)
{
    if (this == std::addressof(other))
    {
        return *this;
    }

    List tmp{other};
    std::swap(this->front_, tmp.front_);
    std::swap(this->back_, tmp.back_);
    std::swap(this->size_, tmp.size_);

    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept
{
    std::swap(this->front_, other.front_);
    std::swap(this->back_, other.back_);
    std::swap(this->size_, other.size_);

    return *this;
}

template<typename T>
bool List<T>::operator==(const List& other) const
{
    if (size_ != other.size_)
    {
        return false;
    }

    auto iter = front_;
    auto other_iter = other.front_;
    for (; iter; iter = iter->next, other_iter = other_iter->next)
    {
        if (iter->data != other_iter->data)
        {
            return false;
        }
    }

    return true;
}

template<typename T>
bool List<T>::operator!=(const List& other) const
{
    return !(*this == other);
}

template <typename T>
List<T>::~List()
{
    while(front_)
    {
        auto new_front = front_->next;
        delete front_;
        front_ = new_front;
    }
    
}

template <typename T>
typename List<T>::iterator List<T>::begin()
{
    return iterator{front_};
}

template <typename T>
typename List<T>::iterator List<T>::end()
{
    return iterator{};
}


template <typename T>
typename List<T>::const_iterator List<T>::cbegin()
{
    return const_iterator{front_};
}

template <typename T>
typename List<T>::const_iterator List<T>::cend()
{
    return const_iterator{};
}


} // namespace custom_containers




#endif