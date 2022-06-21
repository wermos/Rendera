#ifndef VEC4_HPP
#define VEC4_HPP

#include <ostream>
#include <cmath>
#include <xsimd/xsimd.hpp>

#define ALPHA_ 0 //include alpha or not.

#if XSIMD_WITH_AVX512BW || XSIMD_WITH_AVX512DQ || XSIMD_WITH_AVX512F
    #define ALIGN_WIDTH 64
#elif XSIMD_WITH_FMA3_AVX2 || XSIMD_WITH_AVX2 || XSIMD_WITH_FMA3_AVX || XSIMD_WITH_AVX
    #define ALIGN_WIDTH 32
#elif XSIMD_WITH_SSE4_2 || XSIMD_WITH_SSE4_1 || XSIMD_WITH_SSSE3 || XSIMD_WITH_SSE3 || XSIMD_WITH_SSE2
    #define ALIGN_WIDTH 16
#endif

template<class T, class A = xsimd::default_arch>
class alignas(ALIGN_WIDTH) vec4{
    public:
        constexpr vec4() : m_v{0,0,0,0} {}
        constexpr vec4(T x) : m_v{x,x,x,x} {}
        constexpr vec4(T x,T y,T z) : m_v{x,y,z,0} {}
        constexpr vec4(T x,T y,T z,T a) : m_v{x,y,z,a} {}
        constexpr vec4(xsimd::batch<T,A> x){x.store_aligned(m_v);}
        
        //getters
        constexpr T x() const{
            return m_v[0];
        }

        constexpr T y() const{
            return m_v[1];
        }
        
        constexpr T z() const{
            return m_v[2];
        }

        constexpr T a() const{
            return m_v[3];
        }
        

        constexpr T dot(const vec4& v2,const bool alpha=ALPHA_) const{
            return m_v[0]*v2.m_v[0]+m_v[1]*v2.m_v[1]+m_v[2]*v2.m_v[2]+(m_v[3]*v2.m_v[3])*alpha;
        }
        
        constexpr T norm(const bool alpha=ALPHA_) const{ //__GNUC__
            return sqrt(dot(*this,alpha));
        }

        constexpr static T angle(const vec4& v1,const vec4& v2,const bool alpha=ALPHA_){//__GNUC__
            return acos(v1.dot(v2,alpha)/(v1.norm(alpha)*v2.norm(alpha)));
        }
        constexpr vec4 unit() const{//__GNUC__
            return *this/this->norm();
        }

        
        constexpr vec4 cross(const vec4& v2) const{ //ignoring the "alpha" channel
            return vec4(m_v[1] * v2.m_v[2] - m_v[2] * v2.m_v[1], m_v[2] * v2.m_v[0] - m_v[0] * v2.m_v[2],m_v[0] * v2.m_v[1] - m_v[1] * v2.m_v[0],0);
        }

        //vector addition
        friend constexpr vec4 operator+(const vec4& v1, const vec4& v2){
            return b2v(v2b(v1)+v2b(v2));
        }

        //vector subtraction
        friend constexpr vec4 operator-(const vec4& v1, const vec4& v2){
            return b2v(v2b(v1)-v2b(v2));
        }

        //scalar post-multiplication
        friend constexpr vec4 operator*(const vec4& v1, const T& s){
            return b2v(v2b(v1)*xsimd::batch<T,A>::broadcast(s));
        }

        //scalar pre-multiplication
        friend constexpr vec4 operator*(const T& s, const vec4& v1){
            return v1*s;
        }

        //scalar post-division
        friend constexpr vec4 operator/(const vec4& v1, const T& s){
            return v1*(1/double(s));
        }

        //addition+assignemnt
        friend constexpr vec4& operator+=(vec4& v1, const vec4& v2){
            v1=v1+v2;
            return v1;
        }
        
        //subtraction+assignemnt
        friend constexpr vec4& operator-=(vec4& v1, const vec4& v2){
            v1=v1-v2;
            return v1;
        }
    
        //scalar multiplication+assignment
        friend constexpr vec4& operator*=(vec4& v1, const float& s){
            v1=v1*s;
            return v1;
        }
        
        //scalar division+assignment
        friend constexpr vec4& operator/=(vec4& v1, const float& s){
            v1=v1/s;
            return v1;
        }

        //negation operator 
        friend constexpr vec4 operator-(const vec4& v1){
            return b2v(-v2b(v1));
        }

        //indexing operation
        constexpr T operator[](int i){
            return m_v[i];
        }
        
        //print the vector
        friend std::ostream& operator<<(std::ostream& out, const vec4& v) {
			out <<"("<< v.m_v[0] << "," << v.m_v[1] << "," << v.m_v[2]<<"," << v.m_v[3]<<")";
			return out;
		}

	private:
        T m_v[4];

        static constexpr xsimd::batch<T,A> v2b(const vec4& v){
            return  xsimd::batch<T,A>::load_aligned(v.m_v);
        }
        
        static constexpr vec4 b2v(xsimd::batch<T,A> x){
            vec4 v{x};
            return v;
        }

        static constexpr T sum(xsimd::batch<T,A> x){
            return xsimd::batch<T,A>::hadd(x);
        }
    

};

#endif
