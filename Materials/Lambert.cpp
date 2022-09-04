#include "Lambert.hpp"
#include "Hit.hpp"

bool Lambert::scatter(const Ray &r, const Hit &rec, Color &attenuation, Ray &scattered) const{
    auto scatterDirection = rec.unitNormal + randomUnit();

    if(scatterDirection.closeToZero())
        scatterDirection = rec.unitNormal;

    scattered = Ray(rec.p, scatterDirection);
    attenuation = albedo;
    return true;
}
