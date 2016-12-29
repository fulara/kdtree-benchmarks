#pragma once

#include <random>

class RandomGenerator
{
public:
    RandomGenerator(int seed = 0) : gen(seed){

    }

    double random_double(double min, double max) {
        std::uniform_real_distribution<> dis(min, max);

        return dis(gen);
    }

    int random_int(int min, int max) {
        std::uniform_int_distribution<> dis(min, max);

        return dis(gen);
    }

    void reseed(int seed = 0) {
        gen.seed(seed);
    }

private:
    std::mt19937 gen;
};