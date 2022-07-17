#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "ray.hpp"
#include "color.hpp"
class Hitinfo{
    bool ishitting;
    float dist;
    vec3 intersection_pt;
    vec3 normal_pt;
    ray ray_;
    color shade;
};
class Display{
    public:
        int img_width;
        int img_height;
        Hitinfo *hitinfo = new Hitinfo[img_height*img_width];
};



#endif