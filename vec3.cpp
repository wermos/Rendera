#include "vec3.h"
#include<cmath>


vec3::vec3()
{
}


vec3::vec3(double x, double y, double z)
{
    this->a[0] = x;
    this->a[1] = y;
    this->a[2] = z;
}

vec3::vec3(double x)
{
    this->a[0] = x;
    this->a[1] = x;
    this->a[2] = x;
}

vec3::~vec3()
{
}


vec3 vec3::operator-()
{
    return vec3(-this->a[0], -this->a[1], -this->a[2]);
}


vec3 vec3::operator+(vec3 v)
{
    return vec3(v.a[0] + this->a[0], v.a[1] + this->a[1], v.a[2] + this->a[2]);
}


vec3 vec3::operator-(vec3 v)
{
    return (*this)+(-v);
}


vec3 vec3::operator*(double k)
{
    return vec3(k*this->a[0], k*this->a[1], k*this->a[2]);
}


vec3 vec3::operator*(vec3 v)
{
    vec3 cross;
    for(int i=0;i<VEC3SIZE;i++)
    {
        cross.a[i] = this->a[(i+1)%3]*v.a[(i+2)%3] - this->a[(i+2)%3]*v.a[(i+1)%3];
    }
    return cross;
}


double vec3::operator&(vec3 v)
{
    double sum = 0;
    for(int i=0;i<VEC3SIZE;i++)
    {
        sum += this->a[i]*v.a[i];
    }
    return sum;
}


double vec3::len()
{
    return std::sqrt((*this)&(*this));
}


vec3 vec3::unit()
{
    return (*this) * (1.0/this->len());
}


double vec3::operator[](int i)
{
    return this->a[i];
}


vec3 operator*(double k,vec3 v)
{
    return vec3(k*v[0], k*v[1], k*v[2]);
}


vec3 vec3::operator/(double k)
{
    return vec3(this->a[0]/k,this->a[1]/k,this->a[2]/k);
}


vec3& vec3::operator+=(vec3 v)
{
    for(int i=0;i<VEC3SIZE;i++)
    {
        this->a[i] += v.a[i];
    }
    return *this;
}


vec3& vec3::operator-=(vec3 v)
{
    for(int i=0;i<VEC3SIZE;i++)
    {
        this->a[i] -= v.a[i];
    }
    return *this;
}


vec3& vec3::operator*=(vec3 v)
{
    (*this) = (*this)*v;
    return *this;
}


vec3& vec3::operator*=(double k)
{
    for(int i=0;i<VEC3SIZE;i++)
    {
        this->a[i] *= k;
    }
    return *this;
}


vec3& vec3::operator/=(double k)
{
    for(int i=0;i<VEC3SIZE;i++)
    {
        this->a[i] /= k;
    }
    return *this;
}