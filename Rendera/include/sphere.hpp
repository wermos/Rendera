#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "material.hpp"

class Sphere{
    vec3 center;
    float radius;
    Material material;

    public:
        Sphere(){}
        Sphere(vec3 Center, float Radius, Material mat): center {Center}, radius {Radius}, material {mat} {}

        //surface normal function, returns ray along outward normal
        ray normal(vec3 point){
            return ray(center, point - center);
        }

        //getters
        vec3 c() const{
            return center;
        }

        float r() const{
            return radius;
        }
         
        Material mat() const{
            return material;
        }
        
        

};

#endif
