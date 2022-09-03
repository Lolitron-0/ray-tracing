#include "Sphere.hpp"

Sphere::Sphere(Vec3 center, float radius)
    :mCenter(center), mRadius(radius)
{
}

bool Sphere::hit(const Ray &r, float tMin, float tMax, Hit &rec) const
{
    //t^2 * b*b + 2t * b(A-C) + (A-C)^2 -r^2 = 0
    Vec3 oc = r.origin - mCenter;
    auto a = r.direction.lengthSquared();
    auto halfB = dot(r.direction, oc);
    auto c = oc.lengthSquared() - mRadius*mRadius;
    auto discriminant = halfB*halfB - a*c;

    if(discriminant < 0) return false;
    auto sqrtd = std::sqrt(discriminant);

    auto t = (-halfB - sqrtd)/a;
    if(t<tMin || t>tMax)
    {
        t = (-halfB + sqrtd)/a;
        if(t<tMin || t>tMax)
            return false;
    }

    rec.t = t;
    rec.p = r.at(rec.t);
    rec.setFaceNormal(r, rec.p - mCenter);

    return true;
}
