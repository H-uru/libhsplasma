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

// Includes for all KeyedObject types
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
#include "PRP/Message/plMsgForwarder.h"
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
#include "PRP/Surface/plShader.h"
#include "PRP/Surface/plWaveSet.h"
// End type includes

plCreatable* IConvert(pyCreatable* pCre)
{
    switch (pCre->fClsType) {
        case kSceneNode: return dynamic_cast<plCreatable*>(reinterpret_cast<plSceneNode*>(pCre->fThis));
        case kSceneObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plSceneObject*>(pCre->fThis));
        case kKeyedObject: return dynamic_cast<plCreatable*>(reinterpret_cast<hsKeyedObject*>(pCre->fThis));
        case kBitmap: return dynamic_cast<plCreatable*>(reinterpret_cast<plBitmap*>(pCre->fThis));
        case kMipmap: return dynamic_cast<plCreatable*>(reinterpret_cast<plMipmap*>(pCre->fThis));
        case kCubicEnvironmap: return dynamic_cast<plCreatable*>(reinterpret_cast<plCubicEnvironmap*>(pCre->fThis));
        case kLayer: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayer*>(pCre->fThis));
        case kGMaterial: return dynamic_cast<plCreatable*>(reinterpret_cast<hsGMaterial*>(pCre->fThis));
        case kParticleSystem: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleSystem*>(pCre->fThis));
        case kParticleEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleEffect*>(pCre->fThis));
        case kParticleCollisionEffectBeat: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleCollisionEffectBeat*>(pCre->fThis));
        case kParticleFadeVolumeEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleFadeVolumeEffect*>(pCre->fThis));
        case kBoundInterface: return dynamic_cast<plCreatable*>(reinterpret_cast<plBoundInterface*>(pCre->fThis));
        case kRenderTarget: return dynamic_cast<plCreatable*>(reinterpret_cast<plRenderTarget*>(pCre->fThis));
        case kCubicRenderTarget: return dynamic_cast<plCreatable*>(reinterpret_cast<plCubicRenderTarget*>(pCre->fThis));
        //case kCubicRenderTargetModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plCubicRenderTargetModifier*>(pCre->fThis));
        case kObjInterface: return dynamic_cast<plCreatable*>(reinterpret_cast<plObjInterface*>(pCre->fThis));
        case kAudioInterface: return dynamic_cast<plCreatable*>(reinterpret_cast<plAudioInterface*>(pCre->fThis));
        case kAudible: return dynamic_cast<plCreatable*>(reinterpret_cast<plAudible*>(pCre->fThis));
        case kAudibleNull: return dynamic_cast<plCreatable*>(reinterpret_cast<plAudibleNull*>(pCre->fThis));
        case kWinAudible: return dynamic_cast<plCreatable*>(reinterpret_cast<plWinAudible*>(pCre->fThis));
        case kCoordinateInterface: return dynamic_cast<plCreatable*>(reinterpret_cast<plCoordinateInterface*>(pCre->fThis));
        case kDrawInterface: return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawInterface*>(pCre->fThis));
        case kDrawable: return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawable*>(pCre->fThis));
        //case kDrawableMesh: return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawableMesh*>(pCre->fThis));
        //case kDrawableIce: return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawableIce*>(pCre->fThis));
        case kPhysical: return dynamic_cast<plCreatable*>(reinterpret_cast<plPhysical*>(pCre->fThis));
        //case kPhysicalMesh: return dynamic_cast<plCreatable*>(reinterpret_cast<plPhysicalMesh*>(pCre->fThis));
        case kSimulationInterface: return dynamic_cast<plCreatable*>(reinterpret_cast<plSimulationInterface*>(pCre->fThis));
        case kCameraModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraModifier*>(pCre->fThis));
        case kModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plModifier*>(pCre->fThis));
        case kSingleModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plSingleModifier*>(pCre->fThis));
        //case kSimpleModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plSimpleModifier*>(pCre->fThis));
        //case kSimpleTMModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plSimpleTMModifier*>(pCre->fThis));
        //case kRandomTMModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plRandomTMModifier*>(pCre->fThis));
        //case kInterestingModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plInterestingModifier*>(pCre->fThis));
        case kDetectorModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plDetectorModifier*>(pCre->fThis));
        //case kSimplePhysicalMesh: return dynamic_cast<plCreatable*>(reinterpret_cast<plSimplePhysicalMesh*>(pCre->fThis));
        //case kCompoundPhysicalMesh: return dynamic_cast<plCreatable*>(reinterpret_cast<plCompoundPhysicalMesh*>(pCre->fThis));
        case kMultiModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plMultiModifier*>(pCre->fThis));
        case kSynchedObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plSynchedObject*>(pCre->fThis));
        case kSoundBuffer: return dynamic_cast<plCreatable*>(reinterpret_cast<plSoundBuffer*>(pCre->fThis));
        case kAliasModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plAliasModifier*>(pCre->fThis));
        case kPickingDetector: return dynamic_cast<plCreatable*>(reinterpret_cast<plPickingDetector*>(pCre->fThis));
        case kCollisionDetector: return dynamic_cast<plCreatable*>(reinterpret_cast<plCollisionDetector*>(pCre->fThis));
        case kLogicModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plLogicModifier*>(pCre->fThis));
        case kConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plConditionalObject*>(pCre->fThis));
        case kANDConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plANDConditionalObject*>(pCre->fThis));
        case kORConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plORConditionalObject*>(pCre->fThis));
        case kPickedConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plPickedConditionalObject*>(pCre->fThis));
        case kActivatorConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plActivatorConditionalObject*>(pCre->fThis));
        //case kTimerCallbackManager: return dynamic_cast<plCreatable*>(reinterpret_cast<plTimerCallbackManager*>(pCre->fThis));
        case kKeyPressConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plKeyPressConditionalObject*>(pCre->fThis));
        case kAnimationEventConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plAnimationEventConditionalObject*>(pCre->fThis));
        case kControlEventConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plControlEventConditionalObject*>(pCre->fThis));
        case kObjectInBoxConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plObjectInBoxConditionalObject*>(pCre->fThis));
        case kLocalPlayerInBoxConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plLocalPlayerInBoxConditionalObject*>(pCre->fThis));
        case kObjectIntersectPlaneConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plObjectIntersectPlaneConditionalObject*>(pCre->fThis));
        case kLocalPlayerIntersectPlaneConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plLocalPlayerIntersectPlaneConditionalObject*>(pCre->fThis));
        //case kPortalDrawable: return dynamic_cast<plCreatable*>(reinterpret_cast<plPortalDrawable*>(pCre->fThis));
        //case kPortalPhysical: return dynamic_cast<plCreatable*>(reinterpret_cast<plPortalPhysical*>(pCre->fThis));
        case kSpawnModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plSpawnModifier*>(pCre->fThis));
        case kFacingConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plFacingConditionalObject*>(pCre->fThis));
        case kGenericPhysical: return dynamic_cast<plCreatable*>(reinterpret_cast<plGenericPhysical*>(pCre->fThis));
        case kViewFaceModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plViewFaceModifier*>(pCre->fThis));
        case kLayerInterface: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerInterface*>(pCre->fThis));
        //case kLayerWrapper: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerWrapper*>(pCre->fThis));
        case kLayerAnimation: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerAnimation*>(pCre->fThis));
        case kLayerDepth: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerDepth*>(pCre->fThis));
        case kLayerMovie: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerMovie*>(pCre->fThis));
        case kLayerBink: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerBink*>(pCre->fThis));
        case kLayerAVI: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerAVI*>(pCre->fThis));
        case kSound: return dynamic_cast<plCreatable*>(reinterpret_cast<plSound*>(pCre->fThis));
        case kWin32Sound: return dynamic_cast<plCreatable*>(reinterpret_cast<plWin32Sound*>(pCre->fThis));
        //case kLayerOr: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerOr*>(pCre->fThis));
        //case kAudioSystem: return dynamic_cast<plCreatable*>(reinterpret_cast<plAudioSystem*>(pCre->fThis));
        case kDrawableSpans: return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawableSpans*>(pCre->fThis));
        //case kDrawablePatchSet: return dynamic_cast<plCreatable*>(reinterpret_cast<plDrawablePatchSet*>(pCre->fThis));
        //case kInputManager: return dynamic_cast<plCreatable*>(reinterpret_cast<plInputManager*>(pCre->fThis));
        case kLogicModBase: return dynamic_cast<plCreatable*>(reinterpret_cast<plLogicModBase*>(pCre->fThis));
        case kFogEnvironment: return dynamic_cast<plCreatable*>(reinterpret_cast<plFogEnvironment*>(pCre->fThis));
        //case kNetApp: return dynamic_cast<plCreatable*>(reinterpret_cast<plNetApp*>(pCre->fThis));
        //case kNetClientMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plNetClientMgr*>(pCre->fThis));
        case k2WayWinAudible: return dynamic_cast<plCreatable*>(reinterpret_cast<pl2WayWinAudible*>(pCre->fThis));
        case kLightInfo: return dynamic_cast<plCreatable*>(reinterpret_cast<plLightInfo*>(pCre->fThis));
        case kDirectionalLightInfo: return dynamic_cast<plCreatable*>(reinterpret_cast<plDirectionalLightInfo*>(pCre->fThis));
        case kOmniLightInfo: return dynamic_cast<plCreatable*>(reinterpret_cast<plOmniLightInfo*>(pCre->fThis));
        case kSpotLightInfo: return dynamic_cast<plCreatable*>(reinterpret_cast<plSpotLightInfo*>(pCre->fThis));
        //case kLightSpace: return dynamic_cast<plCreatable*>(reinterpret_cast<plLightSpace*>(pCre->fThis));
        //case kNetClientApp: return dynamic_cast<plCreatable*>(reinterpret_cast<plNetClientApp*>(pCre->fThis));
        //case kNetServerApp: return dynamic_cast<plCreatable*>(reinterpret_cast<plNetServerApp*>(pCre->fThis));
        //case kClient: return dynamic_cast<plCreatable*>(reinterpret_cast<plClient*>(pCre->fThis));
        //case kCompoundTMModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plCompoundTMModifier*>(pCre->fThis));
        case kCameraBrain: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain*>(pCre->fThis));
        //case kCameraBrain_Default: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Default*>(pCre->fThis));
        //case kCameraBrain_Drive: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Drive*>(pCre->fThis));
        //case kCameraBrain_Fixed: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Fixed*>(pCre->fThis));
        //case kCameraBrain_FixedPan: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_FixedPan*>(pCre->fThis));
        case kGUIClickMapCtrl: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIClickMapCtrl*>(pCre->fThis));
        //case kListener: return dynamic_cast<plCreatable*>(reinterpret_cast<plListener*>(pCre->fThis));
        //case kAvatarMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarMod*>(pCre->fThis));
        //case kAvatarAnim: return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarAnim*>(pCre->fThis));
        //case kAvatarAnimMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarAnimMgr*>(pCre->fThis));
        case kOccluder: return dynamic_cast<plCreatable*>(reinterpret_cast<plOccluder*>(pCre->fThis));
        case kMobileOccluder: return dynamic_cast<plCreatable*>(reinterpret_cast<plMobileOccluder*>(pCre->fThis));
        //case kLayerShadowBase: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerShadowBase*>(pCre->fThis));
        case kLimitedDirLightInfo: return dynamic_cast<plCreatable*>(reinterpret_cast<plLimitedDirLightInfo*>(pCre->fThis));
        case kAGAnim: return dynamic_cast<plCreatable*>(reinterpret_cast<plAGAnim*>(pCre->fThis));
        case kAGModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plAGModifier*>(pCre->fThis));
        case kAGMasterMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plAGMasterMod*>(pCre->fThis));
        //case kCameraBrain_Avatar: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Avatar*>(pCre->fThis));
        case kCameraRegionDetector: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraRegionDetector*>(pCre->fThis));
        //case kCameraBrain_FP: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_FP*>(pCre->fThis));
        case kLineFollowMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plLineFollowMod*>(pCre->fThis));
        //case kLightModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plLightModifier*>(pCre->fThis));
        //case kOmniModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plOmniModifier*>(pCre->fThis));
        //case kSpotModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plSpotModifier*>(pCre->fThis));
        //case kLtdDirModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plLtdDirModifier*>(pCre->fThis));
        case kSeekPointMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plSeekPointMod*>(pCre->fThis));
        case kOneShotMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plOneShotMod*>(pCre->fThis));
        case kRandomCommandMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plRandomCommandMod*>(pCre->fThis));
        case kRandomSoundMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plRandomSoundMod*>(pCre->fThis));
        case kPostEffectMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plPostEffectMod*>(pCre->fThis));
        case kObjectInVolumeDetector: return dynamic_cast<plCreatable*>(reinterpret_cast<plObjectInVolumeDetector*>(pCre->fThis));
        case kResponderModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plResponderModifier*>(pCre->fThis));
        case kAxisAnimModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plAxisAnimModifier*>(pCre->fThis));
        //case kLayerLightBase: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerLightBase*>(pCre->fThis));
        //case kFollowMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plFollowMod*>(pCre->fThis));
        //case kTransitionMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plTransitionMgr*>(pCre->fThis));
        //case kInventoryMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plInventoryMod*>(pCre->fThis));
        //case kInventoryObjMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plInventoryObjMod*>(pCre->fThis));
        //case kLinkEffectsMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plLinkEffectsMgr*>(pCre->fThis));
        case kWin32StreamingSound: return dynamic_cast<plCreatable*>(reinterpret_cast<plWin32StreamingSound*>(pCre->fThis));
        case kPythonMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plPythonMod*>(pCre->fThis));
        case kActivatorActivatorConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plActivatorActivatorConditionalObject*>(pCre->fThis));
        case kSoftVolume: return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolume*>(pCre->fThis));
        case kSoftVolumeSimple: return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolumeSimple*>(pCre->fThis));
        case kSoftVolumeComplex: return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolumeComplex*>(pCre->fThis));
        case kSoftVolumeUnion: return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolumeUnion*>(pCre->fThis));
        case kSoftVolumeIntersect: return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolumeIntersect*>(pCre->fThis));
        case kSoftVolumeInvert: return dynamic_cast<plCreatable*>(reinterpret_cast<plSoftVolumeInvert*>(pCre->fThis));
        case kWin32LinkSound: return dynamic_cast<plCreatable*>(reinterpret_cast<plWin32LinkSound*>(pCre->fThis));
        case kLayerLinkAnimation: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerLinkAnimation*>(pCre->fThis));
        case kArmatureMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureMod*>(pCre->fThis));
        //case kCameraBrain_Freelook: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Freelook*>(pCre->fThis));
        //case kHavokConstraintsMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plHavokConstraintsMod*>(pCre->fThis));
        //case kHingeConstraintMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plHingeConstraintMod*>(pCre->fThis));
        //case kWheelConstraintMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plWheelConstraintMod*>(pCre->fThis));
        //case kStrongSpringConstraintMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plStrongSpringConstraintMod*>(pCre->fThis));
        case kArmatureLODMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureLODMod*>(pCre->fThis));
        case kWin32StaticSound: return dynamic_cast<plCreatable*>(reinterpret_cast<plWin32StaticSound*>(pCre->fThis));
        //case kGameGUIMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGameGUIMgr*>(pCre->fThis));
        case kGUIDialogMod: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIDialogMod*>(pCre->fThis));
        case kCameraBrain1: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1*>(pCre->fThis));
        //case kVirtualCam1: return dynamic_cast<plCreatable*>(reinterpret_cast<plVirtualCam1*>(pCre->fThis));
        case kCameraBrain1_Drive: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Drive*>(pCre->fThis));
        //case kCameraBrain1_POA: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_POA*>(pCre->fThis));
        case kCameraBrain1_Avatar: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Avatar*>(pCre->fThis));
        case kCameraBrain1_Fixed: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Fixed*>(pCre->fThis));
        //case kCameraBrain1_POAFixed: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_POAFixed*>(pCre->fThis));
        case kGUIButtonMod: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIButtonMod*>(pCre->fThis));
        case kPythonFileMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plPythonFileMod*>(pCre->fThis));
        case kGUIControlMod: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIControlMod*>(pCre->fThis));
        case kExcludeRegionModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plExcludeRegionModifier*>(pCre->fThis));
        case kGUIDraggableMod: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIDraggableMod*>(pCre->fThis));
        case kVolumeSensorConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plVolumeSensorConditionalObject*>(pCre->fThis));
        case kVolActivatorConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plVolActivatorConditionalObject*>(pCre->fThis));
        case kMsgForwarder: return dynamic_cast<plCreatable*>(reinterpret_cast<plMsgForwarder*>(pCre->fThis));
        case kBlower: return dynamic_cast<plCreatable*>(reinterpret_cast<plBlower*>(pCre->fThis));
        case kGUIListBoxMod: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIListBoxMod*>(pCre->fThis));
        case kGUITextBoxMod: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUITextBoxMod*>(pCre->fThis));
        case kGUIEditBoxMod: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIEditBoxMod*>(pCre->fThis));
        case kDynamicTextMap: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynamicTextMap*>(pCre->fThis));
        case kSittingModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plSittingModifier*>(pCre->fThis));
        case kGUIUpDownPairMod: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIUpDownPairMod*>(pCre->fThis));
        case kGUIValueCtrl: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIValueCtrl*>(pCre->fThis));
        case kGUIKnobCtrl: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIKnobCtrl*>(pCre->fThis));
        case kAvLadderMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plAvLadderMod*>(pCre->fThis));
        case kCameraBrain1_FirstPerson: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_FirstPerson*>(pCre->fThis));
        //case kCloneSpawnModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plCloneSpawnModifier*>(pCre->fThis));
        case kClothingItem: return dynamic_cast<plCreatable*>(reinterpret_cast<plClothingItem*>(pCre->fThis));
        case kClothingOutfit: return dynamic_cast<plCreatable*>(reinterpret_cast<plClothingOutfit*>(pCre->fThis));
        case kClothingBase: return dynamic_cast<plCreatable*>(reinterpret_cast<plClothingBase*>(pCre->fThis));
        //case kClothingMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plClothingMgr*>(pCre->fThis));
        case kGUIDragBarCtrl: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIDragBarCtrl*>(pCre->fThis));
        case kGUICheckBoxCtrl: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUICheckBoxCtrl*>(pCre->fThis));
        case kGUIRadioGroupCtrl: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIRadioGroupCtrl*>(pCre->fThis));
        //case kPlayerBookMod: return dynamic_cast<plCreatable*>(reinterpret_cast<pfPlayerBookMod*>(pCre->fThis));
        case kGUIDynDisplayCtrl: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIDynDisplayCtrl*>(pCre->fThis));
        //case kLayerProject: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerProject*>(pCre->fThis));
        //case kInputInterfaceMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plInputInterfaceMgr*>(pCre->fThis));
        case kRailCameraMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plRailCameraMod*>(pCre->fThis));
        case kMultistageBehMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plMultistageBehMod*>(pCre->fThis));
        case kCameraBrain1_Circle: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Circle*>(pCre->fThis));
        case kParticleWindEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleWindEffect*>(pCre->fThis));
        case kAnimEventModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plAnimEventModifier*>(pCre->fThis));
        //case kAutoProfile: return dynamic_cast<plCreatable*>(reinterpret_cast<plAutoProfile*>(pCre->fThis));
        case kGUISkin: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUISkin*>(pCre->fThis));
        //case kAVIWriter: return dynamic_cast<plCreatable*>(reinterpret_cast<plAVIWriter*>(pCre->fThis));
        case kParticleCollisionEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleCollisionEffect*>(pCre->fThis));
        case kParticleCollisionEffectDie: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleCollisionEffectDie*>(pCre->fThis));
        case kParticleCollisionEffectBounce: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleCollisionEffectBounce*>(pCre->fThis));
        case kInterfaceInfoModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plInterfaceInfoModifier*>(pCre->fThis));
        case kSharedMesh: return dynamic_cast<plCreatable*>(reinterpret_cast<plSharedMesh*>(pCre->fThis));
        case kArmatureEffectsMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureEffectsMgr*>(pCre->fThis));
        //case kMarkerMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<pfMarkerMgr*>(pCre->fThis));
        case kVehicleModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plVehicleModifier*>(pCre->fThis));
        case kParticleLocalWind: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleLocalWind*>(pCre->fThis));
        case kParticleUniformWind: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleUniformWind*>(pCre->fThis));
        case kInstanceDrawInterface: return dynamic_cast<plCreatable*>(reinterpret_cast<plInstanceDrawInterface*>(pCre->fThis));
        case kShadowMaster: return dynamic_cast<plCreatable*>(reinterpret_cast<plShadowMaster*>(pCre->fThis));
        case kShadowCaster: return dynamic_cast<plCreatable*>(reinterpret_cast<plShadowCaster*>(pCre->fThis));
        case kPointShadowMaster: return dynamic_cast<plCreatable*>(reinterpret_cast<plPointShadowMaster*>(pCre->fThis));
        case kDirectShadowMaster: return dynamic_cast<plCreatable*>(reinterpret_cast<plDirectShadowMaster*>(pCre->fThis));
        //case kSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plSDLModifier*>(pCre->fThis));
        //case kPhysicalSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plPhysicalSDLModifier*>(pCre->fThis));
        //case kClothingSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plClothingSDLModifier*>(pCre->fThis));
        //case kAvatarSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarSDLModifier*>(pCre->fThis));
        //case kAGMasterSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plAGMasterSDLModifier*>(pCre->fThis));
        //case kPythonSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plPythonSDLModifier*>(pCre->fThis));
        //case kLayerSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerSDLModifier*>(pCre->fThis));
        //case kAnimTimeConvertSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plAnimTimeConvertSDLModifier*>(pCre->fThis));
        //case kResponderSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plResponderSDLModifier*>(pCre->fThis));
        //case kSoundSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plSoundSDLModifier*>(pCre->fThis));
        //case kResManagerHelper: return dynamic_cast<plCreatable*>(reinterpret_cast<plResManagerHelper*>(pCre->fThis));
        case kHKSubWorld: return dynamic_cast<plCreatable*>(reinterpret_cast<plHKSubWorld*>(pCre->fThis));
        case kArmatureEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureEffect*>(pCre->fThis));
        case kArmatureEffectFootSound: return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureEffectFootSound*>(pCre->fThis));
        case kEAXListenerMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plEAXListenerMod*>(pCre->fThis));
        case kDynaDecalMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaDecalMgr*>(pCre->fThis));
        case kObjectInVolumeAndFacingDetector: return dynamic_cast<plCreatable*>(reinterpret_cast<plObjectInVolumeAndFacingDetector*>(pCre->fThis));
        case kDynaFootMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaFootMgr*>(pCre->fThis));
        case kDynaRippleMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaRippleMgr*>(pCre->fThis));
        case kDynaBulletMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaBulletMgr*>(pCre->fThis));
        //case kDecalEnableMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plDecalEnableMod*>(pCre->fThis));
        case kPrintShape: return dynamic_cast<plCreatable*>(reinterpret_cast<plPrintShape*>(pCre->fThis));
        case kDynaPuddleMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaPuddleMgr*>(pCre->fThis));
        case kGUIMultiLineEditCtrl: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIMultiLineEditCtrl*>(pCre->fThis));
        case kLayerAnimationBase: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerAnimationBase*>(pCre->fThis));
        case kLayerSDLAnimation: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerSDLAnimation*>(pCre->fThis));
        case kATCAnim: return dynamic_cast<plCreatable*>(reinterpret_cast<plATCAnim*>(pCre->fThis));
        case kAgeGlobalAnim: return dynamic_cast<plCreatable*>(reinterpret_cast<plAgeGlobalAnim*>(pCre->fThis));
        case kSubworldRegionDetector: return dynamic_cast<plCreatable*>(reinterpret_cast<plSubworldRegionDetector*>(pCre->fThis));
        //case kAvatarMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarMgr*>(pCre->fThis));
        case kNPCSpawnMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plNPCSpawnMod*>(pCre->fThis));
        case kActivePrintShape: return dynamic_cast<plCreatable*>(reinterpret_cast<plActivePrintShape*>(pCre->fThis));
        //case kExcludeRegionSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plExcludeRegionSDLModifier*>(pCre->fThis));
        //case kLOSDispatch: return dynamic_cast<plCreatable*>(reinterpret_cast<plLOSDispatch*>(pCre->fThis));
        case kDynaWakeMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaWakeMgr*>(pCre->fThis));
        //case kSimulationMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plSimulationMgr*>(pCre->fThis));
        case kWaveSet7: return dynamic_cast<plCreatable*>(reinterpret_cast<plWaveSet7*>(pCre->fThis));
        case kPanicLinkRegion: return dynamic_cast<plCreatable*>(reinterpret_cast<plPanicLinkRegion*>(pCre->fThis));
        case kWin32GroupedSound: return dynamic_cast<plCreatable*>(reinterpret_cast<plWin32GroupedSound*>(pCre->fThis));
        case kFilterCoordInterface: return dynamic_cast<plCreatable*>(reinterpret_cast<plFilterCoordInterface*>(pCre->fThis));
        case kStereizer: return dynamic_cast<plCreatable*>(reinterpret_cast<plStereizer*>(pCre->fThis));
        //case kCCRMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plCCRMgr*>(pCre->fThis));
        //case kCCRSpecialist: return dynamic_cast<plCreatable*>(reinterpret_cast<plCCRSpecialist*>(pCre->fThis));
        //case kCCRSeniorSpecialist: return dynamic_cast<plCreatable*>(reinterpret_cast<plCCRSeniorSpecialist*>(pCre->fThis));
        //case kCCRShiftSupervisor: return dynamic_cast<plCreatable*>(reinterpret_cast<plCCRShiftSupervisor*>(pCre->fThis));
        //case kCCRGameOperator: return dynamic_cast<plCreatable*>(reinterpret_cast<plCCRGameOperator*>(pCre->fThis));
        case kShader: return dynamic_cast<plCreatable*>(reinterpret_cast<plShader*>(pCre->fThis));
        case kDynamicEnvMap: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynamicEnvMap*>(pCre->fThis));
        case kSimpleRegionSensor: return dynamic_cast<plCreatable*>(reinterpret_cast<plSimpleRegionSensor*>(pCre->fThis));
        case kMorphSequence: return dynamic_cast<plCreatable*>(reinterpret_cast<plMorphSequence*>(pCre->fThis));
        case kEmoteAnim: return dynamic_cast<plCreatable*>(reinterpret_cast<plEmoteAnim*>(pCre->fThis));
        case kDynaRippleVSMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaRippleVSMgr*>(pCre->fThis));
        case kWaveSet6: return dynamic_cast<plCreatable*>(reinterpret_cast<plWaveSet6*>(pCre->fThis));
        case kGUIProgressCtrl: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIProgressCtrl*>(pCre->fThis));
        case kMaintainersMarkerModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plMaintainersMarkerModifier*>(pCre->fThis));
        //case kMorphSequenceSDLMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plMorphSequenceSDLMod*>(pCre->fThis));
        case kMorphDataSet: return dynamic_cast<plCreatable*>(reinterpret_cast<plMorphDataSet*>(pCre->fThis));
        case kHardRegion: return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegion*>(pCre->fThis));
        case kHardRegionPlanes: return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegionPlanes*>(pCre->fThis));
        case kHardRegionComplex: return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegionComplex*>(pCre->fThis));
        case kHardRegionUnion: return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegionUnion*>(pCre->fThis));
        case kHardRegionIntersect: return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegionIntersect*>(pCre->fThis));
        case kHardRegionInvert: return dynamic_cast<plCreatable*>(reinterpret_cast<plHardRegionInvert*>(pCre->fThis));
        case kVisRegion: return dynamic_cast<plCreatable*>(reinterpret_cast<plVisRegion*>(pCre->fThis));
        //case kVisMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plVisMgr*>(pCre->fThis));
        case kRegionBase: return dynamic_cast<plCreatable*>(reinterpret_cast<plRegionBase*>(pCre->fThis));
        case kGUIPopUpMenu: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIPopUpMenu*>(pCre->fThis));
        case kGUIMenuItem: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUIMenuItem*>(pCre->fThis));
        //case kCoopCoordinator: return dynamic_cast<plCreatable*>(reinterpret_cast<plCoopCoordinator*>(pCre->fThis));
        case kFont: return dynamic_cast<plCreatable*>(reinterpret_cast<plFont*>(pCre->fThis));
        //case kFontCache: return dynamic_cast<plCreatable*>(reinterpret_cast<plFontCache*>(pCre->fThis));
        case kRelevanceRegion: return dynamic_cast<plCreatable*>(reinterpret_cast<plRelevanceRegion*>(pCre->fThis));
        //case kRelevanceMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plRelevanceMgr*>(pCre->fThis));
        //case kJournalBook: return dynamic_cast<plCreatable*>(reinterpret_cast<pfJournalBook*>(pCre->fThis));
        //case kLayerTargetContainer: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerTargetContainer*>(pCre->fThis));
        case kImageLibMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plImageLibMod*>(pCre->fThis));
        case kParticleFlockEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleFlockEffect*>(pCre->fThis));
        //case kParticleSDLMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleSDLMod*>(pCre->fThis));
        //case kAgeLoader: return dynamic_cast<plCreatable*>(reinterpret_cast<plAgeLoader*>(pCre->fThis));
        case kWaveSetBase: return dynamic_cast<plCreatable*>(reinterpret_cast<plWaveSetBase*>(pCre->fThis));
        case kPhysicalSndGroup: return dynamic_cast<plCreatable*>(reinterpret_cast<plPhysicalSndGroup*>(pCre->fThis));
        //case kBookData: return dynamic_cast<plCreatable*>(reinterpret_cast<pfBookData*>(pCre->fThis));
        case kDynaTorpedoMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaTorpedoMgr*>(pCre->fThis));
        case kDynaTorpedoVSMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynaTorpedoVSMgr*>(pCre->fThis));
        case kClusterGroup: return dynamic_cast<plCreatable*>(reinterpret_cast<plClusterGroup*>(pCre->fThis));
        case kGameMarkerModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plGameMarkerModifier*>(pCre->fThis));
        case kLODMipmap: return dynamic_cast<plCreatable*>(reinterpret_cast<plLODMipmap*>(pCre->fThis));
        case kSwimDetector: return dynamic_cast<plCreatable*>(reinterpret_cast<plSwimDetector*>(pCre->fThis));
        case kFadeOpacityMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plFadeOpacityMod*>(pCre->fThis));
        //case kFadeOpacityLay: return dynamic_cast<plCreatable*>(reinterpret_cast<plFadeOpacityLay*>(pCre->fThis));
        case kDistOpacityMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plDistOpacityMod*>(pCre->fThis));
        case kArmatureModBase: return dynamic_cast<plCreatable*>(reinterpret_cast<plArmatureModBase*>(pCre->fThis));
        case kSwimRegionInterface: return dynamic_cast<plCreatable*>(reinterpret_cast<plSwimRegionInterface*>(pCre->fThis));
        case kSwimCircularCurrentRegion: return dynamic_cast<plCreatable*>(reinterpret_cast<plSwimCircularCurrentRegion*>(pCre->fThis));
        case kParticleFollowSystemEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleFollowSystemEffect*>(pCre->fThis));
        case kSwimStraightCurrentRegion: return dynamic_cast<plCreatable*>(reinterpret_cast<plSwimStraightCurrentRegion*>(pCre->fThis));
        case kObjectFlocker: return dynamic_cast<plCreatable*>(reinterpret_cast<pfObjectFlocker*>(pCre->fThis));
        case kGrassShaderMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plGrassShaderMod*>(pCre->fThis));
        case kDynamicCamMap: return dynamic_cast<plCreatable*>(reinterpret_cast<plDynamicCamMap*>(pCre->fThis));
        case kAutoWalkRegion: return dynamic_cast<plCreatable*>(reinterpret_cast<plAutoWalkRegion*>(pCre->fThis));
        case kCrossfade: return dynamic_cast<plCreatable*>(reinterpret_cast<plCrossfade*>(pCre->fThis));
        case kParticleFadeOutEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleFadeOutEffect*>(pCre->fThis));
        //case kSecurePreloader: return dynamic_cast<plCreatable*>(reinterpret_cast<pfSecurePreloader*>(pCre->fThis));
        //case kWindBoneMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plWindBoneMod*>(pCre->fThis));
        case kCameraBrain_NovicePlus: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_NovicePlus*>(pCre->fThis));
        //case kSubtitleMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<pfSubtitleMgr*>(pCre->fThis));
        case kPythonFileModConditionalObject: return dynamic_cast<plCreatable*>(reinterpret_cast<plPythonFileModConditionalObject*>(pCre->fThis));
        //case kLayerTransform: return dynamic_cast<plCreatable*>(reinterpret_cast<plLayerTransform*>(pCre->fThis));
        //case kBubbleShaderMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plBubbleShaderMod*>(pCre->fThis));
        //case kLineFollowModBase: return dynamic_cast<plCreatable*>(reinterpret_cast<plLineFollowModBase*>(pCre->fThis));
        //case kClientApp: return dynamic_cast<plCreatable*>(reinterpret_cast<plClientApp*>(pCre->fThis));
        //case kGUICreditsCtrl: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUICreditsCtrl*>(pCre->fThis));
        case kCameraBrainUru: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1*>(pCre->fThis));
        //case kVirtualCamera: return dynamic_cast<plCreatable*>(reinterpret_cast<plVirtualCamera*>(pCre->fThis));
        case kCameraBrainUru_Drive: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Drive*>(pCre->fThis));
        case kCameraBrainUru_Follow: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Avatar*>(pCre->fThis));
        case kCameraBrainUru_Fixed: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Fixed*>(pCre->fThis));
        //case kGUISketchCtrl: return dynamic_cast<plCreatable*>(reinterpret_cast<pfGUISketchCtrl*>(pCre->fThis));
        case kLadderModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plLadderModifier*>(pCre->fThis));
        case kCameraBrainUru_FirstPerson: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_FirstPerson*>(pCre->fThis));
        case kCameraBrainUru_Circle: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain1_Circle*>(pCre->fThis));
        //case kEAXReverbEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plEAXReverbEffect*>(pCre->fThis));
        case kSpawnMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plSpawnMod*>(pCre->fThis));
        case kCameraBrain_Novice: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Novice*>(pCre->fThis));
        //case kAvatarPhysicalSDLModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plAvatarPhysicalSDLModifier*>(pCre->fThis));
        case kDirectMusicSound: return dynamic_cast<plCreatable*>(reinterpret_cast<plDirectMusicSound*>(pCre->fThis));
        //case kClientSessionMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<plClientSessionMgr*>(pCre->fThis));
        //case kSDLVarChangeNotifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plSDLVarChangeNotifier*>(pCre->fThis));
        //case kInterestWellModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plInterestWellModifier*>(pCre->fThis));
        case kElevatorModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plElevatorModifier*>(pCre->fThis));
        case kCameraBrain_Expert: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Expert*>(pCre->fThis));
        //case kPagingRegionModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plPagingRegionModifier*>(pCre->fThis));
        //case kGuidepathModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plGuidepathModifier*>(pCre->fThis));
        //case kNodeMgr: return dynamic_cast<plCreatable*>(reinterpret_cast<pfNodeMgr*>(pCre->fThis));
        //case kEAXEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plEAXEffect*>(pCre->fThis));
        //case kEAXPitchShifter: return dynamic_cast<plCreatable*>(reinterpret_cast<plEAXPitchShifter*>(pCre->fThis));
        //case kIKModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plIKModifier*>(pCre->fThis));
        case kCameraBrain_M5: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_M5*>(pCre->fThis));
        case kAGAnimBink: return dynamic_cast<plCreatable*>(reinterpret_cast<plAGAnimBink*>(pCre->fThis));
        //case kTreeShader: return dynamic_cast<plCreatable*>(reinterpret_cast<plTreeShader*>(pCre->fThis));
        case kNodeRegionModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plNodeRegionModifier*>(pCre->fThis));
        //case kPiranhaRegionModifier: return dynamic_cast<plCreatable*>(reinterpret_cast<plPiranhaRegionModifier*>(pCre->fThis));
        case kRidingAnimatedPhysicalDetector: return dynamic_cast<plCreatable*>(reinterpret_cast<plRidingAnimatedPhysicalDetector*>(pCre->fThis));
        case kVolumeSensorConditionalObjectNoArbitration: return dynamic_cast<plCreatable*>(reinterpret_cast<plVolumeSensorConditionalObjectNoArbitration*>(pCre->fThis));
        //case kFXMaterial: return dynamic_cast<plCreatable*>(reinterpret_cast<plFXMaterial*>(pCre->fThis));
        //case kMovableMod: return dynamic_cast<plCreatable*>(reinterpret_cast<plMovableMod*>(pCre->fThis));
        //case kMaterial: return dynamic_cast<plCreatable*>(reinterpret_cast<plMaterial*>(pCre->fThis));
        //case kEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plEffect*>(pCre->fThis));
        //case kParticleBulletEffect: return dynamic_cast<plCreatable*>(reinterpret_cast<plParticleBulletEffect*>(pCre->fThis));
        case kCameraBrain_Ground: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Ground*>(pCre->fThis));
        case kCameraBrain_Flight: return dynamic_cast<plCreatable*>(reinterpret_cast<plCameraBrain_Flight*>(pCre->fThis));
        default: return pCre->fThis;
    }
}
