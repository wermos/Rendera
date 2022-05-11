
#define VEC3SIZE 3

class vec3
{
private:
    double a[VEC3SIZE];

public:
    vec3();
    vec3(double x, double y, double z);
    vec3(double x);

    //addition
    vec3 operator+(vec3 v);

    //subtraction
    vec3 operator-(vec3 v);

    //negation
    vec3 operator-();

    //scalar multiplication
    vec3 operator*(double k);

    //cross multiplication
    vec3 operator*(vec3 v);

    //scalar division 
    vec3 operator/(double k);

    //addition and assignment
    vec3& operator+=(vec3 v);

    //subtraction and assignment
    vec3& operator-=(vec3 v);

    //cross product and assignment
    vec3& operator*=(vec3 v);

    //scalar mul. and assignment
    vec3& operator*=(double k);

    //scalar div. and assignment
    vec3& operator/=(double k);

    //getting x,y,z component
    double operator[](int i);

    //vector length
    double len();

    //dot product
    double operator&(vec3 v);

    //unit vector
    vec3 unit();

    //destructor
    ~vec3();
};
