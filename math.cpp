#include <random>
#include "math.h"

int get_random(int inferior, int superior){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(inferior, superior); // define the range
    return distr(eng);
}
