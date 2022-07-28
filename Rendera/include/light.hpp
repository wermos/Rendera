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

class Directional : public Light {
    private:
        color Col;
        ray dir;
    
    public:
        virtual ray get_direction(vec3 hit_point){
            return dir;
        }

        virtual color L(vec3 hit_point){
            return Col;
        }
};

class PointLight : public Light {
    private:
        color Col;
        vec3 position;
    
    public:
        virtual ray get_direction(vec3 hit_point){
            return {hit_point,(hit_point - position)};
        }
};
#endif
