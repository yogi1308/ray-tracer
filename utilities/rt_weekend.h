#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Constants

#define infinity INFINITY
#define pi 3.1415926535897932385

// Utility Functions

static inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

static inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

static inline double random_double_min_max(double min, double max) {
    return min + (max-min)*random_double();

}

// Common Headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif
