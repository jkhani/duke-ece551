CCFLAGS=--std=c++11 -pedantic -Wall -Werror -ggdb3
code: numerics.o
	g++ -o numerics $(CCFLAGS) numerics.o

%.o: %.cpp
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ numerics
