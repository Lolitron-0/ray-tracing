#include "Metal.hpp"
#include "Hit.hpp"


Metal::Metal(Color albedo, float roughness)
    :albedo(albedo), roughness(roughness<=1 ? roughness : 1)
{}

bool Metal::scatter(const Ray &r, const Hit &rec, Color &attenuation, Ray &scattered) const
{
    auto reflected = r.direction.reflect(rec.unitNormal);
    scattered = Ray(rec.p, reflected + randomInUnitSphere()*roughness);
    attenuation = albedo;
    return dot(scattered.direction, rec.unitNormal) > 0;
}
