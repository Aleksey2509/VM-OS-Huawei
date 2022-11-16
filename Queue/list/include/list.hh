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
    size_t size_ = 0;

    struct Node final
    {
        Node* next = nullptr;
        Node* prev = nullptr;
        T data{};
    };

    Node* front_ = nullptr;
    Node* back_ = nullptr;

public:
    List() = default;
    List(const List& other);
    List(List&& other) = default;

    T& front () &;
    T& back () &;

    bool empty();
    size_t size();

    void push_front(const T& elem);
    void push_back(const T& elem);

    void pop_front();
    void pop_back();

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept = default;

    bool operator==(const List& other) const;
    bool operator!=(const List& other) const;

    ~List();

private:
    void push_empty(const T& elem);
    void pop_last();
};

template <typename T>
List<T>::List(const List& other) : size_(other.size_)
{
    if (other.front_)
    {
        front_ = new Node;
        front_->data = other.front_->data;
    }

    back_ = front_;

    for(auto other_it = other.front_->next; other_it; other_it = other_it->next)
    {
        back_->next = new Node;
        back_->next->prev = back_;
        back_ = back_->next;

        back_->data = other_it->data;
    }

}

template <typename T>
T& List<T>::front () &
{
    return front_->data;
}

template <typename T>
T& List<T>::back () &
{
    return back_->data;
}

template <typename T>
bool List<T>::empty()
{
    return size_ == 0;
}

template <typename T>
size_t List<T>::size()
{
    return size_;
}

template <typename T>
void List<T>::push_empty(const T& elem)
{
    front_ = new Node;
    front_->data = elem;
    back_ = front_;
    size_++;

    return;
}

template <typename T>
void List<T>::push_front(const T& elem)
{
    if (empty())
    {
        push_empty(elem);
        return;
    }

    front_->prev = new Node;
    front_->prev->next = front_;
    front_ = front_->prev;
    front_->data = elem;

    size_++;
}

// debug me
template <typename T>
void List<T>::push_back(const T& elem)
{
    if (empty())
    {
        push_empty(elem);
        return;
    }

    back_->next = new Node;
    back_->next->prev = back_;
    back_ = back_->next;
    back_->data = elem;

    size_++;
}

template <typename T>
void List<T>::pop_last()
{
    delete front_;
    front_ = nullptr;
    back_ = nullptr;
    size_--;

    return;
}

template <typename T>
void List<T>::pop_front()
{
    if (size_ == 1)
    {
        pop_last();
        return;
    }

    front_ = front_->next;
    delete front_->prev;
    front_->prev = nullptr;
    size_--;

    return;
}

template <typename T>
void List<T>::pop_back()
{
    if (size_ == 1)
    {
        pop_last();
        return;
    }

    back_ = back_->prev;
    delete back_->next;
    back_->next = nullptr;
    size_--;

    return;
}

template <typename T>
List<T>& List<T>::operator=(const List& other)
{
    List tmp{other};
    std::swap(this->front_, tmp.front_);
    std::swap(this->back_, tmp.back_);
    std::swap(this->size_, tmp.size_);

    return *this;
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


} // namespace custom_containers




#endif