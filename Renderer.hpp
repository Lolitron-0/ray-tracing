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

    //1 for no antialiasing up to infinity (default 100)
    void setAntialiasingStrength(int strength);
    int getAntialiasingStrength() const;
    //how many times can ray bounce (default 50)
    void setMaxShadowDepth(int depth);
    //set num threads to render (default - 4)
    void setNumThreads(int threads);
    int getNumThreads() const;

    int getLinesRemaining() const;
private:
    int mSamplesPerPixel;
    int mMaxDepth;
    int mNumThreads;

    int mLinesRemaining;
};

#endif // RENDERER_HPP
