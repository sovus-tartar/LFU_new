# LFU cache on C++

## Brief

The program takes the cache size and the number of requests from stdin and prints the number of hits to stdout

## Tests

Tests are in the tests folder. Use '-t' flag and < to enter them to the program.

        ./lfu -t < 111.in

### Tests format: cache_size attemts_number values... expected_hits

 Tests generator is also included. It asks for cache size, attempts number and range(max number). The results outputs to stdout in correct format

        ./python3 ./tests/test_gen.py
        10
        100
        30

## Ideal cache

 Ideal cache is also included. To use input test files from tests folder: it will print comparison results.

    ./id_cache < ./tests/555.in

## Compilation

To compile CMake and g++ are needed. To create makefile run:

                cmake --make

To make:

                make






