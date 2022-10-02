#include <iostream>
#include <gtest/gtest.h>
#include "../../headers/LFU_cache.hpp"
#include <fstream>

std::ifstream instrm;


struct page_t
{
    int key;
    char data[60];
};

page_t slow_get_page(int key)
{
    page_t temp;
    temp.key = key;
    instrm >> temp.data;
    return temp;
}

int cache_test()
{
    int N;
    instrm >> N;

    lfu::cache_t<page_t, int, page_t(int)> C(N);

    int attempts;
    instrm >> attempts;

    int hits = 0;

    for (int i = 0; i < attempts; i++)
    {
        int temp;
        instrm >> temp;
        bool succ = C.cache_request(temp, slow_get_page);
        if (succ) {
            hits += 1;
            char data[60];
            instrm >> data;
        }
    }

    return hits;
}

TEST(str_test, test1)
{
    instrm.open("../tests/data_test/111.in");

    int got_hits = cache_test();
    int exp_hits = -1;
    instrm >> exp_hits;

    instrm.close();

    EXPECT_EQ(got_hits, exp_hits);

}

int main(int argc, char * argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

