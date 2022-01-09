//
//  main.cpp
//  learningC++
//
//  Created by John Szaniszlo on 1/8/22.
//
#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include <iostream>


// use auto where ever something is initialized to make things easier and sometimes faster.
const auto IMG_W = 512;
const auto IMG_H = 512;

color ray_color(const ray& r)
{
    vec3 unit_direction = unit_vector(r.direction());
}

int main(int argc, const char * argv[]) {
    // Render
    for (auto j = IMG_H - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (auto i = 0; i < IMG_W; ++i)
        {
            color pixel_color(double(i) / (IMG_W - 1), double(j) / (IMG_H - 1), 0.25);
            write_color(std::cout, pixel_color);
            
//OLD            // auto - automatically deals with types.
//            auto r = double(i) / (IMG_W-1);
//            auto g = double(j) / (IMG_H-1);
//            auto b = 0.25;
//
//            // static_cast C++ style casts, try not to use C style or (int) kind.
//            // use static or dynamic casting for class types.
//            // static to be used where a runtime check is not necessary
//            auto ir = static_cast<int>(255.999 * r);
//            auto ig = static_cast<int>(255.999 * g);
//            auto ib = static_cast<int>(255.999 * b);
//
//            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\nDone.\n";
    return 0;
}
