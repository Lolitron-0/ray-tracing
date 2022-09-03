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
    void render(const Scene& scene, Camera& camera) const;

    //0 for no antialiasing up to infinity (default 100)
    void setAntialiasingStrength(int strength);
    //how many times can ray bounce (default 50)
    void setMaxShadowDepth(int depth);
private:
    int mSamplesPerPixel;
    int mMaxDepth;
};

#endif // RENDERER_HPP
