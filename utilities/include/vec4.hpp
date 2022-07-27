#ifndef VEC4_HPP
#define VEC4_HPP

#include <cstddef>
#include <ostream>
#include <cmath> // for the std::size_t datatype
#include <type_traits> // for std::is_constant_evaluated

#include <xsimd/xsimd.hpp>

#include "config.hpp"
/*  *Macros provided by config.hpp
    - ALIGN_WIDTH: Alignment width for class, since it is dependent on Arch.
    - UArch: Architecture to be used.
    - UType: Data type to be used.
    - CONSTEXPR_CMATH: Switch constexpr if available in cmath.
*/

class alignas(ALIGN_WIDTH) vec4{
    
    public:
        constexpr vec4() : m_v{0,0,0,0} {}
        constexpr explicit vec4(Utype x) : m_v{x,x,x,x} {}
        constexpr vec4(Utype x,Utype y,Utype z,Utype w) : m_v{x,y,z,w} {}
        constexpr explicit vec4(xsimd::batch<Utype,UArch> x) : m_v{0,0,0,0} {store_aligned(m_v,x);}
        
        //getters
        constexpr Utype x() const{
            return m_v[0];
        }

        constexpr Utype y() const{
            return m_v[1];
        }
        
        constexpr Utype z() const{
            return m_v[2];
        }

        constexpr Utype w() const{
            return m_v[3];
        }
        
        //indexing operations
        constexpr const Utype& operator[](std::size_t i) const{
            return m_v[i];
        }

        constexpr Utype& operator[](std::size_t i){
            return m_v[i];
        }

        // Common Vec operations
        friend constexpr Utype dot(const vec4& v1,const vec4& v2){
            if (std::is_constant_evaluated()){
                return v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z() + v1.w()*v2.w() ;
            } else {    
                xsimd::batch<Utype,UArch> temp = vec2batch(v1)*vec2batch(v2);
                return sum(temp);
            }
        }
        
        CONSTEXPR_CMATH Utype norm() const{
            return std::sqrt(dot(*this,*this));
        }

        CONSTEXPR_CMATH static Utype angle(const vec4& v1,const vec4& v2){
            return std::acos(dot(v1,v2)/(v1.norm()*v2.norm()));
        }
        CONSTEXPR_CMATH vec4 unit() const{
            return *this/this->norm();
        }

        // Negation 
        friend constexpr vec4 operator-(const vec4& v1){
            if (std::is_constant_evaluated()){
                return vec4{-v1.x(),-v1.y(),-v1.z(),-v1.w()};
            } else {
                return vec4{-vec2batch(v1)};
            }
        }

        // Addition and Substraction
        friend constexpr vec4& operator+=(vec4& v1, const vec4& v2){
            if (std::is_constant_evaluated()){
            v1.m_v[0] += v2.x();
            v1.m_v[1] += v2.y();
            v1.m_v[2] += v2.z();
            v1.m_v[3] += v2.w();
            } else {
                xsimd::batch<Utype,UArch> b1 = vec2batch(v1);
                b1+=vec2batch(v2);
                v1= vec4{b1};
            }
            return v1;
        }

        friend constexpr vec4 operator+(const vec4& v1, const vec4& v2){
            vec4 v1_copy = v1;
            v1_copy+=v2;
            return v1_copy;
        }

        friend constexpr vec4 operator-(const vec4& v1, const vec4& v2){
            return v1+(-v2);
        }

        friend constexpr vec4& operator-=(vec4& v1, const vec4& v2){
            return v1+=-v2;
        }

        // Scalar Multiplication and Division
        // scalar post-multiplications
        friend constexpr vec4 operator*(const vec4& v1, const Utype& s){
            vec4 v1_copy = v1;
            v1_copy*=s;
            return v1_copy;
        }

        // scalar pre-multiplications
        friend constexpr vec4 operator*(const Utype& s, const vec4& v1){
            vec4 v1_copy = v1;
            v1_copy*=s;
            return v1_copy;
        }

        // scalar post-multiplication-assignment
        friend constexpr vec4& operator*=(vec4& v1, const Utype& s){
            if (std::is_constant_evaluated()){
                v1.m_v[0]*=s;
                v1.m_v[1]*=s;
                v1.m_v[2]*=s;
                v1.m_v[3]*=s;
            } else {
                xsimd::batch<Utype,UArch> vs= xsimd::batch<Utype,UArch>::broadcast(s);
                v1  = vec4(vec2batch(v1)*vs);
            }
            return v1;
        }
        
        // scalar post-division
        friend constexpr vec4 operator/(const vec4& v1, const Utype& s){
            return v1*(1/s);
        }

        // scalar division+assignment
        friend constexpr vec4& operator/=(vec4& v1, const Utype& s){
            v1*=1/s;
            return v1;
        }

        // print the vector
        friend std::ostream& operator<<(std::ostream& out, const vec4& v) {            
            out <<'('<< v.m_v[0] << ',' << v.m_v[1] << ',' << v.m_v[2]<<','<< v.m_v[3]<<')';
            return out;
		}
	
    protected:
        static xsimd::batch<Utype,UArch> vec2batch(const vec4& v){
            return  xsimd::batch<Utype,UArch>::load_aligned(v.m_v);
        }

        static Utype sum(xsimd::batch<Utype,UArch> x){
            return xsimd::hadd(x);
        }
    
    private:
        Utype m_v[4];

};

#endif
