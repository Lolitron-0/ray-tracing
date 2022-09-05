# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.5)
project(PPM_RayTracing)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})


include_directories(
    Materials/
    )

set (SRCS
    main.cpp
    Sphere.cpp
    Scene.cpp
    Camera.cpp
    Snapshot.cpp
    Renderer.cpp
    RawTexture.cpp
    Materials/Lambert.cpp
    Materials/Metal.cpp

    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
)



add_custom_target(target ${CMAKE_COMMAND} -E env OMP_CANCELLATION=true)

add_executable(${CMAKE_PROJECT_NAME} ${SRCS})


find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} OpenGL::GL)

#find_package(imgui CONFIG)
#target_link_libraries(${CMAKE_PROJECT_NAME} imgui::imgui)

find_package(OpenMP)
target_link_libraries(${CMAKE_PROJECT_NAME} OpenMP::OpenMP_CXX)




