#include "color.h"
#include "interval.h"

void write_color(FILE *out, color pixel_color) {
    double r = vec3_x(pixel_color);
    double g = vec3_y(pixel_color);
    double b = vec3_z(pixel_color);

    interval intensity = interval_new(0.000, 0.999);
    int rbyte = (int)(256* clamp(intensity, r));
    int gbyte = (int)(256* clamp(intensity, g));
    int bbyte = (int)(256* clamp(intensity, b));

    fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}
