#ifndef CONFIG_HPP
#define CONFIG_HPP

/*  - ALIGN_WIDTH: Sets according to dtype used. 32 for doubles and 16 for floates.
    - UArch: Architecture to be used.
    - UType: Dtype to be used.
    - CONSTEXPR_CMATH: Switch constexpr if available in cmath.

*/

#define ALIGN_WIDTH 16
typedef float Utype;
typedef xsimd::sse4_2 UArch;

#if defined(__GLIBCXX__) && __GLIBCXX__ >= 20210923L 
    #define CONSTEXPR_CMATH constexpr
#else
    #define CONSTEXPR_CMATH  
#endif 


#endif