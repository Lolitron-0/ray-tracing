#ifndef RAWTEXTURE_HPP
#define RAWTEXTURE_HPP
#include "Vec3.hpp"

class RawTexture
{
public:
    RawTexture(int width, int height);

    void regenerateTexture(Vec3** arrayOfPixels, int w, int h);

    unsigned int getHandle() const;
private:
    unsigned int mHandle;
    int mWidth;
    int mHeight;
    float* mData;
};

#endif // RAWTEXTURE_HPP
