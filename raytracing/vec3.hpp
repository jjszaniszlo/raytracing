//
//  vec3.hpp
//  learningC++
//
//  Created by John Szaniszlo on 1/8/22.
//

#ifndef vec3_hpp
#define vec3_hpp

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3
{
public:
    // the colon makes an initialization list, where the double array m_vec gets 0'd
    vec3() : m_vec{0, 0, 0} {}
    // overloaded constructor which allows us to pass in vector numbers to the underlying member array.
    vec3(double v0, double v1, double v2) : m_vec{v0, v1, v2} {}
    
    // const here, tells the compiler that the function will leave the instance unchanged.
    double x() const {return m_vec[0];}
    double y() const {return m_vec[1];}
    double z() const {return m_vec[2];}
    
    // operator overload for -
    vec3 operator-() const {return vec3(-m_vec[0], -m_vec[1], -m_vec[2]);}
    // operator overload for accessing the array through [].
    double operator[](int i) const {return m_vec[i];}
    // operator overload for accessing the array that returns a reference.
    // References can be used to directly modify the m_vec array.
    // given a vec3 instance named 'vec' u can do ++vec[2]; to increment the 3rd value in the m_vec array.
    double& operator[](int i) {return m_vec[i];}
    
    // Operator overloading for +=.  Note that it returns a pointer to the instance which called it.
    vec3& operator+=(const vec3 &v)
    {
        m_vec[0] += v.m_vec[0];
        m_vec[1] += v.m_vec[1];
        m_vec[2] += v.m_vec[2];
        return *this;
    }
    
    vec3& operator*=(const double t)
    {
        m_vec[0] *= t;
        m_vec[1] *= t;
        m_vec[2] *= t;
        return *this;
    }
    // Uses the previouslly overloaded *= operator to do the dvision.  clever.
    vec3& operator/=(const double t)
    {
        return *this *= 1/t;
    }
    
    // using const to tell compiler that this doesn't modify the class member variables.
    double length() const
    {
        return sqrt(length_squared());
    }
    
    double length_squared() const
    {
        return m_vec[0]*m_vec[0] + m_vec[1]*m_vec[1] + m_vec[2]*m_vec[2];
    }
    inline static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) {
        return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }
    bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (fabs(m_vec[0]) < s) && (fabs(m_vec[1]) < s) && (fabs(m_vec[2]) < s);
    }
public:
    double m_vec[3];
};

// type aliases for vec3

using point3 = vec3;
using color = vec3;

// vec3 utility

// inline means that compiler does optimal things with this code. \0_0/
// operator overload for << operator.
// when u do an instance of std::cout << vec << std::endl; this will print it nicely.
inline std::ostream& operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.m_vec[0] << ' ' << v.m_vec[1] << ' ' << v.m_vec[2] << ' ';
}

inline vec3 operator+(const vec3 u, const vec3 v)
{
    return vec3(u.m_vec[0] + v.m_vec[0], u.m_vec[1] + v.m_vec[1], u.m_vec[2] + v.m_vec[2]);
}

inline vec3 operator-(const vec3 u, const vec3 v)
{
    return vec3(u.m_vec[0] - v.m_vec[0], u.m_vec[1] - v.m_vec[1], u.m_vec[2] - v.m_vec[2]);
}

inline vec3 operator*(const vec3 u, const vec3 v)
{
    return vec3(u.m_vec[0] * v.m_vec[0], u.m_vec[1] * v.m_vec[1], u.m_vec[2] * v.m_vec[2]);
}

inline vec3 operator*(double t, const vec3 v)
{
    return vec3(t * v.m_vec[0], t * v.m_vec[1], t * v.m_vec[2]);
}

inline vec3 operator*(const vec3 u, double t)
{
    return t * u;
}

inline vec3 operator/(vec3 u, double t)
{
    return (1 / t) * u;
}

inline double dot(const vec3 &u, const vec3 &v)
{
    return  u.m_vec[0] * v.m_vec[0] +
            u.m_vec[1] * v.m_vec[1] +
            u.m_vec[2] * v.m_vec[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.m_vec[1] * v.m_vec[2] - u.m_vec[2] * v.m_vec[1],
                u.m_vec[2] * v.m_vec[0] - u.m_vec[0] * v.m_vec[2],
                u.m_vec[0] * v.m_vec[1] - u.m_vec[1] * v.m_vec[0]);
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif /* vec3_hpp */
