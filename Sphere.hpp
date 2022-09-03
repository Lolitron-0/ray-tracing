#ifndef SPHERE_H
#define SPHERE_H
#include "Hittable.hpp"

struct Hit;

class Sphere : public Hittable
{
public:
    Sphere(Vec3 center, float radius, std::shared_ptr<Material> m);

    bool hit(const Ray& r, float tMin, float tMax, Hit& rec) const override;
private:
    Vec3 mCenter;
    float mRadius;
};

#endif // SPHERE_H

