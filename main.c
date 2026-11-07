#include "utilities/rt_weekend.h" // IWYU pragma: keep
#include "utilities/camera.h"

int main(void) {
    hittable_list world = {0};
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(0, 0, -1), 0.5)));
    hittable_list_add(&world, hittable_from_sphere(sphere_new(vec3_new(0, -100.5, -1), 100)));

    camera cam = camera_new();
    camera_render(&cam, &world);
}
