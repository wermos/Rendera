#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vec3.hpp"
#include "ray.hpp"

class Camera{
    
    
    vec3 origin;
    float port_width;
    float port_height;
    int img_width;
    int img_height;
    float focal_length;
    //viewport screen at (x = focal_length) (viewing direction is +X)
    
    public:
        Camera(){}
        Camera(vec3 Origin, float p_width, float p_height, int i_width, int i_height, float Focal_length):
            origin {Origin},
            port_width {p_width},
            port_height {p_height},
            img_width {i_width},
            img_height {i_height},
            focal_length {Focal_length} {}
        
        //returns the ray corresponding to (x,y) on the image
        ray get_ray(int x, int y){
            float viewport_Y = (x*1.0/img_width) * port_width - port_width/2;
            float viewport_Z = port_height/2 - (y*1.0/img_height) * port_height;
            vec3 viewpoint = {focal_length ,viewport_Y, viewport_Z};
            return ray(origin, viewpoint);
            
        }
};

#endif
