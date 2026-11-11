#include "utilities/camera.h"
#include "utilities/rt_weekend.h" // IWYU pragma: keep

int main(void) {
    material material_ground = material_lambertian(color_new(0.8, 0.8, 0.0));
    material material_center = material_lambertian(color_new(0.1, 0.2, 0.5));
    /* material material_left = material_metal(color_new(0.8, 0.8, 0.8), 0.3); */
    material material_left = meterial_dielectric(1.50);
    material material_bubble = meterial_dielectric(1.00 / 1.50);
    material material_right = material_metal(color_new(0.8, 0.6, 0.2), 1.0);

    hittable_list world = {0};
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(0.0, -100.5, -1.0), 100.0, material_ground)));
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(0.0, 0.0, -1.2), 0.5, material_center)));
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(-1.0, 0.0, -1.0), 0.5, material_left)));
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(-1.0, 0.0, -1.0), 0.4, material_bubble)));
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(1.0, 0.0, -1.0), 0.5, material_right)));

    camera cam = camera_new();
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.vfov = 20;
    cam.lookfrom = vec3_new(-2, 2, 1);
    cam.lookat = vec3_new(0, 0, -1);
    cam.vup = vec3_new(0, 1, 0);

    camera_render(&cam, &world);
}
