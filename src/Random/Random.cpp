#include "Random.h"

int Random::generate(int min, int max)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());

    std::uniform_int_distribution<> distribution(min, max);

    return distribution(generator);
}
