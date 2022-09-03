#include "Renderer.hpp"
#include "Assertions.hpp"
#include "Colors.hpp"
#include "Utils.hpp"
#include "Timer.hpp"
#include <omp.h>

Renderer::Renderer()
    :mSamplesPerPixel(100), mMaxDepth(50)
{}

Color Renderer::getRayColor(const Ray &r, const Scene &scene, int currentDepth) const
{
    Hit rec;
    if(scene.hit(r, 0.001, infinity, rec)){
        return 0.5 * (rec.unitNormal + colors::white);
    }

    Vec3 unitDirection = unitVector(r.direction);
    rec.t = 0.5 * (unitDirection.y+1);
    return (1.-rec.t)*colors::white + rec.t*colors::lightBlue;
}

void Renderer::render(const Scene &scene, Camera &camera) const
{
    omp_set_num_threads(1);

    Timer timer;
#pragma omp parallel for shared(camera)
    for(int j = camera.snapshot.getHeight()-1; j>=0;j--)
    {
        std::cout<<"Lines remaining: "<<j<<std::endl;
        for(int i=0;i<camera.snapshot.getWidth();i++)
        {
            Color pixelColor = colors::black;
            for(int k=0;k<mSamplesPerPixel;k++)
            {
                auto u = (i+randomFloat())/(camera.snapshot.getWidth()-1);
                auto v = (j+randomFloat())/(camera.snapshot.getHeight()-1);
                Ray r = camera.getRay(u, v);
                pixelColor += getRayColor(r, scene, 0);
            }
            camera.snapshot.putPixel(i,j,pixelColor/mSamplesPerPixel);
        }
    }
    camera.snapshot.writeToImage();
    std::cout<<"Done in "<<timer.elapsedMs()/1000.<<" sec!"<<std::endl;
}

void Renderer::setAntialiasingStrength(int strength)
{
    rtAssert(strength>=0, "Antialiasing must be >=0");
    mSamplesPerPixel = strength+1; //+1 so 0 is i sample
}

void Renderer::setMaxShadowDepth(int depth)
{
    rtAssert(depth>=1,"Shadow depth must be >=1");
    mMaxDepth = depth;
}
