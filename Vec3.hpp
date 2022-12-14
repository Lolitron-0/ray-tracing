#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>
#include "Utils.hpp"


class Vec3
{
public:
    Vec3() :x(0), y(0), z(0){}
    Vec3(float x, float y, float z)
        :x(x), y(y), z(z)
    {}
    Vec3(float* coords)
        :x(coords[0]), y(coords[1]), z(coords[2])
    {}


    Vec3 operator+(const Vec3& v) const {
        return Vec3(x+v.x, y+v.y, z+v.z);
    }

    Vec3 operator+(float t) const {
        return Vec3(x+t, y+t, z+t);
    }

    Vec3 operator-(const Vec3& v) const {
        return Vec3(x-v.x, y-v.y, z-v.z);
    }

    Vec3 operator-(float t) const {
        return Vec3(x-t, y-t, z-t);
    }

    Vec3 operator*(const Vec3& v) const {
        return Vec3(x*v.x, y*v.y, z*v.z);
    }

    Vec3 operator*(float t) const {
        return Vec3(x*t, y*t, z*t);
    }

    Vec3 operator/(float t) const {
        return Vec3(x/t, y/t, z/t);
    }


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

    Vec3& operator*=(float t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vec3& operator/=(float t){
        return *this *= 1/t;
    }


    Vec3& negate()
    {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    //make a unit vector out of this
    void normalize()
    {
        (*this)*=(1/length());
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

    Vec3 reflect(const Vec3& normal) const{
        return *this - normal * dot(normal) * 2;
    }

    Vec3 refract(const Vec3& normal, float etaRatio) const {
        auto cosTheta = fmin((-*this).dot(normal), 1.0);
        Vec3 rOutPerp = ((*this)+normal*cosTheta) * etaRatio;
        Vec3 rOutPar = normal * -std::sqrt(fabs(1-rOutPerp.lengthSquared()));
        return rOutPerp + rOutPar;
    }

    float length() const {
        return std::sqrt(lengthSquared());
    }

    float lengthSquared() const {
       return x*x + y*y+ z*z;
    }

    bool closeToZero(){
        const auto eps = 1e-8;
        return (fabs(x)<eps) && (fabs(y)<eps) && (fabs(z)<eps);
    }

    inline static Vec3 random(){
        return Vec3(randomFloat(), randomFloat(), randomFloat());
    }

    inline static Vec3 random(float min, float max){
        return Vec3(randomFloat(min,max), randomFloat(min, max), randomFloat(min, max));
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

inline float dot(const Vec3& v, const Vec3& u)
{
    return v.x*u.x+
            v.y*u.y+
            v.z*u.z;
}

inline Vec3 cross(const Vec3& v, const Vec3& u)
{
    return Vec3(v.y*u.z - v.z*u.y,
                v.z*u.x - v.x*u.z,
                v.x*u.y - v.y*u.x
                );
}

//normalizes vector to 0..1 with same direction
inline Vec3 unitVector(const Vec3& v)
{
    return v/v.length();
}

inline Vec3 randomInUnitSphere(){
    while (1) {
        auto p = Vec3::random(-1,1);
        if(p.lengthSquared() >= 1) continue;
        return p;
    }
}

inline Vec3 randomUnit(){
    return unitVector(randomInUnitSphere());
}

inline Vec3 randomInUnitDisk() {
    while (true) {
        auto p = Vec3(randomFloat(-1,1), randomFloat(-1,1), 0);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}
#endif // VEC3_HPP


