#ifndef VEC3.HPP
#define VEC3.HPP

//code by Ameya Vikrama Singh
#include<iostream>
#include<cmath>
class vec3{
    float x,y,z;
    public:
        vec3() : x{0},y{0},z{0}{}

        //Cartesian coordinate Constructor
        vec3(float X,float Y,float Z) : x{X}, y{Y}, z{Z}{}

        //norm function
        constexpr float norm() const{
            return sqrt(x*x+y*y+z*z);
        }

        //vector addition
        friend vec3 operator+(vec3 const& h, vec3 const & s);

        //vector subtraction
        friend vec3 operator-(vec3 const& h, vec3 const & s);

        //scalar post-multiplication
        friend vec3 operator*(vec3 const& h, float const & s);

        //scalar post-division
        friend vec3 operator/(vec3 const& h, float const & s);


        //addition+assignemnt
        vec3& operator+=(vec3 const & s){
            x+=s.x;
            y+=s.y;
            z+=s.z;
            return *this;
        }

        //subtraction+assignemnt
        vec3& operator-=(vec3 const & s){
            x-=s.x;
            y-=s.y;
            z-=s.z;
            return *this;
        } 
    
        //scalar multiplication+assignment
        vec3& operator*=(float const& s){
            x*=s;
            y*=s;
            z*=s;
            return *this;
        }

        //scalar division+assignment
        vec3& operator/=(float const & s){
            x/=s;
            y/=s;
            z/=s;
            return *this;
        }

        //unary unit vector operator(not to confuse with -1 * a)
        vec3 operator-() const{
            return *this/norm();
        }

        //dot product
        friend float dot(vec3 const& h, vec3 const& s);

        //cross product
        friend vec3 cross(vec3 const& h, vec3 const& s);

        //angle between vectors, in radians
        friend float angle(vec3 const& h, vec3 const& s);

        //projection of h on s
        friend vec3 proj(vec3 const& h, vec3 const& s);

        //perpendicular projection
        friend vec3 perp(vec3 const& h, vec3 const& s);

        friend std::ostream& operator<<(std::ostream& out, const vec3& vect);

};

vec3 operator+(vec3 const& h, vec3 const & s){
            return {s.x+h.x, s.y+h.y, s.z+h.z};
        }

vec3 operator-(vec3 const& h, vec3 const & s){
            return {h.x-s.x,h.y-s.y,h.z-s.z};
        }

vec3 operator*(vec3 const& h, float const & s){
            return {s*h.x,s*h.y,s*h.z};
        }

vec3 operator/(vec3 const& h, float const & s){
            return h*(1/s);
        }

float dot(vec3 const& h, vec3 const& s){
            return h.x*s.x+h.y*s.y+h.z*s.z;
        }

vec3 cross(vec3 const& h, vec3 const& s){
            return {h.y*s.z-h.z*s.y, h.z*s.x-h.x*s.z, h.x*s.y-h.y*s.x };
        }

float angle(vec3 const& h, vec3 const& s){
            float cos=(dot(h,s))/(h.norm()*s.norm());
            return acos(cos);
        }

vec3 proj(vec3 const& h, vec3 const& s){
            return s*(dot(h,s))/(s.norm()*s.norm());                       
        }

vec3 perp(vec3 const& h, vec3 const& s){
            return h - proj(h,s);
        }

std::ostream& operator<<(std::ostream& out, const vec3& vect){
            out<<"("<<vect.x<<","<<vect.y<<","<<vect.z<<")\n";
            return out;
        }

#endif