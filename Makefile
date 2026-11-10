SRC = main.c $(wildcard utilities/*.c)
HDRS = $(wildcard *.h) $(wildcard utilities/*.h)
LDLIBS = -lm
CC = gcc
OUTPUT_FILE = "outputs/image14.ppm"

main: $(SRC) $(HDRS)
	$(CC) $(SRC) -o main $(LDLIBS)

debug: $(SRC) $(HDRS)
	$(CC) -g -O0 $(SRC) -o main $(LDLIBS)

release: $(SRC) $(HDRS)
	$(CC) -O3 $(SRC) -o main $(LDLIBS)

run: main
	./main > $(OUTPUT_FILE)
	xdg-open $(OUTPUT_FILE)

clean:
	rm -f main
