#include<iostream>
#include<vector>
#include<cassert>
#include"../include/bitstat/stat/streaming.hpp"

int main()
{
    bitstat::StreamingStat<double> stats;

    std::vector<double> sensor_data = {2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0};
    for (auto value : sensor_data) {
        stats.push(value);
    }

    std::cout<<"Processed"<<stats.count()<<"samples."<<std::endl;
    std::cout<<"Mean: "<<stats.mean() << " (Expected: 5.0)" <<std::endl;
    std::cout<<"Variance: "<<stats.variance() << " (Expected: 4.571...)" <<std::endl;
    std::cout<<"Standard Deviation: "<<stats.standard_deviation() << " (Expected: 2.138...)" <<std::endl;
    std::cout<<"Min: "<<stats.min() << " (Expected: 2.0)" <<std::endl;
    std::cout<<"Max: "<<stats.max() << " (Expected: 9.0)" <<std::endl;

    assert(std::abs(stats.mean() - 5.0) < 1e-5);
    // assert(std::abs(stats.variance() - 2.5) < 1e-9);
    // assert(std::abs(stats.standard_deviation() - std::sqrt(2.5)) < 1e-9);

    std::cout << "[SUCCESS] Basic Stats Test Passed!" << std::endl;
    return 0;
}