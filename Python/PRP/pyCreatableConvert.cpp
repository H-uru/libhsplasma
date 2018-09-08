/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pyCreatable.h"
#include <ResManager/plFactory.h>
#include <typeinfo>

// Includes for all plCreatable types
#include "PRP/plSceneNode.h"
#include "PRP/Animation/plBlower.h"
#include "PRP/Animation/plFilterCoordInterface.h"
#include "PRP/Animation/plLineFollowMod.h"
#include "PRP/Animation/pfObjectFlocker.h"
#include "PRP/Animation/plStereizer.h"
#include "PRP/Animation/plViewFaceModifier.h"
#include "PRP/Audio/plAudible.h"
#include "PRP/Audio/plCrossfade.h"
#include "PRP/Audio/plDirectMusicSound.h"
#include "PRP/Audio/plEAXListenerMod.h"
#include "PRP/Audio/plSound.h"
#include "PRP/Audio/plSoundBuffer.h"
#include "PRP/Audio/plWin32Sound.h"
#include "PRP/Audio/plWin32StaticSound.h"
#include "PRP/Avatar/plAGMasterMod.h"
#include "PRP/Avatar/plAGModifier.h"
#include "PRP/Avatar/plArmatureEffects.h"
#include "PRP/Avatar/plArmatureMod.h"
#include "PRP/Avatar/plATCAnim.h"
#include "PRP/Avatar/plAvatarClothing.h"
#include "PRP/Avatar/plAvBrainCoop.h"
#include "PRP/Avatar/plAvTask.h"
#include "PRP/Avatar/plClothingItem.h"
#include "PRP/Avatar/plLadderModifier.h"
#include "PRP/Avatar/plMatrixChannel.h"
#include "PRP/Avatar/plMultistageBehMod.h"
#include "PRP/Avatar/plNPCSpawnMod.h"
#include "PRP/Avatar/plPointChannel.h"
#include "PRP/Avatar/plQuatChannel.h"
#include "PRP/Avatar/plScalarChannel.h"
#include "PRP/Avatar/plSeekPointMod.h"
#include "PRP/Avatar/plSittingModifier.h"
#include "PRP/Camera/plCameraBrain.h"
#include "PRP/Camera/plCameraModifier.h"
#include "PRP/ConditionalObject/plActivatorConditionalObject.h"
#include "PRP/ConditionalObject/plAnimationEventConditionalObject.h"
#include "PRP/ConditionalObject/plBooleanConditionalObject.h"
#include "PRP/ConditionalObject/plControlEventConditionalObject.h"
#include "PRP/ConditionalObject/plDetectConditionalObjects.hpp"
#include "PRP/ConditionalObject/plFacingConditionalObject.h"
#include "PRP/ConditionalObject/plKeyPressConditionalObject.h"
#include "PRP/ConditionalObject/plVolumeSensorConditionalObject.h"
#include "PRP/Geometry/plClusterGroup.h"
#include "PRP/Geometry/plDrawableSpans.h"
#include "PRP/Geometry/plMorphDataSet.h"
#include "PRP/Geometry/plMorphSequence.h"
#include "PRP/Geometry/plOccluder.h"
#include "PRP/Geometry/plSharedMesh.h"
#include "PRP/GUI/pfGUIButtonMod.h"
#include "PRP/GUI/pfGUICheckBoxCtrl.h"
#include "PRP/GUI/pfGUIDialogMod.h"
#include "PRP/GUI/pfGUIDynDisplayCtrl.h"
#include "PRP/GUI/pfGUIKnobCtrl.h"
#include "PRP/GUI/pfGUIListBoxMod.h"
#include "PRP/GUI/pfGUIMisc.hpp"
#include "PRP/GUI/pfGUIMultiLineEditCtrl.h"
#include "PRP/GUI/pfGUIPopUpMenu.h"
#include "PRP/GUI/pfGUIProgressCtrl.h"
#include "PRP/GUI/pfGUIRadioGroupCtrl.h"
#include "PRP/GUI/pfGUISkin.h"
#include "PRP/GUI/pfGUITextBoxMod.h"
#include "PRP/GUI/pfGUIUpDownPairMod.h"
#include "PRP/GUI/plImageLibMod.h"
#include "PRP/Light/plDirectionalLightInfo.h"
#include "PRP/Light/plOmniLightInfo.h"
#include "PRP/Light/plShadowMaster.h"
#include "PRP/Light/plShadowCaster.h"
#include "PRP/Message/plAnimCmdMsg.h"
#include "PRP/Message/plArmatureEffectMsg.h"
#include "PRP/Message/plAvatarInputStateMsg.h"
#include "PRP/Message/plAvatarMsg.h"
#include "PRP/Message/plAvSeekMsg.h"
#include "PRP/Message/plAvTaskMsg.h"
#include "PRP/Message/plClimbMsg.h"
#include "PRP/Message/plCursorChangeMsg.h"
#include "PRP/Message/plEnableMsg.h"
#include "PRP/Message/plExcludeRegionMsg.h"
#include "PRP/Message/plInputIfaceMgrMsg.h"
#include "PRP/Message/pfKIMsg.h"
#include "PRP/Message/plLinkToAgeMsg.h"
#include "PRP/Message/plLinkEffectsTriggerMsg.h"
#include "PRP/Message/plLoadAvatarMsg.h"
#include "PRP/Message/plLoadCloneMsg.h"
#include "PRP/Message/plMsgForwarder.h"
#include "PRP/Message/plResponderMsg.h"
#include "PRP/Message/plRideAnimatedPhysMsg.h"
#include "PRP/Message/plServerReplyMsg.h"
#include "PRP/Message/plSimulationMsg.h"
#include "PRP/Message/plSoundMsg.h"
#include "PRP/Message/plSwimMsg.h"
#include "PRP/Message/plTimerCallbackMsg.h"
#include "PRP/Message/plTransitionMsg.h"
#include "PRP/Misc/plFogEnvironment.h"
#include "PRP/Modifier/plAliasModifier.h"
#include "PRP/Modifier/plAnimEventModifier.h"
#include "PRP/Modifier/plAxisAnimModifier.h"
#include "PRP/Modifier/plExcludeRegionModifier.h"
#include "PRP/Modifier/plFollowMod.h"
#include "PRP/Modifier/plGameMarkerModifier.h"
#include "PRP/Modifier/plInterfaceInfoModifier.h"
#include "PRP/Modifier/plLogicModifier.h"
#include "PRP/Modifier/plMaintainersMarkerModifier.h"
#include "PRP/Modifier/plNodeRegionModifier.h"
#include "PRP/Modifier/plOneShotMod.h"
#include "PRP/Modifier/plPostEffectMod.h"
#include "PRP/Modifier/plPythonFileMod.h"
#include "PRP/Modifier/plPythonMod.h"
#include "PRP/Modifier/plRandomSoundMod.h"
#include "PRP/Modifier/plResponderModifier.h"
#include "PRP/Modifier/plSpawnModifier.h"
#include "PRP/Object/plAudioInterface.h"
#include "PRP/Object/plCoordinateInterface.h"
#include "PRP/Object/plDrawInterface.h"
#include "PRP/Object/plObjInterface.h"
#include "PRP/Object/plSceneObject.h"
#include "PRP/Object/plSimulationInterface.h"
#include "PRP/Particle/plParticleApplicator.hpp"
#include "PRP/Particle/plParticleEffect.h"
#include "PRP/Particle/plParticleSystem.h"
#include "PRP/Physics/plObjectInVolumeDetector.h"
#include "PRP/Physics/plGenericPhysical.h"
#include "PRP/Physics/plHKSubWorld.h"
#include "PRP/Physics/plPhysicalSndGroup.h"
#include "PRP/Physics/plVehicleModifier.h"
#include "PRP/Region/plHardRegionPlanes.h"
#include "PRP/Region/plRelevanceRegion.h"
#include "PRP/Region/plSimpleRegionSensor.h"
#include "PRP/Region/plSoftVolume.h"
#include "PRP/Region/plSwimRegion.h"
#include "PRP/Region/plVisRegion.h"
#include "PRP/Surface/plCubicEnvironmap.h"
#include "PRP/Surface/plDistOpacityMod.h"
#include "PRP/Surface/plDynamicEnvMap.h"
#include "PRP/Surface/plDynamicTextMap.h"
#include "PRP/Surface/plDynaRippleMgr.h"
#include "PRP/Surface/plFadeOpacityMod.h"
#include "PRP/Surface/plGrassShaderMod.h"
#include "PRP/Surface/plLayer.h"
#include "PRP/Surface/plLayerMovie.h"
#include "PRP/Surface/plPrintShape.h"
#include "PRP/Surface/plRenderTarget.h"
#include "PRP/Surface/plShader.h"
#include "PRP/Surface/plWaveSet.h"
// End type includes

// Incude all their Python equivalents
#include "PRP/pySceneNode.h"
#include "PRP/Animation/pyAnimPath.h"
#include "PRP/Animation/pyAnimTimeConvert.h"
#include "PRP/Animation/pyATCEaseCurves.h"
#include "PRP/Animation/pyController.h"
#include "PRP/Animation/pyFilterCoordInterface.h"
#include "PRP/Animation/pyKeys.h"
#include "PRP/Animation/pyLeafController.h"
#include "PRP/Animation/pyLineFollowMod.h"
#include "PRP/Animation/pyPosController.h"
#include "PRP/Animation/pyRotController.h"
#include "PRP/Animation/pyScaleController.h"
#include "PRP/Animation/pyViewFaceModifier.h"
#include "PRP/Avatar/pyAGAnim.h"
#include "PRP/Avatar/pyAGApplicator.h"
#include "PRP/Avatar/pyAGChannel.h"
#include "PRP/Avatar/pyAGMasterMod.h"
#include "PRP/Avatar/pyAGModifier.h"
#include "PRP/Avatar/pyATCAnim.h"
#include "PRP/Avatar/pyLadderModifier.h"
#include "PRP/Avatar/pyMultistageBehMod.h"
#include "PRP/Avatar/pySeekPointMod.h"
#include "PRP/Avatar/pySittingModifier.h"
#include "PRP/Audio/pyAudible.h"
#include "PRP/Audio/pySound.h"
#include "PRP/Audio/pySoundBuffer.h"
#include "PRP/Audio/pyWin32Sound.h"
#include "PRP/Audio/pyWin32StaticSound.h"
#include "PRP/Camera/pyCameraBrain.h"
#include "PRP/Camera/pyCameraModifier.h"
#include "PRP/ConditionalObject/pyActivatorConditionalObject.h"
#include "PRP/ConditionalObject/pyAnimationEventConditionalObject.h"
#include "PRP/ConditionalObject/pyBooleanConditionalObject.h"
#include "PRP/ConditionalObject/pyConditionalObject.h"
#include "PRP/ConditionalObject/pyControlEventConditionalObject.h"
#include "PRP/ConditionalObject/pyDetectConditionalObjects.h"
#include "PRP/ConditionalObject/pyFacingConditionalObject.h"
#include "PRP/ConditionalObject/pyKeyPressConditionalObject.h"
#include "PRP/ConditionalObject/pyVolumeSensorConditionalObject.h"
#include "PRP/Geometry/pyCluster.h"
#include "PRP/Geometry/pyClusterGroup.h"
#include "PRP/Geometry/pyDrawableSpans.h"
#include "PRP/Geometry/pyOccluder.h"
#include "PRP/Geometry/pySpaceTree.h"
#include "PRP/GUI/pyGUIButtonMod.h"
#include "PRP/GUI/pyGUICheckBoxCtrl.h"
#include "PRP/GUI/pyGUIControlMod.h"
#include "PRP/GUI/pyGUIDialogMod.h"
#include "PRP/GUI/pyGUIDynDisplayCtrl.h"
#include "PRP/GUI/pyGUIKnobCtrl.h"
#include "PRP/GUI/pyGUIListBoxMod.h"
#include "PRP/GUI/pyGUIMisc.h"
#include "PRP/GUI/pyGUIMultiLineEditCtrl.h"
#include "PRP/GUI/pyGUIPopUpMenu.h"
#include "PRP/GUI/pyGUIProgressCtrl.h"
#include "PRP/GUI/pyGUIRadioGroupCtrl.h"
#include "PRP/GUI/pyGUISkin.h"
#include "PRP/GUI/pyGUITextBoxMod.h"
#include "PRP/GUI/pyGUIUpDownPairMod.h"
#include "PRP/GUI/pyGUIValueCtrl.h"
#include "PRP/GUI/pyImageLibMod.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/Light/pyLightInfo.h"
#include "PRP/Light/pyShadowCaster.h"
#include "PRP/Light/pyShadowMaster.h"
#include "PRP/Message/pyAnimCmdMsg.h"
#include "PRP/Message/pyArmatureEffectMsg.h"
#include "PRP/Message/pyCameraMsg.h"
#include "PRP/Message/pyCursorChangeMsg.h"
#include "PRP/Message/pyEnableMsg.h"
#include "PRP/Message/pyEventCallbackMsg.h"
#include "PRP/Message/pyExcludeRegionMsg.h"
#include "PRP/Message/pyMessage.h"
#include "PRP/Message/pyMessageWithCallbacks.h"
#include "PRP/Message/pyMsgForwarder.h"
#include "PRP/Message/pyNotifyMsg.h"
#include "PRP/Message/pyLinkToAgeMsg.h"
#include "PRP/Message/pyResponderMsg.h"
#include "PRP/Message/pyRideAnimatedPhysMsg.h"
#include "PRP/Message/pySimulationMsg.h"
#include "PRP/Message/pySoundMsg.h"
#include "PRP/Message/pySwimMsg.h"
#include "PRP/Message/pyTimerCallbackMsg.h"
#include "PRP/Misc/pyRenderLevel.h"
#include "PRP/Misc/pyAgeLinkInfo.h"
#include "PRP/Misc/pyFogEnvironment.h"
#include "PRP/Modifier/pyExcludeRegionModifier.h"
#include "PRP/Modifier/pyFollowMod.h"
#include "PRP/Modifier/pyInterfaceInfoModifier.h"
#include "PRP/Modifier/pyLogicModifier.h"
#include "PRP/Modifier/pyMaintainersMarkerModifier.h"
#include "PRP/Modifier/pyModifier.h"
#include "PRP/Modifier/pyOneShotMod.h"
#include "PRP/Modifier/pyPostEffectMod.h"
#include "PRP/Modifier/pyPythonFileMod.h"
#include "PRP/Modifier/pyResponderModifier.h"
#include "PRP/Modifier/pySpawnModifier.h"
#include "PRP/Object/pyObjInterface.h"
#include "PRP/Object/pySceneObject.h"
#include "PRP/Object/pySynchedObject.h"
#include "PRP/Particle/pyBoundInterface.h"
#include "PRP/Particle/pyParticleApplicator.h"
#include "PRP/Particle/pyParticleEffect.h"
#include "PRP/Particle/pyParticleEmitter.h"
#include "PRP/Particle/pyParticleGenerator.h"
#include "PRP/Particle/pyParticleSystem.h"
#include "PRP/Physics/pyCollisionDetector.h"
#include "PRP/Physics/pyDetectorModifier.h"
#include "PRP/Physics/pyHKSubWorld.h"
#include "PRP/Physics/pyObjectInVolumeDetector.h"
#include "PRP/Physics/pyPhysical.h"
#include "PRP/Region/pyBounds.h"
#include "PRP/Region/pyConvexVolume.h"
#include "PRP/Region/pySimpleRegionSensor.h"
#include "PRP/Region/pySoftVolume.h"
#include "PRP/Region/pySwimRegion.h"
#include "PRP/Region/pyVisRegion.h"
#include "PRP/Region/pyVolumeIsect.h"
#include "PRP/Surface/pyBitmap.h"
#include "PRP/Surface/pyCubicEnvironmap.h"
#include "PRP/Surface/pyDistOpacityMod.h"
#include "PRP/Surface/pyDynamicEnvMap.h"
#include "PRP/Surface/pyDynamicTextMap.h"
#include "PRP/Surface/pyFadeOpacityMod.h"
#include "PRP/Surface/pyGMaterial.h"
#include "PRP/Surface/pyGMatState.h"
#include "PRP/Surface/pyLayer.h"
#include "PRP/Surface/pyLayerAnimation.h"
#include "PRP/Surface/pyLayerMovie.h"
#include "PRP/Surface/pyRenderTarget.h"
#include "PRP/Surface/pyShader.h"
#include "PRP/Surface/pyWaveSet.h"
// End python includes

PyObject* ICreate(plCreatable* pCre)
{
    if (pCre == NULL)
        Py_RETURN_NONE;
    if ((typeid(*pCre)) == typeid(hsKeyedObjectStub))
        return pyKeyedObjectStub_FromKeyedObjectStub(dynamic_cast<hsKeyedObjectStub*>(pCre));
    if ((typeid(*pCre)) == typeid(plCreatableStub))
        return pyCreatableStub_FromCreatableStub(dynamic_cast<plCreatableStub*>(pCre));
    switch (pCre->ClassIndex()) {
        case kKeyedObject: return pyKeyedObject_FromKeyedObject(hsKeyedObject::Convert(pCre));
        case kSceneNode: return pySceneNode_FromSceneNode(plSceneNode::Convert(pCre));
        case kSynchedObject: return pySynchedObject_FromSynchedObject(plSynchedObject::Convert(pCre));
        case kSceneObject: return pySceneObject_FromSceneObject(plSceneObject::Convert(pCre));
        case kObjInterface: return pyObjInterface_FromObjInterface(plObjInterface::Convert(pCre));
        case kAudioInterface: return pyAudioInterface_FromAudioInterface(plAudioInterface::Convert(pCre));
        case kCoordinateInterface: return pyCoordinateInterface_FromCoordinateInterface(plCoordinateInterface::Convert(pCre));
        case kDrawInterface: return pyDrawInterface_FromDrawInterface(plDrawInterface::Convert(pCre));
        case kSimulationInterface: return pySimulationInterface_FromSimulationInterface(plSimulationInterface::Convert(pCre));
        case kDrawable: return pyDrawable_FromDrawable(plDrawable::Convert(pCre));
        case kDrawableSpans: return pyDrawableSpans_FromDrawableSpans(plDrawableSpans::Convert(pCre));
        case kGMaterial: return pyGMaterial_FromGMaterial(hsGMaterial::Convert(pCre));
        case kLayerInterface: return pyLayerInterface_FromLayerInterface(plLayerInterface::Convert(pCre));
        case kLayer: return pyLayer_FromLayer(plLayer::Convert(pCre));
        case kLayerDepth: return pyLayerDepth_FromLayerDepth(plLayerDepth::Convert(pCre));
        case kShader: return pyShader_FromShader(plShader::Convert(pCre));
        case kRenderTarget: return pyRenderTarget_FromRenderTarget(plRenderTarget::Convert(pCre));
        case kCubicRenderTarget: return pyCubicRenderTarget_FromCubicRenderTarget(plCubicRenderTarget::Convert(pCre));
        case kBitmap: return pyBitmap_FromBitmap(plBitmap::Convert(pCre));
        case kMipmap: return pyMipmap_FromMipmap(plMipmap::Convert(pCre));
        case kCubicEnvironmap: return pyCubicEnvironmap_FromCubicEnvironmap(plCubicEnvironmap::Convert(pCre));
        case kLightInfo: return pyLightInfo_FromLightInfo(plLightInfo::Convert(pCre));
        case kDirectionalLightInfo: return pyDirectionalLightInfo_FromDirectionalLightInfo(plDirectionalLightInfo::Convert(pCre));
        case kLimitedDirLightInfo: return pyLimitedDirLightInfo_FromLimitedDirLightInfo(plLimitedDirLightInfo::Convert(pCre));
        case kOmniLightInfo: return pyOmniLightInfo_FromOmniLightInfo(plOmniLightInfo::Convert(pCre));
        case kSpotLightInfo: return pySpotLightInfo_FromSpotLightInfo(plSpotLightInfo::Convert(pCre));
        case kSoundBuffer: return pySoundBuffer_FromSoundBuffer(plSoundBuffer::Convert(pCre));
        case kSound: return pySound_FromSound(plSound::Convert(pCre));
        case kWin32Sound: return pyWin32Sound_FromWin32Sound(plWin32Sound::Convert(pCre));
        case kWin32StreamingSound: return pyWin32StreamingSound_FromWin32StreamingSound(plWin32StreamingSound::Convert(pCre));
        case kWin32StaticSound: return pyWin32StaticSound_FromWin32StaticSound(plWin32StaticSound::Convert(pCre));
        case kPhysical: return pyPhysical_FromPhysical(plPhysical::Convert(pCre));
        case kGenericPhysical: return pyGenericPhysical_FromGenericPhysical(plGenericPhysical::Convert(pCre));
        case kModifier: return pyModifier_FromModifier(plModifier::Convert(pCre));
        case kSingleModifier: return pySingleModifier_FromSingleModifier(plSingleModifier::Convert(pCre));
        case kMultiModifier: return pyMultiModifier_FromMultiModifier(plMultiModifier::Convert(pCre));
        case kPythonFileMod: return pyPythonFileMod_FromPythonFileMod(plPythonFileMod::Convert(pCre));
        case kActivatorActivatorConditionalObject: return pyActivatorActivatorConditionalObject_FromActivatorActivatorConditionalObject(plActivatorActivatorConditionalObject::Convert(pCre));
        case kActivatorConditionalObject: return pyActivatorConditionalObject_FromActivatorConditionalObject(plActivatorConditionalObject::Convert(pCre));
        case kANDConditionalObject: return pyANDConditionalObject_FromANDConditionalObject(plANDConditionalObject::Convert(pCre));
        case kAnimationEventConditionalObject: return pyAnimationEventConditionalObject_FromAnimationEventConditionalObject(plAnimationEventConditionalObject::Convert(pCre));
        case kControlEventConditionalObject: return pyControlEventConditionalObject_FromControlEventConditionalObject(plControlEventConditionalObject::Convert(pCre));
        case kFacingConditionalObject: return pyFacingConditionalObject_FromFacingConditionalObject(plFacingConditionalObject::Convert(pCre));
        case kKeyPressConditionalObject: return pyKeyPressConditionalObject_FromKeyPressConditionalObject(plKeyPressConditionalObject::Convert(pCre));
        case kLocalPlayerInBoxConditionalObject: return pyLocalPlayerInBoxConditionalObject_FromLocalPlayerInBoxConditionalObject(plLocalPlayerInBoxConditionalObject::Convert(pCre));
        case kLocalPlayerIntersectPlaneConditionalObject: return pyLocalPlayerIntersectPlaneConditionalObject_FromLocalPlayerIntersectPlaneConditionalObject(plLocalPlayerIntersectPlaneConditionalObject::Convert(pCre));
        case kObjectInBoxConditionalObject: return pyObjectInBoxConditionalObject_FromObjectInBoxConditionalObject(plObjectInBoxConditionalObject::Convert(pCre));
        case kObjectIntersectPlaneConditionalObject: return pyObjectIntersectPlaneConditionalObject_FromObjectIntersectPlaneConditionalObject(plObjectIntersectPlaneConditionalObject::Convert(pCre));
        case kORConditionalObject: return pyORConditionalObject_FromORConditionalObject(plORConditionalObject::Convert(pCre));
        case kVolActivatorConditionalObject: return pyVolActivatorConditionalObject_FromVolActivatorConditionalObject(plVolActivatorConditionalObject::Convert(pCre));
        case kVolumeSensorConditionalObject: return pyVolumeSensorConditionalObject_FromVolumeSensorConditionalObject(plVolumeSensorConditionalObject::Convert(pCre));
        case kSpawnModifier: return pySpawnModifier_FromSpawnModifier(plSpawnModifier::Convert(pCre));
        case kViewFaceModifier: return pyViewFaceModifier_FromViewFaceModifier(plViewFaceModifier::Convert(pCre));
        case kMaintainersMarkerModifier: return pyMaintainersMarkerModifier_FromMaintainersMarkerModifier(plMaintainersMarkerModifier::Convert(pCre));
        case kExcludeRegionModifier: return pyExcludeRegionModifier_FromExcludeRegionModifier(plExcludeRegionModifier::Convert(pCre));
        case kClusterGroup: return pyClusterGroup_FromClusterGroup(plClusterGroup::Convert(pCre));
        case kLayerAnimationBase: return pyLayerAnimationBase_FromLayerAnimationBase(plLayerAnimationBase::Convert(pCre));
        case kLayerAnimation: return pyLayerAnimation_FromLayerAnimation(plLayerAnimation::Convert(pCre));
        case kLayerLinkAnimation: return pyLayerLinkAnimation_FromLayerLinkAnimation(plLayerLinkAnimation::Convert(pCre));
        case kLayerSDLAnimation: return pyLayerSDLAnimation_FromLayerSDLAnimation(plLayerSDLAnimation::Convert(pCre));
        case kLayerMovie: return pyLayerMovie_FromLayerMovie(plLayerMovie::Convert(pCre));
        case kLayerAVI: return pyLayerAVI_FromLayerAVI(plLayerAVI::Convert(pCre));
        case kLayerBink: return pyLayerBink_FromLayerBink(plLayerBink::Convert(pCre));
        case kOneShotMod: return pyOneShotMod_FromOneShotMod(plOneShotMod::Convert(pCre));
        case kObjectInVolumeDetector: return pyObjectInVolumeDetector_FromObjectInVolumeDetector(plObjectInVolumeDetector::Convert(pCre));
        case kObjectInVolumeAndFacingDetector: return pyObjectInVolumeAndFacingDetector_FromObjectInVolumeAndFacingDetector(plObjectInVolumeAndFacingDetector::Convert(pCre));
        case kResponderModifier: return pyResponderModifier_FromResponderModifier(plResponderModifier::Convert(pCre));
        case kFollowMod: return pyFollowMod_FromFollowMod(plFollowMod::Convert(pCre));
        case kFadeOpacityMod: return pyFadeOpacityMod_FromFadeOpacityMod(plFadeOpacityMod::Convert(pCre));
        case kDistOpacityMod: return pyDistOpacityMod_FromDistOpacityMod(plDistOpacityMod::Convert(pCre));
        case kDynamicEnvMap: return pyDynamicEnvMap_FromDynamicEnvMap(plDynamicEnvMap::Convert(pCre));
        case kDynamicCamMap: return pyDynamicCamMap_FromDynamicCamMap(plDynamicCamMap::Convert(pCre));
        case kDynamicTextMap: return pyDynamicTextMap_FromDynamicTextMap(plDynamicTextMap::Convert(pCre));
        case kSittingModifier: return pySittingModifier_FromSittingModifier(plSittingModifier::Convert(pCre));
        case kAGAnim: return pyAGAnim_FromAGAnim(plAGAnim::Convert(pCre));
        case kAGModifier: return pyAGModifier_FromAGModifier(plAGModifier::Convert(pCre));
        case kAGMasterMod: return pyAGMasterMod_FromAGMasterMod(plAGMasterMod::Convert(pCre));
        case kAgeGlobalAnim: return pyAgeGlobalAnim_FromAgeGlobalAnim(plAgeGlobalAnim::Convert(pCre));
        case kATCAnim: return pyATCAnim_FromATCAnim(plATCAnim::Convert(pCre));
        case kSeekPointMod: return pySeekPointMod_FromSeekPointMod(plSeekPointMod::Convert(pCre));
        case kSubworldRegionDetector: return pySubworldRegionDetector_FromSubworldRegionDetector(plSubworldRegionDetector::Convert(pCre));
        case kHKSubWorld: return pyHKSubWorld_FromHKSubWorld(plHKSubWorld::Convert(pCre));
        case kPanicLinkRegion: return pyPanicLinkRegion_FromPanicLinkRegion(plPanicLinkRegion::Convert(pCre));
        case kEmoteAnim: return pyEmoteAnim_FromEmoteAnim(plEmoteAnim::Convert(pCre));
        case kAGAnimBink: return pyAGAnimBink_FromAGAnimBink(plAGAnimBink::Convert(pCre));
        case kVolumeSensorConditionalObjectNoArbitration: return pyVolumeSensorConditionalObjectNoArbitration_FromVolumeSensorConditionalObjectNoArbitration(plVolumeSensorConditionalObjectNoArbitration::Convert(pCre));
        case kMsgForwarder: return pyMsgForwarder_FromMsgForwarder(plMsgForwarder::Convert(pCre));
        case kOccluder: return pyOccluder_FromOccluder(plOccluder::Convert(pCre));
        case kMobileOccluder: return pyMobileOccluder_FromMobileOccluder(plMobileOccluder::Convert(pCre));
        case kMultistageBehMod: return pyMultistageBehMod_FromMultistageBehMod(plMultistageBehMod::Convert(pCre));
        case kInterfaceInfoModifier: return pyInterfaceInfoModifier_FromInterfaceInfoModifier(plInterfaceInfoModifier::Convert(pCre));
        case kPickingDetector: return pyPickingDetector_FromPickingDetector(plPickingDetector::Convert(pCre));
        case kLogicModBase: return pyLogicModBase_FromLogicModBase(plLogicModBase::Convert(pCre));
        case kLogicModifier: return pyLogicModifier_FromLogicModifier(plLogicModifier::Convert(pCre));
        case kAudible: return pyAudible_FromAudible(plAudible::Convert(pCre));
        case kAudibleNull: return pyAudibleNull_FromAudibleNull(plAudibleNull::Convert(pCre));
        case kWinAudible: return pyWinAudible_FromWinAudible(plWinAudible::Convert(pCre));
        case k2WayWinAudible: return py2WayWinAudible_From2WayWinAudible(pl2WayWinAudible::Convert(pCre));
        case kShadowCaster: return pyShadowCaster_FromShadowCaster(plShadowCaster::Convert(pCre));
        case kShadowMaster: return pyShadowMaster_FromShadowMaster(plShadowMaster::Convert(pCre));
        case kPointShadowMaster: return pyPointShadowMaster_FromPointShadowMaster(plPointShadowMaster::Convert(pCre));
        case kDirectShadowMaster: return pyDirectShadowMaster_FromDirectShadowMaster(plDirectShadowMaster::Convert(pCre));
        case kWaveSetBase: return pyWaveSetBase_FromWaveSetBase(plWaveSetBase::Convert(pCre));
        case kWaveSet7: return pyWaveSet7_FromWaveSet7(plWaveSet7::Convert(pCre));
        case kSoftVolume: return pySoftVolume_FromSoftVolume(plSoftVolume::Convert(pCre));
        case kSoftVolumeSimple: return pySoftVolumeSimple_FromSoftVolumeSimple(plSoftVolumeSimple::Convert(pCre));
        case kSoftVolumeComplex: return pySoftVolumeComplex_FromSoftVolumeComplex(plSoftVolumeComplex::Convert(pCre));
        case kSoftVolumeUnion: return pySoftVolumeUnion_FromSoftVolumeUnion(plSoftVolumeUnion::Convert(pCre));
        case kSoftVolumeIntersect: return pySoftVolumeIntersect_FromSoftVolumeIntersect(plSoftVolumeIntersect::Convert(pCre));
        case kSoftVolumeInvert: return pySoftVolumeInvert_FromSoftVolumeInvert(plSoftVolumeInvert::Convert(pCre));
        case kVisRegion: return pyVisRegion_FromVisRegion(plVisRegion::Convert(pCre));
        case kSwimRegionInterface: return pySwimRegionInterface_FromSwimRegionInterface(plSwimRegionInterface::Convert(pCre));
        case kSwimCircularCurrentRegion: return pySwimCircularCurrentRegion_FromSwimCircularCurrentRegion(plSwimCircularCurrentRegion::Convert(pCre));
        case kSwimStraightCurrentRegion: return pySwimStraightCurrentRegion_FromSwimStraightCurrentRegion(plSwimStraightCurrentRegion::Convert(pCre));
        case kSimpleRegionSensor: return pySimpleRegionSensor_FromSimpleRegionSensor(plSimpleRegionSensor::Convert(pCre));
        case kSwimDetector: return pySwimDetector_FromSwimDetector(plSwimDetector::Convert(pCre));
        case kSpaceTree: return pySpaceTree_FromSpaceTree(plSpaceTree::Convert(pCre));
        case kController: return pyController_FromController(plController::Convert(pCre));
        case kCompoundController: return pyCompoundController_FromCompoundController(plCompoundController::Convert(pCre));
        case kTMController: return pyTMController_FromTMController(plTMController::Convert(pCre));
        case kPosController: return pyPosController_FromPosController(plPosController::Convert(pCre));
        case kSimplePosController: return pySimplePosController_FromSimplePosController(plSimplePosController::Convert(pCre));
        case kCompoundPosController: return pyCompoundPosController_FromCompoundPosController(plCompoundPosController::Convert(pCre));
        case kRotController: return pyRotController_FromRotController(plRotController::Convert(pCre));
        case kSimpleRotController: return pySimpleRotController_FromSimpleRotController(plSimpleRotController::Convert(pCre));
        case kCompoundRotController: return pyCompoundRotController_FromCompoundRotController(plCompoundRotController::Convert(pCre));
        case kScaleController: return pyScaleController_FromScaleController(plScaleController::Convert(pCre));
        case kSimpleScaleController: return pySimpleScaleController_FromSimpleScaleController(plSimpleScaleController::Convert(pCre));
        case kLeafController: return pyLeafController_FromLeafController(plLeafController::Convert(pCre));
        case kEaseController: return pyEaseController_FromEaseController(plEaseController::Convert(pCre));
        case kMatrix33Controller: return pyMatrix33Controller_FromMatrix33Controller(plMatrix33Controller::Convert(pCre));
        case kMatrix44Controller: return pyMatrix44Controller_FromMatrix44Controller(plMatrix44Controller::Convert(pCre));
        case kPoint3Controller: return pyPoint3Controller_FromPoint3Controller(plPoint3Controller::Convert(pCre));
        case kQuatController: return pyQuatController_FromQuatController(plQuatController::Convert(pCre));
        case kScalarController: return pyScalarController_FromScalarController(plScalarController::Convert(pCre));
        case kScaleValueController: return pyScaleValueController_FromScaleValueController(plScaleValueController::Convert(pCre));
        case kATCEaseCurve: return pyATCEaseCurve_FromATCEaseCurve(plATCEaseCurve::Convert(pCre));
        case kSplineEaseCurve: return pySplineEaseCurve_FromSplineEaseCurve(plSplineEaseCurve::Convert(pCre));
        case kConstAccelEaseCurve: return pyConstAccelEaseCurve_FromConstAccelEaseCurve(plConstAccelEaseCurve::Convert(pCre));
        case kAnimTimeConvert: return pyAnimTimeConvert_FromAnimTimeConvert(plAnimTimeConvert::Convert(pCre));
        case kMessage: return pyMessage_FromMessage(plMessage::Convert(pCre));
        case kEventCallbackMsg: return pyEventCallbackMsg_FromEventCallbackMsg(plEventCallbackMsg::Convert(pCre));
        case kResponderEnableMsg: return pyResponderEnableMsg_FromResponderEnableMsg(plResponderEnableMsg::Convert(pCre));
        case kAGApplicator: return pyAGApplicator_FromAGApplicator(plAGApplicator::Convert(pCre));
        case kAGChannel: return pyAGChannel_FromAGChannel(plAGChannel::Convert(pCre));
        case kSoundVolumeApplicator: return pySoundVolumeApplicator_FromSoundVolumeApplicator(plSoundVolumeApplicator::Convert(pCre));
        case kLightAmbientApplicator: return pyLightAmbientApplicator_FromLightAmbientApplicator(plLightAmbientApplicator::Convert(pCre));
        case kLightDiffuseApplicator: return pyLightDiffuseApplicator_FromLightDiffuseApplicator(plLightDiffuseApplicator::Convert(pCre));
        case kLightSpecularApplicator: return pyLightSpecularApplicator_FromLightSpecularApplicator(plLightSpecularApplicator::Convert(pCre));
        case kOmniApplicator: return pyOmniApplicator_FromOmniApplicator(plOmniApplicator::Convert(pCre));
        case kOmniCutoffApplicator: return pyOmniCutoffApplicator_FromOmniCutoffApplicator(plOmniCutoffApplicator::Convert(pCre));
        case kOmniSqApplicator: return pyOmniSqApplicator_FromOmniSqApplicator(plOmniSqApplicator::Convert(pCre));
        case kSpotInnerApplicator: return pySpotInnerApplicator_FromSpotInnerApplicator(plSpotInnerApplicator::Convert(pCre));
        case kSpotOuterApplicator: return pySpotOuterApplicator_FromSpotOuterApplicator(plSpotOuterApplicator::Convert(pCre));
        case kMatrixChannel: return pyMatrixChannel_FromMatrixChannel(plMatrixChannel::Convert(pCre));
        case kMatrixBlend: return pyMatrixBlend_FromMatrixBlend(plMatrixBlend::Convert(pCre));
        case kMatrixConstant: return pyMatrixConstant_FromMatrixConstant(plMatrixConstant::Convert(pCre));
        case kMatrixControllerCacheChannel: return pyMatrixControllerCacheChannel_FromMatrixControllerCacheChannel(plMatrixControllerCacheChannel::Convert(pCre));
        case kMatrixControllerChannel: return pyMatrixControllerChannel_FromMatrixControllerChannel(plMatrixControllerChannel::Convert(pCre));
        case kMatrixTimeScale: return pyMatrixTimeScale_FromMatrixTimeScale(plMatrixTimeScale::Convert(pCre));
        case kQuatPointCombine: return pyQuatPointCombine_FromQuatPointCombine(plQuatPointCombine::Convert(pCre));
        case kMatrixChannelApplicator: return pyMatrixChannelApplicator_FromMatrixChannelApplicator(plMatrixChannelApplicator::Convert(pCre));
        case kMatrixDelayedCorrectionApplicator: return pyMatrixDelayedCorrectionApplicator_FromMatrixDelayedCorrectionApplicator(plMatrixDelayedCorrectionApplicator::Convert(pCre));
        case kMatrixDifferenceApp: return pyMatrixDifferenceApp_FromMatrixDifferenceApp(plMatrixDifferenceApp::Convert(pCre));
        case kRelativeMatrixChannelApplicator: return pyRelativeMatrixChannelApplicator_FromRelativeMatrixChannelApplicator(plRelativeMatrixChannelApplicator::Convert(pCre));
        case kPointChannel: return pyPointChannel_FromPointChannel(plPointChannel::Convert(pCre));
        case kPointBlend: return pyPointBlend_FromPointBlend(plPointBlend::Convert(pCre));
        case kPointConstant: return pyPointConstant_FromPointConstant(plPointConstant::Convert(pCre));
        case kPointControllerCacheChannel: return pyPointControllerCacheChannel_FromPointControllerCacheChannel(plPointControllerCacheChannel::Convert(pCre));
        case kPointControllerChannel: return pyPointControllerChannel_FromPointControllerChannel(plPointControllerChannel::Convert(pCre));
        case kPointTimeScale: return pyPointTimeScale_FromPointTimeScale(plPointTimeScale::Convert(pCre));
        case kPointChannelApplicator: return pyPointChannelApplicator_FromPointChannelApplicator(plPointChannelApplicator::Convert(pCre));
        case kQuatChannel: return pyQuatChannel_FromQuatChannel(plQuatChannel::Convert(pCre));
        case kQuatBlend: return pyQuatBlend_FromQuatBlend(plQuatBlend::Convert(pCre));
        case kQuatConstant: return pyQuatConstant_FromQuatConstant(plQuatConstant::Convert(pCre));
        case kQuatTimeScale: return pyQuatTimeScale_FromQuatTimeScale(plQuatTimeScale::Convert(pCre));
        case kQuatChannelApplicator: return pyQuatChannelApplicator_FromQuatChannelApplicator(plQuatChannelApplicator::Convert(pCre));
        case kScalarChannel: return pyScalarChannel_FromScalarChannel(plScalarChannel::Convert(pCre));
        case kScalarBlend: return pyScalarBlend_FromScalarBlend(plScalarBlend::Convert(pCre));
        case kScalarConstant: return pyScalarConstant_FromScalarConstant(plScalarConstant::Convert(pCre));
        case kScalarControllerCacheChannel: return pyScalarControllerCacheChannel_FromScalarControllerCacheChannel(plScalarControllerCacheChannel::Convert(pCre));
        case kScalarControllerChannel: return pyScalarControllerChannel_FromScalarControllerChannel(plScalarControllerChannel::Convert(pCre));
        case kScalarTimeScale: return pyScalarTimeScale_FromScalarTimeScale(plScalarTimeScale::Convert(pCre));
        case kScalarSDLChannel: return pyScalarSDLChannel_FromScalarSDLChannel(plScalarSDLChannel::Convert(pCre));
        case kATCChannel: return pyATCChannel_FromATCChannel(plATCChannel::Convert(pCre));
        case kScalarChannelApplicator: return pyScalarChannelApplicator_FromScalarChannelApplicator(plScalarChannelApplicator::Convert(pCre));
        case kAnimStage: return pyAnimStage_FromAnimStage(plAnimStage::Convert(pCre));
        case kLinkToAgeMsg: return pyLinkToAgeMsg_FromLinkToAgeMsg(plLinkToAgeMsg::Convert(pCre));
        case kNotifyMsg: return pyNotifyMsg_FromNotifyMsg(plNotifyMsg::Convert(pCre));
        case kAgeLinkStruct: return pyAgeLinkStruct_FromAgeLinkStruct(plAgeLinkStruct::Convert(pCre));
        case kAgeInfoStruct: return pyAgeInfoStruct_FromAgeInfoStruct(plAgeInfoStruct::Convert(pCre));
        case kArmatureEffectStateMsg: return pyArmatureEffectStateMsg_FromArmatureEffectStateMsg(plArmatureEffectStateMsg::Convert(pCre));
        case kCursorChangeMsg: return pyCursorChangeMsg_FromCursorChangeMsg(plCursorChangeMsg::Convert(pCre));
        case kResponderMsg: return pyResponderMsg_FromResponderMsg(plResponderMsg::Convert(pCre));
        case kOneShotMsg: return pyOneShotMsg_FromOneShotMsg(plOneShotMsg::Convert(pCre));
        case kMessageWithCallbacks: return pyMessageWithCallbacks_FromMessageWithCallbacks(plMessageWithCallbacks::Convert(pCre));
        case kAnimCmdMsg: return pyAnimCmdMsg_FromAnimCmdMsg(plAnimCmdMsg::Convert(pCre));
        case kTimerCallbackMsg: return pyTimerCallbackMsg_FromTimerCallbackMsg(plTimerCallbackMsg::Convert(pCre));
        case kEnableMsg: return pyEnableMsg_FromEnableMsg(plEnableMsg::Convert(pCre));
        case kExcludeRegionMsg: return pyExcludeRegionMsg_FromExcludeRegionMsg(plExcludeRegionMsg::Convert(pCre));
        case kVolumeIsect: return pyVolumeIsect_FromVolumeIsect(plVolumeIsect::Convert(pCre));
        case kConvexIsect: return pyConvexIsect_FromConvexIsect(plConvexIsect::Convert(pCre));
        case kSoundMsg: return pySoundMsg_FromSoundMsg(plSoundMsg::Convert(pCre));
        case kSwimMsg: return pySwimMsg_FromSwimMsg(plSwimMsg::Convert(pCre));
        case kGUIButtonMod: return pyGUIButtonMod_FromGUIButtonMod(pfGUIButtonMod::Convert(pCre));
        case kGUIMenuItem: return pyGUIMenuItem_FromGUIMenuItem(pfGUIMenuItem::Convert(pCre));
        case kGUICheckBoxCtrl: return pyGUICheckBoxCtrl_FromGUICheckBoxCtrl(pfGUICheckBoxCtrl::Convert(pCre));
        case kGUIControlMod: return pyGUIControlMod_FromGUIControlMod(pfGUIControlMod::Convert(pCre));
        case kGUIDialogMod: return pyGUIDialogMod_FromGUIDialogMod(pfGUIDialogMod::Convert(pCre));
        case kGUIDynDisplayCtrl: return pyGUIDynDisplayCtrl_FromGUIDynDisplayCtrl(pfGUIDynDisplayCtrl::Convert(pCre));
        case kGUIKnobCtrl: return pyGUIKnobCtrl_FromGUIKnobCtrl(pfGUIKnobCtrl::Convert(pCre));
        case kGUIListBoxMod: return pyGUIListBoxMod_FromGUIListBoxMod(pfGUIListBoxMod::Convert(pCre));
        case kGUIClickMapCtrl: return pyGUIClickMapCtrl_FromGUIClickMapCtrl(pfGUIClickMapCtrl::Convert(pCre));
        case kGUIDragBarCtrl: return pyGUIDragBarCtrl_FromGUIDragBarCtrl(pfGUIDragBarCtrl::Convert(pCre));
        case kGUIDraggableMod: return pyGUIDraggableMod_FromGUIDraggableMod(pfGUIDraggableMod::Convert(pCre));
        case kGUIEditBoxMod: return pyGUIEditBoxMod_FromGUIEditBoxMod(pfGUIEditBoxMod::Convert(pCre));
        case kGUIMultiLineEditCtrl: return pyGUIMultiLineEditCtrl_FromGUIMultiLineEditCtrl(pfGUIMultiLineEditCtrl::Convert(pCre));
        case kGUIPopUpMenu: return pyGUIPopUpMenu_FromGUIPopUpMenu(pfGUIPopUpMenu::Convert(pCre));
        case kGUIProgressCtrl: return pyGUIProgressCtrl_FromGUIProgressCtrl(pfGUIProgressCtrl::Convert(pCre));
        case kGUIRadioGroupCtrl: return pyGUIRadioGroupCtrl_FromGUIRadioGroupCtrl(pfGUIRadioGroupCtrl::Convert(pCre));
        case kGUISkin: return pyGUISkin_FromGUISkin(pfGUISkin::Convert(pCre));
        case kGUITextBoxMod: return pyGUITextBoxMod_FromGUITextBoxMod(pfGUITextBoxMod::Convert(pCre));
        case kGUIUpDownPairMod: return pyGUIUpDownPairMod_FromGUIUpDownPairMod(pfGUIUpDownPairMod::Convert(pCre));
        case kGUIValueCtrl: return pyGUIValueCtrl_FromGUIValueCtrl(pfGUIValueCtrl::Convert(pCre));
        case kImageLibMod: return pyImageLibMod_FromImageLibMod(plImageLibMod::Convert(pCre));
        case kPostEffectMod: return pyPostEffectMod_FromPostEffectMod(plPostEffectMod::Convert(pCre));
        case kAvLadderMod: return pyAvLadderMod_FromAvLadderMod(plAvLadderMod::Convert(pCre));
        case kLadderModifier: return pyLadderModifier_FromLadderModifier(plLadderModifier::Convert(pCre));
        case kCameraBrain: return pyCameraBrain_FromCameraBrain(plCameraBrain::Convert(pCre));
        case kCameraBrain1: return pyCameraBrain1_FromCameraBrain1(plCameraBrain1::Convert(pCre));
        case kCameraBrain1_Avatar: return pyCameraBrain1_Avatar_FromCameraBrain1_Avatar(plCameraBrain1_Avatar::Convert(pCre));
        case kCameraBrain1_FirstPerson: return pyCameraBrain1_FirstPerson_FromCameraBrain1_FirstPerson(plCameraBrain1_FirstPerson::Convert(pCre));
        case kCameraBrain1_Fixed: return pyCameraBrain1_Fixed_FromCameraBrain1_Fixed(plCameraBrain1_Fixed::Convert(pCre));
        case kCameraBrain1_Circle: return pyCameraBrain1_Circle_FromCameraBrain1_Circle(plCameraBrain1_Circle::Convert(pCre));
        case kCameraMsg: return pyCameraMsg_FromCameraMsg(plCameraMsg::Convert(pCre));
        case kCameraRegionDetector: return pyCameraRegionDetector_FromCameraRegionDetector(plCameraRegionDetector::Convert(pCre));
        case kCameraModifier: return pyCameraModifier_FromCameraModifier(plCameraModifier::Convert(pCre));
        case kAnimPath: return pyAnimPath_FromAnimPath(plAnimPath::Convert(pCre));
        case kLineFollowMod: return pyLineFollowMod_FromLineFollowMod(plLineFollowMod::Convert(pCre));
        case kRailCameraMod: return pyRailCameraMod_FromRailCameraMod(plRailCameraMod::Convert(pCre));
        case kFogEnvironment: return pyFogEnvironment_FromFogEnvironment(plFogEnvironment::Convert(pCre));
        case kConvexVolume: return pyConvexVolume_FromConvexVolume(plConvexVolume::Convert(pCre));
        case kBoundInterface: return pyBoundInterface_FromBoundInterface(plBoundInterface::Convert(pCre));
        case kParticleApplicator: return pyParticleApplicator_FromParticleApplicator(plParticleApplicator::Convert(pCre));
        case kParticleAngleApplicator: return pyParticleAngleApplicator_FromParticleAngleApplicator(plParticleAngleApplicator::Convert(pCre));
        case kParticleLifeMinApplicator: return pyParticleLifeMinApplicator_FromParticleLifeMinApplicator(plParticleLifeMinApplicator::Convert(pCre));
        case kParticleLifeMaxApplicator: return pyParticleLifeMaxApplicator_FromParticleLifeMaxApplicator(plParticleLifeMaxApplicator::Convert(pCre));
        case kParticlePPSApplicator: return pyParticlePPSApplicator_FromParticlePPSApplicator(plParticlePPSApplicator::Convert(pCre));
        case kParticleScaleMinApplicator: return pyParticleScaleMinApplicator_FromParticleScaleMinApplicator(plParticleScaleMinApplicator::Convert(pCre));
        case kParticleScaleMaxApplicator: return pyParticleScaleMaxApplicator_FromParticleScaleMaxApplicator(plParticleScaleMaxApplicator::Convert(pCre));
        case kParticleVelMinApplicator: return pyParticleVelMinApplicator_FromParticleVelMinApplicator(plParticleVelMinApplicator::Convert(pCre));
        case kParticleVelMaxApplicator: return pyParticleVelMaxApplicator_FromParticleVelMaxApplicator(plParticleVelMaxApplicator::Convert(pCre));
        case kParticleEffect: return pyParticleEffect_FromParticleEffect(plParticleEffect::Convert(pCre));
        case kParticleCollisionEffect: return pyParticleCollisionEffect_FromParticleCollisionEffect(plParticleCollisionEffect::Convert(pCre));
        case kParticleCollisionEffectBeat: return pyParticleCollisionEffectBeat_FromParticleCollisionEffectBeat(plParticleCollisionEffectBeat::Convert(pCre));
        case kParticleCollisionEffectBounce: return pyParticleCollisionEffectBounce_FromParticleCollisionEffectBounce(plParticleCollisionEffectBounce::Convert(pCre));
        case kParticleCollisionEffectDie: return pyParticleCollisionEffectDie_FromParticleCollisionEffectDie(plParticleCollisionEffectDie::Convert(pCre));
        case kParticleFadeOutEffect: return pyParticleFadeOutEffect_FromParticleFadeOutEffect(plParticleFadeOutEffect::Convert(pCre));
        case kParticleFadeVolumeEffect: return pyParticleFadeVolumeEffect_FromParticleFadeVolumeEffect(plParticleFadeVolumeEffect::Convert(pCre));
        case kParticleFlockEffect: return pyParticleFlockEffect_FromParticleFlockEffect(plParticleFlockEffect::Convert(pCre));
        case kParticleFollowSystemEffect: return pyParticleFollowSystemEffect_FromParticleFollowSystemEffect(plParticleFollowSystemEffect::Convert(pCre));
        case kParticleWindEffect: return pyParticleWindEffect_FromParticleWindEffect(plParticleWindEffect::Convert(pCre));
        case kParticleLocalWind: return pyParticleLocalWind_FromParticleLocalWind(plParticleLocalWind::Convert(pCre));
        case kParticleUniformWind: return pyParticleUniformWind_FromParticleUniformWind(plParticleUniformWind::Convert(pCre));
        case kParticleGenerator: return pyParticleGenerator_FromParticleGenerator(plParticleGenerator::Convert(pCre));
        case kOneTimeParticleGenerator: return pyOneTimeParticleGenerator_FromOneTimeParticleGenerator(plOneTimeParticleGenerator::Convert(pCre));
        case kSimpleParticleGenerator: return pySimpleParticleGenerator_FromSimpleParticleGenerator(plSimpleParticleGenerator::Convert(pCre));
        case kParticleEmitter: return pyParticleEmitter_FromParticleEmitter(plParticleEmitter::Convert(pCre));
        case kParticleSystem: return pyParticleSystem_FromParticleSystem(plParticleSystem::Convert(pCre));
        case kSimulationMsg: return pySimulationMsg_FromSimulationMsg(plSimulationMsg::Convert(pCre));
        case kSubWorldMsg: return pySubWorldMsg_FromSubWorldMsg(plSubWorldMsg::Convert(pCre));
        case kFilterCoordInterface: return pyFilterCoordInterface_FromFilterCoordInterface(plFilterCoordInterface::Convert(pCre));
        case kRidingAnimatedPhysicalDetector: return pyRidingAnimatedPhysicalDetector_FromRidingAnimatedPhysicalDetector(plRidingAnimatedPhysicalDetector::Convert(pCre));
        case kRideAnimatedPhysMsg: return pyRideAnimatedPhysMsg_FromRideAnimatedPhysMsg(plRideAnimatedPhysMsg::Convert(pCre));
        default:
            // many messages are not implemented, make sure they are at least a plMessage
            if (pCre->ClassInstance(kMessage))
                return pyMessage_FromMessage(plMessage::Convert(pCre));
            else if (pCre->ClassInstance(kKeyedObject))
                return pyKeyedObject_FromKeyedObject(hsKeyedObject::Convert(pCre));
            return pyCreatable_FromCreatable(pCre);
    }
}
