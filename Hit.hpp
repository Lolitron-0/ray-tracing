#ifndef HIT_HPP
#define HIT_HPP
#include <memory>
#include "Ray.hpp"


class Material;

struct Hit
{
    Vec3 p;
    Vec3 unitNormal;
    float t;
    bool frontFace;
    std::shared_ptr<Material> material;

    //sets the proper unit normal and frontFace values
    //outwardNormal - normal always pointing away from back face
    void setFaceNormal(const Ray& r, const Vec3& outwardNormal)
    {
       frontFace = dot(r.direction, outwardNormal) < 0;
       unitNormal = (frontFace ? outwardNormal : -outwardNormal);
       unitNormal.normalize();
    }
};


#endif // HIT_HPP
