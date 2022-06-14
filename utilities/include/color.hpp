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

        friend constexpr color& int2float(color& c1);

        //adding colors
        friend constexpr color operator+(const color& c1, const color& c2);

        //multiplying colors(elementwise)
        friend constexpr color operator*(const color& c1, const color& c2);

        //multiplying by scalar
        friend constexpr color operator*(const color& c1, const float& s);
        friend constexpr color operator*(const float& s, const color& c1);

        //compound assignments
        friend constexpr color& operator+=(color& c1, const color& c2);
        friend constexpr color& operator*=(color& c1, const color& c2);
        friend constexpr color& operator*=(color& c1, const float& s);
};

constexpr color& float2int(color& c1){
    c1.r = int(255*c1.r);
    c1.g = int(255*c1.g);
    c1.b = int(255*c1.b);
    return c1;
}

constexpr color& int2float(color& c1){
    c1.r /= 255.0;
    c1.g /= 255.0;
    c1.b /= 255.0;
    return c1;
}

constexpr color operator+(const color& c1, const color& c2){
    color copy = c1;
    copy += c2;
    return copy;
}

constexpr color operator*(const color& c1, const color& c2){
    color copy = c1;
    copy *= c2;
    return copy;
}

constexpr color operator*(const color& c1, const float& c2){
    color copy = c1;
    copy *= c2;
    return copy;
}

constexpr color operator*(const float& s, const color& c1){
    color copy = c1;
    copy *= s;
    return copy;
}

constexpr color& operator+=(color& c1, const color& c2){
    c1.r += c2.r;
    c1.g += c2.g;
    c1.b += c2.b;
    return c1;
}

constexpr color& operator*=(color& c1, const color& c2){
    c1.r *= c2.r;
    c1.g *= c2.r;
    c1.b *= c2.b;
    return c1;
}

constexpr color& operator*=(color& c1, const float& s){
    c1.r *= s; 
    c1.g *= s;
    c1.b *= s;
    return c1;
}




#endif
