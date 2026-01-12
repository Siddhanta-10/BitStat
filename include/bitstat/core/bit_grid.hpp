#ifndef BITSTAT_CORE_BIT_GRID_HPP
#define BITSTAT_CORE_BIT_GRID_HPP

#include <vector>
#include <cstdint>
#include <stdexcept>

namespace bitstat{

    /**
     * @brief A memory-efficient grid that stores binary states (0/1) using single bits.
     * Ideal for Occupancy Grids in robotics.
     */
    class BitGrid {
        private:
            std::vector<uint8_t> data_;
            size_t width_;
            size_t height_;

        public:
            BitGrid(size_t width, size_t height) : width_(width), height_(height) {
                //Calculate total bits needed
                size_t total_bits = width * height;
                // Calculate bytes needed (round up division by 8)
                // formula: (N + 7) / 8 is integer math for ceil(N/8)
                size_t total_bytes = (total_bits + 7) / 8;

                // Initialize with 0s (Unknown/Free space)
                data_.resize(total_bytes, 0); // Initialize all bits to 0
            }

            void set(size_t x, size_t y, bool value) {
                if (x >= width_ || y >= height_) {
                    throw std::out_of_range("Grid index out of bounds");
                }
                size_t linear_index = y * width_ + x;
                size_t byte_index = linear_index / 8;
                size_t bit_index = linear_index % 8;

                if (value) {
                    // Set bit to 1: OR with (1 shifted left by bit_index)
                    data_[byte_index] |= (1 << bit_index);
                } else {
                    // Set bit to 0: AND with NOT (1 shifted left by bit_index)
                    // Example: ~(00100) -> 11011. ANDing preserves other bits, kills the target.
                    data_[byte_index] &= ~(1 << bit_index); // Set bit to 0
                }
            }

            // Get the status of a cell
            bool get(size_t x, size_t y) const {
                if (x >= width_ || y >= height_) throw std::out_of_range("Grid index out of bounds");

                size_t linear_index = y * width_ + x;
                size_t byte_index = linear_index / 8;
                size_t bit_index  = linear_index % 8;

                // Check if bit is set
                return (data_[byte_index] & (1 << bit_index)) != 0;
            }

            // Fast clear (memset is highly optimized by OS)
            void clear() {
                std::fill(data_.begin(), data_.end(), 0);
            }

            size_t width() const { return width_; }
            size_t height() const { return height_; }
            
            // Debug: How much memory are we actually using?
            size_t memory_usage_bytes() const { return data_.size(); }
        };
}

#endif // BITSTAT_CORE_BIT_GRID_HPP