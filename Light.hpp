#ifndef Light_hpp
#define Light_hpp

#include <iostream>
#include "Vec3d.hpp"

// источник света

struct Light {
    Vec3d _position;
    double _intensity;

    Light(): _position(), _intensity(1.5) {};
    Light(const Vec3d& position): _position(position), _intensity(1.5) {};
    Light(const Vec3d& position, double intensity): _position(position), _intensity(intensity) {};
    Light(const Light& light): _position(light._position), _intensity(light._intensity) {};

    Light& operator=(const Light& light){
        if(this == &light) return *this;
        _position = light._position;
        _intensity = light._intensity;
        return *this;
    }
};

#endif
