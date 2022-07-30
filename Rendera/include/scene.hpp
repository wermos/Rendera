#ifndef SCENE_HPP
#define SCENE_HPP

#include "sphere.hpp"
#include "intersection.hpp"
#include "camera.hpp"
#include "cube.hpp"
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
    Hitinfo() = default;
};

color lighting(Material mat, ray cam_ray, ray normal, vec3 point, vec3 light_src, color intensity){

    ray incident_ray = {point, point - light_src};
    ray reflect_ray = reflect(incident_ray, normal);

    color effective_col = mat.col * intensity;

    //determine ambient contribution
    color ambient_col = effective_col * mat.ambient;

    
    //determine diffuse contribution, using Lambert's cosine law
    color diffuse_col = {0, 0, 0};
    float diffuse_cosine = dot(-incident_ray.get_direction(), normal.get_direction());

    // float lambert_cosine = dot(-cam_ray.get_direction(), normal.get_direction());

    if (diffuse_cosine >= 0){
        diffuse_col = diffuse_cosine * effective_col * mat.diffuse;
    }

    

    float specular_cosine = dot(-cam_ray.get_direction(), reflect_ray.get_direction());
    float spec_factor = 0;

    if(specular_cosine >= 0){
        spec_factor = pow(specular_cosine, mat.shininess;
    }
    color specular_col = spec_factor * intensity * mat.specular;

    return ambient_col + diffuse_col + specular_col;
}

class Scene{
    public:
        int n_sphere = 1;
        int n_cube = 0;
        uint16_t img_width;
        uint16_t img_height;
        Hitinfo *hitinfo = new Hitinfo[img_height*img_width];
        std::vector<Sphere> hitable_sphere;
        std::vector<Cube> hitable_cube;


        vec3 light_src = {-5,3,5};
        color light_col = {1,1,1};
        vec3 light_src2 = {0, 10, 0};



        vec3 cam_origin = {0,0,1};
        float port_width = 10;
        float port_height = 10;
        float focal_length = 4;
        int max_col = 255;
        Camera cam;



    




    public:
        Scene(int n_sphere_, uint16_t img_height_, uint16_t img_width_):n_sphere {n_sphere_}, img_height {img_height_},img_width {img_width_} {
                    cam = Camera(cam_origin, port_width, port_height, img_width, img_height, focal_length);

        }
        ~Scene(){
            delete hitinfo;
        }
        void add_sphere(vec3 center, float radius, Material mat){
            n_sphere++;
            hitable_sphere.push_back(Sphere(center, radius, mat));
        }
        void add_cube(vec3 position, vec3 a, vec3 b, vec3 c, Material mat){
            n_cube++;
            hitable_cube.push_back(Cube(position, a, b, c, mat));
        }



        void hit_object(int x, int y){
            std::vector<Sphere>::iterator sp;
            std::vector<Cube>::iterator cb;
            hitinfo[y*img_width + x].ray_ = cam.get_ray(x, y);
            // std::cout<<cam.get_ray(x, y).get_direction();
            for(sp = hitable_sphere.begin(); sp != hitable_sphere.end(); ++sp){
                Intersection i_;
                bool hits = i_.hit(*sp, hitinfo[y*img_width + x].ray_);
                if (hitinfo[y*img_width + x].ishitting && hits){
                    if (hitinfo[y*img_width + x].dist > i_.dist_1()){
                        hitinfo[y*img_width + x].dist = i_.dist_1();
                        hitinfo[y*img_width + x].intersection_pt = hitinfo[y*img_width + x].ray_.fetch(hitinfo[y*img_width + x].dist); 
                        hitinfo[y*img_width + x].normal = (*sp).normal(hitinfo[y*img_width + x].intersection_pt);
                        hitinfo[y*img_width + x].shade = lighting((*sp).mat(), hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src, light_col);
                        hitinfo[y*img_width + x].shade += lighting((*sp).mat(), hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src2, light_col);
                        hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();
                        hitinfo[y*img_width + x].ref_ray = reflect(hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal);
                        }
                }
                else if (hits){
                    hitinfo[y*img_width + x].ishitting = true;
                    hitinfo[y*img_width + x].dist = i_.dist_1();
                    hitinfo[y*img_width + x].intersection_pt = hitinfo[y*img_width + x].ray_.fetch(hitinfo[y*img_width + x].dist); 
                    hitinfo[y*img_width + x].normal = (*sp).normal(hitinfo[y*img_width + x].intersection_pt);
                    hitinfo[y*img_width + x].shade = lighting((*sp).mat(), hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src, light_col);
                    hitinfo[y*img_width + x].shade += lighting((*sp).mat(), hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src2, light_col);
                    hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();
                    hitinfo[y*img_width + x].ref_ray = reflect(hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal);

                }
            }

            for(cb = hitable_cube.begin(); cb != hitable_cube.end(); ++cb){
                bool hits = (*cb).hit(hitinfo[y*img_width + x].ray_);
                if(hitinfo[y*img_width + x].ishitting && hits){
                    float d = (*cb).get_int_pt().norm();
                    if (hitinfo[y*img_width + x].dist>d){
                        hitinfo[y*img_width + x].ishitting = true;
                        hitinfo[y*img_width + x].intersection_pt = (*cb).get_int_pt();
                        hitinfo[y*img_width + x].dist = d;
                        hitinfo[y*img_width + x].normal = (*cb).normal(hitinfo[y*img_width + x].intersection_pt);
                        hitinfo[y*img_width + x].shade = lighting((*cb).mat(), hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src, light_col);
                        hitinfo[y*img_width + x].shade += lighting((*cb).mat(), hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src2, light_col);
                        hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();
                        hitinfo[y*img_width + x].ref_ray = reflect(hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal);
                    }

                }
                else if(hits){
                    hitinfo[y*img_width + x].ishitting = true;
                    hitinfo[y*img_width + x].intersection_pt = (*cb).get_int_pt();
                    hitinfo[y*img_width + x].dist = hitinfo[y*img_width + x].intersection_pt.norm();
                    hitinfo[y*img_width + x].normal = (*cb).normal(hitinfo[y*img_width + x].intersection_pt);
                    hitinfo[y*img_width + x].shade = lighting((*cb).mat(), hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src, light_col);
                    hitinfo[y*img_width + x].shade += lighting((*cb).mat(), hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src2, light_col);
                    hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();
                    hitinfo[y*img_width + x].ref_ray = reflect(hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal);


                }
            }
        }

        void next_depth(int x, int y){
            std::vector<Sphere>::iterator sp;
            std::vector<Cube>::iterator cb;
            for(sp = hitable_sphere.begin(); sp != hitable_sphere.end(); ++sp){
                if(hitinfo[y*img_width + x].ishitting){
                Intersection i_;
                bool hits = i_.hit(*sp, hitinfo[y*img_width + x].ref_ray);
                if (hits){
                    if (hitinfo[y*img_width + x].dist > i_.dist_1()){
                        hitinfo[y*img_width + x].dist = i_.dist_1();
                        hitinfo[y*img_width + x].intersection_pt = hitinfo[y*img_width + x].ref_ray.fetch(hitinfo[y*img_width + x].dist); 
                        hitinfo[y*img_width + x].normal = (*sp).normal(hitinfo[y*img_width + x].intersection_pt);
                        hitinfo[y*img_width + x].shade_new = lighting((*sp).mat(), hitinfo[y*img_width + x].ref_ray, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src, light_col);
                        hitinfo[y*img_width + x].shade_new = lighting((*sp).mat(), hitinfo[y*img_width + x].ref_ray, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src2, light_col);
                        hitinfo[y*img_width + x].ref_ray = reflect(hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal);
                        }
                }
                }
            }

            for(cb = hitable_cube.begin(); cb != hitable_cube.end(); ++cb){
                if(hitinfo[y*img_width + x].ishitting){
                bool hits = (*cb).hit(hitinfo[y*img_width + x].ray_);
                    if (hits){
                        float d = (*cb).get_int_pt().norm();
                        if (hitinfo[y*img_width + x].dist>d){
                            hitinfo[y*img_width + x].intersection_pt = (*cb).get_int_pt();
                            hitinfo[y*img_width + x].dist = d;
                            hitinfo[y*img_width + x].normal = (*cb).normal(hitinfo[y*img_width + x].intersection_pt);
                            hitinfo[y*img_width + x].shade_new = lighting((*cb).mat(), hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal, hitinfo[y*img_width + x].intersection_pt, light_src, light_col);
                            hitinfo[y*img_width + x].ref_ray = reflect(hitinfo[y*img_width + x].ray_, hitinfo[y*img_width + x].normal);
                        }
                    }

                }
            }
        }

        void render(){
            for(int x=0; x<img_width; x++){
                for(int y=0; y<img_height; y++){
                    hit_object(x,y);
                    next_depth(x,y);
                    hitinfo[y*img_width + x].shade += hitinfo[y*img_width + x].shade_new;
                    hitinfo[y*img_width + x].shade_new = {0,0,0};
                    hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();
                    next_depth(x,y);
                    hitinfo[y*img_width + x].shade += hitinfo[y*img_width + x].shade_new;
                    hitinfo[y*img_width + x].shade_new = {0,0,0};
                    hitinfo[y*img_width + x].rgb = hitinfo[y*img_width + x].shade.get_int();                    
                   
                    }
                }
            }


};




#endif