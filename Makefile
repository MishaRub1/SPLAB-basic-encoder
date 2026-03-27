all: encoder
encoder: encoder.c
	gcc -m32 -g -Wall -o encoder encoder.c

run: encoder
	./encoder
clean:
	rm -f encoder

