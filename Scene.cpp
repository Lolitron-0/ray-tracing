#include "Scene.hpp"
#include "Hit.hpp"


Scene::Scene()
{

}

bool Scene::hit(const Ray &r, float tMin, float tMax, Hit &rec) const
{
    Hit tempRec;
    bool hitAnything = false;
    float closest = tMax;

    for(const auto& object : mObjects)
    {
        if(object->hit(r,tMin,closest,tempRec))
        {
            hitAnything = true;
            closest = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}

void Scene::addObject(std::shared_ptr<Hittable> newObject)
{
    mObjects.push_back(newObject);
}
