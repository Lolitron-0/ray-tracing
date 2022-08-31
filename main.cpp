#include <iostream>
#include "Vec3.hpp"
#include "Utils.hpp"
#include "Ray.hpp"
#include "Colors.hpp"

Color rayColor(const Ray& r)
{
    Vec3 unitDirection = unitVector(r.direction);
    auto t = 0.5 * (unitDirection.y+1);
    return (1.-t)*colors::white + t*colors::lightBlue;
}


int main()
{
    const auto aspectRatio = 16./9.;
    const int imageWidth=1000;
    const int imageHeight=static_cast<int>(imageWidth/aspectRatio);

    auto viewportHeight = 2.;
    auto viewportWidth = viewportHeight * aspectRatio;
    auto focalLength = 1.;

    auto origin = Vec3(0,0,0);
    auto horizontal = Vec3(viewportWidth, 0, 0);
    auto vertical = Vec3(0, viewportHeight, 0);
    auto lowerLeft = origin - horizontal/2 - vertical/2 - Vec3(0,0,focalLength);

    std::cout<<"P3\n"<<imageWidth<<" "<<imageHeight<<"\n255\n";

    for(int j = imageHeight-1;j>=0;j--)
	{
        std::cerr<<"Lines remaining: "<<j<<std::endl;
        for(int i = 0; i<imageWidth;i++)
		{
            auto u = (float)i/(imageWidth-1);
            auto v = (float)j/(imageHeight-1);
            Ray r(origin, lowerLeft + u*horizontal + v*vertical - origin);

            Color pixelColor = rayColor(r);
            writeColor(std::cout, pixelColor);
		}
	}
	std::cerr<<"Done!"<<std::endl;
}
