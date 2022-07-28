#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"


struct Material{
    color col;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
};


#endif