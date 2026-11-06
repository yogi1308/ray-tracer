main: main.c utilities/color.c utilities/color.h utilities/ray.h utilities/vec3.h utilities/rt_weekend.h utilities/sphere.h utilities/hittable.h utilities/hit_record.h utilities/hittable_list.h
	gcc main.c utilities/color.c -o main -lm

debug: main.c utilities/color.c utilities/color.h utilities/ray.h utilities/vec3.h utilities/rt_weekend.h utilities/sphere.h utilities/hittable.h utilities/hit_record.h utilities/hittable_list.h
	gcc -g -O0 main.c utilities/color.c -o main -lm

release: main.c utilities/color.c utilities/color.h utilities/ray.h utilities/vec3.h utilities/rt_weekend.h utilities/sphere.h utilities/hittable.h utilities/hit_record.h utilities/hittable_list.h
	gcc -O3 main.c utilities/color.c -o main -lm

run: main
	./main > outputs/image5.ppm
	xdg-open outputs/image5.ppm

clean:
	rm -f main
