#ifndef PROJECT2_CACHESIM_H
#define PROJECT2_CACHESIM_H
#include <cstdint>
#include <iostream>
using std::cout;

struct Line{
    // uint8_t* words; // array of half words to store data
    uint16_t tag;
    bool valid = false; // all lines are invalid (cold-start)
};

// cache size is fixed
constexpr unsigned int cache_size =  16384; // 16 * 1024 bytes

class CacheSim{
    Line * cache;

    uint8_t  line_size;
    uint8_t  num_of_ways;
    uint16_t num_of_sets;

public:
    // constructor to initialize with a line_size and a number of ways
    CacheSim(uint8_t line_size , uint8_t num_of_ways);
    // search for a given memory address if it exists in the cache
    bool Search(uint32_t address);

    ~CacheSim();
};

#endif //PROJECT2_CACHESIM_H
