#ifndef HASHMAP_HH
#define HASHMAP_HH

#include "list.hh"
#include <vector>
#include <utility>
#include <unordered_map>


namespace custom_containers
{

template <typename Key, typename T, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class Hashmap
{
private:

struct HashmapNode
{
    Key key;
    T value;
};

public:


private:
    std::vector<List<T>::iterator> iter_vec;
    List<HashmapNode> node_list;
};

}


#endif