#include "utilities/camera.h"
#include "utilities/rt_weekend.h" // IWYU pragma: keep

int main(void) {
    hittable_list world = {0};

    material ground_material = material_lambertian(color_new(0.5, 0.5, 0.5));
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(0, -1000, 0), 1000, ground_material)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            point3 center = vec3_new(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if (vec3_length(vec3_sub(center, vec3_new(4, 0.2, 0))) > 0.9) {
                material sphere_material;

                if (choose_mat < 0.8) { // matte
                    color albedo = vec3_mult(vec3_random(), vec3_random());
                    sphere_material = material_lambertian(albedo);
                } else if (choose_mat < 0.95) { // metal
                    color albedo = vec3_random_range(0.5, 1);
                    double fuzz = random_double_range(0, 0.5);
                    sphere_material = material_metal(albedo, fuzz);
                } else { // glass
                    sphere_material = material_dielectric(1.5);
                }
                hittable_list_add(&world, hittable_from_sphere(sphere_new(center, 0.2, sphere_material)));
            }
        }
    }

    material material1 = material_dielectric(1.5);
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(0, 1, 0), 1.0, material1)));

    material material2 = material_lambertian(color_new(0.4, 0.2, 0.1));
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(-4, 1, 0), 1.0, material2)));

    material material3 = material_metal(color_new(0.7, 0.6, 0.5), 0.0);
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(4, 1, 0), 1.0, material3)));

    camera cam = camera_new();
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = vec3_new(13, 2, 3);
    cam.lookat = vec3_new(0, 0, 0);
    cam.vup = vec3_new(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    camera_render(&cam, &world);
}
