#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

typedef struct vec3 {
    double e[3];
} vec3;

/// Alias for vec3, used for positions/points.
typedef vec3 point3;

static inline vec3 vec3_new(double x, double y, double z) {
    vec3 v = {{x, y, z}};
    return v;
}

static inline double vec3_x(vec3 v) { return v.e[0]; }
static inline double vec3_y(vec3 v) { return v.e[1]; }
static inline double vec3_z(vec3 v) { return v.e[2]; }

static inline vec3 vec3_negate(vec3 v) { return vec3_new(-v.e[0], -v.e[1], -v.e[2]); }

static inline double vec3_length_squared(vec3 v) { return v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]; }
static inline double vec3_length(vec3 v) { return sqrt(vec3_length_squared(v)); }

static inline void vec3_print(FILE *out, vec3 v) { fprintf(out, "%g %g %g", v.e[0], v.e[1], v.e[2]); }

static inline vec3 vec3_add(vec3 u, vec3 v) { return vec3_new(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]); }
/// u - v (subtracts v from u).
static inline vec3 vec3_sub(vec3 u, vec3 v) { return vec3_new(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]); }

/// Component-wise product (u.x*v.x, ...); not a scalar multiply.
static inline vec3 vec3_mult(vec3 u, vec3 v) { return vec3_new(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]); }
/// Scale v by scalar t (returns t * v).
static inline vec3 vec3_scale(double t, vec3 v) { return vec3_new(t * v.e[0], t * v.e[1], t * v.e[2]); }
/// Divide v by scalar t (returns v / t).
static inline vec3 vec3_div(vec3 v, double t) { return vec3_scale(1 / t, v); }

/// Add v to *a in place (a += v).
static inline void vec3_add_assign(vec3 *a, vec3 v) {
    a->e[0] += v.e[0];
    a->e[1] += v.e[1];
    a->e[2] += v.e[2];
}

static inline double dot(vec3 u, vec3 v) { return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]; }
static inline vec3 cross(vec3 u, vec3 v) {
    return vec3_new(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
static inline vec3 unit_vector(vec3 v) { return vec3_div(v, vec3_length(v)); }

#endif
