#ifndef QUEUE_HH
#define QUEUE_HH

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

// decltype(push_stack_.Top())

    auto front () const& -> decltype(pop_stack_.Top());
    auto back () const& -> decltype(push_stack_.Top());

    auto front () & -> decltype(pop_stack_.Top());
    auto back () & -> decltype(push_stack_.Top());

    bool empty() const;
    size_t size() const;

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
    // we have to preserve the last element of push_stack_ in push_stack_ for correct work of back()

    // take it out, so it is not copied to pop_stack_
    auto push_stack_back = push_stack_.Top();
    push_stack_.Pop();

    while(!(push_stack_.Empty()))
    {
        pop_stack_.Push(push_stack_.Top());
        push_stack_.Pop();
    }

    // put the last element back into the push_stack()
    push_stack_.Push(push_stack_back);
}

template <typename T>
auto Queue<T, custom_containers::Stack<T>>::front () const& -> decltype(pop_stack_.Top())
    {
        if (pop_stack_.Empty() && (push_stack_.Size() == 1))
            return push_stack_.Top();

        if (pop_stack_.Empty())
            MoveFromPushToPop();
        
        return pop_stack_.Top();
    }

template <typename T>
auto Queue<T, custom_containers::Stack<T>>::back () const& -> decltype(push_stack_.Top())
{
    return push_stack_.Top();
}

template <typename T>
auto Queue<T, custom_containers::Stack<T>>::front () & -> decltype(pop_stack_.Top())
    {
        if ((pop_stack_.Empty()) && (push_stack_.Size() == 1))
            return push_stack_.Top();

        if (pop_stack_.Empty())
            MoveFromPushToPop();
        
        return pop_stack_.Top();
    }

template <typename T>
auto Queue<T, custom_containers::Stack<T>>::back () & -> decltype(push_stack_.Top())
    {
        return push_stack_.Top();
    }

template <typename T>
bool Queue<T, custom_containers::Stack<T>>::empty() const
{
    return pop_stack_.Empty() && push_stack_.Empty();
}

template <typename T>
size_t Queue<T, custom_containers::Stack<T>>::size() const
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
    if (pop_stack_.Empty() && (push_stack_.Size() == 1))
    {
        push_stack_.Pop();
        return;
    }

    if (pop_stack_.Empty())
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