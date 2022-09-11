#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <memory>
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Snapshot.hpp"

class Camera
{
public:
    Camera(int width, float aspectRatio, float vFov, float aperture, float focalDistance);

    void lookAt(const Vec3& pos);
    void lookFrom(const Vec3& pos);

    Ray getRay(float u, float v) const;

    Snapshot snapshot;
private:
    Vec3 mOrigin;
    Vec3 mLookAt;
    Vec3 mLowerLeft;
    Vec3 mHorizontal;
    Vec3 mVertical;
    Vec3 u, v, w; //local basis
    float mLensRadius; //aperture/2
    float mFocusDistance;
    float mResolution;
    float mViewportHeight;
    float mAspectRatio;
};

#endif // CAMERA_HPP
