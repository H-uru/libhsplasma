include ../config.mf

CXXFLAGS += -I.
OBJDIR=out/

PLSOBJ=\
	$(OBJDIR)plDebug.o \
	$(OBJDIR)hsExceptions.o \
	$(OBJDIR)hsAffineParts.o \
	$(OBJDIR)hsGeometry3.o \
	$(OBJDIR)hsMatrix33.o \
	$(OBJDIR)hsMatrix44.o \
	$(OBJDIR)hsQuat.o \
	$(OBJDIR)plAgeInfo.o \
	$(OBJDIR)plFactory.o \
	$(OBJDIR)plKeyCollector.o \
	$(OBJDIR)plResManager.o \
	$(OBJDIR)pdUnifiedTypeMap.o \
	$(OBJDIR)plNetGameServerState.o \
	$(OBJDIR)plSDL.o \
	$(OBJDIR)plSDLMgr.o \
	$(OBJDIR)plStateDataRecord.o \
	$(OBJDIR)plStateDescriptor.o \
	$(OBJDIR)plStateVariable.o \
	$(OBJDIR)hsElfStream.o \
	$(OBJDIR)plEncryptedStream.o \
	$(OBJDIR)pfPrcHelper.o \
	$(OBJDIR)pfPrcParser.o \
	$(OBJDIR)hsRAMStream.o \
	$(OBJDIR)hsStdioStream.o \
	$(OBJDIR)hsStream.o \
	$(OBJDIR)hsTokenStream.o \
	$(OBJDIR)hsColor.o \
	$(OBJDIR)hsThread.o \
	$(OBJDIR)plUnifiedTime.o \
	$(OBJDIR)plUuid.o \
	$(OBJDIR)hsBitVector.o \
	$(OBJDIR)plJPEG.o \
	$(OBJDIR)plMD5.o \
	$(OBJDIR)PlasmaVersions.o \
	$(OBJDIR)plString.o \
	$(OBJDIR)plZlib.o \
	$(OBJDIR)plServerGuid.o \
	$(OBJDIR)plVaultNode.o \
	$(OBJDIR)plVaultNodeRef.o \
	$(OBJDIR)plVaultNodeTypes.o \
	$(OBJDIR)plVaultStore.o \
	$(OBJDIR)plCreatable.o \
	$(OBJDIR)plPageInfo.o \
	$(OBJDIR)plSceneNode.o \
	$(OBJDIR)plAnimPath.o \
	$(OBJDIR)plAnimTimeConvert.o \
	$(OBJDIR)plATCEaseCurves.o \
	$(OBJDIR)plBlower.o \
	$(OBJDIR)plController.o \
	$(OBJDIR)plFilterCoordInterface.o \
	$(OBJDIR)hsKeys.o \
	$(OBJDIR)plKeyControllers.o \
	$(OBJDIR)plLeafController.o \
	$(OBJDIR)plLineFollowMod.o \
	$(OBJDIR)pfObjectFlocker.o \
	$(OBJDIR)plPosController.o \
	$(OBJDIR)plRotController.o \
	$(OBJDIR)plScaleController.o \
	$(OBJDIR)plStereizer.o \
	$(OBJDIR)plTMController.o \
	$(OBJDIR)plViewFaceModifier.o \
	$(OBJDIR)plAudible.o \
	$(OBJDIR)plCrossfade.o \
	$(OBJDIR)plDirectMusicSound.o \
	$(OBJDIR)plEAXEffects.o \
	$(OBJDIR)plEAXListenerMod.o \
	$(OBJDIR)plSound.o \
	$(OBJDIR)plSoundBuffer.o \
	$(OBJDIR)plWin32Sound.o \
	$(OBJDIR)plWin32StaticSound.o \
	$(OBJDIR)plAGAnim.o \
	$(OBJDIR)plAGApplicator.o \
	$(OBJDIR)plAGChannel.o \
	$(OBJDIR)plAGMasterMod.o \
	$(OBJDIR)plAGModifier.o \
	$(OBJDIR)plAnimStage.o \
	$(OBJDIR)plArmatureBrain.o \
	$(OBJDIR)plArmatureEffects.o \
	$(OBJDIR)plArmatureMod.o \
	$(OBJDIR)plATCAnim.o \
	$(OBJDIR)plAvatarClothing.o \
	$(OBJDIR)plClothingItem.o \
	$(OBJDIR)plElevatorModifier.o \
	$(OBJDIR)plLadderModifier.o \
	$(OBJDIR)plMatrixChannel.o \
	$(OBJDIR)plMultistageBehMod.o \
	$(OBJDIR)plNPCSpawnMod.o \
	$(OBJDIR)plPointChannel.o \
	$(OBJDIR)plQuatChannel.o \
	$(OBJDIR)plScalarChannel.o \
	$(OBJDIR)plSeekPointMod.o \
	$(OBJDIR)plSittingModifier.o \
	$(OBJDIR)plCameraBrain.o \
	$(OBJDIR)plCameraModifier.o \
	$(OBJDIR)plActivatorConditionalObject.o \
	$(OBJDIR)plAnimationEventConditionalObject.o \
	$(OBJDIR)plBooleanConditionalObject.o \
	$(OBJDIR)plConditionalObject.o \
	$(OBJDIR)plControlEventConditionalObject.o \
	$(OBJDIR)plDetectConditionalObjects.o \
	$(OBJDIR)plFacingConditionalObject.o \
	$(OBJDIR)plKeyPressConditionalObject.o \
	$(OBJDIR)plVolumeSensorConditionalObject.o \
	$(OBJDIR)plCluster.o \
	$(OBJDIR)plClusterGroup.o \
	$(OBJDIR)plCullPoly.o \
	$(OBJDIR)plDrawableSpans.o \
	$(OBJDIR)plGBufferGroup.o \
	$(OBJDIR)hsGDeviceRef.o \
	$(OBJDIR)plGeometrySpan.o \
	$(OBJDIR)plIcicle.o \
	$(OBJDIR)plMorphArray.o \
	$(OBJDIR)plMorphDataSet.o \
	$(OBJDIR)plMorphDelta.o \
	$(OBJDIR)plOccluder.o \
	$(OBJDIR)plSharedMesh.o \
	$(OBJDIR)plSpaceTree.o \
	$(OBJDIR)plSpan.o \
	$(OBJDIR)plSpanInstance.o \
	$(OBJDIR)plSpanTemplate.o \
	$(OBJDIR)plVertCoder.o \
	$(OBJDIR)plVertexSpan.o \
	$(OBJDIR)pfGUIButtonMod.o \
	$(OBJDIR)pfGUICheckBoxCtrl.o \
	$(OBJDIR)pfGUIClickMapCtrl.o \
	$(OBJDIR)pfGUIControlHandlers.o \
	$(OBJDIR)pfGUIControlMod.o \
	$(OBJDIR)pfGUIDialogMod.o \
	$(OBJDIR)pfGUIDragBarCtrl.o \
	$(OBJDIR)pfGUIDraggableMod.o \
	$(OBJDIR)pfGUIDynDisplayCtrl.o \
	$(OBJDIR)pfGUIEditBoxMod.o \
	$(OBJDIR)pfGUIKnobCtrl.o \
	$(OBJDIR)pfGUIListBoxMod.o \
	$(OBJDIR)pfGUIMultiLineEditCtrl.o \
	$(OBJDIR)pfGUIPopUpMenu.o \
	$(OBJDIR)pfGUIProgressCtrl.o \
	$(OBJDIR)pfGUIRadioGroupCtrl.o \
	$(OBJDIR)pfGUISkin.o \
	$(OBJDIR)pfGUITextBoxMod.o \
	$(OBJDIR)pfGUIUpDownPairMod.o \
	$(OBJDIR)pfGUIValueCtrl.o \
	$(OBJDIR)plImageLibMod.o \
	$(OBJDIR)hsKeyedObject.o \
	$(OBJDIR)plKey.o \
	$(OBJDIR)plLoadMask.o \
	$(OBJDIR)plLocation.o \
	$(OBJDIR)plReceiver.o \
	$(OBJDIR)plUoid.o \
	$(OBJDIR)plDirectionalLightInfo.o \
	$(OBJDIR)plLightInfo.o \
	$(OBJDIR)plOmniLightInfo.o \
	$(OBJDIR)plShadowCaster.o \
	$(OBJDIR)plShadowMaster.o \
	$(OBJDIR)plAnimCmdMsg.o \
	$(OBJDIR)plArmatureEffectMsg.o \
	$(OBJDIR)plAvatarInputStateMsg.o \
	$(OBJDIR)plCameraMsg.o \
	$(OBJDIR)plClimbMsg.o \
	$(OBJDIR)plEnableMsg.o \
	$(OBJDIR)plEventCallbackMsg.o \
	$(OBJDIR)proEventData.o \
	$(OBJDIR)plExcludeRegionMsg.o \
	$(OBJDIR)plLinkToAgeMsg.o \
	$(OBJDIR)plLoadCloneMsg.o \
	$(OBJDIR)plMessage.o \
	$(OBJDIR)plMessageWithCallbacks.o \
	$(OBJDIR)plMsgForwarder.o \
	$(OBJDIR)plNotifyMsg.o \
	$(OBJDIR)plOneShotCallbacks.o \
	$(OBJDIR)plPseudoLinkEffectMsg.o \
	$(OBJDIR)plResponderMsg.o \
	$(OBJDIR)plServerReplyMsg.o \
	$(OBJDIR)plSimulationMsg.o \
	$(OBJDIR)plSoundMsg.o \
	$(OBJDIR)plSwimMsg.o \
	$(OBJDIR)plTimerCallbackMsg.o \
	$(OBJDIR)plTransitionMsg.o \
	$(OBJDIR)plAgeLinkInfo.o \
	$(OBJDIR)plFogEnvironment.o \
	$(OBJDIR)plSpawnPointInfo.o \
	$(OBJDIR)plAliasModifier.o \
	$(OBJDIR)plAnimEventModifier.o \
	$(OBJDIR)plAxisAnimModifier.o \
	$(OBJDIR)plExcludeRegionModifier.o \
	$(OBJDIR)plInterfaceInfoModifier.o \
	$(OBJDIR)plLogicModBase.o \
	$(OBJDIR)plLogicModifier.o \
	$(OBJDIR)plMaintainersMarkerModifier.o \
	$(OBJDIR)plModifier.o \
	$(OBJDIR)plNodeRegionModifier.o \
	$(OBJDIR)plOneShotMod.o \
	$(OBJDIR)plPostEffectMod.o \
	$(OBJDIR)plPythonFileMod.o \
	$(OBJDIR)plPythonMod.o \
	$(OBJDIR)plRandomCommandMod.o \
	$(OBJDIR)plRandomSoundMod.o \
	$(OBJDIR)plResponderModifier.o \
	$(OBJDIR)plSpawnModifier.o \
	$(OBJDIR)plClientGuid.o \
	$(OBJDIR)plNetGroupId.o \
	$(OBJDIR)plNetMessage.o \
	$(OBJDIR)plNetMsgGameMessage.o \
	$(OBJDIR)plNetMsgGroupOwner.o \
	$(OBJDIR)plNetMsgInitialAgeStateSent.o \
	$(OBJDIR)plNetMsgLoadClone.o \
	$(OBJDIR)plNetMsgMembersList.o \
	$(OBJDIR)plNetMsgObject.o \
	$(OBJDIR)plNetMsgPlayerPage.o \
	$(OBJDIR)plNetMsgRelevanceRegions.o \
	$(OBJDIR)plNetMsgRoomsList.o \
	$(OBJDIR)plNetMsgSDLState.o \
	$(OBJDIR)plNetMsgSharedState.o \
	$(OBJDIR)plNetMsgStream.o \
	$(OBJDIR)plNetMsgStreamedObject.o \
	$(OBJDIR)plNetSharedState.o \
	$(OBJDIR)plAudioInterface.o \
	$(OBJDIR)plCoordinateInterface.o \
	$(OBJDIR)plDrawInterface.o \
	$(OBJDIR)plObjInterface.o \
	$(OBJDIR)plSceneObject.o \
	$(OBJDIR)plSimulationInterface.o \
	$(OBJDIR)plSynchedObject.o \
	$(OBJDIR)plBoundInterface.o \
	$(OBJDIR)plParticleApplicator.o \
	$(OBJDIR)plParticleEffect.o \
	$(OBJDIR)plParticleEmitter.o \
	$(OBJDIR)plParticleGenerator.o \
	$(OBJDIR)plParticleSystem.o \
	$(OBJDIR)plCollisionDetector.o \
	$(OBJDIR)plDetectorModifier.o \
	$(OBJDIR)plGenericPhysical.o \
	$(OBJDIR)plObjectInVolumeDetector.o \
	$(OBJDIR)plPhysical.o \
	$(OBJDIR)plPhysicalSndGroup.o \
	$(OBJDIR)plVehicleModifier.o \
	$(OBJDIR)hsBounds.o \
	$(OBJDIR)plConvexVolume.o \
	$(OBJDIR)plHardRegion.o \
	$(OBJDIR)plHardRegionPlanes.o \
	$(OBJDIR)plRegionBase.o \
	$(OBJDIR)plRelevanceRegion.o \
	$(OBJDIR)plSimpleRegionSensor.o \
	$(OBJDIR)plSoftVolume.o \
	$(OBJDIR)plSwimRegion.o \
	$(OBJDIR)plVisRegion.o \
	$(OBJDIR)plVolumeIsect.o \
	$(OBJDIR)plBitmap.o \
	$(OBJDIR)plCubicEnvironmap.o \
	$(OBJDIR)plDistOpacityMod.o \
	$(OBJDIR)plDynaDecalMgr.o \
	$(OBJDIR)plDynamicEnvMap.o \
	$(OBJDIR)plDynamicTextMap.o \
	$(OBJDIR)plDynaRippleMgr.o \
	$(OBJDIR)plFadeOpacityMod.o \
	$(OBJDIR)plFixedWaterState6.o \
	$(OBJDIR)plFixedWaterState7.o \
	$(OBJDIR)plFont.o \
	$(OBJDIR)hsGMaterial.o \
	$(OBJDIR)hsGMatState.o \
	$(OBJDIR)plGrassShaderMod.o \
	$(OBJDIR)plLayer.o \
	$(OBJDIR)plLayerAnimation.o \
	$(OBJDIR)plLayerInterface.o \
	$(OBJDIR)plLayerMovie.o \
	$(OBJDIR)plMipmap.o \
	$(OBJDIR)plPrintShape.o \
	$(OBJDIR)plRenderTarget.o \
	$(OBJDIR)plShader.o \
	$(OBJDIR)plWaveSet6.o \
	$(OBJDIR)plWaveSet7.o \
	$(OBJDIR)plWaveSetBase.o

# 3rd Party Libs
OBJFILES3P=\
	$(OBJDIR)rijndael.o \
	3rdPartyLibs/squish/libsquish.a

PLSLIB=libPlasma.$(LIBSUFFIX)
LIBDIR=../lib

all: $(LIBDIR)/$(PLSLIB)

$(LIBDIR)/$(PLSLIB): $(PLSOBJ) $(OBJFILES3P)
	( cd 3rdPartyLibs/squish  ; $(MAKE) )
	$(CXX) $(CXXFLAGS) $(CXXLINK) $(PLSOBJ) $(OBJFILES3P) $(LINKLIB)$(PLSLIB) -o $@

install:
	cp $(LIBDIR)/$(PLSLIB) $(PREFIX)/lib
	ldconfig

uninstall:
	rm -f $(PREFIX)/lib/$(PLSLIB)

clean:
	rm -f $(PLSOBJ)
	rm -f $(OBJFILES3P)

distclean:
	rm -f $(LIBDIR)/$(PLSLIB)


# 3rd Party
$(OBJDIR)rijndael.o: 3rdPartyLibs/rijndael.h 3rdPartyLibs/rijndael.cpp
	$(CXX) $(CXXFLAGS3) -c 3rdPartyLibs/rijndael.cpp -o $@

3rdPartyLibs/squish/libsquish.a:
	( cd 3rdPartyLibs/squish ; $(MAKE) )

# Plasma Lib
$(OBJDIR)plDebug.o: Debug/plDebug.h Debug/plDebug.cpp
	$(CXX) $(CXXFLAGS) -c Debug/plDebug.cpp -o $@

$(OBJDIR)hsExceptions.o: Debug/hsExceptions.h Debug/hsExceptions.cpp
	$(CXX) $(CXXFLAGS) -c Debug/hsExceptions.cpp -o $@

$(OBJDIR)hsAffineParts.o: Math/hsAffineParts.h Math/hsAffineParts.cpp
	$(CXX) $(CXXFLAGS) -c Math/hsAffineParts.cpp -o $@

$(OBJDIR)hsGeometry3.o: Math/hsGeometry3.h Math/hsGeometry3.cpp
	$(CXX) $(CXXFLAGS) -c Math/hsGeometry3.cpp -o $@

$(OBJDIR)hsMatrix33.o: Math/hsMatrix33.h Math/hsMatrix33.cpp
	$(CXX) $(CXXFLAGS) -c Math/hsMatrix33.cpp -o $@

$(OBJDIR)hsMatrix44.o: Math/hsMatrix44.h Math/hsMatrix44.cpp
	$(CXX) $(CXXFLAGS) -c Math/hsMatrix44.cpp -o $@

$(OBJDIR)hsQuat.o: Math/hsQuat.h Math/hsQuat.cpp
	$(CXX) $(CXXFLAGS) -c Math/hsQuat.cpp -o $@

$(OBJDIR)plAgeInfo.o: ResManager/plAgeInfo.h ResManager/plAgeInfo.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/plAgeInfo.cpp -o $@

$(OBJDIR)plFactory.o: ResManager/plFactory.h ResManager/plFactory.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/plFactory.cpp -o $@

$(OBJDIR)plKeyCollector.o: ResManager/plKeyCollector.h ResManager/plKeyCollector.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/plKeyCollector.cpp -o $@

$(OBJDIR)plResManager.o: ResManager/plResManager.h ResManager/plResManager.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/plResManager.cpp -o $@

$(OBJDIR)pdUnifiedTypeMap.o: ResManager/pdUnifiedTypeMap.h ResManager/pdUnifiedTypeMap.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/pdUnifiedTypeMap.cpp -o $@

$(OBJDIR)plNetGameServerState.o: SDL/plNetGameServerState.h SDL/plNetGameServerState.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plNetGameServerState.cpp -o $@

$(OBJDIR)plSDL.o: SDL/plSDL.h SDL/plSDL.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plSDL.cpp -o $@

$(OBJDIR)plSDLMgr.o: SDL/plSDLMgr.h SDL/plSDLMgr.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plSDLMgr.cpp -o $@

$(OBJDIR)plStateDataRecord.o: SDL/plStateDataRecord.h SDL/plStateDataRecord.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plStateDataRecord.cpp -o $@

$(OBJDIR)plStateDescriptor.o: SDL/plStateDescriptor.h SDL/plStateDescriptor.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plStateDescriptor.cpp -o $@

$(OBJDIR)plStateVariable.o: SDL/plStateVariable.h SDL/plStateVariable.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plStateVariable.cpp -o $@

$(OBJDIR)hsElfStream.o: Stream/hsElfStream.h Stream/hsElfStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/hsElfStream.cpp -o $@

$(OBJDIR)plEncryptedStream.o: Stream/plEncryptedStream.h Stream/plEncryptedStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/plEncryptedStream.cpp -o $@

$(OBJDIR)pfPrcHelper.o: Stream/pfPrcHelper.h Stream/pfPrcHelper.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pfPrcHelper.cpp -o $@

$(OBJDIR)pfPrcParser.o: Stream/pfPrcParser.h Stream/pfPrcParser.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pfPrcParser.cpp -o $@

$(OBJDIR)hsRAMStream.o: Stream/hsRAMStream.h Stream/hsRAMStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/hsRAMStream.cpp -o $@

$(OBJDIR)hsStdioStream.o: Stream/hsStdioStream.h Stream/hsStdioStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/hsStdioStream.cpp -o $@

$(OBJDIR)hsStream.o: Stream/hsStream.h Stream/hsStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/hsStream.cpp -o $@

$(OBJDIR)hsTokenStream.o: Stream/hsTokenStream.h Stream/hsTokenStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/hsTokenStream.cpp -o $@

$(OBJDIR)hsColor.o: Sys/hsColor.h Sys/hsColor.cpp
	$(CXX) $(CXXFLAGS) -c Sys/hsColor.cpp -o $@

$(OBJDIR)hsThread.o: Sys/hsThread.h Sys/hsThread_pthread.cpp
	$(CXX) $(CXXFLAGS) -c Sys/hsThread_pthread.cpp -o $@

$(OBJDIR)plUnifiedTime.o: Sys/plUnifiedTime.h Sys/plUnifiedTime.cpp
	$(CXX) $(CXXFLAGS) -c Sys/plUnifiedTime.cpp -o $@

$(OBJDIR)plUuid.o: Sys/plUuid.h Sys/plUuid.cpp
	$(CXX) $(CXXFLAGS) -c Sys/plUuid.cpp -o $@

$(OBJDIR)hsBitVector.o: Util/hsBitVector.h Util/hsBitVector.cpp
	$(CXX) $(CXXFLAGS) -c Util/hsBitVector.cpp -o $@

$(OBJDIR)plJPEG.o: Util/plJPEG.h Util/plJPEG.cpp
	$(CXX) $(CXXFLAGS) -c Util/plJPEG.cpp -o $@

$(OBJDIR)plMD5.o: Util/plMD5.h Util/plMD5.cpp
	$(CXX) $(CXXFLAGS) -c Util/plMD5.cpp -o $@

$(OBJDIR)PlasmaVersions.o: Util/PlasmaVersions.h Util/PlasmaVersions.cpp
	$(CXX) $(CXXFLAGS) -c Util/PlasmaVersions.cpp -o $@

$(OBJDIR)plString.o: Util/plString.h Util/plString.cpp
	$(CXX) $(CXXFLAGS) -c Util/plString.cpp -o $@

$(OBJDIR)plZlib.o: Util/plZlib.h Util/plZlib.cpp
	$(CXX) $(CXXFLAGS) -c Util/plZlib.cpp -o $@

$(OBJDIR)plServerGuid.o: Vault/plServerGuid.h Vault/plServerGuid.cpp
	$(CXX) $(CXXFLAGS) -c Vault/plServerGuid.cpp -o $@

$(OBJDIR)plVaultNode.o: Vault/plVaultNode.h Vault/plVaultNode.cpp
	$(CXX) $(CXXFLAGS) -c Vault/plVaultNode.cpp -o $@

$(OBJDIR)plVaultNodeRef.o: Vault/plVaultNodeRef.h Vault/plVaultNodeRef.cpp
	$(CXX) $(CXXFLAGS) -c Vault/plVaultNodeRef.cpp -o $@

$(OBJDIR)plVaultNodeTypes.o: Vault/plVaultNodeTypes.h Vault/plVaultNodeTypes.cpp
	$(CXX) $(CXXFLAGS) -c Vault/plVaultNodeTypes.cpp -o $@

$(OBJDIR)plVaultStore.o: Vault/plVaultStore.h Vault/plVaultStore.cpp
	$(CXX) $(CXXFLAGS) -c Vault/plVaultStore.cpp -o $@

$(OBJDIR)plCreatable.o: PRP/plCreatable.h PRP/plCreatable.cpp
	$(CXX) $(CXXFLAGS) -c PRP/plCreatable.cpp -o $@

$(OBJDIR)plPageInfo.o: PRP/plPageInfo.h PRP/plPageInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/plPageInfo.cpp -o $@

$(OBJDIR)plSceneNode.o: PRP/plSceneNode.h PRP/plSceneNode.cpp
	$(CXX) $(CXXFLAGS) -c PRP/plSceneNode.cpp -o $@

$(OBJDIR)plAnimPath.o: PRP/Animation/plAnimPath.h PRP/Animation/plAnimPath.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plAnimPath.cpp -o $@

$(OBJDIR)plAnimTimeConvert.o: PRP/Animation/plAnimTimeConvert.h PRP/Animation/plAnimTimeConvert.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plAnimTimeConvert.cpp -o $@

$(OBJDIR)plATCEaseCurves.o: PRP/Animation/plATCEaseCurves.h PRP/Animation/plATCEaseCurves.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plATCEaseCurves.cpp -o $@

$(OBJDIR)plBlower.o: PRP/Animation/plBlower.h PRP/Animation/plBlower.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plBlower.cpp -o $@

$(OBJDIR)plController.o: PRP/Animation/plController.h PRP/Animation/plController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plController.cpp -o $@

$(OBJDIR)plFilterCoordInterface.o: PRP/Animation/plFilterCoordInterface.h PRP/Animation/plFilterCoordInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plFilterCoordInterface.cpp -o $@

$(OBJDIR)hsKeys.o: PRP/Animation/hsKeys.h PRP/Animation/hsKeys.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/hsKeys.cpp -o $@

$(OBJDIR)plKeyControllers.o: PRP/Animation/plKeyControllers.h PRP/Animation/plKeyControllers.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plKeyControllers.cpp -o $@

$(OBJDIR)plLeafController.o: PRP/Animation/plLeafController.h PRP/Animation/plLeafController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plLeafController.cpp -o $@

$(OBJDIR)plLineFollowMod.o: PRP/Animation/plLineFollowMod.h PRP/Animation/plLineFollowMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plLineFollowMod.cpp -o $@

$(OBJDIR)pfObjectFlocker.o: PRP/Animation/pfObjectFlocker.h PRP/Animation/pfObjectFlocker.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pfObjectFlocker.cpp -o $@

$(OBJDIR)plPosController.o: PRP/Animation/plPosController.h PRP/Animation/plPosController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plPosController.cpp -o $@

$(OBJDIR)plRotController.o: PRP/Animation/plRotController.h PRP/Animation/plRotController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plRotController.cpp -o $@

$(OBJDIR)plScaleController.o: PRP/Animation/plScaleController.h PRP/Animation/plScaleController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plScaleController.cpp -o $@

$(OBJDIR)plStereizer.o: PRP/Animation/plStereizer.h PRP/Animation/plStereizer.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plStereizer.cpp -o $@

$(OBJDIR)plTMController.o: PRP/Animation/plTMController.h PRP/Animation/plTMController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plTMController.cpp -o $@

$(OBJDIR)plViewFaceModifier.o: PRP/Animation/plViewFaceModifier.h PRP/Animation/plViewFaceModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plViewFaceModifier.cpp -o $@

$(OBJDIR)plAudible.o: PRP/Audio/plAudible.h PRP/Audio/plAudible.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plAudible.cpp -o $@

$(OBJDIR)plCrossfade.o: PRP/Audio/plCrossfade.h PRP/Audio/plCrossfade.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plCrossfade.cpp -o $@

$(OBJDIR)plDirectMusicSound.o: PRP/Audio/plDirectMusicSound.h PRP/Audio/plDirectMusicSound.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plDirectMusicSound.cpp -o $@

$(OBJDIR)plEAXEffects.o: PRP/Audio/plEAXEffects.h PRP/Audio/plEAXEffects.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plEAXEffects.cpp -o $@

$(OBJDIR)plEAXListenerMod.o: PRP/Audio/plEAXListenerMod.h PRP/Audio/plEAXListenerMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plEAXListenerMod.cpp -o $@

$(OBJDIR)plSound.o: PRP/Audio/plSound.h PRP/Audio/plSound.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plSound.cpp -o $@

$(OBJDIR)plSoundBuffer.o: PRP/Audio/plSoundBuffer.h PRP/Audio/plSoundBuffer.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plSoundBuffer.cpp -o $@

$(OBJDIR)plWin32Sound.o: PRP/Audio/plWin32Sound.h PRP/Audio/plWin32Sound.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plWin32Sound.cpp -o $@

$(OBJDIR)plWin32StaticSound.o: PRP/Audio/plWin32StaticSound.h PRP/Audio/plWin32StaticSound.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plWin32StaticSound.cpp -o $@

$(OBJDIR)plAGAnim.o: PRP/Avatar/plAGAnim.h PRP/Avatar/plAGAnim.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAGAnim.cpp -o $@

$(OBJDIR)plAGApplicator.o: PRP/Avatar/plAGApplicator.h PRP/Avatar/plAGApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAGApplicator.cpp -o $@

$(OBJDIR)plAGChannel.o: PRP/Avatar/plAGChannel.h PRP/Avatar/plAGChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAGChannel.cpp -o $@

$(OBJDIR)plAGMasterMod.o: PRP/Avatar/plAGMasterMod.h PRP/Avatar/plAGMasterMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAGMasterMod.cpp -o $@

$(OBJDIR)plAGModifier.o: PRP/Avatar/plAGModifier.h PRP/Avatar/plAGModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAGModifier.cpp -o $@

$(OBJDIR)plAnimStage.o: PRP/Avatar/plAnimStage.h PRP/Avatar/plAnimStage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAnimStage.cpp -o $@

$(OBJDIR)plArmatureBrain.o: PRP/Avatar/plArmatureBrain.h PRP/Avatar/plArmatureBrain.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plArmatureBrain.cpp -o $@

$(OBJDIR)plArmatureEffects.o: PRP/Avatar/plArmatureEffects.h PRP/Avatar/plArmatureEffects.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plArmatureEffects.cpp -o $@

$(OBJDIR)plArmatureMod.o: PRP/Avatar/plArmatureMod.h PRP/Avatar/plArmatureMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plArmatureMod.cpp -o $@

$(OBJDIR)plATCAnim.o: PRP/Avatar/plATCAnim.h PRP/Avatar/plATCAnim.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plATCAnim.cpp -o $@

$(OBJDIR)plAvatarClothing.o: PRP/Avatar/plAvatarClothing.h PRP/Avatar/plAvatarClothing.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAvatarClothing.cpp -o $@

$(OBJDIR)plClothingItem.o: PRP/Avatar/plClothingItem.h PRP/Avatar/plClothingItem.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plClothingItem.cpp -o $@

$(OBJDIR)plElevatorModifier.o: PRP/Avatar/plElevatorModifier.h PRP/Avatar/plElevatorModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plElevatorModifier.cpp -o $@

$(OBJDIR)plLadderModifier.o: PRP/Avatar/plLadderModifier.h PRP/Avatar/plLadderModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plLadderModifier.cpp -o $@

$(OBJDIR)plMatrixChannel.o: PRP/Avatar/plMatrixChannel.h PRP/Avatar/plMatrixChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plMatrixChannel.cpp -o $@

$(OBJDIR)plMultistageBehMod.o: PRP/Avatar/plMultistageBehMod.h PRP/Avatar/plMultistageBehMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plMultistageBehMod.cpp -o $@

$(OBJDIR)plNPCSpawnMod.o: PRP/Avatar/plNPCSpawnMod.h PRP/Avatar/plNPCSpawnMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plNPCSpawnMod.cpp -o $@

$(OBJDIR)plPointChannel.o: PRP/Avatar/plPointChannel.h PRP/Avatar/plPointChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plPointChannel.cpp -o $@

$(OBJDIR)plQuatChannel.o: PRP/Avatar/plQuatChannel.h PRP/Avatar/plQuatChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plQuatChannel.cpp -o $@

$(OBJDIR)plScalarChannel.o: PRP/Avatar/plScalarChannel.h PRP/Avatar/plScalarChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plScalarChannel.cpp -o $@

$(OBJDIR)plSeekPointMod.o: PRP/Avatar/plSeekPointMod.h PRP/Avatar/plSeekPointMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plSeekPointMod.cpp -o $@

$(OBJDIR)plSittingModifier.o: PRP/Avatar/plSittingModifier.h PRP/Avatar/plSittingModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plSittingModifier.cpp -o $@

$(OBJDIR)plCameraBrain.o: PRP/Camera/plCameraBrain.h PRP/Camera/plCameraBrain.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Camera/plCameraBrain.cpp -o $@

$(OBJDIR)plCameraModifier.o: PRP/Camera/plCameraModifier.h PRP/Camera/plCameraModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Camera/plCameraModifier.cpp -o $@

$(OBJDIR)plActivatorConditionalObject.o: PRP/ConditionalObject/plActivatorConditionalObject.h PRP/ConditionalObject/plActivatorConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plActivatorConditionalObject.cpp -o $@

$(OBJDIR)plAnimationEventConditionalObject.o: PRP/ConditionalObject/plAnimationEventConditionalObject.h PRP/ConditionalObject/plAnimationEventConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plAnimationEventConditionalObject.cpp -o $@

$(OBJDIR)plBooleanConditionalObject.o: PRP/ConditionalObject/plBooleanConditionalObject.h PRP/ConditionalObject/plBooleanConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plBooleanConditionalObject.cpp -o $@

$(OBJDIR)plConditionalObject.o: PRP/ConditionalObject/plConditionalObject.h PRP/ConditionalObject/plConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plConditionalObject.cpp -o $@

$(OBJDIR)plControlEventConditionalObject.o: PRP/ConditionalObject/plControlEventConditionalObject.h PRP/ConditionalObject/plControlEventConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plControlEventConditionalObject.cpp -o $@

$(OBJDIR)plDetectConditionalObjects.o: PRP/ConditionalObject/plDetectConditionalObjects.h PRP/ConditionalObject/plDetectConditionalObjects.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plDetectConditionalObjects.cpp -o $@

$(OBJDIR)plFacingConditionalObject.o: PRP/ConditionalObject/plFacingConditionalObject.h PRP/ConditionalObject/plFacingConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plFacingConditionalObject.cpp -o $@

$(OBJDIR)plKeyPressConditionalObject.o: PRP/ConditionalObject/plKeyPressConditionalObject.h PRP/ConditionalObject/plKeyPressConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plKeyPressConditionalObject.cpp -o $@

$(OBJDIR)plVolumeSensorConditionalObject.o: PRP/ConditionalObject/plVolumeSensorConditionalObject.h PRP/ConditionalObject/plVolumeSensorConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plVolumeSensorConditionalObject.cpp -o $@

$(OBJDIR)plCluster.o: PRP/Geometry/plCluster.h PRP/Geometry/plCluster.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plCluster.cpp -o $@

$(OBJDIR)plClusterGroup.o: PRP/Geometry/plClusterGroup.h PRP/Geometry/plClusterGroup.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plClusterGroup.cpp -o $@

$(OBJDIR)plCullPoly.o: PRP/Geometry/plCullPoly.h PRP/Geometry/plCullPoly.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plCullPoly.cpp -o $@

$(OBJDIR)plDrawableSpans.o: PRP/Geometry/plDrawableSpans.h PRP/Geometry/plDrawableSpans.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plDrawableSpans.cpp -o $@

$(OBJDIR)plGBufferGroup.o: PRP/Geometry/plGBufferGroup.h PRP/Geometry/plGBufferGroup.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plGBufferGroup.cpp -o $@

$(OBJDIR)hsGDeviceRef.o: PRP/Geometry/hsGDeviceRef.h PRP/Geometry/hsGDeviceRef.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/hsGDeviceRef.cpp -o $@

$(OBJDIR)plGeometrySpan.o: PRP/Geometry/plGeometrySpan.h PRP/Geometry/plGeometrySpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plGeometrySpan.cpp -o $@

$(OBJDIR)plIcicle.o: PRP/Geometry/plIcicle.h PRP/Geometry/plIcicle.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plIcicle.cpp -o $@

$(OBJDIR)plMorphArray.o: PRP/Geometry/plMorphArray.h PRP/Geometry/plMorphArray.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plMorphArray.cpp -o $@

$(OBJDIR)plMorphDataSet.o: PRP/Geometry/plMorphDataSet.h PRP/Geometry/plMorphDataSet.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plMorphDataSet.cpp -o $@

$(OBJDIR)plMorphDelta.o: PRP/Geometry/plMorphDelta.h PRP/Geometry/plMorphDelta.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plMorphDelta.cpp -o $@

$(OBJDIR)plOccluder.o: PRP/Geometry/plOccluder.h PRP/Geometry/plOccluder.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plOccluder.cpp -o $@

$(OBJDIR)plSharedMesh.o: PRP/Geometry/plSharedMesh.h PRP/Geometry/plSharedMesh.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plSharedMesh.cpp -o $@

$(OBJDIR)plSpaceTree.o: PRP/Geometry/plSpaceTree.h PRP/Geometry/plSpaceTree.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plSpaceTree.cpp -o $@

$(OBJDIR)plSpan.o: PRP/Geometry/plSpan.h PRP/Geometry/plSpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plSpan.cpp -o $@

$(OBJDIR)plSpanInstance.o: PRP/Geometry/plSpanInstance.h PRP/Geometry/plSpanInstance.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plSpanInstance.cpp -o $@

$(OBJDIR)plSpanTemplate.o: PRP/Geometry/plSpanTemplate.h PRP/Geometry/plSpanTemplate.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plSpanTemplate.cpp -o $@

$(OBJDIR)plVertCoder.o: PRP/Geometry/plVertCoder.h PRP/Geometry/plVertCoder.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plVertCoder.cpp -o $@

$(OBJDIR)plVertexSpan.o: PRP/Geometry/plVertexSpan.h PRP/Geometry/plVertexSpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plVertexSpan.cpp -o $@

$(OBJDIR)pfGUIButtonMod.o: PRP/GUI/pfGUIButtonMod.h PRP/GUI/pfGUIButtonMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIButtonMod.cpp -o $@

$(OBJDIR)pfGUICheckBoxCtrl.o: PRP/GUI/pfGUICheckBoxCtrl.h PRP/GUI/pfGUICheckBoxCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUICheckBoxCtrl.cpp -o $@

$(OBJDIR)pfGUIClickMapCtrl.o: PRP/GUI/pfGUIClickMapCtrl.h PRP/GUI/pfGUIClickMapCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIClickMapCtrl.cpp -o $@

$(OBJDIR)pfGUIControlHandlers.o: PRP/GUI/pfGUIControlHandlers.h PRP/GUI/pfGUIControlHandlers.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIControlHandlers.cpp -o $@

$(OBJDIR)pfGUIControlMod.o: PRP/GUI/pfGUIControlMod.h PRP/GUI/pfGUIControlMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIControlMod.cpp -o $@

$(OBJDIR)pfGUIDialogMod.o: PRP/GUI/pfGUIDialogMod.h PRP/GUI/pfGUIDialogMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIDialogMod.cpp -o $@

$(OBJDIR)pfGUIDragBarCtrl.o: PRP/GUI/pfGUIDragBarCtrl.h PRP/GUI/pfGUIDragBarCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIDragBarCtrl.cpp -o $@

$(OBJDIR)pfGUIDraggableMod.o: PRP/GUI/pfGUIDraggableMod.h PRP/GUI/pfGUIDraggableMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIDraggableMod.cpp -o $@

$(OBJDIR)pfGUIDynDisplayCtrl.o: PRP/GUI/pfGUIDynDisplayCtrl.h PRP/GUI/pfGUIDynDisplayCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIDynDisplayCtrl.cpp -o $@

$(OBJDIR)pfGUIEditBoxMod.o: PRP/GUI/pfGUIEditBoxMod.h PRP/GUI/pfGUIEditBoxMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIEditBoxMod.cpp -o $@

$(OBJDIR)pfGUIKnobCtrl.o: PRP/GUI/pfGUIKnobCtrl.h PRP/GUI/pfGUIKnobCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIKnobCtrl.cpp -o $@

$(OBJDIR)pfGUIListBoxMod.o: PRP/GUI/pfGUIListBoxMod.h PRP/GUI/pfGUIListBoxMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIListBoxMod.cpp -o $@

$(OBJDIR)pfGUIMultiLineEditCtrl.o: PRP/GUI/pfGUIMultiLineEditCtrl.h PRP/GUI/pfGUIMultiLineEditCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIMultiLineEditCtrl.cpp -o $@

$(OBJDIR)pfGUIPopUpMenu.o: PRP/GUI/pfGUIPopUpMenu.h PRP/GUI/pfGUIPopUpMenu.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIPopUpMenu.cpp -o $@

$(OBJDIR)pfGUIProgressCtrl.o: PRP/GUI/pfGUIProgressCtrl.h PRP/GUI/pfGUIProgressCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIProgressCtrl.cpp -o $@

$(OBJDIR)pfGUIRadioGroupCtrl.o: PRP/GUI/pfGUIRadioGroupCtrl.h PRP/GUI/pfGUIRadioGroupCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIRadioGroupCtrl.cpp -o $@

$(OBJDIR)pfGUISkin.o: PRP/GUI/pfGUISkin.h PRP/GUI/pfGUISkin.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUISkin.cpp -o $@

$(OBJDIR)pfGUITextBoxMod.o: PRP/GUI/pfGUITextBoxMod.h PRP/GUI/pfGUITextBoxMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUITextBoxMod.cpp -o $@

$(OBJDIR)pfGUIUpDownPairMod.o: PRP/GUI/pfGUIUpDownPairMod.h PRP/GUI/pfGUIUpDownPairMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIUpDownPairMod.cpp -o $@

$(OBJDIR)pfGUIValueCtrl.o: PRP/GUI/pfGUIValueCtrl.h PRP/GUI/pfGUIValueCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIValueCtrl.cpp -o $@

$(OBJDIR)plImageLibMod.o: PRP/GUI/plImageLibMod.h PRP/GUI/plImageLibMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/plImageLibMod.cpp -o $@

$(OBJDIR)hsKeyedObject.o: PRP/KeyedObject/hsKeyedObject.h PRP/KeyedObject/hsKeyedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/hsKeyedObject.cpp -o $@

$(OBJDIR)plKey.o: PRP/KeyedObject/plKey.h PRP/KeyedObject/plKey.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/plKey.cpp -o $@

$(OBJDIR)plLoadMask.o: PRP/KeyedObject/plLoadMask.h PRP/KeyedObject/plLoadMask.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/plLoadMask.cpp -o $@

$(OBJDIR)plLocation.o: PRP/KeyedObject/plLocation.h PRP/KeyedObject/plLocation.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/plLocation.cpp -o $@

$(OBJDIR)plReceiver.o: PRP/KeyedObject/plReceiver.h PRP/KeyedObject/plReceiver.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/plReceiver.cpp -o $@

$(OBJDIR)plUoid.o: PRP/KeyedObject/plUoid.h PRP/KeyedObject/plUoid.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/plUoid.cpp -o $@

$(OBJDIR)plDirectionalLightInfo.o: PRP/Light/plDirectionalLightInfo.h PRP/Light/plDirectionalLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/plDirectionalLightInfo.cpp -o $@

$(OBJDIR)plLightInfo.o: PRP/Light/plLightInfo.h PRP/Light/plLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/plLightInfo.cpp -o $@

$(OBJDIR)plOmniLightInfo.o: PRP/Light/plOmniLightInfo.h PRP/Light/plOmniLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/plOmniLightInfo.cpp -o $@

$(OBJDIR)plShadowCaster.o: PRP/Light/plShadowCaster.h PRP/Light/plShadowCaster.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/plShadowCaster.cpp -o $@

$(OBJDIR)plShadowMaster.o: PRP/Light/plShadowMaster.h PRP/Light/plShadowMaster.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/plShadowMaster.cpp -o $@

$(OBJDIR)plAnimCmdMsg.o: PRP/Message/plAnimCmdMsg.h PRP/Message/plAnimCmdMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plAnimCmdMsg.cpp -o $@

$(OBJDIR)plArmatureEffectMsg.o: PRP/Message/plArmatureEffectMsg.h PRP/Message/plArmatureEffectMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plArmatureEffectMsg.cpp -o $@

$(OBJDIR)plAvatarInputStateMsg.o: PRP/Message/plAvatarInputStateMsg.h PRP/Message/plAvatarInputStateMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plAvatarInputStateMsg.cpp -o $@

$(OBJDIR)plCameraMsg.o: PRP/Message/plCameraMsg.h PRP/Message/plCameraMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plCameraMsg.cpp -o $@

$(OBJDIR)plClimbMsg.o: PRP/Message/plClimbMsg.h PRP/Message/plClimbMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plClimbMsg.cpp -o $@

$(OBJDIR)plEnableMsg.o: PRP/Message/plEnableMsg.h PRP/Message/plEnableMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plEnableMsg.cpp -o $@

$(OBJDIR)plEventCallbackMsg.o: PRP/Message/plEventCallbackMsg.h PRP/Message/plEventCallbackMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plEventCallbackMsg.cpp -o $@

$(OBJDIR)proEventData.o: PRP/Message/proEventData.h PRP/Message/proEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/proEventData.cpp -o $@

$(OBJDIR)plExcludeRegionMsg.o: PRP/Message/plExcludeRegionMsg.h PRP/Message/plExcludeRegionMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plExcludeRegionMsg.cpp -o $@

$(OBJDIR)plLinkToAgeMsg.o: PRP/Message/plLinkToAgeMsg.h PRP/Message/plLinkToAgeMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plLinkToAgeMsg.cpp -o $@

$(OBJDIR)plLoadCloneMsg.o: PRP/Message/plLoadCloneMsg.h PRP/Message/plLoadCloneMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plLoadCloneMsg.cpp -o $@

$(OBJDIR)plMessage.o: PRP/Message/plMessage.h PRP/Message/plMessage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plMessage.cpp -o $@

$(OBJDIR)plMessageWithCallbacks.o: PRP/Message/plMessageWithCallbacks.h PRP/Message/plMessageWithCallbacks.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plMessageWithCallbacks.cpp -o $@

$(OBJDIR)plMsgForwarder.o: PRP/Message/plMsgForwarder.h PRP/Message/plMsgForwarder.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plMsgForwarder.cpp -o $@

$(OBJDIR)plNotifyMsg.o: PRP/Message/plNotifyMsg.h PRP/Message/plNotifyMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plNotifyMsg.cpp -o $@

$(OBJDIR)plOneShotCallbacks.o: PRP/Message/plOneShotCallbacks.h PRP/Message/plOneShotCallbacks.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plOneShotCallbacks.cpp -o $@

$(OBJDIR)plPseudoLinkEffectMsg.o: PRP/Message/plPseudoLinkEffectMsg.h PRP/Message/plPseudoLinkEffectMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plPseudoLinkEffectMsg.cpp -o $@

$(OBJDIR)plResponderMsg.o: PRP/Message/plResponderMsg.h PRP/Message/plResponderMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plResponderMsg.cpp -o $@

$(OBJDIR)plServerReplyMsg.o: PRP/Message/plServerReplyMsg.h PRP/Message/plServerReplyMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plServerReplyMsg.cpp -o $@

$(OBJDIR)plSimulationMsg.o: PRP/Message/plSimulationMsg.h PRP/Message/plSimulationMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plSimulationMsg.cpp -o $@

$(OBJDIR)plSoundMsg.o: PRP/Message/plSoundMsg.h PRP/Message/plSoundMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plSoundMsg.cpp -o $@

$(OBJDIR)plSwimMsg.o: PRP/Message/plSwimMsg.h PRP/Message/plSwimMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plSwimMsg.cpp -o $@

$(OBJDIR)plTimerCallbackMsg.o: PRP/Message/plTimerCallbackMsg.h PRP/Message/plTimerCallbackMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plTimerCallbackMsg.cpp -o $@

$(OBJDIR)plTransitionMsg.o: PRP/Message/plTransitionMsg.h PRP/Message/plTransitionMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plTransitionMsg.cpp -o $@

$(OBJDIR)plAgeLinkInfo.o: PRP/Misc/plAgeLinkInfo.h PRP/Misc/plAgeLinkInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Misc/plAgeLinkInfo.cpp -o $@

$(OBJDIR)plFogEnvironment.o: PRP/Misc/plFogEnvironment.h PRP/Misc/plFogEnvironment.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Misc/plFogEnvironment.cpp -o $@

$(OBJDIR)plSpawnPointInfo.o: PRP/Misc/plSpawnPointInfo.h PRP/Misc/plSpawnPointInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Misc/plSpawnPointInfo.cpp -o $@

$(OBJDIR)plAliasModifier.o: PRP/Modifier/plAliasModifier.h PRP/Modifier/plAliasModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plAliasModifier.cpp -o $@

$(OBJDIR)plAnimEventModifier.o: PRP/Modifier/plAnimEventModifier.h PRP/Modifier/plAnimEventModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plAnimEventModifier.cpp -o $@

$(OBJDIR)plAxisAnimModifier.o: PRP/Modifier/plAxisAnimModifier.h PRP/Modifier/plAxisAnimModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plAxisAnimModifier.cpp -o $@

$(OBJDIR)plExcludeRegionModifier.o: PRP/Modifier/plExcludeRegionModifier.h PRP/Modifier/plExcludeRegionModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plExcludeRegionModifier.cpp -o $@

$(OBJDIR)plInterfaceInfoModifier.o: PRP/Modifier/plInterfaceInfoModifier.h PRP/Modifier/plInterfaceInfoModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plInterfaceInfoModifier.cpp -o $@

$(OBJDIR)plLogicModBase.o: PRP/Modifier/plLogicModBase.h PRP/Modifier/plLogicModBase.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plLogicModBase.cpp -o $@

$(OBJDIR)plLogicModifier.o: PRP/Modifier/plLogicModifier.h PRP/Modifier/plLogicModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plLogicModifier.cpp -o $@

$(OBJDIR)plMaintainersMarkerModifier.o: PRP/Modifier/plMaintainersMarkerModifier.h PRP/Modifier/plMaintainersMarkerModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plMaintainersMarkerModifier.cpp -o $@

$(OBJDIR)plModifier.o: PRP/Modifier/plModifier.h PRP/Modifier/plModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plModifier.cpp -o $@

$(OBJDIR)plNodeRegionModifier.o: PRP/Modifier/plNodeRegionModifier.h PRP/Modifier/plNodeRegionModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plNodeRegionModifier.cpp -o $@

$(OBJDIR)plOneShotMod.o: PRP/Modifier/plOneShotMod.h PRP/Modifier/plOneShotMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plOneShotMod.cpp -o $@

$(OBJDIR)plPostEffectMod.o: PRP/Modifier/plPostEffectMod.h PRP/Modifier/plPostEffectMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plPostEffectMod.cpp -o $@

$(OBJDIR)plPythonFileMod.o: PRP/Modifier/plPythonFileMod.h PRP/Modifier/plPythonFileMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plPythonFileMod.cpp -o $@

$(OBJDIR)plPythonMod.o: PRP/Modifier/plPythonMod.h PRP/Modifier/plPythonMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plPythonMod.cpp -o $@

$(OBJDIR)plRandomCommandMod.o: PRP/Modifier/plRandomCommandMod.h PRP/Modifier/plRandomCommandMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plRandomCommandMod.cpp -o $@

$(OBJDIR)plRandomSoundMod.o: PRP/Modifier/plRandomSoundMod.h PRP/Modifier/plRandomSoundMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plRandomSoundMod.cpp -o $@

$(OBJDIR)plResponderModifier.o: PRP/Modifier/plResponderModifier.h PRP/Modifier/plResponderModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plResponderModifier.cpp -o $@

$(OBJDIR)plSpawnModifier.o: PRP/Modifier/plSpawnModifier.h PRP/Modifier/plSpawnModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plSpawnModifier.cpp -o $@

$(OBJDIR)plClientGuid.o: PRP/NetMessage/plClientGuid.h PRP/NetMessage/plClientGuid.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plClientGuid.cpp -o $@

$(OBJDIR)plNetGroupId.o: PRP/NetMessage/plNetGroupId.h PRP/NetMessage/plNetGroupId.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetGroupId.cpp -o $@

$(OBJDIR)plNetMessage.o: PRP/NetMessage/plNetMessage.h PRP/NetMessage/plNetMessage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMessage.cpp -o $@

$(OBJDIR)plNetMsgGameMessage.o: PRP/NetMessage/plNetMsgGameMessage.h PRP/NetMessage/plNetMsgGameMessage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgGameMessage.cpp -o $@

$(OBJDIR)plNetMsgGroupOwner.o: PRP/NetMessage/plNetMsgGroupOwner.h PRP/NetMessage/plNetMsgGroupOwner.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgGroupOwner.cpp -o $@

$(OBJDIR)plNetMsgInitialAgeStateSent.o: PRP/NetMessage/plNetMsgInitialAgeStateSent.h PRP/NetMessage/plNetMsgInitialAgeStateSent.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgInitialAgeStateSent.cpp -o $@

$(OBJDIR)plNetMsgLoadClone.o: PRP/NetMessage/plNetMsgLoadClone.h PRP/NetMessage/plNetMsgLoadClone.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgLoadClone.cpp -o $@

$(OBJDIR)plNetMsgMembersList.o: PRP/NetMessage/plNetMsgMembersList.h PRP/NetMessage/plNetMsgMembersList.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgMembersList.cpp -o $@

$(OBJDIR)plNetMsgObject.o: PRP/NetMessage/plNetMsgObject.h PRP/NetMessage/plNetMsgObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgObject.cpp -o $@

$(OBJDIR)plNetMsgPlayerPage.o: PRP/NetMessage/plNetMsgPlayerPage.h PRP/NetMessage/plNetMsgPlayerPage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgPlayerPage.cpp -o $@

$(OBJDIR)plNetMsgRelevanceRegions.o: PRP/NetMessage/plNetMsgRelevanceRegions.h PRP/NetMessage/plNetMsgRelevanceRegions.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgRelevanceRegions.cpp -o $@

$(OBJDIR)plNetMsgRoomsList.o: PRP/NetMessage/plNetMsgRoomsList.h PRP/NetMessage/plNetMsgRoomsList.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgRoomsList.cpp -o $@

$(OBJDIR)plNetMsgSDLState.o: PRP/NetMessage/plNetMsgSDLState.h PRP/NetMessage/plNetMsgSDLState.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgSDLState.cpp -o $@

$(OBJDIR)plNetMsgSharedState.o: PRP/NetMessage/plNetMsgSharedState.h PRP/NetMessage/plNetMsgSharedState.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgSharedState.cpp -o $@

$(OBJDIR)plNetMsgStream.o: PRP/NetMessage/plNetMsgStream.h PRP/NetMessage/plNetMsgStream.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgStream.cpp -o $@

$(OBJDIR)plNetMsgStreamedObject.o: PRP/NetMessage/plNetMsgStreamedObject.h PRP/NetMessage/plNetMsgStreamedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgStreamedObject.cpp -o $@

$(OBJDIR)plNetSharedState.o: PRP/NetMessage/plNetSharedState.h PRP/NetMessage/plNetSharedState.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetSharedState.cpp -o $@

$(OBJDIR)plAudioInterface.o: PRP/Object/plAudioInterface.h PRP/Object/plAudioInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plAudioInterface.cpp -o $@

$(OBJDIR)plCoordinateInterface.o: PRP/Object/plCoordinateInterface.h PRP/Object/plCoordinateInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plCoordinateInterface.cpp -o $@

$(OBJDIR)plDrawInterface.o: PRP/Object/plDrawInterface.h PRP/Object/plDrawInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plDrawInterface.cpp -o $@

$(OBJDIR)plObjInterface.o: PRP/Object/plObjInterface.h PRP/Object/plObjInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plObjInterface.cpp -o $@

$(OBJDIR)plSceneObject.o: PRP/Object/plSceneObject.h PRP/Object/plSceneObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plSceneObject.cpp -o $@

$(OBJDIR)plSimulationInterface.o: PRP/Object/plSimulationInterface.h PRP/Object/plSimulationInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plSimulationInterface.cpp -o $@

$(OBJDIR)plSynchedObject.o: PRP/Object/plSynchedObject.h PRP/Object/plSynchedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plSynchedObject.cpp -o $@

$(OBJDIR)plBoundInterface.o: PRP/Particle/plBoundInterface.h PRP/Particle/plBoundInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Particle/plBoundInterface.cpp -o $@

$(OBJDIR)plParticleApplicator.o: PRP/Particle/plParticleApplicator.h PRP/Particle/plParticleApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Particle/plParticleApplicator.cpp -o $@

$(OBJDIR)plParticleEffect.o: PRP/Particle/plParticleEffect.h PRP/Particle/plParticleEffect.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Particle/plParticleEffect.cpp -o $@

$(OBJDIR)plParticleEmitter.o: PRP/Particle/plParticleEmitter.h PRP/Particle/plParticleEmitter.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Particle/plParticleEmitter.cpp -o $@

$(OBJDIR)plParticleGenerator.o: PRP/Particle/plParticleGenerator.h PRP/Particle/plParticleGenerator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Particle/plParticleGenerator.cpp -o $@

$(OBJDIR)plParticleSystem.o: PRP/Particle/plParticleSystem.h PRP/Particle/plParticleSystem.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Particle/plParticleSystem.cpp -o $@

$(OBJDIR)plCollisionDetector.o: PRP/Physics/plCollisionDetector.h PRP/Physics/plCollisionDetector.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plCollisionDetector.cpp -o $@

$(OBJDIR)plDetectorModifier.o: PRP/Physics/plDetectorModifier.h PRP/Physics/plDetectorModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plDetectorModifier.cpp -o $@

$(OBJDIR)plGenericPhysical.o: PRP/Physics/plGenericPhysical.h PRP/Physics/plGenericPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plGenericPhysical.cpp -o $@

$(OBJDIR)plObjectInVolumeDetector.o: PRP/Physics/plObjectInVolumeDetector.h PRP/Physics/plObjectInVolumeDetector.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plObjectInVolumeDetector.cpp -o $@

$(OBJDIR)plPhysical.o: PRP/Physics/plPhysical.h PRP/Physics/plPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plPhysical.cpp -o $@

$(OBJDIR)plPhysicalSndGroup.o: PRP/Physics/plPhysicalSndGroup.h PRP/Physics/plPhysicalSndGroup.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plPhysicalSndGroup.cpp -o $@

$(OBJDIR)plVehicleModifier.o: PRP/Physics/plVehicleModifier.h PRP/Physics/plVehicleModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plVehicleModifier.cpp -o $@

$(OBJDIR)hsBounds.o: PRP/Region/hsBounds.h PRP/Region/hsBounds.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/hsBounds.cpp -o $@

$(OBJDIR)plConvexVolume.o: PRP/Region/plConvexVolume.h PRP/Region/plConvexVolume.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plConvexVolume.cpp -o $@

$(OBJDIR)plHardRegion.o: PRP/Region/plHardRegion.h PRP/Region/plHardRegion.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plHardRegion.cpp -o $@

$(OBJDIR)plHardRegionPlanes.o: PRP/Region/plHardRegionPlanes.h PRP/Region/plHardRegionPlanes.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plHardRegionPlanes.cpp -o $@

$(OBJDIR)plRegionBase.o: PRP/Region/plRegionBase.h PRP/Region/plRegionBase.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plRegionBase.cpp -o $@

$(OBJDIR)plRelevanceRegion.o: PRP/Region/plRelevanceRegion.h PRP/Region/plRelevanceRegion.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plRelevanceRegion.cpp -o $@

$(OBJDIR)plSimpleRegionSensor.o: PRP/Region/plSimpleRegionSensor.h PRP/Region/plSimpleRegionSensor.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plSimpleRegionSensor.cpp -o $@

$(OBJDIR)plSoftVolume.o: PRP/Region/plSoftVolume.h PRP/Region/plSoftVolume.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plSoftVolume.cpp -o $@

$(OBJDIR)plSwimRegion.o: PRP/Region/plSwimRegion.h PRP/Region/plSwimRegion.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plSwimRegion.cpp -o $@

$(OBJDIR)plVisRegion.o: PRP/Region/plVisRegion.h PRP/Region/plVisRegion.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plVisRegion.cpp -o $@

$(OBJDIR)plVolumeIsect.o: PRP/Region/plVolumeIsect.h PRP/Region/plVolumeIsect.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plVolumeIsect.cpp -o $@

$(OBJDIR)plBitmap.o: PRP/Surface/plBitmap.h PRP/Surface/plBitmap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plBitmap.cpp -o $@

$(OBJDIR)plCubicEnvironmap.o: PRP/Surface/plCubicEnvironmap.h PRP/Surface/plCubicEnvironmap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plCubicEnvironmap.cpp -o $@

$(OBJDIR)plDistOpacityMod.o: PRP/Surface/plDistOpacityMod.h PRP/Surface/plDistOpacityMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plDistOpacityMod.cpp -o $@

$(OBJDIR)plDynaDecalMgr.o: PRP/Surface/plDynaDecalMgr.h PRP/Surface/plDynaDecalMgr.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plDynaDecalMgr.cpp -o $@

$(OBJDIR)plDynamicEnvMap.o: PRP/Surface/plDynamicEnvMap.h PRP/Surface/plDynamicEnvMap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plDynamicEnvMap.cpp -o $@

$(OBJDIR)plDynamicTextMap.o: PRP/Surface/plDynamicTextMap.h PRP/Surface/plDynamicTextMap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plDynamicTextMap.cpp -o $@

$(OBJDIR)plDynaRippleMgr.o: PRP/Surface/plDynaRippleMgr.h PRP/Surface/plDynaRippleMgr.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plDynaRippleMgr.cpp -o $@

$(OBJDIR)plFadeOpacityMod.o: PRP/Surface/plFadeOpacityMod.h PRP/Surface/plFadeOpacityMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plFadeOpacityMod.cpp -o $@

$(OBJDIR)plFixedWaterState6.o: PRP/Surface/plFixedWaterState6.h PRP/Surface/plFixedWaterState6.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plFixedWaterState6.cpp -o $@

$(OBJDIR)plFixedWaterState7.o: PRP/Surface/plFixedWaterState7.h PRP/Surface/plFixedWaterState7.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plFixedWaterState7.cpp -o $@

$(OBJDIR)plFont.o: PRP/Surface/plFont.h PRP/Surface/plFont.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plFont.cpp -o $@

$(OBJDIR)hsGMaterial.o: PRP/Surface/hsGMaterial.h PRP/Surface/hsGMaterial.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/hsGMaterial.cpp -o $@

$(OBJDIR)hsGMatState.o: PRP/Surface/hsGMatState.h PRP/Surface/hsGMatState.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/hsGMatState.cpp -o $@

$(OBJDIR)plGrassShaderMod.o: PRP/Surface/plGrassShaderMod.h PRP/Surface/plGrassShaderMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plGrassShaderMod.cpp -o $@

$(OBJDIR)plLayer.o: PRP/Surface/plLayer.h PRP/Surface/plLayer.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plLayer.cpp -o $@

$(OBJDIR)plLayerAnimation.o: PRP/Surface/plLayerAnimation.h PRP/Surface/plLayerAnimation.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plLayerAnimation.cpp -o $@

$(OBJDIR)plLayerInterface.o: PRP/Surface/plLayerInterface.h PRP/Surface/plLayerInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plLayerInterface.cpp -o $@

$(OBJDIR)plLayerMovie.o: PRP/Surface/plLayerMovie.h PRP/Surface/plLayerMovie.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plLayerMovie.cpp -o $@

$(OBJDIR)plMipmap.o: PRP/Surface/plMipmap.h PRP/Surface/plMipmap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plMipmap.cpp -o $@

$(OBJDIR)plPrintShape.o: PRP/Surface/plPrintShape.h PRP/Surface/plPrintShape.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plPrintShape.cpp -o $@

$(OBJDIR)plRenderTarget.o: PRP/Surface/plRenderTarget.h PRP/Surface/plRenderTarget.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plRenderTarget.cpp -o $@

$(OBJDIR)plShader.o: PRP/Surface/plShader.h PRP/Surface/plShader.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plShader.cpp -o $@

$(OBJDIR)plWaveSet6.o: PRP/Surface/plWaveSet6.h PRP/Surface/plWaveSet6.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plWaveSet6.cpp -o $@

$(OBJDIR)plWaveSet7.o: PRP/Surface/plWaveSet7.h PRP/Surface/plWaveSet7.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plWaveSet7.cpp -o $@

$(OBJDIR)plWaveSetBase.o: PRP/Surface/plWaveSetBase.h PRP/Surface/plWaveSetBase.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plWaveSetBase.cpp -o $@
