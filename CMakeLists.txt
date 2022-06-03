cmake_minimum_required(VERSION 2.8)

project(task5)

set(task5_src main.cpp Vec3d.cpp create_image.cpp GetDataFromFile.cpp Figure.cpp)
set(task5_hdr head.hpp Vec3d.hpp Light.hpp Figure.hpp Figure_Factory.hpp)

add_executable(${PROJECT_NAME} ${task5_src } ${task5_hdr})