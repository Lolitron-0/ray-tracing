#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "Vec3.hpp"

struct Hit;
class Ray;

class Material
{
public:

    virtual bool scatter(const Ray& r, const Hit& rec, Color& attenuation, Ray& scattered) const = 0;
};

#endif // MATERIAL_HPP
