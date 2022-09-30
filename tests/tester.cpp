#include <gtest/gtest.h>
#include "../headers/LFU_cache.hpp"
#include <stdio.h>

FILE * test_file;

int slow_get_page(int key)
{
    return key;
}


int cache_test()
{
    int N;
    fscanf(test_file, "%d", &N);

    lfu::cache_t<int, int, int(int)> C(N);

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
        }
    }

    return hits;
}

TEST(unit_test, test1)
{
    test_file = fopen("../tests/111.in", "r");

    int got_hits = cache_test();
    int exp_hits = -1;
    fscanf(test_file, "%d", &exp_hits);

    fclose(test_file);

    EXPECT_EQ(got_hits, exp_hits);

}

TEST(unit_test, test2)
{
    test_file = fopen("../tests/222.in", "r");

    int got_hits = cache_test();
    int exp_hits = -1;
    fscanf(test_file, "%d", &exp_hits);

    fclose(test_file);

    EXPECT_EQ(got_hits, exp_hits);

}

TEST(unit_test, test3)
{
    test_file = fopen("../tests/333.in", "r");

    int got_hits = cache_test();
    int exp_hits = -1;
    fscanf(test_file, "%d", &exp_hits);

    fclose(test_file);

    EXPECT_EQ(got_hits, exp_hits);

}

TEST(unit_test, test4)
{
    test_file = fopen("../tests/444.in", "r");

    int got_hits = cache_test();
    int exp_hits = -1;
    fscanf(test_file, "%d", &exp_hits);

    fclose(test_file);

    EXPECT_EQ(got_hits, exp_hits);
}

TEST(unit_test, test5)
{
    test_file = fopen("../tests/555.in", "r");

    int got_hits = cache_test();
    int exp_hits = -1;
    fscanf(test_file, "%d", &exp_hits);

    fclose(test_file);

    EXPECT_EQ(got_hits, exp_hits);
}

TEST(unit_test, test6)
{
    test_file = fopen("../tests/666.in", "r");

    int got_hits = cache_test();
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