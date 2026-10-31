#include "color.h"

void write_color(FILE *out, color pixel_color) {
    double r = vec3_x(pixel_color);
    double g = vec3_y(pixel_color);
    double b = vec3_z(pixel_color);

    int rbyte = (int)(255.999 * r);
    int gbyte = (int)(255.999 * g);
    int bbyte = (int)(255.999 * b);

    fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}
