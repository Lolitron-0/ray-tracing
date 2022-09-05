#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "Ray.hpp"


class Scene;
class Camera;

class Renderer
{
public:
    Renderer();

    Color getRayColor(const Ray& r, const Scene& scene, int currentDepth) const;
    void render(const Scene& scene, Camera& camera);
    void askInterrupt();

    //1 for no antialiasing up to infinity (default 100)
    void setAntialiasingStrength(int strength);
    int getTargetAntialiasingStrength() const;
    int getCurrentAntialiasingStrength() const;
    //how many times can ray bounce (default 50)
    void setMaxShadowDepth(int depth);
    //set num threads to render (default - 4)
    void setNumThreads(int threads);
    int getNumThreads() const;
    //if true the render function will adjust antialiasing and re-render to
    //achieve fast results and render with target antialiasing then
    void setDynamicAntialiasing(bool val);
    bool getDynamicAntialiasing() const;

    int getLinesRemaining() const;
private:
    int mTargetSamplesPerPixel;
    int mCurrentSamplesPerPixel;
    int mMaxDepth;
    int mNumThreads;
    bool mDynamicAntialiasing{false};

    int mLinesRemaining;
    bool mShouldInterrupt{false};
};

#endif // RENDERER_HPP
