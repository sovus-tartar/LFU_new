#include <iostream>
#include "../headers/id_cache.hpp"

int slow_get_page(int key)
{
    return key;
}

int main()
{
    int sz, req;

    std::cin >> sz >> req;


    id_cache::cache_t<int, int(int)>  C(sz, req, slow_get_page);

    std::cout << C.get_hits() << std::endl;

    
}