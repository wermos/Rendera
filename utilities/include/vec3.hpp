#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <cmath>

#include "vec4.hpp"
#include "config.hpp"

class alignas(ALIGN_WIDTH) Vec3 : public Vec4{
    
    private:
                
        /*
        structs as_index,indices are used to generate appropriate xsimd::batch_constant 
        to be used for xsimd::swizzle function used inside cross product. 
        */
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

        static constexpr Vec3 batch2vec3(xsimd::batch<Utype,UArch> x){
            Vec3 v{x};
            return v;
        }

    public:
        constexpr Vec3(Utype x,Utype y,Utype z) : Vec4{x,y,z,0} {}
        constexpr explicit Vec3(xsimd::batch<Utype,UArch> x) : Vec4{x} {}
        
        // cross-product
        constexpr Vec3 cross(const Vec3& v2) const{

            xsimd::batch<Utype,UArch> B0 = vec2batch(*this); 
            xsimd::batch<Utype,UArch> B1= vec2batch(v2);
            
            //create a appropriate mask for cross product.
            auto shuffler =  xsimd::make_batch_constant<typename as_index<xsimd::batch<float, xsimd::sse4_2>>::type, indices>();
            
            xsimd::batch<Utype,UArch> temp0 = xsimd::swizzle(B1,shuffler);
            xsimd::batch<Utype,UArch> temp1 = xsimd::swizzle(B0,shuffler);

            temp0 = temp0*B0;
            temp1 = temp1*B1;

            return batch2vec3(xsimd::swizzle(temp0-temp1,shuffler));
        }



};

#endif
