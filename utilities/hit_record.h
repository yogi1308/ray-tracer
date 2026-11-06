#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "ray.h"
#include "vec3.h"
typedef struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
} hit_record;

static inline void set_face_normal(hit_record *rec, ray r, vec3 outward_normal) {
    rec->front_face = dot(ray_direction(r), outward_normal) < 0;
    rec->normal = rec->front_face ? outward_normal : vec3_negate(outward_normal);
}

#endif /* ifndef HIT_RECORD */
