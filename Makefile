all:
	gcc -O3 -Wall -Wextra -lb2 *.c && ./a.out
clean:
	rm -rf *.o *.out

