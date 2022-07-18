#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <cmath>

#include "vec4.hpp"
#include "config.hpp"

template <class T>
struct as_index
{
    using type = xsimd::as_unsigned_integer_t<T>;
};

struct indices
{
    static constexpr unsigned get(unsigned i, unsigned n)
    {
        if(i==n-1) return i;
        else return (i+1)%(n-1);
    }
};



class alignas(ALIGN_WIDTH) Vec3 : public Vec4{

    public:
        constexpr Vec3(Utype x,Utype y,Utype z) : Vec4{x,y,z,0} {}
        constexpr explicit Vec3(xsimd::batch<Utype,UArch> x) : Vec4{x} {}
        
        // cross-product
        constexpr Vec3 cross(const Vec3& v2) const{

            auto B0 = v2b(*this); 
            auto B1= v2b(v2);

            auto shuffler =  xsimd::make_batch_constant<typename as_index<xsimd::batch<float, xsimd::sse4_2>>::type, indices>();

            auto _temp0 = xsimd::swizzle(B1,shuffler);
            auto _temp1 = xsimd::swizzle(B0,shuffler);

            _temp0 = _temp0*B0;
            _temp1 = _temp1*B1;

            return b2vec3(xsimd::swizzle(_temp0-_temp1,shuffler));
        }

    private:
        static constexpr Vec3 b2vec3(xsimd::batch<Utype,UArch> x){
            Vec3 v{x};
            return v;
        }



};

#endif
