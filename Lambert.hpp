#ifndef LAMBERT_HPP
#define LAMBERT_HPP

#include "Vec3.hpp"
#include "Material.hpp"


class Lambert : public Material
{
public:
    Lambert(const Color& a):albedo(a){}

    bool scatter(const Ray &r, const Hit &rec, Color &attenuation, Ray &scattered) const override;

private:
    Color albedo;
};

#endif // LAMBERT_HPP
