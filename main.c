#include <stdio.h>

#include "utilities/color.h"
#include "utilities/ray.h"
#include "utilities/vec3.h"

int main(void) {
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 800;

    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Viewport: imaginary 3D rectangle the camera looks through; gives each pixel a 3D point to aim at
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)image_width / image_height);

    // Focal length: distance from camera to viewport; sets how wide/zoomed the view is
    double focal_length = 1.0;
    point3 camera_center = vec3_new(0, 0, 0);

    // viewport_x/veiwport_y: vector across the full viewport, left to right/top to bottom
    vec3 viewport_x = vec3_new(viewport_width, 0, 0);
    vec3 viewport_y = vec3_new(0, -viewport_height, 0);

    // pixel_delta: 3D step from one pixel to the next
    vec3 pixel_delta_x = vec3_div(viewport_x, image_width);
    vec3 pixel_delta_y = vec3_div(viewport_y, image_height);

    // Start at the camera, move forward to the viewport plane, then half a width left and half a height up, which lands on the top-left corner.
    // upper_left = camera_center − (0, 0, focal_length) − viewport_x/2 − viewport_y/2
    point3 viewport_upper_left =
        vec3_sub(vec3_sub(vec3_sub(camera_center, vec3_new(0, 0, focal_length)), vec3_div(viewport_x, 2)),
            vec3_div(viewport_y, 2));

    // Move from that corner half a pixel right and half a pixel down, so the ray goes through the middle of pixel (0,0).
    // pixel00 = upper_left + 0.5 × (pixel_delta_x + pixel_delta_y)
    point3 pixel_00_loc = vec3_add(viewport_upper_left, vec3_scale(0.5, vec3_add(pixel_delta_x, pixel_delta_y)));

    printf("P3\n");
    printf("%d %d", image_width, image_height);
    printf("\n255\n");

    for (int y = 0; y < image_height; y++) {
        fprintf(stderr, "\rScanlines remaining: %d\n", image_height - y);
        for (int x = 0; x < image_width; x++) {
            // From pixel (0,0), take x steps right and y steps down to reach the center of pixel (x, y)
            // pixel_center = pixel00 + x × pixel_delta_x + y × pixel_delta_y
            point3 pixel_center =
                vec3_add(pixel_00_loc, vec3_add(vec3_scale(x, pixel_delta_x), vec3_scale(y, pixel_delta_y)));

            vec3 ray_direction = vec3_sub(pixel_center, camera_center);
            ray r = ray_new(camera_center, ray_direction);
            color pixel_color = ray_color(r);
            write_color(stdout, pixel_color);
        }
    }
    fprintf(stderr, "\rDone. \n");
}
