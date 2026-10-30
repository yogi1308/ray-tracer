#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

#include "vec3.h"

typedef vec3 color;

static inline void write_color(FILE *out, vec3 pixel_color) {
    double r = vec3_x(pixel_color);
    double g = vec3_y(pixel_color);
    double b = vec3_z(pixel_color);

    int ir = (int)(255.999 * r);
    int ig = (int)(255.999 * g);
    int ib = (int)(255.999 * b);

    fprintf(out, "%d %d %d\n", ir, ig, ib);
}

#endif /* ifndef COLOR_H */
