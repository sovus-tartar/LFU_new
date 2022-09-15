#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <iterator>
#include <vector>

namespace caches
{

    template <typename T>
    struct node_t
    {
        T data;
        int hit_count;
        int key;
    };

    template <typename T>
    bool cmp_(const node_t<T> &a, const node_t<T> &b)
    {
        return a.hit_count <= b.hit_count;
    }

    template <typename T, typename key_t, typename F>
    struct cache_t
    {
        using ListIt = typename std::list<node_t<T>>::iterator;

        size_t sz_;
        std::list<node_t<T>> cache_;
        std::unordered_map<key_t, ListIt> hashmap_;

        cache_t(size_t sz) : sz_(sz){};

        
        ListIt put_node(ListIt node)
        {
            int hit = node->hit_count;

            for (auto it = cache_.begin();; it++)
            {
                int curr_hit = it->hit_count;

                if ((hit < curr_hit) || (it == cache_.end()))
                {
                    auto new_it = cache_.insert(it, *node);

                    hashmap_[node->key] = new_it;
                    cache_.erase(node);

                    return new_it;
                }
            }
        }
        
        ListIt put_node(node_t<T> node)
        {
            int hit = node.hit_count;

            for (auto it = cache_.begin();; it++)
            {
                int curr_hit = it->hit_count;

                if ((hit < curr_hit) || (it == cache_.end()))
                {
                    auto new_it = cache_.insert(it, node);

                    hashmap_[node.key] = new_it;

                    return new_it;
                }
            }
        }

        bool cache_request(int key, F slow_get_page)
        {
            auto node = hashmap_.find(key);

            if (node != hashmap_.end())
            {
                node->second->hit_count++;
                // hashmap_.erase(node->second->key);
                put_node(node->second);
                return true;
            }

            if (is_full())
            {
                int key_to_delete = cache_.front().key;
                cache_.pop_front();
                hashmap_.erase(key_to_delete);
            }

            struct node_t<T> temp;
            temp.data = slow_get_page(key);
            temp.hit_count = 0;
            temp.key = key;

            put_node(temp);

            return false;
        }

        bool is_full() const
        {
            return (cache_.size() == sz_);
        }

        void print_cache() const // only for int
        {
            for (auto it = cache_.begin(); it != cache_.end(); it++)
            {
                std::cout << (*it).data << " ";
            }
            std::cout << std::endl;
        }
    };
}
