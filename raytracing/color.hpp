//
//  color.h
//  learningC++
//
//  Created by John Szaniszlo on 1/9/22.
//

#ifndef color_h
#define color_h

#include "vec3.hpp"
#include <iostream>

// Write color to the ostream buffer.
void write_color(std::ostream &out, color pixel_color)
{
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif /* color_h */
