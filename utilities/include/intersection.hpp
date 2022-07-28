#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "sphere.hpp"
#include "ray.hpp"

//stores the t-value of ray-sphere intersections
class Intersection{
    float t_1;
    float t_2;

    public:
        bool hit(const sphere &s, const ray &ray_1){
            //make a quadratic equation in t
            vec3 a = ray_1.get_direction();
            vec3 b = ray_1.get_origin();
            vec3 c = s.c();
            float radius = s.r();

            float alpha = a.norm()*a.norm(); //tsquare coeff
            float beta = 2*dot(a,b-c); //t coeff
            float gamma = (b-c).norm()*(b-c).norm() - radius*radius; //constant

            float disc = beta*beta - 4*alpha*gamma;

            if(disc >= 0){
                t_1 = (-beta - sqrt(disc))/(2 * alpha);
                t_2 = (-beta + sqrt(disc))/(2 * alpha);
                return t_2 >= 0;
            }

            //only positive hits
            return false;
        }



        //getters
        
};

#endif
