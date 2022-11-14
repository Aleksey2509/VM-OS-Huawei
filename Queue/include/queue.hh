#ifndef QUEUE_HH
#define QUEUE_HH

#include <concepts>
#include "stack.hh"
#include "list.hh"

namespace custom_containers
{

template <typename T, typename Container>
class Queue
{

public:

    Queue() = default;
    Queue(const Queue& other) = default;
    Queue(Queue&& other) = default;

    T& front () &{};
    T& back () &{};

    bool empty(){};
    size_t size(){};

    void push(const T& elem){};
    void pop(){};

    Queue& operator=(const Queue& other){};
    Queue& operator=(Queue&& other) noexcept{};

    bool operator==(const Queue& other) const{};
    bool operator!=(const Queue& other) const{};

    ~Queue(){};

};

template <typename T>
class Queue<T, custom_containers::Stack<T>>
{
public:
    Queue() = default;
    Queue(const Queue& other) = default;
    Queue(Queue&& other) = default;

    T& front () &{};
    T& back () &{};

    bool empty(){};
    size_t size(){};

    void push(const T& elem){};
    void pop(){};

    Queue& operator=(const Queue& other) = default;
    Queue& operator=(Queue&& other) noexcept = default;

    bool operator==(const Queue& other) const{};
    bool operator!=(const Queue& other) const{};

    ~Queue(){};

};


} // namespace custom_containers

#endif