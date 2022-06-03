#ifndef head_hpp
#define head_hpp

#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include <vector>
#include <omp.h>
#include <string>
#include <map>

#include "Vec3d.hpp"
#include "Figure.hpp"
#include "Light.hpp"

struct Parametrs {
    Vec3d cam;
    Vec3d normal;
    Vec3d up;
    double screen;
    double limit;
    double alpha;
    size_t width;
    size_t height;
    Light light;
};

#define PI 3.14159265358979323846


bool scene_intersect(const Vec3d&, const Vec3d&, const std::vector<Figure*>&, Vec3d&, Vec3d&, Vec3d&, double);
Vec3d cast_ray(const Vec3d&, const Vec3d&, const std::vector<Figure*>&, const Light&, double);
void create_image(const std::vector<Figure*>&, Parametrs&);


bool GetParametrs(const std::string&, Parametrs&);
bool GetFigures(const std::string&, std::vector<Figure*>&);

#endif
