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
        constexpr explicit vec4(T x) : m_v{x,x,x,x} {}
        constexpr vec4(T x,T y,T z) : m_v{x,y,z,0} {}
        constexpr vec4(T x,T y,T z,T w) : m_v{x,y,z,w} {}
        constexpr explicit vec4(xsimd::batch<T,A> x){x.store_aligned(m_v);}
        
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

        constexpr T w() const{
            return m_v[3];
        }
        
        //indexing operation
        constexpr T const & operator[](std::size_t i ) const{
            return m_v[i];
        }
        

        constexpr T dot(const vec4& v2) const{
            auto temp = v2b(*this)*v2b(v2);
            return sum(temp); //returns the sum of first 3 elements.
        }
        
        constexpr T norm(const bool alpha=ALPHA_) const{ //__GNUC__
            return sqrt(dot(*this));
        }

        constexpr static T angle(const vec4& v1,const vec4& v2,const bool alpha=ALPHA_){//__GNUC__
            return acos(v1.dot(v2)/(v1.norm(alpha)*v2.norm(alpha)));
        }
        constexpr vec4 unit() const{//__GNUC__
            return *this/this->norm();
        }

        
        constexpr vec4 cross(const vec4& v2) const{
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
            auto vs= xsimd::batch<T,A>::broadcast(s);
            return b2v(v2b(v1)*vs);
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

        //print the vector
        friend std::ostream& operator<<(std::ostream& out, const vec4& v) {
            
			out <<'('<< v.m_v[0] << ',' << v.m_v[1] << ',' << v.m_v[2]<<','<< v.m_v[3]<<')';
			return out;
		}

	private:
        T m_v[4];

        static constexpr xsimd::batch<T,A> v2b(const vec4& v){
            /*
            v2b: vector to batch 
            returns: a xsimd::batch object using aligned memory access. 
            */
            return  xsimd::batch<T,A>::load_aligned(v.m_v);
        }
        
        static constexpr vec4 b2v(xsimd::batch<T,A> x){
            /*
            b2v:batch to vector
            returns: a Vec4 object using aligned memory access. 
            */
            vec4 v{x};
            return v;
        }

        static constexpr T sum(xsimd::batch<T,A> x){ //nice alternative is xsimd::hadd but garbage vals.
            /*
            returns: sum of first 3 values.
            */
            auto b_temp=b2v(x);
            return b_temp[0]+b_temp[1]+b_temp[2];
        }
    

};

#endif
