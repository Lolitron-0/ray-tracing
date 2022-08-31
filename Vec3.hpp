#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

class Vec3
{
public:
    Vec3() :x(0), y(0), z(0){}
    Vec3(float x, float y, float z)
        :x(x), y(y), z(z)
    {}

    Vec3 operator-() const { return Vec3(-x, -y, -z); }

    Vec3& operator+=(const Vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vec3& operator*=(const float& t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vec3& operator/=(const float& t){
        return *this *= 1/t;
    }


    Vec3& negate()
    {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    float dot(const Vec3& u) const
    {
        return x*u.x+
                y*u.y+
                z*u.z;
    }

    Vec3 cross(const Vec3& u) const
    {
        return Vec3(y*u.z - z*u.y,
                    z*u.x - x*u.z,
                    x*u.y - y*u.x
                    );
    }

    float length() const {
        return std::sqrt(lengthSquared());
    }

    float lengthSquared() const {
       return x*x + y*y+ z*z;
    }

public:
    float x;
    float y;
    float z;
};

using Color = Vec3;



inline std::ostream& operator<<(std::ostream& out, const Vec3& v){
    return out<<static_cast<int>(v.x)<<' '<<static_cast<int>(v.y)<<' '<<static_cast<int>(v.z);
}

inline Vec3 operator+(const Vec3& u, const Vec3& v){
    return Vec3(u.x+v.x, u.y+v.y, u.z+v.z);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v){
    return Vec3(u.x-v.x, u.y-v.y, u.z-v.z);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v){
    return Vec3(u.x*v.x, u.y*v.y, u.z*v.z);
}

inline Vec3 operator*(const Vec3& v, const float& t){
    return Vec3(v.x*t, v.y*t, v.z*t);
}

inline Vec3 operator*(const float& t, const Vec3& v){
    return Vec3(v.x*t, v.y*t, v.z*t);
}

inline Vec3 operator/(const Vec3& v, const float& t){
    return Vec3(v.x/t, v.y/t, v.z/t);
}


//normalizes vector to 0..1 with same direction
inline Vec3 unitVector(const Vec3& v)
{
    return v/v.length();
}

#endif // VEC3_HPP


