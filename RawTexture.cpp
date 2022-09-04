#include "RawTexture.hpp"
#include <GLFW/glfw3.h>
#include "Assertions.hpp"

RawTexture::RawTexture(int w, int h)
        :mWidth(w), mHeight(h)
{
    mData = new float[w * h * 3];
    //for(int i=0;i<h;i++){
    //    for(int j=0;j<w;j++){
    //        mData[i*w*3 + j*3 ] = arrayOfPixels[i][j].x;
    //        mData[i*w*3 + j*3 + 1] = arrayOfPixels[i][j].y;
    //        mData[i*w*3 + j*3 + 2] = arrayOfPixels[i][j].z;
    //    }
    //}
    glGenTextures(1, &mHandle);
    glBindTexture(GL_TEXTURE_2D, mHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_FLOAT, mData);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void RawTexture::regenerateTexture(Vec3 **arrayOfPixels, int w, int h)
{
    rtAssert(w==mWidth && h==mHeight, "Invalid regenerateTexture matrix size");
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            mData[i*w*3 + j*3 ] = arrayOfPixels[i][j].x;
            mData[i*w*3 + j*3 + 1] = arrayOfPixels[i][j].y;
            mData[i*w*3 + j*3 + 2] = arrayOfPixels[i][j].z;
        }
    }

    glBindTexture(GL_TEXTURE_2D, mHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_FLOAT, mData);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int RawTexture::getHandle() const
{
    return mHandle;
}
