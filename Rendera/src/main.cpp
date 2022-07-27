#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "intersection.hpp"
#include "scene.hpp"
#include <fstream>
#include <cmath>
#include <random>
#include<iostream>





int main(){
    int n_sphere = 3;
    int img_width = 5000;
    int img_height = 5000;

    vec3 center = {3,-2,0};
    vec3 center1 = {3, 1, 0};
    vec3 center2 = {5, 0, 5};

    color b = {0,0, 1};
    color g = {0,1,0};
    color r = {1, 0,0};
    Material mat_1 ={b, 0.1, 1, 0.9, 200};
    Material mat_2 = {g, 0.1, 1, 0.9, 200};
    Material mat_3 = {0.5*r + 0.2*b, 0.1, 1, 0.9, 200};

    Scene sc(n_sphere, img_height, img_width);
    sc.add_sphere(center, 1, mat_1);
    sc.add_sphere(center1, 1, mat_2);
    sc.add_sphere(center2, 1, mat_3);

    sc.render();





    int max_col = 255;
    std::ofstream image("sphere.ppm");
    image << "P3\n";
    image << img_width << " " << img_height << "\n";
    image << max_col << "\n";

    for(int i = 0; i < img_height*img_width ; i++){
        if(sc.hitinfo[i].ishitting){
            image << sc.hitinfo[i].rgb.get_R() << " " << sc.hitinfo[i].rgb.get_G() << " " << sc.hitinfo[i].rgb.get_B()<<" " ;
        }
        else
            image << "0 0 0 ";
    }
    image.close();
}
