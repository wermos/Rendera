#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "intersection.hpp"
#include <fstream>
#include <cmath>
#include <random>
#include <iostream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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
    // std::ofstream image("sphere.ppm");
    // image << "P3\n";
    // image << img_width << " " << img_height << "\n";
    // image << max_col << "\n";
    

    // for(int i=0; i<img_height; i++){
    //     for(int j=0; j<img_width; j++){

    //         //process each ray
    //         color shade;
    //         for(int sample=0; sample<50; sample++){

    //             ray ray_1 = cam.get_ray(j,i);

    //             Intersection i;
    //             bool hits = i.hit(s,ray_1);
    //             color temp_shade = {1,1,1};
                
                
    //             if(hits){

    //                 vec3 hit_point = ray_1.fetch(i.dist_1()); 
    //                 temp_shade = lighting(s.mat(), ray_1, s.normal(hit_point),hit_point,light_src, light_col);
    //             }

    //             if(sample==0){shade = temp_shade;}
    //             shade = (shade*(sample) + temp_shade)* (1.0/(sample+1));

    //         }
    //         shade = shade.get_int();

    //         //print result
    //         image << shade.get_R() << " " << shade.get_G() << " " << shade.get_B()<<" " ;
    //     }
    // }

    // image.close();
    
    // Jpeg and png
    uint8_t* pixels = new uint8_t[img_width * img_height * 3];

    int index = 0;
    for (int j = img_height - 1; j >= 0; --j){
        for (int i = 0; i < img_width; ++i){
        //process each ray
        color shade;
            for(int sample=0; sample<50; sample++){
                ray ray_1 = cam.get_ray(j,i);

                Intersection i;
                bool hits = i.hit(s,ray_1);
                color temp_shade = {1,1,1};


                    if(hits){

                        vec3 hit_point = ray_1.fetch(i.dist_1()); 
                        temp_shade = lighting(s.mat(), ray_1, s.normal(hit_point),hit_point,light_src, light_col);
                    }

                    if(sample==0){shade = temp_shade;}
                    shade = (shade*(sample) + temp_shade)* (1.0/(sample+1));

                }
                shade = shade.get_int();

            pixels[index++] = shade.get_R();
            pixels[index++] = shade.get_G();
            pixels[index++] = shade.get_B();
        }
    }
    
    stbi_write_png("Spherepng.png", img_width, img_height, 3, pixels, img_width * 3);

    stbi_write_jpg("Spherejpg3.jpg", img_width, img_height, 3, pixels, 100);
    delete[] pixels;
    
    return 0;
}
