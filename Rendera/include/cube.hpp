#ifndef CUBE_HPP
#define CUBE_HPP

#include <cmath>
#include <limits>
#include "vec3.hpp"
#include "ray.hpp"
#include "material.hpp"

// checks which point is farther going along the ray 
vec3 max(vec3 a, vec3 b, ray r)
{
    // if dot of a-ray.origin and ray.direction is greater than dot of b-ray.origin and ray.direction
    if (dot((a - r.get_origin()),r.get_direction()) > dot((b- r.get_origin()),r.get_direction()))
    {
        return a;
    }
    else
    {
        return b;
    }
}

// checks which point is closer going along the ray
vec3 min(vec3 a, vec3 b, ray r)
{
    // if dot of a-ray.origin and ray.direction is smaller than dot of b-ray.origin and ray.direction
    if (dot((a - r.get_origin()),r.get_direction()) < dot((b- r.get_origin()),r.get_direction()))
    {
        return a;
    }
    else
    {
        return b;
    }
}

class Cube
{
private:
    vec3 m_position;
    vec3 m_a, m_b, m_c;
    Material m_material;

public:
    Cube(vec3 position, vec3 a, vec3 b, vec3 c, Material mat) : m_position{position}, m_a{a}, m_b{b}, m_c{c}, m_material{mat} {};

    ray normal(const vec3 &point)
    {
        // p_pos : vector from m_position to point
        // np_pos : vector from diagonally opposite corner to point
        vec3 p_pos=point - m_position;
        vec3 np_pos=point - m_a - m_b - m_c - m_position;
        vec3 normal;

        static double m_epsilon = 1e-5;

        // every if statement checks if the point is on which of the 6 faces of the cube
        if (dot(p_pos, cross(m_a, m_b)) < m_epsilon)
        {
            normal = cross(m_a, m_b);
            if (dot(m_c, normal) < 0)
            {
                normal = -normal;
            }
        }
        else if (abs(dot(p_pos, cross(m_a, m_c))) < m_epsilon)
        {
            normal = cross(m_a, m_c);
            if (dot(m_b, normal) < 0)
            {
                normal = -normal;
            }
        }
        else if (dot(p_pos, cross(m_b, m_c)) < m_epsilon)
        {
            normal = cross(m_b, m_c);
            if (dot(m_a, normal) < 0)
            {
                normal = -normal;
            }
        }
        else if (dot(np_pos, cross(m_a, m_b)) < m_epsilon)
        {
            normal = cross(m_a, m_b);
            if (dot(-m_c, normal) < 0)
            {
                normal = -normal;
            }
        }
        else if (dot(np_pos, cross(m_a, m_c)) < m_epsilon)
        {
            normal = cross(m_a, m_c);
            if (dot(-m_b, normal) < 0)
            {
                normal = -normal;
            }
        }
        else if (dot(np_pos, cross(m_b, m_c)) < m_epsilon)
        {
            normal = cross(m_b, m_c);
            if (dot(-m_a, normal) < 0)
            {
                normal = -normal;
            }
        }
        else
        {
            normal = vec3(0, 0, 0);
        }
        return ray(point, normal);
    }

    // returns the intersection of the ray with the plane passing through the point p and perpendicular to the normal n
    vec3 plane_intersect(const vec3 &n, const vec3 &p, const ray &r)
    {
        float num = dot(n, p - r.get_origin());
        if (abs(dot(r.get_direction(), n)) > 1e-5)
        {
            num = num / dot(r.get_direction(), n);
        }
        else                                            // if ray is parallel to the plane
        {
            if(num > 0){
                num = std::numeric_limits<float>::max();
            }
            else{
                num = std::numeric_limits<float>::lowest();
            }
        }

        return r.get_origin() + num * r.get_direction();
    }



    /*
        1. computes intersection with all parallel plane pairs
        2. intersection that comes first when going along the ray be mins and the next one be maxs
        3. it will make three pairs for three pairs of parallel planes
        4. then get first occuring intersection of maxs and last occuring intersection of mins
        if last occuring intersection of mins occurs before first occuring intersection of maxs, then rays intersects with these two intersection points
        otherwise, rays do not intersect with the cube 
        (all occurences are referenced when traversing along the ray direction)
    */

    HitInfo hit(const ray &r, int recursion_depth)
    {
        vec3 temp_a = plane_intersect(cross(m_b, m_c), m_position, r);
        vec3 temp_b = plane_intersect(cross(m_b, m_c), m_position + m_a, r);
        vec3 amin = min(temp_a, temp_b, r);
        vec3 amax = max(temp_a, temp_b, r);

        temp_a = plane_intersect(cross(m_a, m_c), m_position, r);
        temp_b = plane_intersect(cross(m_a, m_c), m_position + m_b, r);
        amin = max(amin, min(temp_a, temp_b, r), r);
        amax = min(amax, max(temp_a, temp_b, r), r);

        temp_a = plane_intersect(cross(m_a, m_b), m_position, r);
        temp_b = plane_intersect(cross(m_a, m_b), m_position + m_c, r);
        amin = max(amin, min(temp_a, temp_b, r), r);
        amax = min(amax, max(temp_a, temp_b, r), r);

        // if the ray is outside the cube amin comes after amax when going along the ray
        if(dot((amin-r.get_origin()),r.get_direction())>dot((amax-r.get_origin()),r.get_direction()))
        {
            return {false, vec3(0,0,0), m_material, r, recursion_depth};
        }
        else if(dot(r.get_direction(),amax - r.get_origin())<0 )    // checks if both intersection are behind the r.origin
        {
            return {false, vec3(0,0,0), m_material, r, recursion_depth};
        }
        else if(dot(r.get_direction(),amin - r.get_origin())<0)     // checks if r.origin is inside the cube
        {
            return {true, amax, m_material, r, recursion_depth-1};
        }
        
        return {true, amin, m_material, r, recursion_depth-1};     // if two intersections, returns the closest one
        
    }
};

#endif // CUBE_HPP
