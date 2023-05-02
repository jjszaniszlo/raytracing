//
//  main.cpp
//  learningC++
//
//  Created by John Szaniszlo on 1/8/22.
//
#include "rtweekend.hpp"

#include "camera.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "sphere.hpp"

#include <iostream>
color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;
    
    // recursive base case.
    if (depth <= 0)
        return color(0,0,0);
    
    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main(int argc, const char * argv[]) {
    // Image
    // use auto where ever something is initialized to make things easier and sometimes faster.
    const auto ASPECT_RATIO = 16.0 / 9.0;
    const auto IMG_W = 1920;
    const auto IMG_H = static_cast<int>(IMG_W / ASPECT_RATIO);
    const auto SAMPLES_PP = 10;
    const auto MAX_DEPTH = 3;
    
    // World
    hittable_list world;
    
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<dielectric>(1.5);
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    
    //Camera
    camera cam;
    
    // Render
    std::cout << "P3\n" << IMG_W << " " << IMG_H << "\n255\n";
    
    for (auto j = IMG_H - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (auto i = 0; i < IMG_W; ++i)
        {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < SAMPLES_PP; ++s) {
                auto u = (i + random_double()) / (IMG_W-1);
                auto v = (j + random_double()) / (IMG_H-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, MAX_DEPTH);
            }
            write_color(std::cout, pixel_color, SAMPLES_PP);
            
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
