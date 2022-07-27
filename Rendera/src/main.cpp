#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "intersection.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "scene.hpp"
#include <fstream>
#include <cmath>
#include <random>

int main(){
    int n_sphere = 3;
    int img_width = 5000;
    int img_height = 5000;

    vec3 center = {3,-2,0};
    vec3 center1 = {3, 1, 0};
    vec3 center2 = {5, 0, 5};

    float specular_cosine = dot(-cam_ray.get_direction(), reflect_ray.get_direction());
    float spec_factor = 0;
    color b = {0,0, 1};
    color g = {0,1,0};
    color r = {1, 0,0};
    Material mat_1 ={b, 0.1, 1, 0.9, 200};
    Material mat_2 = {g, 0.1, 1, 0.9, 200};
    Material mat_3 = {0.5*r + 0.2*b, 0.1, 1, 0.9, 200};

    Scene sc(n_sphere, img_height, img_width);
    sc.set_sphere(0, center, 1, mat_1);
    sc.set_sphere(1, center1, 1, mat_2);
    sc.set_sphere(2, center2, 1, mat_3);

    sc.render();

    int max_col = 255;
    Camera cam(cam_origin, port_width, port_height, img_width, img_height, focal_length);

    // Jpeg and png
    // Making an array of such size as there are width*height pixels and each pixel has 3 RGB values.
    std::uint8_t* pixels = new std::uint8_t[img_width * img_height * 3]; 
    int index = 0;  //Index of the array containing RGB values of image for the current pixel
    std::ofstream image("sphere.ppm");
    image << "P3\n";
    image << img_width << " " << img_height << "\n";
    image << max_col << "\n";
    for(int i = 0; i < img_height*img_width ; i++){
        if(sc.hitinfo[i].ishitting){
            image << sc.hitinfo[i].rgb.get_R() << " " << sc.hitinfo[i].rgb.get_G() << " " << sc.hitinfo[i].rgb.get_B()<<" " ;
            pixels[index++] = sc.hitinfo[i].rgb.get_R();
            pixels[index++] = sc.hitinfo[i].rgb.get_G();
            pixels[index++] = sc.hitinfo[i].rgb.get_B();
        }
        else
            image << "0 0 0 ";
    }
    
    stbi_write_png("Sphere.png", img_width, img_height, 3, pixels, img_width * 3);
    std::cout<<"PNG image generated\n";
    stbi_write_jpg("Sphere.jpg", img_width, img_height, 3, pixels, 100);
    std::cout<<"JPG image generated\n";
    delete[] pixels;
    image.close()
    return 0;
}
