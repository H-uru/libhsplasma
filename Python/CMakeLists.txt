find_package(PythonLibs REQUIRED)
find_package(PythonInterp "${PYTHONLIBS_VERSION_STRING}" REQUIRED)
# make sure the versions match
if (NOT "${PYTHONLIBS_VERSION_STRING}" STREQUAL "${PYTHON_VERSION_STRING}")
    message(FATAL_ERROR "Versions of Python libraries (${PYTHONLIBS_VERSION_STRING}) and Python interpreter (${PYTHON_VERSION_STRING}) do not match. Please configure the paths manually.")
endif()


if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
    set(CMAKE_CXX_FLAGS "-fno-strict-aliasing ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR}/core)
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(./)

set(DEBUG_SRCS
    Debug/pyDebug.cpp
)
set(DEBUG_HDRS
    Debug/pyDebug.h
)

set(MATH_SRCS
    Math/pyAffineParts.cpp
    Math/pyMatrix33.cpp
    Math/pyMatrix44.cpp
    Math/pyPlane3.cpp
    Math/pyQuat.cpp
    Math/pyVector3.cpp
)
set(MATH_HDRS
    Math/pyGeometry3.h
    Math/pyMatrix.h
)

set(PRP_ANIM_SRCS
    PRP/Animation/pyATCEaseCurve.cpp
    PRP/Animation/pyAnimTimeConvert.cpp
    PRP/Animation/pyCompoundController.cpp
    PRP/Animation/pyCompoundPosController.cpp
    PRP/Animation/pyCompoundRotController.cpp
    PRP/Animation/pyCompressedQuatKey32.cpp
    PRP/Animation/pyCompressedQuatKey64.cpp
    PRP/Animation/pyConstAccelEaseCurve.cpp
    PRP/Animation/pyController.cpp
    PRP/Animation/pyEaseController.cpp
    PRP/Animation/pyG3DSMaxKeyFrame.cpp
    PRP/Animation/pyKeyFrame.cpp
    PRP/Animation/pyLeafController.cpp
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
set(PRP_ANIM_HDRS
    PRP/Animation/pyATCEaseCurves.h
    PRP/Animation/pyAnimTimeConvert.h
    PRP/Animation/pyController.h
    PRP/Animation/pyKeys.h
    PRP/Animation/pyLeafController.h
    PRP/Animation/pyPosController.h
    PRP/Animation/pyRotController.h
    PRP/Animation/pyScaleController.h
    PRP/Animation/pyViewFaceModifier.h
)

set(PRP_AUD_SRCS
    PRP/Audio/py2WayWinAudible.cpp
    PRP/Audio/pyAudible.cpp
    PRP/Audio/pyAudibleNull.cpp
    PRP/Audio/pySoundBuffer.cpp
    PRP/Audio/pyWAVHeader.cpp
    PRP/Audio/pyWinAudible.cpp
)
set(PRP_AUD_HDRS
    PRP/Audio/pyAudible.h
    PRP/Audio/pySoundBuffer.h
)

set(PRP_AVTR_SRCS
    PRP/Avatar/pyAGAnim.cpp
    PRP/Avatar/pyAGAnimBink.cpp
    PRP/Avatar/pyAGApplicator.cpp
    PRP/Avatar/pyAGChannel.cpp
    PRP/Avatar/pyAGModifier.cpp
    PRP/Avatar/pyATCAnim.cpp
    PRP/Avatar/pyATCChannel.cpp
    PRP/Avatar/pyAgeGlobalAnim.cpp
    PRP/Avatar/pyAnimStage.cpp
    PRP/Avatar/pyClothingItem.cpp
    PRP/Avatar/pyEmoteAnim.cpp
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
    PRP/Avatar/pySittingModifier.cpp
    PRP/Avatar/pySoundVolumeApplicator.cpp
    PRP/Avatar/pySpotInnerApplicator.cpp
    PRP/Avatar/pySpotOuterApplicator.cpp
)
set(PRP_AVTR_HDRS
    PRP/Avatar/pyAGAnim.h
    PRP/Avatar/pyAGApplicator.h
    PRP/Avatar/pyAGChannel.h
    PRP/Avatar/pyAGModifier.h
    PRP/Avatar/pyATCAnim.h
    PRP/Avatar/pyMultistageBehMod.h
    PRP/Avatar/pySittingModifier.h
)

set(PRP_COND_SRCS
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
set(PRP_COND_HDRS
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

set(PRP_GEOM_SRCS
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
set(PRP_GEOM_HDRS
    PRP/Geometry/pyCluster.h
    PRP/Geometry/pyClusterGroup.h
    PRP/Geometry/pyDrawableSpans.h
    PRP/Geometry/pyGBufferGroup.h
    PRP/Geometry/pyGeometrySpan.h
    PRP/Geometry/pyOccluder.h
    PRP/Geometry/pySpaceTree.h
    PRP/Geometry/pySpan.h
    PRP/Geometry/pySpanInstance.h
    PRP/Geometry/pySpanTemplate.h
    PRP/Geometry/pyTempVertex.h
)

set(PRP_GUI_SRCS
    PRP/GUI/pyGUICloseDlgProc.cpp
    PRP/GUI/pyGUIConsoleCmdProc.cpp
    PRP/GUI/pyGUICtrlProcObject.cpp
    PRP/GUI/pyGUICtrlProcWriteableObject.cpp
    PRP/GUI/pyGUIDialogProc.cpp
    PRP/GUI/pyGUIPythonScriptProc.cpp
)
set(PRP_GUI_HDRS
    PRP/GUI/pyGUIControlHandlers.h
)

set(PRP_KEY_SRCS
    PRP/KeyedObject/pyKey.cpp
    PRP/KeyedObject/pyKeyedObject.cpp
    PRP/KeyedObject/pyKeyedObjectStub.cpp
    PRP/KeyedObject/pyLocation.cpp
)
set(PRP_KEY_HDRS
    PRP/KeyedObject/pyKey.h
    PRP/KeyedObject/pyKeyedObject.h
)

set(PRP_LIT_SRCS
    PRP/Light/pyDirectShadowMaster.cpp
    PRP/Light/pyDirectionalLightInfo.cpp
    PRP/Light/pyLightInfo.cpp
    PRP/Light/pyLimitedDirLightInfo.cpp
    PRP/Light/pyOmniLightInfo.cpp
    PRP/Light/pyPointShadowMaster.cpp
    PRP/Light/pyShadowMaster.cpp
    PRP/Light/pySpotLightInfo.cpp
)
set(PRP_LIT_HDRS
    PRP/Light/pyLightInfo.h
    PRP/Light/pyShadowMaster.h
)

set(PRP_MSG_SRCS
    PRP/Message/pyActivateEventData.cpp
    PRP/Message/pyArmatureEffectMsg.cpp
    PRP/Message/pyBookEventData.cpp
    PRP/Message/pyCallbackEventData.cpp
    PRP/Message/pyClickDragEventData.cpp
    PRP/Message/pyClimbingBlockerHitEventData.cpp
    PRP/Message/pyCollisionEventData.cpp
    PRP/Message/pyContainedEventData.cpp
    PRP/Message/pyControlKeyEventData.cpp
    PRP/Message/pyCoopEventData.cpp
    PRP/Message/pyCursorChangeMsg.cpp
    PRP/Message/pyEventCallbackMsg.cpp
    PRP/Message/pyEventData.cpp
    PRP/Message/pyFacingEventData.cpp
    PRP/Message/pyLinkToAgeMsg.cpp
    PRP/Message/pyMessage.cpp
    PRP/Message/pyMsgForwarder.cpp
    PRP/Message/pyMultiStageEventData.cpp
    PRP/Message/pyNotifyMsg.cpp
    PRP/Message/pyOfferLinkBookEventData.cpp
    PRP/Message/pyPickedEventData.cpp
    PRP/Message/pyResponderStateEventData.cpp
    PRP/Message/pySpawnedEventData.cpp
    PRP/Message/pyVariableEventData.cpp
)
set(PRP_MSG_HDRS
    PRP/Message/pyArmatureEffectMsg.h
    PRP/Message/pyCursorChangeMsg.h
    PRP/Message/pyEventCallbackMsg.h
    PRP/Message/pyEventData.h
    PRP/Message/pyLinkToAgeMsg.h
    PRP/Message/pyMessage.h
    PRP/Message/pyMsgForwarder.h
    PRP/Message/pyNotifyMsg.h
)

set(PRP_MISC_SRCS
    PRP/Misc/pyAgeLinkInfo.cpp
    PRP/Misc/pyRenderLevel.cpp
)
set(PRP_MISC_HDRS
    PRP/Misc/pyAgeLinkInfo.h
    PRP/Misc/pyRenderLevel.h
)

set(PRP_MOD_SRCS
    PRP/Modifier/pyInterfaceInfoModifier.cpp
    PRP/Modifier/pyLogicModBase.cpp
    PRP/Modifier/pyLogicModifier.cpp
    PRP/Modifier/pyMaintainersMarkerModifier.cpp
    PRP/Modifier/pyModifier.cpp
    PRP/Modifier/pyMultiModifier.cpp
    PRP/Modifier/pyOneShotMod.cpp
    PRP/Modifier/pyPythonFileMod.cpp
    PRP/Modifier/pyPythonParameter.cpp
    PRP/Modifier/pyResponderEnableMsg.cpp
    PRP/Modifier/pyResponderModifier.cpp
    PRP/Modifier/pyResponderModifier_Cmd.cpp
    PRP/Modifier/pyResponderModifier_State.cpp
    PRP/Modifier/pySingleModifier.cpp
    PRP/Modifier/pySpawnModifier.cpp
)
set(PRP_MOD_HDRS
    PRP/Modifier/pyInterfaceInfoModifier.h
    PRP/Modifier/pyLogicModifier.h
    PRP/Modifier/pyMaintainersMarkerModifier.h
    PRP/Modifier/pyModifier.h
    PRP/Modifier/pyOneShotMod.h
    PRP/Modifier/pyPythonFileMod.h
    PRP/Modifier/pyResponderModifier.h
    PRP/Modifier/pySpawnModifier.h
)

set(PRP_OBJ_SRCS
    PRP/Object/pyAudioInterface.cpp
    PRP/Object/pyCoordinateInterface.cpp
    PRP/Object/pyDrawInterface.cpp
    PRP/Object/pyObjInterface.cpp
    PRP/Object/pySceneObject.cpp
    PRP/Object/pySimulationInterface.cpp
    PRP/Object/pySynchedObject.cpp
)
set(PRP_OBJ_HDRS
    PRP/Object/pyObjInterface.h
    PRP/Object/pySceneObject.h
    PRP/Object/pySynchedObject.h
)

set(PRP_PHYS_SRCS
    PRP/Physics/pyCollisionDetector.cpp
    PRP/Physics/pyDetectorModifier.cpp
    PRP/Physics/pyGenericPhysical.cpp
    PRP/Physics/pyObjectInVolumeDetector.cpp
    PRP/Physics/pyObjectInVolumeAndFacingDetector.cpp
    PRP/Physics/pyPanicLinkRegion.cpp
    PRP/Physics/pyPhysical.cpp
    PRP/Physics/pyPickingDetector.cpp
    PRP/Physics/pySimDefs.cpp
    PRP/Physics/pySubworldRegionDetector.cpp
)
set(PRP_PHYS_HDRS
    PRP/Physics/pyCollisionDetector.h
    PRP/Physics/pyDetectorModifier.h
    PRP/Physics/pyObjectInVolumeDetector.h
    PRP/Physics/pyPhysical.h
)

set(PRP_RGN_SRCS
    PRP/Region/pyBounds.cpp
    PRP/Region/pyBounds3.cpp
    PRP/Region/pyBounds3Ext.cpp
    PRP/Region/pyBoundsOriented.cpp
)
set(PRP_RGN_HDRS
    PRP/Region/pyBounds.h
)

set(PRP_SRFC_SRCS
    PRP/Surface/pyBitmap.cpp
    PRP/Surface/pyCubicEnvironmap.cpp
    PRP/Surface/pyCubicRenderTarget.cpp
    PRP/Surface/pyDynamicCamMap.cpp
    PRP/Surface/pyDynamicEnvMap.cpp
    PRP/Surface/pyDynamicTextMap.cpp
    PRP/Surface/pyGMatState.cpp
    PRP/Surface/pyGMaterial.cpp
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
    PRP/Surface/pyRenderTarget.cpp
    PRP/Surface/pyShader.cpp
    PRP/Surface/pyShaderConst.cpp
)
set(PRP_SRFC_HDRS
    PRP/Surface/pyBitmap.h
    PRP/Surface/pyCubicEnvironmap.h
    PRP/Surface/pyDynamicEnvMap.h
    PRP/Surface/pyDynamicTextMap.h
    PRP/Surface/pyGMatState.h
    PRP/Surface/pyGMaterial.h
    PRP/Surface/pyLayer.h
    PRP/Surface/pyLayerAnimation.h
    PRP/Surface/pyLayerMovie.h
    PRP/Surface/pyRenderTarget.h
    PRP/Surface/pyShader.h
)

set(PRP_SRCS
    PRP/pyCreatable.cpp
    PRP/pyCreatableConvert.cpp
    PRP/pyCreatableStub.cpp
    PRP/pySceneNode.cpp
)
set(PRP_HDRS
    PRP/pyCreatable.h
    PRP/pySceneNode.h
)

set(RESMGR_SRCS
    ResManager/pyAgeInfo.cpp
    ResManager/pyFactory.cpp
    ResManager/pyPageInfo.cpp
    ResManager/pyResManager.cpp
)
set(RESMGR_HDRS
    ResManager/pyResManager.h
)

set(STREAM_SRCS
    Stream/pyEncryptedStream.cpp
    Stream/pyFileStream.cpp
    Stream/pyRAMStream.cpp
    Stream/pyStream.cpp
)
set(STREAM_HDRS
    Stream/pyStream.h
)

set(SYS_SRCS
    Sys/pyColor32.cpp
    Sys/pyColorRGBA.cpp
)
set(SYS_HDRS
    Sys/pyColor.h
)

set(UTIL_SRCS
    Util/pyBitVector.cpp
    Util/pyDDSurface.cpp
)
set(UTIL_HDRS
    Util/pyBitVector.h
    Util/pyDDSurface.h
)

set(PYTHON_SRCS
    Module.cpp
    PyPlasma.cpp
)
set(PYTHON_HDRS
    PyPlasma.h
)

add_library(PyHSPlasma SHARED
          ${DEBUG_SRCS}    ${DEBUG_HDRS}
          ${MATH_SRCS}     ${MATH_HDRS}
          ${PRP_ANIM_SRCS} ${PRP_ANIM_HDRS}
          ${PRP_AUD_SRCS}  ${PRP_AUD_HDRS}
          ${PRP_AVTR_SRCS} ${PRP_AVTR_HDRS}
          ${PRP_COND_SRCS} ${PRP_COND_HDRS}
          ${PRP_GEOM_SRCS} ${PRP_GEOM_HDRS}
          ${PRP_GUI_SRCS}  ${PRP_GUI_HDRS}
          ${PRP_KEY_SRCS}  ${PRP_KEY_HDRS}
          ${PRP_LIT_SRCS}  ${PRP_LIT_HDRS}
          ${PRP_MSG_SRCS}  ${PRP_MSG_HDRS}
          ${PRP_MISC_SRCS} ${PRP_MISC_HDRS}
          ${PRP_MOD_SRCS}  ${PRP_MOD_HDRS}
          ${PRP_OBJ_SRCS}  ${PRP_OBJ_HDRS}
          ${PRP_PHYS_SRCS} ${PRP_PHYS_HDRS}
          ${PRP_RGN_SRCS}  ${PRP_RGN_HDRS}
          ${PRP_SRFC_SRCS} ${PRP_SRFC_HDRS}
          ${PRP_SRCS}      ${PRP_HDRS}
          ${RESMGR_SRCS}   ${RESMGR_HDRS}
          ${STREAM_SRCS}   ${STREAM_HDRS}
          ${SYS_SRCS}      ${SYS_HDRS}
          ${UTIL_SRCS}     ${UTIL_HDRS}
          ${PYTHON_SRCS}   ${PYTHON_HDRS}
)

target_link_libraries(PyHSPlasma HSPlasma ${PYTHON_LIBRARIES})
set_target_properties(PyHSPlasma PROPERTIES PREFIX "")

if(NOT WIN32)
    set_target_properties(PyHSPlasma PROPERTIES
                          SUFFIX ".so"
    )

    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import sys, distutils.sysconfig; sys.stdout.write(distutils.sysconfig.get_python_lib())"
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
source_group("Debug" FILES ${DEBUG_HDRS} ${DEBUG_SRCS})
source_group("Math" FILES ${MATH_HDRS} ${MATH_SRCS})
source_group("PRP\\Animation" FILES ${PRP_ANIM_HDRS} ${PRP_ANIM_SRCS})
source_group("PRP\\Audio" FILES ${PRP_AUD_HDRS} ${PRP_AUD_SRCS})
source_group("PRP\\Avatar" FILES ${PRP_AVTR_HDRS} ${PRP_AVTR_SRCS})
source_group("PRP\\ConditionalObject" FILES ${PRP_COND_SRCS} ${PRP_COND_HDRS})
source_group("PRP\\Geometry" FILES ${PRP_GEOM_HDRS} ${PRP_GEOM_SRCS})
source_group("PRP\\GUI" FILES ${PRP_GUI_HDRS} ${PRP_GUI_SRCS})
source_group("PRP\\KeyedObject" FILES ${PRP_KEY_HDRS} ${PRP_KEY_SRCS})
source_group("PRP\\Light" FILES ${PRP_LIT_HDRS} ${PRP_LIT_SRCS})
source_group("PRP\\Message" FILES ${PRP_MSG_HDRS} ${PRP_MSG_SRCS})
source_group("PRP\\Misc" FILES ${PRP_MISC_HDRS} ${PRP_MISC_SRCS})
source_group("PRP\\Modifier" FILES ${PRP_MOD_HDRS} ${PRP_MOD_SRCS})
source_group("PRP\\Object" FILES ${PRP_OBJ_HDRS} ${PRP_OBJ_SRCS})
source_group("PRP\\Physics" FILES ${PRP_PHYS_HDRS} ${PRP_PHYS_SRCS})
source_group("PRP\\Region" FILES ${PRP_RGN_HDRS} ${PRP_RGN_SRCS})
source_group("PRP\\Surface" FILES ${PRP_SRFC_HDRS} ${PRP_SRFC_SRCS})
source_group("PRP" FILES ${PRP_HDRS} ${PRP_SRCS})
source_group("ResManager" FILES ${RESMGR_HDRS} ${RESMGR_SRCS})
source_group("SDL" FILES ${SDL_HDRS} ${SDL_SRCS})
source_group("Stream" FILES ${STREAM_HDRS} ${STREAM_SRCS})
source_group("Sys" FILES ${SYS_HDRS} ${SYS_SRCS})
source_group("Util" FILES ${UTIL_HDRS} ${UTIL_SRCS})
