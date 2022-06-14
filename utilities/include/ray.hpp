#ifndef RAY_HPP
#define RAY_HPP


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

        //getters
        vec3 get_direction(){
            return direction;
        }

        vec3 get_origin(){
            return origin;
        }
        

        //check for intersection between rays, dont use float equality
        friend bool is_intersecting(const ray& ray1, const ray& ray2);

        //return intersection point
        friend vec3 intersection(const ray& ray1, const ray& ray2);
        
};

bool is_intersecting(const ray& ray1, const ray& ray2){
    if (abs(dot((ray1.origin-ray2.origin), cross(ray1.direction,ray2.direction))) < epsilon){
        return true;
    }

    return false;
}

vec3 intersection(const ray& ray1, const ray& ray2){
    vec3 g = ray1.origin - ray1.origin;
    vec3 v1 = cross(g, ray2.direction);
    vec3 v2 = cross(ray1.direction,ray2.direction);
    float a = v1.norm();
    float b = v2.norm();
    float sign = dot(v1,v2) > 0 ? 1 : -1;
    return ray1.fetch(sign*a/b);

}

#endif
