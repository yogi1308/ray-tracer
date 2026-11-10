#include "utilities/camera.h"
#include "utilities/rt_weekend.h" // IWYU pragma: keep

int main(void) {
    material material_ground = material_lambertian(color_new(0.8, 0.8, 0.0));
    material material_center = material_lambertian(color_new(0.1, 0.2, 0.5));
    material material_left = material_metal(color_new(0.8, 0.8, 0.8));
    material material_right = material_metal(color_new(0.8, 0.6, 0.2));
    hittable_list world = {0};
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(0.0, -100.5, -1.0), 100.0, material_ground)));
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(0.0, 0.0, -1.2), 0.5, material_center)));
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(-1.0, 0.0, -1.0), 0.5, material_left)));
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(1.0, 0.0, -1.0), 0.5, material_right)));

    camera cam = camera_new();
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    camera_render(&cam, &world);
}
