#include <iostream>
#include <cassert>
#include "../include/bitstat/core/bit_grid.hpp"

int main() {
    // Create a small 10x10 grid
    bitstat::BitGrid grid(10, 10);
    
    std::cout << "Grid Memory Usage: " << grid.memory_usage_bytes() << " bytes." << std::endl;
    // Expected: 100 bits -> 13 bytes.
    
    // Set an obstacle at (5, 5)
    grid.set(5, 5, true);
    
    // Set another at (0, 0)
    grid.set(0, 0, true);

    // Assertions
    assert(grid.get(5, 5) == true);
    assert(grid.get(0, 0) == true);
    assert(grid.get(5, 6) == false); // Should be empty
    
    // Test overwriting
    grid.set(5, 5, false);
    assert(grid.get(5, 5) == false);

    std::cout << "[SUCCESS] BitGrid Test Passed!" << std::endl;
    return 0;
}