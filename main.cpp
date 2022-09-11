#include <iostream>
#include "AllHeader.hpp"
#include <thread>
#include <GLFW/glfw3.h>
#include <stdlib.h>
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

Scene generateScene()
{
    Scene scene;
    auto groundMaterial = std::make_shared<Lambert>(Color(0.5, 0.5, 0.5));
    scene.addObject(std::make_shared<Sphere>(Vec3(0,-1000,0), 1000, groundMaterial));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto chooseMat = randomFloat();
            Vec3 center(a + 0.9*randomFloat(), 0.2, b + 0.9*randomFloat());

            if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphereMaterial;

                if (chooseMat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphereMaterial = std::make_shared<Lambert>(albedo);
                    scene.addObject(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                } else if (chooseMat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = randomFloat(0, 0.5);
                    sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
                    scene.addObject(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                } else {
                    // glass
                    sphereMaterial = std::make_shared<Glass>(1.5);
                    scene.addObject(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    auto material1 = std::make_shared<Glass>(1.5);
    scene.addObject(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambert>(Color(0.4, 0.2, 0.1));
    scene.addObject(std::make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    scene.addObject(std::make_shared<Sphere>(Vec3(4, 1, 0), 1.0, material3));

    return scene;
}


int main()
{
    srand(time(0));


    //Gui values
    bool guiShowPreview = true;
    bool guiDynamicAntialiasing = true;
    bool guiRerender = true;
    int guiTargetAntialiasing = 50;
    int guiNumThreads = 4;
    float guiLookAt[3] = {0,0,0.1};
    float guiLookFrom[3] = {13,2,3};


    //Global values
    const auto aspectRatio = 3./2.;
    const int imageWidth=1200;
    const int imageHeight=static_cast<int>(imageWidth/aspectRatio);

    //Render
    GLFWwindow* window = initGui(imageWidth, imageHeight);

    Camera camera(imageWidth, aspectRatio, 20, 0.1, (Vec3(guiLookFrom)-Vec3(guiLookAt)).length()+10);
    camera.lookFrom(guiLookFrom);
    camera.lookAt(guiLookAt);
    Scene scene = generateScene();

    Renderer renderer;
    renderer.setAntialiasingStrength(guiTargetAntialiasing);
    renderer.setDynamicAntialiasing(guiDynamicAntialiasing);
    renderer.setNumThreads(guiNumThreads);

    std::thread renderThread([&renderer, scene, &camera](){
        renderer.render(scene, camera);
    });

    //Preview
    RawTexture texture(camera.snapshot.getWidth(), camera.snapshot.getHeight());

    glOrtho(0, imageWidth, imageHeight, 0, -1, 1);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //ImGui::ShowDemoWindow();

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        //ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x/3, ImGui));

        ImGui::Begin("Render", NULL, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::ProgressBar(1-renderer.getLinesRemaining()/(float)imageHeight);
            ImGui::Text("Using %d threads", renderer.getNumThreads());
            if(renderer.getLinesRemaining()>0)
                ImGui::Text("Rendering with %d samples per pixel", renderer.getCurrentAntialiasingStrength());
            else
                ImGui::Text("Done!");

            ImGui::NewLine();
            ImGui::Separator();
            ImGui::NewLine();

            if(ImGui::Button("Interrupt"))
                renderer.askInterrupt();
            ImGui::SameLine();
            if(ImGui::Button("Clear")){
                camera.snapshot.clear();
                texture.regenerateTexture(camera.snapshot.getPixelData(), imageWidth, imageHeight);
            }
            ImGui::SameLine();
            if(ImGui::Button("Render")){
                renderer.askInterrupt();
                renderThread.join();
                renderThread = std::thread([&renderer, scene, &camera](){
                    renderer.render(scene, camera);
                });
            }
            if(ImGui::Checkbox("Show preview", &guiShowPreview))
                texture.regenerateTexture(camera.snapshot.getPixelData(), imageWidth, imageHeight);
            if(ImGui::Checkbox("Dynamic render", &guiDynamicAntialiasing))
                renderer.setDynamicAntialiasing(guiDynamicAntialiasing);
            if(ImGui::SliderInt("Num threads", &guiNumThreads, 1, 20))
                renderer.setNumThreads(guiNumThreads);
            if(ImGui::SliderInt("Target antialiasing", &guiTargetAntialiasing, 1, 5000))
                renderer.setAntialiasingStrength(guiTargetAntialiasing);

            ImGui::NewLine();
            ImGui::Separator();
            ImGui::NewLine();

            ImGui::Checkbox("Rerender", &guiRerender);
            if(ImGui::SliderFloat3("Look At", guiLookAt, -10, 10) ||
                    ImGui::SliderFloat3("Look From", guiLookFrom, -10, 10)){
                camera.lookAt(guiLookAt);
                camera.lookFrom(guiLookFrom);
                renderer.askInterrupt();
                if(guiRerender){
                    renderThread.join();
                    renderThread = std::thread([&renderer, scene, &camera](){
                        renderer.render(scene, camera);
                    });
                }
            }

        ImGui::End();

        ImGui::Render();

        glClearColor(.5,.5,.5,1);
        glClear(GL_COLOR_BUFFER_BIT);

        if(guiShowPreview){
            if(renderer.getLinesRemaining()!=0)
                texture.regenerateTexture(camera.snapshot.getPixelData(), imageWidth, imageHeight);
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
        }
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    renderer.askInterrupt();
    renderThread.join();

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
