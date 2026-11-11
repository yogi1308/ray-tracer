#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.h"

typedef enum material_type {
    MATERIAL_LAMBERTIAN,
    MATERIAL_METAL,
    MATERIAL_DIELECTRIC // glass
} material_type;

typedef struct material {
    material_type type;
    color albedo; // fraction of red/green/blue the surface reflects, each 0 to 1
    double fuzz;  //  = perfect mirror, 1 = very blurry
    double refratcion_index;
} material;

static inline material material_lambertian(color albedo) {
    material m;
    m.type = MATERIAL_LAMBERTIAN;
    m.albedo = albedo;
    m.fuzz = 0;
    m.refratcion_index = 1;
    return m;
}
static inline material material_metal(color albedo, double fuzz) {
    material m;
    m.type = MATERIAL_METAL;
    m.albedo = albedo;
    m.fuzz = (fuzz < 1) ? fuzz : 1.0;
    m.refratcion_index = 1;
    return m;
}

static inline material meterial_dielectric(double refraction_index) {
    material m;
    m.type = MATERIAL_DIELECTRIC;
    m.albedo = color_new(1, 1, 1);
    m.fuzz = 0;
    m.refratcion_index = refraction_index;
    return m;
}

#endif
