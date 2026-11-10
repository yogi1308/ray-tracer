#ifndef SCATTER_H
#define SCATTER_H

#include "color.h"
#include "hit_record.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"

static inline bool
material_scatter(const material *m, ray r_in, const hit_record *rec, color *attenuation, ray *scattered) {
    (void)r_in; // used by metal later
    switch (m->type) {
        case MATERIAL_LAMBERTIAN: {
            vec3 scatter_direction = vec3_add(rec->normal, vec3_random_unit_vector());
            if (vec3_near_zero(scatter_direction)) {
                scatter_direction = rec->normal;
            }
            *scattered = ray_new(rec->p, scatter_direction);
            *attenuation = m->albedo;
            return true;
        }
        case MATERIAL_METAL: {
            vec3 reflected = vec3_reflect(ray_direction(r_in), rec->normal);
            reflected = vec3_add(unit_vector(reflected), vec3_scale(m->fuzz, vec3_random_unit_vector()));
            *scattered = ray_new(rec->p, reflected);
            *attenuation = m->albedo;
            if (vec3_near_zero(reflected)) {
                reflected = rec->normal;
            }
            *scattered = ray_new(rec->p, reflected);
            *attenuation = m->albedo;
            return dot(ray_direction(*scattered), rec->normal) > 0;
        }
    }
    return false;
}

#endif /* ifndef SCATTER_H */
