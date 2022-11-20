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
    virtual const T& front () const& = 0;
    virtual const T& back () const& = 0;

    virtual T& front () & = 0;
    virtual T& back () & = 0;
    #endif

    virtual bool empty() const = 0;
    virtual size_t size() const = 0;

    virtual void push(const T& elem) = 0;
    virtual void pop() = 0;

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

    const T& front () const&;
    const T& back () const&;

    T& front () &;
    T& back () &;

    bool empty() const override;
    size_t size() const override;

    void push(const T& elem) override;
    void pop() override;

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

    auto front () const& -> decltype(pop_stack_.Top());
    auto back () const& -> decltype(push_stack_.Top());

    auto front () & -> decltype(pop_stack_.Top());
    auto back () & -> decltype(push_stack_.Top());

    bool empty() const override;
    size_t size() const override;

    void push(const T& elem) override;
    void pop() override;

    QueueStack& operator=(const QueueStack& other) = default;
    QueueStack& operator=(QueueStack&& other) noexcept = default;

    bool operator==(const QueueStack& other) const;
    bool operator!=(const QueueStack& other) const;

    ~QueueStack() = default;

private:

    void MoveFromPushToPop();

};

template <typename T>
const T& QueueList<T>::front () const&
{
    return list_.front();
}

template <typename T>
const T& QueueList<T>::back () const&
{
    return list_.back();
}

template <typename T>
T& QueueList<T>::front () &
{
    return list_.front();
}

template <typename T>
T& QueueList<T>::back () &
{
    return list_.back();
}


template <typename T>
bool QueueList<T>::empty() const
{
    return list_.empty();
}

template <typename T>
size_t QueueList<T>::size() const
{
    return list_.size();
}

template <typename T>
void QueueList<T>::push(const T& elem)
{
    list_.push_back(elem);
}

template <typename T>
void QueueList<T>::pop()
{
    list_.pop_front();
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
auto QueueStack<T>::front () const& -> decltype(pop_stack_.Top())
    {
        if (pop_stack_.Empty() && (push_stack_.Size() == 1))
            return push_stack_.Top();

        if (pop_stack_.Empty())
            MoveFromPushToPop();
        
        return pop_stack_.Top();
    }

template <typename T>
auto QueueStack<T>::back () const& -> decltype(push_stack_.Top())
{
    return push_stack_.Top();
}

template <typename T>
auto QueueStack<T>::front () & -> decltype(pop_stack_.Top())
    {
        if ((pop_stack_.Empty()) && (push_stack_.Size() == 1))
            return push_stack_.Top();

        if (pop_stack_.Empty())
            MoveFromPushToPop();
        
        return pop_stack_.Top();
    }

template <typename T>
auto QueueStack<T>::back () & -> decltype(push_stack_.Top())
    {
        return push_stack_.Top();
    }

template <typename T>
bool QueueStack<T>::empty() const
{
    return pop_stack_.Empty() && push_stack_.Empty();
}

template <typename T>
size_t QueueStack<T>::size() const
{
    return pop_stack_.Size() + push_stack_.Size();
}

template <typename T>
void QueueStack<T>::push(const T& elem)
{
    push_stack_.Push(elem);
}

template <typename T>
void QueueStack<T>::pop()
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