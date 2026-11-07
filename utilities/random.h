#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>

/// Random real in [0, 1). Never returns exactly 1.
static inline double random_double(void) { return rand() / (RAND_MAX + 1.0); }

/// Random real in [min, max).
static inline double random_double_range(double min, double max) { return min + (max - min) * random_double(); }

#endif
