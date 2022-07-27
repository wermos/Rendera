#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"

class Material{
    color col;
    float ambient;
    float diffuse;
    float specular;
    float shininess;

    public:
        Material() = default;
        Material(color _Color, float _ambient, float _diffuse, float _specular, float _shininess):
        col {_Color},
        ambient {_ambient},
        diffuse {_diffuse},
        specular {_specular},
        shininess {_shininess} {}

        //getters
        color Color() const{
            return col;
        }

        float amb() const{
            return ambient;
        }

        float dif() const{
            return diffuse;
        }
        float spe() const{
            return specular;
        }

        float shiny() const{
            return shininess;
        }
};
#endif