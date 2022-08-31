#ifndef RAY_HPP
#define RAY_HPP

#include "Vec3.hpp"

class Ray
{
public:
    Ray(){}
    Ray(const Vec3& origin, const Vec3& direction)
        :origin(origin), direction(direction){}

    Vec3 at(float t) const {
        return origin + t*direction;
    }

public:
    Vec3 origin;
    Vec3 direction;
};

#endif // RAY_HPP
