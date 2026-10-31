main: main.c utilities/color.c utilities/color.h utilities/ray.h utilities/vec3.h
	gcc main.c utilities/color.c -o main -lm

debug: main.c utilities/color.c  utilities/color.h utilities/ray.h utilities/vec3.h
	gcc -g -O0 main.c utilities/color.c -o main -lm

release: main.c utilities/color.c utilities/color.h utilities/ray.h utilities/vec3.h
	gcc -O3 main.c utilities/color.c -o main -lm

run: main
	./main > outputs/image2.ppm
	xdg-open outputs/image2.ppm

clean:
	rm -f main
