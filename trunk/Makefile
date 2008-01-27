CXX = g++
CXXFLAGS += -I. -fPIC -Wall -g
CXXFLAGSEXTERN = -fPIC -O2

LIBDIR=out/
OBJFILES=\
	$(LIBDIR)hsExceptions.o \
	$(LIBDIR)hsSemaphore.o \
	$(LIBDIR)hsStream.o \
	$(LIBDIR)hsStdioStream.o \
	$(LIBDIR)plEncryptedStream.o \
	$(LIBDIR)hsElfStream.o \
	$(LIBDIR)plDebug.o \
	$(LIBDIR)plAgeInfo.o \
	$(LIBDIR)plKeyCollector.o \
	$(LIBDIR)plPageInfo.o \
	$(LIBDIR)plResManager.o \
	$(LIBDIR)hsBitVector.o \
	$(LIBDIR)hsColor.o \
	$(LIBDIR)hsMatrix33.o \
	$(LIBDIR)hsMatrix44.o \
	$(LIBDIR)hsGeometry3.o \
	$(LIBDIR)hsQuat.o \
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
	$(LIBDIR)plMsgForwarder.o \
	$(LIBDIR)plUoid.o \
	$(LIBDIR)proEventData.o \
	$(LIBDIR)plMessage.o \
	$(LIBDIR)plCameraMsg.o \
	$(LIBDIR)plEnableMsg.o \
	$(LIBDIR)plEventCallbackMsg.o \
	$(LIBDIR)plNotifyMsg.o \
	$(LIBDIR)plMessageWithCallbacks.o \
	$(LIBDIR)plSimStateMsg.o \
	$(LIBDIR)plSimulationMsg.o \
	$(LIBDIR)plSoundMsg.o \
	$(LIBDIR)plModifier.o \
	$(LIBDIR)plLogicModBase.o \
	$(LIBDIR)plResponderModifier.o \
	$(LIBDIR)plSynchedObject.o \
	$(LIBDIR)plObjInterface.o \
	$(LIBDIR)plAudioInterface.o \
	$(LIBDIR)plCoordinateInterface.o \
	$(LIBDIR)plDrawInterface.o \
	$(LIBDIR)plSimulationInterface.o \
	$(LIBDIR)plSceneObject.o \
	$(LIBDIR)plAudible.o \
	$(LIBDIR)plEAXEffects.o \
	$(LIBDIR)plSound.o \
	$(LIBDIR)plWin32Sound.o \
	$(LIBDIR)plWin32StaticSound.o \
	$(LIBDIR)plSoundBuffer.o \
	$(LIBDIR)plAnimStage.o \
	$(LIBDIR)plAvLadderMod.o \
	$(LIBDIR)plClothingItem.o \
	$(LIBDIR)plAGMasterMod.o \
	$(LIBDIR)plMultistageBehMod.o \
	$(LIBDIR)plNPCSpawnMod.o \
	$(LIBDIR)plOneShotMod.o \
	$(LIBDIR)plDrawableSpans.o \
	$(LIBDIR)plDynaDecalMgr.o \
	$(LIBDIR)plDynaRippleMgr.o \
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
	$(LIBDIR)plShadowCaster.o \
	$(LIBDIR)plShadowMaster.o \
	$(LIBDIR)plAnimTimeConvert.o \
	$(LIBDIR)plAnimPath.o \
	$(LIBDIR)plATCEaseCurves.o \
	$(LIBDIR)plController.o \
	$(LIBDIR)plKeyControllers.o \
	$(LIBDIR)plLeafController.o \
	$(LIBDIR)plPosController.o \
	$(LIBDIR)plRotController.o \
	$(LIBDIR)plScaleController.o \
	$(LIBDIR)plTMController.o \
	$(LIBDIR)hsKeys.o \
	$(LIBDIR)UruKeys.o \
	$(LIBDIR)plHardRegion.o \
	$(LIBDIR)plHardRegionPlanes.o \
	$(LIBDIR)plRegionBase.o \
	$(LIBDIR)plSoftVolume.o \
	$(LIBDIR)plVolumeIsect.o \
	$(LIBDIR)plJPEG.o \
	$(LIBDIR)plAnimCmdMsg.o \
	$(LIBDIR)plExcludeRegionMsg.o \
	$(LIBDIR)plLinkToAgeMsg.o \
	$(LIBDIR)plOneShotCallbacks.o \
	$(LIBDIR)plResponderMsg.o \
	$(LIBDIR)plTimerCallbackMsg.o \
	$(LIBDIR)plTransitionMsg.o \
	$(LIBDIR)plExcludeRegionModifier.o \
	$(LIBDIR)plImageLibMod.o \
	$(LIBDIR)plInterfaceInfoModifier.o \
	$(LIBDIR)plLogicModifier.o \
	$(LIBDIR)plSpawnModifier.o \
	$(LIBDIR)plNetServerSessionInfo.o \
	$(LIBDIR)plSpawnPointInfo.o \
	$(LIBDIR)plBoundInterface.o \
	$(LIBDIR)plConvexVolume.o \
	$(LIBDIR)plParticleEffect.o \
	$(LIBDIR)plCollisionDetector.o \
	$(LIBDIR)plDetectorModifier.o \
	$(LIBDIR)plObjectInVolumeDetector.o \
	$(LIBDIR)plPhysical.o \
	$(LIBDIR)plHKPhysical.o \
	$(LIBDIR)plPXPhysical.o \
	$(LIBDIR)plODEPhysical.o \
	$(LIBDIR)plPhysicalSndGroup.o \
	$(LIBDIR)plCubicEnvironmap.o \
	$(LIBDIR)plFogEnvironment.o \
	$(LIBDIR)hsGDeviceRef.o \
	$(LIBDIR)plGBufferGroup.o \
	$(LIBDIR)plVertCoder.o \
	$(LIBDIR)plPostEffectMod.o \
	$(LIBDIR)plSceneNode.o \
	$(LIBDIR)plVisRegion.o \
	$(LIBDIR)hsGMaterial.o \
	$(LIBDIR)plLayerInterface.o \
	$(LIBDIR)plLayer.o \
	$(LIBDIR)plLayerAnimation.o \
	$(LIBDIR)plLayerMovie.o \
	$(LIBDIR)hsAffineParts.o \
	$(LIBDIR)plUUID.o \
	$(LIBDIR)plLineFollowMod.o \
	$(LIBDIR)plRandomCommandMod.o \
	$(LIBDIR)plStereizer.o \
	$(LIBDIR)plViewFaceModifier.o \
	$(LIBDIR)plRandomSoundMod.o \
	$(LIBDIR)plConditionalObject.o \
	$(LIBDIR)plActivatorConditionalObject.o \
	$(LIBDIR)plAnimationEventConditionalObject.o \
	$(LIBDIR)plBooleanConditionalObject.o \
	$(LIBDIR)plControlEventConditionalObject.o \
	$(LIBDIR)plDetectConditionalObjects.o \
	$(LIBDIR)plFacingConditionalObject.o \
	$(LIBDIR)plKeyPressConditionalObject.o \
	$(LIBDIR)plPickedConditionalObject.o \
	$(LIBDIR)plPythonFileModConditionalObject.o \
	$(LIBDIR)plVolumeSensorConditionalObject.o \
	$(LIBDIR)pfGUIControlHandlers.o \
	$(LIBDIR)pfGUIControlMod.o \
	$(LIBDIR)pfGUIButtonMod.o \
	$(LIBDIR)pfGUICheckBoxCtrl.o \
	$(LIBDIR)pfGUIClickMapCtrl.o \
	$(LIBDIR)pfGUIDialogMod.o \
	$(LIBDIR)pfGUIDragBarCtrl.o \
	$(LIBDIR)pfGUIDraggableMod.o \
	$(LIBDIR)pfGUIDynDisplayCtrl.o \
	$(LIBDIR)pfGUIEditBoxMod.o \
	$(LIBDIR)pfGUIListBoxMod.o \
	$(LIBDIR)pfGUIMultiLineEditCtrl.o \
	$(LIBDIR)pfGUIPopUpMenu.o \
	$(LIBDIR)pfGUIRadioGroupCtrl.o \
	$(LIBDIR)pfGUISkin.o \
	$(LIBDIR)pfGUITextBoxMod.o \
	$(LIBDIR)pfGUIValueCtrl.o \
	$(LIBDIR)pfGUIKnobCtrl.o \
	$(LIBDIR)pfGUIProgressCtrl.o \
	$(LIBDIR)pfGUIUpDownPairMod.o \
	$(LIBDIR)plArmatureEffectMsg.o \
	$(LIBDIR)plPythonFileMod.o \
	$(LIBDIR)pfPrcHelper.o \
	$(LIBDIR)rijndael.o
PLSLIB=lib/libPlasma.so.1.0.1

all: $(PLSLIB) lib/libPlasma.so

lib/libPlasma.so: $(PLSLIB)
	( cd lib ; ln -s libPlasma.so.1.0.1 libPlasma.so )
	( cd lib ; ln -s libPlasma.so.1.0.1 libPlasma.so.1 )

$(PLSLIB): $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(OBJFILES) -ljpeg -shared -Wl,-soname,libPlasma.so.1 -o $(PLSLIB)

$(LIBDIR)hsExceptions.o: CoreLib/hsExceptions.h CoreLib/hsExceptions.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsExceptions.cpp -o $(LIBDIR)hsExceptions.o

$(LIBDIR)hsSemaphore.o: CoreLib/hsSemaphore.h CoreLib/hsSemaphore.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsSemaphore.cpp -o $(LIBDIR)hsSemaphore.o

$(LIBDIR)hsStream.o: CoreLib/hsStream.h CoreLib/hsStream.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsStream.cpp -o $(LIBDIR)hsStream.o

$(LIBDIR)hsStdioStream.o: CoreLib/hsStdioStream.h CoreLib/hsStdioStream.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsStdioStream.cpp -o $(LIBDIR)hsStdioStream.o

$(LIBDIR)plEncryptedStream.o: CoreLib/plEncryptedStream.h CoreLib/plEncryptedStream.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/plEncryptedStream.cpp -o $(LIBDIR)plEncryptedStream.o

$(LIBDIR)hsElfStream.o: CoreLib/hsElfStream.h CoreLib/hsElfStream.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsElfStream.cpp -o $(LIBDIR)hsElfStream.o

$(LIBDIR)plDebug.o: CoreLib/plDebug.h CoreLib/plDebug.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/plDebug.cpp -o $(LIBDIR)plDebug.o

$(LIBDIR)hsBitVector.o: CoreLib/hsBitVector.h CoreLib/hsBitVector.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsBitVector.cpp -o $(LIBDIR)hsBitVector.o

$(LIBDIR)hsColor.o: CoreLib/hsColor.h CoreLib/hsColor.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsColor.cpp -o $(LIBDIR)hsColor.o

$(LIBDIR)hsMatrix33.o: CoreLib/hsMatrix33.h CoreLib/hsMatrix33.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsMatrix33.cpp -o $(LIBDIR)hsMatrix33.o

$(LIBDIR)hsMatrix44.o: CoreLib/hsMatrix44.h CoreLib/hsMatrix44.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsMatrix44.cpp -o $(LIBDIR)hsMatrix44.o

$(LIBDIR)hsGeometry3.o: CoreLib/hsGeometry3.h CoreLib/hsGeometry3.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsGeometry3.cpp -o $(LIBDIR)hsGeometry3.o

$(LIBDIR)hsQuat.o: CoreLib/hsQuat.h CoreLib/hsQuat.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsQuat.cpp -o $(LIBDIR)hsQuat.o

$(LIBDIR)hsBounds.o: CoreLib/hsBounds.h CoreLib/hsBounds.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsBounds.cpp -o $(LIBDIR)hsBounds.o

$(LIBDIR)plLoadMask.o: CoreLib/plLoadMask.h CoreLib/plLoadMask.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/plLoadMask.cpp -o $(LIBDIR)plLoadMask.o

$(LIBDIR)plString.o: CoreLib/plString.h CoreLib/plString.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/plString.cpp -o $(LIBDIR)plString.o

$(LIBDIR)PageID.o: DynLib/PageID.h DynLib/PageID.cpp
	$(CXX) $(CXXFLAGS) -c DynLib/PageID.cpp -o $(LIBDIR)PageID.o

$(LIBDIR)pdUnifiedTypeMap.o: DynLib/pdUnifiedTypeMap.h DynLib/pdUnifiedTypeMap.cpp
	$(CXX) $(CXXFLAGS) -c DynLib/pdUnifiedTypeMap.cpp -o $(LIBDIR)pdUnifiedTypeMap.o

$(LIBDIR)hsGMatState.o: NucleusLib/inc/hsGMatState.h NucleusLib/inc/hsGMatState.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/inc/hsGMatState.cpp -o $(LIBDIR)hsGMatState.o

$(LIBDIR)plCreatable.o: NucleusLib/pnFactory/plCreatable.h NucleusLib/pnFactory/plCreatable.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnFactory/plCreatable.cpp -o $(LIBDIR)plCreatable.o

$(LIBDIR)plFactory.o: NucleusLib/pnFactory/plFactory.h NucleusLib/pnFactory/plFactory.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnFactory/plFactory.cpp -o $(LIBDIR)plFactory.o

$(LIBDIR)plKey.o: NucleusLib/pnKeyedObject/plKey.h NucleusLib/pnKeyedObject/plKey.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnKeyedObject/plKey.cpp -o $(LIBDIR)plKey.o

$(LIBDIR)plReceiver.o: NucleusLib/pnKeyedObject/plReceiver.h NucleusLib/pnKeyedObject/plReceiver.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnKeyedObject/plReceiver.cpp -o $(LIBDIR)plReceiver.o

$(LIBDIR)hsKeyedObject.o: NucleusLib/pnKeyedObject/hsKeyedObject.h NucleusLib/pnKeyedObject/hsKeyedObject.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnKeyedObject/hsKeyedObject.cpp -o $(LIBDIR)hsKeyedObject.o

$(LIBDIR)plMsgForwarder.o: NucleusLib/pnKeyedObject/plMsgForwarder.h NucleusLib/pnKeyedObject/plMsgForwarder.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnKeyedObject/plMsgForwarder.cpp -o $(LIBDIR)plMsgForwarder.o

$(LIBDIR)plUoid.o: NucleusLib/pnKeyedObject/plUoid.h NucleusLib/pnKeyedObject/plUoid.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnKeyedObject/plUoid.cpp -o $(LIBDIR)plUoid.o

$(LIBDIR)proEventData.o: NucleusLib/pnMessage/proEventData.h NucleusLib/pnMessage/proEventData.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/proEventData.cpp -o $(LIBDIR)proEventData.o

$(LIBDIR)plMessage.o: NucleusLib/pnMessage/plMessage.h NucleusLib/pnMessage/plMessage.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plMessage.cpp -o $(LIBDIR)plMessage.o

$(LIBDIR)plCameraMsg.o: NucleusLib/pnMessage/plCameraMsg.h NucleusLib/pnMessage/plCameraMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plCameraMsg.cpp -o $(LIBDIR)plCameraMsg.o

$(LIBDIR)plEnableMsg.o: NucleusLib/pnMessage/plEnableMsg.h NucleusLib/pnMessage/plEnableMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plEnableMsg.cpp -o $(LIBDIR)plEnableMsg.o

$(LIBDIR)plEventCallbackMsg.o: NucleusLib/pnMessage/plEventCallbackMsg.h NucleusLib/pnMessage/plEventCallbackMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plEventCallbackMsg.cpp -o $(LIBDIR)plEventCallbackMsg.o

$(LIBDIR)plNotifyMsg.o: NucleusLib/pnMessage/plNotifyMsg.h NucleusLib/pnMessage/plNotifyMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plNotifyMsg.cpp -o $(LIBDIR)plNotifyMsg.o

$(LIBDIR)plMessageWithCallbacks.o: NucleusLib/pnMessage/plMessageWithCallbacks.h NucleusLib/pnMessage/plMessageWithCallbacks.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plMessageWithCallbacks.cpp -o $(LIBDIR)plMessageWithCallbacks.o

$(LIBDIR)plSimStateMsg.o: NucleusLib/pnMessage/plSimStateMsg.h NucleusLib/pnMessage/plSimStateMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plSimStateMsg.cpp -o $(LIBDIR)plSimStateMsg.o

$(LIBDIR)plSimulationMsg.o: NucleusLib/pnMessage/plSimulationMsg.h NucleusLib/pnMessage/plSimulationMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plSimulationMsg.cpp -o $(LIBDIR)plSimulationMsg.o

$(LIBDIR)plSoundMsg.o: NucleusLib/pnMessage/plSoundMsg.h NucleusLib/pnMessage/plSoundMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plSoundMsg.cpp -o $(LIBDIR)plSoundMsg.o

$(LIBDIR)plModifier.o: NucleusLib/pnModifier/plModifier.h NucleusLib/pnModifier/plModifier.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnModifier/plModifier.cpp -o $(LIBDIR)plModifier.o

$(LIBDIR)plLogicModBase.o: NucleusLib/pnModifier/plLogicModBase.h NucleusLib/pnModifier/plLogicModBase.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnModifier/plLogicModBase.cpp -o $(LIBDIR)plLogicModBase.o

$(LIBDIR)plSynchedObject.o: NucleusLib/pnNetCommon/plSynchedObject.h NucleusLib/pnNetCommon/plSynchedObject.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnNetCommon/plSynchedObject.cpp -o $(LIBDIR)plSynchedObject.o

$(LIBDIR)plAudioInterface.o: NucleusLib/pnSceneObject/plAudioInterface.h NucleusLib/pnSceneObject/plAudioInterface.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plAudioInterface.cpp -o $(LIBDIR)plAudioInterface.o

$(LIBDIR)plCoordinateInterface.o: NucleusLib/pnSceneObject/plCoordinateInterface.h NucleusLib/pnSceneObject/plCoordinateInterface.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plCoordinateInterface.cpp -o $(LIBDIR)plCoordinateInterface.o

$(LIBDIR)plDrawInterface.o: NucleusLib/pnSceneObject/plDrawInterface.h NucleusLib/pnSceneObject/plDrawInterface.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plDrawInterface.cpp -o $(LIBDIR)plDrawInterface.o

$(LIBDIR)plObjInterface.o: NucleusLib/pnSceneObject/plObjInterface.h NucleusLib/pnSceneObject/plObjInterface.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plObjInterface.cpp -o $(LIBDIR)plObjInterface.o

$(LIBDIR)plSceneObject.o: NucleusLib/pnSceneObject/plSceneObject.h NucleusLib/pnSceneObject/plSceneObject.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plSceneObject.cpp -o $(LIBDIR)plSceneObject.o

$(LIBDIR)plSimulationInterface.o: NucleusLib/pnSceneObject/plSimulationInterface.h NucleusLib/pnSceneObject/plSimulationInterface.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plSimulationInterface.cpp -o $(LIBDIR)plSimulationInterface.o

$(LIBDIR)plAudible.o: PubUtilLib/plAudible/plAudible.h PubUtilLib/plAudible/plAudible.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudible/plAudible.cpp -o $(LIBDIR)plAudible.o

$(LIBDIR)plEAXEffects.o: PubUtilLib/plAudio/plEAXEffects.h PubUtilLib/plAudio/plEAXEffects.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudio/plEAXEffects.cpp -o $(LIBDIR)plEAXEffects.o

$(LIBDIR)plSound.o: PubUtilLib/plAudio/plSound.h PubUtilLib/plAudio/plSound.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudio/plSound.cpp -o $(LIBDIR)plSound.o

$(LIBDIR)plWin32Sound.o: PubUtilLib/plAudio/plWin32Sound.h PubUtilLib/plAudio/plWin32Sound.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudio/plWin32Sound.cpp -o $(LIBDIR)plWin32Sound.o

$(LIBDIR)plWin32StaticSound.o: PubUtilLib/plAudio/plWin32StaticSound.h PubUtilLib/plAudio/plWin32StaticSound.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudio/plWin32StaticSound.cpp -o $(LIBDIR)plWin32StaticSound.o

$(LIBDIR)plSoundBuffer.o: PubUtilLib/plAudioCore/plSoundBuffer.h PubUtilLib/plAudioCore/plSoundBuffer.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudioCore/plSoundBuffer.cpp -o $(LIBDIR)plSoundBuffer.o

$(LIBDIR)plAnimStage.o: PubUtilLib/plAvatar/plAnimStage.h PubUtilLib/plAvatar/plAnimStage.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plAnimStage.cpp -o $(LIBDIR)plAnimStage.o

$(LIBDIR)plAvLadderMod.o: PubUtilLib/plAvatar/plAvLadderMod.h PubUtilLib/plAvatar/plAvLadderMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plAvLadderMod.cpp -o $(LIBDIR)plAvLadderMod.o

$(LIBDIR)plClothingItem.o: PubUtilLib/plAvatar/plClothingItem.h PubUtilLib/plAvatar/plClothingItem.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plClothingItem.cpp -o $(LIBDIR)plClothingItem.o

$(LIBDIR)plAGMasterMod.o: PubUtilLib/plAvatar/plAGMasterMod.h PubUtilLib/plAvatar/plAGMasterMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plAGMasterMod.cpp -o $(LIBDIR)plAGMasterMod.o

$(LIBDIR)plMultistageBehMod.o: PubUtilLib/plAvatar/plMultistageBehMod.h PubUtilLib/plAvatar/plMultistageBehMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plMultistageBehMod.cpp -o $(LIBDIR)plMultistageBehMod.o

$(LIBDIR)plNPCSpawnMod.o: PubUtilLib/plAvatar/plNPCSpawnMod.h PubUtilLib/plAvatar/plNPCSpawnMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plNPCSpawnMod.cpp -o $(LIBDIR)plNPCSpawnMod.o

$(LIBDIR)plOneShotMod.o: PubUtilLib/plAvatar/plOneShotMod.h PubUtilLib/plAvatar/plOneShotMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plOneShotMod.cpp -o $(LIBDIR)plOneShotMod.o

$(LIBDIR)plDrawableSpans.o: PubUtilLib/plDrawable/plDrawableSpans.h PubUtilLib/plDrawable/plDrawableSpans.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plDrawableSpans.cpp -o $(LIBDIR)plDrawableSpans.o

$(LIBDIR)plDynaDecalMgr.o: PubUtilLib/plDrawable/plDynaDecalMgr.h PubUtilLib/plDrawable/plDynaDecalMgr.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plDynaDecalMgr.cpp -o $(LIBDIR)plDynaDecalMgr.o

$(LIBDIR)plDynaRippleMgr.o: PubUtilLib/plDrawable/plDynaRippleMgr.h PubUtilLib/plDrawable/plDynaRippleMgr.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plDynaRippleMgr.cpp -o $(LIBDIR)plDynaRippleMgr.o

$(LIBDIR)plMorphArray.o: PubUtilLib/plDrawable/plMorphArray.h PubUtilLib/plDrawable/plMorphArray.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plMorphArray.cpp -o $(LIBDIR)plMorphArray.o

$(LIBDIR)plMorphDataSet.o: PubUtilLib/plDrawable/plMorphDataSet.h PubUtilLib/plDrawable/plMorphDataSet.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plMorphDataSet.cpp -o $(LIBDIR)plMorphDataSet.o

$(LIBDIR)plMorphDelta.o: PubUtilLib/plDrawable/plMorphDelta.h PubUtilLib/plDrawable/plMorphDelta.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plMorphDelta.cpp -o $(LIBDIR)plMorphDelta.o

$(LIBDIR)plSpan.o: PubUtilLib/plDrawable/plSpan.h PubUtilLib/plDrawable/plSpan.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plSpan.cpp -o $(LIBDIR)plSpan.o

$(LIBDIR)plVertexSpan.o: PubUtilLib/plDrawable/plVertexSpan.h PubUtilLib/plDrawable/plVertexSpan.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plVertexSpan.cpp -o $(LIBDIR)plVertexSpan.o

$(LIBDIR)plIcicle.o: PubUtilLib/plDrawable/plIcicle.h PubUtilLib/plDrawable/plIcicle.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plIcicle.cpp -o $(LIBDIR)plIcicle.o

$(LIBDIR)plGeometrySpan.o: PubUtilLib/plDrawable/plGeometrySpan.h PubUtilLib/plDrawable/plGeometrySpan.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plGeometrySpan.cpp -o $(LIBDIR)plGeometrySpan.o

$(LIBDIR)plSharedMesh.o: PubUtilLib/plDrawable/plSharedMesh.h PubUtilLib/plDrawable/plSharedMesh.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plSharedMesh.cpp -o $(LIBDIR)plSharedMesh.o

$(LIBDIR)plSpaceTree.o: PubUtilLib/plDrawable/plSpaceTree.h PubUtilLib/plDrawable/plSpaceTree.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plSpaceTree.cpp -o $(LIBDIR)plSpaceTree.o

$(LIBDIR)plBitmap.o: PubUtilLib/plGImage/plBitmap.h PubUtilLib/plGImage/plBitmap.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGImage/plBitmap.cpp -o $(LIBDIR)plBitmap.o

$(LIBDIR)plCubicEnvironmap.o: PubUtilLib/plGImage/plCubicEnvironmap.h PubUtilLib/plGImage/plCubicEnvironmap.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGImage/plCubicEnvironmap.cpp -o $(LIBDIR)plCubicEnvironmap.o

$(LIBDIR)plFont.o: PubUtilLib/plGImage/plFont.h PubUtilLib/plGImage/plFont.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGImage/plFont.cpp -o $(LIBDIR)plFont.o

$(LIBDIR)plMipmap.o: PubUtilLib/plGImage/plMipmap.h PubUtilLib/plGImage/plMipmap.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGImage/plMipmap.cpp -o $(LIBDIR)plMipmap.o

$(LIBDIR)plLightInfo.o: PubUtilLib/plGLight/plLightInfo.h PubUtilLib/plGLight/plLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGLight/plLightInfo.cpp -o $(LIBDIR)plLightInfo.o

$(LIBDIR)plDirectionalLightInfo.o: PubUtilLib/plGLight/plDirectionalLightInfo.h PubUtilLib/plGLight/plDirectionalLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGLight/plDirectionalLightInfo.cpp -o $(LIBDIR)plDirectionalLightInfo.o

$(LIBDIR)plOmniLightInfo.o: PubUtilLib/plGLight/plOmniLightInfo.h PubUtilLib/plGLight/plOmniLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGLight/plOmniLightInfo.cpp -o $(LIBDIR)plOmniLightInfo.o

$(LIBDIR)plShadowCaster.o: PubUtilLib/plGLight/plShadowCaster.h PubUtilLib/plGLight/plShadowCaster.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGLight/plShadowCaster.cpp -o $(LIBDIR)plShadowCaster.o

$(LIBDIR)plShadowMaster.o: PubUtilLib/plGLight/plShadowMaster.h PubUtilLib/plGLight/plShadowMaster.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGLight/plShadowMaster.cpp -o $(LIBDIR)plShadowMaster.o

$(LIBDIR)plAnimTimeConvert.o: PubUtilLib/plInterp/plAnimTimeConvert.h PubUtilLib/plInterp/plAnimTimeConvert.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plAnimTimeConvert.cpp -o $(LIBDIR)plAnimTimeConvert.o

$(LIBDIR)plAnimPath.o: PubUtilLib/plInterp/plAnimPath.h PubUtilLib/plInterp/plAnimPath.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plAnimPath.cpp -o $(LIBDIR)plAnimPath.o

$(LIBDIR)plATCEaseCurves.o: PubUtilLib/plInterp/plATCEaseCurves.h PubUtilLib/plInterp/plATCEaseCurves.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plATCEaseCurves.cpp -o $(LIBDIR)plATCEaseCurves.o

$(LIBDIR)plController.o: PubUtilLib/plInterp/plController.h PubUtilLib/plInterp/plController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plController.cpp -o $(LIBDIR)plController.o

$(LIBDIR)plKeyControllers.o: PubUtilLib/plInterp/plKeyControllers.h PubUtilLib/plInterp/plKeyControllers.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plKeyControllers.cpp -o $(LIBDIR)plKeyControllers.o

$(LIBDIR)plLeafController.o: PubUtilLib/plInterp/plLeafController.h PubUtilLib/plInterp/plLeafController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plLeafController.cpp -o $(LIBDIR)plLeafController.o

$(LIBDIR)plPosController.o: PubUtilLib/plInterp/plPosController.h PubUtilLib/plInterp/plPosController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plPosController.cpp -o $(LIBDIR)plPosController.o

$(LIBDIR)plRotController.o: PubUtilLib/plInterp/plRotController.h PubUtilLib/plInterp/plRotController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plRotController.cpp -o $(LIBDIR)plRotController.o

$(LIBDIR)plScaleController.o: PubUtilLib/plInterp/plScaleController.h PubUtilLib/plInterp/plScaleController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plScaleController.cpp -o $(LIBDIR)plScaleController.o

$(LIBDIR)plTMController.o: PubUtilLib/plInterp/plTMController.h PubUtilLib/plInterp/plTMController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plTMController.cpp -o $(LIBDIR)plTMController.o

$(LIBDIR)hsKeys.o: PubUtilLib/plInterp/hsKeys.h PubUtilLib/plInterp/hsKeys.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/hsKeys.cpp -o $(LIBDIR)hsKeys.o

$(LIBDIR)UruKeys.o: PubUtilLib/plInterp/UruKeys.h PubUtilLib/plInterp/UruKeys.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/UruKeys.cpp -o $(LIBDIR)UruKeys.o

$(LIBDIR)plHardRegion.o: PubUtilLib/plIntersect/plHardRegion.h PubUtilLib/plIntersect/plHardRegion.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plIntersect/plHardRegion.cpp -o $(LIBDIR)plHardRegion.o

$(LIBDIR)plHardRegionPlanes.o: PubUtilLib/plIntersect/plHardRegionPlanes.h PubUtilLib/plIntersect/plHardRegionPlanes.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plIntersect/plHardRegionPlanes.cpp -o $(LIBDIR)plHardRegionPlanes.o

$(LIBDIR)plRegionBase.o: PubUtilLib/plIntersect/plRegionBase.h PubUtilLib/plIntersect/plRegionBase.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plIntersect/plRegionBase.cpp -o $(LIBDIR)plRegionBase.o

$(LIBDIR)plSoftVolume.o: PubUtilLib/plIntersect/plSoftVolume.h PubUtilLib/plIntersect/plSoftVolume.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plIntersect/plSoftVolume.cpp -o $(LIBDIR)plSoftVolume.o

$(LIBDIR)plVolumeIsect.o: PubUtilLib/plIntersect/plVolumeIsect.h PubUtilLib/plIntersect/plVolumeIsect.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plIntersect/plVolumeIsect.cpp -o $(LIBDIR)plVolumeIsect.o

$(LIBDIR)plJPEG.o: PubUtilLib/plJPEG/plJPEG.h PubUtilLib/plJPEG/plJPEG.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plJPEG/plJPEG.cpp -o $(LIBDIR)plJPEG.o

$(LIBDIR)plAnimCmdMsg.o: PubUtilLib/plMessage/plAnimCmdMsg.h PubUtilLib/plMessage/plAnimCmdMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plAnimCmdMsg.cpp -o $(LIBDIR)plAnimCmdMsg.o

$(LIBDIR)plExcludeRegionMsg.o: PubUtilLib/plMessage/plExcludeRegionMsg.h PubUtilLib/plMessage/plExcludeRegionMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plExcludeRegionMsg.cpp -o $(LIBDIR)plExcludeRegionMsg.o

$(LIBDIR)plLinkToAgeMsg.o: PubUtilLib/plMessage/plLinkToAgeMsg.h PubUtilLib/plMessage/plLinkToAgeMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plLinkToAgeMsg.cpp -o $(LIBDIR)plLinkToAgeMsg.o

$(LIBDIR)plOneShotCallbacks.o: PubUtilLib/plMessage/plOneShotCallbacks.h PubUtilLib/plMessage/plOneShotCallbacks.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plOneShotCallbacks.cpp -o $(LIBDIR)plOneShotCallbacks.o

$(LIBDIR)plResponderMsg.o: PubUtilLib/plMessage/plResponderMsg.h PubUtilLib/plMessage/plResponderMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plResponderMsg.cpp -o $(LIBDIR)plResponderMsg.o

$(LIBDIR)plTimerCallbackMsg.o: PubUtilLib/plMessage/plTimerCallbackMsg.h PubUtilLib/plMessage/plTimerCallbackMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plTimerCallbackMsg.cpp -o $(LIBDIR)plTimerCallbackMsg.o

$(LIBDIR)plTransitionMsg.o: PubUtilLib/plMessage/plTransitionMsg.h PubUtilLib/plMessage/plTransitionMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plTransitionMsg.cpp -o $(LIBDIR)plTransitionMsg.o

$(LIBDIR)plExcludeRegionModifier.o: PubUtilLib/plModifier/plExcludeRegionModifier.h PubUtilLib/plModifier/plExcludeRegionModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plExcludeRegionModifier.cpp -o $(LIBDIR)plExcludeRegionModifier.o

$(LIBDIR)plImageLibMod.o: PubUtilLib/plModifier/plImageLibMod.h PubUtilLib/plModifier/plImageLibMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plImageLibMod.cpp -o $(LIBDIR)plImageLibMod.o

$(LIBDIR)plInterfaceInfoModifier.o: PubUtilLib/plModifier/plInterfaceInfoModifier.h PubUtilLib/plModifier/plInterfaceInfoModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plInterfaceInfoModifier.cpp -o $(LIBDIR)plInterfaceInfoModifier.o

$(LIBDIR)plLogicModifier.o: PubUtilLib/plModifier/plLogicModifier.h PubUtilLib/plModifier/plLogicModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plLogicModifier.cpp -o $(LIBDIR)plLogicModifier.o

$(LIBDIR)plResponderModifier.o: PubUtilLib/plModifier/plResponderModifier.h PubUtilLib/plModifier/plResponderModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plResponderModifier.cpp -o $(LIBDIR)plResponderModifier.o

$(LIBDIR)plSpawnModifier.o: PubUtilLib/plModifier/plSpawnModifier.h PubUtilLib/plModifier/plSpawnModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plSpawnModifier.cpp -o $(LIBDIR)plSpawnModifier.o

$(LIBDIR)plNetServerSessionInfo.o: PubUtilLib/plNetCommon/plNetServerSessionInfo.h PubUtilLib/plNetCommon/plNetServerSessionInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plNetCommon/plNetServerSessionInfo.cpp -o $(LIBDIR)plNetServerSessionInfo.o

$(LIBDIR)plSpawnPointInfo.o: PubUtilLib/plNetCommon/plSpawnPointInfo.h PubUtilLib/plNetCommon/plSpawnPointInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plNetCommon/plSpawnPointInfo.cpp -o $(LIBDIR)plSpawnPointInfo.o

$(LIBDIR)plBoundInterface.o: PubUtilLib/plParticleSystem/plBoundInterface.h PubUtilLib/plParticleSystem/plBoundInterface.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plParticleSystem/plBoundInterface.cpp -o $(LIBDIR)plBoundInterface.o

$(LIBDIR)plConvexVolume.o: PubUtilLib/plParticleSystem/plConvexVolume.h PubUtilLib/plParticleSystem/plConvexVolume.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plParticleSystem/plConvexVolume.cpp -o $(LIBDIR)plConvexVolume.o

$(LIBDIR)plParticleEffect.o: PubUtilLib/plParticleSystem/plParticleEffect.h PubUtilLib/plParticleSystem/plParticleEffect.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plParticleSystem/plParticleEffect.cpp -o $(LIBDIR)plParticleEffect.o

$(LIBDIR)plCollisionDetector.o: PubUtilLib/plPhysics/plCollisionDetector.h PubUtilLib/plPhysics/plCollisionDetector.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plCollisionDetector.cpp -o $(LIBDIR)plCollisionDetector.o

$(LIBDIR)plDetectorModifier.o: PubUtilLib/plPhysics/plDetectorModifier.h PubUtilLib/plPhysics/plDetectorModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plDetectorModifier.cpp -o $(LIBDIR)plDetectorModifier.o

$(LIBDIR)plObjectInVolumeDetector.o: PubUtilLib/plPhysics/plObjectInVolumeDetector.h PubUtilLib/plPhysics/plObjectInVolumeDetector.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plObjectInVolumeDetector.cpp -o $(LIBDIR)plObjectInVolumeDetector.o

$(LIBDIR)plPhysical.o: PubUtilLib/plPhysics/plPhysical.h PubUtilLib/plPhysics/plPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plPhysical.cpp -o $(LIBDIR)plPhysical.o

$(LIBDIR)plHKPhysical.o: PubUtilLib/plPhysics/plHKPhysical.h PubUtilLib/plPhysics/plHKPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plHKPhysical.cpp -o $(LIBDIR)plHKPhysical.o

$(LIBDIR)plPXPhysical.o: PubUtilLib/plPhysics/plPXPhysical.h PubUtilLib/plPhysics/plPXPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plPXPhysical.cpp -o $(LIBDIR)plPXPhysical.o

$(LIBDIR)plODEPhysical.o: PubUtilLib/plPhysics/plODEPhysical.h PubUtilLib/plPhysics/plODEPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plODEPhysical.cpp -o $(LIBDIR)plODEPhysical.o

$(LIBDIR)plPhysicalSndGroup.o: PubUtilLib/plPhysics/plPhysicalSndGroup.h PubUtilLib/plPhysics/plPhysicalSndGroup.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plPhysicalSndGroup.cpp -o $(LIBDIR)plPhysicalSndGroup.o

$(LIBDIR)plFogEnvironment.o: PubUtilLib/plPipeline/plFogEnvironment.h PubUtilLib/plPipeline/plFogEnvironment.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPipeline/plFogEnvironment.cpp -o $(LIBDIR)plFogEnvironment.o

$(LIBDIR)hsGDeviceRef.o: PubUtilLib/plPipeline/hsGDeviceRef.h PubUtilLib/plPipeline/hsGDeviceRef.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPipeline/hsGDeviceRef.cpp -o $(LIBDIR)hsGDeviceRef.o

$(LIBDIR)plGBufferGroup.o: PubUtilLib/plPipeline/plGBufferGroup.h PubUtilLib/plPipeline/plGBufferGroup.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPipeline/plGBufferGroup.cpp -o $(LIBDIR)plGBufferGroup.o

$(LIBDIR)plVertCoder.o: PubUtilLib/plPipeline/plVertCoder.h PubUtilLib/plPipeline/plVertCoder.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPipeline/plVertCoder.cpp -o $(LIBDIR)plVertCoder.o

$(LIBDIR)plAgeInfo.o: PubUtilLib/plResMgr/plAgeInfo.h PubUtilLib/plResMgr/plAgeInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plResMgr/plAgeInfo.cpp -o $(LIBDIR)plAgeInfo.o

$(LIBDIR)plKeyCollector.o: PubUtilLib/plResMgr/plKeyCollector.h PubUtilLib/plResMgr/plKeyCollector.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plResMgr/plKeyCollector.cpp -o $(LIBDIR)plKeyCollector.o

$(LIBDIR)plPageInfo.o: PubUtilLib/plResMgr/plPageInfo.h PubUtilLib/plResMgr/plPageInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plResMgr/plPageInfo.cpp -o $(LIBDIR)plPageInfo.o

$(LIBDIR)plResManager.o: PubUtilLib/plResMgr/plResManager.h PubUtilLib/plResMgr/plResManager.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plResMgr/plResManager.cpp -o $(LIBDIR)plResManager.o

$(LIBDIR)plPostEffectMod.o: PubUtilLib/plScene/plPostEffectMod.h PubUtilLib/plScene/plPostEffectMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plScene/plPostEffectMod.cpp -o $(LIBDIR)plPostEffectMod.o

$(LIBDIR)plSceneNode.o: PubUtilLib/plScene/plSceneNode.h PubUtilLib/plScene/plSceneNode.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plScene/plSceneNode.cpp -o $(LIBDIR)plSceneNode.o

$(LIBDIR)plVisRegion.o: PubUtilLib/plScene/plVisRegion.h PubUtilLib/plScene/plVisRegion.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plScene/plVisRegion.cpp -o $(LIBDIR)plVisRegion.o

$(LIBDIR)hsGMaterial.o: PubUtilLib/plSurface/hsGMaterial.h PubUtilLib/plSurface/hsGMaterial.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSurface/hsGMaterial.cpp -o $(LIBDIR)hsGMaterial.o

$(LIBDIR)plLayerInterface.o: PubUtilLib/plSurface/plLayerInterface.h PubUtilLib/plSurface/plLayerInterface.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSurface/plLayerInterface.cpp -o $(LIBDIR)plLayerInterface.o

$(LIBDIR)plLayer.o: PubUtilLib/plSurface/plLayer.h PubUtilLib/plSurface/plLayer.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSurface/plLayer.cpp -o $(LIBDIR)plLayer.o

$(LIBDIR)plLayerAnimation.o: PubUtilLib/plSurface/plLayerAnimation.h PubUtilLib/plSurface/plLayerAnimation.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSurface/plLayerAnimation.cpp -o $(LIBDIR)plLayerAnimation.o

$(LIBDIR)plLayerMovie.o: PubUtilLib/plSurface/plLayerMovie.h PubUtilLib/plSurface/plLayerMovie.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSurface/plLayerMovie.cpp -o $(LIBDIR)plLayerMovie.o

$(LIBDIR)hsAffineParts.o: PubUtilLib/plTransform/hsAffineParts.h PubUtilLib/plTransform/hsAffineParts.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plTransform/hsAffineParts.cpp -o $(LIBDIR)hsAffineParts.o

$(LIBDIR)plUUID.o: PubUtilLib/plUUID/plUUID.h PubUtilLib/plUUID/plUUID.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plUUID/plUUID.cpp -o $(LIBDIR)plUUID.o

$(LIBDIR)plLineFollowMod.o: FeatureLib/pfAnimation/plLineFollowMod.h FeatureLib/pfAnimation/plLineFollowMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAnimation/plLineFollowMod.cpp -o $(LIBDIR)plLineFollowMod.o

$(LIBDIR)plRandomCommandMod.o: FeatureLib/pfAnimation/plRandomCommandMod.h FeatureLib/pfAnimation/plRandomCommandMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAnimation/plRandomCommandMod.cpp -o $(LIBDIR)plRandomCommandMod.o

$(LIBDIR)plStereizer.o: FeatureLib/pfAnimation/plStereizer.h FeatureLib/pfAnimation/plStereizer.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAnimation/plStereizer.cpp -o $(LIBDIR)plStereizer.o

$(LIBDIR)plViewFaceModifier.o: FeatureLib/pfAnimation/plViewFaceModifier.h FeatureLib/pfAnimation/plViewFaceModifier.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAnimation/plViewFaceModifier.cpp -o $(LIBDIR)plViewFaceModifier.o

$(LIBDIR)plRandomSoundMod.o: FeatureLib/pfAudio/plRandomSoundMod.h FeatureLib/pfAudio/plRandomSoundMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAudio/plRandomSoundMod.cpp -o $(LIBDIR)plRandomSoundMod.o

$(LIBDIR)plConditionalObject.o: FeatureLib/pfConditional/plConditionalObject.h FeatureLib/pfConditional/plConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plConditionalObject.cpp -o $(LIBDIR)plConditionalObject.o

$(LIBDIR)plActivatorConditionalObject.o: FeatureLib/pfConditional/plActivatorConditionalObject.h FeatureLib/pfConditional/plActivatorConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plActivatorConditionalObject.cpp -o $(LIBDIR)plActivatorConditionalObject.o

$(LIBDIR)plAnimationEventConditionalObject.o: FeatureLib/pfConditional/plAnimationEventConditionalObject.h FeatureLib/pfConditional/plAnimationEventConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plAnimationEventConditionalObject.cpp -o $(LIBDIR)plAnimationEventConditionalObject.o

$(LIBDIR)plBooleanConditionalObject.o: FeatureLib/pfConditional/plBooleanConditionalObject.h FeatureLib/pfConditional/plBooleanConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plBooleanConditionalObject.cpp -o $(LIBDIR)plBooleanConditionalObject.o

$(LIBDIR)plControlEventConditionalObject.o: FeatureLib/pfConditional/plControlEventConditionalObject.h FeatureLib/pfConditional/plControlEventConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plControlEventConditionalObject.cpp -o $(LIBDIR)plControlEventConditionalObject.o

$(LIBDIR)plDetectConditionalObjects.o: FeatureLib/pfConditional/plDetectConditionalObjects.h FeatureLib/pfConditional/plDetectConditionalObjects.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plDetectConditionalObjects.cpp -o $(LIBDIR)plDetectConditionalObjects.o

$(LIBDIR)plFacingConditionalObject.o: FeatureLib/pfConditional/plFacingConditionalObject.h FeatureLib/pfConditional/plFacingConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plFacingConditionalObject.cpp -o $(LIBDIR)plFacingConditionalObject.o

$(LIBDIR)plKeyPressConditionalObject.o: FeatureLib/pfConditional/plKeyPressConditionalObject.h FeatureLib/pfConditional/plKeyPressConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plKeyPressConditionalObject.cpp -o $(LIBDIR)plKeyPressConditionalObject.o

$(LIBDIR)plPickedConditionalObject.o: FeatureLib/pfConditional/plPickedConditionalObject.h FeatureLib/pfConditional/plPickedConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plPickedConditionalObject.cpp -o $(LIBDIR)plPickedConditionalObject.o

$(LIBDIR)plPythonFileModConditionalObject.o: FeatureLib/pfConditional/plPythonFileModConditionalObject.h FeatureLib/pfConditional/plPythonFileModConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plPythonFileModConditionalObject.cpp -o $(LIBDIR)plPythonFileModConditionalObject.o

$(LIBDIR)plVolumeSensorConditionalObject.o: FeatureLib/pfConditional/plVolumeSensorConditionalObject.h FeatureLib/pfConditional/plVolumeSensorConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plVolumeSensorConditionalObject.cpp -o $(LIBDIR)plVolumeSensorConditionalObject.o

$(LIBDIR)pfGUIControlHandlers.o: FeatureLib/pfGameGUIMgr/pfGUIControlHandlers.h FeatureLib/pfGameGUIMgr/pfGUIControlHandlers.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIControlHandlers.cpp -o $(LIBDIR)pfGUIControlHandlers.o

$(LIBDIR)pfGUIControlMod.o: FeatureLib/pfGameGUIMgr/pfGUIControlMod.h FeatureLib/pfGameGUIMgr/pfGUIControlMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIControlMod.cpp -o $(LIBDIR)pfGUIControlMod.o

$(LIBDIR)pfGUIButtonMod.o: FeatureLib/pfGameGUIMgr/pfGUIButtonMod.h FeatureLib/pfGameGUIMgr/pfGUIButtonMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIButtonMod.cpp -o $(LIBDIR)pfGUIButtonMod.o

$(LIBDIR)pfGUICheckBoxCtrl.o: FeatureLib/pfGameGUIMgr/pfGUICheckBoxCtrl.h FeatureLib/pfGameGUIMgr/pfGUICheckBoxCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUICheckBoxCtrl.cpp -o $(LIBDIR)pfGUICheckBoxCtrl.o

$(LIBDIR)pfGUIClickMapCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIClickMapCtrl.h FeatureLib/pfGameGUIMgr/pfGUIClickMapCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIClickMapCtrl.cpp -o $(LIBDIR)pfGUIClickMapCtrl.o

$(LIBDIR)pfGUIDialogMod.o: FeatureLib/pfGameGUIMgr/pfGUIDialogMod.h FeatureLib/pfGameGUIMgr/pfGUIDialogMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIDialogMod.cpp -o $(LIBDIR)pfGUIDialogMod.o

$(LIBDIR)pfGUIDragBarCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIDragBarCtrl.h FeatureLib/pfGameGUIMgr/pfGUIDragBarCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIDragBarCtrl.cpp -o $(LIBDIR)pfGUIDragBarCtrl.o

$(LIBDIR)pfGUIDraggableMod.o: FeatureLib/pfGameGUIMgr/pfGUIDraggableMod.h FeatureLib/pfGameGUIMgr/pfGUIDraggableMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIDraggableMod.cpp -o $(LIBDIR)pfGUIDraggableMod.o

$(LIBDIR)pfGUIDynDisplayCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIDynDisplayCtrl.h FeatureLib/pfGameGUIMgr/pfGUIDynDisplayCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIDynDisplayCtrl.cpp -o $(LIBDIR)pfGUIDynDisplayCtrl.o

$(LIBDIR)pfGUIEditBoxMod.o: FeatureLib/pfGameGUIMgr/pfGUIEditBoxMod.h FeatureLib/pfGameGUIMgr/pfGUIEditBoxMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIEditBoxMod.cpp -o $(LIBDIR)pfGUIEditBoxMod.o

$(LIBDIR)pfGUIListBoxMod.o: FeatureLib/pfGameGUIMgr/pfGUIListBoxMod.h FeatureLib/pfGameGUIMgr/pfGUIListBoxMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIListBoxMod.cpp -o $(LIBDIR)pfGUIListBoxMod.o

$(LIBDIR)pfGUIMultiLineEditCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIMultiLineEditCtrl.h FeatureLib/pfGameGUIMgr/pfGUIMultiLineEditCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIMultiLineEditCtrl.cpp -o $(LIBDIR)pfGUIMultiLineEditCtrl.o

$(LIBDIR)pfGUIPopUpMenu.o: FeatureLib/pfGameGUIMgr/pfGUIPopUpMenu.h FeatureLib/pfGameGUIMgr/pfGUIPopUpMenu.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIPopUpMenu.cpp -o $(LIBDIR)pfGUIPopUpMenu.o

$(LIBDIR)pfGUIRadioGroupCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIRadioGroupCtrl.h FeatureLib/pfGameGUIMgr/pfGUIRadioGroupCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIRadioGroupCtrl.cpp -o $(LIBDIR)pfGUIRadioGroupCtrl.o

$(LIBDIR)pfGUISkin.o: FeatureLib/pfGameGUIMgr/pfGUISkin.h FeatureLib/pfGameGUIMgr/pfGUISkin.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUISkin.cpp -o $(LIBDIR)pfGUISkin.o

$(LIBDIR)pfGUITextBoxMod.o: FeatureLib/pfGameGUIMgr/pfGUITextBoxMod.h FeatureLib/pfGameGUIMgr/pfGUITextBoxMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUITextBoxMod.cpp -o $(LIBDIR)pfGUITextBoxMod.o

$(LIBDIR)pfGUIValueCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIValueCtrl.h FeatureLib/pfGameGUIMgr/pfGUIValueCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIValueCtrl.cpp -o $(LIBDIR)pfGUIValueCtrl.o

$(LIBDIR)pfGUIKnobCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIKnobCtrl.h FeatureLib/pfGameGUIMgr/pfGUIKnobCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIKnobCtrl.cpp -o $(LIBDIR)pfGUIKnobCtrl.o

$(LIBDIR)pfGUIProgressCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIProgressCtrl.h FeatureLib/pfGameGUIMgr/pfGUIProgressCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIProgressCtrl.cpp -o $(LIBDIR)pfGUIProgressCtrl.o

$(LIBDIR)pfGUIUpDownPairMod.o: FeatureLib/pfGameGUIMgr/pfGUIUpDownPairMod.h FeatureLib/pfGameGUIMgr/pfGUIUpDownPairMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIUpDownPairMod.cpp -o $(LIBDIR)pfGUIUpDownPairMod.o

$(LIBDIR)plArmatureEffectMsg.o: FeatureLib/pfMessage/plArmatureEffectMsg.h FeatureLib/pfMessage/plArmatureEffectMsg.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfMessage/plArmatureEffectMsg.cpp -o $(LIBDIR)plArmatureEffectMsg.o

$(LIBDIR)plPythonFileMod.o: FeatureLib/pfPython/plPythonFileMod.h FeatureLib/pfPython/plPythonFileMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfPython/plPythonFileMod.cpp -o $(LIBDIR)plPythonFileMod.o

$(LIBDIR)pfPrcHelper.o: FeatureLib/pfPRC/pfPrcHelper.h FeatureLib/pfPRC/pfPrcHelper.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfPRC/pfPrcHelper.cpp -o $(LIBDIR)pfPrcHelper.o

$(LIBDIR)rijndael.o: rijndael.h rijndael.cpp
	$(CXX) $(CXXFLAGSEXTERN) -c rijndael.cpp -o $(LIBDIR)rijndael.o

install:
	cp $(PLSLIB) /usr/local/lib
	ldconfig

clean:
	rm -f $(OBJFILES)

distclean:
	rm -f $(PLSLIB)
