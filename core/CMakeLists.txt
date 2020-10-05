find_package(ZLIB REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(Threads REQUIRED)

if(ENABLE_PHYSX)
    find_package(PhysX)
endif(ENABLE_PHYSX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdPartyLibs/squish)
include_directories(${ZLIB_INCLUDE_DIR})
include_directories(${JPEG_INCLUDE_DIR})
include_directories(${PNG_INCLUDE_DIR})

if(PHYSX_FOUND AND ENABLE_PHYSX)
    add_definitions(-DHAVE_PX_SDK)
    include_directories(${PHYSX_INCLUDE_DIRS})
endif(PHYSX_FOUND AND ENABLE_PHYSX)

add_definitions(-DBUILD_PLASMA_DLL)

set(DEBUG_SOURCES
    Debug/plDebug.cpp
)
set(DEBUG_HEADERS
    Debug/hsExceptions.hpp
    Debug/plDebug.h
)

set(MATH_SOURCES
    Math/hsAffineParts.cpp
    Math/hsGeometry3.cpp
    Math/hsMatrix33.cpp
    Math/hsMatrix44.cpp
    Math/hsQuat.cpp
)
set(MATH_HEADERS
    Math/hsAffineParts.h
    Math/hsGeometry3.h
    Math/hsMatrix33.h
    Math/hsMatrix44.h
    Math/hsQuat.h
)

set(PRP_ANIM_SOURCES
    PRP/Animation/hsKeys.cpp
    PRP/Animation/pfObjectFlocker.cpp
    PRP/Animation/plATCEaseCurves.cpp
    PRP/Animation/plAnimPath.cpp
    PRP/Animation/plAnimTimeConvert.cpp
    PRP/Animation/plBlower.cpp
    PRP/Animation/plController.cpp
    PRP/Animation/plFilterCoordInterface.cpp
    PRP/Animation/plLeafController.cpp
    PRP/Animation/plLineFollowMod.cpp
    PRP/Animation/plPosController.cpp
    PRP/Animation/plRotController.cpp
    PRP/Animation/plScaleController.cpp
    PRP/Animation/plStereizer.cpp
    PRP/Animation/plTMController.cpp
    PRP/Animation/plViewFaceModifier.cpp
    PRP/Animation/plWindBoneMod.cpp
)
set(PRP_ANIM_HEADERS
    PRP/Animation/hsKeys.h
    PRP/Animation/pfObjectFlocker.h
    PRP/Animation/plATCEaseCurves.h
    PRP/Animation/plAnimPath.h
    PRP/Animation/plAnimTimeConvert.h
    PRP/Animation/plBlower.h
    PRP/Animation/plController.h
    PRP/Animation/plFilterCoordInterface.h
    PRP/Animation/plKeyControllers.hpp
    PRP/Animation/plLeafController.h
    PRP/Animation/plLineFollowMod.h
    PRP/Animation/plPosController.h
    PRP/Animation/plRotController.h
    PRP/Animation/plScaleController.h
    PRP/Animation/plStereizer.h
    PRP/Animation/plTMController.h
    PRP/Animation/plViewFaceModifier.h
    PRP/Animation/plWindBoneMod.h
)

set(PRP_AUDIO_SOURCES
    PRP/Audio/plAudible.cpp
    PRP/Audio/plCrossfade.cpp
    PRP/Audio/plDirectMusicSound.cpp
    PRP/Audio/plEAXEffects.cpp
    PRP/Audio/plEAXListenerMod.cpp
    PRP/Audio/plSound.cpp
    PRP/Audio/plSoundBuffer.cpp
    PRP/Audio/plWin32Sound.cpp
    PRP/Audio/plWin32StaticSound.cpp
)
set(PRP_AUDIO_HEADERS
    PRP/Audio/plAudible.h
    PRP/Audio/plCrossfade.h
    PRP/Audio/plDirectMusicSound.h
    PRP/Audio/plEAXEffects.h
    PRP/Audio/plEAXListenerMod.h
    PRP/Audio/plSound.h
    PRP/Audio/plSoundBuffer.h
    PRP/Audio/plWin32Sound.h
    PRP/Audio/plWin32StaticSound.h
)

set(PRP_AVATAR_SOURCES
    PRP/Avatar/plAGAnim.cpp
    PRP/Avatar/plAGApplicator.cpp
    PRP/Avatar/plAGChannel.cpp
    PRP/Avatar/plAGMasterMod.cpp
    PRP/Avatar/plAGModifier.cpp
    PRP/Avatar/plATCAnim.cpp
    PRP/Avatar/plAnimStage.cpp
    PRP/Avatar/plArmatureBrain.cpp
    PRP/Avatar/plArmatureEffects.cpp
    PRP/Avatar/plArmatureMod.cpp
    PRP/Avatar/plAvBrainCoop.cpp
    PRP/Avatar/plAvBrainGeneric.cpp
    PRP/Avatar/plAvTask.cpp
    PRP/Avatar/plAvatarClothing.cpp
    PRP/Avatar/plClothingItem.cpp
    PRP/Avatar/plLadderModifier.cpp
    PRP/Avatar/plMatrixChannel.cpp
    PRP/Avatar/plMultistageBehMod.cpp
    PRP/Avatar/plNPCSpawnMod.cpp
    PRP/Avatar/plPointChannel.cpp
    PRP/Avatar/plQuatChannel.cpp
    PRP/Avatar/plScalarChannel.cpp
    PRP/Avatar/plSeekPointMod.cpp
    PRP/Avatar/plSittingModifier.cpp
)
set(PRP_AVATAR_HEADERS
    PRP/Avatar/plAGAnim.h
    PRP/Avatar/plAGApplicator.h
    PRP/Avatar/plAGChannel.h
    PRP/Avatar/plAGMasterMod.h
    PRP/Avatar/plAGModifier.h
    PRP/Avatar/plATCAnim.h
    PRP/Avatar/plAnimStage.h
    PRP/Avatar/plArmatureBrain.h
    PRP/Avatar/plArmatureEffects.h
    PRP/Avatar/plArmatureMod.h
    PRP/Avatar/plAvBrainCoop.h
    PRP/Avatar/plAvBrainGeneric.h
    PRP/Avatar/plAvTask.h
    PRP/Avatar/plAvatarClothing.h
    PRP/Avatar/plClothingItem.h
    PRP/Avatar/plLadderModifier.h
    PRP/Avatar/plMatrixChannel.h
    PRP/Avatar/plMultistageBehMod.h
    PRP/Avatar/plNPCSpawnMod.h
    PRP/Avatar/plPointChannel.h
    PRP/Avatar/plQuatChannel.h
    PRP/Avatar/plScalarChannel.h
    PRP/Avatar/plSeekPointMod.h
    PRP/Avatar/plSittingModifier.h
)

set(PRP_CAMERA_SOURCES
    PRP/Camera/plCameraBrain.cpp
    PRP/Camera/plCameraModifier.cpp
)
set(PRP_CAMERA_HEADERS
    PRP/Camera/plCameraBrain.h
    PRP/Camera/plCameraModifier.h
)

set(PRP_COND_SOURCES
    PRP/ConditionalObject/plActivatorConditionalObject.cpp
    PRP/ConditionalObject/plAnimationEventConditionalObject.cpp
    PRP/ConditionalObject/plBooleanConditionalObject.cpp
    PRP/ConditionalObject/plConditionalObject.cpp
    PRP/ConditionalObject/plControlEventConditionalObject.cpp
    PRP/ConditionalObject/plFacingConditionalObject.cpp
    PRP/ConditionalObject/plKeyPressConditionalObject.cpp
    PRP/ConditionalObject/plVolumeSensorConditionalObject.cpp
)
set(PRP_COND_HEADERS
    PRP/ConditionalObject/plActivatorConditionalObject.h
    PRP/ConditionalObject/plAnimationEventConditionalObject.h
    PRP/ConditionalObject/plBooleanConditionalObject.h
    PRP/ConditionalObject/plConditionalObject.h
    PRP/ConditionalObject/plControlEventConditionalObject.h
    PRP/ConditionalObject/plDetectConditionalObjects.hpp
    PRP/ConditionalObject/plFacingConditionalObject.h
    PRP/ConditionalObject/plKeyPressConditionalObject.h
    PRP/ConditionalObject/plVolumeSensorConditionalObject.h
)

set(PRP_GEOM_SOURCES
    PRP/Geometry/plCluster.cpp
    PRP/Geometry/plClusterGroup.cpp
    PRP/Geometry/plCullPoly.cpp
    PRP/Geometry/plDrawableSpans.cpp
    PRP/Geometry/plGBufferGroup.cpp
    PRP/Geometry/plGeometrySpan.cpp
    PRP/Geometry/plIcicle.cpp
    PRP/Geometry/plMorphArray.cpp
    PRP/Geometry/plMorphDataSet.cpp
    PRP/Geometry/plMorphDelta.cpp
    PRP/Geometry/plMorphSequence.cpp
    PRP/Geometry/plOccluder.cpp
    PRP/Geometry/plSharedMesh.cpp
    PRP/Geometry/plSpaceTree.cpp
    PRP/Geometry/plSpan.cpp
    PRP/Geometry/plSpanInstance.cpp
    PRP/Geometry/plSpanTemplate.cpp
    PRP/Geometry/plVertCoder.cpp
    PRP/Geometry/plVertexSpan.cpp
)
set(PRP_GEOM_HEADERS
    PRP/Geometry/plCluster.h
    PRP/Geometry/plClusterGroup.h
    PRP/Geometry/plCullPoly.h
    PRP/Geometry/plDrawableSpans.h
    PRP/Geometry/plGBufferGroup.h
    PRP/Geometry/plGeometrySpan.h
    PRP/Geometry/plIcicle.h
    PRP/Geometry/plMorphArray.h
    PRP/Geometry/plMorphDataSet.h
    PRP/Geometry/plMorphDelta.h
    PRP/Geometry/plMorphSequence.h
    PRP/Geometry/plOccluder.h
    PRP/Geometry/plSharedMesh.h
    PRP/Geometry/plSpaceTree.h
    PRP/Geometry/plSpan.h
    PRP/Geometry/plSpanInstance.h
    PRP/Geometry/plSpanTemplate.h
    PRP/Geometry/plVertCoder.h
    PRP/Geometry/plVertexSpan.h
)

set(PRP_GUI_SOURCES
    PRP/GUI/pfGUIButtonMod.cpp
    PRP/GUI/pfGUICheckBoxCtrl.cpp
    PRP/GUI/pfGUIControlHandlers.cpp
    PRP/GUI/pfGUIControlMod.cpp
    PRP/GUI/pfGUIDialogMod.cpp
    PRP/GUI/pfGUIDynDisplayCtrl.cpp
    PRP/GUI/pfGUIKnobCtrl.cpp
    PRP/GUI/pfGUIListBoxMod.cpp
    PRP/GUI/pfGUIMultiLineEditCtrl.cpp
    PRP/GUI/pfGUIPopUpMenu.cpp
    PRP/GUI/pfGUIProgressCtrl.cpp
    PRP/GUI/pfGUIRadioGroupCtrl.cpp
    PRP/GUI/pfGUISkin.cpp
    PRP/GUI/pfGUITextBoxMod.cpp
    PRP/GUI/pfGUIUpDownPairMod.cpp
    PRP/GUI/pfGUIValueCtrl.cpp
    PRP/GUI/plImageLibMod.cpp
)
set(PRP_GUI_HEADERS
    PRP/GUI/pfGUIButtonMod.h
    PRP/GUI/pfGUICheckBoxCtrl.h
    PRP/GUI/pfGUIControlHandlers.h
    PRP/GUI/pfGUIControlMod.h
    PRP/GUI/pfGUIDialogMod.h
    PRP/GUI/pfGUIDynDisplayCtrl.h
    PRP/GUI/pfGUIKnobCtrl.h
    PRP/GUI/pfGUIListBoxMod.h
    PRP/GUI/pfGUIMisc.hpp
    PRP/GUI/pfGUIMultiLineEditCtrl.h
    PRP/GUI/pfGUIPopUpMenu.h
    PRP/GUI/pfGUIProgressCtrl.h
    PRP/GUI/pfGUIRadioGroupCtrl.h
    PRP/GUI/pfGUISkin.h
    PRP/GUI/pfGUITextBoxMod.h
    PRP/GUI/pfGUIUpDownPairMod.h
    PRP/GUI/pfGUIValueCtrl.h
    PRP/GUI/plImageLibMod.h
)

set(PRP_KEYOBJ_SOURCES
    PRP/KeyedObject/hsKeyedObject.cpp
    PRP/KeyedObject/plKey.cpp
    PRP/KeyedObject/plLoadMask.cpp
    PRP/KeyedObject/plLocation.cpp
    PRP/KeyedObject/plUoid.cpp
)
set(PRP_KEYOBJ_HEADERS
    PRP/KeyedObject/hsKeyedObject.h
    PRP/KeyedObject/plKey.h
    PRP/KeyedObject/plLoadMask.h
    PRP/KeyedObject/plLocation.h
    PRP/KeyedObject/plUoid.h
)

set(PRP_LIGHT_SOURCES
    PRP/Light/plDirectionalLightInfo.cpp
    PRP/Light/plLightInfo.cpp
    PRP/Light/plOmniLightInfo.cpp
    PRP/Light/plShadowCaster.cpp
    PRP/Light/plShadowMaster.cpp
)
set(PRP_LIGHT_HEADERS
    PRP/Light/plDirectionalLightInfo.h
    PRP/Light/plLightInfo.h
    PRP/Light/plOmniLightInfo.h
    PRP/Light/plShadowCaster.h
    PRP/Light/plShadowMaster.h
)

set(PRP_MSG_SOURCES
    PRP/Message/pfKIMsg.cpp
    PRP/Message/plAccountUpdateMsg.cpp
    PRP/Message/plAnimCmdMsg.cpp
    PRP/Message/plArmatureEffectMsg.cpp
    PRP/Message/plAvSeekMsg.cpp
    PRP/Message/plAvTaskMsg.cpp
    PRP/Message/plAvatarInputStateMsg.cpp
    PRP/Message/plAvatarMsg.cpp
    PRP/Message/plCameraMsg.cpp
    PRP/Message/plClimbMsg.cpp
    PRP/Message/plConsoleMsg.cpp
    PRP/Message/plCursorChangeMsg.cpp
    PRP/Message/plEnableMsg.cpp
    PRP/Message/plEventCallbackMsg.cpp
    PRP/Message/plExcludeRegionMsg.cpp
    PRP/Message/plInputIfaceMgrMsg.cpp
    PRP/Message/plLinkEffectsTriggerMsg.cpp
    PRP/Message/plLinkToAgeMsg.cpp
    PRP/Message/plLoadAvatarMsg.cpp
    PRP/Message/plLoadCloneMsg.cpp
    PRP/Message/plMessage.cpp
    PRP/Message/plMessageWithCallbacks.cpp
    PRP/Message/plMsgForwarder.cpp
    PRP/Message/plNotifyMsg.cpp
    PRP/Message/plOneShotCallbacks.cpp
    PRP/Message/plPseudoLinkEffectMsg.cpp
    PRP/Message/plResponderMsg.cpp
    PRP/Message/plRideAnimatedPhysMsg.cpp
    PRP/Message/plServerReplyMsg.cpp
    PRP/Message/plSimulationMsg.cpp
    PRP/Message/plSoundMsg.cpp
    PRP/Message/plSwimMsg.cpp
    PRP/Message/plTimerCallbackMsg.cpp
    PRP/Message/plTransitionMsg.cpp
    PRP/Message/plWarpMsg.cpp
    PRP/Message/proEventData.cpp
)
set(PRP_MSG_HEADERS
    PRP/Message/pfKIMsg.h
    PRP/Message/plAccountUpdateMsg.h
    PRP/Message/plAnimCmdMsg.h
    PRP/Message/plArmatureEffectMsg.h
    PRP/Message/plAvSeekMsg.h
    PRP/Message/plAvTaskMsg.h
    PRP/Message/plAvatarInputStateMsg.h
    PRP/Message/plAvatarMsg.h
    PRP/Message/plCameraMsg.h
    PRP/Message/plClimbMsg.h
    PRP/Message/plConsoleMsg.h
    PRP/Message/plCursorChangeMsg.h
    PRP/Message/plEnableMsg.h
    PRP/Message/plEventCallbackMsg.h
    PRP/Message/plExcludeRegionMsg.h
    PRP/Message/plInputIfaceMgrMsg.h
    PRP/Message/plLinkEffectsTriggerMsg.h
    PRP/Message/plLinkToAgeMsg.h
    PRP/Message/plLoadAvatarMsg.h
    PRP/Message/plLoadCloneMsg.h
    PRP/Message/plMessage.h
    PRP/Message/plMessageWithCallbacks.h
    PRP/Message/plMsgForwarder.h
    PRP/Message/plNotifyMsg.h
    PRP/Message/plOneShotCallbacks.h
    PRP/Message/plPseudoLinkEffectMsg.h
    PRP/Message/plResponderMsg.h
    PRP/Message/plRideAnimatedPhysMsg.h
    PRP/Message/plServerReplyMsg.h
    PRP/Message/plSimulationMsg.h
    PRP/Message/plSoundMsg.h
    PRP/Message/plSwimMsg.h
    PRP/Message/plTimerCallbackMsg.h
    PRP/Message/plTransitionMsg.h
    PRP/Message/plWarpMsg.h
    PRP/Message/proEventData.h
)

set(PRP_MISC_SOURCES
    PRP/Misc/plAgeLinkInfo.cpp
    PRP/Misc/plFogEnvironment.cpp
    PRP/Misc/plSpawnPointInfo.cpp
)
set(PRP_MISC_HEADERS
    PRP/Misc/plAgeLinkInfo.h
    PRP/Misc/plFogEnvironment.h
    PRP/Misc/plRenderLevel.h
    PRP/Misc/plSpawnPointInfo.h
)

set(PRP_MOD_SOURCES
    PRP/Modifier/plAliasModifier.cpp
    PRP/Modifier/plAnimEventModifier.cpp
    PRP/Modifier/plAxisAnimModifier.cpp
    PRP/Modifier/plExcludeRegionModifier.cpp
    PRP/Modifier/plFollowMod.cpp
    PRP/Modifier/plGameMarkerModifier.cpp
    PRP/Modifier/plInterfaceInfoModifier.cpp
    PRP/Modifier/plLogicModBase.cpp
    PRP/Modifier/plLogicModifier.cpp
    PRP/Modifier/plMaintainersMarkerModifier.cpp
    PRP/Modifier/plModifier.cpp
    PRP/Modifier/plNodeRegionModifier.cpp
    PRP/Modifier/plOneShotMod.cpp
    PRP/Modifier/plPostEffectMod.cpp
    PRP/Modifier/plPythonFileMod.cpp
    PRP/Modifier/plPythonMod.cpp
    PRP/Modifier/plRandomCommandMod.cpp
    PRP/Modifier/plRandomSoundMod.cpp
    PRP/Modifier/plResponderModifier.cpp
    PRP/Modifier/plSpawnModifier.cpp
)
set(PRP_MOD_HEADERS
    PRP/Modifier/plAliasModifier.h
    PRP/Modifier/plAnimEventModifier.h
    PRP/Modifier/plAxisAnimModifier.h
    PRP/Modifier/plExcludeRegionModifier.h
    PRP/Modifier/plFollowMod.h
    PRP/Modifier/plGameMarkerModifier.h
    PRP/Modifier/plInterfaceInfoModifier.h
    PRP/Modifier/plLogicModBase.h
    PRP/Modifier/plLogicModifier.h
    PRP/Modifier/plMaintainersMarkerModifier.h
    PRP/Modifier/plModifier.h
    PRP/Modifier/plNodeRegionModifier.h
    PRP/Modifier/plOneShotMod.h
    PRP/Modifier/plPostEffectMod.h
    PRP/Modifier/plPythonFileMod.h
    PRP/Modifier/plPythonMod.h
    PRP/Modifier/plRandomCommandMod.h
    PRP/Modifier/plRandomSoundMod.h
    PRP/Modifier/plResponderModifier.h
    PRP/Modifier/plSpawnModifier.h
)

set(PRP_NETMSG_SOURCES
    PRP/NetMessage/plClientGuid.cpp
    PRP/NetMessage/plNetGroupId.cpp
    PRP/NetMessage/plNetMessage.cpp
    PRP/NetMessage/plNetMsgGameMessage.cpp
    PRP/NetMessage/plNetMsgGroupOwner.cpp
    PRP/NetMessage/plNetMsgInitialAgeStateSent.cpp
    PRP/NetMessage/plNetMsgLoadClone.cpp
    PRP/NetMessage/plNetMsgMembersList.cpp
    PRP/NetMessage/plNetMsgObject.cpp
    PRP/NetMessage/plNetMsgPlayerPage.cpp
    PRP/NetMessage/plNetMsgRelevanceRegions.cpp
    PRP/NetMessage/plNetMsgRoomsList.cpp
    PRP/NetMessage/plNetMsgSDLState.cpp
    PRP/NetMessage/plNetMsgSharedState.cpp
    PRP/NetMessage/plNetMsgStream.cpp
    PRP/NetMessage/plNetMsgStreamedObject.cpp
    PRP/NetMessage/plNetSharedState.cpp
)
set(PRP_NETMSG_HEADERS
    PRP/NetMessage/plClientGuid.h
    PRP/NetMessage/plNetGroupId.h
    PRP/NetMessage/plNetMessage.h
    PRP/NetMessage/plNetMsgGameMessage.h
    PRP/NetMessage/plNetMsgGroupOwner.h
    PRP/NetMessage/plNetMsgInitialAgeStateSent.h
    PRP/NetMessage/plNetMsgLoadClone.h
    PRP/NetMessage/plNetMsgMembersList.h
    PRP/NetMessage/plNetMsgObject.h
    PRP/NetMessage/plNetMsgPlayerPage.h
    PRP/NetMessage/plNetMsgRelevanceRegions.h
    PRP/NetMessage/plNetMsgRoomsList.h
    PRP/NetMessage/plNetMsgSDLState.h
    PRP/NetMessage/plNetMsgSharedState.h
    PRP/NetMessage/plNetMsgStream.h
    PRP/NetMessage/plNetMsgStreamedObject.h
    PRP/NetMessage/plNetSharedState.h
)

set(PRP_OBJ_SOURCES
    PRP/Object/plAudioInterface.cpp
    PRP/Object/plCoordinateInterface.cpp
    PRP/Object/plDrawInterface.cpp
    PRP/Object/plObjInterface.cpp
    PRP/Object/plSceneObject.cpp
    PRP/Object/plSimulationInterface.cpp
    PRP/Object/plSynchedObject.cpp
)
set(PRP_OBJ_HEADERS
    PRP/Object/plAudioInterface.h
    PRP/Object/plCoordinateInterface.h
    PRP/Object/plDrawInterface.h
    PRP/Object/plObjInterface.h
    PRP/Object/plSceneObject.h
    PRP/Object/plSimulationInterface.h
    PRP/Object/plSynchedObject.h
)

set(PRP_PARTICLE_SOURCES
    PRP/Particle/plBoundInterface.cpp
    PRP/Particle/plParticleEffect.cpp
    PRP/Particle/plParticleEmitter.cpp
    PRP/Particle/plParticleGenerator.cpp
    PRP/Particle/plParticleSystem.cpp
)
set(PRP_PARTICLE_HEADERS
    PRP/Particle/plBoundInterface.h
    PRP/Particle/plParticleApplicator.hpp
    PRP/Particle/plParticleEffect.h
    PRP/Particle/plParticleEmitter.h
    PRP/Particle/plParticleGenerator.h
    PRP/Particle/plParticleSystem.h
)

set(PRP_PHYS_SOURCES
    PRP/Physics/plCollisionDetector.cpp
    PRP/Physics/plDetectorModifier.cpp
    PRP/Physics/plGenericPhysical.cpp
    PRP/Physics/plHKSubWorld.cpp
    PRP/Physics/plObjectInVolumeDetector.cpp
    PRP/Physics/plPhysical.cpp
    PRP/Physics/plPhysicalSndGroup.cpp
    PRP/Physics/plPXPhysical.cpp
    PRP/Physics/plVehicleModifier.cpp
)
set(PRP_PHYS_HEADERS
    PRP/Physics/plCollisionDetector.h
    PRP/Physics/plDetectorModifier.h
    PRP/Physics/plGenericPhysical.h
    PRP/Physics/plHKSubWorld.h
    PRP/Physics/plObjectInVolumeDetector.h
    PRP/Physics/plPhysical.h
    PRP/Physics/plPhysicalSndGroup.h
    PRP/Physics/plVehicleModifier.h
)

set(PRP_REGION_SOURCES
    PRP/Region/hsBounds.cpp
    PRP/Region/plConvexVolume.cpp
    PRP/Region/plHardRegion.cpp
    PRP/Region/plHardRegionPlanes.cpp
    PRP/Region/plRelevanceRegion.cpp
    PRP/Region/plSimpleRegionSensor.cpp
    PRP/Region/plSoftVolume.cpp
    PRP/Region/plSwimRegion.cpp
    PRP/Region/plVisRegion.cpp
    PRP/Region/plVolumeIsect.cpp
)
set(PRP_REGION_HEADERS
    PRP/Region/hsBounds.h
    PRP/Region/plConvexVolume.h
    PRP/Region/plHardRegion.h
    PRP/Region/plHardRegionPlanes.h
    PRP/Region/plRegionBase.hpp
    PRP/Region/plRelevanceRegion.h
    PRP/Region/plSimpleRegionSensor.h
    PRP/Region/plSoftVolume.h
    PRP/Region/plSwimRegion.h
    PRP/Region/plVisRegion.h
    PRP/Region/plVolumeIsect.h
)

set(PRP_SURFACE_SOURCES
    PRP/Surface/hsGMatState.cpp
    PRP/Surface/hsGMaterial.cpp
    PRP/Surface/plBitmap.cpp
    PRP/Surface/plCubicEnvironmap.cpp
    PRP/Surface/plDistOpacityMod.cpp
    PRP/Surface/plDynaDecalMgr.cpp
    PRP/Surface/plDynaRippleMgr.cpp
    PRP/Surface/plDynamicEnvMap.cpp
    PRP/Surface/plDynamicTextMap.cpp
    PRP/Surface/plFadeOpacityMod.cpp
    PRP/Surface/plFixedWaterState6.cpp
    PRP/Surface/plFixedWaterState7.cpp
    PRP/Surface/plFont.cpp
    PRP/Surface/plGrassShaderMod.cpp
    PRP/Surface/plLayer.cpp
    PRP/Surface/plLayerAnimation.cpp
    PRP/Surface/plLayerInterface.cpp
    PRP/Surface/plLayerMovie.cpp
    PRP/Surface/plMipmap.cpp
    PRP/Surface/plPrintShape.cpp
    PRP/Surface/plRenderTarget.cpp
    PRP/Surface/plShader.cpp
    PRP/Surface/plWaveSet.cpp
)
set(PRP_SURFACE_HEADERS
    PRP/Surface/hsGMatState.h
    PRP/Surface/hsGMaterial.h
    PRP/Surface/plBitmap.h
    PRP/Surface/plCubicEnvironmap.h
    PRP/Surface/plDistOpacityMod.h
    PRP/Surface/plDynaDecalMgr.h
    PRP/Surface/plDynaRippleMgr.h
    PRP/Surface/plDynamicEnvMap.h
    PRP/Surface/plDynamicTextMap.h
    PRP/Surface/plFadeOpacityMod.h
    PRP/Surface/plFixedWaterState6.h
    PRP/Surface/plFixedWaterState7.h
    PRP/Surface/plFont.h
    PRP/Surface/plGrassShaderMod.h
    PRP/Surface/plLayer.h
    PRP/Surface/plLayerAnimation.h
    PRP/Surface/plLayerInterface.h
    PRP/Surface/plLayerMovie.h
    PRP/Surface/plMipmap.h
    PRP/Surface/plPrintShape.h
    PRP/Surface/plRenderTarget.h
    PRP/Surface/plShader.h
    PRP/Surface/plWaveSet.h
)

set(PRP_SOURCES
    PRP/plCreatable.cpp
    PRP/plCreatableListHelper.cpp
    PRP/plPageInfo.cpp
    PRP/plSceneNode.cpp
)
set(PRP_HEADERS
    PRP/plCreatable.h
    PRP/plCreatableListHelper.h
    PRP/plPageInfo.h
    PRP/plSceneNode.h
)

set(RESMGR_SOURCES
    ResManager/pdUnifiedTypeMap.cpp
    ResManager/plAgeInfo.cpp
    ResManager/plFactory.cpp
    ResManager/plKeyCollector.cpp
    ResManager/plResManager.cpp
)
set(RESMGR_HEADERS
    ResManager/pdUnifiedTypeMap.h
    ResManager/plAgeInfo.h
    ResManager/plFactory.h
    ResManager/plKeyCollector.h
    ResManager/plResManager.h
)

set(SDL_SOURCES
    SDL/plNetGameServerState.cpp
    SDL/plSDL.cpp
    SDL/plSDLMgr.cpp
    SDL/plStateDataRecord.cpp
    SDL/plStateDescriptor.cpp
    SDL/plStateVariable.cpp
)
set(SDL_HEADERS
    SDL/plNetGameServerState.h
    SDL/plSDL.h
    SDL/plSDLMgr.h
    SDL/plStateDataRecord.h
    SDL/plStateDescriptor.h
    SDL/plStateVariable.h
)

set(STREAM_SOURCES
    Stream/hsElfStream.cpp
    Stream/hsRAMStream.cpp
    Stream/hsStdioStream.cpp
    Stream/hsStream.cpp
    Stream/hsTokenStream.cpp
    Stream/pfPrcHelper.cpp
    Stream/pfPrcParser.cpp
    Stream/pfSizedStream.cpp
    Stream/plEncryptedStream.cpp
)
set(STREAM_HEADERS
    Stream/hsElfStream.h
    Stream/hsRAMStream.h
    Stream/hsStdioStream.h
    Stream/hsStream.h
    Stream/hsTokenStream.h
    Stream/pfPrcHelper.h
    Stream/pfPrcParser.h
    Stream/pfSizedStream.h
    Stream/plEncryptedStream.h
)

set(SYS_SOURCES
    Sys/hsColor.cpp
    Sys/hsThread.cpp
    Sys/plUnifiedTime.cpp
    Sys/plUuid.cpp
)
set(SYS_HEADERS
    Sys/Platform.h
    Sys/hsColor.h
    Sys/hsThread.h
    Sys/plUnifiedTime.h
    Sys/plUuid.h
)

set(UTIL_SOURCES
    Util/PlasmaVersions.cpp
    Util/hs3DDevice.cpp
    Util/hsBitVector.cpp
    Util/hsRadixSort.cpp
    Util/hsSumFile.cpp
    Util/plDDSurface.cpp
    Util/plJPEG.cpp
    Util/plPNG.cpp
    Util/plMD5.cpp
    Util/plZlib.cpp
)
set(UTIL_HEADERS
    Util/PlasmaVersions.h
    Util/hs3DDevice.h
    Util/hsBitVector.h
    Util/hsRadixSort.h
    Util/hsSumFile.h
    Util/plDDSurface.h
    Util/plJPEG.h
    Util/plPNG.h
    Util/plMD5.h
    Util/plZlib.h
)

set(VAULT_SOURCES
    Vault/plServerGuid.cpp
    Vault/plVaultNode.cpp
    Vault/plVaultNodeRef.cpp
    Vault/plVaultNodeTypes.cpp
    Vault/plVaultStore.cpp
)
set(VAULT_HEADERS
    Vault/plServerGuid.h
    Vault/plVaultNode.h
    Vault/plVaultNodeRef.h
    Vault/plVaultNodeTypes.h
    Vault/plVaultStore.h
)

set(PLASMA_HEADERS
    PlasmaDefs.h
    ${PROJECT_BINARY_DIR}/PlasmaConfig.h
)

set(RIJNDAEL_SOURCES
    3rdPartyLibs/rijndael.cpp
    3rdPartyLibs/rijndael.h
)

set(SQUISH_SOURCES
    3rdPartyLibs/squish/alpha.cpp
    3rdPartyLibs/squish/alpha.h
    3rdPartyLibs/squish/clusterfit.cpp
    3rdPartyLibs/squish/clusterfit.h
    3rdPartyLibs/squish/colourblock.cpp
    3rdPartyLibs/squish/colourblock.h
    3rdPartyLibs/squish/colourfit.cpp
    3rdPartyLibs/squish/colourfit.h
    3rdPartyLibs/squish/colourset.cpp
    3rdPartyLibs/squish/colourset.h
    3rdPartyLibs/squish/maths.cpp
    3rdPartyLibs/squish/maths.h
    3rdPartyLibs/squish/rangefit.cpp
    3rdPartyLibs/squish/rangefit.h
    3rdPartyLibs/squish/simd.h
    3rdPartyLibs/squish/simd_float.h
    3rdPartyLibs/squish/simd_sse.h
    3rdPartyLibs/squish/singlecolourfit.cpp
    3rdPartyLibs/squish/singlecolourfit.h
    3rdPartyLibs/squish/squish.cpp
    3rdPartyLibs/squish/squish.h
)

if(ENABLE_SSE2)
    add_definitions(-DSQUISH_USE_SSE=2)
endif()

add_library(HSPlasma
            ${DEBUG_SOURCES}        ${DEBUG_HEADERS}
            ${MATH_SOURCES}         ${MATH_HEADERS}
            ${PRP_ANIM_SOURCES}     ${PRP_ANIM_HEADERS}
            ${PRP_AUDIO_SOURCES}    ${PRP_AUDIO_HEADERS}
            ${PRP_AVATAR_SOURCES}   ${PRP_AVATAR_HEADERS}
            ${PRP_CAMERA_SOURCES}   ${PRP_CAMERA_HEADERS}
            ${PRP_COND_SOURCES}     ${PRP_COND_HEADERS}
            ${PRP_GEOM_SOURCES}     ${PRP_GEOM_HEADERS}
            ${PRP_GUI_SOURCES}      ${PRP_GUI_HEADERS}
            ${PRP_KEYOBJ_SOURCES}   ${PRP_KEYOBJ_HEADERS}
            ${PRP_LIGHT_SOURCES}    ${PRP_LIGHT_HEADERS}
            ${PRP_MISC_SOURCES}     ${PRP_MISC_HEADERS}
            ${PRP_MOD_SOURCES}      ${PRP_MOD_HEADERS}
            ${PRP_MSG_SOURCES}      ${PRP_MSG_HEADERS}
            ${PRP_NETMSG_SOURCES}   ${PRP_NETMSG_HEADERS}
            ${PRP_OBJ_SOURCES}      ${PRP_OBJ_HEADERS}
            ${PRP_PARTICLE_SOURCES} ${PRP_PARTICLE_HEADERS}
            ${PRP_PHYS_SOURCES}     ${PRP_PHYS_HEADERS}
            ${PRP_REGION_SOURCES}   ${PRP_REGION_HEADERS}
            ${PRP_SURFACE_SOURCES}  ${PRP_SURFACE_HEADERS}
            ${PRP_SOURCES}          ${PRP_HEADERS}
            ${RESMGR_SOURCES}       ${RESMGR_HEADERS}
            ${SDL_SOURCES}          ${SDL_HEADERS}
            ${STREAM_SOURCES}       ${STREAM_HEADERS}
            ${SYS_SOURCES}          ${SYS_HEADERS}
            ${UTIL_SOURCES}         ${UTIL_HEADERS}
            ${VAULT_SOURCES}        ${VAULT_HEADERS}
                                    ${PLASMA_HEADERS}
            ${RIJNDAEL_SOURCES}
            ${SQUISH_SOURCES}
)
target_link_libraries(HSPlasma ${PNG_LIBRARIES} ${JPEG_LIBRARIES} ${ZLIB_LIBRARIES}
                      ${CMAKE_THREAD_LIBS_INIT} ${STRING_THEORY_LIBRARIES})
if(PHYSX_FOUND AND ENABLE_PHYSX)
    target_link_libraries(HSPlasma ${PHYSX_COOKING_LIBRARY})
endif(PHYSX_FOUND AND ENABLE_PHYSX)

target_include_directories(HSPlasma PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
                           $<INSTALL_INTERFACE:include/HSPlasma>)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libhsplasma.pc.in.cmake ${CMAKE_CURRENT_BINARY_DIR}/libhsplasma.pc @ONLY)

# Package Installation
install(TARGETS HSPlasma
        EXPORT HSPlasma-targets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

include(CMakePackageConfigHelpers)
configure_package_config_file(HSPlasmaConfig.cmake.in
                              ${CMAKE_CURRENT_BINARY_DIR}/HSPlasmaConfig.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake/HSPlasma)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/HSPlasmaConfig.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake/HSPlasma)

install(FILES ${DEBUG_HEADERS} DESTINATION include/HSPlasma/Debug)
install(FILES ${MATH_HEADERS} DESTINATION include/HSPlasma/Math)
install(FILES ${PRP_ANIM_HEADERS} DESTINATION include/HSPlasma/PRP/Animation)
install(FILES ${PRP_AUDIO_HEADERS} DESTINATION include/HSPlasma/PRP/Audio)
install(FILES ${PRP_AVATAR_HEADERS} DESTINATION include/HSPlasma/PRP/Avatar)
install(FILES ${PRP_CAMERA_HEADERS} DESTINATION include/HSPlasma/PRP/Camera)
install(FILES ${PRP_COND_HEADERS} DESTINATION include/HSPlasma/PRP/ConditionalObject)
install(FILES ${PRP_GEOM_HEADERS} DESTINATION include/HSPlasma/PRP/Geometry)
install(FILES ${PRP_GUI_HEADERS} DESTINATION include/HSPlasma/PRP/GUI)
install(FILES ${PRP_KEYOBJ_HEADERS} DESTINATION include/HSPlasma/PRP/KeyedObject)
install(FILES ${PRP_LIGHT_HEADERS} DESTINATION include/HSPlasma/PRP/Light)
install(FILES ${PRP_MSG_HEADERS} DESTINATION include/HSPlasma/PRP/Message)
install(FILES ${PRP_MISC_HEADERS} DESTINATION include/HSPlasma/PRP/Misc)
install(FILES ${PRP_MOD_HEADERS} DESTINATION include/HSPlasma/PRP/Modifier)
install(FILES ${PRP_NETMSG_HEADERS} DESTINATION include/HSPlasma/PRP/NetMessage)
install(FILES ${PRP_OBJ_HEADERS} DESTINATION include/HSPlasma/PRP/Object)
install(FILES ${PRP_PARTICLE_HEADERS} DESTINATION include/HSPlasma/PRP/Particle)
install(FILES ${PRP_PHYS_HEADERS} DESTINATION include/HSPlasma/PRP/Physics)
install(FILES ${PRP_REGION_HEADERS} DESTINATION include/HSPlasma/PRP/Region)
install(FILES ${PRP_SURFACE_HEADERS} DESTINATION include/HSPlasma/PRP/Surface)
install(FILES ${PRP_HEADERS} DESTINATION include/HSPlasma/PRP)
install(FILES ${RESMGR_HEADERS} DESTINATION include/HSPlasma/ResManager)
install(FILES ${SDL_HEADERS} DESTINATION include/HSPlasma/SDL)
install(FILES ${STREAM_HEADERS} DESTINATION include/HSPlasma/Stream)
install(FILES ${SYS_HEADERS} DESTINATION include/HSPlasma/Sys)
install(FILES ${UTIL_HEADERS} DESTINATION include/HSPlasma/Util)
install(FILES ${VAULT_HEADERS} DESTINATION include/HSPlasma/Vault)
install(FILES ${PLASMA_HEADERS} DESTINATION include/HSPlasma)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libhsplasma.pc DESTINATION lib/pkgconfig)

# Visual studio source grouping
source_group("Debug" FILES ${DEBUG_HEADERS} ${DEBUG_SOURCES})
source_group("Math" FILES ${MATH_HEADERS} ${MATH_SOURCES})
source_group("PRP\\Animation" FILES ${PRP_ANIM_HEADERS} ${PRP_ANIM_SOURCES})
source_group("PRP\\Audio" FILES ${PRP_AUDIO_HEADERS} ${PRP_AUDIO_SOURCES})
source_group("PRP\\Avatar" FILES ${PRP_AVATAR_HEADERS} ${PRP_AVATAR_SOURCES})
source_group("PRP\\Camera" FILES ${PRP_CAMERA_HEADERS} ${PRP_CAMERA_SOURCES})
source_group("PRP\\ConditionalObject" FILES ${PRP_COND_HEADERS} ${PRP_COND_SOURCES})
source_group("PRP\\Geometry" FILES ${PRP_GEOM_HEADERS} ${PRP_GEOM_SOURCES})
source_group("PRP\\GUI" FILES ${PRP_GUI_HEADERS} ${PRP_GUI_SOURCES})
source_group("PRP\\KeyedObject" FILES ${PRP_KEYOBJ_HEADERS} ${PRP_KEYOBJ_SOURCES})
source_group("PRP\\Light" FILES ${PRP_LIGHT_HEADERS} ${PRP_LIGHT_SOURCES})
source_group("PRP\\Message" FILES ${PRP_MSG_HEADERS} ${PRP_MSG_SOURCES})
source_group("PRP\\Misc" FILES ${PRP_MISC_HEADERS} ${PRP_MISC_SOURCES})
source_group("PRP\\Modifier" FILES ${PRP_MOD_HEADERS} ${PRP_MOD_SOURCES})
source_group("PRP\\NetMessage" FILES ${PRP_NETMSG_HEADERS} ${PRP_NETMSG_SOURCES})
source_group("PRP\\Object" FILES ${PRP_OBJ_HEADERS} ${PRP_OBJ_SOURCES})
source_group("PRP\\Particle" FILES ${PRP_PARTICLE_HEADERS} ${PRP_PARTICLE_SOURCES})
source_group("PRP\\Physics" FILES ${PRP_PHYS_HEADERS} ${PRP_PHYS_SOURCES})
source_group("PRP\\Region" FILES ${PRP_REGION_HEADERS} ${PRP_REGION_SOURCES})
source_group("PRP\\Surface" FILES ${PRP_SURFACE_HEADERS} ${PRP_SURFACE_SOURCES})
source_group("PRP" FILES ${PRP_HEADERS} ${PRP_SOURCES})
source_group("ResManager" FILES ${RESMGR_HEADERS} ${RESMGR_SOURCES})
source_group("SDL" FILES ${SDL_HEADERS} ${SDL_SOURCES})
source_group("Stream" FILES ${STREAM_HEADERS} ${STREAM_SOURCES})
source_group("Sys" FILES ${SYS_HEADERS} ${SYS_SOURCES})
source_group("Util" FILES ${UTIL_HEADERS} ${UTIL_SOURCES})
source_group("Vault" FILES ${VAULT_HEADERS} ${VAULT_SOURCES})
