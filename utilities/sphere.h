#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>

#include "hit_record.h"
#include "ray.h"
#include "vec3.h"

typedef struct sphere {
    point3 center;
    double radius;
} sphere;

static inline sphere sphere_new(point3 center, double radius) {
    sphere s = {center, fmax(radius, 0.0)};
    return s;
}

static inline bool sphere_hit(sphere s, ray r, double ray_tmin, double ray_tmax, hit_record *rec) {
    vec3 oc = vec3_sub(s.center, ray_origin(r));
    double a = vec3_length_squared(ray_direction(r));
    double h = dot(ray_direction(r), oc);
    double c = vec3_length_squared(oc) - s.radius * s.radius;
    double discriminant = h * h - a * c;
    if (discriminant < 0) {
        return false;
    }
    double sqrtd = sqrt(discriminant);
    double root = (h - sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root) {
        root = (h + sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root)
            return false;
    }

    rec->t = root;
    rec->p = ray_at(r, rec->t);
    vec3 normal = vec3_div(vec3_sub(rec->p, s.center), s.radius);
    set_face_normal(rec, r, normal);

    return true;
}

#endif /* ifndef SPHERE_H */
