#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "ray.hpp"
#include "color.hpp"

class Light{
    public:
        virtual ray get_direction(vec3 hit_point) = 0;
        virtual color L(vec3 hit_point) = 0;

    protected:
        bool shadows;
};

class Ambient : public Light {
    private:
        color Col;
    
    public:
        virtual color L(vec3 hit_point){

            return Col;
        }
};
#endif
