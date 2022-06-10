#ifndef VEC3_HPP
#define VEC3_HPP


#include <iostream>
#include <cmath>
class vec3{
    float x,y,z;
    public:
        vec3() : x {0}, y {0}, z {0} {}

        //Cartesian coordinate Constructor
        vec3(float X,float Y,float Z) : x {X}, y {Y}, z {Z} {}

        //norm function
        constexpr float norm() const {
            return sqrt(x * x + y * y + z * z);
        }

        //unit vector function
        constexpr vec3 unit(){
            return *this/this->norm();
        }

        //vector addition
        friend constexpr vec3 operator+(const vec3& h, const vec3& s);

        //vector subtraction
        friend constexpr vec3 operator-(const vec3& h, const vec3& s);

        //scalar post-multiplication
        friend constexpr vec3 operator*(const vec3& h, const float& s);

        //scalar pre-multiplication
        friend constexpr vec3 operator*(const float& s, const vec3& h);

        //scalar post-division
        friend constexpr vec3 operator/(const vec3& h, const float& s);

        //addition+assignemnt
        friend constexpr vec3& operator+=(vec3 &h, const vec3& s);
        
        //subtraction+assignemnt
        friend constexpr vec3& operator-=(vec3 &h, const vec3& s);
    
        //scalar multiplication+assignment
        friend constexpr vec3& operator*=(vec3& h, const float& s);
        
        //scalar division+assignment
        friend constexpr vec3& operator/=(vec3& h, const float& s);

        //negation operator 
        friend constexpr vec3 operator-(const vec3& h);

        //dot product
        friend constexpr float dot(const vec3& h, const vec3& s);

        //cross product
        friend constexpr vec3 cross(const vec3& h, const vec3& s);

        //angle between vectors, in radians
        friend constexpr float angle(const vec3& h, const vec3& s);

        //projection of h on s
        friend constexpr vec3 proj(const vec3& h, const vec3& s);

        //perpendicular projection
        friend constexpr vec3 perp(const vec3& h, const vec3& s);

    
        friend std::ostream& operator<<(std::ostream& out, const vec3& vect);

};

constexpr vec3 operator+(const vec3& h, const vec3& s){
            vec3 copy = h;
            copy += s;
            return copy;

        }

constexpr vec3 operator-(const vec3& h, const vec3& s){
            vec3 copy = h;
            copy -= s;
            return copy;
        }

constexpr vec3 operator*(const vec3& h, const float& s){
            vec3 copy = h;
            copy *= s;
            return copy;
        }

constexpr vec3 operator*(const float& s, const vec3& h){
            return h*s;
}

constexpr vec3 operator/(const vec3& h, const float& s){
            vec3 copy = h;
            copy /= s;
            return copy;
        }

constexpr vec3& operator+=(vec3& h, const vec3& s){
            h.x+=s.x;
            h.y+=s.y;
            h.z+=s.z;
            return h;
        }

constexpr vec3& operator-=(vec3 &h, const vec3& s){
            h.x-=s.x;
            h.y-=s.y;
            h.z-=s.z;
            return h;
        }

constexpr vec3& operator*=(vec3& h, const float& s){
            h.x*=s;
            h.y*=s;
            h.z*=s;
            return h;
        }

constexpr vec3& operator/=(vec3& h, const float& s){
            h.x/=s;
            h.y/=s;
            h.z/=s;
            return h;
        }

constexpr vec3 operator-(const vec3& h) {
            return h*(-1);
        }

constexpr float dot(const vec3& h, const vec3& s){
            return h.x*s.x+h.y*s.y+h.z*s.z;
        }

constexpr vec3 cross(const vec3& h, const vec3& s){
            return {h.y*s.z-h.z*s.y, h.z*s.x-h.x*s.z, h.x*s.y-h.y*s.x };
        }

constexpr float angle(const vec3& h, const vec3& s){
            float cos=(dot(h,s))/(h.norm()*s.norm());
            return acos(cos);
        }

constexpr vec3 proj(const vec3& h, const vec3& s){
            return s*(dot(h,s))/(s.norm()*s.norm());                       
        }

constexpr vec3 perp(const vec3& h, const vec3& s){
            return h - proj(h,s);
        }

std::ostream& operator<<(std::ostream& out, const vec3& vect){
            out<<"("<<vect.x<<","<<vect.y<<","<<vect.z<<")\n";
            return out;
        }

#endif
