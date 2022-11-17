#ifndef QUEUE_HH
#define QUEUE_HH

#include <concepts>
#include "stack.hh"
#include "list.hh"

namespace custom_containers
{

template <typename T, typename Container = custom_containers::List<T>>
class Queue
{

    Container cont_;

public:

    Queue() = default;
    Queue(const Queue& other) = default;
    Queue(Queue&& other) = default;

    const T& front () const&;
    const T& back () const&;

    T& front () &;
    T& back () &;

    bool empty() const;
    size_t size() const;

    void push(const T& elem);
    void pop();

    Queue& operator=(const Queue& other) = default;
    Queue& operator=(Queue&& other) noexcept = default;

    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;

    ~Queue() = default;

};

template <typename T>
class Queue<T, custom_containers::Stack<T>>
{

    custom_containers::Stack<T> push_stack_;
    custom_containers::Stack<T> pop_stack_;

public:
    Queue() = default;
    Queue(const Queue& other) = default;
    Queue(Queue&& other) = default;

    const T& front () const&;
    const T& back () const&;

    T& front () &;
    T& back () &;

    bool empty();
    size_t size();

    void push(const T& elem);
    void pop();

    Queue& operator=(const Queue& other) = default;
    Queue& operator=(Queue&& other) noexcept = default;

    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;

    ~Queue() = default;

private:

    void MoveFromPushToPop();

};

template <typename T, typename Container>
const T& Queue<T, Container>::front () const&
{
    return cont_.front();
}

template <typename T, typename Container>
const T& Queue<T, Container>::back () const&
{
    return cont_.back();
}

template <typename T, typename Container>
T& Queue<T, Container>::front () &
{
    return cont_.front();
}

template <typename T, typename Container>
T& Queue<T, Container>::back () &
{
    return cont_.back();
}


template <typename T, typename Container>
bool Queue<T, Container>::empty() const
{
    return cont_.empty();
}

template <typename T, typename Container>
size_t Queue<T, Container>::size() const
{
    return cont_.size();
}

template <typename T, typename Container>
void Queue<T, Container>::push(const T& elem)
{
    cont_.push_back(elem);
}

template <typename T, typename Container>
void Queue<T, Container>::pop()
{
    cont_.pop_front();
}

template <typename T, typename Container>
bool Queue<T, Container>::operator==(const Queue& other) const
{
    return cont_ == other.cont_;
}

template <typename T, typename Container>
bool Queue<T, Container>::operator!=(const Queue& other) const
{
    return !(cont_ == other.cont_);
}

template <typename T>
void Queue<T, custom_containers::Stack<T>>::MoveFromPushToPop()
{
    while(!(push_stack_.Empty()))
    {
        pop_stack_.Push(push_stack_.Top());
    }
}

template <typename T>
T& Queue<T, custom_containers::Stack<T>>::front () &
{
    if (push_stack_.Empty())
        MoveFromPushToPop();

    return push_stack_.Top();
}

template <typename T>
T& Queue<T, custom_containers::Stack<T>>::back () &
{
    return pop_stack_.Top();
}

template <typename T>
const T& Queue<T, custom_containers::Stack<T>>::front () const&
{
    if (push_stack_.Empty())
        MoveFromPushToPop();

    return push_stack_.Top();
}

template <typename T>
const T& Queue<T, custom_containers::Stack<T>>::back () const &
{
    return pop_stack_.Top();
}

template <typename T>
bool Queue<T, custom_containers::Stack<T>>::empty()
{
    return pop_stack_.Empty() && push_stack_.Empty();
}

template <typename T>
size_t Queue<T, custom_containers::Stack<T>>::size()
{
    return pop_stack_.Size() + push_stack_.Size();
}

template <typename T>
void Queue<T, custom_containers::Stack<T>>::push(const T& elem)
{
    push_stack_.Push(elem);
}

template <typename T>
void Queue<T, custom_containers::Stack<T>>::pop()
{
    if (push_stack_.Empty())
        MoveFromPushToPop();

    pop_stack_.Pop();
}

template <typename T>
bool Queue<T, custom_containers::Stack<T>>::operator==(const Queue& other) const
{
    return (pop_stack_ == other.pop_stack_) && (push_stack_ == other.push_stack_);
}

template <typename T>
bool Queue<T, custom_containers::Stack<T>>::operator!=(const Queue& other) const
{
    return !(*this == other);
}


} // namespace custom_containers

#endif