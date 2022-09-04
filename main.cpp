#include <iostream>
#include "AllHeader.hpp"
#include <thread>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

GLFWwindow* initGui(int w, int h)
{
   GLFWwindow* window;
   glfwInit();
   window = glfwCreateWindow(w, h, "Hello World", NULL, NULL);
   glfwMakeContextCurrent(window);
   glfwSetErrorCallback([](int errCode, const char* message){
      std::cerr<<message<<std::endl;
   });

   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init("#version 130");
   ImGui::StyleColorsDark();

   return window;
}

void onFrame()
{

}

Scene generateScene(int numObjects)
{
    Scene scene;

    scene.addObject(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100,
                                             std::make_shared<Lambert>(colors::grey)));

    for(int a=-numObjects/2;a<numObjects/2;a++){
        for(int b=-numObjects/2;b<numObjects/2;b++){
            Vec3 center(a+0.9*randomFloat(), 0.2, b+0.9*randomFloat());

            scene.addObject(std::make_shared<Sphere>(center, 0.2,
                                                     std::make_shared<Lambert>(Color::random()*Color::random())));
        }

    }

    return scene;

}


int main()
{
    const auto aspectRatio = 16./9.;
    const int imageWidth=1000;
    const int imageHeight=static_cast<int>(imageWidth/aspectRatio);

    GLFWwindow* window = initGui(imageWidth, imageHeight);

    Camera camera(imageWidth, aspectRatio);
    Scene scene = generateScene(0);
    scene.addObject(std::make_shared<Sphere>(Vec3(0,-100.5,-1),100,std::make_shared<Lambert>(Color(.5,.8,.5))));
    //scene.addObject(std::make_shared<Sphere>(Vec3(-1,0,-1),0.5,std::make_shared<Lambert>(Color::random()*Color::random())));
    //scene.addObject(std::make_shared<Sphere>(Vec3(1,0,-1),0.5,std::make_shared<Lambert>(Color::random()*Color::random())));
    scene.addObject(std::make_shared<Sphere>(Vec3(-0.5,0,-1),0.5,
                                             std::make_shared<Metal>(Color::random()*Color::random(),0.5)));
    scene.addObject(std::make_shared<Sphere>(Vec3(0.5,0,-1),0.5,
                                             std::make_shared<Metal>(Color::random()*Color::random(), 0.1)));

    Renderer renderer;
    renderer.setAntialiasingStrength(50);

    std::thread th([&renderer, scene, &camera](){
        int i=1;
        renderer.setAntialiasingStrength(i);
        renderer.render(scene, camera);

        i = 10;
        renderer.setAntialiasingStrength(i);
        renderer.render(scene, camera);

        i = 30;
        renderer.setAntialiasingStrength(i);
        renderer.render(scene, camera);
    });

    RawTexture texture(camera.snapshot.getWidth(), camera.snapshot.getHeight());
    texture.regenerateTexture(camera.snapshot.mPixels, imageWidth, imageHeight);

    glOrtho(0, imageWidth, imageHeight, 0, -1, 1);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("aRolf");
        ImGui::ProgressBar(1-renderer.getLinesRemaining()/(float)imageHeight);
        ImGui::Text("Rendering with %d samples per pixel", renderer.getAntialiasingStrength());
        ImGui::Text("Using %d threads", renderer.getNumThreads());
        ImGui::End();

        ImGui::Render();

        glClearColor(.5,.5,.5,1);
        glClear(GL_COLOR_BUFFER_BIT);

        texture.regenerateTexture(camera.snapshot.mPixels, imageWidth, imageHeight);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture.getHandle());
        glBegin(GL_QUADS);
            glTexCoord2d(0, 1); glVertex2i(0,0);
            glTexCoord2d(1, 1); glVertex2i(imageWidth,0);
            glTexCoord2d(1, 0); glVertex2i(imageWidth,imageHeight);
            glTexCoord2d(0, 0); glVertex2i(0,imageHeight);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

//int main()
//{
//    srand(time(0));
//
//    const auto aspectRatio = 16./9.;
//    const int imageWidth=1000;
//    const int imageHeight=static_cast<int>(imageWidth/aspectRatio);
//
//    Camera camera(imageWidth, aspectRatio);
//    Scene scene = generateScene(0);
//    scene.addObject(std::make_shared<Sphere>(Vec3(0,-100.5,-1),100,std::make_shared<Lambert>(Color(.5,.8,.5))));
//    //scene.addObject(std::make_shared<Sphere>(Vec3(-1,0,-1),0.5,std::make_shared<Lambert>(Color::random()*Color::random())));
//    //scene.addObject(std::make_shared<Sphere>(Vec3(1,0,-1),0.5,std::make_shared<Lambert>(Color::random()*Color::random())));
//    scene.addObject(std::make_shared<Sphere>(Vec3(-0.5,0,-1),0.5,
//                                             std::make_shared<Metal>(Color::random()*Color::random(),0.5)));
//    scene.addObject(std::make_shared<Sphere>(Vec3(0.5,0,-1),0.5,
//                                             std::make_shared<Metal>(Color::random()*Color::random(), 0.1)));
//
//    Renderer renderer;
//    renderer.setAntialiasingStrength(50);
//
//    renderer.render(scene, camera);
//
//}
