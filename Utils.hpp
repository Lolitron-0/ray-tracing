#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include "Vec3.hpp"
#include "Assertions.hpp"


//Constants
const float infinity = std::numeric_limits<float>::infinity();
const float pi = M_PI;

//Utility functions
inline float degToRad(float deg)
{
    return deg * pi/180.;
}

inline float clamp(float val, float lower, float upper)
{
    if(val>upper) return upper;
    if(val<lower) return lower;
    return val;
}

inline float randomFloat()
{
    return rand()/(RAND_MAX+1.);
}

inline float randomFloat(float min, float max)
{
    rtAssert(min<=max, "randomInRange: min>max");
    return min + (max-min)*randomFloat();
}

#endif // UTILS_HPP
