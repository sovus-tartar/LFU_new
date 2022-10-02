#include <gtest/gtest.h>
#include "../headers/LFU_cache.hpp"
#include <fstream>

int slow_get_page(int key)
{
    return key;
}


int cache_test(std::ifstream &strm)
{
    int N;
    strm >> N;

    lfu::cache_t<int, int, int(int)> C(N);

    int attempts;
    strm >> attempts;

    int hits = 0;

    for (int i = 0; i < attempts; i++)
    {
        int temp;
        strm >> temp;
        bool succ = C.cache_request(temp, slow_get_page);
        if (succ) {
            hits += 1;
        }
    }

    return hits;
}

TEST(unit_test, test1)
{
    std::ifstream istrm("../tests/111.in", std::ios::binary);

    int got_hits = cache_test(istrm);
    int exp_hits = -1;
    istrm >> exp_hits;

    istrm.close();

    EXPECT_EQ(got_hits, exp_hits);

}

TEST(unit_test, test2)
{
    std::ifstream istrm("../tests/222.in", std::ios::binary);

    int got_hits = cache_test(istrm);
    int exp_hits = -1;
    istrm >> exp_hits;

    istrm.close();

    EXPECT_EQ(got_hits, exp_hits);

}

TEST(unit_test, test3)
{
    std::ifstream istrm("../tests/333.in", std::ios::binary);

    int got_hits = cache_test(istrm);
    int exp_hits = -1;
    istrm >> exp_hits;

    istrm.close();

    EXPECT_EQ(got_hits, exp_hits);

}

TEST(unit_test, test4)
{
    std::ifstream istrm("../tests/444.in", std::ios::binary);

    int got_hits = cache_test(istrm);
    int exp_hits = -1;
    istrm >> exp_hits;

    istrm.close();

    EXPECT_EQ(got_hits, exp_hits);
}

TEST(unit_test, test5)
{
    std::ifstream istrm("../tests/555.in", std::ios::binary);

    int got_hits = cache_test(istrm);
    int exp_hits = -1;
    istrm >> exp_hits;

    istrm.close();

    EXPECT_EQ(got_hits, exp_hits);
}

TEST(unit_test, test6)
{
    std::ifstream istrm("../tests/666.in", std::ios::binary);

    int got_hits = cache_test(istrm);
    int exp_hits = -1;
    istrm >> exp_hits;

    istrm.close();

    EXPECT_EQ(got_hits, exp_hits);

}

int main(int argc, char * argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}