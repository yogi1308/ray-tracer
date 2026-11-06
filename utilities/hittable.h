#ifndef HITTABLE_H
#define HITTABLE_H

#include "hit_record.h"
#include "sphere.h"
typedef enum hittable_type{ HITTABLE_SPHERE } hittable_type;
typedef struct hittable {
    hittable_type type;
    union {
        sphere sphere;
    } shape;
} hittable;

static inline hittable hittable_from_sphere(sphere s) {
    hittable h;
    h.type = HITTABLE_SPHERE;
    h.shape.sphere = s;
    return h;
}

static inline bool hittable_hit(const hittable *obj, ray r, double t_min, double t_max, hit_record *rec) {
    switch (obj->type) {
        case HITTABLE_SPHERE:
            return sphere_hit(obj->shape.sphere, r, t_min, t_max, rec);
    }
    return false;
}

#endif /* ifndef HITTABLE_H */
