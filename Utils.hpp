#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include "Vec3.hpp"

void writeColor(std::ostream& out, Color pixelColor)
{
    out<<(pixelColor*255.999)<<std::endl;
    //out << static_cast<int>(255.999 * pixelColor.x) << ' '
    //    << static_cast<int>(255.999 * pixelColor.y) << ' '
    //    << static_cast<int>(255.999 * pixelColor.z) << std::endl;
}

#endif // UTILS_HPP
