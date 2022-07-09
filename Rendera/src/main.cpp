#include "../include/vec3.hpp"
#include "../include/ray.hpp"
#include "../include/color.hpp"
#include "../include/camera.hpp"
#include "../include/sphere.hpp"
#include "../include/intersection.hpp"
#include <fstream>
#include <cmath>

color lighting(Material mat, ray cam_ray, ray normal, vec3 point, vec3 light_src, color intensity){

    ray incident_ray = {point, point - light_src};
    ray reflect_ray = reflect(incident_ray, normal);

    color effective_col = mat.Color() * intensity;

    //determine ambient contribution
    color ambient_col = effective_col * mat.amb();

    
    //determine diffuse contribution, using Lambert's cosine law
    color diffuse_col = {0, 0, 0};
    float diffuse_cosine = dot(-incident_ray.get_direction(), normal.get_direction());

    // float lambert_cosine = dot(-cam_ray.get_direction(), normal.get_direction());

    if (diffuse_cosine >= 0){
        diffuse_col = diffuse_cosine * effective_col * mat.dif();
    }

    

    float specular_cosine = dot(-cam_ray.get_direction(), reflect_ray.get_direction());
    float spec_factor = 0;

    if(specular_cosine >= 0){
        spec_factor = pow(specular_cosine, mat.shiny());
    }
    color specular_col = spec_factor * intensity * mat.spe();

    return ambient_col + diffuse_col + specular_col;
}

int main(){
    
    vec3 center = {5,0,0};
    color blue = {0.2,0.2, 1};
    Material mat_1 ={blue, 0.1, 1, 0.9, 200};
    sphere s(center,4, mat_1);

    vec3 light_src = {-0.5,-3,5};
    color light_col = {1,1,1};

    vec3 cam_origin = {0,0,0};
    float port_width = 8;
    float port_height = 8;
    int img_width = 512;
    int img_height = 512;
    float focal_length = 2;
    int max_col = 255;
    Camera cam(cam_origin, port_width, port_height, img_width, img_height, focal_length);

    //ppm file
    std::ofstream image("sphere.ppm");
    image << "P3\n";
    image << img_width << " " << img_height << "\n";
    image << max_col << "\n";


    for(int i=0; i<img_height; i++){
        for(int j=0; j<img_width; j++){

            //process each ray

            ray ray_1 = cam.get_ray(j,i);

            Intersection i;
            bool hits = i.hit(s,ray_1);

            vec3 hit_point = ray_1.fetch(i.dist_1()); 
            color shade = lighting(s.mat(), ray_1, s.normal(hit_point),hit_point,light_src, light_col).get_int();

            //print result
            if(hits){
                image << shade.get_R() << " " << shade.get_G() << " " << shade.get_B()<<" " ;
                //std::cout<< shade.get_R()<<" ";
            }

            else{
                image << "255 255 255 ";
            }
        }
    }

    image.close();
}
