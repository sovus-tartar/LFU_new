#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <iterator>
#include <vector>

namespace lfu
{
    template <typename T>
    struct node_t
    {
        T data;
        int hit_count;
        int key;

        node_t(T data_, int hit_, int key_) : data(data_), hit_count(hit_), key(key_){};
        ~node_t(){};
    };

    template <typename T, typename key_t, typename F>
    struct cache_t
    {
        using ListIt = typename std::list<node_t<T> *>::iterator;

    private:
        size_t sz_;
        std::list<node_t<T> *> cache_;
        std::unordered_map<key_t, ListIt> hashmap_;

        void move_node(ListIt node_it)
        {   
            int hit_curr = (*node_it)->hit_count;
            ListIt it = node_it;
            it++;
            for(node_it; it != cache_.end(); ++it)
            {

                if ((*it)->hit_count > hit_curr)
                {
                    cache_.splice(it, cache_, node_it);
                    //std::cout << "put: " << (*node_it)->key << " before: " << (*it)->key << std::endl;
                    return;
                }
            }

            cache_.splice(cache_.end(), cache_, node_it);
        }

        bool is_full() const
        {
            return (cache_.size() == sz_);
        }

    public:

        cache_t(size_t sz) : sz_(sz){};

        bool cache_request(int &key, F &slow_get_page)
        {
            auto search = hashmap_.find(key);

            if (search != hashmap_.end()) // found
            {
                ListIt node_it = search->second;

                (*node_it)->hit_count += 1;
                move_node(node_it);
                return true;
                
            }
            else // not found
            {
                if (is_full())
                {
                    node_t<T> *node = cache_.front();

                    cache_.pop_front();
                    hashmap_.erase(node->key);

                    delete node;
                }

                T data = slow_get_page(key);
                node_t<T> *node = new node_t<T>(data, 1, key);


                cache_.push_front(node);
                hashmap_[key] = cache_.begin();
                return false;
            }
        }

        void print_cache() const // only for int
        {
            auto it = cache_.begin();

            for(it; it != cache_.end(); it++)
            {
                std::cout << (*it)->key << " "; 
            }

            std::cout << std::endl;

            it = cache_.begin();

            for(it; it != cache_.end(); it++)
            {
                std::cout << (*it)->hit_count << " "; 
            }

            std::cout << std::endl;
        }
    };
}
