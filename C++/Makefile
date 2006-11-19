CC=g++
GCCOPTS=-O2 -fPIC -Wall
OBJFILES=CoreLib/hsStream.o CoreLib/hsBitVector.o \
	DynLib/PageID.o DynLib/plString.o \
	NucleusLib/pnKeyedObject/plKey.o NucleusLib/pnKeyedObject/hsKeyedObject.o \
	NucleusLib/pnNetCommon/plSynchedObject.o \
	NucleusLib/pnSceneObject/plObjInterface.o \
	PubUtilLib/plAvatar/plClothingItem.o \
	PubUtilLib/plGImage/plBitmap.o \
	PubUtilLib/plGImage/plFont.o \
	hsMatrix44.o plCreatable.o plReceiver.o
PLSLIB=lib/libPlasma.so.1.0.1

all: $(PLSLIB) bin/PlasmaTest

lib/libPlasma.so.1.0.1: $(OBJFILES)
	$(CC) $(GCCOPTS) -shared -Wl,-soname,libPlasma.so.1 -o $(PLSLIB) $(OBJFILES)

bin/PlasmaTest: PlasmaTest.cpp $(PLSLIB)
	$(CC) $(GCCOPTS) -Llib/ -lPlasma PlasmaTest.cpp -o bin/PlasmaTest

CoreLib/hsStream.o: CoreLib/hsStream.cpp
	$(CC) $(GCCOPTS) -c CoreLib/hsStream.cpp -o CoreLib/hsStream.o

CoreLib/hsBitVector.o: CoreLib/hsBitVector.cpp
	$(CC) $(GCCOPTS) -c CoreLib/hsBitVector.cpp -o CoreLib/hsBitVector.o

DynLib/PageID.o: DynLib/PageID.cpp
	$(CC) $(GCCOPTS) -c DynLib/PageID.cpp -o DynLib/PageID.o

DynLib/plString.o: DynLib/plString.cpp
	$(CC) $(GCCOPTS) -c DynLib/plString.cpp -o DynLib/plString.o

NucleusLib/pnKeyedObject/plKey.o: NucleusLib/pnKeyedObject/plKey.cpp
	$(CC) $(GCCOPTS) -c NucleusLib/pnKeyedObject/plKey.cpp -o NucleusLib/pnKeyedObject/plKey.o

NucleusLib/pnKeyedObject/hsKeyedObject.o: NucleusLib/pnKeyedObject/hsKeyedObject.cpp
	$(CC) $(GCCOPTS) -c NucleusLib/pnKeyedObject/hsKeyedObject.cpp -o NucleusLib/pnKeyedObject/hsKeyedObject.o

NucleusLib/pnNetCommon/plSynchedObject.o: NucleusLib/pnNetCommon/plSynchedObject.cpp
	$(CC) $(GCCOPTS) -c NucleusLib/pnNetCommon/plSynchedObject.cpp -o NucleusLib/pnNetCommon/plSynchedObject.o

NucleusLib/pnSceneObject/plObjInterface.o: NucleusLib/pnSceneObject/plObjInterface.cpp
	$(CC) $(GCCOPTS) -c NucleusLib/pnSceneObject/plObjInterface.cpp -o NucleusLib/pnSceneObject/plObjInterface.o

PubUtilLib/plAvatar/plClothingItem.o: PubUtilLib/plAvatar/plClothingItem.cpp
	$(CC) $(GCCOPTS) -c PubUtilLib/plAvatar/plClothingItem.cpp -o PubUtilLib/plAvatar/plClothingItem.o

PubUtilLib/plGImage/plBitmap.o: PubUtilLib/plGImage/plBitmap.cpp
	$(CC) $(GCCOPTS) -c PubUtilLib/plGImage/plBitmap.cpp -o PubUtilLib/plGImage/plBitmap.o

PubUtilLib/plGImage/plFont.o: PubUtilLib/plGImage/plFont.cpp
	$(CC) $(GCCOPTS) -c PubUtilLib/plGImage/plFont.cpp -o PubUtilLib/plGImage/plFont.o

hsMatrix44.o: hsMatrix44.cpp
	$(CC) $(GCCOPTS) -c hsMatrix44.cpp -o hsMatrix44.o

plCreatable.o: plCreatable.cpp
	$(CC) $(GCCOPTS) -c plCreatable.cpp -o plCreatable.o

plReceiver.o: plReceiver.cpp
	$(CC) $(GCCOPTS) -c plReceiver.cpp -o plReceiver.o

install:
	cp $(PLSLIB) /usr/local/lib
	ldconfig

clean:
	rm $(OBJFILES)

distclean:
	rm $(PLSLIB)
	rm bin/PlasmaTest
