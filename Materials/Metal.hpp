#ifndef METAL_HPP
#define METAL_HPP
#include "Material.hpp"
#include "Vec3.hpp"

class Metal : public Material
{
public:
    Metal(Color albedo, float roughness);
    bool scatter(const Ray &r, const Hit &rec, Color &attenuation, Ray &scattered) const override;
private:
    Color albedo;
    float roughness;
};


#endif // METAL_HPP
