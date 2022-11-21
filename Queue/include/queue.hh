#ifndef QUEUE_HH
#define QUEUE_HH

#include "stack.hh"
#include "list.hh"

namespace custom_containers
{

template <typename T>
struct IQueue
{
    #if 0
    virtual const T& Front () const& = 0;
    virtual const T& Back () const& = 0;

    virtual T& Front () & = 0;
    virtual T& Back () & = 0;
    #endif

    virtual bool Empty() const = 0;
    virtual size_t Size() const = 0;

    virtual void Push(const T& elem) = 0;
    virtual void Pop() = 0;

    virtual ~IQueue(){}
};

template <typename T>
class QueueList : public IQueue<T>
{

    custom_containers::List<T> list_;

public:

    QueueList() = default;
    QueueList(const QueueList& other) = default;
    QueueList(QueueList&& other) = default;

    const T& Front () const&;
    const T& Back () const&;

    T& Front () &;
    T& Back () &;

    bool Empty() const override;
    size_t Size() const override;

    void Push(const T& elem) override;
    void Pop() override;

    QueueList& operator=(const QueueList& other) = default;
    QueueList& operator=(QueueList&& other) noexcept = default;

    bool operator==(const QueueList& other) const;
    bool operator!=(const QueueList& other) const;

    ~QueueList() = default;

};

template <typename T>
class QueueStack : public IQueue<T>
{

    custom_containers::Stack<T> push_stack_;
    custom_containers::Stack<T> pop_stack_;

public:
    QueueStack() = default;
    QueueStack(const QueueStack& other) = default;
    QueueStack(QueueStack&& other) = default;

    auto Front () const& -> decltype(pop_stack_.Top());
    auto Back () const& -> decltype(push_stack_.Top());

    auto Front () & -> decltype(pop_stack_.Top());
    auto Back () & -> decltype(push_stack_.Top());

    bool Empty() const override;
    size_t Size() const override;

    void Push(const T& elem) override;
    void Pop() override;

    QueueStack& operator=(const QueueStack& other) = default;
    QueueStack& operator=(QueueStack&& other) noexcept = default;

    bool operator==(const QueueStack& other) const;
    bool operator!=(const QueueStack& other) const;

    ~QueueStack() = default;

private:

    void MoveFromPushToPop();

};

template <typename T>
const T& QueueList<T>::Front () const&
{
    return list_.Front();
}

template <typename T>
const T& QueueList<T>::Back () const&
{
    return list_.Back();
}

template <typename T>
T& QueueList<T>::Front () &
{
    return list_.Front();
}

template <typename T>
T& QueueList<T>::Back () &
{
    return list_.Back();
}


template <typename T>
bool QueueList<T>::Empty() const
{
    return list_.Empty();
}

template <typename T>
size_t QueueList<T>::Size() const
{
    return list_.Size();
}

template <typename T>
void QueueList<T>::Push(const T& elem)
{
    list_.PushBack(elem);
}

template <typename T>
void QueueList<T>::Pop()
{
    list_.PopFront();
}

template <typename T>
bool QueueList<T>::operator==(const QueueList& other) const
{
    return list_ == other.list_;
}

template <typename T>
bool QueueList<T>::operator!=(const QueueList& other) const
{
    return !(list_ == other.list_);
}

template <typename T>
void QueueStack<T>::MoveFromPushToPop()
{
    // we have to preserve the last element of push_stack_ in push_stack_ for correct work of Back()

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
auto QueueStack<T>::Front () const& -> decltype(pop_stack_.Top())
    {
        if (pop_stack_.Empty() && (push_stack_.Size() == 1))
        {
            return push_stack_.Top();
        }

        if (pop_stack_.Empty())
        {
            MoveFromPushToPop();
        }
        
        return pop_stack_.Top();
    }

template <typename T>
auto QueueStack<T>::Back () const& -> decltype(push_stack_.Top())
{
    return push_stack_.Top();
}

template <typename T>
auto QueueStack<T>::Front () & -> decltype(pop_stack_.Top())
    {
        if ((pop_stack_.Empty()) && (push_stack_.Size() == 1))
        {
            return push_stack_.Top();
        }

        if (pop_stack_.Empty())
        {
            MoveFromPushToPop();
        }
        
        return pop_stack_.Top();
    }

template <typename T>
auto QueueStack<T>::Back () & -> decltype(push_stack_.Top())
    {
        return push_stack_.Top();
    }

template <typename T>
bool QueueStack<T>::Empty() const
{
    return pop_stack_.Empty() && push_stack_.Empty();
}

template <typename T>
size_t QueueStack<T>::Size() const
{
    return pop_stack_.Size() + push_stack_.Size();
}

template <typename T>
void QueueStack<T>::Push(const T& elem)
{
    push_stack_.Push(elem);
}

template <typename T>
void QueueStack<T>::Pop()
{
    if (pop_stack_.Empty() && (push_stack_.Size() == 1))
    {
        push_stack_.Pop();
        return;
    }

    if (pop_stack_.Empty())
    {
        MoveFromPushToPop();
    }

    pop_stack_.Pop();
}

template <typename T>
bool QueueStack<T>::operator==(const QueueStack& other) const
{
    return (pop_stack_ == other.pop_stack_) && (push_stack_ == other.push_stack_);
}

template <typename T>
bool QueueStack<T>::operator!=(const QueueStack& other) const
{
    return !(*this == other);
}


} // namespace custom_containers

#endif