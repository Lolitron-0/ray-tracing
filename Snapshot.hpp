#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include "Vec3.hpp"
#include "Colors.hpp"
#include <iostream>
#include <fstream>


class Snapshot
{
public:
    Snapshot(int width, int height);
    Snapshot(const Snapshot&);
    ~Snapshot();

    void clear(Color clearColor = colors::black);
    void putPixel(int x, int y, Color color);
    Vec3 getPixel(int i, int j);
    Vec3** getPixelData();

    void writeToImage();

    int getWidth() const;
    int getHeight() const;

private:
    int mWidth;
    int mHeight;
    bool mWritten{false};
    std::string mPathToFile;
    Color** mPixels;
};

#endif // SNAPSHOT_H
