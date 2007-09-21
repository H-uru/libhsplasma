CC = g++
CFLAGS += -fPIC -Wall -g
CFLAGSEXTERN = -fPIC -g

LIBDIR=out/
OBJFILES=\
	$(LIBDIR)hsExceptions.o \
	$(LIBDIR)hsSemaphore.o \
	$(LIBDIR)hsStream.o \
	$(LIBDIR)plEncryptedStream.o \
	$(LIBDIR)hsElfStream.o \
	$(LIBDIR)plPageInfo.o \
	$(LIBDIR)plResManager.o \
	$(LIBDIR)plKeyCollector.o \
	$(LIBDIR)hsBitVector.o \
	$(LIBDIR)hsColor.o \
	$(LIBDIR)hsMatrix44.o \
	$(LIBDIR)hsGeometry3.o \
	$(LIBDIR)hsBounds.o \
	$(LIBDIR)plLoadMask.o \
	$(LIBDIR)plString.o \
	$(LIBDIR)PageID.o \
	$(LIBDIR)pdUnifiedTypeMap.o \
	$(LIBDIR)hsGMatState.o \
	$(LIBDIR)plCreatable.o \
	$(LIBDIR)plFactory.o \
	$(LIBDIR)plKey.o \
	$(LIBDIR)plReceiver.o \
	$(LIBDIR)hsKeyedObject.o \
	$(LIBDIR)plUoid.o \
	$(LIBDIR)proEventData.o \
	$(LIBDIR)plMessage.o \
	$(LIBDIR)plNotifyMsg.o \
	$(LIBDIR)plModifier.o \
	$(LIBDIR)plSynchedObject.o \
	$(LIBDIR)plObjInterface.o \
	$(LIBDIR)plAudioInterface.o \
	$(LIBDIR)plCoordinateInterface.o \
	$(LIBDIR)plDrawInterface.o \
	$(LIBDIR)plSimulationInterface.o \
	$(LIBDIR)plSceneObject.o \
	$(LIBDIR)plSoundBuffer.o \
	$(LIBDIR)plClothingItem.o \
	$(LIBDIR)plAGMasterMod.o \
	$(LIBDIR)plNPCSpawnMod.o \
	$(LIBDIR)plDrawableSpans.o \
	$(LIBDIR)plMorphArray.o \
	$(LIBDIR)plMorphDataSet.o \
	$(LIBDIR)plMorphDelta.o \
	$(LIBDIR)plSpan.o \
	$(LIBDIR)plVertexSpan.o \
	$(LIBDIR)plIcicle.o \
	$(LIBDIR)plGeometrySpan.o \
	$(LIBDIR)plSharedMesh.o \
	$(LIBDIR)plSpaceTree.o \
	$(LIBDIR)plBitmap.o \
	$(LIBDIR)plFont.o \
	$(LIBDIR)plMipmap.o \
	$(LIBDIR)plLightInfo.o \
	$(LIBDIR)plDirectionalLightInfo.o \
	$(LIBDIR)plOmniLightInfo.o \
	$(LIBDIR)plJPEG.o \
	$(LIBDIR)plImageLibMod.o \
	$(LIBDIR)plPhysical.o \
	$(LIBDIR)plHKPhysical.o \
	$(LIBDIR)plPXPhysical.o \
	$(LIBDIR)plODEPhysical.o \
	$(LIBDIR)plCubicEnvironmap.o \
	$(LIBDIR)plFogEnvironment.o \
	$(LIBDIR)hsGDeviceRef.o \
	$(LIBDIR)plGBufferGroup.o \
	$(LIBDIR)plVertCoder.o \
	$(LIBDIR)plSceneNode.o \
	$(LIBDIR)hsGMaterial.o \
	$(LIBDIR)plLayerInterface.o \
	$(LIBDIR)plLayer.o \
	$(LIBDIR)plPythonFileMod.o \
	$(LIBDIR)pfPrcHelper.o \
	$(LIBDIR)rijndael.o
PLSLIB=lib/libPlasma.so.1.0.1

all: $(PLSLIB)

$(PLSLIB): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -ljpeg -shared -Wl,-soname,libPlasma.so.1 -o $(PLSLIB)

$(LIBDIR)hsExceptions.o: CoreLib/hsExceptions.h CoreLib/hsExceptions.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsExceptions.cpp -o $(LIBDIR)hsExceptions.o

$(LIBDIR)hsSemaphore.o: CoreLib/hsSemaphore.h CoreLib/hsSemaphore.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsSemaphore.cpp -o $(LIBDIR)hsSemaphore.o

$(LIBDIR)hsStream.o: CoreLib/hsStream.h CoreLib/hsStream.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsStream.cpp -o $(LIBDIR)hsStream.o

$(LIBDIR)plEncryptedStream.o: CoreLib/plEncryptedStream.h CoreLib/plEncryptedStream.cpp
	$(CC) $(CFLAGS) -c CoreLib/plEncryptedStream.cpp -o $(LIBDIR)plEncryptedStream.o

$(LIBDIR)hsElfStream.o: CoreLib/hsElfStream.h CoreLib/hsElfStream.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsElfStream.cpp -o $(LIBDIR)hsElfStream.o

$(LIBDIR)hsBitVector.o: CoreLib/hsBitVector.h CoreLib/hsBitVector.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsBitVector.cpp -o $(LIBDIR)hsBitVector.o

$(LIBDIR)hsColor.o: CoreLib/hsColor.h CoreLib/hsColor.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsColor.cpp -o $(LIBDIR)hsColor.o

$(LIBDIR)hsMatrix44.o: CoreLib/hsMatrix44.h CoreLib/hsMatrix44.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsMatrix44.cpp -o $(LIBDIR)hsMatrix44.o

$(LIBDIR)hsGeometry3.o: CoreLib/hsGeometry3.h CoreLib/hsGeometry3.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsGeometry3.cpp -o $(LIBDIR)hsGeometry3.o

$(LIBDIR)hsBounds.o: CoreLib/hsBounds.h CoreLib/hsBounds.cpp
	$(CC) $(CFLAGS) -c CoreLib/hsBounds.cpp -o $(LIBDIR)hsBounds.o

$(LIBDIR)plLoadMask.o: CoreLib/plLoadMask.h CoreLib/plLoadMask.cpp
	$(CC) $(CFLAGS) -c CoreLib/plLoadMask.cpp -o $(LIBDIR)plLoadMask.o

$(LIBDIR)plString.o: CoreLib/plString.h CoreLib/plString.cpp
	$(CC) $(CFLAGS) -c CoreLib/plString.cpp -o $(LIBDIR)plString.o

$(LIBDIR)PageID.o: DynLib/PageID.h DynLib/PageID.cpp
	$(CC) $(CFLAGS) -c DynLib/PageID.cpp -o $(LIBDIR)PageID.o

$(LIBDIR)pdUnifiedTypeMap.o: DynLib/pdUnifiedTypeMap.h DynLib/pdUnifiedTypeMap.cpp
	$(CC) $(CFLAGS) -c DynLib/pdUnifiedTypeMap.cpp -o $(LIBDIR)pdUnifiedTypeMap.o

$(LIBDIR)hsGMatState.o: NucleusLib/inc/hsGMatState.h NucleusLib/inc/hsGMatState.cpp
	$(CC) $(CFLAGS) -c NucleusLib/inc/hsGMatState.cpp -o $(LIBDIR)hsGMatState.o

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

$(LIBDIR)plUoid.o: NucleusLib/pnKeyedObject/plUoid.h NucleusLib/pnKeyedObject/plUoid.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnKeyedObject/plUoid.cpp -o $(LIBDIR)plUoid.o

$(LIBDIR)proEventData.o: NucleusLib/pnMessage/proEventData.h NucleusLib/pnMessage/proEventData.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnMessage/proEventData.cpp -o $(LIBDIR)proEventData.o

$(LIBDIR)plMessage.o: NucleusLib/pnMessage/plMessage.h NucleusLib/pnMessage/plMessage.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnMessage/plMessage.cpp -o $(LIBDIR)plMessage.o

$(LIBDIR)plNotifyMsg.o: NucleusLib/pnMessage/plNotifyMsg.h NucleusLib/pnMessage/plNotifyMsg.cpp
	$(CC) $(CFLAGS) -c NucleusLib/pnMessage/plNotifyMsg.cpp -o $(LIBDIR)plNotifyMsg.o

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

$(LIBDIR)plSoundBuffer.o: PubUtilLib/plAudioCore/plSoundBuffer.h PubUtilLib/plAudioCore/plSoundBuffer.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plAudioCore/plSoundBuffer.cpp -o $(LIBDIR)plSoundBuffer.o

$(LIBDIR)plClothingItem.o: PubUtilLib/plAvatar/plClothingItem.h PubUtilLib/plAvatar/plClothingItem.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plAvatar/plClothingItem.cpp -o $(LIBDIR)plClothingItem.o

$(LIBDIR)plAGMasterMod.o: PubUtilLib/plAvatar/plAGMasterMod.h PubUtilLib/plAvatar/plAGMasterMod.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plAvatar/plAGMasterMod.cpp -o $(LIBDIR)plAGMasterMod.o

$(LIBDIR)plNPCSpawnMod.o: PubUtilLib/plAvatar/plNPCSpawnMod.h PubUtilLib/plAvatar/plNPCSpawnMod.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plAvatar/plNPCSpawnMod.cpp -o $(LIBDIR)plNPCSpawnMod.o

$(LIBDIR)plDrawableSpans.o: PubUtilLib/plDrawable/plDrawableSpans.h PubUtilLib/plDrawable/plDrawableSpans.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plDrawableSpans.cpp -o $(LIBDIR)plDrawableSpans.o

$(LIBDIR)plMorphArray.o: PubUtilLib/plDrawable/plMorphArray.h PubUtilLib/plDrawable/plMorphArray.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plMorphArray.cpp -o $(LIBDIR)plMorphArray.o

$(LIBDIR)plMorphDataSet.o: PubUtilLib/plDrawable/plMorphDataSet.h PubUtilLib/plDrawable/plMorphDataSet.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plMorphDataSet.cpp -o $(LIBDIR)plMorphDataSet.o

$(LIBDIR)plMorphDelta.o: PubUtilLib/plDrawable/plMorphDelta.h PubUtilLib/plDrawable/plMorphDelta.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plMorphDelta.cpp -o $(LIBDIR)plMorphDelta.o

$(LIBDIR)plSpan.o: PubUtilLib/plDrawable/plSpan.h PubUtilLib/plDrawable/plSpan.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plSpan.cpp -o $(LIBDIR)plSpan.o

$(LIBDIR)plVertexSpan.o: PubUtilLib/plDrawable/plVertexSpan.h PubUtilLib/plDrawable/plVertexSpan.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plVertexSpan.cpp -o $(LIBDIR)plVertexSpan.o

$(LIBDIR)plIcicle.o: PubUtilLib/plDrawable/plIcicle.h PubUtilLib/plDrawable/plIcicle.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plIcicle.cpp -o $(LIBDIR)plIcicle.o

$(LIBDIR)plGeometrySpan.o: PubUtilLib/plDrawable/plGeometrySpan.h PubUtilLib/plDrawable/plGeometrySpan.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plGeometrySpan.cpp -o $(LIBDIR)plGeometrySpan.o

$(LIBDIR)plSharedMesh.o: PubUtilLib/plDrawable/plSharedMesh.h PubUtilLib/plDrawable/plSharedMesh.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plDrawable/plSharedMesh.cpp -o $(LIBDIR)plSharedMesh.o

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

$(LIBDIR)plDirectionalLightInfo.o: PubUtilLib/plGLight/plDirectionalLightInfo.h PubUtilLib/plGLight/plDirectionalLightInfo.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plGLight/plDirectionalLightInfo.cpp -o $(LIBDIR)plDirectionalLightInfo.o

$(LIBDIR)plOmniLightInfo.o: PubUtilLib/plGLight/plOmniLightInfo.h PubUtilLib/plGLight/plOmniLightInfo.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plGLight/plOmniLightInfo.cpp -o $(LIBDIR)plOmniLightInfo.o

$(LIBDIR)plJPEG.o: PubUtilLib/plJPEG/plJPEG.h PubUtilLib/plJPEG/plJPEG.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plJPEG/plJPEG.cpp -o $(LIBDIR)plJPEG.o

$(LIBDIR)plImageLibMod.o: PubUtilLib/plModifier/plImageLibMod.h PubUtilLib/plModifier/plImageLibMod.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plModifier/plImageLibMod.cpp -o $(LIBDIR)plImageLibMod.o

$(LIBDIR)plPhysical.o: PubUtilLib/plPhysics/plPhysical.h PubUtilLib/plPhysics/plPhysical.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPhysics/plPhysical.cpp -o $(LIBDIR)plPhysical.o

$(LIBDIR)plHKPhysical.o: PubUtilLib/plPhysics/plHKPhysical.h PubUtilLib/plPhysics/plHKPhysical.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPhysics/plHKPhysical.cpp -o $(LIBDIR)plHKPhysical.o

$(LIBDIR)plPXPhysical.o: PubUtilLib/plPhysics/plPXPhysical.h PubUtilLib/plPhysics/plPXPhysical.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPhysics/plPXPhysical.cpp -o $(LIBDIR)plPXPhysical.o

$(LIBDIR)plODEPhysical.o: PubUtilLib/plPhysics/plODEPhysical.h PubUtilLib/plPhysics/plODEPhysical.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPhysics/plODEPhysical.cpp -o $(LIBDIR)plODEPhysical.o

$(LIBDIR)plFogEnvironment.o: PubUtilLib/plPipeline/plFogEnvironment.h PubUtilLib/plPipeline/plFogEnvironment.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPipeline/plFogEnvironment.cpp -o $(LIBDIR)plFogEnvironment.o

$(LIBDIR)hsGDeviceRef.o: PubUtilLib/plPipeline/hsGDeviceRef.h PubUtilLib/plPipeline/hsGDeviceRef.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPipeline/hsGDeviceRef.cpp -o $(LIBDIR)hsGDeviceRef.o

$(LIBDIR)plGBufferGroup.o: PubUtilLib/plPipeline/plGBufferGroup.h PubUtilLib/plPipeline/plGBufferGroup.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPipeline/plGBufferGroup.cpp -o $(LIBDIR)plGBufferGroup.o

$(LIBDIR)plVertCoder.o: PubUtilLib/plPipeline/plVertCoder.h PubUtilLib/plPipeline/plVertCoder.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plPipeline/plVertCoder.cpp -o $(LIBDIR)plVertCoder.o

$(LIBDIR)plKeyCollector.o: PubUtilLib/plResMgr/plKeyCollector.h PubUtilLib/plResMgr/plKeyCollector.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plResMgr/plKeyCollector.cpp -o $(LIBDIR)plKeyCollector.o

$(LIBDIR)plPageInfo.o: PubUtilLib/plResMgr/plPageInfo.h PubUtilLib/plResMgr/plPageInfo.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plResMgr/plPageInfo.cpp -o $(LIBDIR)plPageInfo.o

$(LIBDIR)plResManager.o: PubUtilLib/plResMgr/plResManager.h PubUtilLib/plResMgr/plResManager.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plResMgr/plResManager.cpp -o $(LIBDIR)plResManager.o

$(LIBDIR)plSceneNode.o: PubUtilLib/plScene/plSceneNode.h PubUtilLib/plScene/plSceneNode.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plScene/plSceneNode.cpp -o $(LIBDIR)plSceneNode.o

$(LIBDIR)hsGMaterial.o: PubUtilLib/plSurface/hsGMaterial.h PubUtilLib/plSurface/hsGMaterial.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plSurface/hsGMaterial.cpp -o $(LIBDIR)hsGMaterial.o

$(LIBDIR)plLayerInterface.o: PubUtilLib/plSurface/plLayerInterface.h PubUtilLib/plSurface/plLayerInterface.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plSurface/plLayerInterface.cpp -o $(LIBDIR)plLayerInterface.o

$(LIBDIR)plLayer.o: PubUtilLib/plSurface/plLayer.h PubUtilLib/plSurface/plLayer.cpp
	$(CC) $(CFLAGS) -c PubUtilLib/plSurface/plLayer.cpp -o $(LIBDIR)plLayer.o

$(LIBDIR)plPythonFileMod.o: FeatureLib/pfPython/plPythonFileMod.h FeatureLib/pfPython/plPythonFileMod.cpp
	$(CC) $(CFLAGS) -c FeatureLib/pfPython/plPythonFileMod.cpp -o $(LIBDIR)plPythonFileMod.o

$(LIBDIR)pfPrcHelper.o: FeatureLib/pfPRC/pfPrcHelper.h FeatureLib/pfPRC/pfPrcHelper.cpp
	$(CC) $(CFLAGS) -c FeatureLib/pfPRC/pfPrcHelper.cpp -o $(LIBDIR)pfPrcHelper.o

$(LIBDIR)rijndael.o: rijndael.h rijndael.cpp
	$(CC) $(CFLAGSEXTERN) -c rijndael.cpp -o $(LIBDIR)rijndael.o

install:
	cp $(PLSLIB) /usr/local/lib
	ldconfig

clean:
	rm -f $(OBJFILES)

distclean:
	rm -f $(PLSLIB)
