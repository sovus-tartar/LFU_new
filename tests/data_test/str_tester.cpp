#include <iostream>
#include <gtest/gtest.h>
#include "../../headers/LFU_cache.hpp"
#include <stdio.h>

FILE * test_file;


struct page_t
{
    int key;
    char data[60];
};

page_t slow_get_page(int key)
{
    page_t temp;
    temp.key = key;
    fscanf(test_file, "%s\n", temp.data);
    return temp;
}

int cache_test(FILE * in)
{
    int N;
    fscanf(test_file, "%d", &N);

    lfu::cache_t<page_t, int, page_t(int)> C(N);

    int attempts;
    fscanf(test_file, "%d", &attempts);

    int hits = 0;

    for (int i = 0; i < attempts; i++)
    {
        int temp;
        fscanf(test_file, "%d", &temp);
        bool succ = C.cache_request(temp, slow_get_page);
        if (succ) {
            hits += 1;
            char data[60];
            fscanf(test_file, "%s ", data);
        }
    }

    return hits;
}

TEST(str_test, test1)
{
    test_file = fopen("../tests/data_test/111.in", "r");

    int got_hits = cache_test(test_file);
    int exp_hits = -1;
    fscanf(test_file, "%d", &exp_hits);

    fclose(test_file);

    EXPECT_EQ(got_hits, exp_hits);

}

int main(int argc, char * argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

