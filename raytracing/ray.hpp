//
//  ray.h
//  learningC++
//
//  Created by John Szaniszlo on 1/9/22.
//

#ifndef ray_h
#define ray_h

#include "vec3.hpp"

class ray {
public:
    ray() {}
    ray(const point3 &origin, const vec3 &direction)
        : m_orig(origin), m_dir(direction)
    {}
    
    point3 origin() {return m_orig;}
    point3 direction() {return m_dir;}
    
    point3 at(double t) const {
        return m_orig + t * m_dir;
    }
    
public:
    point3 m_orig;
    vec3 m_dir;
};

#endif /* ray_h */
