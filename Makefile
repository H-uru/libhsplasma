GCCOPTS=-O2

all: PlasmaTest.cpp
	g++ $(GCCOPTS) PlasmaTest.cpp -o PlasmaTest

clean:
	rm *.o
