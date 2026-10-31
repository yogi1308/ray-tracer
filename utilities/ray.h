#ifndef RAY_H
#define RAY_H

#include <math.h>

#include "color.h"
#include "vec3.h"

typedef struct ray {
    point3 origin;
    vec3 dir;
} ray;

/// Build a ray from origin and direction (direction need not be normalized).
static inline ray ray_new(point3 origin, vec3 direction) {
    ray r = {origin, direction};
    return r;
}

static inline point3 ray_origin(ray r) { return r.origin; }

static inline vec3 ray_direction(ray r) { return r.dir; }

/// Point at origin + t*dir. t is scaled by |dir|, so it is only a distance
/// when the direction is normalized.
static inline point3 ray_at(ray r, double t) { return vec3_add(r.origin, vec3_scale(t, r.dir)); }

static inline double hit_sphere(vec3 center, double radius, ray r) {
    // vector from ray origin to sphere center
    vec3 oc = vec3_sub(center, ray_origin(r));
    // refer to NOTES.md to see how a,b,c were derived
    double a = dot(ray_direction(r), ray_direction(r));
    double b = -2.0 * dot(ray_direction(r), oc);
    double c = dot(oc, oc) - radius * radius;

    // Discriminant b^2 - 4ac: < 0 means no hit, 0 means touches once, > 0 means passes through twice.
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

static inline color ray_color(ray r) {
    // hit_sphere returns where on the ray the sphere was hit
    double t = hit_sphere(vec3_new(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 normal = vec3_sub(unit_vector(ray_at(r, t)), vec3_new(0, 0, -1));
        return vec3_scale(0.5, vec3_new(vec3_x(normal) + 1, vec3_y(normal) + 1, vec3_z(normal) + 1));
    }
    // Normalize the direction, then use its height to blend white and blue, which gives the sky gradient.
    vec3 unit_direction = unit_vector(ray_direction(r));

    // tells us how high the ray points, which gives the vertical gradient. if changed to vec3_x, then it becomes a
    // horizontal gradient also converts unit vectors -1 to 1 values to 0 to 1.
    double a = 0.5 * (vec3_y(unit_direction) + 1.0);
    // calculates lerp(linear interpolation aka linear blend) = (1-a)*startValue+a*endValue, with a going from 0.0
    // to 1.0
    return vec3_add(vec3_scale((1.0 - a), color_new(1.0, 1.0, 1.0)), vec3_scale(a, color_new(0.5, 0.7, 1.0)));
}

#endif
