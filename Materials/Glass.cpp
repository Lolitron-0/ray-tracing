#include "Glass.hpp"
#include "Colors.hpp"
#include "Hit.hpp"

Glass::Glass(float refractionIndex)
    :mRefractionIndex(refractionIndex)
{

}

bool Glass::scatter(const Ray &r, const Hit &rec, Color &attenuation, Ray &scattered) const
{
    attenuation = colors::white;
    float refractionRatio = rec.frontFace?(1.0/mRefractionIndex):mRefractionIndex;

    Vec3 unitDirection = unitVector(r.direction);
    float cosTheta = fmin(dot(-unitDirection, rec.unitNormal), 1.0);
    float sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0;
    Vec3 direction;

    if(cannotRefract || reflectance(cosTheta, refractionRatio) > randomFloat())
        direction = unitDirection.reflect(rec.unitNormal);
    else
        direction = unitDirection.refract(rec.unitNormal, refractionRatio);

    scattered = Ray(rec.p, direction);
    return true;
}

float Glass::reflectance(float cosine, float refIdx)
{
    auto r0 = (1-refIdx) / (1+refIdx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}
