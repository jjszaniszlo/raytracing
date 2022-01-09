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

#endif /* vec3_hpp */
