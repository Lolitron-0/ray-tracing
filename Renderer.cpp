#include "Renderer.hpp"
#include "Assertions.hpp"
#include "Colors.hpp"
#include "Utils.hpp"
#include "Timer.hpp"
#include "Material.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Hit.hpp"
#include <omp.h>

Renderer::Renderer()
    :mTargetSamplesPerPixel(100),
     mMaxDepth(50),
     mNumThreads(4)
{}

Color Renderer::getRayColor(const Ray &r, const Scene &scene, int currentDepth) const
{
    if(currentDepth > mMaxDepth)
        return colors::black;

    Hit rec;
    if(scene.hit(r, 0.01, infinity, rec)){
        Ray scattered;
        Color attenuation;
        if(rec.material->scatter(r, rec, attenuation, scattered))
            return attenuation * getRayColor(scattered, scene, currentDepth+1);
        return colors::black;
    }

    Vec3 unitDirection = unitVector(r.direction);
    rec.t = 0.5 * (unitDirection.y+1);
    return colors::white*(1.-rec.t) + colors::lightBlue*rec.t;
}

void Renderer::render(const Scene &scene, Camera &camera)
{
    omp_set_num_threads(mNumThreads);

    mShouldInterrupt = false;
    for(mCurrentSamplesPerPixel = mDynamicAntialiasing?1:mTargetSamplesPerPixel;
        /*and target condition below*/!mShouldInterrupt;
        mCurrentSamplesPerPixel = clamp(mCurrentSamplesPerPixel+std::ceil(mTargetSamplesPerPixel/3.), 0, mTargetSamplesPerPixel))//dynamic render loop
    {
        mLinesRemaining = camera.snapshot.getHeight();
        Timer timer;
#pragma omp parallel for shared(camera)
        for(int j = camera.snapshot.getHeight()-1; j>=0;j--)
        {
            for(int i=0;i<camera.snapshot.getWidth();i++)
            {
                Color pixelColor = colors::black;
                for(int k=0;k< mCurrentSamplesPerPixel;k++) //antialiasing loop
                {
                    auto u = (i+randomFloat())/(camera.snapshot.getWidth()-1);
                    auto v = (j+randomFloat())/(camera.snapshot.getHeight()-1);
                    Ray r = camera.getRay(u, v);
                    pixelColor += getRayColor(r, scene, 0);
                }
                camera.snapshot.putPixel(i,j,pixelColor/ mCurrentSamplesPerPixel);
            }

            if(mShouldInterrupt){
#pragma omp cancel for
            }
            mLinesRemaining--;
        }

        mLinesRemaining = 0; //doing it implicitly so cancelled threads don't go below zero
        std::cout<<"Iteration done in "<<timer.elapsedMs()/1000.<<" sec!"<<std::endl;

        if(mCurrentSamplesPerPixel>=mTargetSamplesPerPixel) break; //here it is
    }
}

void Renderer::askInterrupt()
{
    mShouldInterrupt = true;
}

void Renderer::setAntialiasingStrength(int strength)
{
    rtAssert(strength>=1, "Antialiasing must be >=0");
    mTargetSamplesPerPixel = strength;
}

int Renderer::getCurrentAntialiasingStrength() const
{
    return mCurrentSamplesPerPixel;
}

int Renderer::getTargetAntialiasingStrength() const
{
    return mTargetSamplesPerPixel;
}

void Renderer::setMaxShadowDepth(int depth)
{
    rtAssert(depth>=1,"Shadow depth must be >=1");
    mMaxDepth = depth;
}

void Renderer::setNumThreads(int threads)
{
    rtAssert(threads>0, "Number of threads must be positive");
    mNumThreads = threads;
}

int Renderer::getLinesRemaining() const
{
    return mLinesRemaining;
}

int Renderer::getNumThreads() const
{
    return mNumThreads;
}

void Renderer::setDynamicAntialiasing(bool val)
{
    mDynamicAntialiasing = val;
}

bool Renderer::getDynamicAntialiasing() const
{
    return mDynamicAntialiasing;
}
