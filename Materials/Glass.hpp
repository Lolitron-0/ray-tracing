#ifndef GLASS_HPP
#define GLASS_HPP
#include "Material.hpp"
#include "Ray.hpp"

class Glass : public Material
{
public:
    Glass(float refractionIndex);

    bool scatter(const Ray &r, const Hit &rec, Color &attenuation, Ray &scattered) const override;
private:
    float mRefractionIndex;

    static float reflectance(float cosine, float refIdx);
};

#endif // GLASS_HPP
