#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Constants

#define infinity INFINITY
#define pi 3.1415926535897932385

// Utility Functions

static inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

// Common Headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif
