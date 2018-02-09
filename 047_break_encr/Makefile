breaker: breaker.o
	gcc -o breaker breaker.o
breaker.o: breaker.c
	gcc -std=gnu99 -pedantic -Wwrite-strings -Werror -Wall -c breaker.c
.PHONY: clean
clean:
	rm -f breaker *.o *.c~
