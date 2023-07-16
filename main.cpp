#include <iostream>
#include <fstream>
#include "include/CacheSim.h"

using std::cout;
using std::fstream;
using std::ofstream;
using std::ifstream;

#define		DBG				1
#define		DRAM_SIZE		(64*1024*1024)
#define		CACHE_SIZE		(64*1024)


/* The following implements a random number generator */
unsigned int m_w = 0xABABAB55;    /* must not be zero, nor 0x464fffff */
unsigned int m_z = 0x05080902;    /* must not be zero, nor 0x9068ffff */
unsigned int rand_()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}

unsigned int memGen1()
{
    static unsigned int addr=0;
    return (addr++)%(DRAM_SIZE);
}

unsigned int memGen2()
{
    static unsigned int addr=0;
    return  rand_()%(24*1024);
}

unsigned int memGen3()
{
    return rand_()%(DRAM_SIZE);
}

unsigned int memGen4()
{
    static unsigned int addr=0;
    return (addr++)%(4*1024);
}

unsigned int memGen5()
{
    static unsigned int addr=0;
    return (addr++)%(1024*64);
}

unsigned int memGen6()
{
    static unsigned int addr=0;
    return (addr+=32)%(64*4*1024);
}

int main() {
    srand(time(nullptr));

    ofstream results;
    results.open("results.csv");

    /********************Testing********************/
    double hit_ratio_Exp1[24];
    double hit_ratio_Exp2[30];

    // array of function pointers to the six generators
    unsigned int (*address_generators[])() = {memGen1, memGen2, memGen3, memGen4, memGen5, memGen6};

    // Test for different line sizes, holding number of ways constant at 4
    int index = 0;
    for(int line_size = 16; line_size <= 128; line_size *= 2) {
        for (auto & address_generator: address_generators) {
            CacheSim cache_sim(line_size, 4);  // cache object

            int hits = 0, i = 0;
            for(; i < 1000000; ++i){
                unsigned int mem_address = (*address_generator)();
                hits += (cache_sim.Search(mem_address) ? 1: 0);
            }
            hit_ratio_Exp1[index++] = hits/(i * 1.0);   // typecast to double
        }
    }

    results << "Experiment 1: \n";
    for(int i = 0; i < 4; i++){
        int line_size = 0;
        switch (i%6) {
            case 0:
                line_size = 16;
                break;
            case 1:
                line_size = 32;
                break;
            case 2:
                line_size = 64;
                break;
            case 3:
                line_size = 128;
                break;
            default:
                break;
        }
        results << line_size << ",";
        for(int j = 0; j < 6; j++){
            results << hit_ratio_Exp1[6*i + j] << (j == 5 ? "\n": ",");
        }
    }
    results << "End of Experiment 1\n";


    // Test for different number of ways, holding line size constant at 32
    index = 0;
    for (int num_of_ways = 1; num_of_ways <= 16; num_of_ways *= 2) {
        for (auto &address_generator: address_generators) {
            CacheSim cache_sim(32, num_of_ways);  // cache object

            int hits = 0, i = 0;
            for (; i < 1000000; ++i) {
                unsigned int mem_address = (*address_generator)();
                hits += (cache_sim.Search(mem_address) ? 1 : 0);
            }
            hit_ratio_Exp2[index++] = hits / (i * 1.0);   // typecast to double
        }
    }
    results << "Experiment 2: \n";
    for(int i = 0; i < 5; i++){
        int num_of_ways = 0;
        switch (i%6) {
            case 0:
                num_of_ways = 16;
                break;
            case 1:
                num_of_ways = 32;
                break;
            case 2:
                num_of_ways = 64;
                break;
            case 3:
                num_of_ways = 128;
                break;
            default:
                break;
        }
        results << num_of_ways << ",";
        for(int j = 0; j < 6; j++){
            results << hit_ratio_Exp2[6*i + j] << (j == 5 ? "\n": ",");
        }
    }
    results << "End of Experiment 2\n";
}
