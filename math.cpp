#include <random>
#include <ctime>

#include "math.h"

int get_random(int inferior, int superior){
    static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }

    return (inferior + (rand() % (int)(superior - inferior + 1)));
}
