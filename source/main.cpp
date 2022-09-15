#include <iostream>
#include <cstring>
#include "../headers/LFU_cache.hpp"

int slow_get_page(int key)
{
    return key;
}

int main(int argc, char *argv[])
{
    int N;
    std::cin >> N;

    caches::cache_t<int, int, int(int)> C(N);

    int attempts;
    std::cin >> attempts;

    int hits = 0;

    for (int i = 0; i < attempts; i++)
    {
        int temp;
        std::cin >> temp;

        bool succ = C.cache_request(temp, slow_get_page);
        if (succ)
            hits++;
    }

    if ((argc > 1) && (!std::strcmp(argv[1], "-t")))
    {
        int expected_hit = 0;

        std::cin >> expected_hit;
        std::cout << hits << std::endl;

        if (expected_hit == hits)
            std::cout << "Tests passed" << std::endl;
        else
            std::cout << "Tests not passed, expected hit: " << expected_hit << " received: " << hits << std::endl;
    } 
    else if (argc == 1)
        std::cout << hits;
    else
        std::cout << "Unknown argument: \"" << argv[2] << "\", exiting...\n";
        exit(-1);
    
    return 0;
}