#ifndef VEC3_HPP
#define VEC3_HPP


#include <iostream>
#include <cmath>
class vec3{
    float x,y,z;
    public:
        constexpr vec3() : x {0}, y {0}, z {0} {}

        //Cartesian coordinate Constructor
        constexpr vec3(float X,float Y,float Z) : x {X}, y {Y}, z {Z} {}

        //norm function
        constexpr float norm() const {
            return sqrt(x * x + y * y + z * z);
        }

        //unit vector function
        constexpr vec3 unit() const{
            return *this/this->norm();
        }

        //getters
        constexpr float get_X() const{
            return x;
        }

        constexpr float get_Y() const{
            return y;
        }
        
        constexpr float get_Z() const{
            return z;
        }

        //vector addition
        friend constexpr vec3 operator+(const vec3& v1, const vec3& v2);

        //vector subtraction
        friend constexpr vec3 operator-(const vec3& v1, const vec3& v2);

        //scalar post-multiplication
        friend constexpr vec3 operator*(const vec3& v1, const float& s);

        //scalar pre-multiplication
        friend constexpr vec3 operator*(const float& s, const vec3& v1);

        //scalar post-division
        friend constexpr vec3 operator/(const vec3& v1, const float& s);

        //addition+assignemnt
        friend constexpr vec3& operator+=(vec3& v1, const vec3& v2);
        
        //subtraction+assignemnt
        friend constexpr vec3& operator-=(vec3& v1, const vec3& v2);
    
        //scalar multiplication+assignment
        friend constexpr vec3& operator*=(vec3& v1, const float& s);
        
        //scalar division+assignment
        friend constexpr vec3& operator/=(vec3& v1, const float& s);

        //negation operator 
        friend constexpr vec3 operator-(const vec3& v1);

        //dot product
        friend constexpr float dot(const vec3& v1, const vec3& v2);

        //cross product
        friend constexpr vec3 cross(const vec3& v1, const vec3& v2);

        //angle between vectors, in radians
        friend constexpr float angle(const vec3& v1, const vec3& v2);

        //projection of h on s
        friend constexpr vec3 proj(const vec3& v1, const vec3& v2);

        //perpendicular projection
        friend constexpr vec3 perp(const vec3& v1, const vec3& v2);

    
        friend std::ostream& operator<<(std::ostream& out, const vec3& vect);

};

constexpr vec3 operator+(const vec3& v1, const vec3& v2){
    vec3 copy = v1;
    copy += v2;
    return copy;

}

constexpr vec3 operator-(const vec3& v1, const vec3& v2){
    vec3 copy = v1;
    copy -= v2;
    return copy;
}

constexpr vec3 operator*(const vec3& v1, const float& v2){
    vec3 copy = v1;
    copy *= v2;
    return copy;
}

constexpr vec3 operator*(const float& s, const vec3& v1){
    return v1*s;
}

constexpr vec3 operator/(const vec3& v1, const float& s){
    vec3 copy = v1;
    copy /= s;
    return copy;
}

constexpr vec3& operator+=(vec3& v1, const vec3& v2){
    v1.x+=v2.x;
    v1.y+=v2.y;
    v1.z+=v2.z;
    return v1;
}

constexpr vec3& operator-=(vec3& v1, const vec3& v2){
    v1.x-=v2.x;
    v1.y-=v2.y;
    v1.z-=v2.z;
    return v1;
}

constexpr vec3& operator*=(vec3& v1, const float& s){
    v1.x*=s;
    v1.y*=s;
    v1.z*=s;
    return v1;
}

constexpr vec3& operator/=(vec3& v1, const float& s){
    v1.x/=s;
    v1.y/=s;
    v1.z/=s;
    return v1;
}

constexpr vec3 operator-(const vec3& v1) {
    return v1*(-1);
}

constexpr float dot(const vec3& v1, const vec3& v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

constexpr vec3 cross(const vec3& v1, const vec3& v2){
    return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

constexpr float angle(const vec3& v1, const vec3& v2){
    float cos=(dot(v1,v2))/(v1.norm()*v2.norm());
    return acos(cos);
}

constexpr vec3 proj(const vec3& v1, const vec3& v2){
    return v2*(dot(v1,v2))/(v2.norm()*v2.norm());                       
}

constexpr vec3 perp(const vec3& v1, const vec3& v2){
    return v1 - proj(v1,v2);
}

std::ostream& operator<<(std::ostream& out, const vec3& vect){
    out<<"("<<vect.x<<","<<vect.y<<","<<vect.z<<")\n";
    return out;
}

#endif
