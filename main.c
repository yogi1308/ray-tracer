#include <stdio.h>

int main(void) {
    int image_width = 256;
    int image_height = 256;

    printf("P3\n");
    printf("%d %d", image_width, image_height);
    printf("\n255\n");

    for (int y = 0; y < image_height; y++) {
        fprintf(stderr, "\rScanlines remaining: %d\n", image_height - y);
        for (int x = 0; x < image_width; x++) {
            double r = (double)x / (image_width - 1);
            double g = (double)y / (image_height - 1);
            double b = 0.0;

            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);

            printf("%d %d %d\n", ir, ig, ib);
        }
    }
    fprintf(stderr, "\rDone. \n");
}
