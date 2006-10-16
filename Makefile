GCCOPTS=-O2

all: PlasmaTest.cpp hsMatrix44.o
	g++ $(GCCOPTS) hsMatrix44.o PlasmaTest.cpp -o PlasmaTest

hsMatrix44.o: hsMatrix44.cpp
	g++ $(GCCOPTS) -c hsMatrix44.cpp

clean:
	rm *.o
