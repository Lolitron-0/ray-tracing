#include "Snapshot.hpp"

Snapshot::Snapshot(int width, int height, std::string path)
    :mWidth(width), mHeight(height), mPathToFile(path)
{
   mPixels = new Color*[mHeight];
   for(int i = 0;i<mHeight;i++)
       mPixels[i] = new Color[mWidth];
}

Snapshot::Snapshot(const Snapshot &other)
    :Snapshot(other.mWidth, other.mHeight, other.mPathToFile)
{

}

Snapshot::~Snapshot()
{
   for(int i=0;i<mHeight;i++)
       delete[] mPixels[i];
   delete[] mPixels;
   mPixels = nullptr;
}

void Snapshot::putPixel(int x, int y, Color color)
{
   mPixels[y][x] = color;
}

void Snapshot::writeToImage()
{
    std::ofstream file;
    file.open(mPathToFile);
    file << "P3\n" << mWidth <<' '<< mHeight<<"\n255\n";
    for(int i=mHeight-1;i>0;i--){
        for(int j=0;j<mWidth;j++){
            file<<mPixels[i][j] * 255.999<<std::endl;
        }
    }
    file.close();
}

int Snapshot::getWidth() const
{
    return mWidth;
}

int Snapshot::getHeight() const
{
    return mHeight;
}
