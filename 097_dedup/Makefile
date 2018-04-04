CCFLAGS=--std=gnu++11 -pedantic -Wall -Werror -ggdb3
dedup:  dedup.o
	g++ -o dedup $(CCFLAGS) dedup.o

%.o: %.cpp
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ dedup
