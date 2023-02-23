#ifndef HASHTABLE_HH
#define HASHTABLE_HH

// #include "list.hh"
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <iostream>


namespace custom_containers
{

template <typename Key, typename T, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class HashTable // virt destr?
{
public:

struct Node
{
    Key key{};
    T elem{};

    bool operator<=>(const Node& other) const = default;
};

public:
    static constexpr size_t DEFAULT_CAPACITY_ = 1 << 13;

    explicit HashTable(size_t capacity = DEFAULT_CAPACITY_);
    HashTable(const HashTable& rhs);
    HashTable(HashTable&& rhs) noexcept;

    HashTable& operator=(const HashTable &rhs);
    HashTable& operator=(HashTable&& rhs) noexcept;

    bool Empty() const;
    size_t Size() const;
    size_t Capacity() const;
    void Clear();

    bool operator==(const HashTable& rhs) const;
    bool operator!=(const HashTable& rhs) const;

    using iterator = typename std::list<Node>::iterator;
    using const_iterator = typename std::list<Node>::const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    iterator find(const Key& key);
    const_iterator find(const Key& key) const;

    bool insert(const Key& key, const T& elem); // not correct API
    bool insert_or_assign(const Key& key, const T& elem); // not correct API

    T& operator[](const Key& key);
    bool contains(const Key& key) const;


private:
    size_t capacity_;

    std::list<Node> node_list_;
    std::vector<typename std::list<Node>::iterator> iter_vec_;
};

template <typename Key, typename T, typename Hash, typename Pred>
HashTable<Key, T, Hash, Pred>::HashTable(size_t capacity) : capacity_(capacity), node_list_(), iter_vec_(capacity, node_list_.end())
{}

template <typename Key, typename T, typename Hash, typename Pred>
HashTable<Key, T, Hash, Pred>::HashTable(const HashTable& other) : capacity_(other.capacity_), node_list_(other.node_list_), iter_vec_(capacity_, node_list_.end())
{
    for (auto iter = node_list_.begin(); iter != node_list_.end(); iter++)
    {
        auto index = Hash()(iter->key) % capacity_;
        if (iter_vec_[index] == node_list_.end())
        {
            iter_vec_[index] = iter;
        }
    }
}

template <typename Key, typename T, typename Hash, typename Pred>
HashTable<Key, T, Hash, Pred>::HashTable(HashTable&& other) noexcept
{
    std::swap(this->capacity_, other.capacity_);
    std::swap(this->node_list_, other.node_list_);
    std::swap(this->iter_vec_, other.iter_vec_);
}


template <typename Key, typename T, typename Hash, typename Pred>
HashTable<Key, T, Hash, Pred>& HashTable<Key, T, Hash, Pred>::operator=(const HashTable &rhs)
{
    HashTable<Key, T, Hash, Pred> tmp{rhs};

    std::swap(this->capacity_, tmp.capacity_);
    std::swap(this->node_list_, tmp.node_list_);
    std::swap(this->iter_vec_, tmp.iter_vec_);

    return *this;
}


template <typename Key, typename T, typename Hash, typename Pred>
HashTable<Key, T, Hash, Pred>& HashTable<Key, T, Hash, Pred>::operator=(HashTable&& rhs) noexcept
{
    std::swap(this->capacity_, rhs.capacity_);
    std::swap(this->node_list_, rhs.node_list_);
    std::swap(this->iter_vec_, rhs.iter_vec_);

    return *this;
}

template <typename Key, typename T, typename Hash, typename Pred>
bool HashTable<Key, T, Hash, Pred>::Empty() const
{
    return node_list_.empty();
}


template <typename Key, typename T, typename Hash, typename Pred>
size_t HashTable<Key, T, Hash, Pred>::Size() const
{
    return node_list_.size();
}

template <typename Key, typename T, typename Hash, typename Pred>
size_t HashTable<Key, T, Hash, Pred>::Capacity() const
{
    return capacity_;
}
    
template <typename Key, typename T, typename Hash, typename Pred>
void HashTable<Key, T, Hash, Pred>::Clear()
{
    iter_vec_.clear();
    node_list_.clear();
}


template <typename Key, typename T, typename Hash, typename Pred>
bool HashTable<Key, T, Hash, Pred>::operator==(const HashTable& rhs) const
{
    if ((Size() != rhs.Size() ) || (Capacity() != rhs.Capacity()))
        return false;

    if (Empty())
        return true;

    return std::is_permutation(node_list_.begin(), node_list_.end(), rhs.node_list_.begin());
}


template <typename Key, typename T, typename Hash, typename Pred>
bool HashTable<Key, T, Hash, Pred>::operator!=(const HashTable& rhs) const
{
    return !(*this == rhs);
}

template <typename Key, typename T, typename Hash, typename Pred>
bool HashTable<Key, T, Hash, Pred>::insert(const Key& key, const T& elem)
{
    auto iter = find(key);
    if (iter != node_list_.end())
    {
        return false;
    }

    auto index = Hash{}(key) % capacity_;
    iter_vec_[index] =  node_list_.insert(iter_vec_[index], Node{key, elem});

    return true;
}


template <typename Key, typename T, typename Hash, typename Pred>
bool HashTable<Key, T, Hash, Pred>::insert_or_assign(const Key& key, const T& elem)
{
    auto iter = find(key);
    if (iter != node_list_.end())
    {
        iter->elem = elem;
        return false;
    }

    auto index = Hash{}(key) % capacity_;
    iter_vec_[index] =  node_list_.insert(iter_vec_[index], Node{key, elem});

    return true;
}

template <typename Key, typename T, typename Hash, typename Pred>
T& HashTable<Key, T, Hash, Pred>::operator[](const Key& key)
{
    auto iter = find(key);
    if (iter == node_list_.end())
    {
        auto index = Hash{}(key) % capacity_;
        iter_vec_[index] =  node_list_.insert(iter_vec_[index], Node{key, T{}});
    }

    return iter->elem;
}

template <typename Key, typename T, typename Hash, typename Pred>
bool HashTable<Key, T, Hash, Pred>::contains(const Key& key) const
{
    auto iter = find(key);

    if (iter == node_list_.end())
    {
        return false;
    }

    return true;
}

template <typename Key, typename T, typename Hash, typename Pred>
typename HashTable<Key, T, Hash, Pred>::iterator HashTable<Key, T, Hash, Pred>::begin()
{
    return node_list_.begin();
}

template <typename Key, typename T, typename Hash, typename Pred>
typename HashTable<Key, T, Hash, Pred>::iterator HashTable<Key, T, Hash, Pred>::end()
{
    return node_list_.end();
}

template <typename Key, typename T, typename Hash, typename Pred>
typename HashTable<Key, T, Hash, Pred>::const_iterator HashTable<Key, T, Hash, Pred>::begin() const
{
    return node_list_.begin();
}

template <typename Key, typename T, typename Hash, typename Pred>
typename HashTable<Key, T, Hash, Pred>::const_iterator HashTable<Key, T, Hash, Pred>::end() const
{
    return node_list_.end();
}

template <typename Key, typename T, typename Hash, typename Pred>
typename HashTable<Key, T, Hash, Pred>::const_iterator HashTable<Key, T, Hash, Pred>::cbegin() const
{
    return node_list_.cbegin();
}

template <typename Key, typename T, typename Hash, typename Pred>
typename HashTable<Key, T, Hash, Pred>::const_iterator HashTable<Key, T, Hash, Pred>::cend() const
{
    return node_list_.cend();
}

template <typename Key, typename T, typename Hash, typename Pred>
typename HashTable<Key, T, Hash, Pred>::iterator HashTable<Key, T, Hash, Pred>::find(const Key& key)
{
    auto index = Hash{}(key) % capacity_;

    auto iter = iter_vec_[index];
    for (; (iter != node_list_.end()) && ((Hash{}(iter->key) % capacity_) == index); iter++)
    {
        if (iter->key == key)
        {
            return iter;
        }
    }

    return node_list_.end();
}

template <typename Key, typename T, typename Hash, typename Pred>
typename HashTable<Key, T, Hash, Pred>::const_iterator HashTable<Key, T, Hash, Pred>::find(const Key& key) const
{
    auto index = Hash{}(key) % capacity_;

    auto iter = iter_vec_[index];
    for (; (iter != node_list_.end()) && ((Hash{}(iter->key) % capacity_) == index); iter++)
    {
        if (iter->key == key)
        {
            return iter;
        }
    }

    return node_list_.end();
}

}


#endif