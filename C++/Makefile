CC = g++
CFLAGS += -O2 -fPIC -Wall

OBJFILES=\
	CoreLib/hsRefCnt.o \
	CoreLib/hsStream.o \
	CoreLib/hsElfStream.o \
	CoreLib/hsBitVector.o \
	CoreLib/hsMatrix44.o \
	CoreLib/hsGeometry3.o \
	CoreLib/hsBounds.o \
	DynLib/PageID.o DynLib/plString.o \
	NucleusLib/pnFactory/plCreatable.o \
	NucleusLib/pnFactory/plFactory.o \
	NucleusLib/pnKeyedObject/plKey.o \
	NucleusLib/pnKeyedObject/plReceiver.o \
	NucleusLib/pnKeyedObject/hsKeyedObject.o \
	NucleusLib/pnMessage/plMessage.o \
	NucleusLib/pnNetCommon/plSynchedObject.o \
	NucleusLib/pnSceneObject/plObjInterface.o \
	NucleusLib/pnSceneObject/plAudioInterface.o \
	NucleusLib/pnSceneObject/plCoordinateInterface.o \
	NucleusLib/pnSceneObject/plDrawInterface.o \
	NucleusLib/pnSceneObject/plSimulationInterface.o \
	NucleusLib/pnSceneObject/plSceneObject.o \
	PubUtilLib/plAvatar/plClothingItem.o \
	PubUtilLib/plDrawable/plSpan.o \
	PubUtilLib/plGImage/plBitmap.o \
	PubUtilLib/plGImage/plFont.o \
	PubUtilLib/plPipeline/plFogEnvironment.o \
	PubUtilLib/plScene/plSceneNode.o \
	PubUtilLib/plSurface/hsGMaterial.o
PLSLIB=lib/libPlasma.so.1.0.1

all: $(PLSLIB) bin/PlasmaTest

lib/libPlasma.so.1.0.1: $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -shared -Wl,-soname,libPlasma.so.1 -o $(PLSLIB)

bin/PlasmaTest: PlasmaTest.cpp $(PLSLIB)
	$(CC) $(CFLAGS) -Llib/ -lPlasma PlasmaTest.cpp -o bin/PlasmaTest

CoreLib/hsRefCnt.o: CoreLib/hsRefCnt.h CoreLib/hsRefCnt.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsRefCnt.cpp -o CoreLib/hsRefCnt.o

CoreLib/hsStream.o: CoreLib/hsStream.h CoreLib/hsStream.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsStream.cpp -o CoreLib/hsStream.o

CoreLib/hsElfStream.o: CoreLib/hsElfStream.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsElfStream.cpp -o CoreLib/hsElfStream.o

CoreLib/hsBitVector.o: CoreLib/hsBitVector.h CoreLib/hsBitVector.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsBitVector.cpp -o CoreLib/hsBitVector.o

CoreLib/hsMatrix44.o: CoreLib/hsMatrix44.h CoreLib/hsMatrix44.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsMatrix44.cpp -o CoreLib/hsMatrix44.o

CoreLib/hsGeometry3.o: CoreLib/hsGeometry3.h CoreLib/hsGeometry3.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsGeometry3.cpp -o CoreLib/hsGeometry3.o

CoreLib/hsBounds.o: CoreLib/hsBounds.h CoreLib/hsBounds.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsBounds.cpp -o CoreLib/hsBounds.o

DynLib/PageID.o: DynLib/PageID.h DynLib/PageID.cpp
	$(CC) $(CFLAGS) -c DynLib/PageID.cpp -o DynLib/PageID.o

DynLib/plString.o: DynLib/plString.h DynLib/plString.cpp
	$(CC) $(CFLAGS) -c DynLib/plString.cpp -o DynLib/plString.o

NucleusLib/pnFactory/plCreatable.o: NucleusLib/pnFactory/plCreatable.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnFactory/plCreatable.cpp -o NucleusLib/pnFactory/plCreatable.o

NucleusLib/pnFactory/plFactory.o: NucleusLib/pnFactory/plFactory.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnFactory/plFactory.cpp -o NucleusLib/pnFactory/plFactory.o

NucleusLib/pnKeyedObject/plKey.o: NucleusLib/pnKeyedObject/plKey.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnKeyedObject/plKey.cpp -o NucleusLib/pnKeyedObject/plKey.o

NucleusLib/pnKeyedObject/plReceiver.o: NucleusLib/pnKeyedObject/plReceiver.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnKeyedObject/plReceiver.cpp -o NucleusLib/pnKeyedObject/plReceiver.o

NucleusLib/pnKeyedObject/hsKeyedObject.o: NucleusLib/pnKeyedObject/hsKeyedObject.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnKeyedObject/hsKeyedObject.cpp -o NucleusLib/pnKeyedObject/hsKeyedObject.o

NucleusLib/pnMessage/plMessage.o: NucleusLib/pnMessage/plMessage.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnMessage/plMessage.cpp -o NucleusLib/pnMessage/plMessage.o

NucleusLib/pnNetCommon/plSynchedObject.o: NucleusLib/pnNetCommon/plSynchedObject.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnNetCommon/plSynchedObject.cpp -o NucleusLib/pnNetCommon/plSynchedObject.o

NucleusLib/pnSceneObject/plAudioInterface.o: NucleusLib/pnSceneObject/plAudioInterface.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plAudioInterface.cpp -o NucleusLib/pnSceneObject/plAudioInterface.o

NucleusLib/pnSceneObject/plCoordinateInterface.o: NucleusLib/pnSceneObject/plCoordinateInterface.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plCoordinateInterface.cpp -o NucleusLib/pnSceneObject/plCoordinateInterface.o

NucleusLib/pnSceneObject/plDrawInterface.o: NucleusLib/pnSceneObject/plDrawInterface.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plDrawInterface.cpp -o NucleusLib/pnSceneObject/plDrawInterface.o

NucleusLib/pnSceneObject/plObjInterface.o: NucleusLib/pnSceneObject/plObjInterface.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plObjInterface.cpp -o NucleusLib/pnSceneObject/plObjInterface.o

NucleusLib/pnSceneObject/plSceneObject.o: NucleusLib/pnSceneObject/plSceneObject.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plSceneObject.cpp -o NucleusLib/pnSceneObject/plSceneObject.o

NucleusLib/pnSceneObject/plSimulationInterface.o: NucleusLib/pnSceneObject/plSimulationInterface.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plSimulationInterface.cpp -o NucleusLib/pnSceneObject/plSimulationInterface.o

PubUtilLib/plAvatar/plClothingItem.o: PubUtilLib/plAvatar/plClothingItem.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plAvatar/plClothingItem.cpp -o PubUtilLib/plAvatar/plClothingItem.o

PubUtilLib/plDrawable/plSpan.o: PubUtilLib/plDrawable/plSpan.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plSpan.cpp -o PubUtilLib/plDrawable/plSpan.o

PubUtilLib/plGImage/plBitmap.o: PubUtilLib/plGImage/plBitmap.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plGImage/plBitmap.cpp -o PubUtilLib/plGImage/plBitmap.o

PubUtilLib/plGImage/plFont.o: PubUtilLib/plGImage/plFont.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plGImage/plFont.cpp -o PubUtilLib/plGImage/plFont.o

PubUtilLib/plPipeline/plFogEnvironment.o: PubUtilLib/plPipeline/plFogEnvironment.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPipeline/plFogEnvironment.cpp -o PubUtilLib/plPipeline/plFogEnvironment.o

PubUtilLib/plScene/plSceneNode.o: PubUtilLib/plScene/plSceneNode.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plScene/plSceneNode.cpp -o PubUtilLib/plScene/plSceneNode.o

PubUtilLib/plSurface/hsGMaterial.o: PubUtilLib/plSurface/hsGMaterial.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plSurface/hsGMaterial.cpp -o PubUtilLib/plSurface/hsGMaterial.o

install:
	cp $(PLSLIB) /usr/local/lib
	ldconfig

clean:
	rm $(OBJFILES)

distclean:
	rm $(PLSLIB)
	rm bin/PlasmaTest
