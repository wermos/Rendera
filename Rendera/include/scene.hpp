#ifndef SCENE_HPP
#define SCENE_HPP

#include "sphere.hpp"
#include "intersection.hpp"
#include "camera.hpp"

class Hitinfo{
    public:
        bool ishitting = false;
        float dist;
        vec3 intersection_pt;
        ray normal;
        ray ray_;
        color shade = {0,0,0};
        color shade_new = {0,0,0};
        color rgb;
        ray ref_ray;
};

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

class Scene{
    public:
        int n_sphere;
        int img_width;
        int img_height;
        Hitinfo *hitinfo = new Hitinfo[img_height*img_width];
        sphere *hitable_sphere = new sphere[n_sphere];


        vec3 light_src = {-5,3,5};
        color light_col = {1,1,1};


        vec3 cam_origin = {0,0,0};
        float port_width = 8;
        float port_height = 8;
        float focal_length = 2;
        int max_col = 255;
        Camera cam;



    




    public:
        Scene(int n_sphere_, int img_height_, int img_width_):n_sphere {n_sphere_}, img_height {img_height_},img_width {img_width_} {
                    cam = Camera(cam_origin, port_width, port_height, img_width, img_height, focal_length);

        }
        ~Scene(){
            delete hitable_sphere;
            delete hitinfo;
        }
        void set_sphere(int index, vec3 center, float radius, Material mat){
            if (index < n_sphere)
                hitable_sphere[index] = sphere(center, radius, mat);
            else
                std::cout<<"accessing wrong index"<<std::endl;
        }



        void hit_object(int x, int y){
            hitinfo[y*img_width + x].ray_ = ray(cam.get_ray(x, y));
            for(int i = 0; i < n_sphere; i++){
                Intersection i_;
                bool hits = i_.hit(hitable_sphere[i], hitinfo[y*img_width + x].ray_);
                if (hitinfo[y*img_width + x].ishitting && hits){
                    if (hitinfo[y*img_width + x].dist > i_.dist_1()){
                        hitinfo[y*img_width + x].dist = i_.dist_1();
                        hitinfo[y*img_width + x].intersection_pt = hitinfo[y*img_width + x].ray_.fetch(hitinfo[y*img_width + x].dist); 
                        hitinfo[y*img_width + x].normal = hitable_sphere[i].normal(hitinfo[y*img_width + x].intersection_pt);
                        hitinfo[y*img_width + x].shade = lighting(hitable_sphere[i].mat(), hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src, light_col);
                        hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();
                        hitinfo[y*img_width + x].ref_ray = reflect(hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal);
                        }
                }
                else if (hits){
                    hitinfo[y*img_width + x].ishitting = true;
                    hitinfo[y*img_width + x].dist = i_.dist_1();
                    hitinfo[y*img_width + x].intersection_pt = hitinfo[y*img_width + x].ray_.fetch(hitinfo[y*img_width + x].dist); 
                    hitinfo[y*img_width + x].normal = hitable_sphere[i].normal(hitinfo[y*img_width + x].intersection_pt);
                    hitinfo[y*img_width + x].shade = lighting(hitable_sphere[i].mat(), hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src, light_col);
                    hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();
                    hitinfo[y*img_width + x].ref_ray = reflect(hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal);

                }
            }
        }

        void next_depth(int x, int y){
            // hitinfo[y*img_width + x].ray_ = hitinfo[y*img_width + x].ref_ray;
            for(int i = 0; i < n_sphere; i++){
                if(hitinfo[y*img_width + x].ishitting){
                Intersection i_;
                bool hits = i_.hit(hitable_sphere[i], hitinfo[y*img_width + x].ref_ray);
                if (hitinfo[y*img_width + x].ishitting && hits){
                                    // std::cout<<hits;

                    if (hitinfo[y*img_width + x].dist > i_.dist_1()){
                        hitinfo[y*img_width + x].dist = i_.dist_1();
                        hitinfo[y*img_width + x].intersection_pt = hitinfo[y*img_width + x].ref_ray.fetch(hitinfo[y*img_width + x].dist); 
                        hitinfo[y*img_width + x].normal = hitable_sphere[i].normal(hitinfo[y*img_width + x].intersection_pt);
                        hitinfo[y*img_width + x].shade_new = lighting(hitable_sphere[i].mat(), hitinfo[y*img_width + x].ref_ray, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src, light_col);
                        // hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();
                        hitinfo[y*img_width + x].ref_ray = reflect(hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal);

                        }
                }
                if (!hitinfo[y*img_width + x].ishitting && hits){
                                    // std::cout<<hits;

                    hitinfo[y*img_width + x].ishitting = true;
                    hitinfo[y*img_width + x].dist = i_.dist_1();
                    hitinfo[y*img_width + x].intersection_pt = hitinfo[y*img_width + x].ref_ray.fetch(hitinfo[y*img_width + x].dist); 
                    hitinfo[y*img_width + x].normal = hitable_sphere[i].normal(hitinfo[y*img_width + x].intersection_pt);
                    hitinfo[y*img_width + x].shade_new = lighting(hitable_sphere[i].mat(), hitinfo[y*img_width + x].ref_ray, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src, light_col);
                    // hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();
                    hitinfo[y*img_width + x].ref_ray = reflect(hitinfo[y*img_width + x].ref_ray, hitinfo[y*img_width + x].normal);

                }}
            }
        }

        void render(){
            for(int x=0; x<img_width; x++){
                for(int y=0; y<img_height; y++){
                    hit_object(x,y);
                    // hitinfo[y*img_width + x].ishitting = false;
                    next_depth(x,y);
                    hitinfo[y*img_width + x].shade += hitinfo[y*img_width + x].shade_new;
                    hitinfo[y*img_width + x].shade_new = {0,0,0};
                    hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();
                    // next_depth(x,y);
                    next_depth(x,y);
                    hitinfo[y*img_width + x].shade += hitinfo[y*img_width + x].shade_new;
                    hitinfo[y*img_width + x].shade_new = {0,0,0};
                    hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();                    
                   
                    }
                }
            }


};




#endif