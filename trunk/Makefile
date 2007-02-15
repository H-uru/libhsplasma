CC = g++
CFLAGS += -O2 -fPIC -Wall -g
CFLAGSEXTERN = -O2 -fPIC -g

LIBDIR=out/
OBJFILES=\
	$(LIBDIR)hsRefCnt.o \
	$(LIBDIR)hsStream.o \
	$(LIBDIR)plEncryptedStream.o \
	$(LIBDIR)hsElfStream.o \
	$(LIBDIR)plResManager.o \
	$(LIBDIR)plKeyCollector.o \
	$(LIBDIR)hsBitVector.o \
	$(LIBDIR)hsMatrix44.o \
	$(LIBDIR)hsGeometry3.o \
	$(LIBDIR)hsBounds.o \
	$(LIBDIR)PageID.o \
	$(LIBDIR)plCreatable.o \
	$(LIBDIR)plFactory.o \
	$(LIBDIR)plKey.o \
	$(LIBDIR)plReceiver.o \
	$(LIBDIR)hsKeyedObject.o \
	$(LIBDIR)plMessage.o \
	$(LIBDIR)plModifier.o \
	$(LIBDIR)plSynchedObject.o \
	$(LIBDIR)plObjInterface.o \
	$(LIBDIR)plAudioInterface.o \
	$(LIBDIR)plCoordinateInterface.o \
	$(LIBDIR)plDrawInterface.o \
	$(LIBDIR)plSimulationInterface.o \
	$(LIBDIR)plSceneObject.o \
	$(LIBDIR)plClothingItem.o \
	$(LIBDIR)plDrawableSpans.o \
	$(LIBDIR)plSpan.o \
	$(LIBDIR)plVertexSpan.o \
	$(LIBDIR)plIcicle.o \
	$(LIBDIR)plGeometrySpan.o \
	$(LIBDIR)plSpaceTree.o \
	$(LIBDIR)plBitmap.o \
	$(LIBDIR)plFont.o \
	$(LIBDIR)plMipmap.o \
	$(LIBDIR)plLightInfo.o \
	$(LIBDIR)plJPEG.o \
	$(LIBDIR)plCubicEnvironmap.o \
	$(LIBDIR)plFogEnvironment.o \
	$(LIBDIR)hsGDeviceRef.o \
	$(LIBDIR)plGBufferGroup.o \
	$(LIBDIR)plSceneNode.o \
	$(LIBDIR)hsGMaterial.o \
	$(LIBDIR)plLayerInterface.o \
	$(LIBDIR)plPythonFileMod.o \
	$(LIBDIR)rijndael.o
PLSLIB=lib/libPlasma.so.1.0.1

all: $(PLSLIB)

$(PLSLIB): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -shared -Wl,-soname,libPlasma.so.1 -o $(PLSLIB)

$(LIBDIR)hsRefCnt.o: CoreLib/hsRefCnt.h CoreLib/hsRefCnt.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsRefCnt.cpp -o $(LIBDIR)hsRefCnt.o

$(LIBDIR)hsStream.o: CoreLib/hsStream.h CoreLib/hsStream.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsStream.cpp -o $(LIBDIR)hsStream.o

$(LIBDIR)plEncryptedStream.o: CoreLib/plEncryptedStream.h CoreLib/plEncryptedStream.cpp
	$(CC) $(CFLAGS) -c CoreLib/plEncryptedStream.cpp -o $(LIBDIR)plEncryptedStream.o

$(LIBDIR)hsElfStream.o: CoreLib/hsElfStream.h CoreLib/hsElfStream.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsElfStream.cpp -o $(LIBDIR)hsElfStream.o

$(LIBDIR)hsBitVector.o: CoreLib/hsBitVector.h CoreLib/hsBitVector.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsBitVector.cpp -o $(LIBDIR)hsBitVector.o

$(LIBDIR)hsMatrix44.o: CoreLib/hsMatrix44.h CoreLib/hsMatrix44.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsMatrix44.cpp -o $(LIBDIR)hsMatrix44.o

$(LIBDIR)hsGeometry3.o: CoreLib/hsGeometry3.h CoreLib/hsGeometry3.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsGeometry3.cpp -o $(LIBDIR)hsGeometry3.o

$(LIBDIR)hsBounds.o: CoreLib/hsBounds.h CoreLib/hsBounds.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsBounds.cpp -o $(LIBDIR)hsBounds.o

$(LIBDIR)PageID.o: DynLib/PageID.h DynLib/PageID.cpp
	$(CC) $(CFLAGS) -c DynLib/PageID.cpp -o $(LIBDIR)PageID.o

$(LIBDIR)plCreatable.o: NucleusLib/pnFactory/plCreatable.h NucleusLib/pnFactory/plCreatable.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnFactory/plCreatable.cpp -o $(LIBDIR)plCreatable.o

$(LIBDIR)plFactory.o: NucleusLib/pnFactory/plFactory.h NucleusLib/pnFactory/plFactory.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnFactory/plFactory.cpp -o $(LIBDIR)plFactory.o

$(LIBDIR)plKey.o: NucleusLib/pnKeyedObject/plKey.h NucleusLib/pnKeyedObject/plKey.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnKeyedObject/plKey.cpp -o $(LIBDIR)plKey.o

$(LIBDIR)plReceiver.o: NucleusLib/pnKeyedObject/plReceiver.h NucleusLib/pnKeyedObject/plReceiver.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnKeyedObject/plReceiver.cpp -o $(LIBDIR)plReceiver.o

$(LIBDIR)hsKeyedObject.o: NucleusLib/pnKeyedObject/hsKeyedObject.h NucleusLib/pnKeyedObject/hsKeyedObject.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnKeyedObject/hsKeyedObject.cpp -o $(LIBDIR)hsKeyedObject.o

$(LIBDIR)plMessage.o: NucleusLib/pnMessage/plMessage.h NucleusLib/pnMessage/plMessage.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnMessage/plMessage.cpp -o $(LIBDIR)plMessage.o

$(LIBDIR)plModifier.o: NucleusLib/pnModifier/plModifier.h NucleusLib/pnModifier/plModifier.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnModifier/plModifier.cpp -o $(LIBDIR)plModifier.o

$(LIBDIR)plSynchedObject.o: NucleusLib/pnNetCommon/plSynchedObject.h NucleusLib/pnNetCommon/plSynchedObject.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnNetCommon/plSynchedObject.cpp -o $(LIBDIR)plSynchedObject.o

$(LIBDIR)plAudioInterface.o: NucleusLib/pnSceneObject/plAudioInterface.h NucleusLib/pnSceneObject/plAudioInterface.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plAudioInterface.cpp -o $(LIBDIR)plAudioInterface.o

$(LIBDIR)plCoordinateInterface.o: NucleusLib/pnSceneObject/plCoordinateInterface.h NucleusLib/pnSceneObject/plCoordinateInterface.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plCoordinateInterface.cpp -o $(LIBDIR)plCoordinateInterface.o

$(LIBDIR)plDrawInterface.o: NucleusLib/pnSceneObject/plDrawInterface.h NucleusLib/pnSceneObject/plDrawInterface.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plDrawInterface.cpp -o $(LIBDIR)plDrawInterface.o

$(LIBDIR)plObjInterface.o: NucleusLib/pnSceneObject/plObjInterface.h NucleusLib/pnSceneObject/plObjInterface.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plObjInterface.cpp -o $(LIBDIR)plObjInterface.o

$(LIBDIR)plSceneObject.o: NucleusLib/pnSceneObject/plSceneObject.h NucleusLib/pnSceneObject/plSceneObject.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plSceneObject.cpp -o $(LIBDIR)plSceneObject.o

$(LIBDIR)plSimulationInterface.o: NucleusLib/pnSceneObject/plSimulationInterface.h NucleusLib/pnSceneObject/plSimulationInterface.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnSceneObject/plSimulationInterface.cpp -o $(LIBDIR)plSimulationInterface.o

$(LIBDIR)plClothingItem.o: PubUtilLib/plAvatar/plClothingItem.h PubUtilLib/plAvatar/plClothingItem.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plAvatar/plClothingItem.cpp -o $(LIBDIR)plClothingItem.o

$(LIBDIR)plDrawableSpans.o: PubUtilLib/plDrawable/plDrawableSpans.h PubUtilLib/plDrawable/plDrawableSpans.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plDrawableSpans.cpp -o $(LIBDIR)plDrawableSpans.o

$(LIBDIR)plSpan.o: PubUtilLib/plDrawable/plSpan.h PubUtilLib/plDrawable/plSpan.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plSpan.cpp -o $(LIBDIR)plSpan.o

$(LIBDIR)plVertexSpan.o: PubUtilLib/plDrawable/plVertexSpan.h PubUtilLib/plDrawable/plVertexSpan.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plVertexSpan.cpp -o $(LIBDIR)plVertexSpan.o

$(LIBDIR)plIcicle.o: PubUtilLib/plDrawable/plIcicle.h PubUtilLib/plDrawable/plIcicle.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plIcicle.cpp -o $(LIBDIR)plIcicle.o

$(LIBDIR)plGeometrySpan.o: PubUtilLib/plDrawable/plGeometrySpan.h PubUtilLib/plDrawable/plGeometrySpan.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plGeometrySpan.cpp -o $(LIBDIR)plGeometrySpan.o

$(LIBDIR)plSpaceTree.o: PubUtilLib/plDrawable/plSpaceTree.h PubUtilLib/plDrawable/plSpaceTree.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plSpaceTree.cpp -o $(LIBDIR)plSpaceTree.o

$(LIBDIR)plBitmap.o: PubUtilLib/plGImage/plBitmap.h PubUtilLib/plGImage/plBitmap.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plGImage/plBitmap.cpp -o $(LIBDIR)plBitmap.o

$(LIBDIR)plCubicEnvironmap.o: PubUtilLib/plGImage/plCubicEnvironmap.h PubUtilLib/plGImage/plCubicEnvironmap.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plGImage/plCubicEnvironmap.cpp -o $(LIBDIR)plCubicEnvironmap.o

$(LIBDIR)plFont.o: PubUtilLib/plGImage/plFont.h PubUtilLib/plGImage/plFont.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plGImage/plFont.cpp -o $(LIBDIR)plFont.o

$(LIBDIR)plMipmap.o: PubUtilLib/plGImage/plMipmap.h PubUtilLib/plGImage/plMipmap.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plGImage/plMipmap.cpp -o $(LIBDIR)plMipmap.o

$(LIBDIR)plLightInfo.o: PubUtilLib/plGLight/plLightInfo.h PubUtilLib/plGLight/plLightInfo.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plGLight/plLightInfo.cpp -o $(LIBDIR)plLightInfo.o

$(LIBDIR)plJPEG.o: PubUtilLib/plJPEG/plJPEG.h PubUtilLib/plJPEG/plJPEG.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plJPEG/plJPEG.cpp -o $(LIBDIR)plJPEG.o

$(LIBDIR)plFogEnvironment.o: PubUtilLib/plPipeline/plFogEnvironment.h PubUtilLib/plPipeline/plFogEnvironment.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPipeline/plFogEnvironment.cpp -o $(LIBDIR)plFogEnvironment.o

$(LIBDIR)hsGDeviceRef.o: PubUtilLib/plPipeline/hsGDeviceRef.h PubUtilLib/plPipeline/hsGDeviceRef.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPipeline/hsGDeviceRef.cpp -o $(LIBDIR)hsGDeviceRef.o

$(LIBDIR)plGBufferGroup.o: PubUtilLib/plPipeline/plGBufferGroup.h PubUtilLib/plPipeline/plGBufferGroup.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPipeline/plGBufferGroup.cpp -o $(LIBDIR)plGBufferGroup.o

$(LIBDIR)plKeyCollector.o: PubUtilLib/plResMgr/plKeyCollector.h PubUtilLib/plResMgr/plKeyCollector.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plResMgr/plKeyCollector.cpp -o $(LIBDIR)plKeyCollector.o

$(LIBDIR)plResManager.o: PubUtilLib/plResMgr/plResManager.h PubUtilLib/plResMgr/plResManager.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plResMgr/plResManager.cpp -o $(LIBDIR)plResManager.o

$(LIBDIR)plSceneNode.o: PubUtilLib/plScene/plSceneNode.h PubUtilLib/plScene/plSceneNode.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plScene/plSceneNode.cpp -o $(LIBDIR)plSceneNode.o

$(LIBDIR)hsGMaterial.o: PubUtilLib/plSurface/hsGMaterial.h PubUtilLib/plSurface/hsGMaterial.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plSurface/hsGMaterial.cpp -o $(LIBDIR)hsGMaterial.o

$(LIBDIR)plLayerInterface.o: PubUtilLib/plSurface/plLayerInterface.h PubUtilLib/plSurface/plLayerInterface.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plSurface/plLayerInterface.cpp -o $(LIBDIR)plLayerInterface.o

$(LIBDIR)plPythonFileMod.o: FeatureLib/pfPython/plPythonFileMod.h FeatureLib/pfPython/plPythonFileMod.cpp
	$(CC) $(CFLAGS) -c FeatureLib/pfPython/plPythonFileMod.cpp -o $(LIBDIR)plPythonFileMod.o

$(LIBDIR)rijndael.o: rijndael.h rijndael.cpp
	$(CC) $(CFLAGSEXTERN) -c rijndael.cpp -o $(LIBDIR)rijndael.o

install:
	cp $(PLSLIB) /usr/local/lib
	ldconfig

clean:
	rm $(OBJFILES)

distclean:
	rm $(PLSLIB)
