#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hit_record.h"
#include "hittable.h"
#define MAX_HITTABLES 512

typedef struct hittable_list {
    hittable objects[MAX_HITTABLES];
    int count;
} hittable_list;

static inline bool hittable_list_add(hittable_list *list, hittable obj) {
    if (list->count == MAX_HITTABLES) {
        return false;
    }
    list->objects[list->count] = obj;
    list->count++;
    return true;
}

static inline bool hittable_list_hit(const hittable_list *list, ray r, double t_min, double t_max, hit_record *rec) {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (int i = 0; i < list->count; i++) {
        if (hittable_hit(&list->objects[i], r, t_min, closest_so_far, &temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif /* ifndef HITTABLE_LIST */
