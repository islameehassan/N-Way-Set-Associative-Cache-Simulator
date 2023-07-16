#include "../include/CacheSim.h"


CacheSim::CacheSim(uint8_t line_size, uint8_t num_of_ways) {
    this->line_size = line_size;
    this->num_of_ways = num_of_ways;
    this->num_of_sets = cache_size / (line_size * num_of_ways);
    cache = new Line [num_of_ways * num_of_sets];
}

bool CacheSim::Search(uint32_t address) {
    address = address / line_size;                              // Removed the offset bits
    uint16_t index = (address % num_of_sets) * num_of_ways;     // Extracted the index
    address = address / num_of_sets;                            // The only remaining bits are tag bits now

    // check all blocks of the set
    bool hit = false;
    int i = 0;
    for(; i < num_of_ways; ++i) {
        if(cache[index + i].valid) {
            if (cache[index + i].tag == (uint16_t) address) {
                hit = true;    // hit
                break;
            }
        }
        else{
            // invalid block
            cache[index + i].valid = true;
            cache[index + i].tag = (uint16_t) address;
            break;     // cold-start
        }
    }
    // all blocks have data ==> replace according to FIFO.
    if(i == num_of_ways) {
        // effectively popping the first block
        for(int j = index + 1; j < num_of_ways + index; ++j)
            cache[j - 1] = cache[j];
        cache[index + num_of_ways - 1].tag = address;   // effectively push back the new line
    }

    return hit;
}

CacheSim::~CacheSim() {
    delete[] cache;
}
