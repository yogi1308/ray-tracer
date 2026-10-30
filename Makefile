CFLAGS = -Wall -Wextra

main: main.c
	gcc $(CFLAGS) main.c -o main 

debug: main.c
	gcc $(CFLAGS) -g -O0 main.c -o main 

release: main.c
	gcc $(CFLAGS) -O3 main.c -o main -lm

run: main
	./main

clean:
	rm -f main

