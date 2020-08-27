find_package(PythonLibs REQUIRED)
# Use only the major.minor version -- no patch, no +, etc
STRING(REGEX REPLACE "([0-9]\\.[0-9])[0-9.+]*" "\\1" PYTHONLIBS_VERSION_STRING_FILTERED "${PYTHONLIBS_VERSION_STRING}")
find_package(PythonInterp "${PYTHONLIBS_VERSION_STRING_FILTERED}" REQUIRED)
# make sure the versions match
STRING(REGEX REPLACE "([0-9]\\.[0-9])[0-9.+]*" "\\1" PYTHON_VERSION_STRING_FILTERED "${PYTHON_VERSION_STRING}")
if (NOT "${PYTHONLIBS_VERSION_STRING_FILTERED}" STREQUAL "${PYTHON_VERSION_STRING_FILTERED}")
    message(FATAL_ERROR "Versions of Python libraries (${PYTHONLIBS_VERSION_STRING_FILTERED}) and Python interpreter (${PYTHON_VERSION_STRING_FILTERED}) do not match. Please configure the paths manually.")
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
    set(CMAKE_CXX_FLAGS "-fno-strict-aliasing ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 8.0)
        # GCC 8 adds a warning that prevents us from using Python's C API
        # in the "usual" way -- disable it for now.
        set(CMAKE_CXX_FLAGS "-Wno-cast-function-type ${CMAKE_CXX_FLAGS}")
        set(CMAKE_C_FLAGS "-Wno-cast-function-type ${CMAKE_C_FLAGS}")
    endif()
endif()

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(./)

set(DEBUG_SOURCES
    Debug/pyDebug.cpp
)
set(DEBUG_HEADERS
    Debug/pyDebug.h
)

set(MATH_SOURCES
    Math/pyAffineParts.cpp
    Math/pyMatrix33.cpp
    Math/pyMatrix44.cpp
    Math/pyPlane3.cpp
    Math/pyQuat.cpp
    Math/pyVector3.cpp
)
set(MATH_HEADERS
    Math/pyGeometry3.h
    Math/pyMatrix.h
)

set(PRP_ANIM_SOURCES
    PRP/Animation/pyATCEaseCurve.cpp
    PRP/Animation/pyAnimTimeConvert.cpp
    PRP/Animation/pyAnimPath.cpp
    PRP/Animation/pyCompoundController.cpp
    PRP/Animation/pyCompoundPosController.cpp
    PRP/Animation/pyCompoundRotController.cpp
    PRP/Animation/pyCompressedQuatKey32.cpp
    PRP/Animation/pyCompressedQuatKey64.cpp
    PRP/Animation/pyConstAccelEaseCurve.cpp
    PRP/Animation/pyController.cpp
    PRP/Animation/pyEaseController.cpp
    PRP/Animation/pyFilterCoordInterface.cpp
    PRP/Animation/pyG3DSMaxKeyFrame.cpp
    PRP/Animation/pyKeyFrame.cpp
    PRP/Animation/pyLeafController.cpp
    PRP/Animation/pyLineFollowMod.cpp
    PRP/Animation/pyMatrix33Controller.cpp
    PRP/Animation/pyMatrix33Key.cpp
    PRP/Animation/pyMatrix44Controller.cpp
    PRP/Animation/pyMatrix44Key.cpp
    PRP/Animation/pyPoint3Controller.cpp
    PRP/Animation/pyPoint3Key.cpp
    PRP/Animation/pyPosController.cpp
    PRP/Animation/pyQuatController.cpp
    PRP/Animation/pyQuatKey.cpp
    PRP/Animation/pyRotController.cpp
    PRP/Animation/pyScalarController.cpp
    PRP/Animation/pyScalarKey.cpp
    PRP/Animation/pyScaleController.cpp
    PRP/Animation/pyScaleKey.cpp
    PRP/Animation/pyScaleValueController.cpp
    PRP/Animation/pySimplePosController.cpp
    PRP/Animation/pySimpleRotController.cpp
    PRP/Animation/pySimpleScaleController.cpp
    PRP/Animation/pySplineEaseCurve.cpp
    PRP/Animation/pyTMController.cpp
    PRP/Animation/pyViewFaceModifier.cpp
)
set(PRP_ANIM_HEADERS
    PRP/Animation/pyATCEaseCurves.h
    PRP/Animation/pyAnimPath.h
    PRP/Animation/pyAnimTimeConvert.h
    PRP/Animation/pyController.h
    PRP/Animation/pyFilterCoordInterface.h
    PRP/Animation/pyKeys.h
    PRP/Animation/pyLeafController.h
    PRP/Animation/pyLineFollowMod.h
    PRP/Animation/pyPosController.h
    PRP/Animation/pyRotController.h
    PRP/Animation/pyScaleController.h
    PRP/Animation/pyViewFaceModifier.h
)

set(PRP_AUDIO_SOURCES
    PRP/Audio/py2WayWinAudible.cpp
    PRP/Audio/pyAudible.cpp
    PRP/Audio/pyAudibleNull.cpp
    PRP/Audio/pyFadeParams.cpp
    PRP/Audio/pySound.cpp
    PRP/Audio/pySoundBuffer.cpp
    PRP/Audio/pyWAVHeader.cpp
    PRP/Audio/pyWin32Sound.cpp
    PRP/Audio/pyWin32StaticSound.cpp
    PRP/Audio/pyWin32StreamingSound.cpp
    PRP/Audio/pyWinAudible.cpp
)
set(PRP_AUDIO_HEADERS
    PRP/Audio/pyAudible.h
    PRP/Audio/pySound.h
    PRP/Audio/pySoundBuffer.h
    PRP/Audio/pyWin32Sound.h
    PRP/Audio/pyWin32StaticSound.h
)

set(PRP_AVATAR_SOURCES
    PRP/Avatar/pyAGAnim.cpp
    PRP/Avatar/pyAGAnimBink.cpp
    PRP/Avatar/pyAGApplicator.cpp
    PRP/Avatar/pyAGChannel.cpp
    PRP/Avatar/pyAGMasterMod.cpp
    PRP/Avatar/pyAGModifier.cpp
    PRP/Avatar/pyATCAnim.cpp
    PRP/Avatar/pyATCChannel.cpp
    PRP/Avatar/pyAgeGlobalAnim.cpp
    PRP/Avatar/pyAnimStage.cpp
    PRP/Avatar/pyClothingItem.cpp
    PRP/Avatar/pyEmoteAnim.cpp
    PRP/Avatar/pyLadderModifier.cpp
    PRP/Avatar/pyLightAmbientApplicator.cpp
    PRP/Avatar/pyLightDiffuseApplicator.cpp
    PRP/Avatar/pyLightSpecularApplicator.cpp
    PRP/Avatar/pyMatrixBlend.cpp
    PRP/Avatar/pyMatrixChannel.cpp
    PRP/Avatar/pyMatrixChannelApplicator.cpp
    PRP/Avatar/pyMatrixConstant.cpp
    PRP/Avatar/pyMatrixControllerCacheChannel.cpp
    PRP/Avatar/pyMatrixControllerChannel.cpp
    PRP/Avatar/pyMatrixDelayedCorrectionApplicator.cpp
    PRP/Avatar/pyMatrixDifferenceApp.cpp
    PRP/Avatar/pyMatrixTimeScale.cpp
    PRP/Avatar/pyMultistageBehMod.cpp
    PRP/Avatar/pyOmniApplicator.cpp
    PRP/Avatar/pyOmniCutoffApplicator.cpp
    PRP/Avatar/pyOmniSqApplicator.cpp
    PRP/Avatar/pyPointBlend.cpp
    PRP/Avatar/pyPointChannel.cpp
    PRP/Avatar/pyPointChannelApplicator.cpp
    PRP/Avatar/pyPointConstant.cpp
    PRP/Avatar/pyPointControllerCacheChannel.cpp
    PRP/Avatar/pyPointControllerChannel.cpp
    PRP/Avatar/pyPointTimeScale.cpp
    PRP/Avatar/pyQuatBlend.cpp
    PRP/Avatar/pyQuatChannel.cpp
    PRP/Avatar/pyQuatChannelApplicator.cpp
    PRP/Avatar/pyQuatConstant.cpp
    PRP/Avatar/pyQuatPointCombine.cpp
    PRP/Avatar/pyQuatTimeScale.cpp
    PRP/Avatar/pyRelativeMatrixChannelApplicator.cpp
    PRP/Avatar/pyScalarBlend.cpp
    PRP/Avatar/pyScalarChannel.cpp
    PRP/Avatar/pyScalarChannelApplicator.cpp
    PRP/Avatar/pyScalarConstant.cpp
    PRP/Avatar/pyScalarControllerCacheChannel.cpp
    PRP/Avatar/pyScalarControllerChannel.cpp
    PRP/Avatar/pyScalarSDLChannel.cpp
    PRP/Avatar/pyScalarTimeScale.cpp
    PRP/Avatar/pySeekPointMod.cpp
    PRP/Avatar/pySittingModifier.cpp
    PRP/Avatar/pySoundVolumeApplicator.cpp
    PRP/Avatar/pySpotInnerApplicator.cpp
    PRP/Avatar/pySpotOuterApplicator.cpp
)
set(PRP_AVATAR_HEADERS
    PRP/Avatar/pyAGAnim.h
    PRP/Avatar/pyAGApplicator.h
    PRP/Avatar/pyAGChannel.h
    PRP/Avatar/pyAGMasterMod.h
    PRP/Avatar/pyAGModifier.h
    PRP/Avatar/pyATCAnim.h
    PRP/Avatar/pyLadderModifier.h
    PRP/Avatar/pyMultistageBehMod.h
    PRP/Avatar/pySeekPointMod.h
    PRP/Avatar/pySittingModifier.h
)

set(PRP_CAMERA_SOURCES
    PRP/Camera/pyCameraBrain.h
    PRP/Camera/pyCameraModifier.h
)

set(PRP_CAMERA_HEADERS
    PRP/Camera/pyCameraBrain.cpp
    PRP/Camera/pyCameraModifier.cpp
)

set(PRP_COND_SOURCES
    PRP/ConditionalObject/pyActivatorConditionalObject.cpp
    PRP/ConditionalObject/pyActivatorActivatorConditionalObject.cpp
    PRP/ConditionalObject/pyANDConditionalObject.cpp
    PRP/ConditionalObject/pyAnimationEventConditionalObject.cpp
    PRP/ConditionalObject/pyVolActivatorConditionalObject.cpp
    PRP/ConditionalObject/pyConditionalObject.cpp
    PRP/ConditionalObject/pyControlEventConditionalObject.cpp
    PRP/ConditionalObject/pyFacingConditionalObject.cpp
    PRP/ConditionalObject/pyKeyPressConditionalObject.cpp
    PRP/ConditionalObject/pyLocalPlayerInBoxConditionalObject.cpp
    PRP/ConditionalObject/pyLocalPlayerIntersectPlaneConditionalObject.cpp
    PRP/ConditionalObject/pyObjectInBoxConditionalObject.cpp
    PRP/ConditionalObject/pyObjectIntersectPlaneConditionalObject.cpp
    PRP/ConditionalObject/pyORConditionalObject.cpp
    PRP/ConditionalObject/pyVolumeSensorConditionalObject.cpp
    PRP/ConditionalObject/pyVolumeSensorConditionalObjectNoArbitration.cpp
)
set(PRP_COND_HEADERS
    PRP/ConditionalObject/pyActivatorConditionalObject.h
    PRP/ConditionalObject/pyAnimationEventConditionalObject.h
    PRP/ConditionalObject/pyBooleanConditionalObject.h
    PRP/ConditionalObject/pyConditionalObject.h
    PRP/ConditionalObject/pyControlEventConditionalObject.h
    PRP/ConditionalObject/pyDetectConditionalObjects.h
    PRP/ConditionalObject/pyFacingConditionalObject.h
    PRP/ConditionalObject/pyKeyPressConditionalObject.h
    PRP/ConditionalObject/pyVolumeSensorConditionalObject.h
)

set(PRP_GEOM_SOURCES
    PRP/Geometry/pyCluster.cpp
    PRP/Geometry/pyClusterGroup.cpp
    PRP/Geometry/pyCullPoly.cpp
    PRP/Geometry/pyDISpanIndex.cpp
    PRP/Geometry/pyDrawable.cpp
    PRP/Geometry/pyDrawableSpans.cpp
    PRP/Geometry/pyGBufferCell.cpp
    PRP/Geometry/pyGBufferGroup.cpp
    PRP/Geometry/pyGBufferTriangle.cpp
    PRP/Geometry/pyGBufferVertex.cpp
    PRP/Geometry/pyGeometrySpan.cpp
    PRP/Geometry/pyIcicle.cpp
    PRP/Geometry/pyLODDist.cpp
    PRP/Geometry/pyMobileOccluder.cpp
    PRP/Geometry/pyOccluder.cpp
    PRP/Geometry/pyParticleSpan.cpp
    PRP/Geometry/pySharedMesh.cpp
    PRP/Geometry/pySpaceTree.cpp
    PRP/Geometry/pySpaceTreeNode.cpp
    PRP/Geometry/pySpan.cpp
    PRP/Geometry/pySpanEncoding.cpp
    PRP/Geometry/pySpanInstance.cpp
    PRP/Geometry/pySpanTemplate.cpp
    PRP/Geometry/pySpanTemplateVertex.cpp
    PRP/Geometry/pyTempVertex.cpp
    PRP/Geometry/pyVertexSpan.cpp
)
set(PRP_GEOM_HEADERS
    PRP/Geometry/pyCluster.h
    PRP/Geometry/pyClusterGroup.h
    PRP/Geometry/pyDrawableSpans.h
    PRP/Geometry/pyGBufferGroup.h
    PRP/Geometry/pyGeometrySpan.h
    PRP/Geometry/pyOccluder.h
    PRP/Geometry/pySharedMesh.h
    PRP/Geometry/pySpaceTree.h
    PRP/Geometry/pySpan.h
    PRP/Geometry/pySpanConvert.cpp
    PRP/Geometry/pySpanInstance.h
    PRP/Geometry/pySpanTemplate.h
    PRP/Geometry/pyTempVertex.h
)

set(PRP_GUI_SOURCES
    PRP/GUI/pyGUIButtonMod.cpp
    PRP/GUI/pyGUICheckBoxCtrl.cpp
    PRP/GUI/pyGUICloseDlgProc.cpp
    PRP/GUI/pyGUIConsoleCmdProc.cpp
    PRP/GUI/pyGUIControlMod.cpp
    PRP/GUI/pyGUICtrlProcConvert.cpp
    PRP/GUI/pyGUICtrlProcObject.cpp
    PRP/GUI/pyGUICtrlProcWriteableObject.cpp
    PRP/GUI/pyGUIDialogMod.cpp
    PRP/GUI/pyGUIDialogProc.cpp
    PRP/GUI/pyGUIDynDisplayCtrl.cpp
    PRP/GUI/pyGUIKnobCtrl.cpp
    PRP/GUI/pyGUIListBoxMod.cpp
    PRP/GUI/pyGUIMisc.cpp
    PRP/GUI/pyGUIMultiLineEditCtrl.cpp
    PRP/GUI/pyGUIPopUpMenu.cpp
    PRP/GUI/pyGUIProgressCtrl.cpp
    PRP/GUI/pyGUIPythonScriptProc.cpp
    PRP/GUI/pyGUIRadioGroupCtrl.cpp
    PRP/GUI/pyGUISkin.cpp
    PRP/GUI/pyGUITextBoxMod.cpp
    PRP/GUI/pyGUIUpDownPairMod.cpp
    PRP/GUI/pyGUIValueCtrl.cpp
    PRP/GUI/pyImageLibMod.cpp
)
set(PRP_GUI_HEADERS
    PRP/GUI/pyGUIButtonMod.h
    PRP/GUI/pyGUIControlHandlers.h
    PRP/GUI/pyGUICheckBoxCtrl.h
    PRP/GUI/pyGUIControlMod.h
    PRP/GUI/pyGUIDialogMod.h
    PRP/GUI/pyGUIDynDisplayCtrl.h
    PRP/GUI/pyGUIKnobCtrl.h
    PRP/GUI/pyGUIListBoxMod.h
    PRP/GUI/pyGUIMisc.h
    PRP/GUI/pyGUIMultiLineEditCtrl.h
    PRP/GUI/pyGUIPopUpMenu.h
    PRP/GUI/pyGUIProgressCtrl.h
    PRP/GUI/pyGUIRadioGroupCtrl.h
    PRP/GUI/pyGUISkin.h
    PRP/GUI/pyGUITextBoxMod.h
    PRP/GUI/pyGUIUpDownPairMod.h
    PRP/GUI/pyGUIValueCtrl.h
    PRP/GUI/pyImageLibMod.h
)

set(PRP_KEYOBJ_SOURCES
    PRP/KeyedObject/pyKey.cpp
    PRP/KeyedObject/pyKeyedObject.cpp
    PRP/KeyedObject/pyKeyedObjectStub.cpp
    PRP/KeyedObject/pyLocation.cpp
)
set(PRP_KEYOBJ_HEADERS
    PRP/KeyedObject/pyKey.h
    PRP/KeyedObject/pyKeyedObject.h
)

set(PRP_LIGHT_SOURCES
    PRP/Light/pyDirectShadowMaster.cpp
    PRP/Light/pyDirectionalLightInfo.cpp
    PRP/Light/pyLightInfo.cpp
    PRP/Light/pyLimitedDirLightInfo.cpp
    PRP/Light/pyOmniLightInfo.cpp
    PRP/Light/pyPointShadowMaster.cpp
    PRP/Light/pyShadowCaster.cpp
    PRP/Light/pyShadowMaster.cpp
    PRP/Light/pySpotLightInfo.cpp
)
set(PRP_LIGHT_HEADERS
    PRP/Light/pyLightInfo.h
    PRP/Light/pyShadowCaster.h
    PRP/Light/pyShadowMaster.h
)

set(PRP_MSG_SOURCES
    PRP/Message/pyActivateEventData.cpp
    PRP/Message/pyAnimCmdMsg.cpp
    PRP/Message/pyArmatureEffectMsg.cpp
    PRP/Message/pyBookEventData.cpp
    PRP/Message/pyCallbackEventData.cpp
    PRP/Message/pyCameraMsg.cpp
    PRP/Message/pyClickDragEventData.cpp
    PRP/Message/pyClimbingBlockerHitEventData.cpp
    PRP/Message/pyCollisionEventData.cpp
    PRP/Message/pyContainedEventData.cpp
    PRP/Message/pyControlKeyEventData.cpp
    PRP/Message/pyCoopEventData.cpp
    PRP/Message/pyCursorChangeMsg.cpp
    PRP/Message/pyEnableMsg.cpp
    PRP/Message/pyEventCallbackMsg.cpp
    PRP/Message/pyEventData.cpp
    PRP/Message/pyEventDataConvert.cpp
    PRP/Message/pyExcludeRegionMsg.cpp
    PRP/Message/pyFacingEventData.cpp
    PRP/Message/pyLinkToAgeMsg.cpp
    PRP/Message/pyMessage.cpp
    PRP/Message/pyMessageWithCallbacks.cpp
    PRP/Message/pyMsgForwarder.cpp
    PRP/Message/pyMultiStageEventData.cpp
    PRP/Message/pyNotifyMsg.cpp
    PRP/Message/pyOfferLinkBookEventData.cpp
    PRP/Message/pyOneShotMsg.cpp
    PRP/Message/pyPickedEventData.cpp
    PRP/Message/pyResponderMsg.cpp
    PRP/Message/pyResponderStateEventData.cpp
    PRP/Message/pyRideAnimatedPhysMsg.cpp
    PRP/Message/pySimSuppressMsg.cpp
    PRP/Message/pySimulationMsg.cpp
    PRP/Message/pySoundMsg.cpp
    PRP/Message/pySpawnedEventData.cpp
    PRP/Message/pySubWorldMsg.cpp
    PRP/Message/pySwimMsg.cpp
    PRP/Message/pyTimerCallbackMsg.cpp
    PRP/Message/pyWarpMsg.cpp
    PRP/Message/pyVariableEventData.cpp
)
set(PRP_MSG_HEADERS
    PRP/Message/pyAnimCmdMsg.h
    PRP/Message/pyArmatureEffectMsg.h
    PRP/Message/pyCameraMsg.h
    PRP/Message/pyCursorChangeMsg.h
    PRP/Message/pyEnableMsg.h
    PRP/Message/pyEventCallbackMsg.h
    PRP/Message/pyEventData.h
    PRP/Message/pyExcludeRegionMsg.h
    PRP/Message/pyLinkToAgeMsg.h
    PRP/Message/pyMessage.h
    PRP/Message/pyMessageWithCallbacks.h
    PRP/Message/pyMsgForwarder.h
    PRP/Message/pyNotifyMsg.h
    PRP/Message/pyRideAnimatedPhysMsg.h
    PRP/Message/pySimulationMsg.h
    PRP/Message/pySoundMsg.h
    PRP/Message/pySwimMsg.h
    PRP/Message/pyResponderMsg.h
    PRP/Message/pyTimerCallbackMsg.h
    PRP/Message/pyWarpMsg.h
)

set(PRP_MISC_SOURCES
    PRP/Misc/pyAgeLinkEffects.cpp
    PRP/Misc/pyAgeInfoStruct.cpp
    PRP/Misc/pyAgeLinkStruct.cpp
    PRP/Misc/pyFogEnvironment.cpp
    PRP/Misc/pyRenderLevel.cpp
    PRP/Misc/pySpawnPointInfo.cpp
)
set(PRP_MISC_HEADERS
    PRP/Misc/pyAgeLinkInfo.h
    PRP/Misc/pyFogEnvironment.h
    PRP/Misc/pyRenderLevel.h
    PRP/Misc/pySpawnPointInfo.h
)

set(PRP_MOD_SOURCES
    PRP/Modifier/pyExcludeRegionModifier.cpp
    PRP/Modifier/pyFollowMod.cpp
    PRP/Modifier/pyInterfaceInfoModifier.cpp
    PRP/Modifier/pyLogicModBase.cpp
    PRP/Modifier/pyLogicModifier.cpp
    PRP/Modifier/pyMaintainersMarkerModifier.cpp
    PRP/Modifier/pyModifier.cpp
    PRP/Modifier/pyMultiModifier.cpp
    PRP/Modifier/pyOneShotMod.cpp
    PRP/Modifier/pyPostEffectMod.cpp
    PRP/Modifier/pyPythonFileMod.cpp
    PRP/Modifier/pyPythonParameter.cpp
    PRP/Modifier/pyResponderEnableMsg.cpp
    PRP/Modifier/pyResponderModifier.cpp
    PRP/Modifier/pyResponderModifier_Cmd.cpp
    PRP/Modifier/pyResponderModifier_State.cpp
    PRP/Modifier/pySingleModifier.cpp
    PRP/Modifier/pySpawnModifier.cpp
)
set(PRP_MOD_HEADERS
    PRP/Modifier/pyExcludeRegionModifier.h
    PRP/Modifier/pyFollowMod.h
    PRP/Modifier/pyInterfaceInfoModifier.h
    PRP/Modifier/pyLogicModifier.h
    PRP/Modifier/pyMaintainersMarkerModifier.h
    PRP/Modifier/pyModifier.h
    PRP/Modifier/pyOneShotMod.h
    PRP/Modifier/pyPostEffectMod.h
    PRP/Modifier/pyPythonFileMod.h
    PRP/Modifier/pyResponderModifier.h
    PRP/Modifier/pySpawnModifier.h
)

set(PRP_OBJ_SOURCES
    PRP/Object/pyAudioInterface.cpp
    PRP/Object/pyCoordinateInterface.cpp
    PRP/Object/pyDrawInterface.cpp
    PRP/Object/pyObjInterface.cpp
    PRP/Object/pySceneObject.cpp
    PRP/Object/pySimulationInterface.cpp
    PRP/Object/pySynchedObject.cpp
)
set(PRP_OBJ_HEADERS
    PRP/Object/pyObjInterface.h
    PRP/Object/pySceneObject.h
    PRP/Object/pySynchedObject.h
)

set(PRP_PARTICLE_SOURCES
    PRP/Particle/pyBoundInterface.cpp
    PRP/Particle/pyOneTimeParticleGenerator.cpp
    PRP/Particle/pyParticleApplicator.cpp
    PRP/Particle/pyParticleCollisionEffect.cpp
    PRP/Particle/pyParticleEffect.cpp
    PRP/Particle/pyParticleEmitter.cpp
    PRP/Particle/pyParticleFadeEffect.cpp
    PRP/Particle/pyParticleFlockEffect.cpp
    PRP/Particle/pyParticleGenerator.cpp
    PRP/Particle/pyParticleSystem.cpp
    PRP/Particle/pyParticleWindEffect.cpp
    PRP/Particle/pySimpleParticleGenerator.cpp
)
set(PRP_PARTICLE_HEADERS
    PRP/Particle/pyBoundInterface.h
    PRP/Particle/pyParticleApplicator.h
    PRP/Particle/pyParticleEffect.h
    PRP/Particle/pyParticleEmitter.h
    PRP/Particle/pyParticleGenerator.h
    PRP/Particle/pyParticleSystem.h
)

set(PRP_PHYS_SOURCES
    PRP/Physics/pyCameraRegionDetector.cpp
    PRP/Physics/pyCollisionDetector.cpp
    PRP/Physics/pyDetectorModifier.cpp
    PRP/Physics/pyGenericPhysical.cpp
    PRP/Physics/pyHKSubWorld.cpp
    PRP/Physics/pyObjectInVolumeDetector.cpp
    PRP/Physics/pyObjectInVolumeAndFacingDetector.cpp
    PRP/Physics/pyPanicLinkRegion.cpp
    PRP/Physics/pyPhysical.cpp
    PRP/Physics/pyPickingDetector.cpp
    PRP/Physics/pySimDefs.cpp
    PRP/Physics/pySubworldRegionDetector.cpp
)
set(PRP_PHYS_HEADERS
    PRP/Physics/pyCollisionDetector.h
    PRP/Physics/pyDetectorModifier.h
    PRP/Physics/pyHKSubWorld.h
    PRP/Physics/pyObjectInVolumeDetector.h
    PRP/Physics/pyPhysical.h
)

set(PRP_REGION_SOURCES
    PRP/Region/pyBounds.cpp
    PRP/Region/pyBounds3.cpp
    PRP/Region/pyBounds3Ext.cpp
    PRP/Region/pyBoundsOriented.cpp
    PRP/Region/pyBoundsConvert.cpp
    PRP/Region/pyConvexIsect.cpp
    PRP/Region/pyConvexVolume.cpp
    PRP/Region/pyRidingAnimatedPhysicalDetector.cpp
    PRP/Region/pySimpleRegionSensor.cpp
    PRP/Region/pySoftVolumeComplex.cpp
    PRP/Region/pySoftVolumeIntersect.cpp
    PRP/Region/pySoftVolumeInvert.cpp
    PRP/Region/pySoftVolumeSimple.cpp
    PRP/Region/pySoftVolumeUnion.cpp
    PRP/Region/pySoftVolume.cpp
    PRP/Region/pySwimCircularCurrentRegion.cpp
    PRP/Region/pySwimDetector.cpp
    PRP/Region/pySwimRegionInterface.cpp
    PRP/Region/pySwimStraightCurrentRegion.cpp
    PRP/Region/pyVisRegion.cpp
    PRP/Region/pyVolumeIsect.cpp
)
set(PRP_REGION_HEADERS
    PRP/Region/pyBounds.h
    PRP/Region/pyConvexVolume.h
    PRP/Region/pySimpleRegionSensor.h
    PRP/Region/pySoftVolume.h
    PRP/Region/pySwimRegion.h
    PRP/Region/pyVisRegion.h
    PRP/Region/pyVolumeIsect.h
)

set(PRP_SURFACE_SOURCES
    PRP/Surface/pyActivePrintShape.cpp
    PRP/Surface/pyBitmap.cpp
    PRP/Surface/pyCubicEnvironmap.cpp
    PRP/Surface/pyCubicRenderTarget.cpp
    PRP/Surface/pyDistOpacityMod.cpp
    PRP/Surface/pyDynaBulletMgr.cpp
    PRP/Surface/pyDynaDecalMgr.cpp
    PRP/Surface/pyDynaFootMgr.cpp
    PRP/Surface/pyDynaPuddleMgr.cpp
    PRP/Surface/pyDynaRippleMgr.cpp
    PRP/Surface/pyDynaRippleVSMgr.cpp
    PRP/Surface/pyDynaTorpedoMgr.cpp
    PRP/Surface/pyDynaTorpedoVSMgr.cpp
    PRP/Surface/pyDynaWakeMgr.cpp
    PRP/Surface/pyDynamicCamMap.cpp
    PRP/Surface/pyDynamicEnvMap.cpp
    PRP/Surface/pyDynamicTextMap.cpp
    PRP/Surface/pyFadeOpacityMod.cpp
    PRP/Surface/pyFixedWaterState7.cpp
    PRP/Surface/pyFont.cpp
    PRP/Surface/pyGMatState.cpp
    PRP/Surface/pyGMaterial.cpp
    PRP/Surface/pyGrassShaderMod.cpp
    PRP/Surface/pyGrassWave.cpp
    PRP/Surface/pyLayer.cpp
    PRP/Surface/pyLayerAVI.cpp
    PRP/Surface/pyLayerAnimation.cpp
    PRP/Surface/pyLayerAnimationBase.cpp
    PRP/Surface/pyLayerBink.cpp
    PRP/Surface/pyLayerDepth.cpp
    PRP/Surface/pyLayerInterface.cpp
    PRP/Surface/pyLayerLinkAnimation.cpp
    PRP/Surface/pyLayerMovie.cpp
    PRP/Surface/pyLayerSDLAnimation.cpp
    PRP/Surface/pyMipmap.cpp
    PRP/Surface/pyPrintShape.cpp
    PRP/Surface/pyRenderTarget.cpp
    PRP/Surface/pyShader.cpp
    PRP/Surface/pyShaderConst.cpp
    PRP/Surface/pyWaveSet7.cpp
    PRP/Surface/pyWaveSetBase.cpp
    PRP/Surface/pyWaveState7.cpp
)
set(PRP_SURFACE_HEADERS
    PRP/Surface/pyBitmap.h
    PRP/Surface/pyCubicEnvironmap.h
    PRP/Surface/pyDistOpacityMod.h
    PRP/Surface/pyDynaDecalMgr.h
    PRP/Surface/pyDynaRippleMgr.h
    PRP/Surface/pyDynamicEnvMap.h
    PRP/Surface/pyDynamicTextMap.h
    PRP/Surface/pyFadeOpacityMod.h
    PRP/Surface/pyFixedWaterState7.h
    PRP/Surface/pyFont.h
    PRP/Surface/pyGMatState.h
    PRP/Surface/pyGMaterial.h
    PRP/Surface/pyGrassShaderMod.h
    PRP/Surface/pyLayer.h
    PRP/Surface/pyLayerAnimation.h
    PRP/Surface/pyLayerMovie.h
    PRP/Surface/pyPrintShape.h
    PRP/Surface/pyRenderTarget.h
    PRP/Surface/pyShader.h
    PRP/Surface/pyWaveSet.h
)

set(PRP_SOURCES
    PRP/pyCreatable.cpp
    PRP/pyCreatableConvert.cpp
    PRP/pyCreatableStub.cpp
    PRP/pySceneNode.cpp
)
set(PRP_HEADERS
    PRP/pyCreatable.h
    PRP/pySceneNode.h
)

set(RESMGR_SOURCES
    ResManager/pyAgeInfo.cpp
    ResManager/pyFactory.cpp
    ResManager/pyPageInfo.cpp
    ResManager/pyResManager.cpp
)
set(RESMGR_HEADERS
    ResManager/pyResManager.h
)

set(SDL_SOURCES
    SDL/pyStateDescriptor.cpp
    SDL/pySDLMgr.cpp
    SDL/pyVarDescriptor.cpp
)
set(SDL_HEADERS
    SDL/pySDL.h
)

set(STREAM_SOURCES
    Stream/pyEncryptedStream.cpp
    Stream/pyFileStream.cpp
    Stream/pyPrcHelper.cpp
    Stream/pyRAMStream.cpp
    Stream/pyStream.cpp
)
set(STREAM_HEADERS
    Stream/pyPrcHelper.h
    Stream/pyStream.h
)

set(SYS_SOURCES
    Sys/pyColor32.cpp
    Sys/pyColorRGBA.cpp
    Sys/pyUnifiedTime.cpp
)
set(SYS_HEADERS
    Sys/pyColor.h
    Sys/pyUnifiedTime.h
)

set(UTIL_SOURCES
    Util/pyBitVector.cpp
    Util/pyDDSurface.cpp
)
set(UTIL_HEADERS
    Util/pyBitVector.h
    Util/pyDDSurface.h
)

set(VAULT_SOURCES
    Vault/pyServerGuid.cpp
    Vault/pyVault.cpp
    Vault/pyVaultNode.cpp
    Vault/pyVaultPlayerNode.cpp
    Vault/pyVaultAgeNode.cpp
    Vault/pyVaultGameServerNode.cpp
    Vault/pyVaultAdminNode.cpp
    Vault/pyVaultServerNode.cpp
    Vault/pyVaultFolderNode.cpp
    Vault/pyVaultPlayerInfoNode.cpp
    Vault/pyVaultSystemNode.cpp
    Vault/pyVaultImageNode.cpp
    Vault/pyVaultTextNoteNode.cpp
    Vault/pyVaultSDLNode.cpp
    Vault/pyVaultAgeLinkNode.cpp
    Vault/pyVaultChronicleNode.cpp
    Vault/pyVaultPlayerInfoListNode.cpp
    Vault/pyVaultMarkerNode.cpp
    Vault/pyVaultAgeInfoNode.cpp
    Vault/pyVaultAgeInfoListNode.cpp
    Vault/pyVaultMarkerListNode.cpp
    Vault/pyVaultStore.cpp
)
set(VAULT_HEADERS
    Vault/pyServerGuid.h
    Vault/pyVaultNode.h
    Vault/pyVaultStore.h
)

set(PYTHON_SOURCES
    Module.cpp
    PyPlasma.cpp
)
set(PYTHON_HEADERS
    PyPlasma.h
)

add_library(PyHSPlasma SHARED
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
            ${PRP_MSG_SOURCES}      ${PRP_MSG_HEADERS}
            ${PRP_MISC_SOURCES}     ${PRP_MISC_HEADERS}
            ${PRP_MOD_SOURCES}      ${PRP_MOD_HEADERS}
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
            ${PYTHON_SOURCES}       ${PYTHON_HEADERS}
)

target_link_libraries(PyHSPlasma HSPlasma ${PYTHON_LIBRARIES})
set_target_properties(PyHSPlasma PROPERTIES PREFIX "")

if(NOT WIN32)
    set_target_properties(PyHSPlasma PROPERTIES
                          SUFFIX ".so"
    )

    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import sys, distutils.sysconfig; sys.stdout.write(distutils.sysconfig.get_python_lib(prefix='${CMAKE_INSTALL_PREFIX}'))"
                    OUTPUT_VARIABLE _PYTHON_LIB_DIR
    )
    install(TARGETS PyHSPlasma
            DESTINATION ${_PYTHON_LIB_DIR}
    )
else()
    set_target_properties(PyHSPlasma PROPERTIES
                          SUFFIX ".pyd"
    )

    install(TARGETS PyHSPlasma
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
    )
endif()

#Visual studio source grouping
source_group("Debug" FILES ${DEBUG_HEADERS} ${DEBUG_SOURCES})
source_group("Math" FILES ${MATH_HEADERS} ${MATH_SOURCES})
source_group("PRP\\Animation" FILES ${PRP_ANIM_HEADERS} ${PRP_ANIM_SOURCES})
source_group("PRP\\Audio" FILES ${PRP_AUDIO_HEADERS} ${PRP_AUDIO_SOURCES})
source_group("PRP\\Avatar" FILES ${PRP_AVATAR_HEADERS} ${PRP_AVATAR_SOURCES})
source_group("PRP\\Camera" FILES ${PRP_CAMERA_SOURCES} ${PRP_CAMERA_HEADERS})
source_group("PRP\\ConditionalObject" FILES ${PRP_COND_HEADERS} ${PRP_COND_SOURCES})
source_group("PRP\\Geometry" FILES ${PRP_GEOM_HEADERS} ${PRP_GEOM_SOURCES})
source_group("PRP\\GUI" FILES ${PRP_GUI_HEADERS} ${PRP_GUI_SOURCES})
source_group("PRP\\KeyedObject" FILES ${PRP_KEYOBJ_HEADERS} ${PRP_KEYOBJ_SOURCES})
source_group("PRP\\Light" FILES ${PRP_LIGHT_HEADERS} ${PRP_LIGHT_SOURCES})
source_group("PRP\\Message" FILES ${PRP_MSG_HEADERS} ${PRP_MSG_SOURCES})
source_group("PRP\\Misc" FILES ${PRP_MISC_HEADERS} ${PRP_MISC_SOURCES})
source_group("PRP\\Modifier" FILES ${PRP_MOD_HEADERS} ${PRP_MOD_SOURCES})
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
