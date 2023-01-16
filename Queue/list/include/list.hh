#ifndef LIST_HH
#define LIST_HH
#include <cstdlib>
#include <utility>
#include <memory>

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

private:
    void PushEmpty(const T& elem);
    void PopLast();
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


} // namespace custom_containers




#endif