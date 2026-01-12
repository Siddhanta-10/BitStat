#ifndef BITSTAT_STAT_STREAMING_HPP
#define BITSTAT_STAT_STREAMING_HPP

#include <cmath>
#include <type_traits>
#include <stdexcept>

namespace bitstat{
    template<typename T> class StreamingStat {
        static_assert(std::is_floating_point<T>::value, "StramingStat requires a floating point type.");

        private:
            unsigned long long count_ = 0;
            T mean_ = 0;
            T m2_ = 0; // Sum of squares of differences from the current mean
            T min_ = std::numeric_limits<T>::max();
            T max_ = std::numeric_limits<T>::lowest();
        
        public:
            StreamingStat() = default;

            void push(T value) {
                count_++;

                if (value < min_) min_ = value;
                if (value > max_) max_ = value;

                T delta = value - mean_;
                mean_ += delta / static_cast<T>(count_);
                T delta2 = value - mean_;
                m2_ += delta * delta2;
                
            }   

            T mean() const {
                if (count_ == 0) throw std::runtime_error("No data points have been added.");
                return mean_;
            }

            T variance() const {
                if (count_ < 2) throw std::runtime_error("At least two data points are required to compute variance.");
                return m2_ / static_cast<T>(count_ - 1);
            }

            T standard_deviation() const {
                return std::sqrt(variance());
            }

            unsigned long long count() const {
                return count_;
            }

            T min() const {
                if (count_ == 0) throw std::runtime_error("No data points have been added.");
                return min_;
            }

            T max() const {
                if (count_ == 0) throw std::runtime_error("No data points have been added.");
                return max_;
            }

            void clean() {
                count_ = 0;
                mean_ = 0.0;
                m2_ = 0.0;
                min_ = std::numeric_limits<T>::max();
                max_ = std::numeric_limits<T>::lowest();
            }
    };
} // namespace bitstat

#endif // BITSTAT_STAT_STREAMING_HPP