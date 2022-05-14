#include<math.h>


template<typename T>
class Vec3{
    private:
        T x, y, z;
    public:
        Vec3() : x(T(0)), y(T(0)), z(T(0)) {}           
        Vec3(T xx) : x(xx), y(xx), z(xx) {}
        Vec3(T xx, T yy, T zz): x(xx), y(yy), z(zz) {}

        T getx(){return x;}
        T gety(){return y;}
        T getz(){return z;}
        void xin(T &xx){x = xx;}
        void yin(T &yy){y = yy;}
        void zin(T &zz){z = zz;}




        Vec3<T> operator * (const T &f){
            return Vec3<T>(x*f, y*f, z*f);
        }
        Vec3<T> operator * (const Vec3<T> &v){
            return Vec3<T>(x*v.x, y * v.y, z * v.z);
        }


        Vec3<T> operator - (const Vec3<T> &v){
            return Vec3<T>(x - v.x, y - v.y, z - v.z);
        }
        Vec3<T> operator + (const Vec3<T> &v){
            return Vec3<T>(x + v.x, y + v.y, z + v.z);
        }

        Vec3<T>& operator += (const Vec3<T> &v){
            x += v.x, y += v.y, z += v.z;
            return *this;
        }

        Vec3<T>& operator *= (const Vec3<T> &v){
            x *= v.x, y *= v.y, z *= v.z;
            return *this;
        }

        Vec3<T> operator -(){
            return Vec3<T>(-x, -y, -z);
        }

        void operator = (const Vec3<T> &v){
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }


        























        T length_sq(){
            return x*x + y*y + z*z;
        }
        T length(){
            return sqrt(length_sq());
        }
        T dot(const Vec3<T> &v){
            return x * v.x + y * v.y + z * v.z;
        }
        Vec3<T> unit(){
            T l = length();
            return Vec3<T>(x/l, y/l, z/l);
        }

        void convt_unit(){
            T l = length();
            x = x/l; y = y/l; z = z/l;
        }

        Vec3<T> proj_on(Vec3<T> &v){
            Vec3<T> uv = v.unit();
            return uv*(this->dot(uv));
        }

        Vec3<T> perp_proj_on(Vec3<T> &v){
            return *this - this->proj_on(v);
        }

        T angle(Vec3<T> &v){
            return acos((this->unit()).dot(v.unit()));
        }









        void print(){
            std::cout<<x<<" "<<y<<" "<<z<<std::endl;
        }

};


typedef Vec3<float> Vec3f; 