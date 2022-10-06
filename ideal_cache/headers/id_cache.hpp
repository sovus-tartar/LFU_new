#include <list>
#include <queue>
#include <unordered_map>
#include <vector>
#include <map>

namespace id_cache
{

    template <typename T>
    struct node_t
    {
        int key;
        T data;
        int next_place;
    };

    template <typename T>
    bool is_equal(const node_t<T> &a, const node_t<T> &b)
    {
        return a.data == b.data;
    }

    template <typename T, typename F>
    struct cache_t
    {
        using ListIt = typename std::list<node_t<T>>::iterator;
        using MapIt = typename std::multimap<int, node_t<T>>::iterator;

        size_t sz_;

        size_t requests_num;
        std::multimap<int, node_t<T>> cache_;
        std::unordered_map<int, MapIt> hashmap_cache;

        std::list<node_t<T>> requests;

        cache_t(size_t sz, size_t req, F slow_get_page) : sz_(sz), requests_num(req)
        {
            read_requests(slow_get_page);
        };

        void read_requests(F slow_get_page) // only for numbers
        {
            std::unordered_map<int, ListIt> hashmap_;

            for (int i = 0; i < requests_num; ++i)
            {
                int key;
                node_t<T> node;
                node.next_place = requests_num + 1;
                std::cin >> key;

                node.key = key;
                node.data = slow_get_page(key);

                auto it = hashmap_.find(node.key);

                if (it != hashmap_.end())
                    it->second->next_place = i;

                requests.push_back(node);

                auto last = requests.end();
                std::advance(last, -1);
                hashmap_.insert_or_assign(key, last);
            }
        }

        void cache_pop_far()
        {
            hashmap_cache.erase(cache_.rbegin()->second.key);
            MapIt temp = cache_.end();
            std::advance(temp, -1);
            cache_.erase(temp);
        }

        void cache_pop_near()
        {
            hashmap_cache.erase(cache_.begin()->second.key);
            cache_.erase(cache_.begin());
        }

        bool if_insert(node_t<T> &node)
        {

            if ((node.next_place) > (std::prev(cache_.end())->second.next_place))
                return false;

            return true;
        }

        void cache_insert(node_t<T> &node)
        {
            MapIt temp = cache_.insert({node.next_place, node});
            hashmap_cache[node.key] = temp;
        }

        int get_hits()
        {
            int hits = 0;

            for (auto it = requests.begin(); it != requests.end(); ++it)
            {

                auto found = hashmap_cache.find(it->key);
                if (found != hashmap_cache.end())
                {
                    hits += 1;
                    cache_pop_near();
                    cache_insert(*it);
                }
                else
                {
                    if (!is_full())
                    {
                        cache_insert(*it);
                    }
                    else if (if_insert(*it))
                    {
                        cache_pop_far();
                        cache_insert(*it);
                    }
                }


            }

            return hits;
        }

        bool is_full() const
        {
            return hashmap_cache.size() == sz_;
        }

        void print_cache() const // only for int
        {
            std::cout << "Cache dump started---------------------------" << std::endl;
            for (auto it = cache_.begin(); it != cache_.end(); ++it)
            {
                std::cout << "{ " << it->second.key << ", " << it->first << "}"
                          << ", ";
            }

            std::cout << std::endl
                      << "Cache dump ended-----------------------------" << std::endl;
        }
    };
}