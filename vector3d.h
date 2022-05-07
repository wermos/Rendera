//3d vector class for Rendera, Yashas M Salian

#include<math.h>

class vec3
{
private:
    float x, y, z;    //Components of vector are kept private
public:
    void xinput(float xin)    //functions used to input x, y, z
    {
        x = xin;
    }   
    
    void yinput(float yin)
    {
        y = yin;
    } 
    
    void zinput(float zin)
    {
        z = zin;
    }
    
    float getx()    //functions used to obtain the stored values of x, y, z
    {
        return x;
    }
    
    float gety()
    {
        return y;
    }
    
    float getz()
    {
        return z;
    }
    
    vec3 unitvect(vec3 vect)    //used to obtain unit vector in the direction of the vector vect
    {
        float mag;
        vec3 unit;
        mag = sqrt(vect.getx() * vect.getx() + vect.gety() * vect.gety() + vect.getz() * vect.getz());
        unit.xinput(vect.getx() / mag);
        unit.yinput(vect.gety() / mag);
        unit.zinput(vect.getz() / mag);
        return unit;
    }
    
    vec3 operator + (vec3 vect)    //overloading + for vector addition
    {
        vec3 sum;
        sum.xinput(x + vect.getx());
        sum.yinput(y + vect.gety());
        sum.zinput(z + vect.getz());
        return sum;
    }
    
    vec3 operator - (vec3 vect)    //overloading - for vector subtraction
    {
        vec3 diff;
        diff.xinput(x - vect.getx());
        diff.yinput(y - vect.gety());
        diff.zinput(z - vect.getz());
        return diff;
    }
    
    float operator * (vec3 vect)    //overloading * for dot product
    {
        float dot = x * vect.getx() + y * vect.gety() + z * vect.getz();
        return dot;
    }
    
    vec3 operator % (vec3 vect)    //overloading % for cross product
    {
        vec3 cross;
        cross.xinput(y * vect.getz() - z * vect.gety());
        cross.yinput(z * vect.getx() - x * vect.getz());
        cross.zinput(x * vect.gety() - y * vect.getx());
        return cross;
    }
};
