# tests/CMakeLists.txt

# 1. Statistics Test
add_executable(test_stats test_stats.cpp)
target_link_libraries(test_stats PRIVATE BitStat)
# TELL CTEST TO RUN THIS:
add_test(NAME TestStats COMMAND test_stats)

# 2. BitGrid Test
add_executable(test_bitgrid test_bitgrid.cpp)
target_link_libraries(test_bitgrid PRIVATE BitStat)
# TELL CTEST TO RUN THIS:
add_test(NAME TestBitGrid COMMAND test_bitgrid)

# 3. Benchmark (Optional: benchmarks usually aren't run as pass/fail tests, but you can if you want)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/benchmark_gaussian.cpp")
    add_executable(benchmark_gaussian benchmark_gaussian.cpp)
    target_link_libraries(benchmark_gaussian PRIVATE BitStat)
endif()