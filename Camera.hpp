#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Snapshot.hpp"

class Camera
{
public:
    Camera(Snapshot snapshot, float aspectRatio);

    Ray getRay(float u, float v) const;

    Snapshot snapshot;
private:
    Vec3 mOrigin;
    Vec3 mLowerLeft;
    Vec3 mHorizontal;
    Vec3 mVertical;
};

#endif // CAMERA_HPP
