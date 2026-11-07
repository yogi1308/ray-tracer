#ifndef INTERVAL_H
#define INTERVAL_H

#include <math.h>
#include <stdbool.h>
typedef struct interval {
    double min;
    double max;
} interval;

static inline interval interval_new(double min, double max) {
    interval i = {min, max};
    return i;
}

static inline double size(interval i) {
    return i.max - i.min;
}

static inline bool contains(interval i, double x) {
    return i.min <= x && x <= i.max;
}

static inline bool surrounds(interval i, double x) {
    return i.min < x && x < i.max;
}

static inline interval interval_empty() {
    return interval_new(INFINITY, -INFINITY);
}

static inline interval interval_universe() {
    return interval_new(-INFINITY, INFINITY);
}

#endif /* ifndef INTERVAL_H */
