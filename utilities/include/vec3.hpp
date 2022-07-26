#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <type_traits> // for std::is_constant_evaluated

#include <xsimd/xsimd.hpp>

#include "vec4.hpp"
#include "config.hpp"

class alignas(ALIGN_WIDTH) vec3 : public vec4{
    private:
                
        /*
        structs as_index,indices are used to generate appropriate xsimd::batch_constant 
        to be used for xsimd::swizzle function used inside cross product. 
        */
        template <typename T>
        struct as_index
        {
            using type = xsimd::as_unsigned_integer_t<T>;
        };
        struct indices
        {
            static constexpr unsigned int get(unsigned i, unsigned n)
            {
                if(i==n-1) return i;
                else return (i+1)%(n-1);
            }
        };

    public:
        constexpr explicit vec3(Utype x) : vec4{x,x,x,0} {}
        constexpr vec3(Utype x,Utype y,Utype z) : vec4{x,y,z,0} {}
        constexpr explicit vec3(xsimd::batch<Utype,UArch> x) : vec4{x} {}
        
        // cross-product
        constexpr vec3 cross(const vec3& v2) const{
            if (std::is_constant_evaluated()){
                return vec3((*this).y()*v2.z() - (*this).z()*v2.y(),
                            (*this).z()*v2.x() - (*this).x()*v2.z(),
                            (*this).x()*v2.y() - (*this).y()*v2.x());
            } else {    
                xsimd::batch<Utype,UArch> B0 = vec2batch(*this); 
                xsimd::batch<Utype,UArch> B1= vec2batch(v2);
                
                //create a appropriate mask for cross product.
                auto shuffler =  xsimd::make_batch_constant<typename as_index<xsimd::batch<float, xsimd::sse4_2>>::type, indices>();
                
                xsimd::batch<Utype,UArch> temp0 = xsimd::swizzle(B1,shuffler);
                xsimd::batch<Utype,UArch> temp1 = xsimd::swizzle(B0,shuffler);

                temp0 = temp0*B0;
                temp1 = temp1*B1;

                return vec3{xsimd::swizzle(temp0-temp1,shuffler)};
            }
        }

};

#endif
