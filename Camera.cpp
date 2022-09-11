#include "Camera.hpp"

Camera::Camera(int width, float aspectRatio, float vFov, float aperture, float focalDistance)
    :snapshot(width, width/aspectRatio),
      u(Vec3(1, 0, 0)),
      v(Vec3(0, 1, 0)),
      w(Vec3(0, 0, 1)),
      mLookAt(0,0,-1),
      mLensRadius(aperture/2),
      mFocusDistance(focalDistance),
      mAspectRatio(aspectRatio)
{
    mViewportHeight = std::tan(degToRad(vFov)/2.) * 2;

    auto viewportWidth = mViewportHeight * aspectRatio;

    mOrigin = Vec3(0,0,0);
    mHorizontal =  u * mFocusDistance * viewportWidth;
    mVertical = v * mFocusDistance * mViewportHeight;
    mLowerLeft = mOrigin - mHorizontal/2 - mVertical/2 - w*mFocusDistance;
}

void Camera::lookAt(const Vec3 &pos)
{
    mLookAt = pos;
    w = unitVector(mOrigin - pos);
    u = unitVector(cross(Vec3(0, 1 ,0), w));
    v = cross(w, u);
    mHorizontal =  u * mFocusDistance * mViewportHeight*mAspectRatio;
    mVertical = v * mFocusDistance * mViewportHeight;
    mLowerLeft = mOrigin - mHorizontal/2 - mVertical/2 - w*mFocusDistance;
}

void Camera::lookFrom(const Vec3 &pos)
{
    mOrigin = pos;
    lookAt(mLookAt);
}

Ray Camera::getRay(float s, float t) const
{
    Vec3 offset = randomInUnitDisk() * mLensRadius;
    offset = u * offset.x + v * offset.y;
    //auto hor= (s-snapshot.getWidth() *0.5f)/mResolution;
    //auto ver= (snapshot.getHeight()*0.5f - t)/mResolution;
    //return Ray(mOrigin+offset, u*hor + v*ver - w - offset / mFocusDistance);
    return Ray(mOrigin+offset, mLowerLeft + mHorizontal*s + mVertical*t - mOrigin - offset);
}


