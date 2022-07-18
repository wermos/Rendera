#ifndef VEC4_HPP
#define VEC4_HPP

#include <cstddef>
#include <ostream>
#include <cmath>
#include <xsimd/xsimd.hpp>

#include "config.hpp"

class alignas(ALIGN_WIDTH) Vec4{
    
    public:
        constexpr Vec4() : m_v{0,0,0,0} {}
        constexpr explicit Vec4(Utype x) : m_v{x,x,x,x} {}
        constexpr Vec4(Utype x,Utype y,Utype z,Utype w) : m_v{x,y,z,w} {}
        constexpr explicit Vec4(xsimd::batch<Utype,UArch> x): m_v{0,0,0,0} {x.store_aligned(m_v);}
        
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
        // constexpr Utype& operator[](std::size_t i) const{
        //     return m_v[i];
        // }
        
        constexpr Utype operator[](std::size_t i) const{
            return m_v[i];
        }

        // Common Vec operations
        constexpr Utype dot(const Vec4& v2) const{
            xsimd::batch<Utype,UArch> temp = vec2batch(*this)*vec2batch(v2);
            return sum(temp);
        }
        
        CONSTEXPR_CMATH Utype norm() const{
            return sqrt(dot(*this));
        }

        CONSTEXPR_CMATH static Utype angle(const Vec4& v1,const Vec4& v2){
            return acos(v1.dot(v2)/(v1.norm()*v2.norm()));
        }
        CONSTEXPR_CMATH Vec4 unit() const{
            return *this/this->norm();
        }

        // negation operator 
        friend constexpr Vec4 operator-(const Vec4& v1){
            return batch2vec4(-vec2batch(v1));
        }

        // Addition and Substraction
        friend constexpr Vec4& operator+=(Vec4& v1, const Vec4& v2){
            xsimd::batch<Utype,UArch> b1 = vec2batch(v1);
            b1+=vec2batch(v2);
            v1= batch2vec4(b1);
            return v1;
        }

        friend constexpr Vec4 operator+(const Vec4& v1, const Vec4& v2){
            Vec4 v1c = v1;
            v1c+=v2;
            return v1c;
        }

        friend constexpr Vec4 operator-(const Vec4& v1, const Vec4& v2){
            return v1+(-v2);
        }

        friend constexpr Vec4& operator-=(Vec4& v1, const Vec4& v2){
            return v1+=-v2;
        }

        // Scalar Multiplication and Division
        // scalar post-multiplications
        friend constexpr Vec4 operator*(const Vec4& v1, const Utype& s){
            Vec4 v1c = v1;
            v1c*=s;
            return v1c;
        }

        // scalar pre-multiplications
        friend constexpr Vec4 operator*(const Utype& s, const Vec4& v1){
            xsimd::batch<Utype,UArch> vs= xsimd::batch<Utype,UArch>::broadcast(s);
            Vec4 v1c = v1;
            v1c*=s;
            return v1c;
        }

        // scalar post-multiplication-assignment
        friend constexpr Vec4& operator*=(Vec4& v1, const Utype& s){
            xsimd::batch<Utype,UArch> vs= xsimd::batch<Utype,UArch>::broadcast(s);
            v1  = batch2vec4(vec2batch(v1)*vs);
            return v1;
        }
        
        // scalar post-division
        friend constexpr Vec4 operator/(const Vec4& v1, const Utype& s){
            return v1*(1/s);
        }

        // scalar division+assignment
        friend constexpr Vec4& operator/=(Vec4& v1, const Utype& s){
            v1*=1/s;
            return v1;
        }


        // print the vector
        friend std::ostream& operator<<(std::ostream& out, const Vec4& v) {
            
			out <<'('<< v.m_v[0] << ',' << v.m_v[1] << ',' << v.m_v[2]<<','<< v.m_v[3]<<')';
			return out;
		}
	
    protected:
        static constexpr xsimd::batch<Utype,UArch> vec2batch(const Vec4& v){
            return  xsimd::batch<Utype,UArch>::load_aligned(v.m_v);
        }
        
        static constexpr Vec4 batch2vec4(xsimd::batch<Utype,UArch> x){
            Vec4 v{x};
            return v;
        }

        static constexpr Utype sum(xsimd::batch<Utype,UArch> x){
            return xsimd::hadd(x);
        }
    
    private:
        Utype m_v[4];


};

#endif
