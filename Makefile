CC=cc
CFLAGS=-Wall -Wextra -std=c99 # -fopenmp

houses: houses.c
	$(CC) $(CFLAGS) -o houses houses.c

clean:
	rm -f houses
