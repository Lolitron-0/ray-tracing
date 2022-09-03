#include <iostream>
#include "AllHeader.hpp"


int main()
{
    srand(time(0));

    const auto aspectRatio = 16./9.;
    const int imageWidth=1000;
    const int imageHeight=static_cast<int>(imageWidth/aspectRatio);

    Camera camera(Snapshot(imageWidth, imageHeight, "image.ppm"),aspectRatio);

    Scene scene;
    scene.addObject(std::make_shared<Sphere>(Vec3(0,-100.5,-1),100));
    scene.addObject(std::make_shared<Sphere>(Vec3(0,0,-1),0.5));

    Renderer renderer;

    renderer.render(scene, camera);

}
