#ifndef VEC4_HPP
#define VEC4_HPP


#include <iostream>
#include <cmath>
#define ALPHA_ 0
//include alpha channel into calculations?
#define ALIGN_WIDTH 32
//currently aligned for double and avx
//create macros for alignas func. set to 32. <double,xsimd::avx>


template<class T, class A = xsimd::default_arch>

class alignas(ALIGN_WIDTH) vec4{
    public:
        vec4() : m_v{0,0,0,0} {}
        vec4(T x) : m_v{x,x,x,x} {}
        vec4(T x,T y,T z,T a) : m_v{x,y,z,a} {}
        vec4(xsimd::batch<T,A> x){x.store_aligned(m_v);}
        
        //getters
        T x() const{
            return m_v[0];
        }

        T y() const{
            return m_v[1];
        }
        
        T z() const{
            return m_v[2];
        }

        T a() const{
            return m_v[3];
        }
        

        T dot(const vec4& v2,const bool alpha=ALPHA_) const{
            return m_v[0]*v2.m_v[0]+m_v[1]*v2.m_v[1]+m_v[2]*v2.m_v[2]+(m_v[3]*v2.m_v[3])*alpha;
        }
        
        T norm(const bool alpha=ALPHA_) const{
            return sqrt(dot(*this,alpha));
        }

        static T angle(const vec4& v1,const vec4& v2,const bool alpha=ALPHA_){
            return acos(v1.dot(v2,alpha)/(v1.norm(alpha)*v2.norm(alpha)));
        }
        vec4 unit() const{
            return *this/this->norm();
        }

        
        vec4 cross(const vec4& v2) const{ //ignoring the "alpha" channel
            return vec4(m_v[1] * v2.m_v[2] - m_v[2] * v2.m_v[1], m_v[2] * v2.m_v[0] - m_v[0] * v2.m_v[2],m_v[0] * v2.m_v[1] - m_v[1] * v2.m_v[0],0);
        }

        
        friend std::ostream& operator<<(std::ostream& out, const vec4& v) {
			out <<"("<< v.m_v[0] << "," << v.m_v[1] << "," << v.m_v[2]<<"," << v.m_v[3]<<")\n";
			return out;
		}

	private:
	T m_v[4];

	xsimd::batch<T,A> v2b(){
        auto b = xsimd::load_aligned(m_v);
        return b;
    }
    
    void b2v(xsimd::batch<T,A> x){
        x.store_aligned(m_v);
    }

    static T sum(const vec4& v,const bool alpha=ALPHA_){
        return v.m_v[0]+v.m_v[1]+v.m_v[2]+(v.m_v[4])*alpha;
    }
    

};

//overload [] operator

#endif
