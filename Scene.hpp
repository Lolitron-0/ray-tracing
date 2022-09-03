#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <memory>
#include "Hittable.hpp"



class Scene : public Hittable
{
public:
    Scene();

    bool hit(const Ray &r, float tMin, float tMax, Hit &rec) const override;

    void addObject(std::shared_ptr<Hittable> newObject);
private:
   std::vector<std::shared_ptr<Hittable>> mObjects;

};

#endif // SCENE_H
