#include "Camera.hpp"

Camera::Camera(int width, float aspectRatio)
    :snapshot(width, width/aspectRatio)
{
    auto viewportHeight = 2.;
    auto viewportWidth = viewportHeight * aspectRatio;
    auto focalLength = 1.;

    mOrigin = Vec3(0,0,0);
    mHorizontal = Vec3(viewportWidth, 0, 0);
    mVertical = Vec3(0, viewportHeight, 0);
    mLowerLeft = mOrigin - mHorizontal/2 - mVertical/2 - Vec3(0,0,focalLength);
}

Ray Camera::getRay(float u, float v) const
{
    return Ray(mOrigin, mLowerLeft + mHorizontal*u + mVertical*v - mOrigin);
}


