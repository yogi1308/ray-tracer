#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include <stdbool.h>

#include "color.h"
#include "hit_record.h"
#include "hittable_list.h"
#include "interval.h"
#include "random.h"
#include "ray.h"
#include "rt_weekend.h"
#include "scatter.h"
#include "vec3.h"
typedef struct camera {
    double aspect_ratio;
    int image_width;
    int image_height;
    point3 camera_center;
    point3 pixel_00_loc;
    vec3 pixel_delta_x;
    vec3 pixel_delta_y;
    int samples_per_pixel;
    double pixel_samples_scale;
    int max_depth;
    double vfov;
    point3 lookfrom;      // Point camera is looking from
    point3 lookat;        // Point camera is looking at
    vec3 vup;             // Camera-relative "up" direction
    vec3 u, v, w;         // camera axes
    double defocus_angle; // angle of the cone of rays through each pixel; 0 = no blur
    double focus_dist;    // distance from lookfrom to the perfectly sharp plane
    vec3 defocus_disk_u;  // horizontal radius of the disc
    vec3 defocus_disk_v;  // vertical radius of the disc
} camera;

static inline camera camera_new(void) {
    camera cam = {0};
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 100;
    cam.pixel_samples_scale = 1.0 / cam.samples_per_pixel;
    cam.max_depth = 50;
    cam.vfov = 90;
    cam.lookfrom = vec3_new(0, 0, 0);
    cam.lookat = vec3_new(0, 0, -1);
    cam.vup = vec3_new(0, 1, 0);
    cam.focus_dist = 10;
    return cam;
}

static inline point3 defocus_disk_sample(const camera *cam) {
    vec3 p = vec3_random_in_unit_disk();
    return vec3_add(cam->camera_center,
        vec3_add(vec3_scale(vec3_x(p), cam->defocus_disk_u), vec3_scale(vec3_y(p), cam->defocus_disk_v)));
}

static inline vec3 sample_square(void) { return vec3_new(random_double() - 0.5, random_double() - 0.5, 0); }

static inline ray camera_get_ray(const camera *cam, int x, int y) {
    vec3 offset = sample_square();
    point3 pixel_sample = vec3_add(cam->pixel_00_loc,
        vec3_add(vec3_scale(x + vec3_x(offset), cam->pixel_delta_x),
            vec3_scale(y + vec3_y(offset), cam->pixel_delta_y)));
    point3 origin = (cam->defocus_angle <= 0) ? cam->camera_center : defocus_disk_sample(cam);
    return ray_new(origin, vec3_sub(pixel_sample, origin));
}

static inline void camera_initialize(camera *cam) {
    int image_height = (int)(cam->image_width / cam->aspect_ratio);
    cam->image_height = (image_height < 1) ? 1 : image_height;
    cam->w = unit_vector(vec3_sub(cam->lookfrom, cam->lookat));
    cam->u = unit_vector(cross(cam->vup, cam->w));
    cam->v = cross(cam->w, cam->u);


    double defocus_radius = cam->focus_dist * tan(degrees_to_radians(cam->defocus_angle / 2));
    cam->defocus_disk_u = vec3_scale(defocus_radius, cam->u);
    cam->defocus_disk_v = vec3_scale(defocus_radius, cam->v);
    // Viewport: imaginary 3D rectangle the camera looks through; gives each pixel a 3D point to aim at
    double theta = degrees_to_radians(cam->vfov);
    double h = tan(theta / 2);

    double viewport_height = 2.0 * h * cam->focus_dist;
    double viewport_width = viewport_height * ((double)cam->image_width / cam->image_height);

    // Focal length: distance from camera to viewport; sets how wide/zoomed the view is
    cam->camera_center = cam->lookfrom;

    // viewport_x/veiwport_y: vector across the full viewport, left to right/top to bottom
    vec3 viewport_x = vec3_scale(viewport_width, cam->u);
    vec3 viewport_y = vec3_scale(-viewport_height, cam->v);

    // pixel_delta: 3D step from one pixel to the next
    cam->pixel_delta_x = vec3_div(viewport_x, cam->image_width);
    cam->pixel_delta_y = vec3_div(viewport_y, cam->image_height);

    // Start at the camera, move forward to the viewport plane, then half a width left and half a height up, which lands
    // on the top-left corner. upper_left = camera_center − (0, 0, focal_length) − viewport_x/2 − viewport_y/2
    point3 viewport_upper_left =
        vec3_sub(vec3_sub(vec3_sub(cam->camera_center, vec3_scale(cam->focus_dist, cam->w)), vec3_div(viewport_x, 2)),
            vec3_div(viewport_y, 2));

    // Move from that corner half a pixel right and half a pixel down, so the ray goes through the middle of pixel
    // (0,0). pixel00 = upper_left + 0.5 × (pixel_delta_x + pixel_delta_y)
    cam->pixel_00_loc =
        vec3_add(viewport_upper_left, vec3_scale(0.5, vec3_add(cam->pixel_delta_x, cam->pixel_delta_y)));
}

static inline color ray_color(ray r, int depth, const hittable_list *world) {
    if (depth <= 0) {
        return color_new(0, 0, 0);
    }
    hit_record rec;
    if (hittable_list_hit(world, r, interval_new(0.001, infinity), &rec)) {
        ray scattered;
        color attenuation;
        if (material_scatter(&rec.mat, r, &rec, &attenuation, &scattered)) {
            return vec3_mult(attenuation, ray_color(scattered, depth - 1, world));
        }
        return color_new(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(ray_direction(r));
    double a = 0.5 * (vec3_y(unit_direction) + 1.0);
    return vec3_add(vec3_scale((1.0 - a), color_new(1.0, 1.0, 1.0)), vec3_scale(a, color_new(0.5, 0.7, 1.0)));
}

static inline void camera_render(camera *cam, const hittable_list *world) {
    camera_initialize(cam);
    printf("P3\n");
    printf("%d %d", cam->image_width, cam->image_height);
    printf("\n255\n");

    for (int y = 0; y < cam->image_height; y++) {
        fprintf(stderr, "\rScanlines remaining: %d ", cam->image_height - y);
        for (int x = 0; x < cam->image_width; x++) {
            // From pixel (0,0), take x steps right and y steps down to reach the center of pixel (x, y)
            // pixel_center = pixel00 + x × pixel_delta_x + y × pixel_delta_y
            color pixel_color = color_new(0, 0, 0);
            for (int sample = 0; sample < cam->samples_per_pixel; sample++) {
                ray r = camera_get_ray(cam, x, y);
                vec3_add_assign(&pixel_color, ray_color(r, cam->max_depth, world));
            }
            write_color(stdout, vec3_scale(cam->pixel_samples_scale, pixel_color));
        }
    }
    fprintf(stderr, "\rDone. \n");
}

#endif /* ifndef CAMERA_H */
