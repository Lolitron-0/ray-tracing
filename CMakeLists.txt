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


set (SRCS
    main.cpp
    Sphere.cpp
    Scene.cpp
    Camera.cpp
    Snapshot.cpp
    Renderer.cpp
    Lambert.cpp
)


add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()
