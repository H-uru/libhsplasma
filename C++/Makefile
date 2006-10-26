GCCOPTS=-O2
OBJFILES=CoreLib/hsStream.o DynLib/PageID.o NucleusLib/pnKeyedObject/plKey.o NucleusLib/pnKeyedObject/hsKeyedObject.o hsMatrix44.o plCreatable.o plReceiver.o

all: PlasmaTest

PlasmaTest: PlasmaTest.cpp $(OBJFILES)
	g++ $(GCCOPTS) $(OBJFILES) PlasmaTest.cpp -o PlasmaTest

CoreLib/hsStream.o: CoreLib/hsStream.cpp
	g++ $(GCCOPTS) -c CoreLib/hsStream.cpp -o CoreLib/hsStream.o

DynLib/PageID.o: DynLib/PageID.cpp
	g++ $(GCCOPTS) -c DynLib/PageID.cpp -o DynLib/PageID.o

NucleusLib/pnKeyedObject/plKey.o: NucleusLib/pnKeyedObject/plKey.cpp
	g++ $(GCCOPTS) -c NucleusLib/pnKeyedObject/plKey.cpp -o NucleusLib/pnKeyedObject/plKey.o

NucleusLib/pnKeyedObject/hsKeyedObject.o: NucleusLib/pnKeyedObject/hsKeyedObject.cpp
	g++ $(GCCOPTS) -c NucleusLib/pnKeyedObject/hsKeyedObject.cpp -o NucleusLib/pnKeyedObject/hsKeyedObject.o

hsMatrix44.o: hsMatrix44.cpp
	g++ $(GCCOPTS) -c hsMatrix44.cpp -o hsMatrix44.o

plCreatable.o: plCreatable.cpp
	g++ $(GCCOPTS) -c plCreatable.cpp -o plCreatable.o

plReceiver.o: plReceiver.cpp
	g++ $(GCCOPTS) -c plReceiver.cpp -o plReceiver.o

clean:
	rm $(OBJFILES)
