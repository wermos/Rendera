//code by Ameya Vikrama Singh
#include<iostream>
#include<cmath>
class vec3{
    public:
        float x,y,z;

        vec3(){
            x=y=z=0;
        }

        //Cartesian coordinate Constructor
        vec3(float x,float y,float z){
            this->x=x;
            this->y=y;
            this->z=z;
        }
        
        //assignment operator
        void operator=(vec3 s){
            x=s.x;
            y=s.y;
            z=s.z;
        }

        //norm function
        float norm(){
            return sqrt(x*x+y*y+z*z);
        }

        //vector addition
        vec3 operator+(vec3 s){
            vec3 sum;
            sum.x=s.x+x;
            sum.y=s.y+y;
            sum.z=s.z+z;
            return sum;
        }

        //vector subtraction
        vec3 operator-(vec3 s){
            vec3 diff;
            diff.x=x-s.x;
            diff.y=y-s.y;
            diff.z=z-s.z;
            return diff;
        }

        //addition+assignemnt
        void operator+=(vec3 s){
            x+=s.x;
            y+=s.y;
            z+=s.z;
        }

        //subtraction+assignemnt
        void operator-=(vec3 s){
            x-=s.x;
            y-=s.y;
            z-=s.z;
        }

        //scalar post-multiplication
        vec3 operator*(float s){
            vec3 prod;
            prod.x=s*x;
            prod.y=s*y;
            prod.z=s*z;
            return prod;
        }

        //scalar post-division
        vec3 operator/(float s){
            return *this*(1/s);
        }

        //scalar multiplication+assignment
        void operator*=(float s){
            x*=s;
            y*=s;
            z*=s;
        }

        //dot product
        float operator*(vec3 s){
            return x*s.x+y*s.y+z*s.z;
        }

        //cross product, but dk which operator to use
        vec3 cross(vec3 s){
            vec3 cross;
            cross.x=y*s.z-z*s.y;
            cross.y=z*s.x-x*s.z;
            cross.z=x*s.y-y*s.x;
            return cross;
        }

        //angle between vectors, in radians
        float angle(vec3 s){
            float cos=(*this*s)/(norm()*s.norm());
            return acos(cos);
        }

        //projection of this on s
        vec3 proj(vec3 s){
            return s*(*this*s)/(s.norm()*s.norm());                       
        }

        //perpendicular projection
        vec3 perp(vec3 s){
            return *this - this->proj(s);
        }

        //print the vector
        void print(){
            std::cout<<"("<<x<<","<<y<<","<<z<<")\n";
        }

};

