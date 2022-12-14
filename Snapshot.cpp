#include "Snapshot.hpp"

Snapshot::Snapshot(int width, int height)
    :mWidth(width), mHeight(height), mPathToFile("render"+std::to_string(width)+"x"+std::to_string(height)+"px.ppm")
{
   mPixels = new Color*[mHeight];
   for(int i = 0;i<mHeight;i++)
       mPixels[i] = new Color[mWidth];
}

Snapshot::Snapshot(const Snapshot &other)
    :Snapshot(other.mWidth, other.mHeight)
{

}

Snapshot::~Snapshot()
{
    if(!mWritten){
        mPathToFile = "autosave_"+mPathToFile;
        writeToImage();
    }
    for(int i=0;i<mHeight;i++)
        delete[] mPixels[i];
    delete[] mPixels;
    mPixels = nullptr;
}

void Snapshot::clear(Color clearColor)
{
    for(int i=mHeight-1;i>=0;i--){
        for(int j=0;j<mWidth;j++){
            mPixels[i][j] = clearColor;
        }
    }
}

void Snapshot::putPixel(int x, int y, Color color)
{
   mPixels[y][x] = Color(
               std::sqrt(color.x),
               std::sqrt(color.y),
               std::sqrt(color.z)
               );
}

Vec3 Snapshot::getPixel(int i, int j)
{
    return mPixels[i][j];
}

Vec3 **Snapshot::getPixelData()
{
    return mPixels;
}

void Snapshot::writeToImage()
{
    std::ofstream file;
    file.open(mPathToFile);
    file << "P3\n" << mWidth <<' '<< mHeight<<"\n255\n";
    for(int i=mHeight-1;i>=0;i--){
        for(int j=0;j<mWidth;j++){
            auto r = mPixels[i][j].x;
            auto g = mPixels[i][j].y;
            auto b = mPixels[i][j].z;

            file<<static_cast<int>(256*clamp(r, 0.0, 0.999))<<' '
                <<static_cast<int>(256*clamp(g, 0.0, 0.999))<<' '
                <<static_cast<int>(256*clamp(b, 0.0, 0.999))<<' '<<std::endl;
        }
    }
    file.close();
    mWritten = true;
}

int Snapshot::getWidth() const
{
    return mWidth;
}

int Snapshot::getHeight() const
{
    return mHeight;
}
