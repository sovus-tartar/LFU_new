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

    template <typename T, typename F> struct cache_t
    {
        using ListIt =  typename std::list<node_t<T>>::iterator;
        using VectIt = typename std::vector<node_T<T>>::iterator;

        size_t sz_;
        size_t requests_num;

        std::list<node_t<T>> cache_;
        std::unordered_map<T, ListIt> hashmap_cache;
        ListIt to_remove_node;

        std::vector<node_t<T>> requests;
        cache_t(size_t sz, size_t req): sz_(sz), requests_num(req)  {};

        

        void read_requests(F slow_get_page)    //only for numbers
        {
            std::unordered_map<T, VectIt> hashmap_;

            for(int i = 0; i < requests_num; ++i)
            {
                node_t<T> node;
                node.next_place = requests_num + 1;
                std::cin >> key;

                node.data = slow_get_page(key);

                auto it = hashmap_.find(node.data);
                
                if (it != hashmap_.end())
                    it->second->next_place = i;

                requests.push_back(node);
                hashmap_[node.data] = requests.end();
            }
        }

        void update_cache_state()
        {

        }

        int get_hits()
        {
            int hits = 0;

            for(int i = 0; i < requests_num; ++i)
            {
                auto it = hashmap_cache.find(requests[i].data);

                if (it != hashmap_cache.end())
                {
                    hits += 1;
                    it->second->next_place = requests[i].next_place;
                }
                else 
                {
                    if (is_full())
                    {
                        
                    }
                    else
                    {
                        if (requests[i].next_place != requests_num + 1)
                        {
                            cache_.push_back(requests[i]);
                            hashmap_cache[requests[i].key] = cache_.back();
                        }
                    }
                }


            }

            return hits;
        }

        bool is_full() const
        {
            return cache_.size() == sz_;
        }

        void print_cache() const // only for int
        {
            
        }

    };
}