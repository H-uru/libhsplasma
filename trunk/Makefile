CXX = g++
CXXFLAGS += -I. -fPIC -Wall -g -ansi -fno-rtti
CXXFLAGSEXTERN = -fPIC -O2

OBJDIR=out/

PLSCOREOBJ=\
	$(OBJDIR)hsExceptions.o \
	$(OBJDIR)hsSemaphore.o \
	$(OBJDIR)hsStream.o \
	$(OBJDIR)hsStdioStream.o \
	$(OBJDIR)hsRAMStream.o \
	$(OBJDIR)plEncryptedStream.o \
	$(OBJDIR)hsElfStream.o \
	$(OBJDIR)hsTokenStream.o \
	$(OBJDIR)plDebug.o \
	$(OBJDIR)hsBitVector.o \
	$(OBJDIR)hsColor.o \
	$(OBJDIR)hsMatrix33.o \
	$(OBJDIR)hsMatrix44.o \
	$(OBJDIR)hsGeometry3.o \
	$(OBJDIR)hsQuat.o \
	$(OBJDIR)hsBounds.o \
	$(OBJDIR)plString.o \
	$(OBJDIR)plUnifiedTime.o \
	$(OBJDIR)plUUID.o \
	$(OBJDIR)pfPrcHelper.o

PLSOBJ=\
	$(OBJDIR)plAgeInfo.o \
	$(OBJDIR)plKeyCollector.o \
	$(OBJDIR)plPageInfo.o \
	$(OBJDIR)plResManager.o \
	$(OBJDIR)plLoadMask.o \
	$(OBJDIR)PageID.o \
	$(OBJDIR)pdUnifiedTypeMap.o \
	$(OBJDIR)hsGMatState.o \
	$(OBJDIR)plCreatable.o \
	$(OBJDIR)plFactory.o \
	$(OBJDIR)plKey.o \
	$(OBJDIR)plReceiver.o \
	$(OBJDIR)hsKeyedObject.o \
	$(OBJDIR)plMsgForwarder.o \
	$(OBJDIR)plUoid.o \
	$(OBJDIR)proEventData.o \
	$(OBJDIR)plMessage.o \
	$(OBJDIR)plCameraMsg.o \
	$(OBJDIR)plEnableMsg.o \
	$(OBJDIR)plEventCallbackMsg.o \
	$(OBJDIR)plNotifyMsg.o \
	$(OBJDIR)plMessageWithCallbacks.o \
	$(OBJDIR)plSimStateMsg.o \
	$(OBJDIR)plSimulationMsg.o \
	$(OBJDIR)plSoundMsg.o \
	$(OBJDIR)plModifier.o \
	$(OBJDIR)plLogicModBase.o \
	$(OBJDIR)plResponderModifier.o \
	$(OBJDIR)plSynchedObject.o \
	$(OBJDIR)plObjInterface.o \
	$(OBJDIR)plAudioInterface.o \
	$(OBJDIR)plCoordinateInterface.o \
	$(OBJDIR)plDrawInterface.o \
	$(OBJDIR)plSimulationInterface.o \
	$(OBJDIR)plSceneObject.o \
	$(OBJDIR)plAudible.o \
	$(OBJDIR)plEAXEffects.o \
	$(OBJDIR)plEAXListenerMod.o \
	$(OBJDIR)plSound.o \
	$(OBJDIR)plWin32Sound.o \
	$(OBJDIR)plWin32StaticSound.o \
	$(OBJDIR)plSoundBuffer.o \
	$(OBJDIR)plAGAnim.o \
	$(OBJDIR)plAGApplicator.o \
	$(OBJDIR)plAGChannel.o \
	$(OBJDIR)plAGModifier.o \
	$(OBJDIR)plAnimStage.o \
	$(OBJDIR)plAvLadderMod.o \
	$(OBJDIR)plClothingItem.o \
	$(OBJDIR)plAGMasterMod.o \
	$(OBJDIR)plMatrixChannel.o \
	$(OBJDIR)plMultistageBehMod.o \
	$(OBJDIR)plNPCSpawnMod.o \
	$(OBJDIR)plOneShotMod.o \
	$(OBJDIR)plPointChannel.o \
	$(OBJDIR)plQuatChannel.o \
	$(OBJDIR)plScalarChannel.o \
	$(OBJDIR)plSittingModifier.o \
	$(OBJDIR)plSeekPointMod.o \
	$(OBJDIR)plCluster.o \
	$(OBJDIR)plClusterGroup.o \
	$(OBJDIR)plDrawableSpans.o \
	$(OBJDIR)plDynaDecalMgr.o \
	$(OBJDIR)plDynaRippleMgr.o \
	$(OBJDIR)plFixedWaterState6.o \
	$(OBJDIR)plFixedWaterState7.o \
	$(OBJDIR)plMorphArray.o \
	$(OBJDIR)plMorphDataSet.o \
	$(OBJDIR)plMorphDelta.o \
	$(OBJDIR)plSpan.o \
	$(OBJDIR)plSpanTemplate.o \
	$(OBJDIR)plSpanInstance.o \
	$(OBJDIR)plVertexSpan.o \
	$(OBJDIR)plIcicle.o \
	$(OBJDIR)plGeometrySpan.o \
	$(OBJDIR)plSharedMesh.o \
	$(OBJDIR)plSpaceTree.o \
	$(OBJDIR)plWaveSetBase.o \
	$(OBJDIR)plWaveSet6.o \
	$(OBJDIR)plWaveSet7.o \
	$(OBJDIR)plBitmap.o \
	$(OBJDIR)plCubicEnvironmap.o \
	$(OBJDIR)plDynamicTextMap.o \
	$(OBJDIR)plFont.o \
	$(OBJDIR)plMipmap.o \
	$(OBJDIR)plLightInfo.o \
	$(OBJDIR)plDirectionalLightInfo.o \
	$(OBJDIR)plOmniLightInfo.o \
	$(OBJDIR)plShadowCaster.o \
	$(OBJDIR)plShadowMaster.o \
	$(OBJDIR)plAnimTimeConvert.o \
	$(OBJDIR)plAnimPath.o \
	$(OBJDIR)plATCEaseCurves.o \
	$(OBJDIR)plController.o \
	$(OBJDIR)plKeyControllers.o \
	$(OBJDIR)plLeafController.o \
	$(OBJDIR)plPosController.o \
	$(OBJDIR)plRotController.o \
	$(OBJDIR)plScaleController.o \
	$(OBJDIR)plTMController.o \
	$(OBJDIR)hsKeys.o \
	$(OBJDIR)UruKeys.o \
	$(OBJDIR)plHardRegion.o \
	$(OBJDIR)plHardRegionPlanes.o \
	$(OBJDIR)plRegionBase.o \
	$(OBJDIR)plSoftVolume.o \
	$(OBJDIR)plVolumeIsect.o \
	$(OBJDIR)plJPEG.o \
	$(OBJDIR)plAnimCmdMsg.o \
	$(OBJDIR)plExcludeRegionMsg.o \
	$(OBJDIR)plLinkToAgeMsg.o \
	$(OBJDIR)plOneShotCallbacks.o \
	$(OBJDIR)plResponderMsg.o \
	$(OBJDIR)plTimerCallbackMsg.o \
	$(OBJDIR)plTransitionMsg.o \
	$(OBJDIR)plAnimEventModifier.o \
	$(OBJDIR)plExcludeRegionModifier.o \
	$(OBJDIR)plImageLibMod.o \
	$(OBJDIR)plInterfaceInfoModifier.o \
	$(OBJDIR)plLogicModifier.o \
	$(OBJDIR)plSpawnModifier.o \
	$(OBJDIR)plNetServerSessionInfo.o \
	$(OBJDIR)plSpawnPointInfo.o \
	$(OBJDIR)plBoundInterface.o \
	$(OBJDIR)plConvexVolume.o \
	$(OBJDIR)plParticleApplicator.o \
	$(OBJDIR)plParticleEffect.o \
	$(OBJDIR)plParticleEmitter.o \
	$(OBJDIR)plParticleGenerator.o \
	$(OBJDIR)plParticleSystem.o \
	$(OBJDIR)plCollisionDetector.o \
	$(OBJDIR)plDetectorModifier.o \
	$(OBJDIR)plObjectInVolumeDetector.o \
	$(OBJDIR)plPhysical.o \
	$(OBJDIR)plHKPhysical.o \
	$(OBJDIR)plPXPhysical.o \
	$(OBJDIR)plODEPhysical.o \
	$(OBJDIR)plPhysicalSndGroup.o \
	$(OBJDIR)plDynamicEnvMap.o \
	$(OBJDIR)plFogEnvironment.o \
	$(OBJDIR)hsGDeviceRef.o \
	$(OBJDIR)plGBufferGroup.o \
	$(OBJDIR)plRenderTarget.o \
	$(OBJDIR)plVertCoder.o \
	$(OBJDIR)plCullPoly.o \
	$(OBJDIR)plOccluder.o \
	$(OBJDIR)plPostEffectMod.o \
	$(OBJDIR)plRelevanceRegion.o \
	$(OBJDIR)plSceneNode.o \
	$(OBJDIR)plVisRegion.o \
	$(OBJDIR)plSDL.o \
	$(OBJDIR)plSDLMgr.o \
	$(OBJDIR)plStateDataRecord.o \
	$(OBJDIR)plStateDescriptor.o \
	$(OBJDIR)plStateVariable.o \
	$(OBJDIR)hsGMaterial.o \
	$(OBJDIR)plLayerInterface.o \
	$(OBJDIR)plLayer.o \
	$(OBJDIR)plLayerAnimation.o \
	$(OBJDIR)plLayerMovie.o \
	$(OBJDIR)hsAffineParts.o \
	$(OBJDIR)plBlower.o \
	$(OBJDIR)plFilterCoordInterface.o \
	$(OBJDIR)plLineFollowMod.o \
	$(OBJDIR)plRandomCommandMod.o \
	$(OBJDIR)plStereizer.o \
	$(OBJDIR)plViewFaceModifier.o \
	$(OBJDIR)plRandomSoundMod.o \
	$(OBJDIR)plCameraBrain.o \
	$(OBJDIR)plCameraModifier.o \
	$(OBJDIR)plConditionalObject.o \
	$(OBJDIR)plActivatorConditionalObject.o \
	$(OBJDIR)plAnimationEventConditionalObject.o \
	$(OBJDIR)plBooleanConditionalObject.o \
	$(OBJDIR)plControlEventConditionalObject.o \
	$(OBJDIR)plDetectConditionalObjects.o \
	$(OBJDIR)plFacingConditionalObject.o \
	$(OBJDIR)plKeyPressConditionalObject.o \
	$(OBJDIR)plPickedConditionalObject.o \
	$(OBJDIR)plPythonFileModConditionalObject.o \
	$(OBJDIR)plVolumeSensorConditionalObject.o \
	$(OBJDIR)pfGUIControlHandlers.o \
	$(OBJDIR)pfGUIControlMod.o \
	$(OBJDIR)pfGUIButtonMod.o \
	$(OBJDIR)pfGUICheckBoxCtrl.o \
	$(OBJDIR)pfGUIClickMapCtrl.o \
	$(OBJDIR)pfGUIDialogMod.o \
	$(OBJDIR)pfGUIDragBarCtrl.o \
	$(OBJDIR)pfGUIDraggableMod.o \
	$(OBJDIR)pfGUIDynDisplayCtrl.o \
	$(OBJDIR)pfGUIEditBoxMod.o \
	$(OBJDIR)pfGUIListBoxMod.o \
	$(OBJDIR)pfGUIMultiLineEditCtrl.o \
	$(OBJDIR)pfGUIPopUpMenu.o \
	$(OBJDIR)pfGUIRadioGroupCtrl.o \
	$(OBJDIR)pfGUISkin.o \
	$(OBJDIR)pfGUITextBoxMod.o \
	$(OBJDIR)pfGUIValueCtrl.o \
	$(OBJDIR)pfGUIKnobCtrl.o \
	$(OBJDIR)pfGUIProgressCtrl.o \
	$(OBJDIR)pfGUIUpDownPairMod.o \
	$(OBJDIR)plArmatureEffectMsg.o \
	$(OBJDIR)plPythonFileMod.o

# 3rd Party Libs
OBJFILES3P=\
	$(OBJDIR)rijndael.o

PLSCORELIB=lib/libPlasmaCore.so
PLSLIB=lib/libPlasma.so

all: $(PLSCORELIB) $(PLSLIB)

$(PLSCORELIB): $(PLSCOREOBJ) $(OBJFILES3P)
	$(CXX) $(CXXFLAGS) $(PLSCOREOBJ) $(OBJFILES3P) -shared -Wl,-soname,libPlasmaCore.so -o $(PLSCORELIB)

$(PLSLIB): $(PLSOBJ)
	$(CXX) $(CXXFLAGS) $(PLSOBJ) -ljpeg -shared -Wl,-soname,libPlasma.so -o $(PLSLIB)

install:
	cp $(PLSCORELIB) /usr/local/lib
	cp $(PLSLIB) /usr/local/lib
	ldconfig

clean:
	rm -f $(PLSCOREOBJ)
	rm -f $(PLSOBJ)
	rm -f $(OBJFILES3P)

distclean:
	rm -f $(PLSCORELIB)
	rm -f $(PLSLIB)


# Core Lib
$(OBJDIR)hsExceptions.o: CoreLib/hsExceptions.h CoreLib/hsExceptions.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsExceptions.cpp -o $(OBJDIR)hsExceptions.o

$(OBJDIR)hsSemaphore.o: CoreLib/hsSemaphore.h CoreLib/hsSemaphore.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsSemaphore.cpp -o $(OBJDIR)hsSemaphore.o

$(OBJDIR)hsStream.o: CoreLib/hsStream.h CoreLib/hsStream.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsStream.cpp -o $(OBJDIR)hsStream.o

$(OBJDIR)hsStdioStream.o: CoreLib/hsStdioStream.h CoreLib/hsStdioStream.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsStdioStream.cpp -o $(OBJDIR)hsStdioStream.o

$(OBJDIR)hsRAMStream.o: CoreLib/hsRAMStream.h CoreLib/hsRAMStream.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsRAMStream.cpp -o $(OBJDIR)hsRAMStream.o

$(OBJDIR)plEncryptedStream.o: CoreLib/plEncryptedStream.h CoreLib/plEncryptedStream.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/plEncryptedStream.cpp -o $(OBJDIR)plEncryptedStream.o

$(OBJDIR)hsElfStream.o: CoreLib/hsElfStream.h CoreLib/hsElfStream.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsElfStream.cpp -o $(OBJDIR)hsElfStream.o

$(OBJDIR)hsTokenStream.o: CoreLib/hsTokenStream.h CoreLib/hsTokenStream.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsTokenStream.cpp -o $(OBJDIR)hsTokenStream.o

$(OBJDIR)plDebug.o: CoreLib/plDebug.h CoreLib/plDebug.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/plDebug.cpp -o $(OBJDIR)plDebug.o

$(OBJDIR)hsBitVector.o: CoreLib/hsBitVector.h CoreLib/hsBitVector.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsBitVector.cpp -o $(OBJDIR)hsBitVector.o

$(OBJDIR)hsColor.o: CoreLib/hsColor.h CoreLib/hsColor.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsColor.cpp -o $(OBJDIR)hsColor.o

$(OBJDIR)hsMatrix33.o: CoreLib/hsMatrix33.h CoreLib/hsMatrix33.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsMatrix33.cpp -o $(OBJDIR)hsMatrix33.o

$(OBJDIR)hsMatrix44.o: CoreLib/hsMatrix44.h CoreLib/hsMatrix44.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsMatrix44.cpp -o $(OBJDIR)hsMatrix44.o

$(OBJDIR)hsGeometry3.o: CoreLib/hsGeometry3.h CoreLib/hsGeometry3.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsGeometry3.cpp -o $(OBJDIR)hsGeometry3.o

$(OBJDIR)hsQuat.o: CoreLib/hsQuat.h CoreLib/hsQuat.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsQuat.cpp -o $(OBJDIR)hsQuat.o

$(OBJDIR)hsBounds.o: CoreLib/hsBounds.h CoreLib/hsBounds.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/hsBounds.cpp -o $(OBJDIR)hsBounds.o

$(OBJDIR)plString.o: CoreLib/plString.h CoreLib/plString.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/plString.cpp -o $(OBJDIR)plString.o

$(OBJDIR)plUnifiedTime.o: CoreLib/plUnifiedTime.h CoreLib/plUnifiedTime.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/plUnifiedTime.cpp -o $(OBJDIR)plUnifiedTime.o

$(OBJDIR)plUUID.o: PubUtilLib/plUUID/plUUID.h PubUtilLib/plUUID/plUUID.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plUUID/plUUID.cpp -o $(OBJDIR)plUUID.o

$(OBJDIR)pfPrcHelper.o: FeatureLib/pfPRC/pfPrcHelper.h FeatureLib/pfPRC/pfPrcHelper.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfPRC/pfPrcHelper.cpp -o $(OBJDIR)pfPrcHelper.o

$(OBJDIR)rijndael.o: 3rdPartyLibs/rijndael.h 3rdPartyLibs/rijndael.cpp
	$(CXX) $(CXXFLAGSEXTERN) -c 3rdPartyLibs/rijndael.cpp -o $(OBJDIR)rijndael.o


# Pls Lib
$(OBJDIR)plLoadMask.o: CoreLib/plLoadMask.h CoreLib/plLoadMask.cpp
	$(CXX) $(CXXFLAGS) -c CoreLib/plLoadMask.cpp -o $(OBJDIR)plLoadMask.o

$(OBJDIR)PageID.o: DynLib/PageID.h DynLib/PageID.cpp
	$(CXX) $(CXXFLAGS) -c DynLib/PageID.cpp -o $(OBJDIR)PageID.o

$(OBJDIR)pdUnifiedTypeMap.o: DynLib/pdUnifiedTypeMap.h DynLib/pdUnifiedTypeMap.cpp
	$(CXX) $(CXXFLAGS) -c DynLib/pdUnifiedTypeMap.cpp -o $(OBJDIR)pdUnifiedTypeMap.o

$(OBJDIR)hsGMatState.o: NucleusLib/inc/hsGMatState.h NucleusLib/inc/hsGMatState.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/inc/hsGMatState.cpp -o $(OBJDIR)hsGMatState.o

$(OBJDIR)plCreatable.o: NucleusLib/pnFactory/plCreatable.h NucleusLib/pnFactory/plCreatable.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnFactory/plCreatable.cpp -o $(OBJDIR)plCreatable.o

$(OBJDIR)plFactory.o: NucleusLib/pnFactory/plFactory.h NucleusLib/pnFactory/plFactory.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnFactory/plFactory.cpp -o $(OBJDIR)plFactory.o

$(OBJDIR)plKey.o: NucleusLib/pnKeyedObject/plKey.h NucleusLib/pnKeyedObject/plKey.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnKeyedObject/plKey.cpp -o $(OBJDIR)plKey.o

$(OBJDIR)plReceiver.o: NucleusLib/pnKeyedObject/plReceiver.h NucleusLib/pnKeyedObject/plReceiver.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnKeyedObject/plReceiver.cpp -o $(OBJDIR)plReceiver.o

$(OBJDIR)hsKeyedObject.o: NucleusLib/pnKeyedObject/hsKeyedObject.h NucleusLib/pnKeyedObject/hsKeyedObject.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnKeyedObject/hsKeyedObject.cpp -o $(OBJDIR)hsKeyedObject.o

$(OBJDIR)plMsgForwarder.o: NucleusLib/pnKeyedObject/plMsgForwarder.h NucleusLib/pnKeyedObject/plMsgForwarder.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnKeyedObject/plMsgForwarder.cpp -o $(OBJDIR)plMsgForwarder.o

$(OBJDIR)plUoid.o: NucleusLib/pnKeyedObject/plUoid.h NucleusLib/pnKeyedObject/plUoid.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnKeyedObject/plUoid.cpp -o $(OBJDIR)plUoid.o

$(OBJDIR)proEventData.o: NucleusLib/pnMessage/proEventData.h NucleusLib/pnMessage/proEventData.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/proEventData.cpp -o $(OBJDIR)proEventData.o

$(OBJDIR)plMessage.o: NucleusLib/pnMessage/plMessage.h NucleusLib/pnMessage/plMessage.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plMessage.cpp -o $(OBJDIR)plMessage.o

$(OBJDIR)plCameraMsg.o: NucleusLib/pnMessage/plCameraMsg.h NucleusLib/pnMessage/plCameraMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plCameraMsg.cpp -o $(OBJDIR)plCameraMsg.o

$(OBJDIR)plEnableMsg.o: NucleusLib/pnMessage/plEnableMsg.h NucleusLib/pnMessage/plEnableMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plEnableMsg.cpp -o $(OBJDIR)plEnableMsg.o

$(OBJDIR)plEventCallbackMsg.o: NucleusLib/pnMessage/plEventCallbackMsg.h NucleusLib/pnMessage/plEventCallbackMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plEventCallbackMsg.cpp -o $(OBJDIR)plEventCallbackMsg.o

$(OBJDIR)plNotifyMsg.o: NucleusLib/pnMessage/plNotifyMsg.h NucleusLib/pnMessage/plNotifyMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plNotifyMsg.cpp -o $(OBJDIR)plNotifyMsg.o

$(OBJDIR)plMessageWithCallbacks.o: NucleusLib/pnMessage/plMessageWithCallbacks.h NucleusLib/pnMessage/plMessageWithCallbacks.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plMessageWithCallbacks.cpp -o $(OBJDIR)plMessageWithCallbacks.o

$(OBJDIR)plSimStateMsg.o: NucleusLib/pnMessage/plSimStateMsg.h NucleusLib/pnMessage/plSimStateMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plSimStateMsg.cpp -o $(OBJDIR)plSimStateMsg.o

$(OBJDIR)plSimulationMsg.o: NucleusLib/pnMessage/plSimulationMsg.h NucleusLib/pnMessage/plSimulationMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plSimulationMsg.cpp -o $(OBJDIR)plSimulationMsg.o

$(OBJDIR)plSoundMsg.o: NucleusLib/pnMessage/plSoundMsg.h NucleusLib/pnMessage/plSoundMsg.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnMessage/plSoundMsg.cpp -o $(OBJDIR)plSoundMsg.o

$(OBJDIR)plModifier.o: NucleusLib/pnModifier/plModifier.h NucleusLib/pnModifier/plModifier.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnModifier/plModifier.cpp -o $(OBJDIR)plModifier.o

$(OBJDIR)plLogicModBase.o: NucleusLib/pnModifier/plLogicModBase.h NucleusLib/pnModifier/plLogicModBase.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnModifier/plLogicModBase.cpp -o $(OBJDIR)plLogicModBase.o

$(OBJDIR)plSynchedObject.o: NucleusLib/pnNetCommon/plSynchedObject.h NucleusLib/pnNetCommon/plSynchedObject.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnNetCommon/plSynchedObject.cpp -o $(OBJDIR)plSynchedObject.o

$(OBJDIR)plAudioInterface.o: NucleusLib/pnSceneObject/plAudioInterface.h NucleusLib/pnSceneObject/plAudioInterface.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plAudioInterface.cpp -o $(OBJDIR)plAudioInterface.o

$(OBJDIR)plCoordinateInterface.o: NucleusLib/pnSceneObject/plCoordinateInterface.h NucleusLib/pnSceneObject/plCoordinateInterface.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plCoordinateInterface.cpp -o $(OBJDIR)plCoordinateInterface.o

$(OBJDIR)plDrawInterface.o: NucleusLib/pnSceneObject/plDrawInterface.h NucleusLib/pnSceneObject/plDrawInterface.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plDrawInterface.cpp -o $(OBJDIR)plDrawInterface.o

$(OBJDIR)plObjInterface.o: NucleusLib/pnSceneObject/plObjInterface.h NucleusLib/pnSceneObject/plObjInterface.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plObjInterface.cpp -o $(OBJDIR)plObjInterface.o

$(OBJDIR)plSceneObject.o: NucleusLib/pnSceneObject/plSceneObject.h NucleusLib/pnSceneObject/plSceneObject.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plSceneObject.cpp -o $(OBJDIR)plSceneObject.o

$(OBJDIR)plSimulationInterface.o: NucleusLib/pnSceneObject/plSimulationInterface.h NucleusLib/pnSceneObject/plSimulationInterface.cpp
	$(CXX) $(CXXFLAGS) -c NucleusLib/pnSceneObject/plSimulationInterface.cpp -o $(OBJDIR)plSimulationInterface.o

$(OBJDIR)plAudible.o: PubUtilLib/plAudible/plAudible.h PubUtilLib/plAudible/plAudible.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudible/plAudible.cpp -o $(OBJDIR)plAudible.o

$(OBJDIR)plEAXEffects.o: PubUtilLib/plAudio/plEAXEffects.h PubUtilLib/plAudio/plEAXEffects.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudio/plEAXEffects.cpp -o $(OBJDIR)plEAXEffects.o

$(OBJDIR)plEAXListenerMod.o: PubUtilLib/plAudio/plEAXListenerMod.h PubUtilLib/plAudio/plEAXListenerMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudio/plEAXListenerMod.cpp -o $(OBJDIR)plEAXListenerMod.o

$(OBJDIR)plSound.o: PubUtilLib/plAudio/plSound.h PubUtilLib/plAudio/plSound.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudio/plSound.cpp -o $(OBJDIR)plSound.o

$(OBJDIR)plWin32Sound.o: PubUtilLib/plAudio/plWin32Sound.h PubUtilLib/plAudio/plWin32Sound.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudio/plWin32Sound.cpp -o $(OBJDIR)plWin32Sound.o

$(OBJDIR)plWin32StaticSound.o: PubUtilLib/plAudio/plWin32StaticSound.h PubUtilLib/plAudio/plWin32StaticSound.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudio/plWin32StaticSound.cpp -o $(OBJDIR)plWin32StaticSound.o

$(OBJDIR)plSoundBuffer.o: PubUtilLib/plAudioCore/plSoundBuffer.h PubUtilLib/plAudioCore/plSoundBuffer.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAudioCore/plSoundBuffer.cpp -o $(OBJDIR)plSoundBuffer.o

$(OBJDIR)plAGAnim.o: PubUtilLib/plAvatar/plAGAnim.h PubUtilLib/plAvatar/plAGAnim.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plAGAnim.cpp -o $(OBJDIR)plAGAnim.o

$(OBJDIR)plAGApplicator.o: PubUtilLib/plAvatar/plAGApplicator.h PubUtilLib/plAvatar/plAGApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plAGApplicator.cpp -o $(OBJDIR)plAGApplicator.o

$(OBJDIR)plAGChannel.o: PubUtilLib/plAvatar/plAGChannel.h PubUtilLib/plAvatar/plAGChannel.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plAGChannel.cpp -o $(OBJDIR)plAGChannel.o

$(OBJDIR)plAGModifier.o: PubUtilLib/plAvatar/plAGModifier.h PubUtilLib/plAvatar/plAGModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plAGModifier.cpp -o $(OBJDIR)plAGModifier.o

$(OBJDIR)plAnimStage.o: PubUtilLib/plAvatar/plAnimStage.h PubUtilLib/plAvatar/plAnimStage.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plAnimStage.cpp -o $(OBJDIR)plAnimStage.o

$(OBJDIR)plAvLadderMod.o: PubUtilLib/plAvatar/plAvLadderMod.h PubUtilLib/plAvatar/plAvLadderMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plAvLadderMod.cpp -o $(OBJDIR)plAvLadderMod.o

$(OBJDIR)plClothingItem.o: PubUtilLib/plAvatar/plClothingItem.h PubUtilLib/plAvatar/plClothingItem.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plClothingItem.cpp -o $(OBJDIR)plClothingItem.o

$(OBJDIR)plAGMasterMod.o: PubUtilLib/plAvatar/plAGMasterMod.h PubUtilLib/plAvatar/plAGMasterMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plAGMasterMod.cpp -o $(OBJDIR)plAGMasterMod.o

$(OBJDIR)plMatrixChannel.o: PubUtilLib/plAvatar/plMatrixChannel.h PubUtilLib/plAvatar/plMatrixChannel.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plMatrixChannel.cpp -o $(OBJDIR)plMatrixChannel.o

$(OBJDIR)plMultistageBehMod.o: PubUtilLib/plAvatar/plMultistageBehMod.h PubUtilLib/plAvatar/plMultistageBehMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plMultistageBehMod.cpp -o $(OBJDIR)plMultistageBehMod.o

$(OBJDIR)plNPCSpawnMod.o: PubUtilLib/plAvatar/plNPCSpawnMod.h PubUtilLib/plAvatar/plNPCSpawnMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plNPCSpawnMod.cpp -o $(OBJDIR)plNPCSpawnMod.o

$(OBJDIR)plOneShotMod.o: PubUtilLib/plAvatar/plOneShotMod.h PubUtilLib/plAvatar/plOneShotMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plOneShotMod.cpp -o $(OBJDIR)plOneShotMod.o

$(OBJDIR)plPointChannel.o: PubUtilLib/plAvatar/plPointChannel.h PubUtilLib/plAvatar/plPointChannel.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plPointChannel.cpp -o $(OBJDIR)plPointChannel.o

$(OBJDIR)plQuatChannel.o: PubUtilLib/plAvatar/plQuatChannel.h PubUtilLib/plAvatar/plQuatChannel.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plQuatChannel.cpp -o $(OBJDIR)plQuatChannel.o

$(OBJDIR)plScalarChannel.o: PubUtilLib/plAvatar/plScalarChannel.h PubUtilLib/plAvatar/plScalarChannel.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plScalarChannel.cpp -o $(OBJDIR)plScalarChannel.o

$(OBJDIR)plSittingModifier.o: PubUtilLib/plAvatar/plSittingModifier.h PubUtilLib/plAvatar/plSittingModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plSittingModifier.cpp -o $(OBJDIR)plSittingModifier.o

$(OBJDIR)plSeekPointMod.o: PubUtilLib/plAvatar/plSeekPointMod.h PubUtilLib/plAvatar/plSeekPointMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plAvatar/plSeekPointMod.cpp -o $(OBJDIR)plSeekPointMod.o

$(OBJDIR)plCluster.o: PubUtilLib/plDrawable/plCluster.h PubUtilLib/plDrawable/plCluster.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plCluster.cpp -o $(OBJDIR)plCluster.o

$(OBJDIR)plClusterGroup.o: PubUtilLib/plDrawable/plClusterGroup.h PubUtilLib/plDrawable/plClusterGroup.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plClusterGroup.cpp -o $(OBJDIR)plClusterGroup.o

$(OBJDIR)plDrawableSpans.o: PubUtilLib/plDrawable/plDrawableSpans.h PubUtilLib/plDrawable/plDrawableSpans.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plDrawableSpans.cpp -o $(OBJDIR)plDrawableSpans.o

$(OBJDIR)plDynaDecalMgr.o: PubUtilLib/plDrawable/plDynaDecalMgr.h PubUtilLib/plDrawable/plDynaDecalMgr.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plDynaDecalMgr.cpp -o $(OBJDIR)plDynaDecalMgr.o

$(OBJDIR)plDynaRippleMgr.o: PubUtilLib/plDrawable/plDynaRippleMgr.h PubUtilLib/plDrawable/plDynaRippleMgr.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plDynaRippleMgr.cpp -o $(OBJDIR)plDynaRippleMgr.o

$(OBJDIR)plFixedWaterState6.o: PubUtilLib/plDrawable/plFixedWaterState6.h PubUtilLib/plDrawable/plFixedWaterState6.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plFixedWaterState6.cpp -o $(OBJDIR)plFixedWaterState6.o

$(OBJDIR)plFixedWaterState7.o: PubUtilLib/plDrawable/plFixedWaterState7.h PubUtilLib/plDrawable/plFixedWaterState7.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plFixedWaterState7.cpp -o $(OBJDIR)plFixedWaterState7.o

$(OBJDIR)plMorphArray.o: PubUtilLib/plDrawable/plMorphArray.h PubUtilLib/plDrawable/plMorphArray.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plMorphArray.cpp -o $(OBJDIR)plMorphArray.o

$(OBJDIR)plMorphDataSet.o: PubUtilLib/plDrawable/plMorphDataSet.h PubUtilLib/plDrawable/plMorphDataSet.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plMorphDataSet.cpp -o $(OBJDIR)plMorphDataSet.o

$(OBJDIR)plMorphDelta.o: PubUtilLib/plDrawable/plMorphDelta.h PubUtilLib/plDrawable/plMorphDelta.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plMorphDelta.cpp -o $(OBJDIR)plMorphDelta.o

$(OBJDIR)plSpan.o: PubUtilLib/plDrawable/plSpan.h PubUtilLib/plDrawable/plSpan.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plSpan.cpp -o $(OBJDIR)plSpan.o

$(OBJDIR)plSpanTemplate.o: PubUtilLib/plDrawable/plSpanTemplate.h PubUtilLib/plDrawable/plSpanTemplate.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plSpanTemplate.cpp -o $(OBJDIR)plSpanTemplate.o

$(OBJDIR)plSpanInstance.o: PubUtilLib/plDrawable/plSpanInstance.h PubUtilLib/plDrawable/plSpanInstance.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plSpanInstance.cpp -o $(OBJDIR)plSpanInstance.o

$(OBJDIR)plVertexSpan.o: PubUtilLib/plDrawable/plVertexSpan.h PubUtilLib/plDrawable/plVertexSpan.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plVertexSpan.cpp -o $(OBJDIR)plVertexSpan.o

$(OBJDIR)plIcicle.o: PubUtilLib/plDrawable/plIcicle.h PubUtilLib/plDrawable/plIcicle.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plIcicle.cpp -o $(OBJDIR)plIcicle.o

$(OBJDIR)plGeometrySpan.o: PubUtilLib/plDrawable/plGeometrySpan.h PubUtilLib/plDrawable/plGeometrySpan.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plGeometrySpan.cpp -o $(OBJDIR)plGeometrySpan.o

$(OBJDIR)plSharedMesh.o: PubUtilLib/plDrawable/plSharedMesh.h PubUtilLib/plDrawable/plSharedMesh.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plSharedMesh.cpp -o $(OBJDIR)plSharedMesh.o

$(OBJDIR)plSpaceTree.o: PubUtilLib/plDrawable/plSpaceTree.h PubUtilLib/plDrawable/plSpaceTree.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plSpaceTree.cpp -o $(OBJDIR)plSpaceTree.o

$(OBJDIR)plWaveSetBase.o: PubUtilLib/plDrawable/plWaveSetBase.h PubUtilLib/plDrawable/plWaveSetBase.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plWaveSetBase.cpp -o $(OBJDIR)plWaveSetBase.o

$(OBJDIR)plWaveSet6.o: PubUtilLib/plDrawable/plWaveSet6.h PubUtilLib/plDrawable/plWaveSet6.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plWaveSet6.cpp -o $(OBJDIR)plWaveSet6.o

$(OBJDIR)plWaveSet7.o: PubUtilLib/plDrawable/plWaveSet7.h PubUtilLib/plDrawable/plWaveSet7.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plDrawable/plWaveSet7.cpp -o $(OBJDIR)plWaveSet7.o

$(OBJDIR)plBitmap.o: PubUtilLib/plGImage/plBitmap.h PubUtilLib/plGImage/plBitmap.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGImage/plBitmap.cpp -o $(OBJDIR)plBitmap.o

$(OBJDIR)plCubicEnvironmap.o: PubUtilLib/plGImage/plCubicEnvironmap.h PubUtilLib/plGImage/plCubicEnvironmap.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGImage/plCubicEnvironmap.cpp -o $(OBJDIR)plCubicEnvironmap.o

$(OBJDIR)plDynamicTextMap.o: PubUtilLib/plGImage/plDynamicTextMap.h PubUtilLib/plGImage/plDynamicTextMap.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGImage/plDynamicTextMap.cpp -o $(OBJDIR)plDynamicTextMap.o

$(OBJDIR)plFont.o: PubUtilLib/plGImage/plFont.h PubUtilLib/plGImage/plFont.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGImage/plFont.cpp -o $(OBJDIR)plFont.o

$(OBJDIR)plMipmap.o: PubUtilLib/plGImage/plMipmap.h PubUtilLib/plGImage/plMipmap.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGImage/plMipmap.cpp -o $(OBJDIR)plMipmap.o

$(OBJDIR)plLightInfo.o: PubUtilLib/plGLight/plLightInfo.h PubUtilLib/plGLight/plLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGLight/plLightInfo.cpp -o $(OBJDIR)plLightInfo.o

$(OBJDIR)plDirectionalLightInfo.o: PubUtilLib/plGLight/plDirectionalLightInfo.h PubUtilLib/plGLight/plDirectionalLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGLight/plDirectionalLightInfo.cpp -o $(OBJDIR)plDirectionalLightInfo.o

$(OBJDIR)plOmniLightInfo.o: PubUtilLib/plGLight/plOmniLightInfo.h PubUtilLib/plGLight/plOmniLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGLight/plOmniLightInfo.cpp -o $(OBJDIR)plOmniLightInfo.o

$(OBJDIR)plShadowCaster.o: PubUtilLib/plGLight/plShadowCaster.h PubUtilLib/plGLight/plShadowCaster.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGLight/plShadowCaster.cpp -o $(OBJDIR)plShadowCaster.o

$(OBJDIR)plShadowMaster.o: PubUtilLib/plGLight/plShadowMaster.h PubUtilLib/plGLight/plShadowMaster.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plGLight/plShadowMaster.cpp -o $(OBJDIR)plShadowMaster.o

$(OBJDIR)plAnimTimeConvert.o: PubUtilLib/plInterp/plAnimTimeConvert.h PubUtilLib/plInterp/plAnimTimeConvert.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plAnimTimeConvert.cpp -o $(OBJDIR)plAnimTimeConvert.o

$(OBJDIR)plAnimPath.o: PubUtilLib/plInterp/plAnimPath.h PubUtilLib/plInterp/plAnimPath.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plAnimPath.cpp -o $(OBJDIR)plAnimPath.o

$(OBJDIR)plATCEaseCurves.o: PubUtilLib/plInterp/plATCEaseCurves.h PubUtilLib/plInterp/plATCEaseCurves.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plATCEaseCurves.cpp -o $(OBJDIR)plATCEaseCurves.o

$(OBJDIR)plController.o: PubUtilLib/plInterp/plController.h PubUtilLib/plInterp/plController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plController.cpp -o $(OBJDIR)plController.o

$(OBJDIR)plKeyControllers.o: PubUtilLib/plInterp/plKeyControllers.h PubUtilLib/plInterp/plKeyControllers.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plKeyControllers.cpp -o $(OBJDIR)plKeyControllers.o

$(OBJDIR)plLeafController.o: PubUtilLib/plInterp/plLeafController.h PubUtilLib/plInterp/plLeafController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plLeafController.cpp -o $(OBJDIR)plLeafController.o

$(OBJDIR)plPosController.o: PubUtilLib/plInterp/plPosController.h PubUtilLib/plInterp/plPosController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plPosController.cpp -o $(OBJDIR)plPosController.o

$(OBJDIR)plRotController.o: PubUtilLib/plInterp/plRotController.h PubUtilLib/plInterp/plRotController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plRotController.cpp -o $(OBJDIR)plRotController.o

$(OBJDIR)plScaleController.o: PubUtilLib/plInterp/plScaleController.h PubUtilLib/plInterp/plScaleController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plScaleController.cpp -o $(OBJDIR)plScaleController.o

$(OBJDIR)plTMController.o: PubUtilLib/plInterp/plTMController.h PubUtilLib/plInterp/plTMController.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/plTMController.cpp -o $(OBJDIR)plTMController.o

$(OBJDIR)hsKeys.o: PubUtilLib/plInterp/hsKeys.h PubUtilLib/plInterp/hsKeys.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/hsKeys.cpp -o $(OBJDIR)hsKeys.o

$(OBJDIR)UruKeys.o: PubUtilLib/plInterp/UruKeys.h PubUtilLib/plInterp/UruKeys.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plInterp/UruKeys.cpp -o $(OBJDIR)UruKeys.o

$(OBJDIR)plHardRegion.o: PubUtilLib/plIntersect/plHardRegion.h PubUtilLib/plIntersect/plHardRegion.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plIntersect/plHardRegion.cpp -o $(OBJDIR)plHardRegion.o

$(OBJDIR)plHardRegionPlanes.o: PubUtilLib/plIntersect/plHardRegionPlanes.h PubUtilLib/plIntersect/plHardRegionPlanes.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plIntersect/plHardRegionPlanes.cpp -o $(OBJDIR)plHardRegionPlanes.o

$(OBJDIR)plRegionBase.o: PubUtilLib/plIntersect/plRegionBase.h PubUtilLib/plIntersect/plRegionBase.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plIntersect/plRegionBase.cpp -o $(OBJDIR)plRegionBase.o

$(OBJDIR)plSoftVolume.o: PubUtilLib/plIntersect/plSoftVolume.h PubUtilLib/plIntersect/plSoftVolume.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plIntersect/plSoftVolume.cpp -o $(OBJDIR)plSoftVolume.o

$(OBJDIR)plVolumeIsect.o: PubUtilLib/plIntersect/plVolumeIsect.h PubUtilLib/plIntersect/plVolumeIsect.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plIntersect/plVolumeIsect.cpp -o $(OBJDIR)plVolumeIsect.o

$(OBJDIR)plJPEG.o: PubUtilLib/plJPEG/plJPEG.h PubUtilLib/plJPEG/plJPEG.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plJPEG/plJPEG.cpp -o $(OBJDIR)plJPEG.o

$(OBJDIR)plAnimCmdMsg.o: PubUtilLib/plMessage/plAnimCmdMsg.h PubUtilLib/plMessage/plAnimCmdMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plAnimCmdMsg.cpp -o $(OBJDIR)plAnimCmdMsg.o

$(OBJDIR)plExcludeRegionMsg.o: PubUtilLib/plMessage/plExcludeRegionMsg.h PubUtilLib/plMessage/plExcludeRegionMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plExcludeRegionMsg.cpp -o $(OBJDIR)plExcludeRegionMsg.o

$(OBJDIR)plLinkToAgeMsg.o: PubUtilLib/plMessage/plLinkToAgeMsg.h PubUtilLib/plMessage/plLinkToAgeMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plLinkToAgeMsg.cpp -o $(OBJDIR)plLinkToAgeMsg.o

$(OBJDIR)plOneShotCallbacks.o: PubUtilLib/plMessage/plOneShotCallbacks.h PubUtilLib/plMessage/plOneShotCallbacks.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plOneShotCallbacks.cpp -o $(OBJDIR)plOneShotCallbacks.o

$(OBJDIR)plResponderMsg.o: PubUtilLib/plMessage/plResponderMsg.h PubUtilLib/plMessage/plResponderMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plResponderMsg.cpp -o $(OBJDIR)plResponderMsg.o

$(OBJDIR)plTimerCallbackMsg.o: PubUtilLib/plMessage/plTimerCallbackMsg.h PubUtilLib/plMessage/plTimerCallbackMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plTimerCallbackMsg.cpp -o $(OBJDIR)plTimerCallbackMsg.o

$(OBJDIR)plTransitionMsg.o: PubUtilLib/plMessage/plTransitionMsg.h PubUtilLib/plMessage/plTransitionMsg.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plMessage/plTransitionMsg.cpp -o $(OBJDIR)plTransitionMsg.o

$(OBJDIR)plAnimEventModifier.o: PubUtilLib/plModifier/plAnimEventModifier.h PubUtilLib/plModifier/plAnimEventModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plAnimEventModifier.cpp -o $(OBJDIR)plAnimEventModifier.o

$(OBJDIR)plExcludeRegionModifier.o: PubUtilLib/plModifier/plExcludeRegionModifier.h PubUtilLib/plModifier/plExcludeRegionModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plExcludeRegionModifier.cpp -o $(OBJDIR)plExcludeRegionModifier.o

$(OBJDIR)plImageLibMod.o: PubUtilLib/plModifier/plImageLibMod.h PubUtilLib/plModifier/plImageLibMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plImageLibMod.cpp -o $(OBJDIR)plImageLibMod.o

$(OBJDIR)plInterfaceInfoModifier.o: PubUtilLib/plModifier/plInterfaceInfoModifier.h PubUtilLib/plModifier/plInterfaceInfoModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plInterfaceInfoModifier.cpp -o $(OBJDIR)plInterfaceInfoModifier.o

$(OBJDIR)plLogicModifier.o: PubUtilLib/plModifier/plLogicModifier.h PubUtilLib/plModifier/plLogicModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plLogicModifier.cpp -o $(OBJDIR)plLogicModifier.o

$(OBJDIR)plResponderModifier.o: PubUtilLib/plModifier/plResponderModifier.h PubUtilLib/plModifier/plResponderModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plResponderModifier.cpp -o $(OBJDIR)plResponderModifier.o

$(OBJDIR)plSpawnModifier.o: PubUtilLib/plModifier/plSpawnModifier.h PubUtilLib/plModifier/plSpawnModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plModifier/plSpawnModifier.cpp -o $(OBJDIR)plSpawnModifier.o

$(OBJDIR)plNetServerSessionInfo.o: PubUtilLib/plNetCommon/plNetServerSessionInfo.h PubUtilLib/plNetCommon/plNetServerSessionInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plNetCommon/plNetServerSessionInfo.cpp -o $(OBJDIR)plNetServerSessionInfo.o

$(OBJDIR)plSpawnPointInfo.o: PubUtilLib/plNetCommon/plSpawnPointInfo.h PubUtilLib/plNetCommon/plSpawnPointInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plNetCommon/plSpawnPointInfo.cpp -o $(OBJDIR)plSpawnPointInfo.o

$(OBJDIR)plBoundInterface.o: PubUtilLib/plParticleSystem/plBoundInterface.h PubUtilLib/plParticleSystem/plBoundInterface.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plParticleSystem/plBoundInterface.cpp -o $(OBJDIR)plBoundInterface.o

$(OBJDIR)plConvexVolume.o: PubUtilLib/plParticleSystem/plConvexVolume.h PubUtilLib/plParticleSystem/plConvexVolume.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plParticleSystem/plConvexVolume.cpp -o $(OBJDIR)plConvexVolume.o

$(OBJDIR)plParticleApplicator.o: PubUtilLib/plParticleSystem/plParticleApplicator.h PubUtilLib/plParticleSystem/plParticleApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plParticleSystem/plParticleApplicator.cpp -o $(OBJDIR)plParticleApplicator.o

$(OBJDIR)plParticleEffect.o: PubUtilLib/plParticleSystem/plParticleEffect.h PubUtilLib/plParticleSystem/plParticleEffect.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plParticleSystem/plParticleEffect.cpp -o $(OBJDIR)plParticleEffect.o

$(OBJDIR)plParticleEmitter.o: PubUtilLib/plParticleSystem/plParticleEmitter.h PubUtilLib/plParticleSystem/plParticleEmitter.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plParticleSystem/plParticleEmitter.cpp -o $(OBJDIR)plParticleEmitter.o

$(OBJDIR)plParticleGenerator.o: PubUtilLib/plParticleSystem/plParticleGenerator.h PubUtilLib/plParticleSystem/plParticleGenerator.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plParticleSystem/plParticleGenerator.cpp -o $(OBJDIR)plParticleGenerator.o

$(OBJDIR)plParticleSystem.o: PubUtilLib/plParticleSystem/plParticleSystem.h PubUtilLib/plParticleSystem/plParticleSystem.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plParticleSystem/plParticleSystem.cpp -o $(OBJDIR)plParticleSystem.o

$(OBJDIR)plCollisionDetector.o: PubUtilLib/plPhysics/plCollisionDetector.h PubUtilLib/plPhysics/plCollisionDetector.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plCollisionDetector.cpp -o $(OBJDIR)plCollisionDetector.o

$(OBJDIR)plDetectorModifier.o: PubUtilLib/plPhysics/plDetectorModifier.h PubUtilLib/plPhysics/plDetectorModifier.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plDetectorModifier.cpp -o $(OBJDIR)plDetectorModifier.o

$(OBJDIR)plObjectInVolumeDetector.o: PubUtilLib/plPhysics/plObjectInVolumeDetector.h PubUtilLib/plPhysics/plObjectInVolumeDetector.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plObjectInVolumeDetector.cpp -o $(OBJDIR)plObjectInVolumeDetector.o

$(OBJDIR)plPhysical.o: PubUtilLib/plPhysics/plPhysical.h PubUtilLib/plPhysics/plPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plPhysical.cpp -o $(OBJDIR)plPhysical.o

$(OBJDIR)plHKPhysical.o: PubUtilLib/plPhysics/plHKPhysical.h PubUtilLib/plPhysics/plHKPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plHKPhysical.cpp -o $(OBJDIR)plHKPhysical.o

$(OBJDIR)plPXPhysical.o: PubUtilLib/plPhysics/plPXPhysical.h PubUtilLib/plPhysics/plPXPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plPXPhysical.cpp -o $(OBJDIR)plPXPhysical.o

$(OBJDIR)plODEPhysical.o: PubUtilLib/plPhysics/plODEPhysical.h PubUtilLib/plPhysics/plODEPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plODEPhysical.cpp -o $(OBJDIR)plODEPhysical.o

$(OBJDIR)plPhysicalSndGroup.o: PubUtilLib/plPhysics/plPhysicalSndGroup.h PubUtilLib/plPhysics/plPhysicalSndGroup.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPhysics/plPhysicalSndGroup.cpp -o $(OBJDIR)plPhysicalSndGroup.o

$(OBJDIR)plDynamicEnvMap.o: PubUtilLib/plPipeline/plDynamicEnvMap.h PubUtilLib/plPipeline/plDynamicEnvMap.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPipeline/plDynamicEnvMap.cpp -o $(OBJDIR)plDynamicEnvMap.o

$(OBJDIR)plFogEnvironment.o: PubUtilLib/plPipeline/plFogEnvironment.h PubUtilLib/plPipeline/plFogEnvironment.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPipeline/plFogEnvironment.cpp -o $(OBJDIR)plFogEnvironment.o

$(OBJDIR)hsGDeviceRef.o: PubUtilLib/plPipeline/hsGDeviceRef.h PubUtilLib/plPipeline/hsGDeviceRef.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPipeline/hsGDeviceRef.cpp -o $(OBJDIR)hsGDeviceRef.o

$(OBJDIR)plGBufferGroup.o: PubUtilLib/plPipeline/plGBufferGroup.h PubUtilLib/plPipeline/plGBufferGroup.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPipeline/plGBufferGroup.cpp -o $(OBJDIR)plGBufferGroup.o

$(OBJDIR)plRenderTarget.o: PubUtilLib/plPipeline/plRenderTarget.h PubUtilLib/plPipeline/plRenderTarget.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPipeline/plRenderTarget.cpp -o $(OBJDIR)plRenderTarget.o

$(OBJDIR)plVertCoder.o: PubUtilLib/plPipeline/plVertCoder.h PubUtilLib/plPipeline/plVertCoder.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plPipeline/plVertCoder.cpp -o $(OBJDIR)plVertCoder.o

$(OBJDIR)plAgeInfo.o: PubUtilLib/plResMgr/plAgeInfo.h PubUtilLib/plResMgr/plAgeInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plResMgr/plAgeInfo.cpp -o $(OBJDIR)plAgeInfo.o

$(OBJDIR)plKeyCollector.o: PubUtilLib/plResMgr/plKeyCollector.h PubUtilLib/plResMgr/plKeyCollector.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plResMgr/plKeyCollector.cpp -o $(OBJDIR)plKeyCollector.o

$(OBJDIR)plPageInfo.o: PubUtilLib/plResMgr/plPageInfo.h PubUtilLib/plResMgr/plPageInfo.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plResMgr/plPageInfo.cpp -o $(OBJDIR)plPageInfo.o

$(OBJDIR)plResManager.o: PubUtilLib/plResMgr/plResManager.h PubUtilLib/plResMgr/plResManager.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plResMgr/plResManager.cpp -o $(OBJDIR)plResManager.o

$(OBJDIR)plCullPoly.o: PubUtilLib/plScene/plCullPoly.h PubUtilLib/plScene/plCullPoly.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plScene/plCullPoly.cpp -o $(OBJDIR)plCullPoly.o

$(OBJDIR)plOccluder.o: PubUtilLib/plScene/plOccluder.h PubUtilLib/plScene/plOccluder.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plScene/plOccluder.cpp -o $(OBJDIR)plOccluder.o

$(OBJDIR)plPostEffectMod.o: PubUtilLib/plScene/plPostEffectMod.h PubUtilLib/plScene/plPostEffectMod.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plScene/plPostEffectMod.cpp -o $(OBJDIR)plPostEffectMod.o

$(OBJDIR)plRelevanceRegion.o: PubUtilLib/plScene/plRelevanceRegion.h PubUtilLib/plScene/plRelevanceRegion.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plScene/plRelevanceRegion.cpp -o $(OBJDIR)plRelevanceRegion.o

$(OBJDIR)plSceneNode.o: PubUtilLib/plScene/plSceneNode.h PubUtilLib/plScene/plSceneNode.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plScene/plSceneNode.cpp -o $(OBJDIR)plSceneNode.o

$(OBJDIR)plVisRegion.o: PubUtilLib/plScene/plVisRegion.h PubUtilLib/plScene/plVisRegion.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plScene/plVisRegion.cpp -o $(OBJDIR)plVisRegion.o

$(OBJDIR)plSDL.o: PubUtilLib/plSDL/plSDL.h PubUtilLib/plSDL/plSDL.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSDL/plSDL.cpp -o $(OBJDIR)plSDL.o

$(OBJDIR)plSDLMgr.o: PubUtilLib/plSDL/plSDLMgr.h PubUtilLib/plSDL/plSDLMgr.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSDL/plSDLMgr.cpp -o $(OBJDIR)plSDLMgr.o

$(OBJDIR)plStateDataRecord.o: PubUtilLib/plSDL/plStateDataRecord.h PubUtilLib/plSDL/plStateDataRecord.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSDL/plStateDataRecord.cpp -o $(OBJDIR)plStateDataRecord.o

$(OBJDIR)plStateDescriptor.o: PubUtilLib/plSDL/plStateDescriptor.h PubUtilLib/plSDL/plStateDescriptor.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSDL/plStateDescriptor.cpp -o $(OBJDIR)plStateDescriptor.o

$(OBJDIR)plStateVariable.o: PubUtilLib/plSDL/plStateVariable.h PubUtilLib/plSDL/plStateVariable.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSDL/plStateVariable.cpp -o $(OBJDIR)plStateVariable.o

$(OBJDIR)hsGMaterial.o: PubUtilLib/plSurface/hsGMaterial.h PubUtilLib/plSurface/hsGMaterial.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSurface/hsGMaterial.cpp -o $(OBJDIR)hsGMaterial.o

$(OBJDIR)plLayerInterface.o: PubUtilLib/plSurface/plLayerInterface.h PubUtilLib/plSurface/plLayerInterface.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSurface/plLayerInterface.cpp -o $(OBJDIR)plLayerInterface.o

$(OBJDIR)plLayer.o: PubUtilLib/plSurface/plLayer.h PubUtilLib/plSurface/plLayer.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSurface/plLayer.cpp -o $(OBJDIR)plLayer.o

$(OBJDIR)plLayerAnimation.o: PubUtilLib/plSurface/plLayerAnimation.h PubUtilLib/plSurface/plLayerAnimation.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSurface/plLayerAnimation.cpp -o $(OBJDIR)plLayerAnimation.o

$(OBJDIR)plLayerMovie.o: PubUtilLib/plSurface/plLayerMovie.h PubUtilLib/plSurface/plLayerMovie.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plSurface/plLayerMovie.cpp -o $(OBJDIR)plLayerMovie.o

$(OBJDIR)hsAffineParts.o: PubUtilLib/plTransform/hsAffineParts.h PubUtilLib/plTransform/hsAffineParts.cpp
	$(CXX) $(CXXFLAGS) -c PubUtilLib/plTransform/hsAffineParts.cpp -o $(OBJDIR)hsAffineParts.o

$(OBJDIR)plBlower.o: FeatureLib/pfAnimation/plBlower.h FeatureLib/pfAnimation/plBlower.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAnimation/plBlower.cpp -o $(OBJDIR)plBlower.o

$(OBJDIR)plFilterCoordInterface.o: FeatureLib/pfAnimation/plFilterCoordInterface.h FeatureLib/pfAnimation/plFilterCoordInterface.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAnimation/plFilterCoordInterface.cpp -o $(OBJDIR)plFilterCoordInterface.o

$(OBJDIR)plLineFollowMod.o: FeatureLib/pfAnimation/plLineFollowMod.h FeatureLib/pfAnimation/plLineFollowMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAnimation/plLineFollowMod.cpp -o $(OBJDIR)plLineFollowMod.o

$(OBJDIR)plRandomCommandMod.o: FeatureLib/pfAnimation/plRandomCommandMod.h FeatureLib/pfAnimation/plRandomCommandMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAnimation/plRandomCommandMod.cpp -o $(OBJDIR)plRandomCommandMod.o

$(OBJDIR)plStereizer.o: FeatureLib/pfAnimation/plStereizer.h FeatureLib/pfAnimation/plStereizer.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAnimation/plStereizer.cpp -o $(OBJDIR)plStereizer.o

$(OBJDIR)plViewFaceModifier.o: FeatureLib/pfAnimation/plViewFaceModifier.h FeatureLib/pfAnimation/plViewFaceModifier.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAnimation/plViewFaceModifier.cpp -o $(OBJDIR)plViewFaceModifier.o

$(OBJDIR)plRandomSoundMod.o: FeatureLib/pfAudio/plRandomSoundMod.h FeatureLib/pfAudio/plRandomSoundMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfAudio/plRandomSoundMod.cpp -o $(OBJDIR)plRandomSoundMod.o

$(OBJDIR)plCameraBrain.o: FeatureLib/pfCamera/plCameraBrain.h FeatureLib/pfCamera/plCameraBrain.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfCamera/plCameraBrain.cpp -o $(OBJDIR)plCameraBrain.o

$(OBJDIR)plCameraModifier.o: FeatureLib/pfCamera/plCameraModifier.h FeatureLib/pfCamera/plCameraModifier.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfCamera/plCameraModifier.cpp -o $(OBJDIR)plCameraModifier.o

$(OBJDIR)plConditionalObject.o: FeatureLib/pfConditional/plConditionalObject.h FeatureLib/pfConditional/plConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plConditionalObject.cpp -o $(OBJDIR)plConditionalObject.o

$(OBJDIR)plActivatorConditionalObject.o: FeatureLib/pfConditional/plActivatorConditionalObject.h FeatureLib/pfConditional/plActivatorConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plActivatorConditionalObject.cpp -o $(OBJDIR)plActivatorConditionalObject.o

$(OBJDIR)plAnimationEventConditionalObject.o: FeatureLib/pfConditional/plAnimationEventConditionalObject.h FeatureLib/pfConditional/plAnimationEventConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plAnimationEventConditionalObject.cpp -o $(OBJDIR)plAnimationEventConditionalObject.o

$(OBJDIR)plBooleanConditionalObject.o: FeatureLib/pfConditional/plBooleanConditionalObject.h FeatureLib/pfConditional/plBooleanConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plBooleanConditionalObject.cpp -o $(OBJDIR)plBooleanConditionalObject.o

$(OBJDIR)plControlEventConditionalObject.o: FeatureLib/pfConditional/plControlEventConditionalObject.h FeatureLib/pfConditional/plControlEventConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plControlEventConditionalObject.cpp -o $(OBJDIR)plControlEventConditionalObject.o

$(OBJDIR)plDetectConditionalObjects.o: FeatureLib/pfConditional/plDetectConditionalObjects.h FeatureLib/pfConditional/plDetectConditionalObjects.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plDetectConditionalObjects.cpp -o $(OBJDIR)plDetectConditionalObjects.o

$(OBJDIR)plFacingConditionalObject.o: FeatureLib/pfConditional/plFacingConditionalObject.h FeatureLib/pfConditional/plFacingConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plFacingConditionalObject.cpp -o $(OBJDIR)plFacingConditionalObject.o

$(OBJDIR)plKeyPressConditionalObject.o: FeatureLib/pfConditional/plKeyPressConditionalObject.h FeatureLib/pfConditional/plKeyPressConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plKeyPressConditionalObject.cpp -o $(OBJDIR)plKeyPressConditionalObject.o

$(OBJDIR)plPickedConditionalObject.o: FeatureLib/pfConditional/plPickedConditionalObject.h FeatureLib/pfConditional/plPickedConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plPickedConditionalObject.cpp -o $(OBJDIR)plPickedConditionalObject.o

$(OBJDIR)plPythonFileModConditionalObject.o: FeatureLib/pfConditional/plPythonFileModConditionalObject.h FeatureLib/pfConditional/plPythonFileModConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plPythonFileModConditionalObject.cpp -o $(OBJDIR)plPythonFileModConditionalObject.o

$(OBJDIR)plVolumeSensorConditionalObject.o: FeatureLib/pfConditional/plVolumeSensorConditionalObject.h FeatureLib/pfConditional/plVolumeSensorConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfConditional/plVolumeSensorConditionalObject.cpp -o $(OBJDIR)plVolumeSensorConditionalObject.o

$(OBJDIR)pfGUIControlHandlers.o: FeatureLib/pfGameGUIMgr/pfGUIControlHandlers.h FeatureLib/pfGameGUIMgr/pfGUIControlHandlers.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIControlHandlers.cpp -o $(OBJDIR)pfGUIControlHandlers.o

$(OBJDIR)pfGUIControlMod.o: FeatureLib/pfGameGUIMgr/pfGUIControlMod.h FeatureLib/pfGameGUIMgr/pfGUIControlMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIControlMod.cpp -o $(OBJDIR)pfGUIControlMod.o

$(OBJDIR)pfGUIButtonMod.o: FeatureLib/pfGameGUIMgr/pfGUIButtonMod.h FeatureLib/pfGameGUIMgr/pfGUIButtonMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIButtonMod.cpp -o $(OBJDIR)pfGUIButtonMod.o

$(OBJDIR)pfGUICheckBoxCtrl.o: FeatureLib/pfGameGUIMgr/pfGUICheckBoxCtrl.h FeatureLib/pfGameGUIMgr/pfGUICheckBoxCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUICheckBoxCtrl.cpp -o $(OBJDIR)pfGUICheckBoxCtrl.o

$(OBJDIR)pfGUIClickMapCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIClickMapCtrl.h FeatureLib/pfGameGUIMgr/pfGUIClickMapCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIClickMapCtrl.cpp -o $(OBJDIR)pfGUIClickMapCtrl.o

$(OBJDIR)pfGUIDialogMod.o: FeatureLib/pfGameGUIMgr/pfGUIDialogMod.h FeatureLib/pfGameGUIMgr/pfGUIDialogMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIDialogMod.cpp -o $(OBJDIR)pfGUIDialogMod.o

$(OBJDIR)pfGUIDragBarCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIDragBarCtrl.h FeatureLib/pfGameGUIMgr/pfGUIDragBarCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIDragBarCtrl.cpp -o $(OBJDIR)pfGUIDragBarCtrl.o

$(OBJDIR)pfGUIDraggableMod.o: FeatureLib/pfGameGUIMgr/pfGUIDraggableMod.h FeatureLib/pfGameGUIMgr/pfGUIDraggableMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIDraggableMod.cpp -o $(OBJDIR)pfGUIDraggableMod.o

$(OBJDIR)pfGUIDynDisplayCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIDynDisplayCtrl.h FeatureLib/pfGameGUIMgr/pfGUIDynDisplayCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIDynDisplayCtrl.cpp -o $(OBJDIR)pfGUIDynDisplayCtrl.o

$(OBJDIR)pfGUIEditBoxMod.o: FeatureLib/pfGameGUIMgr/pfGUIEditBoxMod.h FeatureLib/pfGameGUIMgr/pfGUIEditBoxMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIEditBoxMod.cpp -o $(OBJDIR)pfGUIEditBoxMod.o

$(OBJDIR)pfGUIListBoxMod.o: FeatureLib/pfGameGUIMgr/pfGUIListBoxMod.h FeatureLib/pfGameGUIMgr/pfGUIListBoxMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIListBoxMod.cpp -o $(OBJDIR)pfGUIListBoxMod.o

$(OBJDIR)pfGUIMultiLineEditCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIMultiLineEditCtrl.h FeatureLib/pfGameGUIMgr/pfGUIMultiLineEditCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIMultiLineEditCtrl.cpp -o $(OBJDIR)pfGUIMultiLineEditCtrl.o

$(OBJDIR)pfGUIPopUpMenu.o: FeatureLib/pfGameGUIMgr/pfGUIPopUpMenu.h FeatureLib/pfGameGUIMgr/pfGUIPopUpMenu.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIPopUpMenu.cpp -o $(OBJDIR)pfGUIPopUpMenu.o

$(OBJDIR)pfGUIRadioGroupCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIRadioGroupCtrl.h FeatureLib/pfGameGUIMgr/pfGUIRadioGroupCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIRadioGroupCtrl.cpp -o $(OBJDIR)pfGUIRadioGroupCtrl.o

$(OBJDIR)pfGUISkin.o: FeatureLib/pfGameGUIMgr/pfGUISkin.h FeatureLib/pfGameGUIMgr/pfGUISkin.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUISkin.cpp -o $(OBJDIR)pfGUISkin.o

$(OBJDIR)pfGUITextBoxMod.o: FeatureLib/pfGameGUIMgr/pfGUITextBoxMod.h FeatureLib/pfGameGUIMgr/pfGUITextBoxMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUITextBoxMod.cpp -o $(OBJDIR)pfGUITextBoxMod.o

$(OBJDIR)pfGUIValueCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIValueCtrl.h FeatureLib/pfGameGUIMgr/pfGUIValueCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIValueCtrl.cpp -o $(OBJDIR)pfGUIValueCtrl.o

$(OBJDIR)pfGUIKnobCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIKnobCtrl.h FeatureLib/pfGameGUIMgr/pfGUIKnobCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIKnobCtrl.cpp -o $(OBJDIR)pfGUIKnobCtrl.o

$(OBJDIR)pfGUIProgressCtrl.o: FeatureLib/pfGameGUIMgr/pfGUIProgressCtrl.h FeatureLib/pfGameGUIMgr/pfGUIProgressCtrl.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIProgressCtrl.cpp -o $(OBJDIR)pfGUIProgressCtrl.o

$(OBJDIR)pfGUIUpDownPairMod.o: FeatureLib/pfGameGUIMgr/pfGUIUpDownPairMod.h FeatureLib/pfGameGUIMgr/pfGUIUpDownPairMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfGameGUIMgr/pfGUIUpDownPairMod.cpp -o $(OBJDIR)pfGUIUpDownPairMod.o

$(OBJDIR)plArmatureEffectMsg.o: FeatureLib/pfMessage/plArmatureEffectMsg.h FeatureLib/pfMessage/plArmatureEffectMsg.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfMessage/plArmatureEffectMsg.cpp -o $(OBJDIR)plArmatureEffectMsg.o

$(OBJDIR)plPythonFileMod.o: FeatureLib/pfPython/plPythonFileMod.h FeatureLib/pfPython/plPythonFileMod.cpp
	$(CXX) $(CXXFLAGS) -c FeatureLib/pfPython/plPythonFileMod.cpp -o $(OBJDIR)plPythonFileMod.o
