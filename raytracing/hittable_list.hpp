//
//  hittable_list.hpp
//  raytracing
//
//  Created by John Szaniszlo on 1/9/22.
//

#ifndef hittable_list_h
#define hittable_list_h

#include "rtweekend.hpp"
#include "hittable.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
    // shared_ptr is ???
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) {add(object);}
    
    void clear() {m_objects.clear();}
    // pass in a shared_ptr to object and use the vector std function push_back to append to the end of the objects vector.
    void add(shared_ptr<hittable> object) {m_objects.push_back(object);}
    
    virtual bool hit(
        const ray& r, double t_min, double t_max, hit_record& rec) const override;
    
public:
    std::vector<shared_ptr<hittable>> m_objects;
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;
    
    for (const auto& object : m_objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    
    return hit_anything;
}

#endif /* hittable_list_h */
