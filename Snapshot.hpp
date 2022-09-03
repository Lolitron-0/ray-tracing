#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include "Vec3.hpp"
#include <iostream>
#include <fstream>


class Snapshot
{
public:
    Snapshot(int width, int height, std::string path);
    Snapshot(const Snapshot&);
    ~Snapshot();

    void putPixel(int x, int y, Color color);

    void writeToImage();
    void gammaCorrect();

    int getWidth() const;
    int getHeight() const;

private:
    int mWidth;
    int mHeight;
    std::string mPathToFile;
    Color** mPixels;
};

#endif // SNAPSHOT_H