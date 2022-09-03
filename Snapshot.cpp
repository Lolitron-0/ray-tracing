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
            auto r = mPixels[i][j].x;
            auto g = mPixels[i][j].y;
            auto b = mPixels[i][j].z;

            r = std::sqrt(r);
            g = std::sqrt(g);
            b = std::sqrt(b);

            file<<static_cast<int>(256*clamp(r, 0.0, 0.999))<<' '
                <<static_cast<int>(256*clamp(g, 0.0, 0.999))<<' '
                <<static_cast<int>(256*clamp(b, 0.0, 0.999))<<' '<<std::endl;
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
