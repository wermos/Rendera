#ifndef CUBE_HPP
#define CUBE_HPP

#include <limits>
#include "vec3.hpp"
#include "ray.hpp"
#include "material.hpp"


vec3 max(vec3 a, vec3 b, ray r)
{
    if (dot((a - r.get_origin()),r.get_direction()) > dot((b- r.get_origin()),r.get_direction()))
    {
        return a;
    }
    else
    {
        return b;
    }
}

vec3 min(vec3 a, vec3 b, ray r)
{

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
        vec3 p_pos, np_pos;
        p_pos = point - m_position;
        np_pos = point - m_a - m_b - m_c - m_position;
        vec3 normal;
        if (dot(p_pos, cross(m_a, m_b)) < 1e5)
        {
            normal = cross(m_a, m_b);
            if (dot(m_c, normal) < 0)
            {
                normal = -normal;
            }
        }
        else if (dot(p_pos, cross(m_a, m_c)) < 1e5)
        {
            normal = cross(m_a, m_c);
            if (dot(m_b, normal) < 0)
            {
                normal = -normal;
            }
        }
        else if (dot(p_pos, cross(m_b, m_c)) < 1e5)
        {
            normal = cross(m_b, m_c);
            if (dot(m_a, normal) < 0)
            {
                normal = -normal;
            }
        }
        else if (dot(np_pos, cross(m_a, m_b)) < 1e5)
        {
            normal = cross(m_a, m_b);
            if (dot(-m_c, normal) < 0)
            {
                normal = -normal;
            }
        }
        else if (dot(np_pos, cross(m_a, m_c)) < 1e5)
        {
            normal = cross(m_a, m_c);
            if (dot(-m_b, normal) < 0)
            {
                normal = -normal;
            }
        }
        else if (dot(np_pos, cross(m_b, m_c)) < 1e5)
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


    vec3 plane_intersect(const vec3 &n, const vec3 &p, const ray &r)
    {
        float num = dot(n, p - r.get_origin());
        if (abs(dot(r.get_direction(), n)) > 1e-5)
        {
            num = num / dot(r.get_direction(), n);
        }
        else
        {
            num = num/abs(num);
            num *= std::numeric_limits<float>::max();
        }

        return r.get_origin() + num * r.get_direction();
    }

    HitInfo hit(const ray &r, int recursion_depth)
    {
        vec3 temp_a = plane_intersect(cross(m_b, m_c), m_position, r), temp_b = plane_intersect(cross(m_b, m_c), m_position + m_a, r);
        vec3 amin = min(temp_a, temp_b, r);
        vec3 amax = max(temp_a, temp_b, r);

        temp_a = plane_intersect(cross(m_a, m_c), m_position, r), temp_b = plane_intersect(cross(m_a, m_c), m_position + m_b, r);
        amin = max(amin, min(temp_a, temp_b, r), r);
        amax = min(amax, max(temp_a, temp_b, r), r);

        temp_a = plane_intersect(cross(m_a, m_b), m_position, r), temp_b = plane_intersect(cross(m_a, m_b), m_position + m_c, r);
        amin = max(amin, min(temp_a, temp_b, r), r);
        amax = min(amax, max(temp_a, temp_b, r), r);

        if(dot((amin-r.get_origin()),r.get_direction())>dot((amax-r.get_origin()),r.get_direction()))
        {
            return {false, vec3(0,0,0), m_material, r, recursion_depth};
        }
        else if(dot(r.get_direction(),amax - r.get_origin())<0 )
        {
            return {false, vec3(0,0,0), m_material, r, recursion_depth};
        }
        else if(dot(r.get_direction(),amin - r.get_origin())<0)
        {
            return {true, amax, m_material, r, recursion_depth-1};
        }
        
        return {true, amin, m_material, r, recursion_depth-1};
        
    }
};

#endif // CUBE_HPP
