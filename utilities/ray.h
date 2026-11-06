#ifndef RAY_H
#define RAY_H

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

#endif
