#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.h"

typedef enum material_type { MATERIAL_LAMBERTIAN, MATERIAL_METAL } material_type;

typedef struct material {
    material_type type;
    color albedo;
} material;

static inline material material_lambertian(color albedo) {
    material m;
    m.type = MATERIAL_LAMBERTIAN;
    m.albedo = albedo;
    return m;
}
static inline material material_metal(color albedo) {
    material m;
    m.type = MATERIAL_METAL;
    m.albedo = albedo;
    return m;
}



#endif
