#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <iterator>
#include <vector>

namespace lfu
{
    template<typename T>
    struct order_node_t;

    template <typename T>
    struct node_t
    {
        typename std::list<order_node_t<T>>::iterator order_it;
        T data;
        int hit_count;
        int key;

    };

    template <typename T>
    struct order_node_t
    {
        int hit;
        typename std::list<node_t<T>> nodes;
    };
    

    template <typename T, typename key_t, typename F>
    struct cache_t
    {
        using ListIt = typename std::list<node_t<T>>::iterator;
        using OrderIt = typename std::list<order_node_t<T>>::iterator;

    private:
        size_t sz_;
        std::unordered_map<key_t, ListIt> hashmap_;
        std::list<order_node_t<T>> order_list;

        

        void move_node_up(ListIt& node_it)
        {   
            node_it->hit_count += 1;
            int hit = node_it->hit_count;
            
            OrderIt prev_ord = node_it->order_it;
            OrderIt next_ord = prev_ord;
            ++next_ord;

            if ((next_ord == order_list.end()) || (hit != next_ord->hit))
            {
                order_node_t<T> ord_node;
                ord_node.hit = hit;

                next_ord = order_list.insert(next_ord, ord_node);
            }

            node_it->order_it = next_ord;

            typename std::list<node_t<T>> &old_list = prev_ord->nodes, &new_list = next_ord->nodes;

            new_list.splice(new_list.begin(), old_list, node_it);

            if (old_list.empty())
            {
                order_list.erase(prev_ord);
            }

        }

        void pop_node()
        {
            OrderIt ord = order_list.begin();

            int key = ord->nodes.back().key;

            hashmap_.erase(key);

            ord->nodes.pop_back();
        }

        bool is_full() const
        {
            return (hashmap_.size() == sz_);
        }

        ListIt push_node(node_t<T> &node)
        {
            OrderIt ord = order_list.begin();

            if (ord->hit != 1)
            {
                order_node_t<T> ord_node;
                ord_node.hit = 1;

                ord = order_list.insert(ord, ord_node);
            }

            node.order_it = ord;
            node.hit_count = 1;
            ord->nodes.push_front(node);
            hashmap_[node.key] = ord->nodes.begin();

            return ord->nodes.begin();
        }

    public:

        cache_t(size_t sz) : sz_(sz) 
        {
            order_node_t<T> ord;
            ord.hit = 1;
            order_list.push_front(ord);
        };

        bool cache_request(int &key, F &slow_get_page)
        {
            auto search = hashmap_.find(key);

            if (search != hashmap_.end()) // found
            {
                ListIt node_it = search->second;
                move_node_up(node_it);
                return true;
                
            }
            else // not found
            {
                if (is_full())
                {
                    pop_node();
                }

                T data = slow_get_page(key);
                node_t<T> node;
                node.data = data;
                node.key = key;
                push_node(node);

                return false;
            }
        }

        void print_cache() const // only for int
        {
            auto it = order_list.begin();

            std::cout << "Start cache dump--------------" << std::endl;

            for(it; it != order_list.end(); ++it)
            {
                auto it_2 = it->nodes.begin();

                std::cout << "Hits " << it->hit << ": ";

                for(it_2; it_2 != it->nodes.end(); ++it_2)
                    std::cout << it_2->key << " ";

                std::cout << std::endl;
            }

            std::cout << std::endl << "End cache dump----------------" << std::endl;
        }
    };
}
