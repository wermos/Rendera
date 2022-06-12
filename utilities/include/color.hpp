#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

class color{
    //color components as floats from 0 to 1
    float r,g,b;

    public:
        //Constructors
        constexpr color() : r {0}, g {0}, b {0} {};
        constexpr color(float R, float G, float B) : r{R}, g{G}, b{B} {};

        //getters
        float get_R() const{
            return r;
        }

        float get_G() const{
            return g;
        }

        float get_B() const{
            return b;
        }

        //return 8 bit int values
        constexpr color get_int() const{
            return {int(255*r), int(255*g), int(255*b)};
        }

        //converts values
        friend constexpr color& float2int(color& c1);

        friend constexpr color& int2float(color& h);

        //adding colors
        friend constexpr color operator+(const color& h, const color& s);

        //multiplying colors(elementwise)
        friend constexpr color operator*(const color& h, const color& s);

        //multiplying by scalar
        friend constexpr color operator*(const color& h, const float& s);
        friend constexpr color operator*(const float& s, const color& h);

        //compound assignments
        friend constexpr color& operator+=(color& h, const color& s);
        friend constexpr color& operator*=(color& h, const color& s);
        friend constexpr color& operator*=(color& h, const float& s);
};

constexpr color& float2int(color& h){
    h.r = int(255*h.r);
    h.g = int(255*h.g);
    h.b = int(255*h.b);
    return h;
}

constexpr color& int2float(color& h){
    h.r /= 255.0;
    h.g /= 255.0;
    h.b /= 255.0;
    return h;
}

constexpr color operator+(const color& h, const color& s){
    color copy = h;
    copy += s;
    return copy;
}

constexpr color operator*(const color& h, const color& s){
    color copy = h;
    copy *= s;
    return copy;
}

constexpr color operator*(const color& h, const float& s){
    color copy = h;
    copy *= s;
    return copy;
}

constexpr color operator*(const float& s, const color& h){
    color copy = h;
    copy *= s;
    return copy;
}

constexpr color& operator+=(color& h, const color& s){
    h.r += s.r;
    h.g += s.g;
    h.b += s.b;
    return h;
}

constexpr color& operator*=(color& h, const color& s){
    h.r *= s.r;
    h.g *= s.r;
    h.b *= s.b;
    return h;
}

constexpr color& operator*=(color& h, const float& s){
    h.r *= s; 
    h.g *= s;
    h.b *= s;
    return h;
}




#endif
