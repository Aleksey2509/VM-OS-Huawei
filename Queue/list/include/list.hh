#ifndef LIST_HH
#define LIST_HH
#include <cstdlib>
#include <utility>

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
};

template <typename T>
List<T>::List(const List& other)
{
    auto other_it = other.front_;
    auto it = front_;
    Node* prev_it = nullptr;

    while(other_it)
    {
        prev_it = it;
        it = new Node;

        if (prev_it)
            prev_it->next = it;
        it->prev = prev_it;
        it->data = other_it->data;

        size_++;
    }

}

template <typename T>
T& List<T>::front () &
{
    return front->data;
}

template <typename T>
T& List<T>::back () &
{
    return back->data;
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

// debug me
template <typename T>
void List<T>::push_front(const T& elem)
{
    auto new_front = new Node;
    new_front->data = elem;
    new_front->next = front_;
    front_ = new_front;
    size_++;
}

// debug me
template <typename T>
void List<T>::push_back(const T& elem)
{
    auto new_back = new Node;
    new_back->data = elem;
    new_back->prev = back_;
    back_ = new_back;
    size_++;
}

// debug me
template <typename T>
void List<T>::pop_front()
{
    auto new_front = front_->next;
    delete front_;
    front_ = new_front;
    size_--;
}

// debug me
template <typename T>
void List<T>::pop_back()
{
    auto new_back = front_->back;
    delete back_;
    back_ = new_back;
    size_--;
}

// works?
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