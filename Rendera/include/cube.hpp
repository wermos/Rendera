#ifndef CUBE_HPP
#define CUBE_HPP

#include "vec3.hpp"
#include "ray.hpp"
#include "material.hpp"

#define INFINITY 1E10

struct HitInfo
{
    bool is_hitting;
    vec3 intersection_point;
    Material material;
    ray Ray;
    int recursion_depth;

    HitInfo(bool is_hitting, vec3 intersection_point, Material material, ray Ray, int recursion_depth) : is_hitting{is_hitting}, intersection_point{intersection_point}, material{material}, Ray{Ray}, recursion_depth{recursion_depth} {}
};

HitInfo max(HitInfo a, HitInfo b, vec3 o)
{
    if ((a.intersection_point - o).norm() > (b.intersection_point - o).norm())
    {
        return a;
    }
    else
    {
        return b;
    }
}

HitInfo min(HitInfo a, HitInfo b, vec3 o)
{

    if ((a.intersection_point - o).norm() < (b.intersection_point - o).norm())
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

    Material mat() const
    {
        return m_material;
    }

    vec3 position() const
    {
        return m_position;
    }

    vec3 a() const
    {
        return m_a;
    }

    vec3 b() const
    {
        return m_b;
    }

    vec3 c() const
    {
        return m_c;
    }

    HitInfo plane_intersect(const vec3 &n, const vec3 &p, const ray &r)
    {
        // if(dot(r.get_direction(),n) < 1e5 || dot(r.get_direction(),n) > -1e5){
        //     return HitInfo(false, vec3(0,0,0), m_material, r, 0);
        // }
        // float t = dot(n,p - r.get_origin()) / dot(n,r.get_direction());
        // if(t < 0){
        //     return HitInfo(false, vec3(0,0,0), m_material, r, 0);
        // }
        // else{
        //     return HitInfo(true, r.get_origin() + t * r.get_direction(), m_material, r, 0);
        // }

        float num = dot(n, p - r.get_origin());
        if (abs(dot(r.get_direction(), n)) > 1e-5)
        {
            num = num / dot(r.get_direction(), n);
        }
        else
        {
            num *= INFINITY;
        }

        return HitInfo(true, r.get_origin() + num * r.get_direction(), m_material, r, 0);
    }

    HitInfo hit(const ray &r, int recursion_depth)
    {
        HitInfo hit_info(false, vec3(0, 0, 0), m_material, r, recursion_depth);
        // hit_info.is_hitting = false;
        // hit_info.recursion_depth = recursion_depth;
        // hit_info.Ray = r;
        // hit_info.material = m_material;


        HitInfo temp_a = plane_intersect(cross(m_b, m_c), m_position, r), temp_b = plane_intersect(cross(m_b, m_c), m_position + m_a, r);
        HitInfo amin = min(temp_a, temp_b, r.get_origin());
        HitInfo amax = max(temp_a, temp_b, r.get_origin());

        temp_a = plane_intersect(cross(m_a, m_c), m_position, r), temp_b = plane_intersect(cross(m_a, m_c), m_position + m_b, r);
        amin = max(amin, min(temp_a, temp_b, r.get_origin()), r.get_origin());
        amax = min(amax, max(temp_a, temp_b, r.get_origin()), r.get_origin());

        temp_a = plane_intersect(cross(m_a, m_b), m_position, r), temp_b = plane_intersect(cross(m_a, m_b), m_position + m_c, r);
        amin = max(amin, min(temp_a, temp_b, r.get_origin()), r.get_origin());
        amax = min(amax, max(temp_a, temp_b, r.get_origin()), r.get_origin());

        if((amin.intersection_point-r.get_origin()).norm()>(amax.intersection_point-r.get_origin()).norm())
        {
            return hit_info;
        }
        else if(dot(r.get_direction(),amax.intersection_point - r.get_origin())<0 )
        {
            return hit_info;
        }
        else if(dot(r.get_direction(),amin.intersection_point - r.get_origin())<0)
        {
            amax.is_hitting = true;
            amax.recursion_depth = recursion_depth - 1;
            return amax;
        }
        amin.is_hitting = true;
        amin.recursion_depth = recursion_depth - 1;
        return amin;
    }
};

#endif // CUBE_HPP
