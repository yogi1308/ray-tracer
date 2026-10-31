#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

#include "vec3.h"

/// Alias for vec3, used for RGB colors.
typedef vec3 color;

static inline color color_new(double r, double g, double b) { return vec3_new(r, g, b); }

void write_color(FILE *out, vec3 pixel_color);

#endif
