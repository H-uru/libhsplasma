DMDOPTS=-O
OBJFILES=Plasma/CoreLib/hsStream.o \
	Plasma/DynLib/PageID.o Plasma/DynLib/plString.o \
	Plasma/NucleusLib/pnKeyedObject/plKey.o \
	Plasma/NucleusLib/pnKeyedObject/hsKeyedObject.o \
	Plasma/NucleusLib/pnNetCommon/plSynchedObject.o \
	Plasma/PubUtilLib/plGImage/plBitmap.o \
	Plasma/hsMatrix44.o Plasma/plCreatable.o Plasma/plReceiver.o

all: PlasmaTest

PlasmaTest: PlasmaTest.d $(OBJFILES)
	dmd $(DMDOPTS) $(OBJFILES) PlasmaTest.d

Plasma/CoreLib/hsStream.o: Plasma/CoreLib/hsStream.d
	dmd $(DMDOPTS) -c Plasma/CoreLib/hsStream.d -odPlasma/CoreLib/

Plasma/DynLib/PageID.o: Plasma/DynLib/PageID.d
	dmd $(DMDOPTS) -c Plasma/DynLib/PageID.d -odPlasma/DynLib/

Plasma/DynLib/plString.o: Plasma/DynLib/plString.d
	dmd $(DMDOPTS) -c Plasma/DynLib/plString.d -odPlasma/DynLib/

Plasma/NucleusLib/pnKeyedObject/plKey.o: Plasma/NucleusLib/pnKeyedObject/plKey.d
	dmd $(DMDOPTS) -c Plasma/NucleusLib/pnKeyedObject/plKey.d -odPlasma/NucleusLib/pnKeyedObject/

Plasma/NucleusLib/pnKeyedObject/hsKeyedObject.o: Plasma/NucleusLib/pnKeyedObject/hsKeyedObject.d
	dmd $(DMDOPTS) -c Plasma/NucleusLib/pnKeyedObject/hsKeyedObject.d -odPlasma/NucleusLib/pnKeyedObject/

Plasma/NucleusLib/pnNetCommon/plSynchedObject.o: Plasma/NucleusLib/pnNetCommon/plSynchedObject.d
	dmd $(DMDOPTS) -c Plasma/NucleusLib/pnNetCommon/plSynchedObject.d -odPlasma/NucleusLib/pnNetCommon/

Plasma/PubUtilLib/plGImage/plBitmap.o: Plasma/PubUtilLib/plGImage/plBitmap.d
	dmd $(DMDOPTS) -c Plasma/PubUtilLib/plGImage/plBitmap.d -odPlasma/PubUtilLib/plGImage/

Plasma/hsMatrix44.o: Plasma/hsMatrix44.d
	dmd $(DMDOPTS) -c Plasma/hsMatrix44.d -odPlasma/

Plasma/plCreatable.o: Plasma/plCreatable.d
	dmd $(DMDOPTS) -c Plasma/plCreatable.d -odPlasma/

Plasma/plReceiver.o: Plasma/plReceiver.d
	dmd $(DMDOPTS) -c Plasma/plReceiver.d -odPlasma/

clean:
	rm $(OBJFILES)
	rm PlasmaTest.o

