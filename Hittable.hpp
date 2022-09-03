#ifndef HITTABLE_H
#define HITTABLE_H
#include "Ray.hpp"

struct Hit
{
    Vec3 p;
    Vec3 unitNormal;
    float t;
    bool frontFace;

    //sets the proper unit normal and frontFace values
    //outwardNormal - normal always pointing out of back face
    void setFaceNormal(const Ray& r, const Vec3& outwardNormal)
    {
       frontFace = dot(r.direction, outwardNormal) < 0;
       unitNormal = frontFace ? unitVector(outwardNormal) : unitVector(-outwardNormal);
    }
};

class Hittable
{
public:
    virtual bool hit(const Ray& r, float tMin, float tMax, Hit& rec) const = 0;

};

#endif // HITTABLE_H
