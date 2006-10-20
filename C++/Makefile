GCCOPTS=-O2
OBJFILES=CoreLib/hsStream.o DynLib/PageID.o hsMatrix44.o

all: PlasmaTest

PlasmaTest: PlasmaTest.cpp $(OBJFILES)
	g++ $(GCCOPTS) $(OBJFILES) PlasmaTest.cpp -o PlasmaTest

CoreLib/hsStream.o: CoreLib/hsStream.cpp
	g++ $(GCCOPTS) -c CoreLib/hsStream.cpp -o CoreLib/hsStream.o

DynLib/PageID.o: DynLib/PageID.cpp
	g++ $(GCCOPTS) -c DynLib/PageID.cpp -o DynLib/PageID.o

hsMatrix44.o: hsMatrix44.cpp
	g++ $(GCCOPTS) -c hsMatrix44.cpp -o hsMatrix44.o

clean:
	rm $(OBJFILES)
