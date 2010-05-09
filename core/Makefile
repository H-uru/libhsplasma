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
	$(OBJDIR)plDDSurface.o \
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
	$(OBJDIR)plAvBrainCoop.o \
	$(OBJDIR)plAvBrainGeneric.o \
	$(OBJDIR)plAvTask.o \
	$(OBJDIR)plClothingItem.o \
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
	$(OBJDIR)plMorphSequence.o \
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
	$(OBJDIR)pfGUIControlHandlers.o \
	$(OBJDIR)pfGUIControlMod.o \
	$(OBJDIR)pfGUIDialogMod.o \
	$(OBJDIR)pfGUIDynDisplayCtrl.o \
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
	$(OBJDIR)plUoid.o \
	$(OBJDIR)plDirectionalLightInfo.o \
	$(OBJDIR)plLightInfo.o \
	$(OBJDIR)plOmniLightInfo.o \
	$(OBJDIR)plShadowCaster.o \
	$(OBJDIR)plShadowMaster.o \
	$(OBJDIR)pfKIMsg.o \
	$(OBJDIR)plAnimCmdMsg.o \
	$(OBJDIR)plArmatureEffectMsg.o \
	$(OBJDIR)plAvatarInputStateMsg.o \
	$(OBJDIR)plAvatarMsg.o \
	$(OBJDIR)plAvTaskMsg.o \
	$(OBJDIR)plAvSeekMsg.o \
	$(OBJDIR)plCameraMsg.o \
	$(OBJDIR)plClimbMsg.o \
	$(OBJDIR)plEnableMsg.o \
	$(OBJDIR)plEventCallbackMsg.o \
	$(OBJDIR)proEventData.o \
	$(OBJDIR)plExcludeRegionMsg.o \
	$(OBJDIR)plInputIfaceMgrMsg.o \
	$(OBJDIR)plLinkToAgeMsg.o \
	$(OBJDIR)plLinkEffectsTriggerMsg.o \
	$(OBJDIR)plLoadAvatarMsg.o \
	$(OBJDIR)plLoadCloneMsg.o \
	$(OBJDIR)plMessage.o \
	$(OBJDIR)plMessageWithCallbacks.o \
	$(OBJDIR)plMsgForwarder.o \
	$(OBJDIR)plNotifyMsg.o \
	$(OBJDIR)plOneShotCallbacks.o \
	$(OBJDIR)plPseudoLinkEffectMsg.o \
	$(OBJDIR)plResponderMsg.o \
	$(OBJDIR)plRideAnimatedPhysMsg.o \
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
	$(OBJDIR)plGameMarkerModifier.o \
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
	$(OBJDIR)plParticleEffect.o \
	$(OBJDIR)plParticleEmitter.o \
	$(OBJDIR)plParticleGenerator.o \
	$(OBJDIR)plParticleSystem.o \
	$(OBJDIR)plCollisionDetector.o \
	$(OBJDIR)plDetectorModifier.o \
	$(OBJDIR)plGenericPhysical.o \
	$(OBJDIR)plHKSubWorld.o \
	$(OBJDIR)plObjectInVolumeDetector.o \
	$(OBJDIR)plPhysical.o \
	$(OBJDIR)plPhysicalSndGroup.o \
	$(OBJDIR)plVehicleModifier.o \
	$(OBJDIR)hsBounds.o \
	$(OBJDIR)plConvexVolume.o \
	$(OBJDIR)plHardRegion.o \
	$(OBJDIR)plHardRegionPlanes.o \
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
	$(OBJDIR)plWaveSet.o

PLSHEADERS=\
	Debug/hsExceptions.h \
	Debug/plDebug.h \
	Math/hsAffineParts.h \
	Math/hsGeometry3.h \
	Math/hsMatrix33.h \
	Math/hsMatrix44.h \
	Math/hsQuat.h \
	PlasmaDefs.h \
	PRP/Animation/hsKeys.h \
	PRP/Animation/pfObjectFlocker.h \
	PRP/Animation/plAnimPath.h \
	PRP/Animation/plAnimTimeConvert.h \
	PRP/Animation/plATCEaseCurves.h \
	PRP/Animation/plBlower.h \
	PRP/Animation/plController.h \
	PRP/Animation/plFilterCoordInterface.h \
	PRP/Animation/plLeafController.h \
	PRP/Animation/plLineFollowMod.h \
	PRP/Animation/plPosController.h \
	PRP/Animation/plRotController.h \
	PRP/Animation/plScaleController.h \
	PRP/Animation/plStereizer.h \
	PRP/Animation/plTMController.h \
	PRP/Animation/plViewFaceModifier.h \
	PRP/Audio/plAudible.h \
	PRP/Audio/plCrossfade.h \
	PRP/Audio/plDirectMusicSound.h \
	PRP/Audio/plEAXEffects.h \
	PRP/Audio/plEAXListenerMod.h \
	PRP/Audio/plSoundBuffer.h \
	PRP/Audio/plSound.h \
	PRP/Audio/plWin32Sound.h \
	PRP/Audio/plWin32StaticSound.h \
	PRP/Avatar/plAGAnim.h \
	PRP/Avatar/plAGApplicator.h \
	PRP/Avatar/plAGChannel.h \
	PRP/Avatar/plAGMasterMod.h \
	PRP/Avatar/plAGModifier.h \
	PRP/Avatar/plAnimStage.h \
	PRP/Avatar/plArmatureBrain.h \
	PRP/Avatar/plArmatureEffects.h \
	PRP/Avatar/plArmatureMod.h \
	PRP/Avatar/plATCAnim.h \
	PRP/Avatar/plAvatarClothing.h \
	PRP/Avatar/plAvBrainCoop.h \
	PRP/Avatar/plAvBrainGeneric.h \
	PRP/Avatar/plAvTask.h \
	PRP/Avatar/plClothingItem.h \
	PRP/Avatar/plLadderModifier.h \
	PRP/Avatar/plMatrixChannel.h \
	PRP/Avatar/plMultistageBehMod.h \
	PRP/Avatar/plNPCSpawnMod.h \
	PRP/Avatar/plPointChannel.h \
	PRP/Avatar/plQuatChannel.h \
	PRP/Avatar/plScalarChannel.h \
	PRP/Avatar/plSeekPointMod.h \
	PRP/Avatar/plSittingModifier.h \
	PRP/Camera/plCameraBrain.h \
	PRP/Camera/plCameraModifier.h \
	PRP/ConditionalObject/plActivatorConditionalObject.h \
	PRP/ConditionalObject/plAnimationEventConditionalObject.h \
	PRP/ConditionalObject/plBooleanConditionalObject.h \
	PRP/ConditionalObject/plConditionalObject.h \
	PRP/ConditionalObject/plControlEventConditionalObject.h \
	PRP/ConditionalObject/plFacingConditionalObject.h \
	PRP/ConditionalObject/plKeyPressConditionalObject.h \
	PRP/ConditionalObject/plVolumeSensorConditionalObject.h \
	PRP/Geometry/hsGDeviceRef.h \
	PRP/Geometry/plClusterGroup.h \
	PRP/Geometry/plCluster.h \
	PRP/Geometry/plCullPoly.h \
	PRP/Geometry/plDrawableSpans.h \
	PRP/Geometry/plGBufferGroup.h \
	PRP/Geometry/plGeometrySpan.h \
	PRP/Geometry/plIcicle.h \
	PRP/Geometry/plMorphArray.h \
	PRP/Geometry/plMorphDataSet.h \
	PRP/Geometry/plMorphDelta.h \
	PRP/Geometry/plMorphSequence.h \
	PRP/Geometry/plOccluder.h \
	PRP/Geometry/plSharedMesh.h \
	PRP/Geometry/plSpaceTree.h \
	PRP/Geometry/plSpan.h \
	PRP/Geometry/plSpanInstance.h \
	PRP/Geometry/plSpanTemplate.h \
	PRP/Geometry/plVertCoder.h \
	PRP/Geometry/plVertexSpan.h \
	PRP/GUI/pfGUIButtonMod.h \
	PRP/GUI/pfGUICheckBoxCtrl.h \
	PRP/GUI/pfGUIControlHandlers.h \
	PRP/GUI/pfGUIControlMod.h \
	PRP/GUI/pfGUIDialogMod.h \
	PRP/GUI/pfGUIDynDisplayCtrl.h \
	PRP/GUI/pfGUIKnobCtrl.h \
	PRP/GUI/pfGUIListBoxMod.h \
	PRP/GUI/pfGUIMultiLineEditCtrl.h \
	PRP/GUI/pfGUIPopUpMenu.h \
	PRP/GUI/pfGUIProgressCtrl.h \
	PRP/GUI/pfGUIRadioGroupCtrl.h \
	PRP/GUI/pfGUISkin.h \
	PRP/GUI/pfGUITextBoxMod.h \
	PRP/GUI/pfGUIUpDownPairMod.h \
	PRP/GUI/pfGUIValueCtrl.h \
	PRP/GUI/plImageLibMod.h \
	PRP/KeyedObject/hsKeyedObject.h \
	PRP/KeyedObject/plKey.h \
	PRP/KeyedObject/plLoadMask.h \
	PRP/KeyedObject/plLocation.h \
	PRP/KeyedObject/plUoid.h \
	PRP/Light/plDirectionalLightInfo.h \
	PRP/Light/plLightInfo.h \
	PRP/Light/plOmniLightInfo.h \
	PRP/Light/plShadowCaster.h \
	PRP/Light/plShadowMaster.h \
	PRP/Message/pfKIMsg.h \
	PRP/Message/plAnimCmdMsg.h \
	PRP/Message/plArmatureEffectMsg.h \
	PRP/Message/plAvatarInputStateMsg.h \
	PRP/Message/plAvatarMsg.h \
	PRP/Message/plAvSeekMsg.h \
	PRP/Message/plAvTaskMsg.h \
	PRP/Message/plCameraMsg.h \
	PRP/Message/plClimbMsg.h \
	PRP/Message/plEnableMsg.h \
	PRP/Message/plEventCallbackMsg.h \
	PRP/Message/plExcludeRegionMsg.h \
	PRP/Message/plInputIfaceMgrMsg.h \
	PRP/Message/plLinkEffectsTriggerMsg.h \
	PRP/Message/plLinkToAgeMsg.h \
	PRP/Message/plLoadAvatarMsg.h \
	PRP/Message/plLoadCloneMsg.h \
	PRP/Message/plMessage.h \
	PRP/Message/plMessageWithCallbacks.h \
	PRP/Message/plMsgForwarder.h \
	PRP/Message/plNotifyMsg.h \
	PRP/Message/plOneShotCallbacks.h \
	PRP/Message/plPseudoLinkEffectMsg.h \
	PRP/Message/plResponderMsg.h \
	PRP/Message/plRideAnimatedPhysMsg.h \
	PRP/Message/plServerReplyMsg.h \
	PRP/Message/plSimulationMsg.h \
	PRP/Message/plSoundMsg.h \
	PRP/Message/plSwimMsg.h \
	PRP/Message/plTimerCallbackMsg.h \
	PRP/Message/plTransitionMsg.h \
	PRP/Message/proEventData.h \
	PRP/Misc/plAgeLinkInfo.h \
	PRP/Misc/plFogEnvironment.h \
	PRP/Misc/plRenderLevel.h \
	PRP/Misc/plSpawnPointInfo.h \
	PRP/Modifier/plAliasModifier.h \
	PRP/Modifier/plAnimEventModifier.h \
	PRP/Modifier/plAxisAnimModifier.h \
	PRP/Modifier/plExcludeRegionModifier.h \
	PRP/Modifier/plGameMarkerModifier.h \
	PRP/Modifier/plInterfaceInfoModifier.h \
	PRP/Modifier/plLogicModBase.h \
	PRP/Modifier/plLogicModifier.h \
	PRP/Modifier/plMaintainersMarkerModifier.h \
	PRP/Modifier/plModifier.h \
	PRP/Modifier/plNodeRegionModifier.h \
	PRP/Modifier/plOneShotMod.h \
	PRP/Modifier/plPostEffectMod.h \
	PRP/Modifier/plPythonFileMod.h \
	PRP/Modifier/plPythonMod.h \
	PRP/Modifier/plRandomCommandMod.h \
	PRP/Modifier/plRandomSoundMod.h \
	PRP/Modifier/plResponderModifier.h \
	PRP/Modifier/plSpawnModifier.h \
	PRP/NetMessage/plClientGuid.h \
	PRP/NetMessage/plNetGroupId.h \
	PRP/NetMessage/plNetMessage.h \
	PRP/NetMessage/plNetMsgGameMessage.h \
	PRP/NetMessage/plNetMsgGroupOwner.h \
	PRP/NetMessage/plNetMsgInitialAgeStateSent.h \
	PRP/NetMessage/plNetMsgLoadClone.h \
	PRP/NetMessage/plNetMsgMembersList.h \
	PRP/NetMessage/plNetMsgObject.h \
	PRP/NetMessage/plNetMsgPlayerPage.h \
	PRP/NetMessage/plNetMsgRelevanceRegions.h \
	PRP/NetMessage/plNetMsgRoomsList.h \
	PRP/NetMessage/plNetMsgSDLState.h \
	PRP/NetMessage/plNetMsgSharedState.h \
	PRP/NetMessage/plNetMsgStreamedObject.h \
	PRP/NetMessage/plNetMsgStream.h \
	PRP/NetMessage/plNetSharedState.h \
	PRP/Object/plAudioInterface.h \
	PRP/Object/plCoordinateInterface.h \
	PRP/Object/plDrawInterface.h \
	PRP/Object/plObjInterface.h \
	PRP/Object/plSceneObject.h \
	PRP/Object/plSimulationInterface.h \
	PRP/Object/plSynchedObject.h \
	PRP/Particle/plBoundInterface.h \
	PRP/Particle/plParticleEffect.h \
	PRP/Particle/plParticleEmitter.h \
	PRP/Particle/plParticleGenerator.h \
	PRP/Particle/plParticleSystem.h \
	PRP/Physics/plCollisionDetector.h \
	PRP/Physics/plDetectorModifier.h \
	PRP/Physics/plGenericPhysical.h \
	PRP/Physics/plHKSubWorld.h \
	PRP/Physics/plObjectInVolumeDetector.h \
	PRP/Physics/plPhysical.h \
	PRP/Physics/plPhysicalSndGroup.h \
	PRP/Physics/plVehicleModifier.h \
	PRP/plCreatable.h \
	PRP/plPageInfo.h \
	PRP/plSceneNode.h \
	PRP/Region/hsBounds.h \
	PRP/Region/plConvexVolume.h \
	PRP/Region/plHardRegion.h \
	PRP/Region/plHardRegionPlanes.h \
	PRP/Region/plRelevanceRegion.h \
	PRP/Region/plSimpleRegionSensor.h \
	PRP/Region/plSoftVolume.h \
	PRP/Region/plSwimRegion.h \
	PRP/Region/plVisRegion.h \
	PRP/Region/plVolumeIsect.h \
	PRP/Surface/hsGMaterial.h \
	PRP/Surface/hsGMatState.h \
	PRP/Surface/plBitmap.h \
	PRP/Surface/plCubicEnvironmap.h \
	PRP/Surface/plDistOpacityMod.h \
	PRP/Surface/plDynaDecalMgr.h \
	PRP/Surface/plDynamicEnvMap.h \
	PRP/Surface/plDynamicTextMap.h \
	PRP/Surface/plDynaRippleMgr.h \
	PRP/Surface/plFadeOpacityMod.h \
	PRP/Surface/plFixedWaterState6.h \
	PRP/Surface/plFixedWaterState7.h \
	PRP/Surface/plFont.h \
	PRP/Surface/plGrassShaderMod.h \
	PRP/Surface/plLayerAnimation.h \
	PRP/Surface/plLayer.h \
	PRP/Surface/plLayerInterface.h \
	PRP/Surface/plLayerMovie.h \
	PRP/Surface/plMipmap.h \
	PRP/Surface/plPrintShape.h \
	PRP/Surface/plRenderTarget.h \
	PRP/Surface/plShader.h \
	PRP/Surface/plWaveSet.h \
	ResManager/pdUnifiedTypeMap.h \
	ResManager/plAgeInfo.h \
	ResManager/plFactory.h \
	ResManager/plKeyCollector.h \
	ResManager/plResManager.h \
	SDL/plNetGameServerState.h \
	SDL/plSDL.h \
	SDL/plSDLMgr.h \
	SDL/plStateDataRecord.h \
	SDL/plStateDescriptor.h \
	SDL/plStateVariable.h \
	Stream/hsElfStream.h \
	Stream/hsRAMStream.h \
	Stream/hsStdioStream.h \
	Stream/hsStream.h \
	Stream/hsTokenStream.h \
	Stream/pfPrcHelper.h \
	Stream/pfPrcParser.h \
	Stream/plEncryptedStream.h \
	Sys/hsColor.h \
	Sys/hsSemaphore.h \
	Sys/hsThread.h \
	Sys/Platform.h \
	Sys/plUnifiedTime.h \
	Sys/plUuid.h \
	Util/hsBitVector.h \
	Util/PlasmaVersions.h \
	Util/plDDSurface.h \
	Util/plJPEG.h \
	Util/plMD5.h \
	Util/plString.h \
	Util/plZlib.h \
	Vault/plServerGuid.h \
	Vault/plVaultNode.h \
	Vault/plVaultNodeRef.h \
	Vault/plVaultNodeTypes.h \
	Vault/plVaultStore.h

# 3rd Party Libs
OBJFILES3P=\
	$(OBJDIR)rijndael.o \
	3rdPartyLibs/squish/libsquish.a

PLSLIB=libHSPlasma.$(LIBSUFFIX)
LIBDIR=../lib

all: $(LIBDIR)/$(PLSLIB)

$(LIBDIR)/$(PLSLIB): $(PLSOBJ) $(OBJFILES3P)
	( cd 3rdPartyLibs/squish  ; $(MAKE) )
	$(CXX) $(CXXFLAGS) $(CXXLINK) $(PLSOBJ) $(OBJFILES3P) $(LINKLIB)$(PLSLIB) -o $@

install:
	cp $(LIBDIR)/$(PLSLIB) $(PREFIX)/lib
ifneq ($(LIBSUFFIX),dylib)
	ldconfig
endif

install-dev: install
	mkdir -p $(PREFIX)/include/libhsplasma
	cp --parents $(PLSHEADERS) $(PREFIX)/include/libhsplasma

uninstall:
	rm -f $(PREFIX)/lib/$(PLSLIB)
	rm -rf $(PREFIX)/include/libhsplasma

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

# HSPlasma Lib
$(OBJDIR)plDebug.o: $(PLSHEADERS) Debug/plDebug.cpp
	$(CXX) $(CXXFLAGS) -c Debug/plDebug.cpp -o $@

$(OBJDIR)hsExceptions.o: $(PLSHEADERS) Debug/hsExceptions.cpp
	$(CXX) $(CXXFLAGS) -c Debug/hsExceptions.cpp -o $@

$(OBJDIR)hsAffineParts.o: $(PLSHEADERS) Math/hsAffineParts.cpp
	$(CXX) $(CXXFLAGS) -c Math/hsAffineParts.cpp -o $@

$(OBJDIR)hsGeometry3.o: $(PLSHEADERS) Math/hsGeometry3.cpp
	$(CXX) $(CXXFLAGS) -c Math/hsGeometry3.cpp -o $@

$(OBJDIR)hsMatrix33.o: $(PLSHEADERS) Math/hsMatrix33.cpp
	$(CXX) $(CXXFLAGS) -c Math/hsMatrix33.cpp -o $@

$(OBJDIR)hsMatrix44.o: $(PLSHEADERS) Math/hsMatrix44.cpp
	$(CXX) $(CXXFLAGS) -c Math/hsMatrix44.cpp -o $@

$(OBJDIR)hsQuat.o: $(PLSHEADERS) Math/hsQuat.cpp
	$(CXX) $(CXXFLAGS) -c Math/hsQuat.cpp -o $@

$(OBJDIR)plAgeInfo.o: $(PLSHEADERS) ResManager/plAgeInfo.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/plAgeInfo.cpp -o $@

$(OBJDIR)plFactory.o: $(PLSHEADERS) ResManager/plFactory.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/plFactory.cpp -o $@

$(OBJDIR)plKeyCollector.o: $(PLSHEADERS) ResManager/plKeyCollector.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/plKeyCollector.cpp -o $@

$(OBJDIR)plResManager.o: $(PLSHEADERS) ResManager/plResManager.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/plResManager.cpp -o $@

$(OBJDIR)pdUnifiedTypeMap.o: $(PLSHEADERS) ResManager/pdUnifiedTypeMap.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/pdUnifiedTypeMap.cpp -o $@

$(OBJDIR)plNetGameServerState.o: $(PLSHEADERS) SDL/plNetGameServerState.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plNetGameServerState.cpp -o $@

$(OBJDIR)plSDL.o: $(PLSHEADERS) SDL/plSDL.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plSDL.cpp -o $@

$(OBJDIR)plSDLMgr.o: $(PLSHEADERS) SDL/plSDLMgr.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plSDLMgr.cpp -o $@

$(OBJDIR)plStateDataRecord.o: $(PLSHEADERS) SDL/plStateDataRecord.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plStateDataRecord.cpp -o $@

$(OBJDIR)plStateDescriptor.o: $(PLSHEADERS) SDL/plStateDescriptor.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plStateDescriptor.cpp -o $@

$(OBJDIR)plStateVariable.o: $(PLSHEADERS) SDL/plStateVariable.cpp
	$(CXX) $(CXXFLAGS) -c SDL/plStateVariable.cpp -o $@

$(OBJDIR)hsElfStream.o: $(PLSHEADERS) Stream/hsElfStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/hsElfStream.cpp -o $@

$(OBJDIR)plEncryptedStream.o: $(PLSHEADERS) Stream/plEncryptedStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/plEncryptedStream.cpp -o $@

$(OBJDIR)pfPrcHelper.o: $(PLSHEADERS) Stream/pfPrcHelper.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pfPrcHelper.cpp -o $@

$(OBJDIR)pfPrcParser.o: $(PLSHEADERS) Stream/pfPrcParser.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pfPrcParser.cpp -o $@

$(OBJDIR)hsRAMStream.o: $(PLSHEADERS) Stream/hsRAMStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/hsRAMStream.cpp -o $@

$(OBJDIR)hsStdioStream.o: $(PLSHEADERS) Stream/hsStdioStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/hsStdioStream.cpp -o $@

$(OBJDIR)hsStream.o: $(PLSHEADERS) Stream/hsStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/hsStream.cpp -o $@

$(OBJDIR)hsTokenStream.o: $(PLSHEADERS) Stream/hsTokenStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/hsTokenStream.cpp -o $@

$(OBJDIR)hsColor.o: $(PLSHEADERS) Sys/hsColor.cpp
	$(CXX) $(CXXFLAGS) -c Sys/hsColor.cpp -o $@

$(OBJDIR)hsThread.o: $(PLSHEADERS) Sys/hsThread_pthread.cpp
	$(CXX) $(CXXFLAGS) -c Sys/hsThread_pthread.cpp -o $@

$(OBJDIR)plUnifiedTime.o: $(PLSHEADERS) Sys/plUnifiedTime.cpp
	$(CXX) $(CXXFLAGS) -c Sys/plUnifiedTime.cpp -o $@

$(OBJDIR)plUuid.o: $(PLSHEADERS) Sys/plUuid.cpp
	$(CXX) $(CXXFLAGS) -c Sys/plUuid.cpp -o $@

$(OBJDIR)hsBitVector.o: $(PLSHEADERS) Util/hsBitVector.cpp
	$(CXX) $(CXXFLAGS) -c Util/hsBitVector.cpp -o $@

$(OBJDIR)plDDSurface.o: $(PLSHEADERS) Util/plDDSurface.cpp
	$(CXX) $(CXXFLAGS) -c Util/plDDSurface.cpp -o $@

$(OBJDIR)plJPEG.o: $(PLSHEADERS) Util/plJPEG.cpp
	$(CXX) $(CXXFLAGS) -c Util/plJPEG.cpp -o $@

$(OBJDIR)plMD5.o: $(PLSHEADERS) Util/plMD5.cpp
	$(CXX) $(CXXFLAGS) -c Util/plMD5.cpp -o $@

$(OBJDIR)PlasmaVersions.o: $(PLSHEADERS) Util/PlasmaVersions.cpp
	$(CXX) $(CXXFLAGS) -c Util/PlasmaVersions.cpp -o $@

$(OBJDIR)plString.o: $(PLSHEADERS) Util/plString.cpp
	$(CXX) $(CXXFLAGS) -c Util/plString.cpp -o $@

$(OBJDIR)plZlib.o: $(PLSHEADERS) Util/plZlib.cpp
	$(CXX) $(CXXFLAGS) -c Util/plZlib.cpp -o $@

$(OBJDIR)plServerGuid.o: $(PLSHEADERS) Vault/plServerGuid.cpp
	$(CXX) $(CXXFLAGS) -c Vault/plServerGuid.cpp -o $@

$(OBJDIR)plVaultNode.o: $(PLSHEADERS) Vault/plVaultNode.cpp
	$(CXX) $(CXXFLAGS) -c Vault/plVaultNode.cpp -o $@

$(OBJDIR)plVaultNodeRef.o: $(PLSHEADERS) Vault/plVaultNodeRef.cpp
	$(CXX) $(CXXFLAGS) -c Vault/plVaultNodeRef.cpp -o $@

$(OBJDIR)plVaultNodeTypes.o: $(PLSHEADERS) Vault/plVaultNodeTypes.cpp
	$(CXX) $(CXXFLAGS) -c Vault/plVaultNodeTypes.cpp -o $@

$(OBJDIR)plVaultStore.o: $(PLSHEADERS) Vault/plVaultStore.cpp
	$(CXX) $(CXXFLAGS) -c Vault/plVaultStore.cpp -o $@

$(OBJDIR)plCreatable.o: $(PLSHEADERS) PRP/plCreatable.cpp
	$(CXX) $(CXXFLAGS) -c PRP/plCreatable.cpp -o $@

$(OBJDIR)plPageInfo.o: $(PLSHEADERS) PRP/plPageInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/plPageInfo.cpp -o $@

$(OBJDIR)plSceneNode.o: $(PLSHEADERS) PRP/plSceneNode.cpp
	$(CXX) $(CXXFLAGS) -c PRP/plSceneNode.cpp -o $@

$(OBJDIR)plAnimPath.o: $(PLSHEADERS) PRP/Animation/plAnimPath.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plAnimPath.cpp -o $@

$(OBJDIR)plAnimTimeConvert.o: $(PLSHEADERS) PRP/Animation/plAnimTimeConvert.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plAnimTimeConvert.cpp -o $@

$(OBJDIR)plATCEaseCurves.o: $(PLSHEADERS) PRP/Animation/plATCEaseCurves.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plATCEaseCurves.cpp -o $@

$(OBJDIR)plBlower.o: $(PLSHEADERS) PRP/Animation/plBlower.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plBlower.cpp -o $@

$(OBJDIR)plController.o: $(PLSHEADERS) PRP/Animation/plController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plController.cpp -o $@

$(OBJDIR)plFilterCoordInterface.o: $(PLSHEADERS) PRP/Animation/plFilterCoordInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plFilterCoordInterface.cpp -o $@

$(OBJDIR)hsKeys.o: $(PLSHEADERS) PRP/Animation/hsKeys.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/hsKeys.cpp -o $@

$(OBJDIR)plLeafController.o: $(PLSHEADERS) PRP/Animation/plLeafController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plLeafController.cpp -o $@

$(OBJDIR)plLineFollowMod.o: $(PLSHEADERS) PRP/Animation/plLineFollowMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plLineFollowMod.cpp -o $@

$(OBJDIR)pfObjectFlocker.o: $(PLSHEADERS) PRP/Animation/pfObjectFlocker.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pfObjectFlocker.cpp -o $@

$(OBJDIR)plPosController.o: $(PLSHEADERS) PRP/Animation/plPosController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plPosController.cpp -o $@

$(OBJDIR)plRotController.o: $(PLSHEADERS) PRP/Animation/plRotController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plRotController.cpp -o $@

$(OBJDIR)plScaleController.o: $(PLSHEADERS) PRP/Animation/plScaleController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plScaleController.cpp -o $@

$(OBJDIR)plStereizer.o: $(PLSHEADERS) PRP/Animation/plStereizer.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plStereizer.cpp -o $@

$(OBJDIR)plTMController.o: $(PLSHEADERS) PRP/Animation/plTMController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plTMController.cpp -o $@

$(OBJDIR)plViewFaceModifier.o: $(PLSHEADERS) PRP/Animation/plViewFaceModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/plViewFaceModifier.cpp -o $@

$(OBJDIR)plAudible.o: $(PLSHEADERS) PRP/Audio/plAudible.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plAudible.cpp -o $@

$(OBJDIR)plCrossfade.o: $(PLSHEADERS) PRP/Audio/plCrossfade.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plCrossfade.cpp -o $@

$(OBJDIR)plDirectMusicSound.o: $(PLSHEADERS) PRP/Audio/plDirectMusicSound.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plDirectMusicSound.cpp -o $@

$(OBJDIR)plEAXEffects.o: $(PLSHEADERS) PRP/Audio/plEAXEffects.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plEAXEffects.cpp -o $@

$(OBJDIR)plEAXListenerMod.o: $(PLSHEADERS) PRP/Audio/plEAXListenerMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plEAXListenerMod.cpp -o $@

$(OBJDIR)plSound.o: $(PLSHEADERS) PRP/Audio/plSound.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plSound.cpp -o $@

$(OBJDIR)plSoundBuffer.o: $(PLSHEADERS) PRP/Audio/plSoundBuffer.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plSoundBuffer.cpp -o $@

$(OBJDIR)plWin32Sound.o: $(PLSHEADERS) PRP/Audio/plWin32Sound.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plWin32Sound.cpp -o $@

$(OBJDIR)plWin32StaticSound.o: $(PLSHEADERS) PRP/Audio/plWin32StaticSound.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/plWin32StaticSound.cpp -o $@

$(OBJDIR)plAGAnim.o: $(PLSHEADERS) PRP/Avatar/plAGAnim.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAGAnim.cpp -o $@

$(OBJDIR)plAGApplicator.o: $(PLSHEADERS) PRP/Avatar/plAGApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAGApplicator.cpp -o $@

$(OBJDIR)plAGChannel.o: $(PLSHEADERS) PRP/Avatar/plAGChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAGChannel.cpp -o $@

$(OBJDIR)plAGMasterMod.o: $(PLSHEADERS) PRP/Avatar/plAGMasterMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAGMasterMod.cpp -o $@

$(OBJDIR)plAGModifier.o: $(PLSHEADERS) PRP/Avatar/plAGModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAGModifier.cpp -o $@

$(OBJDIR)plAnimStage.o: $(PLSHEADERS) PRP/Avatar/plAnimStage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAnimStage.cpp -o $@

$(OBJDIR)plArmatureBrain.o: $(PLSHEADERS) PRP/Avatar/plArmatureBrain.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plArmatureBrain.cpp -o $@

$(OBJDIR)plArmatureEffects.o: $(PLSHEADERS) PRP/Avatar/plArmatureEffects.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plArmatureEffects.cpp -o $@

$(OBJDIR)plArmatureMod.o: $(PLSHEADERS) PRP/Avatar/plArmatureMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plArmatureMod.cpp -o $@

$(OBJDIR)plATCAnim.o: $(PLSHEADERS) PRP/Avatar/plATCAnim.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plATCAnim.cpp -o $@

$(OBJDIR)plAvatarClothing.o: $(PLSHEADERS) PRP/Avatar/plAvatarClothing.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAvatarClothing.cpp -o $@

$(OBJDIR)plAvBrainCoop.o: $(PLSHEADERS) PRP/Avatar/plAvBrainCoop.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAvBrainCoop.cpp -o $@

$(OBJDIR)plAvBrainGeneric.o: $(PLSHEADERS) PRP/Avatar/plAvBrainGeneric.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAvBrainGeneric.cpp -o $@

$(OBJDIR)plAvTask.o: $(PLSHEADERS) PRP/Avatar/plAvTask.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plAvTask.cpp -o $@

$(OBJDIR)plClothingItem.o: $(PLSHEADERS) PRP/Avatar/plClothingItem.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plClothingItem.cpp -o $@

$(OBJDIR)plLadderModifier.o: $(PLSHEADERS) PRP/Avatar/plLadderModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plLadderModifier.cpp -o $@

$(OBJDIR)plMatrixChannel.o: $(PLSHEADERS) PRP/Avatar/plMatrixChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plMatrixChannel.cpp -o $@

$(OBJDIR)plMultistageBehMod.o: $(PLSHEADERS) PRP/Avatar/plMultistageBehMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plMultistageBehMod.cpp -o $@

$(OBJDIR)plNPCSpawnMod.o: $(PLSHEADERS) PRP/Avatar/plNPCSpawnMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plNPCSpawnMod.cpp -o $@

$(OBJDIR)plPointChannel.o: $(PLSHEADERS) PRP/Avatar/plPointChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plPointChannel.cpp -o $@

$(OBJDIR)plQuatChannel.o: $(PLSHEADERS) PRP/Avatar/plQuatChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plQuatChannel.cpp -o $@

$(OBJDIR)plScalarChannel.o: $(PLSHEADERS) PRP/Avatar/plScalarChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plScalarChannel.cpp -o $@

$(OBJDIR)plSeekPointMod.o: $(PLSHEADERS) PRP/Avatar/plSeekPointMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plSeekPointMod.cpp -o $@

$(OBJDIR)plSittingModifier.o: $(PLSHEADERS) PRP/Avatar/plSittingModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/plSittingModifier.cpp -o $@

$(OBJDIR)plCameraBrain.o: $(PLSHEADERS) PRP/Camera/plCameraBrain.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Camera/plCameraBrain.cpp -o $@

$(OBJDIR)plCameraModifier.o: $(PLSHEADERS) PRP/Camera/plCameraModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Camera/plCameraModifier.cpp -o $@

$(OBJDIR)plActivatorConditionalObject.o: $(PLSHEADERS) PRP/ConditionalObject/plActivatorConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plActivatorConditionalObject.cpp -o $@

$(OBJDIR)plAnimationEventConditionalObject.o: $(PLSHEADERS) PRP/ConditionalObject/plAnimationEventConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plAnimationEventConditionalObject.cpp -o $@

$(OBJDIR)plBooleanConditionalObject.o: $(PLSHEADERS) PRP/ConditionalObject/plBooleanConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plBooleanConditionalObject.cpp -o $@

$(OBJDIR)plConditionalObject.o: $(PLSHEADERS) PRP/ConditionalObject/plConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plConditionalObject.cpp -o $@

$(OBJDIR)plControlEventConditionalObject.o: $(PLSHEADERS) PRP/ConditionalObject/plControlEventConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plControlEventConditionalObject.cpp -o $@

$(OBJDIR)plFacingConditionalObject.o: $(PLSHEADERS) PRP/ConditionalObject/plFacingConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plFacingConditionalObject.cpp -o $@

$(OBJDIR)plKeyPressConditionalObject.o: $(PLSHEADERS) PRP/ConditionalObject/plKeyPressConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plKeyPressConditionalObject.cpp -o $@

$(OBJDIR)plVolumeSensorConditionalObject.o: $(PLSHEADERS) PRP/ConditionalObject/plVolumeSensorConditionalObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/ConditionalObject/plVolumeSensorConditionalObject.cpp -o $@

$(OBJDIR)plCluster.o: $(PLSHEADERS) PRP/Geometry/plCluster.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plCluster.cpp -o $@

$(OBJDIR)plClusterGroup.o: $(PLSHEADERS) PRP/Geometry/plClusterGroup.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plClusterGroup.cpp -o $@

$(OBJDIR)plCullPoly.o: $(PLSHEADERS) PRP/Geometry/plCullPoly.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plCullPoly.cpp -o $@

$(OBJDIR)plDrawableSpans.o: $(PLSHEADERS) PRP/Geometry/plDrawableSpans.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plDrawableSpans.cpp -o $@

$(OBJDIR)plGBufferGroup.o: $(PLSHEADERS) PRP/Geometry/plGBufferGroup.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plGBufferGroup.cpp -o $@

$(OBJDIR)hsGDeviceRef.o: $(PLSHEADERS) PRP/Geometry/hsGDeviceRef.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/hsGDeviceRef.cpp -o $@

$(OBJDIR)plGeometrySpan.o: $(PLSHEADERS) PRP/Geometry/plGeometrySpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plGeometrySpan.cpp -o $@

$(OBJDIR)plIcicle.o: $(PLSHEADERS) PRP/Geometry/plIcicle.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plIcicle.cpp -o $@

$(OBJDIR)plMorphArray.o: $(PLSHEADERS) PRP/Geometry/plMorphArray.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plMorphArray.cpp -o $@

$(OBJDIR)plMorphDataSet.o: $(PLSHEADERS) PRP/Geometry/plMorphDataSet.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plMorphDataSet.cpp -o $@

$(OBJDIR)plMorphDelta.o: $(PLSHEADERS) PRP/Geometry/plMorphDelta.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plMorphDelta.cpp -o $@

$(OBJDIR)plMorphSequence.o: $(PLSHEADERS) PRP/Geometry/plMorphSequence.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plMorphSequence.cpp -o $@

$(OBJDIR)plOccluder.o: $(PLSHEADERS) PRP/Geometry/plOccluder.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plOccluder.cpp -o $@

$(OBJDIR)plSharedMesh.o: $(PLSHEADERS) PRP/Geometry/plSharedMesh.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plSharedMesh.cpp -o $@

$(OBJDIR)plSpaceTree.o: $(PLSHEADERS) PRP/Geometry/plSpaceTree.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plSpaceTree.cpp -o $@

$(OBJDIR)plSpan.o: $(PLSHEADERS) PRP/Geometry/plSpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plSpan.cpp -o $@

$(OBJDIR)plSpanInstance.o: $(PLSHEADERS) PRP/Geometry/plSpanInstance.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plSpanInstance.cpp -o $@

$(OBJDIR)plSpanTemplate.o: $(PLSHEADERS) PRP/Geometry/plSpanTemplate.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plSpanTemplate.cpp -o $@

$(OBJDIR)plVertCoder.o: $(PLSHEADERS) PRP/Geometry/plVertCoder.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plVertCoder.cpp -o $@

$(OBJDIR)plVertexSpan.o: $(PLSHEADERS) PRP/Geometry/plVertexSpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/plVertexSpan.cpp -o $@

$(OBJDIR)pfGUIButtonMod.o: $(PLSHEADERS) PRP/GUI/pfGUIButtonMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIButtonMod.cpp -o $@

$(OBJDIR)pfGUICheckBoxCtrl.o: $(PLSHEADERS) PRP/GUI/pfGUICheckBoxCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUICheckBoxCtrl.cpp -o $@

$(OBJDIR)pfGUIControlHandlers.o: $(PLSHEADERS) PRP/GUI/pfGUIControlHandlers.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIControlHandlers.cpp -o $@

$(OBJDIR)pfGUIControlMod.o: $(PLSHEADERS) PRP/GUI/pfGUIControlMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIControlMod.cpp -o $@

$(OBJDIR)pfGUIDialogMod.o: $(PLSHEADERS) PRP/GUI/pfGUIDialogMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIDialogMod.cpp -o $@

$(OBJDIR)pfGUIDynDisplayCtrl.o: $(PLSHEADERS) PRP/GUI/pfGUIDynDisplayCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIDynDisplayCtrl.cpp -o $@

$(OBJDIR)pfGUIKnobCtrl.o: $(PLSHEADERS) PRP/GUI/pfGUIKnobCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIKnobCtrl.cpp -o $@

$(OBJDIR)pfGUIListBoxMod.o: $(PLSHEADERS) PRP/GUI/pfGUIListBoxMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIListBoxMod.cpp -o $@

$(OBJDIR)pfGUIMultiLineEditCtrl.o: $(PLSHEADERS) PRP/GUI/pfGUIMultiLineEditCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIMultiLineEditCtrl.cpp -o $@

$(OBJDIR)pfGUIPopUpMenu.o: $(PLSHEADERS) PRP/GUI/pfGUIPopUpMenu.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIPopUpMenu.cpp -o $@

$(OBJDIR)pfGUIProgressCtrl.o: $(PLSHEADERS) PRP/GUI/pfGUIProgressCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIProgressCtrl.cpp -o $@

$(OBJDIR)pfGUIRadioGroupCtrl.o: $(PLSHEADERS) PRP/GUI/pfGUIRadioGroupCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIRadioGroupCtrl.cpp -o $@

$(OBJDIR)pfGUISkin.o: $(PLSHEADERS) PRP/GUI/pfGUISkin.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUISkin.cpp -o $@

$(OBJDIR)pfGUITextBoxMod.o: $(PLSHEADERS) PRP/GUI/pfGUITextBoxMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUITextBoxMod.cpp -o $@

$(OBJDIR)pfGUIUpDownPairMod.o: $(PLSHEADERS) PRP/GUI/pfGUIUpDownPairMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIUpDownPairMod.cpp -o $@

$(OBJDIR)pfGUIValueCtrl.o: $(PLSHEADERS) PRP/GUI/pfGUIValueCtrl.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pfGUIValueCtrl.cpp -o $@

$(OBJDIR)plImageLibMod.o: $(PLSHEADERS) PRP/GUI/plImageLibMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/plImageLibMod.cpp -o $@

$(OBJDIR)hsKeyedObject.o: $(PLSHEADERS) PRP/KeyedObject/hsKeyedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/hsKeyedObject.cpp -o $@

$(OBJDIR)plKey.o: $(PLSHEADERS) PRP/KeyedObject/plKey.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/plKey.cpp -o $@

$(OBJDIR)plLoadMask.o: $(PLSHEADERS) PRP/KeyedObject/plLoadMask.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/plLoadMask.cpp -o $@

$(OBJDIR)plLocation.o: $(PLSHEADERS) PRP/KeyedObject/plLocation.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/plLocation.cpp -o $@

$(OBJDIR)plUoid.o: $(PLSHEADERS) PRP/KeyedObject/plUoid.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/plUoid.cpp -o $@

$(OBJDIR)plDirectionalLightInfo.o: $(PLSHEADERS) PRP/Light/plDirectionalLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/plDirectionalLightInfo.cpp -o $@

$(OBJDIR)plLightInfo.o: $(PLSHEADERS) PRP/Light/plLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/plLightInfo.cpp -o $@

$(OBJDIR)plOmniLightInfo.o: $(PLSHEADERS) PRP/Light/plOmniLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/plOmniLightInfo.cpp -o $@

$(OBJDIR)plShadowCaster.o: $(PLSHEADERS) PRP/Light/plShadowCaster.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/plShadowCaster.cpp -o $@

$(OBJDIR)plShadowMaster.o: $(PLSHEADERS) PRP/Light/plShadowMaster.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/plShadowMaster.cpp -o $@

$(OBJDIR)pfKIMsg.o: $(PLSHEADERS) PRP/Message/pfKIMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pfKIMsg.cpp -o $@

$(OBJDIR)plAnimCmdMsg.o: $(PLSHEADERS) PRP/Message/plAnimCmdMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plAnimCmdMsg.cpp -o $@

$(OBJDIR)plArmatureEffectMsg.o: $(PLSHEADERS) PRP/Message/plArmatureEffectMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plArmatureEffectMsg.cpp -o $@

$(OBJDIR)plAvatarInputStateMsg.o: $(PLSHEADERS) PRP/Message/plAvatarInputStateMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plAvatarInputStateMsg.cpp -o $@

$(OBJDIR)plAvatarMsg.o: $(PLSHEADERS) PRP/Message/plAvatarMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plAvatarMsg.cpp -o $@

$(OBJDIR)plAvTaskMsg.o: $(PLSHEADERS) PRP/Message/plAvTaskMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plAvTaskMsg.cpp -o $@

$(OBJDIR)plAvSeekMsg.o: $(PLSHEADERS) PRP/Message/plAvSeekMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plAvSeekMsg.cpp -o $@

$(OBJDIR)plCameraMsg.o: $(PLSHEADERS) PRP/Message/plCameraMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plCameraMsg.cpp -o $@

$(OBJDIR)plClimbMsg.o: $(PLSHEADERS) PRP/Message/plClimbMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plClimbMsg.cpp -o $@

$(OBJDIR)plEnableMsg.o: $(PLSHEADERS) PRP/Message/plEnableMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plEnableMsg.cpp -o $@

$(OBJDIR)plEventCallbackMsg.o: $(PLSHEADERS) PRP/Message/plEventCallbackMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plEventCallbackMsg.cpp -o $@

$(OBJDIR)proEventData.o: $(PLSHEADERS) PRP/Message/proEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/proEventData.cpp -o $@

$(OBJDIR)plExcludeRegionMsg.o: $(PLSHEADERS) PRP/Message/plExcludeRegionMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plExcludeRegionMsg.cpp -o $@

$(OBJDIR)plInputIfaceMgrMsg.o: $(PLSHEADERS) PRP/Message/plInputIfaceMgrMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plInputIfaceMgrMsg.cpp -o $@

$(OBJDIR)plLinkToAgeMsg.o: $(PLSHEADERS) PRP/Message/plLinkToAgeMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plLinkToAgeMsg.cpp -o $@

$(OBJDIR)plLinkEffectsTriggerMsg.o: $(PLSHEADERS) PRP/Message/plLinkEffectsTriggerMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plLinkEffectsTriggerMsg.cpp -o $@

$(OBJDIR)plLoadAvatarMsg.o: $(PLSHEADERS) PRP/Message/plLoadAvatarMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plLoadAvatarMsg.cpp -o $@

$(OBJDIR)plLoadCloneMsg.o: $(PLSHEADERS) PRP/Message/plLoadCloneMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plLoadCloneMsg.cpp -o $@

$(OBJDIR)plMessage.o: $(PLSHEADERS) PRP/Message/plMessage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plMessage.cpp -o $@

$(OBJDIR)plMessageWithCallbacks.o: $(PLSHEADERS) PRP/Message/plMessageWithCallbacks.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plMessageWithCallbacks.cpp -o $@

$(OBJDIR)plMsgForwarder.o: $(PLSHEADERS) PRP/Message/plMsgForwarder.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plMsgForwarder.cpp -o $@

$(OBJDIR)plNotifyMsg.o: $(PLSHEADERS) PRP/Message/plNotifyMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plNotifyMsg.cpp -o $@

$(OBJDIR)plOneShotCallbacks.o: $(PLSHEADERS) PRP/Message/plOneShotCallbacks.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plOneShotCallbacks.cpp -o $@

$(OBJDIR)plPseudoLinkEffectMsg.o: $(PLSHEADERS) PRP/Message/plPseudoLinkEffectMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plPseudoLinkEffectMsg.cpp -o $@

$(OBJDIR)plResponderMsg.o: $(PLSHEADERS) PRP/Message/plResponderMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plResponderMsg.cpp -o $@

$(OBJDIR)plRideAnimatedPhysMsg.o: $(PLSHEADERS) PRP/Message/plRideAnimatedPhysMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plRideAnimatedPhysMsg.cpp -o $@

$(OBJDIR)plServerReplyMsg.o: $(PLSHEADERS) PRP/Message/plServerReplyMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plServerReplyMsg.cpp -o $@

$(OBJDIR)plSimulationMsg.o: $(PLSHEADERS) PRP/Message/plSimulationMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plSimulationMsg.cpp -o $@

$(OBJDIR)plSoundMsg.o: $(PLSHEADERS) PRP/Message/plSoundMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plSoundMsg.cpp -o $@

$(OBJDIR)plSwimMsg.o: $(PLSHEADERS) PRP/Message/plSwimMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plSwimMsg.cpp -o $@

$(OBJDIR)plTimerCallbackMsg.o: $(PLSHEADERS) PRP/Message/plTimerCallbackMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plTimerCallbackMsg.cpp -o $@

$(OBJDIR)plTransitionMsg.o: $(PLSHEADERS) PRP/Message/plTransitionMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/plTransitionMsg.cpp -o $@

$(OBJDIR)plAgeLinkInfo.o: $(PLSHEADERS) PRP/Misc/plAgeLinkInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Misc/plAgeLinkInfo.cpp -o $@

$(OBJDIR)plFogEnvironment.o: $(PLSHEADERS) PRP/Misc/plFogEnvironment.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Misc/plFogEnvironment.cpp -o $@

$(OBJDIR)plSpawnPointInfo.o: $(PLSHEADERS) PRP/Misc/plSpawnPointInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Misc/plSpawnPointInfo.cpp -o $@

$(OBJDIR)plAliasModifier.o: $(PLSHEADERS) PRP/Modifier/plAliasModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plAliasModifier.cpp -o $@

$(OBJDIR)plAnimEventModifier.o: $(PLSHEADERS) PRP/Modifier/plAnimEventModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plAnimEventModifier.cpp -o $@

$(OBJDIR)plAxisAnimModifier.o: $(PLSHEADERS) PRP/Modifier/plAxisAnimModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plAxisAnimModifier.cpp -o $@

$(OBJDIR)plExcludeRegionModifier.o: $(PLSHEADERS) PRP/Modifier/plExcludeRegionModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plExcludeRegionModifier.cpp -o $@

$(OBJDIR)plGameMarkerModifier.o: $(PLSHEADERS) PRP/Modifier/plGameMarkerModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plGameMarkerModifier.cpp -o $@

$(OBJDIR)plInterfaceInfoModifier.o: $(PLSHEADERS) PRP/Modifier/plInterfaceInfoModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plInterfaceInfoModifier.cpp -o $@

$(OBJDIR)plLogicModBase.o: $(PLSHEADERS) PRP/Modifier/plLogicModBase.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plLogicModBase.cpp -o $@

$(OBJDIR)plLogicModifier.o: $(PLSHEADERS) PRP/Modifier/plLogicModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plLogicModifier.cpp -o $@

$(OBJDIR)plMaintainersMarkerModifier.o: $(PLSHEADERS) PRP/Modifier/plMaintainersMarkerModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plMaintainersMarkerModifier.cpp -o $@

$(OBJDIR)plModifier.o: $(PLSHEADERS) PRP/Modifier/plModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plModifier.cpp -o $@

$(OBJDIR)plNodeRegionModifier.o: $(PLSHEADERS) PRP/Modifier/plNodeRegionModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plNodeRegionModifier.cpp -o $@

$(OBJDIR)plOneShotMod.o: $(PLSHEADERS) PRP/Modifier/plOneShotMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plOneShotMod.cpp -o $@

$(OBJDIR)plPostEffectMod.o: $(PLSHEADERS) PRP/Modifier/plPostEffectMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plPostEffectMod.cpp -o $@

$(OBJDIR)plPythonFileMod.o: $(PLSHEADERS) PRP/Modifier/plPythonFileMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plPythonFileMod.cpp -o $@

$(OBJDIR)plPythonMod.o: $(PLSHEADERS) PRP/Modifier/plPythonMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plPythonMod.cpp -o $@

$(OBJDIR)plRandomCommandMod.o: $(PLSHEADERS) PRP/Modifier/plRandomCommandMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plRandomCommandMod.cpp -o $@

$(OBJDIR)plRandomSoundMod.o: $(PLSHEADERS) PRP/Modifier/plRandomSoundMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plRandomSoundMod.cpp -o $@

$(OBJDIR)plResponderModifier.o: $(PLSHEADERS) PRP/Modifier/plResponderModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plResponderModifier.cpp -o $@

$(OBJDIR)plSpawnModifier.o: $(PLSHEADERS) PRP/Modifier/plSpawnModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/plSpawnModifier.cpp -o $@

$(OBJDIR)plClientGuid.o: $(PLSHEADERS) PRP/NetMessage/plClientGuid.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plClientGuid.cpp -o $@

$(OBJDIR)plNetGroupId.o: $(PLSHEADERS) PRP/NetMessage/plNetGroupId.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetGroupId.cpp -o $@

$(OBJDIR)plNetMessage.o: $(PLSHEADERS) PRP/NetMessage/plNetMessage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMessage.cpp -o $@

$(OBJDIR)plNetMsgGameMessage.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgGameMessage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgGameMessage.cpp -o $@

$(OBJDIR)plNetMsgGroupOwner.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgGroupOwner.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgGroupOwner.cpp -o $@

$(OBJDIR)plNetMsgInitialAgeStateSent.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgInitialAgeStateSent.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgInitialAgeStateSent.cpp -o $@

$(OBJDIR)plNetMsgLoadClone.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgLoadClone.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgLoadClone.cpp -o $@

$(OBJDIR)plNetMsgMembersList.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgMembersList.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgMembersList.cpp -o $@

$(OBJDIR)plNetMsgObject.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgObject.cpp -o $@

$(OBJDIR)plNetMsgPlayerPage.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgPlayerPage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgPlayerPage.cpp -o $@

$(OBJDIR)plNetMsgRelevanceRegions.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgRelevanceRegions.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgRelevanceRegions.cpp -o $@

$(OBJDIR)plNetMsgRoomsList.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgRoomsList.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgRoomsList.cpp -o $@

$(OBJDIR)plNetMsgSDLState.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgSDLState.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgSDLState.cpp -o $@

$(OBJDIR)plNetMsgSharedState.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgSharedState.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgSharedState.cpp -o $@

$(OBJDIR)plNetMsgStream.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgStream.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgStream.cpp -o $@

$(OBJDIR)plNetMsgStreamedObject.o: $(PLSHEADERS) PRP/NetMessage/plNetMsgStreamedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetMsgStreamedObject.cpp -o $@

$(OBJDIR)plNetSharedState.o: $(PLSHEADERS) PRP/NetMessage/plNetSharedState.cpp
	$(CXX) $(CXXFLAGS) -c PRP/NetMessage/plNetSharedState.cpp -o $@

$(OBJDIR)plAudioInterface.o: $(PLSHEADERS) PRP/Object/plAudioInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plAudioInterface.cpp -o $@

$(OBJDIR)plCoordinateInterface.o: $(PLSHEADERS) PRP/Object/plCoordinateInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plCoordinateInterface.cpp -o $@

$(OBJDIR)plDrawInterface.o: $(PLSHEADERS) PRP/Object/plDrawInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plDrawInterface.cpp -o $@

$(OBJDIR)plObjInterface.o: $(PLSHEADERS) PRP/Object/plObjInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plObjInterface.cpp -o $@

$(OBJDIR)plSceneObject.o: $(PLSHEADERS) PRP/Object/plSceneObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plSceneObject.cpp -o $@

$(OBJDIR)plSimulationInterface.o: $(PLSHEADERS) PRP/Object/plSimulationInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plSimulationInterface.cpp -o $@

$(OBJDIR)plSynchedObject.o: $(PLSHEADERS) PRP/Object/plSynchedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/plSynchedObject.cpp -o $@

$(OBJDIR)plBoundInterface.o: $(PLSHEADERS) PRP/Particle/plBoundInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Particle/plBoundInterface.cpp -o $@

$(OBJDIR)plParticleEffect.o: $(PLSHEADERS) PRP/Particle/plParticleEffect.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Particle/plParticleEffect.cpp -o $@

$(OBJDIR)plParticleEmitter.o: $(PLSHEADERS) PRP/Particle/plParticleEmitter.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Particle/plParticleEmitter.cpp -o $@

$(OBJDIR)plParticleGenerator.o: $(PLSHEADERS) PRP/Particle/plParticleGenerator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Particle/plParticleGenerator.cpp -o $@

$(OBJDIR)plParticleSystem.o: $(PLSHEADERS) PRP/Particle/plParticleSystem.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Particle/plParticleSystem.cpp -o $@

$(OBJDIR)plCollisionDetector.o: $(PLSHEADERS) PRP/Physics/plCollisionDetector.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plCollisionDetector.cpp -o $@

$(OBJDIR)plDetectorModifier.o: $(PLSHEADERS) PRP/Physics/plDetectorModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plDetectorModifier.cpp -o $@

$(OBJDIR)plGenericPhysical.o: $(PLSHEADERS) PRP/Physics/plGenericPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plGenericPhysical.cpp -o $@

$(OBJDIR)plHKSubWorld.o: $(PLSHEADERS) PRP/Physics/plHKSubWorld.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plHKSubWorld.cpp -o $@

$(OBJDIR)plObjectInVolumeDetector.o: $(PLSHEADERS) PRP/Physics/plObjectInVolumeDetector.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plObjectInVolumeDetector.cpp -o $@

$(OBJDIR)plPhysical.o: $(PLSHEADERS) PRP/Physics/plPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plPhysical.cpp -o $@

$(OBJDIR)plPhysicalSndGroup.o: $(PLSHEADERS) PRP/Physics/plPhysicalSndGroup.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plPhysicalSndGroup.cpp -o $@

$(OBJDIR)plVehicleModifier.o: $(PLSHEADERS) PRP/Physics/plVehicleModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/plVehicleModifier.cpp -o $@

$(OBJDIR)hsBounds.o: $(PLSHEADERS) PRP/Region/hsBounds.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/hsBounds.cpp -o $@

$(OBJDIR)plConvexVolume.o: $(PLSHEADERS) PRP/Region/plConvexVolume.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plConvexVolume.cpp -o $@

$(OBJDIR)plHardRegion.o: $(PLSHEADERS) PRP/Region/plHardRegion.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plHardRegion.cpp -o $@

$(OBJDIR)plHardRegionPlanes.o: $(PLSHEADERS) PRP/Region/plHardRegionPlanes.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plHardRegionPlanes.cpp -o $@

$(OBJDIR)plRelevanceRegion.o: $(PLSHEADERS) PRP/Region/plRelevanceRegion.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plRelevanceRegion.cpp -o $@

$(OBJDIR)plSimpleRegionSensor.o: $(PLSHEADERS) PRP/Region/plSimpleRegionSensor.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plSimpleRegionSensor.cpp -o $@

$(OBJDIR)plSoftVolume.o: $(PLSHEADERS) PRP/Region/plSoftVolume.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plSoftVolume.cpp -o $@

$(OBJDIR)plSwimRegion.o: $(PLSHEADERS) PRP/Region/plSwimRegion.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plSwimRegion.cpp -o $@

$(OBJDIR)plVisRegion.o: $(PLSHEADERS) PRP/Region/plVisRegion.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plVisRegion.cpp -o $@

$(OBJDIR)plVolumeIsect.o: $(PLSHEADERS) PRP/Region/plVolumeIsect.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/plVolumeIsect.cpp -o $@

$(OBJDIR)plBitmap.o: $(PLSHEADERS) PRP/Surface/plBitmap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plBitmap.cpp -o $@

$(OBJDIR)plCubicEnvironmap.o: $(PLSHEADERS) PRP/Surface/plCubicEnvironmap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plCubicEnvironmap.cpp -o $@

$(OBJDIR)plDistOpacityMod.o: $(PLSHEADERS) PRP/Surface/plDistOpacityMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plDistOpacityMod.cpp -o $@

$(OBJDIR)plDynaDecalMgr.o: $(PLSHEADERS) PRP/Surface/plDynaDecalMgr.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plDynaDecalMgr.cpp -o $@

$(OBJDIR)plDynamicEnvMap.o: $(PLSHEADERS) PRP/Surface/plDynamicEnvMap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plDynamicEnvMap.cpp -o $@

$(OBJDIR)plDynamicTextMap.o: $(PLSHEADERS) PRP/Surface/plDynamicTextMap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plDynamicTextMap.cpp -o $@

$(OBJDIR)plDynaRippleMgr.o: $(PLSHEADERS) PRP/Surface/plDynaRippleMgr.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plDynaRippleMgr.cpp -o $@

$(OBJDIR)plFadeOpacityMod.o: $(PLSHEADERS) PRP/Surface/plFadeOpacityMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plFadeOpacityMod.cpp -o $@

$(OBJDIR)plFixedWaterState6.o: $(PLSHEADERS) PRP/Surface/plFixedWaterState6.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plFixedWaterState6.cpp -o $@

$(OBJDIR)plFixedWaterState7.o: $(PLSHEADERS) PRP/Surface/plFixedWaterState7.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plFixedWaterState7.cpp -o $@

$(OBJDIR)plFont.o: $(PLSHEADERS) PRP/Surface/plFont.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plFont.cpp -o $@

$(OBJDIR)hsGMaterial.o: $(PLSHEADERS) PRP/Surface/hsGMaterial.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/hsGMaterial.cpp -o $@

$(OBJDIR)hsGMatState.o: $(PLSHEADERS) PRP/Surface/hsGMatState.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/hsGMatState.cpp -o $@

$(OBJDIR)plGrassShaderMod.o: $(PLSHEADERS) PRP/Surface/plGrassShaderMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plGrassShaderMod.cpp -o $@

$(OBJDIR)plLayer.o: $(PLSHEADERS) PRP/Surface/plLayer.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plLayer.cpp -o $@

$(OBJDIR)plLayerAnimation.o: $(PLSHEADERS) PRP/Surface/plLayerAnimation.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plLayerAnimation.cpp -o $@

$(OBJDIR)plLayerInterface.o: $(PLSHEADERS) PRP/Surface/plLayerInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plLayerInterface.cpp -o $@

$(OBJDIR)plLayerMovie.o: $(PLSHEADERS) PRP/Surface/plLayerMovie.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plLayerMovie.cpp -o $@

$(OBJDIR)plMipmap.o: $(PLSHEADERS) PRP/Surface/plMipmap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plMipmap.cpp -o $@

$(OBJDIR)plPrintShape.o: $(PLSHEADERS) PRP/Surface/plPrintShape.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plPrintShape.cpp -o $@

$(OBJDIR)plRenderTarget.o: $(PLSHEADERS) PRP/Surface/plRenderTarget.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plRenderTarget.cpp -o $@

$(OBJDIR)plShader.o: $(PLSHEADERS) PRP/Surface/plShader.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plShader.cpp -o $@

$(OBJDIR)plWaveSet.o: $(PLSHEADERS) PRP/Surface/plWaveSet.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/plWaveSet.cpp -o $@
