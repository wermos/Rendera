#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include <cmath>
#include "vec3.hpp"

float epsilon=0.0001;
class ray{
    //origin
    vec3 origin;

    //unit vector denoting direction
    vec3 direction;

    public:
        //Constructors
        constexpr ray() : origin {vec3(0,0,0)}, direction {vec3(1,0,0)} {}
        constexpr ray(vec3 Origin, vec3 Direction) : origin {Origin} , direction {Direction.unit()} {}

        //fetch point at distance from point along ray, from origin by default
        constexpr vec3 fetch(float distance, const vec3& point) const{
            return point + distance * direction;
        }

        constexpr vec3 fetch(float distance) const{
            return origin + distance * direction;
        }

        //origin setter
        vec3& Origin(const vec3& Origin){
            origin = Origin;
            return origin;
        }

        //direction setter, maintains unit magnitude for direction
        vec3& Direction(const vec3& Direction){
            direction = Direction.unit();
            return direction;
        }

        vec3 get_direction(){
            return direction;
        }

        vec3 get_origin(){
            return origin;
        }
        

        //check for intersection between rays, dont use float equality
        friend bool is_intersect(const ray& h, const ray& s);

        //return intersection point
        friend vec3 intersection(const ray& h, const ray& s);
        
};

bool is_intersect(const ray& h, const ray& s){
    if (dot((h.origin-s.origin), cross(h.direction,s.direction)) < epsilon){
        return true;
    }

    return false;
}

vec3 intersection(const ray& h, const ray& s){
    vec3 g = h.origin - s.origin;
    vec3 v1 = cross(g, s.direction);
    vec3 v2 = cross(h.direction,s.direction);
    float a = v1.norm();
    float b = v2.norm();
    float sign = dot(v1,v2) > 0 ? 1 : -1;
    return h.fetch(sign*a/b);

}

#endif
