## Notation

- Ray: `P(t) = A + t·d`. **A** is the origin and **d** is the direction.
- Sphere: radius **r**.

## Step 1: sphere centered at the origin

A point (x, y, z) is on the sphere when

```
x² + y² + z² = r²
```

That is the dot product of the point with itself, so with **P** = (x, y, z):

```
P · P = r²
(x, y, z) · (x, y, z) = x·x + y·y + z·z = x² + y² + z²
```

(inside means `< r²`, outside means `> r²`)

## Step 2: move the center to an arbitrary point C

Now the distance is measured from **C** = (Cx, Cy, Cz):

```
(Cx − x)² + (Cy − y)² + (Cz − z)² = r²
```

The vector from P to C is `(C − P)`, and a vector dotted with itself is the sum of its squared components, so:

```
(C − P) · (C − P) = r²
```

Why `(C − P) · (C − P)` is the sum of squares. This is the same dot-product rule as `P · P`, applied to the vector `(C − P)`:

```
(Cx − x, Cy − y, Cz − z) · (Cx − x, Cy − y, Cz − z)
  = (Cx − x)·(Cx − x) + (Cy − y)·(Cy − y) + (Cz − z)·(Cz − z)
  = (Cx − x)² + (Cy − y)² + (Cz − z)²
```

This says "P is on the sphere", and it reduces to Step 1 when **C** = 0.

## Step 3: ask whether the ray's points satisfy it

We want some `t` where the ray's point `P(t)` is on the sphere. Replace **P** with **A + t·d**:

```
(C − (A + t·d)) · (C − (A + t·d)) = r²
```

## Step 4: tidy the inside

Drop the parentheses and group the constant part. Let **w = C − A** (this is `oc` in code):

```
C − A − t·d  =  w − t·d
```

so

```
(w − t·d) · (w − t·d) = r²
```

## Step 5: expand the dot product

The dot product distributes like ordinary algebra, `(u − v)·(u − v) = u·u − 2 u·v + v·v`. Here **u = w** and **v = t·d**:

```
w·w  −  2 (w · t·d)  +  (t·d)·(t·d)  =  r²
```

Scalars come out of dot products, so `w · t·d = t(w·d)` and `(t·d)·(t·d) = t²(d·d)`:

```
w·w  −  2t (d·w)  +  t² (d·d)  =  r²
```

## Step 6: rearrange into a quadratic in t

Move `r²` to the left and write the terms in order of the power of t:

```
(d·d) t²  −  2(d·w) t  +  (w·w − r²)  =  0
```

The vectors and `r` are all known, and the dot products turn them into plain numbers. The only unknown is **t**, so this is a quadratic `a·t² + b·t + c = 0` with:

```
a = d · d
b = −2 d · (C − A)
c = (C − A) · (C − A) − r²
```

These are the three lines in `hit_sphere`.

## Step 7: solve with the quadratic formula

```
t = (−b ± √(b² − 4ac)) / 2a
```

The discriminant `b² − 4ac` tells you how many hits there are:

- negative: no real `t`, so the ray misses
- zero: one `t`, so the ray touches the sphere
- positive: two `t` values, where the ray enters and leaves

That's why `hit_sphere` returns `discriminant >= 0`.

## Step 8: the simplification used later

`b` always has a factor of −2, so let `h = d · (C − A)`. Then `b = −2h`:

```
t = (−(−2h) ± √((−2h)² − 4ac)) / 2a
  = (2h ± √(4h² − 4ac)) / 2a
  = (2h ± 2√(h² − ac)) / 2a
  = (h ± √(h² − ac)) / a
```

The 2s cancel. Final form:

```
a = d · d
h = d · (C − A)
c = (C − A) · (C − A) − r²
discriminant = h² − a·c
t = (h ± √discriminant) / a
```

---

# Surface normals (Section 6.1)

So far `hit_sphere` only says *whether* the ray hits. To shade the sphere we need to know *where* it hit and which way the surface faces there.

## Step 1: what a normal is

A **surface normal** is a vector perpendicular to the surface at a point. It tells you which way the surface "faces", and later lighting is computed from the angle between the normal and the light.

The book's policy: **normals are always unit length (length 1)**. Normalize once, up front, instead of repeatedly "just in case" later.

## Step 2: find the hit point

`hit_sphere` now needs to return `t` (the distance along the ray), not just true/false. Plug `t` back into the ray equation:

```
P = A + t·d          (ray_at(r, t) in code)
```

## Step 3: the sphere's normal

For a sphere, the normal at **P** points straight out from the center. It's the radius line, which is always perpendicular to the sphere's surface.

```
N = (P − C) / r
```

- `P − C` is the arrow from the center out to the hit point. The order matters: `C − P` would point inward.
- Since P is on the sphere, `|P − C| = r`. So dividing by `r` makes the length exactly 1, with no square root needed.
- Earth analogy: the vector from the earth's center to you points straight up.

In this section the book writes `unit_vector(P − C)` instead, because `hit_sphere` doesn't know the radius at that point. It gives the same result.

## Step 4: which `t` do we return?

The quadratic gives two roots, where the ray enters and where it leaves. We want the closer one, which is the smaller `t`, so we use the minus sign:

```
t = (−b − √discriminant) / 2a
```

If the ray misses (`discriminant < 0`), return `−1.0` as a "no hit" marker. The caller then checks `t > 0.0`, which also rejects hits behind the camera.

(Using the simplified form from Step 8, this is `t = (h − √discriminant) / a`, and it's the same value.)

## Step 5: turn the normal into a color

Each component of a unit normal is between −1 and 1, but colors need 0 to 1. This is the same range-shifting trick as the sky's `a`:

```
color = 0.5 × (N + 1)       →   (0.5·(Nx+1), 0.5·(Ny+1), 0.5·(Nz+1))
```

| Normal points | N | Color | Looks |
|---|---|---|---|
| toward the camera | (0, 0, 1) | (0.5, 0.5, 1.0) | blue |
| right | (1, 0, 0) | (1.0, 0.5, 0.5) | reddish |
| up | (0, 1, 0) | (0.5, 1.0, 0.5) | greenish |
| left | (−1, 0, 0) | (0.0, 0.5, 0.5) | teal |

This is why the picture is blue in the middle, red on the right and green on top. The colors are just the surface direction (x, y, z → r, g, b), and there are no lights yet.

## Step 6: the code in C

```c
// returns t of the nearest hit, or -1.0 if the ray misses
static inline double hit_sphere(point3 center, double radius, ray r) {
    vec3 oc = vec3_sub(center, ray_origin(r));
    double a = dot(ray_direction(r), ray_direction(r));
    double b = -2.0 * dot(ray_direction(r), oc);
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return -1.0;
    return (-b - sqrt(discriminant)) / (2.0 * a);   // smaller root = nearer hit
}

static inline color ray_color(ray r) {
    point3 center = vec3_new(0, 0, -1);
    double t = hit_sphere(center, 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(vec3_sub(ray_at(r, t), center));          // N = (P - C) / |P - C|
        return vec3_scale(0.5, color_new(vec3_x(N) + 1, vec3_y(N) + 1, vec3_z(N) + 1));
    }
    /* ...sky gradient as before... */
}

