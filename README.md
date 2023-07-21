# N-Way-Set-Associative-Cache-Simulator
an n-way set associative cache simulator with FIFO
## Introduction:
<font size = "16">
The Cache Simulator Project is a C++ program designed to simulate the behavior of a simple cache system. Caches are essential components in modern computer architectures, used to improve memory access times by storing frequently accessed data closer to the processor. This project aims to provide a tool to analyze the cache performance under different configurations, line sizes, and associativity levels.

The simulator operates as a direct-mapped cache, where each memory address maps to a specific cache line based on the least significant bits of the address. It supports various cache line sizes and different numbers of ways (associativity) to explore their impact on cache hit rates and overall performance.

## Key Features:
<font size = "16">
  
1. Configurable Cache Parameters: The simulator allows users to specify the cache line size and the number of ways, enabling the evaluation of cache behavior under different setups.

2. Memory Address Generation: To thoroughly analyze the cache's efficiency, the project includes several memory address generation functions with distinct access patterns. These functions mimic real-world scenarios and aid in generating diverse workloads for cache testing.

3. Experimentation and Results: The project performs two main experiments. The first experiment examines cache performance for varying line sizes while keeping the number of ways constant. The second experiment investigates the impact of different associativity levels with a fixed line size. The resulting hit ratios are recorded and stored in a CSV file for further analysis.

## How to Use:
<font size = "16">
  
1. Clone the repository and compile the source code to generate the executable.

2. Run the main program, and the cache simulator will conduct the specified experiments automatically.

3. The results will be saved in a CSV file named "results.csv," which can be analyzed or visualized to gain insights into the cache's behavior.

##Requirements:
<font size = "16">

C++ compiler with C++11 support.


## CacheSim.h
<font size = "16">
  location include/CacheSim.h

The CacheSim.h file contains the header definition for the CacheSim class, which represents a simple cache simulator. It includes the necessary headers for handling data types (cstdint for integer types and iostream for input/output operations). The class defines a cache line structure (Line) to store individual cache line information, such as the tag and validity.

The CacheSim class has private member variables, including:

cache: A pointer to an array of cache lines that will store data.
line_size: An 8-bit unsigned integer representing the size of each cache line in bytes.
num_of_ways: An 8-bit unsigned integer representing the number of ways (associativity) in the cache.
num_of_sets: A 16-bit unsigned integer representing the number of cache sets in the cache.
The class provides the following public member functions:

CacheSim(uint8_t line_size, uint8_t num_of_ways): The constructor that initializes the cache with the given line size and number of ways.
bool Search(uint32_t address): A method to search for a given memory address in the cache. It returns true if the address is found in the cache (cache hit), and false otherwise (cache miss).
~CacheSim(): The destructor that releases the dynamically allocated memory used by the cache.
## CacheSim.cpp
<font size = "16">
location lib/CacheSim.cpp
  
The CacheSim.cpp file contains the implementation of the CacheSim class, which represents a simple cache simulator. The file includes the corresponding header file (CacheSim.h) and defines the member functions of the class.

The constructor CacheSim::CacheSim(uint8_t line_size, uint8_t num_of_ways) initializes the cache by calculating the number of cache sets based on the given line size and number of ways. It dynamically allocates memory for the cache array (Line* cache) with the required size.

The CacheSim::Search(uint32_t address) function is responsible for searching a given memory address in the cache. It calculates the cache line index and tag based on the line size and number of sets. The function then checks all blocks in the corresponding set to find a matching tag for the address. If a cache hit occurs, it returns true; otherwise, it handles cache misses by replacing invalid blocks (cold-start) or using FIFO replacement if all blocks have data.

The destructor CacheSim::~CacheSim() releases the dynamically allocated memory used by the cache array to prevent memory leaks.
## main.cpp
<font size = "16">
The main.cpp file contains the main function to run the cache simulation experiments and store the results in a CSV file named "results.csv." The program simulates cache access patterns for various line sizes and numbers of ways (associativity) using different memory address generation functions.

The file defines multiple memory address generation functions (e.g., memGen1, memGen2, etc.) to simulate different address patterns for testing the cache simulator.

In the main() function:

1. The file is opened to write the results.
2. The program initializes two arrays to store the hit ratios for each experiment (hit_ratio_Exp1 and hit_ratio_Exp2).
3. The program creates an array of function pointers that point to the different memory address generation functions.
4. The first experiment (Experiment 1) tests cache performance for different line sizes while holding the number of ways constant at 4. For each combination of line size and address generation function, the cache is tested by generating 1,000,000 memory addresses, and the hit ratio is calculated.
5. The results of Experiment 1 are written to the output file, indicating the line size, followed by the hit ratios for each address generation function.
6. The second experiment (Experiment 2) tests cache performance for different numbers of ways while holding the line size constant at 32. For each combination of 7. the number of ways and address generation function, the cache is tested similarly to Experiment 1, and the hit ratio is calculated.
8. The results of Experiment 2 are written to the output file, indicating the number of ways, followed by the hit ratios for each address generation function.
9. The program finishes, and the output file is closed.
    
## Contributions:
<font size = "16">
Contributions to this project are welcome. If you encounter any issues, discover bugs, or have ideas to enhance the simulator's functionality, feel free to submit pull requests or open issues on the GitHub repository.

Explore the Cache Simulator Project to gain valuable insights into cache performance, analyze various configurations, and refine cache designs for optimal efficiency in computer architectures. Happy caching!
