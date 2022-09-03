#ifndef HITTABLE_H
#define HITTABLE_H
#include <memory>
#include "Ray.hpp"

class Material;
class Hit;


class Hittable
{
public:
    Hittable(std::shared_ptr<Material> material = nullptr) : mMaterial(material){}

    virtual bool hit(const Ray& r, float tMin, float tMax, Hit& rec) const = 0;
protected:
    std::shared_ptr<Material> mMaterial;
};

#endif // HITTABLE_H
