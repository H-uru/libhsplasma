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

#include <PyPlasma.h>
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
#include "PRP/Audio/plSoundBuffer.h"
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
#include "PRP/Avatar/plSittingModifier.h"
#include "PRP/Avatar/plSeekPointMod.h"
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
#include "PRP/Animation/pyAnimTimeConvert.h"
#include "PRP/Animation/pyATCEaseCurves.h"
#include "PRP/Animation/pyController.h"
#include "PRP/Animation/pyKeys.h"
#include "PRP/Animation/pyLeafController.h"
#include "PRP/Animation/pyPosController.h"
#include "PRP/Animation/pyRotController.h"
#include "PRP/Animation/pyScaleController.h"
#include "PRP/Animation/pyViewFaceModifier.h"
#include "PRP/Avatar/pyAGAnim.h"
#include "PRP/Avatar/pyAGApplicator.h"
#include "PRP/Avatar/pyAGChannel.h"
#include "PRP/Avatar/pyATCAnim.h"
#include "PRP/Avatar/pyMultistageBehMod.h"
#include "PRP/Audio/pyAudible.h"
#include "PRP/Audio/pySoundBuffer.h"
#include "PRP/ConditionalObject/pyActivatorConditionalObject.h"
#include "PRP/ConditionalObject/pyAnimationEventConditionalObject.h"
#include "PRP/ConditionalObject/pyBooleanConditionalObject.h"
#include "PRP/ConditionalObject/pyConditionalObject.h"
#include "PRP/ConditionalObject/pyControlEventConditionalObject.h"
#include "PRP/ConditionalObject/pyDetectConditionalObjects.h"
#include "PRP/ConditionalObject/pyVolumeSensorConditionalObject.h"
#include "PRP/Geometry/pyCluster.h"
#include "PRP/Geometry/pyClusterGroup.h"
#include "PRP/Geometry/pyDrawableSpans.h"
#include "PRP/Geometry/pyOccluder.h"
#include "PRP/Geometry/pySpaceTree.h"
#include "PRP/GUI/pyGUIControlHandlers.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/Light/pyLightInfo.h"
#include "PRP/Light/pyShadowMaster.h"
#include "PRP/Message/pyArmatureEffectMsg.h"
#include "PRP/Message/pyEventCallbackMsg.h"
#include "PRP/Message/pyMessage.h"
#include "PRP/Message/pyMsgForwarder.h"
#include "PRP/Message/pyNotifyMsg.h"
#include "PRP/Message/pyLinkToAgeMsg.h"
#include "PRP/Misc/pyRenderLevel.h"
#include "PRP/Misc/pyAgeLinkInfo.h"
#include "PRP/Modifier/pyInterfaceInfoModifier.h"
#include "PRP/Modifier/pyLogicModifier.h"
#include "PRP/Modifier/pyMaintainersMarkerModifier.h"
#include "PRP/Modifier/pyModifier.h"
#include "PRP/Modifier/pyOneShotMod.h"
#include "PRP/Modifier/pyPythonFileMod.h"
#include "PRP/Modifier/pyResponderModifier.h"
#include "PRP/Modifier/pySpawnModifier.h"
#include "PRP/Object/pyObjInterface.h"
#include "PRP/Object/pySceneObject.h"
#include "PRP/Object/pySynchedObject.h"
#include "PRP/Physics/pyCollisionDetector.h"
#include "PRP/Physics/pyDetectorModifier.h"
#include "PRP/Physics/pyObjectInVolumeDetector.h"
#include "PRP/Physics/pyPhysical.h"
#include "PRP/Region/pyBounds.h"
#include "PRP/Surface/pyBitmap.h"
#include "PRP/Surface/pyCubicEnvironmap.h"
#include "PRP/Surface/pyDynamicEnvMap.h"
#include "PRP/Surface/pyDynamicTextMap.h"
#include "PRP/Surface/pyGMaterial.h"
#include "PRP/Surface/pyGMatState.h"
#include "PRP/Surface/pyLayer.h"
#include "PRP/Surface/pyLayerAnimation.h"
#include "PRP/Surface/pyLayerMovie.h"
#include "PRP/Surface/pyRenderTarget.h"
#include "PRP/Surface/pyShader.h"
// End python includes

plCreatable* IConvert(pyCreatable* pCre)
{
    if (Py_TYPE(pCre) == &pySceneNode_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSceneNode*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pySceneObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSceneObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyKeyedObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<hsKeyedObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyBitmap_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plBitmap*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyMipmap_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plMipmap*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyCubicEnvironmap_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCubicEnvironmap*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLayer_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayer*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyGMaterial_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<hsGMaterial*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleSystem_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleSystem*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleCollisionEffectBeat_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleCollisionEffectBeat*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleFadeVolumeEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleFadeVolumeEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyBoundInterface_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plBoundInterface*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyRenderTarget_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plRenderTarget*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyCubicRenderTarget_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCubicRenderTarget*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCubicRenderTargetModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCubicRenderTargetModifier*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyObjInterface_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plObjInterface*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyAudioInterface_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAudioInterface*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyAudible_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAudible*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyAudibleNull_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAudibleNull*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyWinAudible_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plWinAudible*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyCoordinateInterface_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCoordinateInterface*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyDrawInterface_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawInterface*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyDrawable_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawable*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDrawableMesh_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawableMesh*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDrawableIce_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawableIce*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyPhysical_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPhysical*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPhysicalMesh_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPhysicalMesh*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pySimulationInterface_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSimulationInterface*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraModifier*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plModifier*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pySingleModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSingleModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySimpleModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSimpleModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySimpleTMModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSimpleTMModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyRandomTMModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plRandomTMModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyInterestingModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plInterestingModifier*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyDetectorModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDetectorModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySimplePhysicalMesh_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSimplePhysicalMesh*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCompoundPhysicalMesh_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCompoundPhysicalMesh*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyMultiModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plMultiModifier*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pySynchedObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSynchedObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pySoundBuffer_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSoundBuffer*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAliasModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAliasModifier*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyPickingDetector_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPickingDetector*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyCollisionDetector_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCollisionDetector*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLogicModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLogicModifier*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyANDConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plANDConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyORConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plORConditionalObject*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPickedConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPickedConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyActivatorConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plActivatorConditionalObject*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyTimerCallbackManager_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plTimerCallbackManager*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyKeyPressConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plKeyPressConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyAnimationEventConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAnimationEventConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyControlEventConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plControlEventConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyObjectInBoxConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plObjectInBoxConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLocalPlayerInBoxConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLocalPlayerInBoxConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyObjectIntersectPlaneConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plObjectIntersectPlaneConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLocalPlayerIntersectPlaneConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLocalPlayerIntersectPlaneConditionalObject*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPortalDrawable_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPortalDrawable*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPortalPhysical_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPortalPhysical*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pySpawnModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSpawnModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyFacingConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plFacingConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyGenericPhysical_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plGenericPhysical*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyViewFaceModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plViewFaceModifier*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLayerInterface_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerInterface*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLayerWrapper_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerWrapper*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLayerAnimation_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerAnimation*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLayerDepth_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerDepth*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLayerMovie_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerMovie*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLayerBink_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerBink*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLayerAVI_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerAVI*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySound_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSound*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyWin32Sound_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plWin32Sound*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLayerOr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerOr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAudioSystem_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAudioSystem*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyDrawableSpans_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawableSpans*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDrawablePatchSet_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawablePatchSet*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyInputManager_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plInputManager*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLogicModBase_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLogicModBase*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyFogEnvironment_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plFogEnvironment*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyNetApp_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plNetApp*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyNetClientMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plNetClientMgr*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &py2WayWinAudible_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pl2WayWinAudible*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLightInfo_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLightInfo*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyDirectionalLightInfo_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDirectionalLightInfo*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyOmniLightInfo_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plOmniLightInfo*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pySpotLightInfo_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSpotLightInfo*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLightSpace_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLightSpace*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyNetClientApp_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plNetClientApp*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyNetServerApp_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plNetServerApp*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyClient_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plClient*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCompoundTMModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCompoundTMModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_Default_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Default*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_Drive_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Drive*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_Fixed_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Fixed*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_FixedPan_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_FixedPan*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIClickMapCtrl_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIClickMapCtrl*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyListener_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plListener*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAvatarMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAvatarAnim_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarAnim*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAvatarAnimMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarAnimMgr*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyOccluder_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plOccluder*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyMobileOccluder_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plMobileOccluder*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLayerShadowBase_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerShadowBase*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLimitedDirLightInfo_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLimitedDirLightInfo*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyAGAnim_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAGAnim*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAGModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAGModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAGMasterMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAGMasterMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_Avatar_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Avatar*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraRegionDetector_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraRegionDetector*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_FP_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_FP*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLineFollowMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLineFollowMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLightModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLightModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyOmniModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plOmniModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySpotModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSpotModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLtdDirModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLtdDirModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySeekPointMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSeekPointMod*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyOneShotMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plOneShotMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyRandomCommandMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plRandomCommandMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyRandomSoundMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plRandomSoundMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPostEffectMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPostEffectMod*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyObjectInVolumeDetector_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plObjectInVolumeDetector*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyResponderModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plResponderModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAxisAnimModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAxisAnimModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLayerLightBase_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerLightBase*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyFollowMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plFollowMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyTransitionMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plTransitionMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyInventoryMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plInventoryMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyInventoryObjMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plInventoryObjMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLinkEffectsMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLinkEffectsMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyWin32StreamingSound_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plWin32StreamingSound*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPythonMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPythonMod*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyActivatorActivatorConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plActivatorActivatorConditionalObject*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySoftVolume_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolume*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySoftVolumeSimple_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolumeSimple*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySoftVolumeComplex_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolumeComplex*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySoftVolumeUnion_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolumeUnion*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySoftVolumeIntersect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolumeIntersect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySoftVolumeInvert_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolumeInvert*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyWin32LinkSound_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plWin32LinkSound*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLayerLinkAnimation_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerLinkAnimation*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyArmatureMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_Freelook_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Freelook*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyHavokConstraintsMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plHavokConstraintsMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyHingeConstraintMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plHingeConstraintMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyWheelConstraintMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plWheelConstraintMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyStrongSpringConstraintMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plStrongSpringConstraintMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyArmatureLODMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureLODMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyWin32StaticSound_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plWin32StaticSound*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGameGUIMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGameGUIMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIDialogMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIDialogMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain1_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyVirtualCam1_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plVirtualCam1*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain1_Drive_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Drive*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain1_POA_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_POA*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain1_Avatar_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Avatar*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain1_Fixed_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Fixed*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain1_POAFixed_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_POAFixed*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIButtonMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIButtonMod*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyPythonFileMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPythonFileMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIControlMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIControlMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyExcludeRegionModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plExcludeRegionModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIDraggableMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIDraggableMod*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyVolumeSensorConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plVolumeSensorConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyVolActivatorConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plVolActivatorConditionalObject*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyMsgForwarder_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plMsgForwarder*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyBlower_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plBlower*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIListBoxMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIListBoxMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUITextBoxMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUITextBoxMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIEditBoxMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIEditBoxMod*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyDynamicTextMap_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynamicTextMap*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySittingModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSittingModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIUpDownPairMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIUpDownPairMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIValueCtrl_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIValueCtrl*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIKnobCtrl_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIKnobCtrl*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAvLadderMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAvLadderMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain1_FirstPerson_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_FirstPerson*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCloneSpawnModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCloneSpawnModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyClothingItem_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plClothingItem*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyClothingOutfit_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plClothingOutfit*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyClothingBase_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plClothingBase*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyClothingMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plClothingMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIDragBarCtrl_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIDragBarCtrl*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUICheckBoxCtrl_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUICheckBoxCtrl*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIRadioGroupCtrl_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIRadioGroupCtrl*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPlayerBookMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfPlayerBookMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIDynDisplayCtrl_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIDynDisplayCtrl*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLayerProject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerProject*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyInputInterfaceMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plInputInterfaceMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyRailCameraMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plRailCameraMod*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyMultistageBehMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plMultistageBehMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain1_Circle_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Circle*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleWindEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleWindEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAnimEventModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAnimEventModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAutoProfile_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAutoProfile*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUISkin_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUISkin*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAVIWriter_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAVIWriter*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleCollisionEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleCollisionEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleCollisionEffectDie_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleCollisionEffectDie*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleCollisionEffectBounce_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleCollisionEffectBounce*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyInterfaceInfoModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plInterfaceInfoModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySharedMesh_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSharedMesh*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyArmatureEffectsMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureEffectsMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyMarkerMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfMarkerMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyVehicleModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plVehicleModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleLocalWind_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleLocalWind*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleUniformWind_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleUniformWind*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyInstanceDrawInterface_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plInstanceDrawInterface*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyShadowMaster_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plShadowMaster*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyShadowCaster_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plShadowCaster*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyPointShadowMaster_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPointShadowMaster*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyDirectShadowMaster_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDirectShadowMaster*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPhysicalSDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPhysicalSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyClothingSDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plClothingSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAvatarSDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAGMasterSDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAGMasterSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPythonSDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPythonSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLayerSDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAnimTimeConvertSDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAnimTimeConvertSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyResponderSDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plResponderSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySoundSDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSoundSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyResManagerHelper_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plResManagerHelper*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyHKSubWorld_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plHKSubWorld*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyArmatureEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyArmatureEffectFootSound_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureEffectFootSound*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyEAXListenerMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plEAXListenerMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDynaDecalMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaDecalMgr*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyObjectInVolumeAndFacingDetector_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plObjectInVolumeAndFacingDetector*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDynaFootMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaFootMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDynaRippleMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaRippleMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDynaBulletMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaBulletMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDecalEnableMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDecalEnableMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPrintShape_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPrintShape*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDynaPuddleMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaPuddleMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIMultiLineEditCtrl_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIMultiLineEditCtrl*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLayerAnimationBase_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerAnimationBase*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyLayerSDLAnimation_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerSDLAnimation*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyATCAnim_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plATCAnim*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyAgeGlobalAnim_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAgeGlobalAnim*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pySubworldRegionDetector_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSubworldRegionDetector*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAvatarMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyNPCSpawnMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plNPCSpawnMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyActivePrintShape_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plActivePrintShape*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyExcludeRegionSDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plExcludeRegionSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLOSDispatch_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLOSDispatch*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDynaWakeMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaWakeMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySimulationMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSimulationMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyWaveSet7_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plWaveSet7*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyPanicLinkRegion_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPanicLinkRegion*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyWin32GroupedSound_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plWin32GroupedSound*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyFilterCoordInterface_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plFilterCoordInterface*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyStereizer_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plStereizer*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCCRMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCCRMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCCRSpecialist_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCCRSpecialist*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCCRSeniorSpecialist_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCCRSeniorSpecialist*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCCRShiftSupervisor_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCCRShiftSupervisor*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCCRGameOperator_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCCRGameOperator*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyShader_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plShader*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyDynamicEnvMap_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynamicEnvMap*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySimpleRegionSensor_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSimpleRegionSensor*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyMorphSequence_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plMorphSequence*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyEmoteAnim_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plEmoteAnim*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDynaRippleVSMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaRippleVSMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyWaveSet6_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plWaveSet6*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIProgressCtrl_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIProgressCtrl*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyMaintainersMarkerModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plMaintainersMarkerModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyMorphSequenceSDLMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plMorphSequenceSDLMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyMorphDataSet_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plMorphDataSet*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyHardRegion_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegion*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyHardRegionPlanes_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegionPlanes*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyHardRegionComplex_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegionComplex*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyHardRegionUnion_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegionUnion*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyHardRegionIntersect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegionIntersect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyHardRegionInvert_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegionInvert*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyVisRegion_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plVisRegion*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyVisMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plVisMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyRegionBase_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plRegionBase*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIPopUpMenu_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIPopUpMenu*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUIMenuItem_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIMenuItem*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCoopCoordinator_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCoopCoordinator*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyFont_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plFont*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyFontCache_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plFontCache*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyRelevanceRegion_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plRelevanceRegion*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyRelevanceMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plRelevanceMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyJournalBook_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfJournalBook*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLayerTargetContainer_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerTargetContainer*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyImageLibMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plImageLibMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleFlockEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleFlockEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleSDLMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleSDLMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAgeLoader_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAgeLoader*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyWaveSetBase_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plWaveSetBase*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPhysicalSndGroup_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPhysicalSndGroup*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyBookData_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfBookData*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDynaTorpedoMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaTorpedoMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDynaTorpedoVSMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaTorpedoVSMgr*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyClusterGroup_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plClusterGroup*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGameMarkerModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plGameMarkerModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLODMipmap_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLODMipmap*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySwimDetector_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSwimDetector*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyFadeOpacityMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plFadeOpacityMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyFadeOpacityLay_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plFadeOpacityLay*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDistOpacityMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDistOpacityMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyArmatureModBase_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureModBase*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySwimRegionInterface_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSwimRegionInterface*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySwimCircularCurrentRegion_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSwimCircularCurrentRegion*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleFollowSystemEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleFollowSystemEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySwimStraightCurrentRegion_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSwimStraightCurrentRegion*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyObjectFlocker_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfObjectFlocker*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGrassShaderMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plGrassShaderMod*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyDynamicCamMap_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDynamicCamMap*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAutoWalkRegion_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAutoWalkRegion*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCrossfade_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCrossfade*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleFadeOutEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleFadeOutEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySecurePreloader_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfSecurePreloader*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyWindBoneMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plWindBoneMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_NovicePlus_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_NovicePlus*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySubtitleMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfSubtitleMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPythonFileModConditionalObject_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPythonFileModConditionalObject*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLayerTransform_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerTransform*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyBubbleShaderMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plBubbleShaderMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLineFollowModBase_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLineFollowModBase*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyClientApp_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plClientApp*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUICreditsCtrl_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUICreditsCtrl*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrainUru_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyVirtualCamera_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plVirtualCamera*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrainUru_Drive_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Drive*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrainUru_Follow_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Avatar*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrainUru_Fixed_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Fixed*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGUISketchCtrl_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUISketchCtrl*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyLadderModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plLadderModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrainUru_FirstPerson_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_FirstPerson*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrainUru_Circle_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Circle*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyEAXReverbEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plEAXReverbEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySpawnMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSpawnMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_Novice_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Novice*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyAvatarPhysicalSDLModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarPhysicalSDLModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyDirectMusicSound_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plDirectMusicSound*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyClientSessionMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plClientSessionMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pySDLVarChangeNotifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plSDLVarChangeNotifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyInterestWellModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plInterestWellModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyElevatorModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plElevatorModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_Expert_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Expert*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPagingRegionModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPagingRegionModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyGuidepathModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plGuidepathModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyNodeMgr_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<pfNodeMgr*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyEAXEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plEAXEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyEAXPitchShifter_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plEAXPitchShifter*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyIKModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plIKModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_M5_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_M5*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyAGAnimBink_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plAGAnimBink*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyTreeShader_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plTreeShader*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyNodeRegionModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plNodeRegionModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyPiranhaRegionModifier_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plPiranhaRegionModifier*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyRidingAnimatedPhysicalDetector_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plRidingAnimatedPhysicalDetector*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyVolumeSensorConditionalObjectNoArbitration_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plVolumeSensorConditionalObjectNoArbitration*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyFXMaterial_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plFXMaterial*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyMovableMod_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plMovableMod*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyMaterial_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plMaterial*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyParticleBulletEffect_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleBulletEffect*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_Ground_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Ground*>(pCre->fThis));
    //else if (Py_TYPE(pCre) == &pyCameraBrain_Flight_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Flight*>(pCre->fThis));

    else if (Py_TYPE(pCre) == &pyKeyedObjectStub_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<hsKeyedObjectStub*>(pCre->fThis));
    else if (Py_TYPE(pCre) == &pyCreatableStub_Type) return dynamic_cast<plCreatable*>(reinterpret_cast<plCreatableStub*>(pCre->fThis));
    else return pCre->fThis;
}

PyObject* ICreate(plCreatable* pCre)
{
    if (pCre == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    if ((typeid(*pCre)) == typeid(hsKeyedObjectStub)) return pyKeyedObjectStub_FromKeyedObjectStub(dynamic_cast<hsKeyedObjectStub*>(pCre));
    if ((typeid(*pCre)) == typeid(plCreatableStub)) return pyCreatableStub_FromCreatableStub(dynamic_cast<plCreatableStub*>(pCre));
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
        case kDynamicEnvMap: return pyDynamicEnvMap_FromDynamicEnvMap(plDynamicEnvMap::Convert(pCre));
        case kDynamicCamMap: return pyDynamicCamMap_FromDynamicCamMap(plDynamicCamMap::Convert(pCre));
        case kDynamicTextMap: return pyDynamicTextMap_FromDynamicTextMap(plDynamicTextMap::Convert(pCre));
        case kAGAnim: return pyAGAnim_FromAGAnim(plAGAnim::Convert(pCre));
        case kAgeGlobalAnim: return pyAgeGlobalAnim_FromAgeGlobalAnim(plAgeGlobalAnim::Convert(pCre));
        case kATCAnim: return pyATCAnim_FromATCAnim(plATCAnim::Convert(pCre));
        case kSubworldRegionDetector: return pySubworldRegionDetector_FromSubworldRegionDetector(plSubworldRegionDetector::Convert(pCre));
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
        case kShadowMaster: return pyShadowMaster_FromShadowMaster(plShadowMaster::Convert(pCre));
        case kPointShadowMaster: return pyPointShadowMaster_FromPointShadowMaster(plPointShadowMaster::Convert(pCre));
        case kDirectShadowMaster: return pyDirectShadowMaster_FromDirectShadowMaster(plDirectShadowMaster::Convert(pCre));
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
        default:
            // many messages are not implemented, make sure they are at least a plMessage
            if (dynamic_cast<plMessage*>(pCre)) return pyMessage_FromMessage(plMessage::Convert(pCre));
            return pyCreatable_FromCreatable(pCre);
    }
}
