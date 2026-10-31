## Setup

- Sphere with center **C** and radius **r**: a point **P** is on it when `(C − P) · (C − P) = r²`
- Ray: `P(t) = Q + t·d`, where **Q** is the origin and **d** is the direction

## Step 1: substitute the ray into the sphere equation

```
(C − P(t)) · (C − P(t)) = r²
(C − (Q + t·d)) · (C − (Q + t·d)) = r²
```

## Step 2: group the terms

Let `w = C − Q`, which is `oc` in your code. Then `C − Q − t·d = w − t·d`:

```
(w − t·d) · (w − t·d) = r²
```

## Step 3: expand the dot product

It distributes like `(x − y)² = x² − 2xy + y²`:

```
w·w − 2t(d·w) + t²(d·d) = r²
```

## Step 4: move r² over and reorder by powers of t

```
(d·d) t²  −  2(d·w) t  +  (w·w − r²)  =  0
```

This has the form `a·t² + b·t + c = 0`, so matching the coefficients gives:

```
a = d · d
b = −2 d · (C − Q)
c = (C − Q) · (C − Q) − r²
```

These are the three lines in your `hit_sphere` (`oc` is `C − Q`).

## Step 5: solve for t

With the quadratic formula:

```
t = (−b ± √(b² − 4ac)) / 2a
```

The part under the root, `b² − 4ac`, is the discriminant:

- Negative: no real `t`, so the ray misses.
- Zero: one `t`, so the ray touches the sphere.
- Positive: two values of `t`, one where the ray enters and one where it leaves.

That's why `hit_sphere` returns `discriminant >= 0`.

## Step 6: the simplification the book uses next

`b` always has a factor of −2, so let `h = d · (C − Q)`. Then `b = −2h`. Substitute it in:

```
t = (−(−2h) ± √((−2h)² − 4ac)) / 2a
  = (2h ± √(4h² − 4ac)) / 2a
  = (2h ± 2√(h² − ac)) / 2a
  = (h ± √(h² − ac)) / a
```

The 2s cancel, so the code needs fewer multiplications:

```
a = d · d
h = d · (C − Q)
c = (C − Q) · (C − Q) − r²
discriminant = h² − a·c
t = (h ± √discriminant) / a
```

You'll use this form from Section 6 onward.
