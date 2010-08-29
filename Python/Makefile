include ../config.mf

CXXFLAGS += -I../core -I. $(PYTHON_FLAGS) -Wno-write-strings
CXXLINK  += -L../lib -lHSPlasma $(PYTHON_LIBS)
OBJDIR=out/

PYOBJ=\
	$(OBJDIR)Module.o \
	$(OBJDIR)PyPlasma.o \
	$(OBJDIR)pyDebug.o \
	$(OBJDIR)pyAffineParts.o \
	$(OBJDIR)pyMatrix33.o \
	$(OBJDIR)pyMatrix44.o \
	$(OBJDIR)pyPlane3.o \
	$(OBJDIR)pyQuat.o \
	$(OBJDIR)pyVector3.o \
	$(OBJDIR)pyCreatable.o \
	$(OBJDIR)pyCreatableConvert.o \
	$(OBJDIR)pyCreatableStub.o \
	$(OBJDIR)pyAnimTimeConvert.o \
	$(OBJDIR)pyATCEaseCurve.o \
	$(OBJDIR)pyCompoundController.o \
	$(OBJDIR)pyCompoundPosController.o \
	$(OBJDIR)pyCompoundRotController.o \
	$(OBJDIR)pyCompressedQuatKey32.o \
	$(OBJDIR)pyCompressedQuatKey64.o \
	$(OBJDIR)pyConstAccelEaseCurve.o \
	$(OBJDIR)pyController.o \
	$(OBJDIR)pyEaseController.o \
	$(OBJDIR)pyG3DSMaxKeyFrame.o \
	$(OBJDIR)pyKeyFrame.o \
	$(OBJDIR)pyLeafController.o \
	$(OBJDIR)pyMatrix33Controller.o \
	$(OBJDIR)pyMatrix33Key.o \
	$(OBJDIR)pyMatrix44Controller.o \
	$(OBJDIR)pyMatrix44Key.o \
	$(OBJDIR)pyPoint3Controller.o \
	$(OBJDIR)pyPoint3Key.o \
	$(OBJDIR)pyPosController.o \
	$(OBJDIR)pyQuatController.o \
	$(OBJDIR)pyQuatKey.o \
	$(OBJDIR)pyRotController.o \
	$(OBJDIR)pyScalarController.o \
	$(OBJDIR)pyScalarKey.o \
	$(OBJDIR)pyScaleController.o \
	$(OBJDIR)pyScaleKey.o \
	$(OBJDIR)pyScaleValueController.o \
	$(OBJDIR)pySimplePosController.o \
	$(OBJDIR)pySimpleRotController.o \
	$(OBJDIR)pySimpleScaleController.o \
	$(OBJDIR)pySplineEaseCurve.o \
	$(OBJDIR)pyTMController.o \
	$(OBJDIR)pyViewFaceModifier.o \
	$(OBJDIR)pyAGAnim.o \
	$(OBJDIR)pyAGAnimBink.o \
	$(OBJDIR)pyAGApplicator.o \
	$(OBJDIR)pyAGChannel.o \
	$(OBJDIR)pyAgeGlobalAnim.o \
	$(OBJDIR)pyAnimStage.o \
	$(OBJDIR)pyATCAnim.o \
	$(OBJDIR)pyATCChannel.o \
	$(OBJDIR)pyEmoteAnim.o \
	$(OBJDIR)pyMatrixBlend.o \
	$(OBJDIR)pyMatrixChannel.o \
	$(OBJDIR)pyMatrixChannelApplicator.o \
	$(OBJDIR)pyMatrixConstant.o \
	$(OBJDIR)pyMatrixControllerCacheChannel.o \
	$(OBJDIR)pyMatrixControllerChannel.o \
	$(OBJDIR)pyMatrixDelayedCorrectionApplicator.o \
	$(OBJDIR)pyMatrixDifferenceApp.o \
	$(OBJDIR)pyMatrixTimeScale.o \
	$(OBJDIR)pyMultistageBehMod.o \
	$(OBJDIR)pyLightAmbientApplicator.o \
	$(OBJDIR)pyLightDiffuseApplicator.o \
	$(OBJDIR)pyLightSpecularApplicator.o \
	$(OBJDIR)pyOmniApplicator.o \
	$(OBJDIR)pyOmniCutoffApplicator.o \
	$(OBJDIR)pyOmniSqApplicator.o \
	$(OBJDIR)pyPointBlend.o \
	$(OBJDIR)pyPointChannel.o \
	$(OBJDIR)pyPointChannelApplicator.o \
	$(OBJDIR)pyPointConstant.o \
	$(OBJDIR)pyPointControllerCacheChannel.o \
	$(OBJDIR)pyPointControllerChannel.o \
	$(OBJDIR)pyPointTimeScale.o \
	$(OBJDIR)pyQuatBlend.o \
	$(OBJDIR)pyQuatChannel.o \
	$(OBJDIR)pyQuatChannelApplicator.o \
	$(OBJDIR)pyQuatConstant.o \
	$(OBJDIR)pyQuatPointCombine.o \
	$(OBJDIR)pyQuatTimeScale.o \
	$(OBJDIR)pyRelativeMatrixChannelApplicator.o \
	$(OBJDIR)pyScalarBlend.o \
	$(OBJDIR)pyScalarChannel.o \
	$(OBJDIR)pyScalarChannelApplicator.o \
	$(OBJDIR)pyScalarConstant.o \
	$(OBJDIR)pyScalarControllerCacheChannel.o \
	$(OBJDIR)pyScalarControllerChannel.o \
	$(OBJDIR)pyScalarTimeScale.o \
	$(OBJDIR)pyScalarSDLChannel.o \
	$(OBJDIR)pySoundVolumeApplicator.o \
	$(OBJDIR)pySpotInnerApplicator.o \
	$(OBJDIR)pySpotOuterApplicator.o \
	$(OBJDIR)pySceneNode.o \
	$(OBJDIR)py2WayWinAudible.o \
	$(OBJDIR)pyAudible.o \
	$(OBJDIR)pyAudibleNull.o \
	$(OBJDIR)pySoundBuffer.o \
	$(OBJDIR)pyWAVHeader.o \
	$(OBJDIR)pyWinAudible.o \
	$(OBJDIR)pyCluster.o \
	$(OBJDIR)pyClusterGroup.o \
	$(OBJDIR)pyCullPoly.o \
	$(OBJDIR)pyDISpanIndex.o \
	$(OBJDIR)pyDrawable.o \
	$(OBJDIR)pyDrawableSpans.o \
	$(OBJDIR)pyGBufferCell.o \
	$(OBJDIR)pyGBufferGroup.o \
	$(OBJDIR)pyGBufferTriangle.o \
	$(OBJDIR)pyGBufferVertex.o \
	$(OBJDIR)pyIcicle.o \
	$(OBJDIR)pyLODDist.o \
	$(OBJDIR)pyMobileOccluder.o \
	$(OBJDIR)pyOccluder.o \
	$(OBJDIR)pyParticleSpan.o \
	$(OBJDIR)pySpaceTree.o \
	$(OBJDIR)pySpaceTreeNode.o \
	$(OBJDIR)pySpan.o \
	$(OBJDIR)pySpanEncoding.o \
	$(OBJDIR)pySpanInstance.o \
	$(OBJDIR)pySpanTemplate.o \
	$(OBJDIR)pySpanTemplateVertex.o \
	$(OBJDIR)pyVertexSpan.o \
	$(OBJDIR)pyGUICloseDlgProc.o \
	$(OBJDIR)pyGUIConsoleCmdProc.o \
	$(OBJDIR)pyGUICtrlProcObject.o \
	$(OBJDIR)pyGUICtrlProcWriteableObject.o \
	$(OBJDIR)pyGUIDialogProc.o \
	$(OBJDIR)pyGUIPythonScriptProc.o \
	$(OBJDIR)pyKey.o \
	$(OBJDIR)pyKeyedObject.o \
	$(OBJDIR)pyKeyedObjectStub.o \
	$(OBJDIR)pyLocation.o \
	$(OBJDIR)pyDirectionalLightInfo.o \
	$(OBJDIR)pyDirectShadowMaster.o \
	$(OBJDIR)pyLightInfo.o \
	$(OBJDIR)pyLimitedDirLightInfo.o \
	$(OBJDIR)pyOmniLightInfo.o \
	$(OBJDIR)pyPointShadowMaster.o \
	$(OBJDIR)pyShadowMaster.o \
	$(OBJDIR)pySpotLightInfo.o \
	$(OBJDIR)pyActivateEventData.o \
	$(OBJDIR)pyBookEventData.o \
	$(OBJDIR)pyCallbackEventData.o \
	$(OBJDIR)pyClickDragEventData.o \
	$(OBJDIR)pyClimbingBlockerHitEventData.o \
	$(OBJDIR)pyCollisionEventData.o \
	$(OBJDIR)pyContainedEventData.o \
	$(OBJDIR)pyControlKeyEventData.o \
	$(OBJDIR)pyCoopEventData.o \
	$(OBJDIR)pyEventCallbackMsg.o \
	$(OBJDIR)pyEventData.o \
	$(OBJDIR)pyFacingEventData.o \
	$(OBJDIR)pyMessage.o \
	$(OBJDIR)pyMsgForwarder.o \
	$(OBJDIR)pyMultiStageEventData.o \
	$(OBJDIR)pyNotifyMsg.o \
	$(OBJDIR)pyOfferLinkBookEventData.o \
	$(OBJDIR)pyPickedEventData.o \
	$(OBJDIR)pyResponderStateEventData.o \
	$(OBJDIR)pySpawnedEventData.o \
	$(OBJDIR)pyVariableEventData.o \
	$(OBJDIR)pyRenderLevel.o \
	$(OBJDIR)pyInterfaceInfoModifier.o \
	$(OBJDIR)pyLogicModBase.o \
	$(OBJDIR)pyLogicModifier.o \
	$(OBJDIR)pyMaintainersMarkerModifier.o \
	$(OBJDIR)pyModifier.o \
	$(OBJDIR)pyMultiModifier.o \
	$(OBJDIR)pyOneShotMod.o \
	$(OBJDIR)pyPythonFileMod.o \
	$(OBJDIR)pyPythonParameter.o \
	$(OBJDIR)pyResponderEnableMsg.o \
	$(OBJDIR)pyResponderModifier.o \
	$(OBJDIR)pyResponderModifier_Cmd.o \
	$(OBJDIR)pyResponderModifier_State.o \
	$(OBJDIR)pySingleModifier.o \
	$(OBJDIR)pySpawnModifier.o \
	$(OBJDIR)pyAudioInterface.o \
	$(OBJDIR)pyCoordinateInterface.o \
	$(OBJDIR)pyDrawInterface.o \
	$(OBJDIR)pyObjInterface.o \
	$(OBJDIR)pySceneObject.o \
	$(OBJDIR)pySimulationInterface.o \
	$(OBJDIR)pySynchedObject.o \
	$(OBJDIR)pyGenericPhysical.o \
	$(OBJDIR)pyPhysical.o \
	$(OBJDIR)pySimDefs.o \
	$(OBJDIR)pyBounds.o \
	$(OBJDIR)pyBounds3.o \
	$(OBJDIR)pyBounds3Ext.o \
	$(OBJDIR)pyBoundsOriented.o \
	$(OBJDIR)pyBitmap.o \
	$(OBJDIR)pyDynamicTextMap.o \
	$(OBJDIR)pyGMaterial.o \
	$(OBJDIR)pyGMatState.o \
	$(OBJDIR)pyLayer.o \
	$(OBJDIR)pyLayerAnimation.o \
	$(OBJDIR)pyLayerAnimationBase.o \
	$(OBJDIR)pyLayerAVI.o \
	$(OBJDIR)pyLayerBink.o \
	$(OBJDIR)pyLayerDepth.o \
	$(OBJDIR)pyLayerInterface.o \
	$(OBJDIR)pyLayerLinkAnimation.o \
	$(OBJDIR)pyLayerMovie.o \
	$(OBJDIR)pyLayerSDLAnimation.o \
	$(OBJDIR)pyMipmap.o \
	$(OBJDIR)pyShader.o \
	$(OBJDIR)pyShaderConst.o \
	$(OBJDIR)pyAgeInfo.o \
	$(OBJDIR)pyFactory.o \
	$(OBJDIR)pyResManager.o \
	$(OBJDIR)pyPageInfo.o \
	$(OBJDIR)pyEncryptedStream.o \
	$(OBJDIR)pyFileStream.o \
	$(OBJDIR)pyRAMStream.o \
	$(OBJDIR)pyStream.o \
	$(OBJDIR)pyColor32.o \
	$(OBJDIR)pyColorRGBA.o \
	$(OBJDIR)pyBitVector.o \
	$(OBJDIR)pyDDSurface.o

PYLIB=PyHSPlasma.so
LIBDIR=../lib

all: $(LIBDIR)/$(PYLIB)

$(LIBDIR)/$(PYLIB): $(PYOBJ)
	$(CXX) $(CXXFLAGS) $(PYOBJ) $(CXXLINK) $(LINKLIB)$(PYLIB) -o $@

clean:
	rm -f $(PYOBJ)

distclean:
	rm -f $(LIBDIR)/$(PYLIB)

install: $(LIBDIR)/$(PYLIB)
	cp $(LIBDIR)/$(PYLIB) $(PYTHON_PREFIX)/lib/python$(PYTHON_VER)/

uninstall:
	rm -f $(PYTHON_PREFIX)/lib/python$(PYTHON_VER)/$(PYLIB)

$(OBJDIR)Module.o: Module.cpp
	$(CXX) $(CXXFLAGS) -c Module.cpp -o $@

$(OBJDIR)PyPlasma.o: PyPlasma.h PyPlasma.cpp
	$(CXX) $(CXXFLAGS) -c PyPlasma.cpp -o $@

$(OBJDIR)pyDebug.o: Debug/pyDebug.cpp
	$(CXX) $(CXXFLAGS) -c Debug/pyDebug.cpp -o $@

$(OBJDIR)pyAffineParts.o: Math/pyAffineParts.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyAffineParts.cpp -o $@

$(OBJDIR)pyMatrix33.o: Math/pyMatrix33.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyMatrix33.cpp -o $@

$(OBJDIR)pyMatrix44.o: Math/pyMatrix44.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyMatrix44.cpp -o $@

$(OBJDIR)pyPlane3.o: Math/pyPlane3.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyPlane3.cpp -o $@

$(OBJDIR)pyQuat.o: Math/pyQuat.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyQuat.cpp -o $@

$(OBJDIR)pyVector3.o: Math/pyVector3.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyVector3.cpp -o $@

$(OBJDIR)pyCreatable.o: PRP/pyCreatable.cpp
	$(CXX) $(CXXFLAGS) -c PRP/pyCreatable.cpp -o $@

$(OBJDIR)pyCreatableConvert.o: PRP/pyCreatableConvert.cpp
	$(CXX) $(CXXFLAGS) -c PRP/pyCreatableConvert.cpp -o $@

$(OBJDIR)pyCreatableStub.o: PRP/pyCreatableStub.cpp
	$(CXX) $(CXXFLAGS) -c PRP/pyCreatableStub.cpp -o $@

$(OBJDIR)pySceneNode.o: PRP/pySceneNode.cpp
	$(CXX) $(CXXFLAGS) -c PRP/pySceneNode.cpp -o $@

$(OBJDIR)pyAnimTimeConvert.o: PRP/Animation/pyAnimTimeConvert.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyAnimTimeConvert.cpp -o $@

$(OBJDIR)pyATCEaseCurve.o: PRP/Animation/pyATCEaseCurve.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyATCEaseCurve.cpp -o $@

$(OBJDIR)pyCompoundController.o: PRP/Animation/pyCompoundController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyCompoundController.cpp -o $@

$(OBJDIR)pyCompoundPosController.o: PRP/Animation/pyCompoundPosController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyCompoundPosController.cpp -o $@

$(OBJDIR)pyCompoundRotController.o: PRP/Animation/pyCompoundRotController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyCompoundRotController.cpp -o $@

$(OBJDIR)pyCompressedQuatKey32.o: PRP/Animation/pyCompressedQuatKey32.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyCompressedQuatKey32.cpp -o $@

$(OBJDIR)pyCompressedQuatKey64.o: PRP/Animation/pyCompressedQuatKey64.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyCompressedQuatKey64.cpp -o $@

$(OBJDIR)pyConstAccelEaseCurve.o: PRP/Animation/pyConstAccelEaseCurve.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyConstAccelEaseCurve.cpp -o $@

$(OBJDIR)pyController.o: PRP/Animation/pyController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyController.cpp -o $@

$(OBJDIR)pyEaseController.o: PRP/Animation/pyEaseController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyEaseController.cpp -o $@

$(OBJDIR)pyG3DSMaxKeyFrame.o: PRP/Animation/pyG3DSMaxKeyFrame.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyG3DSMaxKeyFrame.cpp -o $@

$(OBJDIR)pyKeyFrame.o: PRP/Animation/pyKeyFrame.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyKeyFrame.cpp -o $@

$(OBJDIR)pyLeafController.o: PRP/Animation/pyLeafController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyLeafController.cpp -o $@

$(OBJDIR)pyMatrix33Controller.o: PRP/Animation/pyMatrix33Controller.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyMatrix33Controller.cpp -o $@

$(OBJDIR)pyMatrix33Key.o: PRP/Animation/pyMatrix33Key.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyMatrix33Key.cpp -o $@

$(OBJDIR)pyMatrix44Controller.o: PRP/Animation/pyMatrix44Controller.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyMatrix44Controller.cpp -o $@

$(OBJDIR)pyMatrix44Key.o: PRP/Animation/pyMatrix44Key.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyMatrix44Key.cpp -o $@

$(OBJDIR)pyPoint3Controller.o: PRP/Animation/pyPoint3Controller.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyPoint3Controller.cpp -o $@

$(OBJDIR)pyPoint3Key.o: PRP/Animation/pyPoint3Key.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyPoint3Key.cpp -o $@

$(OBJDIR)pyPosController.o: PRP/Animation/pyPosController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyPosController.cpp -o $@

$(OBJDIR)pyQuatController.o: PRP/Animation/pyQuatController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyQuatController.cpp -o $@

$(OBJDIR)pyQuatKey.o: PRP/Animation/pyQuatKey.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyQuatKey.cpp -o $@

$(OBJDIR)pyRotController.o: PRP/Animation/pyRotController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyRotController.cpp -o $@

$(OBJDIR)pyScalarController.o: PRP/Animation/pyScalarController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyScalarController.cpp -o $@

$(OBJDIR)pyScalarKey.o: PRP/Animation/pyScalarKey.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyScalarKey.cpp -o $@

$(OBJDIR)pyScaleController.o: PRP/Animation/pyScaleController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyScaleController.cpp -o $@

$(OBJDIR)pyScaleKey.o: PRP/Animation/pyScaleKey.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyScaleKey.cpp -o $@

$(OBJDIR)pyScaleValueController.o: PRP/Animation/pyScaleValueController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyScaleValueController.cpp -o $@

$(OBJDIR)pySimplePosController.o: PRP/Animation/pySimplePosController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pySimplePosController.cpp -o $@

$(OBJDIR)pySimpleRotController.o: PRP/Animation/pySimpleRotController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pySimpleRotController.cpp -o $@

$(OBJDIR)pySimpleScaleController.o: PRP/Animation/pySimpleScaleController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pySimpleScaleController.cpp -o $@

$(OBJDIR)pySplineEaseCurve.o: PRP/Animation/pySplineEaseCurve.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pySplineEaseCurve.cpp -o $@

$(OBJDIR)pyTMController.o: PRP/Animation/pyTMController.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyTMController.cpp -o $@

$(OBJDIR)pyViewFaceModifier.o: PRP/Animation/pyViewFaceModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Animation/pyViewFaceModifier.cpp -o $@

$(OBJDIR)pyAGAnim.o: PRP/Avatar/pyAGAnim.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyAGAnim.cpp -o $@

$(OBJDIR)pyAGAnimBink.o: PRP/Avatar/pyAGAnimBink.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyAGAnimBink.cpp -o $@

$(OBJDIR)pyAGApplicator.o: PRP/Avatar/pyAGApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyAGApplicator.cpp -o $@

$(OBJDIR)pyAGChannel.o: PRP/Avatar/pyAGChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyAGChannel.cpp -o $@

$(OBJDIR)pyAgeGlobalAnim.o: PRP/Avatar/pyAgeGlobalAnim.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyAgeGlobalAnim.cpp -o $@

$(OBJDIR)pyAnimStage.o: PRP/Avatar/pyAnimStage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyAnimStage.cpp -o $@

$(OBJDIR)pyATCAnim.o: PRP/Avatar/pyATCAnim.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyATCAnim.cpp -o $@

$(OBJDIR)pyATCChannel.o: PRP/Avatar/pyATCChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyATCChannel.cpp -o $@

$(OBJDIR)pyEmoteAnim.o: PRP/Avatar/pyEmoteAnim.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyEmoteAnim.cpp -o $@

$(OBJDIR)pyLightAmbientApplicator.o: PRP/Avatar/pyLightAmbientApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyLightAmbientApplicator.cpp -o $@

$(OBJDIR)pyLightDiffuseApplicator.o: PRP/Avatar/pyLightDiffuseApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyLightDiffuseApplicator.cpp -o $@

$(OBJDIR)pyLightSpecularApplicator.o: PRP/Avatar/pyLightSpecularApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyLightSpecularApplicator.cpp -o $@

$(OBJDIR)pyMatrixBlend.o: PRP/Avatar/pyMatrixBlend.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyMatrixBlend.cpp -o $@

$(OBJDIR)pyMatrixChannel.o: PRP/Avatar/pyMatrixChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyMatrixChannel.cpp -o $@

$(OBJDIR)pyMatrixChannelApplicator.o: PRP/Avatar/pyMatrixChannelApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyMatrixChannelApplicator.cpp -o $@

$(OBJDIR)pyMatrixConstant.o: PRP/Avatar/pyMatrixConstant.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyMatrixConstant.cpp -o $@

$(OBJDIR)pyMatrixControllerCacheChannel.o: PRP/Avatar/pyMatrixControllerCacheChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyMatrixControllerCacheChannel.cpp -o $@

$(OBJDIR)pyMatrixControllerChannel.o: PRP/Avatar/pyMatrixControllerChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyMatrixControllerChannel.cpp -o $@

$(OBJDIR)pyMatrixDelayedCorrectionApplicator.o: PRP/Avatar/pyMatrixDelayedCorrectionApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyMatrixDelayedCorrectionApplicator.cpp -o $@

$(OBJDIR)pyMatrixDifferenceApp.o: PRP/Avatar/pyMatrixDifferenceApp.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyMatrixDifferenceApp.cpp -o $@

$(OBJDIR)pyMatrixTimeScale.o: PRP/Avatar/pyMatrixTimeScale.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyMatrixTimeScale.cpp -o $@

$(OBJDIR)pyMultistageBehMod.o: PRP/Avatar/pyMultistageBehMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyMultistageBehMod.cpp -o $@

$(OBJDIR)pyOmniApplicator.o: PRP/Avatar/pyOmniApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyOmniApplicator.cpp -o $@

$(OBJDIR)pyOmniCutoffApplicator.o: PRP/Avatar/pyOmniCutoffApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyOmniCutoffApplicator.cpp -o $@

$(OBJDIR)pyOmniSqApplicator.o: PRP/Avatar/pyOmniSqApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyOmniSqApplicator.cpp -o $@

$(OBJDIR)pyPointBlend.o: PRP/Avatar/pyPointBlend.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyPointBlend.cpp -o $@

$(OBJDIR)pyPointChannel.o: PRP/Avatar/pyPointChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyPointChannel.cpp -o $@

$(OBJDIR)pyPointChannelApplicator.o: PRP/Avatar/pyPointChannelApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyPointChannelApplicator.cpp -o $@

$(OBJDIR)pyPointConstant.o: PRP/Avatar/pyPointConstant.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyPointConstant.cpp -o $@

$(OBJDIR)pyPointControllerCacheChannel.o: PRP/Avatar/pyPointControllerCacheChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyPointControllerCacheChannel.cpp -o $@

$(OBJDIR)pyPointControllerChannel.o: PRP/Avatar/pyPointControllerChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyPointControllerChannel.cpp -o $@

$(OBJDIR)pyPointTimeScale.o: PRP/Avatar/pyPointTimeScale.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyPointTimeScale.cpp -o $@

$(OBJDIR)pyQuatBlend.o: PRP/Avatar/pyQuatBlend.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyQuatBlend.cpp -o $@

$(OBJDIR)pyQuatChannel.o: PRP/Avatar/pyQuatChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyQuatChannel.cpp -o $@

$(OBJDIR)pyQuatChannelApplicator.o: PRP/Avatar/pyQuatChannelApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyQuatChannelApplicator.cpp -o $@

$(OBJDIR)pyQuatConstant.o: PRP/Avatar/pyQuatConstant.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyQuatConstant.cpp -o $@

$(OBJDIR)pyQuatPointCombine.o: PRP/Avatar/pyQuatPointCombine.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyQuatPointCombine.cpp -o $@

$(OBJDIR)pyQuatTimeScale.o: PRP/Avatar/pyQuatTimeScale.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyQuatTimeScale.cpp -o $@

$(OBJDIR)pyRelativeMatrixChannelApplicator.o: PRP/Avatar/pyRelativeMatrixChannelApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyRelativeMatrixChannelApplicator.cpp -o $@

$(OBJDIR)pyScalarBlend.o: PRP/Avatar/pyScalarBlend.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyScalarBlend.cpp -o $@

$(OBJDIR)pyScalarChannel.o: PRP/Avatar/pyScalarChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyScalarChannel.cpp -o $@

$(OBJDIR)pyScalarChannelApplicator.o: PRP/Avatar/pyScalarChannelApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyScalarChannelApplicator.cpp -o $@

$(OBJDIR)pyScalarConstant.o: PRP/Avatar/pyScalarConstant.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyScalarConstant.cpp -o $@

$(OBJDIR)pyScalarControllerCacheChannel.o: PRP/Avatar/pyScalarControllerCacheChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyScalarControllerCacheChannel.cpp -o $@

$(OBJDIR)pyScalarControllerChannel.o: PRP/Avatar/pyScalarControllerChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyScalarControllerChannel.cpp -o $@

$(OBJDIR)pyScalarSDLChannel.o: PRP/Avatar/pyScalarSDLChannel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyScalarSDLChannel.cpp -o $@

$(OBJDIR)pyScalarTimeScale.o: PRP/Avatar/pyScalarTimeScale.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pyScalarTimeScale.cpp -o $@

$(OBJDIR)pySpotInnerApplicator.o: PRP/Avatar/pySpotInnerApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pySpotInnerApplicator.cpp -o $@

$(OBJDIR)pySpotOuterApplicator.o: PRP/Avatar/pySpotOuterApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pySpotOuterApplicator.cpp -o $@

$(OBJDIR)pySoundVolumeApplicator.o: PRP/Avatar/pySoundVolumeApplicator.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Avatar/pySoundVolumeApplicator.cpp -o $@

$(OBJDIR)py2WayWinAudible.o: PRP/Audio/py2WayWinAudible.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/py2WayWinAudible.cpp -o $@

$(OBJDIR)pyAudible.o: PRP/Audio/pyAudible.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/pyAudible.cpp -o $@

$(OBJDIR)pyAudibleNull.o: PRP/Audio/pyAudibleNull.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/pyAudibleNull.cpp -o $@

$(OBJDIR)pySoundBuffer.o: PRP/Audio/pySoundBuffer.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/pySoundBuffer.cpp -o $@

$(OBJDIR)pyWAVHeader.o: PRP/Audio/pyWAVHeader.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/pyWAVHeader.cpp -o $@

$(OBJDIR)pyWinAudible.o: PRP/Audio/pyWinAudible.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/pyWinAudible.cpp -o $@

$(OBJDIR)pyCluster.o: PRP/Geometry/pyCluster.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyCluster.cpp -o $@

$(OBJDIR)pyClusterGroup.o: PRP/Geometry/pyClusterGroup.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyClusterGroup.cpp -o $@

$(OBJDIR)pyCullPoly.o: PRP/Geometry/pyCullPoly.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyCullPoly.cpp -o $@

$(OBJDIR)pyDISpanIndex.o: PRP/Geometry/pyDISpanIndex.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyDISpanIndex.cpp -o $@

$(OBJDIR)pyDrawable.o: PRP/Geometry/pyDrawable.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyDrawable.cpp -o $@

$(OBJDIR)pyDrawableSpans.o: PRP/Geometry/pyDrawableSpans.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyDrawableSpans.cpp -o $@

$(OBJDIR)pyGBufferCell.o: PRP/Geometry/pyGBufferCell.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyGBufferCell.cpp -o $@

$(OBJDIR)pyGBufferGroup.o: PRP/Geometry/pyGBufferGroup.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyGBufferGroup.cpp -o $@

$(OBJDIR)pyGBufferTriangle.o: PRP/Geometry/pyGBufferTriangle.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyGBufferTriangle.cpp -o $@

$(OBJDIR)pyGBufferVertex.o: PRP/Geometry/pyGBufferVertex.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyGBufferVertex.cpp -o $@

$(OBJDIR)pyIcicle.o: PRP/Geometry/pyIcicle.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyIcicle.cpp -o $@

$(OBJDIR)pyLODDist.o: PRP/Geometry/pyLODDist.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyLODDist.cpp -o $@

$(OBJDIR)pyMobileOccluder.o: PRP/Geometry/pyMobileOccluder.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyMobileOccluder.cpp -o $@

$(OBJDIR)pyOccluder.o: PRP/Geometry/pyOccluder.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyOccluder.cpp -o $@

$(OBJDIR)pyParticleSpan.o: PRP/Geometry/pyParticleSpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyParticleSpan.cpp -o $@

$(OBJDIR)pySpaceTree.o: PRP/Geometry/pySpaceTree.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pySpaceTree.cpp -o $@

$(OBJDIR)pySpaceTreeNode.o: PRP/Geometry/pySpaceTreeNode.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pySpaceTreeNode.cpp -o $@

$(OBJDIR)pySpan.o: PRP/Geometry/pySpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pySpan.cpp -o $@

$(OBJDIR)pySpanEncoding.o: PRP/Geometry/pySpanEncoding.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pySpanEncoding.cpp -o $@

$(OBJDIR)pySpanInstance.o: PRP/Geometry/pySpanInstance.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pySpanInstance.cpp -o $@

$(OBJDIR)pySpanTemplate.o: PRP/Geometry/pySpanTemplate.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pySpanTemplate.cpp -o $@

$(OBJDIR)pySpanTemplateVertex.o: PRP/Geometry/pySpanTemplateVertex.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pySpanTemplateVertex.cpp -o $@

$(OBJDIR)pyVertexSpan.o: PRP/Geometry/pyVertexSpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyVertexSpan.cpp -o $@

$(OBJDIR)pyGUICloseDlgProc.o: PRP/GUI/pyGUICloseDlgProc.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pyGUICloseDlgProc.cpp -o $@

$(OBJDIR)pyGUIConsoleCmdProc.o: PRP/GUI/pyGUIConsoleCmdProc.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pyGUIConsoleCmdProc.cpp -o $@

$(OBJDIR)pyGUICtrlProcObject.o: PRP/GUI/pyGUICtrlProcObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pyGUICtrlProcObject.cpp -o $@

$(OBJDIR)pyGUICtrlProcWriteableObject.o: PRP/GUI/pyGUICtrlProcWriteableObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pyGUICtrlProcWriteableObject.cpp -o $@

$(OBJDIR)pyGUIDialogProc.o: PRP/GUI/pyGUIDialogProc.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pyGUIDialogProc.cpp -o $@

$(OBJDIR)pyGUIPythonScriptProc.o: PRP/GUI/pyGUIPythonScriptProc.cpp
	$(CXX) $(CXXFLAGS) -c PRP/GUI/pyGUIPythonScriptProc.cpp -o $@

$(OBJDIR)pyKey.o: PRP/KeyedObject/pyKey.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/pyKey.cpp -o $@

$(OBJDIR)pyKeyedObject.o: PRP/KeyedObject/pyKeyedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/pyKeyedObject.cpp -o $@

$(OBJDIR)pyKeyedObjectStub.o: PRP/KeyedObject/pyKeyedObjectStub.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/pyKeyedObjectStub.cpp -o $@

$(OBJDIR)pyLocation.o: PRP/KeyedObject/pyLocation.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/pyLocation.cpp -o $@

$(OBJDIR)pyDirectionalLightInfo.o: PRP/Light/pyDirectionalLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pyDirectionalLightInfo.cpp -o $@

$(OBJDIR)pyDirectShadowMaster.o: PRP/Light/pyDirectShadowMaster.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pyDirectShadowMaster.cpp -o $@

$(OBJDIR)pyLightInfo.o: PRP/Light/pyLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pyLightInfo.cpp -o $@

$(OBJDIR)pyLimitedDirLightInfo.o: PRP/Light/pyLimitedDirLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pyLimitedDirLightInfo.cpp -o $@

$(OBJDIR)pyOmniLightInfo.o: PRP/Light/pyOmniLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pyOmniLightInfo.cpp -o $@

$(OBJDIR)pyPointShadowMaster.o: PRP/Light/pyPointShadowMaster.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pyPointShadowMaster.cpp -o $@

$(OBJDIR)pyShadowMaster.o: PRP/Light/pyShadowMaster.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pyShadowMaster.cpp -o $@

$(OBJDIR)pySpotLightInfo.o: PRP/Light/pySpotLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pySpotLightInfo.cpp -o $@

$(OBJDIR)pyActivateEventData.o: PRP/Message/pyActivateEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyActivateEventData.cpp -o $@

$(OBJDIR)pyBookEventData.o: PRP/Message/pyBookEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyBookEventData.cpp -o $@

$(OBJDIR)pyCallbackEventData.o: PRP/Message/pyCallbackEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyCallbackEventData.cpp -o $@

$(OBJDIR)pyClickDragEventData.o: PRP/Message/pyClickDragEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyClickDragEventData.cpp -o $@

$(OBJDIR)pyClimbingBlockerHitEventData.o: PRP/Message/pyClimbingBlockerHitEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyClimbingBlockerHitEventData.cpp -o $@

$(OBJDIR)pyCollisionEventData.o: PRP/Message/pyCollisionEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyCollisionEventData.cpp -o $@

$(OBJDIR)pyContainedEventData.o: PRP/Message/pyContainedEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyContainedEventData.cpp -o $@

$(OBJDIR)pyControlKeyEventData.o: PRP/Message/pyControlKeyEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyControlKeyEventData.cpp -o $@

$(OBJDIR)pyCoopEventData.o: PRP/Message/pyCoopEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyCoopEventData.cpp -o $@

$(OBJDIR)pyEventCallbackMsg.o: PRP/Message/pyEventCallbackMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyEventCallbackMsg.cpp -o $@

$(OBJDIR)pyEventData.o: PRP/Message/pyEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyEventData.cpp -o $@

$(OBJDIR)pyFacingEventData.o: PRP/Message/pyFacingEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyFacingEventData.cpp -o $@

$(OBJDIR)pyMessage.o: PRP/Message/pyMessage.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyMessage.cpp -o $@

$(OBJDIR)pyMsgForwarder.o: PRP/Message/pyMsgForwarder.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyMsgForwarder.cpp -o $@

$(OBJDIR)pyMultiStageEventData.o: PRP/Message/pyMultiStageEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyMultiStageEventData.cpp -o $@

$(OBJDIR)pyNotifyMsg.o: PRP/Message/pyNotifyMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyNotifyMsg.cpp -o $@

$(OBJDIR)pyOfferLinkBookEventData.o: PRP/Message/pyOfferLinkBookEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyOfferLinkBookEventData.cpp -o $@

$(OBJDIR)pyPickedEventData.o: PRP/Message/pyPickedEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyPickedEventData.cpp -o $@

$(OBJDIR)pyResponderStateEventData.o: PRP/Message/pyResponderStateEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyResponderStateEventData.cpp -o $@

$(OBJDIR)pySpawnedEventData.o: PRP/Message/pySpawnedEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pySpawnedEventData.cpp -o $@

$(OBJDIR)pyVariableEventData.o: PRP/Message/pyVariableEventData.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Message/pyVariableEventData.cpp -o $@

$(OBJDIR)pyRenderLevel.o: PRP/Misc/pyRenderLevel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Misc/pyRenderLevel.cpp -o $@

$(OBJDIR)pyInterfaceInfoModifier.o: PRP/Modifier/pyInterfaceInfoModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyInterfaceInfoModifier.cpp -o $@

$(OBJDIR)pyLogicModBase.o: PRP/Modifier/pyLogicModBase.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyLogicModBase.cpp -o $@

$(OBJDIR)pyLogicModifier.o: PRP/Modifier/pyLogicModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyLogicModifier.cpp -o $@

$(OBJDIR)pyMaintainersMarkerModifier.o: PRP/Modifier/pyMaintainersMarkerModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyMaintainersMarkerModifier.cpp -o $@

$(OBJDIR)pyModifier.o: PRP/Modifier/pyModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyModifier.cpp -o $@

$(OBJDIR)pyMultiModifier.o: PRP/Modifier/pyMultiModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyMultiModifier.cpp -o $@

$(OBJDIR)pyOneShotMod.o: PRP/Modifier/pyOneShotMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyOneShotMod.cpp -o $@

$(OBJDIR)pyPythonFileMod.o: PRP/Modifier/pyPythonFileMod.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyPythonFileMod.cpp -o $@

$(OBJDIR)pyPythonParameter.o: PRP/Modifier/pyPythonParameter.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyPythonParameter.cpp -o $@

$(OBJDIR)pyResponderEnableMsg.o: PRP/Modifier/pyResponderEnableMsg.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyResponderEnableMsg.cpp -o $@

$(OBJDIR)pyResponderModifier.o: PRP/Modifier/pyResponderModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyResponderModifier.cpp -o $@

$(OBJDIR)pyResponderModifier_Cmd.o: PRP/Modifier/pyResponderModifier_Cmd.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyResponderModifier_Cmd.cpp -o $@

$(OBJDIR)pyResponderModifier_State.o: PRP/Modifier/pyResponderModifier_State.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pyResponderModifier_State.cpp -o $@

$(OBJDIR)pySingleModifier.o: PRP/Modifier/pySingleModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pySingleModifier.cpp -o $@

$(OBJDIR)pySpawnModifier.o: PRP/Modifier/pySpawnModifier.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Modifier/pySpawnModifier.cpp -o $@

$(OBJDIR)pyAudioInterface.o: PRP/Object/pyAudioInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pyAudioInterface.cpp -o $@

$(OBJDIR)pyCoordinateInterface.o: PRP/Object/pyCoordinateInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pyCoordinateInterface.cpp -o $@

$(OBJDIR)pyDrawInterface.o: PRP/Object/pyDrawInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pyDrawInterface.cpp -o $@

$(OBJDIR)pyObjInterface.o: PRP/Object/pyObjInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pyObjInterface.cpp -o $@

$(OBJDIR)pySceneObject.o: PRP/Object/pySceneObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pySceneObject.cpp -o $@

$(OBJDIR)pySimulationInterface.o: PRP/Object/pySimulationInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pySimulationInterface.cpp -o $@

$(OBJDIR)pySynchedObject.o: PRP/Object/pySynchedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pySynchedObject.cpp -o $@

$(OBJDIR)pyGenericPhysical.o: PRP/Physics/pyGenericPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/pyGenericPhysical.cpp -o $@

$(OBJDIR)pyPhysical.o: PRP/Physics/pyPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/pyPhysical.cpp -o $@

$(OBJDIR)pySimDefs.o: PRP/Physics/pySimDefs.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/pySimDefs.cpp -o $@

$(OBJDIR)pyBounds.o: PRP/Region/pyBounds.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/pyBounds.cpp -o $@

$(OBJDIR)pyBounds3.o: PRP/Region/pyBounds3.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/pyBounds3.cpp -o $@

$(OBJDIR)pyBounds3Ext.o: PRP/Region/pyBounds3Ext.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/pyBounds3Ext.cpp -o $@

$(OBJDIR)pyBoundsOriented.o: PRP/Region/pyBoundsOriented.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/pyBoundsOriented.cpp -o $@

$(OBJDIR)pyBitmap.o: PRP/Surface/pyBitmap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyBitmap.cpp -o $@

$(OBJDIR)pyDynamicTextMap.o: PRP/Surface/pyDynamicTextMap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyDynamicTextMap.cpp -o $@

$(OBJDIR)pyGMaterial.o: PRP/Surface/pyGMaterial.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyGMaterial.cpp -o $@

$(OBJDIR)pyGMatState.o: PRP/Surface/pyGMatState.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyGMatState.cpp -o $@

$(OBJDIR)pyLayer.o: PRP/Surface/pyLayer.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayer.cpp -o $@

$(OBJDIR)pyLayerAnimation.o: PRP/Surface/pyLayerAnimation.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayerAnimation.cpp -o $@

$(OBJDIR)pyLayerAnimationBase.o: PRP/Surface/pyLayerAnimationBase.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayerAnimationBase.cpp -o $@

$(OBJDIR)pyLayerAVI.o: PRP/Surface/pyLayerAVI.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayerAVI.cpp -o $@

$(OBJDIR)pyLayerBink.o: PRP/Surface/pyLayerBink.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayerBink.cpp -o $@

$(OBJDIR)pyLayerDepth.o: PRP/Surface/pyLayerDepth.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayerDepth.cpp -o $@

$(OBJDIR)pyLayerInterface.o: PRP/Surface/pyLayerInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayerInterface.cpp -o $@

$(OBJDIR)pyLayerLinkAnimation.o: PRP/Surface/pyLayerLinkAnimation.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayerLinkAnimation.cpp -o $@

$(OBJDIR)pyLayerMovie.o: PRP/Surface/pyLayerMovie.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayerMovie.cpp -o $@

$(OBJDIR)pyLayerSDLAnimation.o: PRP/Surface/pyLayerSDLAnimation.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayerSDLAnimation.cpp -o $@

$(OBJDIR)pyMipmap.o: PRP/Surface/pyMipmap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyMipmap.cpp -o $@

$(OBJDIR)pyShader.o: PRP/Surface/pyShader.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyShader.cpp -o $@

$(OBJDIR)pyShaderConst.o: PRP/Surface/pyShaderConst.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyShaderConst.cpp -o $@

$(OBJDIR)pyAgeInfo.o: ResManager/pyAgeInfo.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/pyAgeInfo.cpp -o $@

$(OBJDIR)pyFactory.o: ResManager/pyFactory.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/pyFactory.cpp -o $@

$(OBJDIR)pyResManager.o: ResManager/pyResManager.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/pyResManager.cpp -o $@

$(OBJDIR)pyPageInfo.o: ResManager/pyPageInfo.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/pyPageInfo.cpp -o $@

$(OBJDIR)pyEncryptedStream.o: Stream/pyEncryptedStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pyEncryptedStream.cpp -o $@

$(OBJDIR)pyFileStream.o: Stream/pyFileStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pyFileStream.cpp -o $@

$(OBJDIR)pyRAMStream.o: Stream/pyRAMStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pyRAMStream.cpp -o $@

$(OBJDIR)pyStream.o: Stream/pyStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pyStream.cpp -o $@

$(OBJDIR)pyColor32.o: Sys/pyColor32.cpp
	$(CXX) $(CXXFLAGS) -c Sys/pyColor32.cpp -o $@

$(OBJDIR)pyColorRGBA.o: Sys/pyColorRGBA.cpp
	$(CXX) $(CXXFLAGS) -c Sys/pyColorRGBA.cpp -o $@

$(OBJDIR)pyBitVector.o: Util/pyBitVector.cpp
	$(CXX) $(CXXFLAGS) -c Util/pyBitVector.cpp -o $@

$(OBJDIR)pyDDSurface.o: Util/pyDDSurface.cpp
	$(CXX) $(CXXFLAGS) -c Util/pyDDSurface.cpp -o $@
