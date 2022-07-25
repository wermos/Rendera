#include <iostream>
#include "vec4.hpp"
#include "vec3.hpp"

int main() {
	Vec3 v{3,-3,1};
    Vec3 v2{4,9,2};
    Vec4 v3{1};
    std::cout<<v3<<'\n';
	std::cout<<v<<" "<<v2<<'\n';
    std::cout<<"v.norm(): "<<v.norm()<<'\n';
    std::cout<<"v.dot(v): "<<v.dot(v)<<'\n';
    std::cout<<"v.dot(v2): "<<v.dot(v2)<<'\n'; //dot(v1,v2)
    std::cout<<"v.cross(v2): "<<v.cross(v2)<<'\n';
    //std::cout<<"angle(v,v2): "<<vec4<double,xsimd::avx2>::angle(v,v2)<<'\n';
    
    std::cout<<"v+v2: "<<v+v2<<'\n';
    std::cout<<"v-v2: "<<v-v2<<'\n';
    std::cout<<"v*2: "<<v*2<<'\n';
    std::cout<<"v/2: "<<v/2.0<<'\n';

    v+=v2;
    std::cout<<"v: "<<v<<'\n';
    std::cout<<"-v:"<<-v<<'\n';

    for(int i=0;i<4;i++){
        std::cout<<v[i]<<'\n';
    }
    xsimd::batch<double, xsimd::avx2> a{1.5, 2.5, 3.5, 4.5};
    xsimd::batch<double, xsimd::avx2> b{2.5, 3.5, 4.5, 5.5};
    //auto bleh = a*b;
    a*=b;
    std::cout<<a<<'\n';
    // xsimd::batch<double, xsimd::avx2> c{2.5};
    // std::cout<<xsimd::batch<double, xsimd::avx2>::broadcast(2.5)<<'\n';
    // possible fuck up
    // float alignas(32) m_v[4]={1.5, 2.5, 3.5, 4.5};
    // auto x = xsimd::load_aligned(m_v);

    // std::cout<<x<<'\n';
    // std::cout<<hadd(x)<<'\n';

    std::cout<<"cross-product-baby"<<std::endl;


    xsimd::batch<float, xsimd::sse4_2> B1{3,-3,1,0};
    xsimd::batch<float, xsimd::sse4_2> B0{4,9,2,0};

    auto shuffler =  xsimd::make_batch_constant<typename as_index<xsimd::batch<float, xsimd::sse4_2>>::type, indices>();

    auto _temp0 = xsimd::swizzle(B1,shuffler);
    auto _temp1 = xsimd::swizzle(B0,shuffler);

    _temp0 = _temp0*B0;
    _temp1 = _temp1*B1;
    auto _temp2 = _temp0-_temp1;
    
    std::cout<<B0<<std::endl;
    std::cout<<B1<<std::endl;
    std::cout<<xsimd::swizzle(_temp2,shuffler);
  
//    std::cout<<xsimd::swizzle(gg,gg2, xsimd::requires_arch<sse4_2>);
    
    //batch<float, xsimd::sse4_2> swizzle(batch<float, xsimd::sse4_2> const& self, batch_constant<batch<uint32_t, A>, V0, V1, V2, V3>, requires_arch<sse2>)
    
    return 0;
}
