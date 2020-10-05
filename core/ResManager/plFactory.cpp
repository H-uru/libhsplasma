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

#include "plFactory.h"
#include "Debug/hsExceptions.hpp"
#include "Debug/plDebug.h"

// Includes for all plCreatable types
#include "PRP/plSceneNode.h"
#include "PRP/Animation/plBlower.h"
#include "PRP/Animation/plFilterCoordInterface.h"
#include "PRP/Animation/plLineFollowMod.h"
#include "PRP/Animation/pfObjectFlocker.h"
#include "PRP/Animation/plStereizer.h"
#include "PRP/Animation/plViewFaceModifier.h"
#include "PRP/Animation/plWindBoneMod.h"
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
#include "PRP/Message/plAccountUpdateMsg.h"
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
#include "PRP/Message/plWarpMsg.h"
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
#include "PRP/NetMessage/plNetMsgGameMessage.h"
#include "PRP/NetMessage/plNetMsgGroupOwner.h"
#include "PRP/NetMessage/plNetMsgInitialAgeStateSent.h"
#include "PRP/NetMessage/plNetMsgLoadClone.h"
#include "PRP/NetMessage/plNetMsgMembersList.h"
#include "PRP/NetMessage/plNetMsgPlayerPage.h"
#include "PRP/NetMessage/plNetMsgRelevanceRegions.h"
#include "PRP/NetMessage/plNetMsgRoomsList.h"
#include "PRP/NetMessage/plNetMsgSDLState.h"
#include "PRP/NetMessage/plNetMsgSharedState.h"
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

#define ABSTRACT(x) \
    do { \
        plDebug::Warning("Warning: Attempted to create abstract class %s", ClassName(x)); \
        return nullptr; \
    } while (0)

#define NOTIMPL(x) \
    do { \
        plDebug::Warning("Warning: class %s is not implemented", ClassName(x)); \
        return nullptr; \
    } while (0)

plFactory::OverrideFunc plFactory::fOverride;

plCreatable* plFactory::Create(short typeIdx)
{
    if (typeIdx < 0)
        return nullptr;

    if (fOverride) {
        plCreatable* over_cre;
        over_cre = fOverride(typeIdx);
        if (over_cre)
            return over_cre;
    }

    switch (typeIdx) {
        // Keyed Classes //
        case kSceneNode: return new plSceneNode();
        case kSceneObject: return new plSceneObject();
        case kKeyedObject: ABSTRACT(kKeyedObject);
        case kBitmap: return new plBitmap();
        case kMipmap: return new plMipmap();
        case kCubicEnvironmap: return new plCubicEnvironmap();
        case kLayer: return new plLayer();
        case kGMaterial: return new hsGMaterial();
        case kParticleSystem: return new plParticleSystem();
        case kParticleEffect: return new plParticleEffect();
        case kParticleCollisionEffectBeat: return new plParticleCollisionEffectBeat();
        case kParticleFadeVolumeEffect: return new plParticleFadeVolumeEffect();
        case kBoundInterface: return new plBoundInterface();
        case kRenderTarget: return new plRenderTarget();
        case kCubicRenderTarget: return new plCubicRenderTarget();
        //case kCubicRenderTargetModifier: return new plCubicRenderTargetModifier();
        case kObjInterface: return new plObjInterface();
        case kAudioInterface: return new plAudioInterface();
        case kAudible: return new plAudible();
        case kAudibleNull: return new plAudibleNull();
        case kWinAudible: return new plWinAudible();
        case kCoordinateInterface: return new plCoordinateInterface();
        case kDrawInterface: return new plDrawInterface();
        case kDrawable: ABSTRACT(kDrawable);
        //case kDrawableMesh: return new plDrawableMesh();
        //case kDrawableIce: return new plDrawableIce();
        case kPhysical: ABSTRACT(kPhysical);
        //case kPhysicalMesh: return new plPhysicalMesh();
        case kSimulationInterface: return new plSimulationInterface();
        case kCameraModifier: return new plCameraModifier();
        case kModifier: ABSTRACT(kModifier);
        case kSingleModifier: ABSTRACT(kSingleModifier);
        //case kSimpleModifier: return new plSimpleModifier();
        //case kSimpleTMModifier: return new plSimpleTMModifier();
        //case kRandomTMModifier: return new plRandomTMModifier();
        //case kInterestingModifier: return new plInterestingModifier();
        case kDetectorModifier: return new plDetectorModifier();
        //case kSimplePhysicalMesh: return new plSimplePhysicalMesh();
        //case kCompoundPhysicalMesh: return new plCompoundPhysicalMesh();
        case kMultiModifier: ABSTRACT(kMultiModifier);
        case kSynchedObject: ABSTRACT(kSynchedObject);
        case kSoundBuffer: return new plSoundBuffer();
        case kAliasModifier: return new plAliasModifier();
        case kPickingDetector: return new plPickingDetector();
        case kCollisionDetector: return new plCollisionDetector();
        case kLogicModifier: return new plLogicModifier();
        case kConditionalObject: return new plConditionalObject();
        case kANDConditionalObject: return new plANDConditionalObject();
        case kORConditionalObject: return new plORConditionalObject();
        case kPickedConditionalObject: return new plPickedConditionalObject();
        case kActivatorConditionalObject: return new plActivatorConditionalObject();
        //case kTimerCallbackManager: return new plTimerCallbackManager();
        case kKeyPressConditionalObject: return new plKeyPressConditionalObject();
        case kAnimationEventConditionalObject: return new plAnimationEventConditionalObject();
        case kControlEventConditionalObject: return new plControlEventConditionalObject();
        case kObjectInBoxConditionalObject: return new plObjectInBoxConditionalObject();
        case kLocalPlayerInBoxConditionalObject: return new plLocalPlayerInBoxConditionalObject();
        case kObjectIntersectPlaneConditionalObject: return new plObjectIntersectPlaneConditionalObject();
        case kLocalPlayerIntersectPlaneConditionalObject: return new plLocalPlayerIntersectPlaneConditionalObject();
        //case kPortalDrawable: return new plPortalDrawable();
        //case kPortalPhysical: return new plPortalPhysical();
        case kSpawnModifier: return new plSpawnModifier();
        case kFacingConditionalObject: return new plFacingConditionalObject();
        case kGenericPhysical: return new plGenericPhysical();
        case kViewFaceModifier: return new plViewFaceModifier();
        case kLayerInterface: return new plLayerInterface();
        //case kLayerWrapper: return new plLayerWrapper();
        case kLayerAnimation: return new plLayerAnimation();
        case kLayerDepth: return new plLayerDepth();
        case kLayerMovie: return new plLayerMovie();
        case kLayerBink: return new plLayerBink();
        case kLayerAVI: return new plLayerAVI();
        case kSound: return new plSound();
        case kWin32Sound: return new plWin32Sound();
        //case kLayerOr: return new plLayerOr();
        //case kAudioSystem: return new plAudioSystem();
        case kDrawableSpans: return new plDrawableSpans();
        //case kDrawablePatchSet: return new plDrawablePatchSet();
        //case kInputManager: return new plInputManager();
        case kLogicModBase: return new plLogicModBase();
        case kFogEnvironment: return new plFogEnvironment();
        //case kNetApp: return new plNetApp();
        //case kNetClientMgr: return new plNetClientMgr();
        case k2WayWinAudible: return new pl2WayWinAudible();
        case kLightInfo: return new plLightInfo();
        case kDirectionalLightInfo: return new plDirectionalLightInfo();
        case kOmniLightInfo: return new plOmniLightInfo();
        case kSpotLightInfo: return new plSpotLightInfo();
        //case kLightSpace: return new plLightSpace();
        //case kNetClientApp: return new plNetClientApp();
        //case kNetServerApp: return new plNetServerApp();
        //case kClient: return new plClient();
        //case kCompoundTMModifier: return new plCompoundTMModifier();
        case kCameraBrain: ABSTRACT(kCameraBrain);
        case kCameraBrain_Default: NOTIMPL(kCameraBrain_Default);
        case kCameraBrain_Drive: NOTIMPL(kCameraBrain_Drive);
        case kCameraBrain_Fixed: NOTIMPL(kCameraBrain_Fixed);
        case kCameraBrain_FixedPan: NOTIMPL(kCameraBrain_FixedPan);
        case kGUIClickMapCtrl: return new pfGUIClickMapCtrl();
        //case kListener: return new plListener();
        //case kAvatarMod: return new plAvatarMod();
        //case kAvatarAnim: return new plAvatarAnim();
        //case kAvatarAnimMgr: return new plAvatarAnimMgr();
        case kOccluder: return new plOccluder();
        case kMobileOccluder: return new plMobileOccluder();
        //case kLayerShadowBase: return new plLayerShadowBase();
        case kLimitedDirLightInfo: return new plLimitedDirLightInfo();
        case kAGAnim: return new plAGAnim();
        case kAGModifier: return new plAGModifier();
        case kAGMasterMod: return new plAGMasterMod();
        case kCameraBrain_Avatar: NOTIMPL(kCameraBrain_Avatar);
        case kCameraRegionDetector: return new plCameraRegionDetector();
        case kCameraBrain_FP: NOTIMPL(kCameraBrain_FP);
        case kLineFollowMod: return new plLineFollowMod();
        //case kLightModifier: return new plLightModifier();
        //case kOmniModifier: return new plOmniModifier();
        //case kSpotModifier: return new plSpotModifier();
        //case kLtdDirModifier: return new plLtdDirModifier();
        case kSeekPointMod: return new plSeekPointMod();
        case kOneShotMod: return new plOneShotMod();
        case kRandomCommandMod: return new plRandomCommandMod();
        case kRandomSoundMod: return new plRandomSoundMod();
        case kPostEffectMod: return new plPostEffectMod();
        case kObjectInVolumeDetector: return new plObjectInVolumeDetector();
        case kResponderModifier: return new plResponderModifier();
        case kAxisAnimModifier: return new plAxisAnimModifier();
        //case kLayerLightBase: return new plLayerLightBase();
        case kFollowMod: return new plFollowMod();
        //case kTransitionMgr: return new plTransitionMgr();
        //case kInventoryMod: return new plInventoryMod();
        //case kInventoryObjMod: return new plInventoryObjMod();
        //case kLinkEffectsMgr: return new plLinkEffectsMgr();
        case kWin32StreamingSound: return new plWin32StreamingSound();
        case kPythonMod: return new plPythonMod();
        case kActivatorActivatorConditionalObject: return new plActivatorActivatorConditionalObject();
        case kSoftVolume: return new plSoftVolume();
        case kSoftVolumeSimple: return new plSoftVolumeSimple();
        case kSoftVolumeComplex: return new plSoftVolumeComplex();
        case kSoftVolumeUnion: return new plSoftVolumeUnion();
        case kSoftVolumeIntersect: return new plSoftVolumeIntersect();
        case kSoftVolumeInvert: return new plSoftVolumeInvert();
        case kWin32LinkSound: return new plWin32LinkSound();
        case kLayerLinkAnimation: return new plLayerLinkAnimation();
        case kArmatureMod: return new plArmatureMod();
        case kCameraBrain_Freelook: NOTIMPL(kCameraBrain_Freelook);
        //case kHavokConstraintsMod: return new plHavokConstraintsMod();
        //case kHingeConstraintMod: return new plHingeConstraintMod();
        //case kWheelConstraintMod: return new plWheelConstraintMod();
        //case kStrongSpringConstraintMod: return new plStrongSpringConstraintMod();
        case kArmatureLODMod: return new plArmatureLODMod();
        case kWin32StaticSound: return new plWin32StaticSound();
        //case kGameGUIMgr: return new pfGameGUIMgr();
        case kGUIDialogMod: return new pfGUIDialogMod();
        case kCameraBrain1: return new plCameraBrain1();
        //case kVirtualCam1: return new plVirtualCam1();
        case kCameraBrain1_Drive: return new plCameraBrain1_Drive();
        case kCameraBrain1_POA: NOTIMPL(kCameraBrain1_POA);
        case kCameraBrain1_Avatar: return new plCameraBrain1_Avatar();
        case kCameraBrain1_Fixed: return new plCameraBrain1_Fixed();
        case kCameraBrain1_POAFixed: NOTIMPL(kCameraBrain1_POAFixed);
        case kGUIButtonMod: return new pfGUIButtonMod();
        case kPythonFileMod: return new plPythonFileMod();
        case kGUIControlMod: ABSTRACT(kGUIControlMod);
        case kExcludeRegionModifier: return new plExcludeRegionModifier();
        case kGUIDraggableMod: return new pfGUIDraggableMod();
        case kVolumeSensorConditionalObject: return new plVolumeSensorConditionalObject();
        case kVolActivatorConditionalObject: return new plVolActivatorConditionalObject();
        case kMsgForwarder: return new plMsgForwarder();
        case kBlower: return new plBlower();
        case kGUIListBoxMod: return new pfGUIListBoxMod();
        case kGUITextBoxMod: return new pfGUITextBoxMod();
        case kGUIEditBoxMod: return new pfGUIEditBoxMod();
        case kDynamicTextMap: return new plDynamicTextMap();
        case kSittingModifier: return new plSittingModifier();
        case kGUIUpDownPairMod: return new pfGUIUpDownPairMod();
        case kGUIValueCtrl: ABSTRACT(kGUIValueCtrl);
        case kGUIKnobCtrl: return new pfGUIKnobCtrl();
        case kAvLadderMod: return new plAvLadderMod();
        case kCameraBrain1_FirstPerson: return new plCameraBrain1_FirstPerson();
        //case kCloneSpawnModifier: return new plCloneSpawnModifier();
        case kClothingItem: return new plClothingItem();
        case kClothingOutfit: return new plClothingOutfit();
        case kClothingBase: return new plClothingBase();
        //case kClothingMgr: return new plClothingMgr();
        case kGUIDragBarCtrl: return new pfGUIDragBarCtrl();
        case kGUICheckBoxCtrl: return new pfGUICheckBoxCtrl();
        case kGUIRadioGroupCtrl: return new pfGUIRadioGroupCtrl();
        //case kPlayerBookMod: return new pfPlayerBookMod();
        case kGUIDynDisplayCtrl: return new pfGUIDynDisplayCtrl();
        //case kLayerProject: return new plLayerProject();
        //case kInputInterfaceMgr: return new plInputInterfaceMgr();
        case kRailCameraMod: return new plRailCameraMod();
        case kMultistageBehMod: return new plMultistageBehMod();
        case kCameraBrain1_Circle: return new plCameraBrain1_Circle();
        case kParticleWindEffect: return new plParticleWindEffect();
        case kAnimEventModifier: return new plAnimEventModifier();
        //case kAutoProfile: return new plAutoProfile();
        case kGUISkin: return new pfGUISkin();
        //case kAVIWriter: return new plAVIWriter();
        case kParticleCollisionEffect: return new plParticleCollisionEffect();
        case kParticleCollisionEffectDie: return new plParticleCollisionEffectDie();
        case kParticleCollisionEffectBounce: return new plParticleCollisionEffectBounce();
        case kInterfaceInfoModifier: return new plInterfaceInfoModifier();
        case kSharedMesh: return new plSharedMesh();
        case kArmatureEffectsMgr: return new plArmatureEffectsMgr();
        //case kMarkerMgr: return new pfMarkerMgr();
        case kVehicleModifier: return new plVehicleModifier();
        case kParticleLocalWind: return new plParticleLocalWind();
        case kParticleUniformWind: return new plParticleUniformWind();
        case kInstanceDrawInterface: return new plInstanceDrawInterface();
        case kShadowMaster: return new plShadowMaster();
        case kShadowCaster: return new plShadowCaster();
        case kPointShadowMaster: return new plPointShadowMaster();
        case kDirectShadowMaster: return new plDirectShadowMaster();
        //case kSDLModifier: return new plSDLModifier();
        //case kPhysicalSDLModifier: return new plPhysicalSDLModifier();
        //case kClothingSDLModifier: return new plClothingSDLModifier();
        //case kAvatarSDLModifier: return new plAvatarSDLModifier();
        //case kAGMasterSDLModifier: return new plAGMasterSDLModifier();
        //case kPythonSDLModifier: return new plPythonSDLModifier();
        //case kLayerSDLModifier: return new plLayerSDLModifier();
        //case kAnimTimeConvertSDLModifier: return new plAnimTimeConvertSDLModifier();
        //case kResponderSDLModifier: return new plResponderSDLModifier();
        //case kSoundSDLModifier: return new plSoundSDLModifier();
        //case kResManagerHelper: return new plResManagerHelper();
        case kHKSubWorld: return new plHKSubWorld();
        case kArmatureEffect: ABSTRACT(kArmatureEffect);
        case kArmatureEffectFootSound: return new plArmatureEffectFootSound();
        case kEAXListenerMod: return new plEAXListenerMod();
        case kDynaDecalMgr: return new plDynaDecalMgr();
        case kObjectInVolumeAndFacingDetector: return new plObjectInVolumeAndFacingDetector();
        case kDynaFootMgr: return new plDynaFootMgr();
        case kDynaRippleMgr: return new plDynaRippleMgr();
        case kDynaBulletMgr: return new plDynaBulletMgr();
        //case kDecalEnableMod: return new plDecalEnableMod();
        case kPrintShape: return new plPrintShape();
        case kDynaPuddleMgr: return new plDynaPuddleMgr();
        case kGUIMultiLineEditCtrl: return new pfGUIMultiLineEditCtrl();
        case kLayerAnimationBase: ABSTRACT(kLayerAnimationBase);
        case kLayerSDLAnimation: return new plLayerSDLAnimation();
        case kATCAnim: return new plATCAnim();
        case kAgeGlobalAnim: return new plAgeGlobalAnim();
        case kSubworldRegionDetector: return new plSubworldRegionDetector();
        //case kAvatarMgr: return new plAvatarMgr();
        case kNPCSpawnMod: return new plNPCSpawnMod();
        case kActivePrintShape: return new plActivePrintShape();
        //case kExcludeRegionSDLModifier: return new plExcludeRegionSDLModifier();
        //case kLOSDispatch: return new plLOSDispatch();
        case kDynaWakeMgr: return new plDynaWakeMgr();
        //case kSimulationMgr: return new plSimulationMgr();
        case kWaveSet7: return new plWaveSet7();
        case kPanicLinkRegion: return new plPanicLinkRegion();
        case kWin32GroupedSound: return new plWin32GroupedSound();
        case kFilterCoordInterface: return new plFilterCoordInterface();
        case kStereizer: return new plStereizer();
        //case kCCRMgr: return new plCCRMgr();
        //case kCCRSpecialist: return new plCCRSpecialist();
        //case kCCRSeniorSpecialist: return new plCCRSeniorSpecialist();
        //case kCCRShiftSupervisor: return new plCCRShiftSupervisor();
        //case kCCRGameOperator: return new plCCRGameOperator();
        case kShader: return new plShader();
        case kDynamicEnvMap: return new plDynamicEnvMap();
        case kSimpleRegionSensor: return new plSimpleRegionSensor();
        case kMorphSequence: return new plMorphSequence();
        case kEmoteAnim: return new plEmoteAnim();
        case kDynaRippleVSMgr: return new plDynaRippleVSMgr();
        case kWaveSet6: return new plWaveSet6();
        case kGUIProgressCtrl: return new pfGUIProgressCtrl();
        case kMaintainersMarkerModifier: return new plMaintainersMarkerModifier();
        //case kMorphSequenceSDLMod: return new plMorphSequenceSDLMod();
        case kMorphDataSet: return new plMorphDataSet();
        case kHardRegion: return new plHardRegion();
        case kHardRegionPlanes: return new plHardRegionPlanes();
        case kHardRegionComplex: return new plHardRegionComplex();
        case kHardRegionUnion: return new plHardRegionUnion();
        case kHardRegionIntersect: return new plHardRegionIntersect();
        case kHardRegionInvert: return new plHardRegionInvert();
        case kVisRegion: return new plVisRegion();
        //case kVisMgr: return new plVisMgr();
        case kRegionBase: ABSTRACT(kRegionBase);
        case kGUIPopUpMenu: return new pfGUIPopUpMenu();
        case kGUIMenuItem: return new pfGUIMenuItem();
        //case kCoopCoordinator: return new plCoopCoordinator();
        case kFont: return new plFont();
        //case kFontCache: return new plFontCache();
        case kRelevanceRegion: return new plRelevanceRegion();
        //case kRelevanceMgr: return new plRelevanceMgr();
        //case kJournalBook: return new pfJournalBook();
        //case kLayerTargetContainer: return new plLayerTargetContainer();
        case kImageLibMod: return new plImageLibMod();
        case kParticleFlockEffect: return new plParticleFlockEffect();
        //case kParticleSDLMod: return new plParticleSDLMod();
        //case kAgeLoader: return new plAgeLoader();;
        case kWaveSetBase: ABSTRACT(kWaveSetBase);
        case kPhysicalSndGroup: return new plPhysicalSndGroup();
        //case kBookData: return new pfBookData();
        case kDynaTorpedoMgr: return new plDynaTorpedoMgr();
        case kDynaTorpedoVSMgr: return new plDynaTorpedoVSMgr();
        case kClusterGroup: return new plClusterGroup();
        case kGameMarkerModifier: return new plGameMarkerModifier();
        case kLODMipmap: return new plLODMipmap();
        case kSwimDetector: return new plSwimDetector();
        case kFadeOpacityMod: return new plFadeOpacityMod();
        //case kFadeOpacityLay: return new plFadeOpacityLay();
        case kDistOpacityMod: return new plDistOpacityMod();
        case kArmatureModBase: ABSTRACT(kArmatureModBase);
        case kSwimRegionInterface: return new plSwimRegionInterface();
        case kSwimCircularCurrentRegion: return new plSwimCircularCurrentRegion();
        case kParticleFollowSystemEffect: return new plParticleFollowSystemEffect();
        case kSwimStraightCurrentRegion: return new plSwimStraightCurrentRegion();
        case kObjectFlocker: return new pfObjectFlocker();
        case kGrassShaderMod: return new plGrassShaderMod();
        case kDynamicCamMap: return new plDynamicCamMap();
        case kAutoWalkRegion: return new plAutoWalkRegion();
        case kCrossfade: return new plCrossfade();
        case kParticleFadeOutEffect: return new plParticleFadeOutEffect();
        //case kSecurePreloader: return new pfSecurePreloader();
        case kWindBoneMod: return new plWindBoneMod();
        case kCameraBrain_NovicePlus: return new plCameraBrain_NovicePlus();
        //case kSubtitleMgr: return new pfSubtitleMgr();
        case kPythonFileModConditionalObject: return new plPythonFileModConditionalObject();
        //case kLayerTransform: return new plLayerTransform();
        //case kBubbleShaderMod: return new plBubbleShaderMod();
        //case kLineFollowModBase: return new plLineFollowModBase();
        //case kClientApp: return new plClientApp();
        //case kGUICreditsCtrl: return new pfGUICreditsCtrl();
        case kCameraBrainUru: return new plCameraBrain1();
        //case kVirtualCamera: return new plVirtualCamera();
        case kCameraBrainUru_Drive: return new plCameraBrain1_Drive();
        case kCameraBrainUru_Follow: return new plCameraBrain1_Avatar();
        case kCameraBrainUru_Fixed: return new plCameraBrain1_Fixed();
        //case kGUISketchCtrl: return new pfGUISketchCtrl();
        case kLadderModifier: return new plLadderModifier();
        case kCameraBrainUru_FirstPerson: return new plCameraBrain1_FirstPerson();
        case kCameraBrainUru_Circle: return new plCameraBrain1_Circle();
        case kEAXReverbEffect: return new plEAXReverbEffect();
        case kSpawnMod: return new plSpawnMod();
        case kCameraBrain_Novice: return new plCameraBrain_Novice();
        //case kAvatarPhysicalSDLModifier: return new plAvatarPhysicalSDLModifier();
        case kDirectMusicSound: return new plDirectMusicSound();
        //case kClientSessionMgr: return new plClientSessionMgr();
        //case kSDLVarChangeNotifier: return new plSDLVarChangeNotifier();
        //case kInterestWellModifier: return new plInterestWellModifier();
        case kElevatorModifier: return new plElevatorModifier();
        case kCameraBrain_Expert: return new plCameraBrain_Expert();
        //case kPagingRegionModifier: return new plPagingRegionModifier();
        //case kGuidepathModifier: return new plGuidepathModifier();
        //case kNodeMgr: return new pfNodeMgr();
        case kEAXEffect: return new plEAXEffect();
        //case kEAXPitchShifter: return new plEAXPitchShifter();
        //case kIKModifier: return new plIKModifier();
        case kCameraBrain_M5: return new plCameraBrain_M5();
        case kAGAnimBink: return new plAGAnimBink();
        //case kTreeShader: return new plTreeShader();
        case kNodeRegionModifier: return new plNodeRegionModifier();
        //case kPiranhaRegionModifier: return new plPiranhaRegionModifier();
        case kRidingAnimatedPhysicalDetector: return new plRidingAnimatedPhysicalDetector();
        case kVolumeSensorConditionalObjectNoArbitration: return new plVolumeSensorConditionalObjectNoArbitration();
        //case kFXMaterial: return new plFXMaterial();
        //case kMovableMod: return new plMovableMod();
        //case kMaterial: return new plMaterial();
        //case kEffect: return new plEffect();
        //case kParticleBulletEffect: return new plParticleBulletEffect();
        case kCameraBrain_Ground: return new plCameraBrain_Ground();
        case kCameraBrain_Flight: return new plCameraBrain_Flight();

        // Non-Keyed Classes //
        //case kObjRefMsg: return new plObjRefMsg();
        //case kNodeRefMsg: return new plNodeRefMsg();
        case kMessage: ABSTRACT(kMessage);
        //case kRefMsg: return new plRefMsg();
        //case kGenRefMsg: return new plGenRefMsg();
        //case kTimeMsg: return new plTimeMsg();
        case kAnimCmdMsg: return new plAnimCmdMsg();
        //case kParticleUpdateMsg: return new plParticleUpdateMsg();
        //case kLayRefMsg: return new plLayRefMsg();
        //case kMatRefMsg: return new plMatRefMsg();
        case kCameraMsg: return new plCameraMsg();
        //case kInputEventMsg: return new plInputEventMsg();
        //case kKeyEventMsg: return new plKeyEventMsg();
        //case kMouseEventMsg: return new plMouseEventMsg();
        //case kEvalMsg: return new plEvalMsg();
        //case kTransformMsg: return new plTransformMsg();
        //case kControlEventMsg: return new plControlEventMsg();
        //case kVaultCCRNode: return new plVaultCCRNode();
        //case kLOSRequestMsg: return new plLOSRequestMsg();
        //case kLOSHitMsg: return new plLOSHitMsg();
        //case kSingleModMsg: return new plSingleModMsg();
        //case kMultiModMsg: return new plMultiModMsg();
        //case kAvatarPhysicsEnableCallbackMsg: return new plAvatarPhysicsEnableCallbackMsg();
        //case kMemberUpdateMsg: return new plMemberUpdateMsg();
        case kNetMsgPagingRoom: return new plNetMsgPagingRoom();
        //case kActivatorMsg: return new plActivatorMsg();
        //case kDispatch: return new plDispatch();
        case kReceiver: ABSTRACT(kReceiver);
        //case kMeshRefMsg: return new plMeshRefMsg();
        //case kGRenderProcs: return new hsGRenderProcs();
        //case kSfxAngleFade: return new hsSfxAngleFade();
        //case kSfxDistFade: return new hsSfxDistFade();
        //case kSfxDistShade: return new hsSfxDistShade();
        //case kSfxGlobalShade: return new hsSfxGlobalShade();
        //case kSfxIntenseAlpha: return new hsSfxIntenseAlpha();
        //case kSfxObjDistFade: return new hsSfxObjDistFade();
        //case kSfxObjDistShade: return new hsSfxObjDistShade();
        //case kDynamicValue: return new hsDynamicValue();
        //case kDynamicScalar: return new hsDynamicScalar();
        //case kDynamicColorRGBA: return new hsDynamicColorRGBA();
        //case kDynamicMatrix33: return new hsDynamicMatrix33();
        //case kDynamicMatrix44: return new hsDynamicMatrix44();
        case kController: ABSTRACT(kController);
        case kLeafController: return new plLeafController();
        case kScaleController: ABSTRACT(kScaleController);
        case kRotController: ABSTRACT(kRotController);
        case kPosController: ABSTRACT(kPosController);
        case kScalarController: return new plScalarController();
        case kPoint3Controller: return new plPoint3Controller();
        case kScaleValueController: return new plScaleValueController();
        case kQuatController: return new plQuatController();
        case kMatrix33Controller: return new plMatrix33Controller();
        case kMatrix44Controller: return new plMatrix44Controller();
        case kEaseController: return new plEaseController();
        case kSimpleScaleController: return new plSimpleScaleController();
        case kSimpleRotController: return new plSimpleRotController();
        case kCompoundRotController: return new plCompoundRotController();
        case kSimplePosController: return new plSimplePosController();
        case kCompoundPosController: return new plCompoundPosController();
        case kTMController: return new plTMController();
        //case kFogControl: return new hsFogControl();
        //case kIntRefMsg: return new plIntRefMsg();
        //case kCollisionReactor: return new plCollisionReactor();
        //case kCorrectionMsg: return new plCorrectionMsg();
        //case kPhysicalModifier: return new plPhysicalModifier();
        //case kPickedMsg: return new plPickedMsg();
        //case kCollideMsg: return new plCollideMsg();
        //case kTriggerMsg: return new plTriggerMsg();
        //case kInterestingModMsg: return new plInterestingModMsg();
        //case kDebugKeyEventMsg: return new plDebugKeyEventMsg();
        //case kPhysicalProperties: return new plPhysicalProperties();
        //case kSimplePhys: return new plSimplePhys();
        //case kMatrixUpdateMsg: return new plMatrixUpdateMsg();
        //case kCondRefMsg: return new plCondRefMsg();
        case kTimerCallbackMsg: return new plTimerCallbackMsg();
        case kEventCallbackMsg: return new plEventCallbackMsg();
        //case kSpawnModMsg: return new plSpawnModMsg();
        //case kSpawnRequestMsg: return new plSpawnRequestMsg();
        case kLoadCloneMsg: return new plLoadCloneMsg();
        case kEnableMsg: return new plEnableMsg();
        case kWarpMsg: return new plWarpMsg();
        //case kAttachMsg: return new plAttachMsg();
        //case kConsole: return new pfConsole();
        //case kRenderMsg: return new plRenderMsg();
        case kAnimTimeConvert: return new plAnimTimeConvert();
        case kSoundMsg: return new plSoundMsg();
        //case kInterestingPing: return new plInterestingPing();
        //case kNodeCleanupMsg: return new plNodeCleanupMsg();
        case kSpaceTree: return new plSpaceTree();
        case kNetMessage: ABSTRACT(kNetMessage);
        //case kNetMsgJoinReq: return new plNetMsgJoinReq();
        //case kNetMsgJoinAck: return new plNetMsgJoinAck();
        //case kNetMsgLeave: return new plNetMsgLeave();
        //case kNetMsgPing: return new plNetMsgPing();
        case kNetMsgRoomsList: return new plNetMsgRoomsList();
        case kNetMsgGroupOwner: return new plNetMsgGroupOwner();
        case kNetMsgGameStateRequest: return new plNetMsgGameStateRequest();
        //case kNetMsgSessionReset: return new plNetMsgSessionReset();
        //case kNetMsgOmnibus: return new plNetMsgOmnibus();
        case kNetMsgObject: return new plNetMsgObject();
        //case kCCRInvisibleMsg: return new plCCRInvisibleMsg();
        case kLinkInDoneMsg: return new plLinkInDoneMsg();
        case kNetMsgGameMessage: return new plNetMsgGameMessage();
        case kNetMsgStream: return new plNetMsgStream();
        //case kAudioSysMsg: return new plAudioSysMsg();
        //case kDispatchBase: return new plDispatchBase();
        case kServerReplyMsg: return new plServerReplyMsg();
        //case kDeviceRecreateMsg: return new plDeviceRecreateMsg();
        case kNetMsgStreamHelper: return new plNetMsgStreamHelper();
        case kNetMsgObjectHelper: NOTIMPL(kNetMsgObjectHelper);
        //case kIMouseXEventMsg: return new plIMouseXEventMsg();
        //case kIMouseYEventMsg: return new plIMouseYEventMsg();
        //case kIMouseBEventMsg: return new plIMouseBEventMsg();
        //case kLogicTriggerMsg: return new plLogicTriggerMsg();
        //case kPipeline: return new plPipeline();
        //case kDX8Pipeline: return new plDX8Pipeline();
        //case kNetMsgVoice: return new plNetMsgVoice();
        //case kLightRefMsg: return new plLightRefMsg();
        case kNetMsgStreamedObject: return new plNetMsgStreamedObject();
        case kNetMsgSharedState: return new plNetMsgSharedState();
        case kNetMsgTestAndSet: return new plNetMsgTestAndSet();
        //case kNetMsgGetSharedState: return new plNetMsgGetSharedState();
        //case kSharedStateMsg: return new plSharedStateMsg();
        //case kNetGenericServerTask: return new plNetGenericServerTask();
        //case kNetLookupServerGetAgeInfoFromVaultTask: return new plNetLookupServerGetAgeInfoFromVaultTask();
        //case kLoadAgeMsg: return new plLoadAgeMsg();
        case kMessageWithCallbacks: ABSTRACT(kMessageWithCallbacks);
        //case kClientMsg: return new plClientMsg();
        //case kClientRefMsg: return new plClientRefMsg();
        //case kNetMsgObjStateRequest: return new plNetMsgObjStateRequest();
        //case kCCRPetitionMsg: return new plCCRPetitionMsg();
        //case kVaultCCRInitializationTask: return new plVaultCCRInitializationTask();
        //case kNetServerMsg: return new plNetServerMsg();
        //case kNetServerMsgWithContext: return new plNetServerMsgWithContext();
        //case kNetServerMsgRegisterServer: return new plNetServerMsgRegisterServer();
        //case kNetServerMsgUnregisterServer: return new plNetServerMsgUnregisterServer();
        //case kNetServerMsgStartProcess: return new plNetServerMsgStartProcess();
        //case kNetServerMsgRegisterProcess: return new plNetServerMsgRegisterProcess();
        //case kNetServerMsgUnregisterProcess: return new plNetServerMsgUnregisterProcess();
        //case kNetServerMsgFindProcess: return new plNetServerMsgFindProcess();
        //case kNetServerMsgProcessFound: return new plNetServerMsgProcessFound();
        //case kNetMsgRoutingInfo: return new plNetMsgRoutingInfo();
        //case kNetServerSessionInfo: return new plNetServerSessionInfo();
        case kSimulationMsg: ABSTRACT(kSimulationMsg);
        //case kSimulationSynchMsg: return new plSimulationSynchMsg();
        //case kHKSimulationSynchMsg: return new plHKSimulationSynchMsg();
        case kAvatarMsg: ABSTRACT(kAvatarMsg);
        case kAvTaskMsg: return new plAvTaskMsg();
        case kAvSeekMsg: return new plAvSeekMsg();
        case kAvOneShotMsg: return new plAvOneShotMsg();
        //case kSatisfiedMsg: return new plSatisfiedMsg();
        //case kNetMsgObjectListHelper: return new plNetMsgObjectListHelper();
        //case kNetMsgObjectUpdateFilter: return new plNetMsgObjectUpdateFilter();
        //case kProxyDrawMsg: return new plProxyDrawMsg();
        //case kSelfDestructMsg: return new plSelfDestructMsg();
        //case kSimInfluenceMsg: return new plSimInfluenceMsg();
        //case kForceMsg: return new plForceMsg();
        //case kOffsetForceMsg: return new plOffsetForceMsg();
        //case kTorqueMsg: return new plTorqueMsg();
        //case kImpulseMsg: return new plImpulseMsg();
        //case kOffsetImpulseMsg: return new plOffsetImpulseMsg();
        //case kAngularImpulseMsg: return new plAngularImpulseMsg();
        //case kDampMsg: return new plDampMsg();
        //case kShiftMassMsg: return new plShiftMassMsg();
        case kSimStateMsg: ABSTRACT(kSimStateMsg);
        //case kFreezeMsg: return new plFreezeMsg();
        //case kEventGroupMsg: return new plEventGroupMsg();
        //case kSuspendEventMsg: return new plSuspendEventMsg();
        case kNetMsgMembersListReq: return new plNetMsgMembersListReq();
        case kNetMsgMembersList: return new plNetMsgMembersList();
        case kNetMsgMemberInfoHelper: return new plNetMsgMemberInfoHelper();
        case kNetMsgMemberListHelper: NOTIMPL(kNetMsgMemberListHelper);
        case kNetMsgMemberUpdate: return new plNetMsgMemberUpdate();
        case kNetMsgServerToClient: ABSTRACT(kNetMsgServerToClient);
        //case kNetMsgCreatePlayer: return new plNetMsgCreatePlayer();
        //case kNetMsgAuthenticateHello: return new plNetMsgAuthenticateHello();
        //case kNetMsgAuthenticateChallenge: return new plNetMsgAuthenticateChallenge();
        //case kConnectedToVaultMsg: return new plConnectedToVaultMsg();
        //case kCCRCommunicationMsg: return new plCCRCommunicationMsg();
        case kNetMsgInitialAgeStateSent: return new plNetMsgInitialAgeStateSent();
        //case kInitialAgeStateLoadedMsg: return new plInitialAgeStateLoadedMsg();
        //case kNetServerMsgFindServerBase: return new plNetServerMsgFindServerBase();
        //case kNetServerMsgFindServerReplyBase: return new plNetServerMsgFindServerReplyBase();
        //case kNetServerMsgFindAuthServer: return new plNetServerMsgFindAuthServer();
        //case kNetServerMsgFindAuthServerReply: return new plNetServerMsgFindAuthServerReply();
        //case kNetServerMsgFindVaultServer: return new plNetServerMsgFindVaultServer();
        //case kNetServerMsgFindVaultServerReply: return new plNetServerMsgFindVaultServerReply();
        //case kAvTaskSeekDoneMsg: return new plAvTaskSeekDoneMsg();
        //case kAvatarSpawnNotifyMsg: return new plAvatarSpawnNotifyMsg();
        //case kNetServerMsgVaultTask: return new plNetServerMsgVaultTask();
        //case kNetMsgVaultTask: return new plNetMsgVaultTask();
        case kAgeLinkStruct: return new plAgeLinkStruct();
        //case kVaultAgeInfoNode: return new plVaultAgeInfoNode();
        //case kNetMsgStreamableHelper: return new plNetMsgStreamableHelper();
        //case kNetMsgReceiversListHelper: return new plNetMsgReceiversListHelper();
        //case kNetMsgListenListUpdate: return new plNetMsgListenListUpdate();
        //case kNetServerMsgPing: return new plNetServerMsgPing();
        //case kNetMsgAlive: return new plNetMsgAlive();
        //case kNetMsgTerminated: return new plNetMsgTerminated();
        //case kSDLModifierMsg: return new plSDLModifierMsg();
        case kNetMsgSDLState: return new plNetMsgSDLState();
        //case kNetServerMsgSessionReset: return new plNetServerMsgSessionReset();
        //case kCCRBanLinkingMsg: return new plCCRBanLinkingMsg();
        //case kCCRSilencePlayerMsg: return new plCCRSilencePlayerMsg();
        //case kRenderRequestMsg: return new plRenderRequestMsg();
        //case kRenderRequestAck: return new plRenderRequestAck();
        //case kNetMember: return new plNetMember();
        //case kNetGameMember: return new plNetGameMember();
        //case kNetTransportMember: return new plNetTransportMember();
        case kConvexVolume: return new plConvexVolume();
        case kParticleGenerator: ABSTRACT(kParticleGenerator);
        case kSimpleParticleGenerator: return new plSimpleParticleGenerator();
        case kParticleEmitter: return new plParticleEmitter();
        case kAGChannel: ABSTRACT(kAGChannel);
        case kMatrixChannel: return new plMatrixChannel();
        case kMatrixTimeScale: return new plMatrixTimeScale();
        case kMatrixBlend: return new plMatrixBlend();
        case kMatrixControllerChannel: return new plMatrixControllerChannel();
        case kQuatPointCombine: return new plQuatPointCombine();
        case kPointChannel: return new plPointChannel();
        case kPointConstant: return new plPointConstant();
        case kPointBlend: return new plPointBlend();
        case kQuatChannel: return new plQuatChannel();
        case kQuatConstant: return new plQuatConstant();
        case kQuatBlend: return new plQuatBlend();
        case kLinkToAgeMsg: return new plLinkToAgeMsg();
        //case kPlayerPageMsg: return new plPlayerPageMsg();
        //case kCmdIfaceModMsg: return new plCmdIfaceModMsg();
        //case kNetServerMsgPlsUpdatePlayer: return new plNetServerMsgPlsUpdatePlayer();
        //case kListenerMsg: return new plListenerMsg();
        case kAnimPath: return new plAnimPath();
        //case kClothingUpdateBCMsg: return new plClothingUpdateBCMsg();
        case kNotifyMsg: return new plNotifyMsg();
        //case kFakeOutMsg: return new plFakeOutMsg();
        case kCursorChangeMsg: return new plCursorChangeMsg();
        //case kNodeChangeMsg: return new plNodeChangeMsg();
        //case kAvEnableMsg: return new plAvEnableMsg();
        //case kLinkCallbackMsg: return new plLinkCallbackMsg();
        case kTransitionMsg: return new plTransitionMsg();
        //case kConsoleMsg: return new plConsoleMsg();
        case kVolumeIsect: ABSTRACT(kVolumeIsect);
        case kSphereIsect: return new plSphereIsect();
        case kConeIsect: return new plConeIsect();
        case kCylinderIsect: return new plCylinderIsect();
        case kParallelIsect: return new plParallelIsect();
        case kConvexIsect: return new plConvexIsect();
        case kComplexIsect: return new plComplexIsect();
        case kUnionIsect: return new plUnionIsect();
        case kIntersectionIsect: return new plIntersectionIsect();
        //case kModulator: return new plModulator();
        //case kInventoryMsg: return new plInventoryMsg();
        case kLinkEffectsTriggerMsg: return new plLinkEffectsTriggerMsg();
        //case kLinkEffectBCMsg: return new plLinkEffectBCMsg();
        case kResponderEnableMsg: return new plResponderEnableMsg();
        //case kNetServerMsgHello: return new plNetServerMsgHello();
        //case kNetServerMsgHelloReply: return new plNetServerMsgHelloReply();
        //case kNetServerMember: return new plNetServerMember();
        case kResponderMsg: return new plResponderMsg();
        case kOneShotMsg: return new plOneShotMsg();
        //case kVaultAgeInfoListNode: return new plVaultAgeInfoListNode();
        //case kNetServerMsgServerRegistered: return new plNetServerMsgServerRegistered();
        case kPointTimeScale: return new plPointTimeScale();
        case kPointControllerChannel: return new plPointControllerChannel();
        case kQuatTimeScale: return new plQuatTimeScale();
        case kAGApplicator: ABSTRACT(kAGApplicator);
        case kMatrixChannelApplicator: return new plMatrixChannelApplicator();
        case kPointChannelApplicator: return new plPointChannelApplicator();
        case kLightDiffuseApplicator: return new plLightDiffuseApplicator();
        case kLightAmbientApplicator: return new plLightAmbientApplicator();
        case kLightSpecularApplicator: return new plLightSpecularApplicator();
        case kOmniApplicator: return new plOmniApplicator();
        case kQuatChannelApplicator: return new plQuatChannelApplicator();
        case kScalarChannel: return new plScalarChannel();
        case kScalarTimeScale: return new plScalarTimeScale();
        case kScalarBlend: return new plScalarBlend();
        case kScalarControllerChannel: return new plScalarControllerChannel();
        case kScalarChannelApplicator: return new plScalarChannelApplicator();
        case kSpotInnerApplicator: return new plSpotInnerApplicator();
        case kSpotOuterApplicator: return new plSpotOuterApplicator();
        //case kNetServerMsgPlsRoutableMsg: return new plNetServerMsgPlsRoutableMsg();
        //case kPuppetBrainMsg: return new plPuppetBrainMsg();
        case kATCEaseCurve: return new plATCEaseCurve();
        case kConstAccelEaseCurve: return new plConstAccelEaseCurve();
        case kSplineEaseCurve: return new plSplineEaseCurve();
        //case kVaultAgeInfoInitializationTask: return new plVaultAgeInfoInitializationTask();
        //case kGameGUIMsg: return new pfGameGUIMsg();
        //case kNetServerMsgVaultRequestGameState: return new plNetServerMsgVaultRequestGameState();
        //case kNetServerMsgVaultGameState: return new plNetServerMsgVaultGameState();
        //case kNetServerMsgVaultGameStateSave: return new plNetServerMsgVaultGameStateSave();
        //case kNetServerMsgVaultGameStateSaved: return new plNetServerMsgVaultGameStateSaved();
        //case kNetServerMsgVaultGameStateLoad: return new plNetServerMsgVaultGameStateLoad();
        //case kNetClientTask: return new plNetClientTask();
        case kNetMsgSDLStateBCast: return new plNetMsgSDLStateBCast();
        //case kReplaceGeometryMsg: return new plReplaceGeometryMsg();
        //case kNetServerMsgExitProcess: return new plNetServerMsgExitProcess();
        //case kNetServerMsgSaveGameState: return new plNetServerMsgSaveGameState();
        //case kDniCoordinateInfo: return new plDniCoordinateInfo();
        case kNetMsgGameMessageDirected: return new plNetMsgGameMessageDirected();
        //case kLinkOutUnloadMsg: return new plLinkOutUnloadMsg();
        case kScalarConstant: return new plScalarConstant();
        case kMatrixConstant: return new plMatrixConstant();
        //case kAGCmdMsg: return new plAGCmdMsg();
        //case kParticleTransferMsg: return new plParticleTransferMsg();
        //case kParticleKillMsg: return new plParticleKillMsg();
        case kExcludeRegionMsg: return new plExcludeRegionMsg();
        case kOneTimeParticleGenerator: return new plOneTimeParticleGenerator();
        case kParticleApplicator: return new plParticleApplicator();
        case kParticleLifeMinApplicator: return new plParticleLifeMinApplicator();
        case kParticleLifeMaxApplicator: return new plParticleLifeMaxApplicator();
        case kParticlePPSApplicator: return new plParticlePPSApplicator();
        case kParticleAngleApplicator: return new plParticleAngleApplicator();
        case kParticleVelMinApplicator: return new plParticleVelMinApplicator();
        case kParticleVelMaxApplicator: return new plParticleVelMaxApplicator();
        case kParticleScaleMinApplicator: return new plParticleScaleMinApplicator();
        case kParticleScaleMaxApplicator: return new plParticleScaleMaxApplicator();
        //case kDynamicTextMsg: return new plDynamicTextMsg();
        //case kCameraTargetFadeMsg: return new plCameraTargetFadeMsg();
        //case kAgeLoadedMsg: return new plAgeLoadedMsg();
        case kPointControllerCacheChannel: return new plPointControllerCacheChannel();
        case kScalarControllerCacheChannel: return new plScalarControllerCacheChannel();
        //case kLinkEffectsTriggerPrepMsg: return new plLinkEffectsTriggerPrepMsg();
        //case kLinkEffectPrepBCMsg: return new plLinkEffectPrepBCMsg();
        case kAvatarInputStateMsg: return new plAvatarInputStateMsg();
        case kAgeInfoStruct: return new plAgeInfoStruct();
        //case kSDLNotificationMsg: return new plSDLNotificationMsg();
        //case kNetClientConnectAgeVaultTask: return new plNetClientConnectAgeVaultTask();
        case kLinkingMgrMsg: return new plLinkingMgrMsg();
        //case kVaultNotifyMsg: return new plVaultNotifyMsg();
        //case kPlayerInfo: return new plPlayerInfo();
        //case kSwapSpansRefMsg: return new plSwapSpansRefMsg();
        //case kKI: return new pfKI();
        //case kDISpansMsg: return new plDISpansMsg();
        //case kNetMsgCreatableHelper: return new plNetMsgCreatableHelper();
        //case kServerGuid: return new plServerGuid();
        //case kNetMsgRequestMyVaultPlayerList: return new plNetMsgRequestMyVaultPlayerList();
        //case kDelayedTransformMsg: return new plDelayedTransformMsg();
        //case kSuperVNodeMgrInitTask: return new plSuperVNodeMgrInitTask();
        //case kElementRefMsg: return new plElementRefMsg();
        //case kClothingMsg: return new plClothingMsg();
        //case kEventGroupEnableMsg: return new plEventGroupEnableMsg();
        //case kGUINotifyMsg: return new pfGUINotifyMsg();
        //case kAvBrain: return new plAvBrain();
        case kArmatureBrain: return new plArmatureBrain();
        case kAvBrainHuman: return new plAvBrainHuman();
        case kAvBrainCritter: return new plAvBrainCritter();
        case kAvBrainDrive: return new plAvBrainDrive();
        //case kAvBrainSample: return new plAvBrainSample();
        case kAvBrainGeneric: return new plAvBrainGeneric();
        //case kAvBrainPuppet: return new plAvBrainPuppet();
        //case kAvBrainLadder: return new plAvBrainLadder();
        case kInputIfaceMgrMsg: return new plInputIfaceMgrMsg();
        case kKIMsg: return new pfKIMsg();
        //case kRemoteAvatarInfoMsg: return new plRemoteAvatarInfoMsg();
        case kMatrixDelayedCorrectionApplicator: return new plMatrixDelayedCorrectionApplicator();
        case kAvPushBrainMsg: return new plAvPushBrainMsg();
        case kAvPopBrainMsg: return new plAvPopBrainMsg();
        //case kRoomLoadNotifyMsg: return new plRoomLoadNotifyMsg();
        case kAvTask: ABSTRACT(kAvTask);
        case kAvAnimTask: return new plAvAnimTask();
        case kAvSeekTask: return new plAvSeekTask();
        //case kAvBlendedSeekTask: return new plAvBlendedSeekTask();
        case kAvOneShotTask: return new plAvOneShotTask();
        //case kAvEnableTask: return new plAvEnableTask();
        case kAvTaskBrain: return new plAvTaskBrain();
        case kAnimStage: return new plAnimStage();
        //case kNetClientMember: return new plNetClientMember();
        //case kNetClientCommTask: return new plNetClientCommTask();
        //case kNetServerMsgAuthRequest: return new plNetServerMsgAuthRequest();
        //case kNetServerMsgAuthReply: return new plNetServerMsgAuthReply();
        //case kNetClientCommAuthTask: return new plNetClientCommAuthTask();
        case kClientGuid: return new plClientGuid();
        //case kNetMsgVaultPlayerList: return new plNetMsgVaultPlayerList();
        //case kNetMsgSetMyActivePlayer: return new plNetMsgSetMyActivePlayer();
        //case kNetServerMsgRequestAccountPlayerList: return new plNetServerMsgRequestAccountPlayerList();
        //case kNetServerMsgAccountPlayerList: return new plNetServerMsgAccountPlayerList();
        //case kNetMsgPlayerCreated: return new plNetMsgPlayerCreated();
        //case kNetServerMsgVaultCreatePlayer: return new plNetServerMsgVaultCreatePlayer();
        //case kNetServerMsgVaultPlayerCreated: return new plNetServerMsgVaultPlayerCreated();
        //case kNetMsgFindAge: return new plNetMsgFindAge();
        //case kNetMsgFindAgeReply: return new plNetMsgFindAgeReply();
        //case kNetClientConnectPrepTask: return new plNetClientConnectPrepTask();
        //case kNetClientAuthTask: return new plNetClientAuthTask();
        //case kNetClientGetPlayerVaultTask: return new plNetClientGetPlayerVaultTask();
        //case kNetClientSetActivePlayerTask: return new plNetClientSetActivePlayerTask();
        //case kNetClientFindAgeTask: return new plNetClientFindAgeTask();
        //case kNetClientLeaveTask: return new plNetClientLeaveTask();
        //case kNetClientJoinTask: return new plNetClientJoinTask();
        //case kNetClientCalibrateTask: return new plNetClientCalibrateTask();
        //case kNetMsgDeletePlayer: return new plNetMsgDeletePlayer();
        //case kNetServerMsgVaultDeletePlayer: return new plNetServerMsgVaultDeletePlayer();
        //case kNetCoreStatsSummary: return new plNetCoreStatsSummary();
        //case kCreatableGenericValue: return new plCreatableGenericValue();
        //case kCreatableListHelper: return new plCreatableListHelper();
        //case kCreatableStream: return new plCreatableStream();
        case kAvBrainGenericMsg: return new plAvBrainGenericMsg();
        case kAvTaskSeek: return new plAvTaskSeek();
        //case kAGInstanceCallbackMsg: return new plAGInstanceCallbackMsg();
        //case kArmatureEffectMsg: return new plArmatureEffectMsg();
        case kArmatureEffectStateMsg: return new plArmatureEffectStateMsg();
        //case kShadowCastMsg: return new plShadowCastMsg();
        case kBoundsIsect: return new plBoundsIsect();
        //case kNetClientCommLeaveTask: return new plNetClientCommLeaveTask();
        //case kResMgrHelperMsg: return new plResMgrHelperMsg();
        //case kNetMsgAuthenticateResponse: return new plNetMsgAuthenticateResponse();
        //case kNetMsgAccountAuthenticated: return new plNetMsgAccountAuthenticated();
        //case kNetClientCommSendPeriodicAliveTask: return new plNetClientCommSendPeriodicAliveTask();
        //case kNetClientCommCheckServerSilenceTask: return new plNetClientCommCheckServerSilenceTask();
        //case kNetClientCommPingTask: return new plNetClientCommPingTask();
        //case kNetClientCommFindAgeTask: return new plNetClientCommFindAgeTask();
        //case kNetClientCommSetActivePlayerTask: return new plNetClientCommSetActivePlayerTask();
        //case kNetClientCommGetPlayerListTask: return new plNetClientCommGetPlayerListTask();
        //case kNetClientCommCreatePlayerTask: return new plNetClientCommCreatePlayerTask();
        //case kNetClientCommJoinAgeTask: return new plNetClientCommJoinAgeTask();
        //case kVaultAdminInitializationTask: return new plVaultAdminInitializationTask();
        //case kMultistageModMsg: return new plMultistageModMsg();
        case kSoundVolumeApplicator: return new plSoundVolumeApplicator();
        //case kCutter: return new plCutter();
        //case kBulletMsg: return new plBulletMsg();
        //case kDynaDecalEnableMsg: return new plDynaDecalEnableMsg();
        case kOmniCutoffApplicator: return new plOmniCutoffApplicator();
        //case kArmatureUpdateMsg: return new plArmatureUpdateMsg();
        //case kAvatarFootMsg: return new plAvatarFootMsg();
        //case kNetOwnershipMsg: return new plNetOwnershipMsg();
        case kNetMsgRelevanceRegions: return new plNetMsgRelevanceRegions();
        //case kParticleFlockMsg: return new plParticleFlockMsg();
        //case kAvatarBehaviorNotifyMsg: return new plAvatarBehaviorNotifyMsg();
        case kATCChannel: return new plATCChannel();
        case kScalarSDLChannel: return new plScalarSDLChannel();
        case kLoadAvatarMsg: return new plLoadAvatarMsg();
        //case kAvatarSetTypeMsg: return new plAvatarSetTypeMsg();
        case kNetMsgLoadClone: return new plNetMsgLoadClone();
        case kNetMsgPlayerPage: return new plNetMsgPlayerPage();
        //case kVNodeInitTask: return new plVNodeInitTask();
        //case kRippleShapeMsg: return new plRippleShapeMsg();
        //case kEventManager: return new plEventManager();
        //case kVaultNeighborhoodInitializationTask: return new plVaultNeighborhoodInitializationTask();
        //case kNetServerMsgAgentRecoveryRequest: return new plNetServerMsgAgentRecoveryRequest();
        //case kNetServerMsgFrontendRecoveryRequest: return new plNetServerMsgFrontendRecoveryRequest();
        //case kNetServerMsgBackendRecoveryRequest: return new plNetServerMsgBackendRecoveryRequest();
        //case kNetServerMsgAgentRecoveryData: return new plNetServerMsgAgentRecoveryData();
        //case kNetServerMsgFrontendRecoveryData: return new plNetServerMsgFrontendRecoveryData();
        //case kNetServerMsgBackendRecoveryData: return new plNetServerMsgBackendRecoveryData();
        case kSubWorldMsg: return new plSubWorldMsg();
        case kMatrixDifferenceApp: return new plMatrixDifferenceApp();
        //case kAvBrainUser: return new plAvBrainUser();
        //case kDX9Pipeline: return new plDX9Pipeline();
        //case kDXPipeline: return new plDXPipeline();
        //case kPlayerMsg: return new plPlayerMsg();
        case kAvBrainPirahna: return new plAvBrainPirahna();
        //case kAxisEventMsg: return new plAxisEventMsg();
        case kCrossfadeMsg: return new plCrossfadeMsg();
        //case kSubtitleMsg: return new pfSubtitleMsg();
        //case kSDLStoreMsg: return new plSDLStoreMsg();
        case kOmniSqApplicator: return new plOmniSqApplicator();
        //case kPreResourceMsg: return new plPreResourceMsg();
        //case kDynamicColorRGBA: return new hsDynamicColorRGBA();
        //case kDynamicMatrix33: return new hsDynamicMatrix33();
        //case kDynamicMatrix44: return new hsDynamicMatrix44();
        case kCompoundController: return new plCompoundController();
        //case kNetClientMgrMsg: return new plNetClientMgrMsg();
        //case kAgeLoaderMsg: return new plAgeLoaderMsg();
        case kAvBrainAvatar: return new plAvBrainAvatar();
        //case kPythonNotifyMsg: return new pfPythonNotifyMsg();
        //case kNCAgeJoinerMsg: return new plNCAgeJoinerMsg();
        //case kAvTaskDumbSeek: return new plAvTaskDumbSeek();
        //case kAvTaskSmartSeek: return new plAvTaskSmartSeek();
        //case kCreatableUuid: return new plCreatableUuid();
        //case kPreloaderMsg: return new plPreloaderMsg();
        //case kNetCommAuthConnectedMsg: return new plNetCommAuthConnectedMsg();
        //case kNetCommAuthMsg: return new plNetCommAuthMsg();
        //case kNetCommFileListMsg: return new plNetCommFileListMsg();
        //case kNetCommFileDownloadMsg: return new plNetCommFileDownloadMsg();
        //case kNetCommLinkToAgeMsg: return new plNetCommLinkToAgeMsg();
        //case kNetCommPlayerListMsg: return new plNetCommPlayerListMsg();
        //case kNetCommActivePlayerMsg: return new plNetCommActivePlayerMsg();
        //case kNetCommCreatePlayerMsg: return new plNetCommCreatePlayerMsg();
        //case kNetCommDeletePlayerMsg: return new plNetCommDeletePlayerMsg();
        //case kNetCommPublicAgeListMsg: return new plNetCommPublicAgeListMsg();
        //case kNetCommPublicAgeMsg: return new plNetCommPublicAgeMsg();
        //case kNetCommRegisterAgeMsg: return new plNetCommRegisterAgeMsg();
        //case kAnimEvalMsg: return new plAnimEvalMsg();
        //case kAvBrainFlight: return new plAvBrainFlight();
        //case kAvBrainNPC: return new plAvBrainNPC();
        //case kAvBrainBlimp: return new plAvBrainBlimp();
        //case kAvBrainFlightNPC: return new plAvBrainFlightNPC();
        //case kParticleBulletHitMsg: return new plParticleBulletHitMsg();
        //case kPanicLinkMsg: return new pfPanicLinkMsg();
        //case kAvTaskOneShot: return new plAvTaskOneShot();

        // Non-Keyed Post-DB Classes //
        //case kVaultGameServerInitializationTask: return new plVaultGameServerInitializationTask();
        //case kNetClientFindDefaultAgeTask: return new plNetClientFindDefaultAgeTask();
        //case kVaultAgeNode: return new plVaultAgeNode();
        //case kVaultAgeInitializationTask: return new plVaultAgeInitializationTask();
        //case kSetListenerMsg: return new plSetListenerMsg();
        //case kVaultSystemNode: return new plVaultSystemNode();
        case kAvBrainSwim: return new plAvBrainSwim();
        //case kNetMsgVault: return new plNetMsgVault();
        //case kNetServerMsgVault: return new plNetServerMsgVault();
        //case kVaultTask: return new plVaultTask();
        //case kVaultConnectTask: return new plVaultConnectTask();
        //case kVaultNegotiateManifestTask: return new plVaultNegotiateManifestTask();
        //case kVaultFetchNodesTask: return new plVaultFetchNodesTask();
        //case kVaultSaveNodeTask: return new plVaultSaveNodeTask();
        //case kVaultFindNodeTask: return new plVaultFindNodeTask();
        //case kVaultAddNodeRefTask: return new plVaultAddNodeRefTask();
        //case kVaultRemoveNodeRefTask: return new plVaultRemoveNodeRefTask();
        //case kVaultSendNodeTask: return new plVaultSendNodeTask();
        //case kVaultNotifyOperationCallbackTask: return new plVaultNotifyOperationCallbackTask();
        //case kVNodeMgrInitializationTask: return new plVNodeMgrInitializationTask();
        //case kVaultPlayerInitializationTask: return new plVaultPlayerInitializationTask();
        //case kNetVaultServerInitializationTask: return new plNetVaultServerInitializationTask();
        //case kCommonNeighborhoodsInitTask: return new plCommonNeighborhoodsInitTask();
        //case kVaultNodeRef: return new plVaultNodeRef();
        //case kVaultNode: return new plVaultNode();
        //case kVaultFolderNode: return new plVaultFolderNode();
        //case kVaultImageNode: return new plVaultImageNode();
        //case kVaultTextNoteNode: return new plVaultTextNoteNode();
        //case kVaultSDLNode: return new plVaultSDLNode();
        //case kVaultAgeLinkNode: return new plVaultAgeLinkNode();
        //case kVaultChronicleNode: return new plVaultChronicleNode();
        //case kVaultPlayerInfoNode: return new plVaultPlayerInfoNode();
        //case kVaultMgrNode: return new plVaultMgrNode();
        //case kVaultPlayerNode: return new plVaultPlayerNode();
        //case kSynchEnableMsg: return new plSynchEnableMsg();
        //case kNetVaultServerNode: return new plNetVaultServerNode();
        //case kVaultAdminNode: return new plVaultAdminNode();
        //case kVaultGameServerNode: return new plVaultGameServerNode();
        //case kVaultPlayerInfoListNode: return new plVaultPlayerInfoListNode();
        //case kAvatarStealthModeMsg: return new plAvatarStealthModeMsg();
        //case kEventCallbackInterceptMsg: return new plEventCallbackInterceptMsg();
        //case kDynamicEnvMapMsg: return new plDynamicEnvMapMsg();
        case kClimbMsg: return new plClimbMsg();
        //case kIfaceFadeAvatarMsg: return new plIfaceFadeAvatarMsg();
        case kAvBrainClimb: return new plAvBrainClimb();
        //case kSharedMeshBCMsg: return new plSharedMeshBCMsg();
        //case kNetVoiceListMsg: return new plNetVoiceListMsg();
        case kSwimMsg: return new plSwimMsg();
        case kMorphDelta: return new plMorphDelta();
        case kMatrixControllerCacheChannel: return new plMatrixControllerCacheChannel();
        //case kVaultMarkerNode: return new plVaultMarkerNode();
        //case kMarkerMsg: return new pfMarkerMsg();
        //case kPipeResMakeMsg: return new plPipeResMakeMsg();
        //case kPipeRTMakeMsg: return new plPipeRTMakeMsg();
        //case kPipeGeoMakeMsg: return new plPipeGeoMakeMsg();
        //case kAvCoopMsg: return new plAvCoopMsg();
        case kAvBrainCoop: return new plAvBrainCoop();
        case kSimSuppressMsg: return new plSimSuppressMsg();
        //case kVaultMarkerListNode: return new plVaultMarkerListNode();
        //case kAvTaskOrient: return new plAvTaskOrient();
        //case kAgeBeginLoadingMsg: return new plAgeBeginLoadingMsg();
        //case kSetNetGroupIDMsg: return new plSetNetGroupIDMsg();
        //case kBackdoorMsg: return new pfBackdoorMsg();
        //case kNetMsgPython: return new plNetMsgPython();
        //case kPythonMsg: return new pfPythonMsg();
        //case kStateDataRecord: return new plStateDataRecord();
        //case kNetClientCommDeletePlayerTask: return new plNetClientCommDeletePlayerTask();
        //case kNetMsgSetTimeout: return new plNetMsgSetTimeout();
        //case kNetMsgActivePlayerSet: return new plNetMsgActivePlayerSet();
        //case kNetClientCommSetTimeoutTask: return new plNetClientCommSetTimeoutTask();
        //case kNetRoutableMsgOmnibus: return new plNetRoutableMsgOmnibus();
        //case kNetMsgGetPublicAgeList: return new plNetMsgGetPublicAgeList();
        //case kNetMsgPublicAgeList: return new plNetMsgPublicAgeList();
        //case kNetMsgCreatePublicAge: return new plNetMsgCreatePublicAge();
        //case kNetMsgPublicAgeCreated: return new plNetMsgPublicAgeCreated();
        //case kNetServerMsgEnvelope: return new plNetServerMsgEnvelope();
        //case kNetClientCommGetPublicAgeListTask: return new plNetClientCommGetPublicAgeListTask();
        //case kNetClientCommCreatePublicAgeTask: return new plNetClientCommCreatePublicAgeTask();
        //case kNetServerMsgPendingMsgs: return new plNetServerMsgPendingMsgs();
        //case kNetServerMsgRequestPendingMsgs: return new plNetServerMsgRequestPendingMsgs();
        //case kDbInterface: return new plDbInterface();
        //case kDbProxyInterface: return new plDbProxyInterface();
        //case kDBGenericSQLDB: return new plDBGenericSQLDB();
        //case kMySqlDB: return new plMySqlDB();
        //case kNetGenericDatabase: return new plNetGenericDatabase();
        //case kNetVaultDatabase: return new plNetVaultDatabase();
        //case kNetServerMsgPlsUpdatePlayerReply: return new plNetServerMsgPlsUpdatePlayerReply();
        //case kVaultDisconnectTask: return new plVaultDisconnectTask();
        //case kNetClientCommSetAgePublicTask: return new plNetClientCommSetAgePublicTask();
        //case kNetClientCommRegisterOwnedAge: return new plNetClientCommRegisterOwnedAge();
        //case kNetClientCommUnregisterOwnerAge: return new plNetClientCommUnregisterOwnerAge();
        //case kNetClientCommRegisterVisitAge: return new plNetClientCommRegisterVisitAge();
        //case kNetClientCommUnregisterVisitAge: return new plNetClientCommUnregisterVisitAge();
        //case kNetMsgRemovePublicAge: return new plNetMsgRemovePublicAge();
        //case kNetMsgPublicAgeRemoved: return new plNetMsgPublicAgeRemoved();
        //case kNetClientCommRemovePublicAgeTask: return new plNetClientCommRemovePublicAgeTask();
        //case kCCRMessage: return new plCCRMessage();
        case kAvOneShotLinkTask: return new plAvOneShotLinkTask();
        //case kNetAuthDatabase: return new plNetAuthDatabase();
        //case kAvatarOpacityCallbackMsg: return new plAvatarOpacityCallbackMsg();
        //case kAGDetachCallbackMsg: return new plAGDetachCallbackMsg();
        //case kMovieEventMsg: return new pfMovieEventMsg();
        //case kMovieMsg: return new plMovieMsg();
        //case kPipeTexMakeMsg: return new plPipeTexMakeMsg();
        //case kEventLog: return new plEventLog();
        //case kDbEventLog: return new plDbEventLog();
        //case kSyslogEventLog: return new plSyslogEventLog();
        //case kCaptureRenderMsg: return new plCaptureRenderMsg();
        //case kAgeLoaded2Msg: return new plAgeLoaded2Msg();
        //case kPseudoLinkEffectMsg: return new plPseudoLinkEffectMsg();
        //case kPseudoLinkAnimTriggerMsg: return new plPseudoLinkAnimTriggerMsg();
        //case kPseudoLinkAnimCallbackMsg: return new plPseudoLinkAnimCallbackMsg();
        //case kClimbingWallMsg: return new pfClimbingWallMsg();
        //case kClimbEventMsg: return new plClimbEventMsg();
        case kAvBrainQuab: return new plAvBrainQuab();
        //case kSDLGameTimeElapsedVar: return new plSDLGameTimeElapsedVar();
        //case kLinkEffectsDoneMsg: return new plLinkEffectsDoneMsg();
        //case kSDLVar: return new plSDLVar();
        //case kSDLStructVar: return new plSDLStructVar();
        //case kSDLBoolVar: return new plSDLBoolVar();
        //case kSDLCharVar: return new plSDLCharVar();
        //case kSDLByteVar: return new plSDLByteVar();
        //case kSDLIntVar: return new plSDLIntVar();
        //case kSDLUIntVar: return new plSDLUIntVar();
        //case kSDLFloatVar: return new plSDLFloatVar();
        //case kSDLDoubleVar: return new plSDLDoubleVar();
        //case kSDLStringVar: return new plSDLStringVar();
        //case kSDLTimeVar: return new plSDLTimeVar();
        //case kSDLUoidVar: return new plSDLUoidVar();
        //case kSDLVector3Var: return new plSDLVector3Var();
        //case kSDLPoint3Var: return new plSDLPoint3Var();
        //case kSDLQuaternionVar: return new plSDLQuaternionVar();
        //case kSDLMatrix44Var: return new plSDLMatrix44Var();
        //case kSDLRGBAVar: return new plSDLRGBAVar();
        //case kSDLAgeTimeOfDayVar: return new plSDLAgeTimeOfDayVar();
        //case kSDLAgeTimeElapsedVar: return new plSDLAgeTimeElapsedVar();
        //case kSDLMetaDoubleVar: return new plSDLMetaDoubleVar();
        //case kSDLFixedArrayStructVar: return new plSDLFixedArrayStructVar();
        //case kSDLFixedArrayBoolVar: return new plSDLFixedArrayBoolVar();
        //case kSDLFixedArrayCharVar: return new plSDLFixedArrayCharVar();
        //case kSDLFixedArrayByteVar: return new plSDLFixedArrayByteVar();
        //case kSDLFixedArrayIntVar: return new plSDLFixedArrayIntVar();
        //case kSDLFixedArrayUIntVar: return new plSDLFixedArrayUIntVar();
        //case kSDLFixedArrayFloatVar: return new plSDLFixedArrayFloatVar();
        //case kSDLFixedArrayDoubleVar: return new plSDLFixedArrayDoubleVar();
        //case kSDLFixedArrayStringVar: return new plSDLFixedArrayStringVar();
        //case kSDLFixedArrayTimeVar: return new plSDLFixedArrayTimeVar();
        //case kSDLFixedArrayUoidVar: return new plSDLFixedArrayUoidVar();
        //case kSDLFixedArrayVector3Var: return new plSDLFixedArrayVector3Var();
        //case kSDLFixedArrayPoint3Var: return new plSDLFixedArrayPoint3Var();
        //case kSDLFixedArrayQuaternionVar: return new plSDLFixedArrayQuaternionVar();
        //case kSDLFixedArrayMatrix44Var: return new plSDLFixedArrayMatrix44Var();
        //case kSDLFixedArrayRGBAVar: return new plSDLFixedArrayRGBAVar();
        //case kSDLDynArrayStructVar: return new plSDLDynArrayStructVar();
        //case kSDLDynArrayBoolVar: return new plSDLDynArrayBoolVar();
        //case kSDLDynArrayCharVar: return new plSDLDynArrayCharVar();
        //case kSDLDynArrayByteVar: return new plSDLDynArrayByteVar();
        //case kSDLDynArrayIntVar: return new plSDLDynArrayIntVar();
        //case kSDLDynArrayUIntVar: return new plSDLDynArrayUIntVar();
        //case kSDLDynArrayFloatVar: return new plSDLDynArrayFloatVar();
        //case kSDLDynArrayDoubleVar: return new plSDLDynArrayDoubleVar();
        //case kSDLDynArrayStringVar: return new plSDLDynArrayStringVar();
        //case kSDLDynArrayTimeVar: return new plSDLDynArrayTimeVar();
        //case kSDLDynArrayUoidVar: return new plSDLDynArrayUoidVar();
        //case kSDLDynArrayVector3Var: return new plSDLDynArrayVector3Var();
        //case kSDLDynArrayPoint3Var: return new plSDLDynArrayPoint3Var();
        //case kSDLDynArrayQuaternionVar: return new plSDLDynArrayQuaternionVar();
        //case kSDLDynArrayMatrix44Var: return new plSDLDynArrayMatrix44Var();
        //case kSDLDynArrayRGBAVar: return new plSDLDynArrayRGBAVar();
        //case kSDLArrayVar: return new plSDLArrayVar();
        //case kSDLVarChangeMsg: return new plSDLVarChangeMsg();
        //case kAvBrainPath: return new plAvBrainPath();
        //case kSDLBufferVar: return new plSDLBufferVar();
        //case kSDLFixedArrayBufferVar: return new plSDLFixedArrayBufferVar();
        //case kSDLDynArrayBufferVar: return new plSDLDynArrayBufferVar();
        //case kMatrixBorrowedChannel: return new plMatrixBorrowedChannel();
        //case kNodeRegionMsg: return new plNodeRegionMsg();
        case kEventCallbackSetupMsg: return new plEventCallbackSetupMsg();
        case kRelativeMatrixChannelApplicator: return new plRelativeMatrixChannelApplicator();
        //case kPiranhaRegionMsg: return new plPiranhaRegionMsg();
        //case kGameMgrMsg: return new pfGameMgrMsg();
        //case kGameCliMsg: return new pfGameCliMsg();
        //case kGameCli: return new pfGameCli();
        //case kGmTicTacToe: return new pfGmTicTacToe();
        //case kGmHeek: return new pfGmHeek();
        //case kGmMarker: return new pfGmMarker();
        //case kGmBlueSpiral: return new pfGmBlueSpiral();
        case kAccountUpdateMsg: return new plAccountUpdateMsg();
        //case kAIMsg: return new plAIMsg();
        //case kAIBrainCreatedMsg: return new plAIBrainCreatedMsg();
        //case kGmClimbingWall: return new pfGmClimbingWall();
        //case kAIArrivedAtGoalMsg: return new plAIArrivedAtGoalMsg();
        //case kGmVarSync: return new pfGmVarSync();
        //case kLinearVelocityMsg: return new plLinearVelocityMsg();
        //case kAngularVelocityMsg: return new plAngularVelocityMsg();
        case kRideAnimatedPhysMsg: return new plRideAnimatedPhysMsg();
        case kAvBrainRideAnimatedPhysical: return new plAvBrainRideAnimatedPhysical();

        // Got an invalid or unsupported ClassIndex //
        default: return nullptr;
    }
}

plCreatable* plFactory::Create(short typeIdx, PlasmaVer ver)
{
    if (typeIdx < 0)
        return nullptr;
    if (!ver.isValid())
        throw hsBadVersionException(__FILE__, __LINE__);
    return Create(pdUnifiedTypeMap::PlasmaToMapped(typeIdx, ver));
}

plCreatable* plFactory::Create(const char* typeName)
{
    return Create(pdUnifiedTypeMap::ClassIndex(typeName));
}

const char* plFactory::ClassName(short typeIdx)
{
    if (typeIdx < 0)
        return nullptr;
    return pdUnifiedTypeMap::ClassName(typeIdx);
}

const char* plFactory::ClassName(short typeIdx, PlasmaVer ver)
{
    if (typeIdx < 0)
        return nullptr;
    return pdUnifiedTypeMap::ClassName(typeIdx, ver);
}

short plFactory::ClassIndex(const char* typeName)
{
    return pdUnifiedTypeMap::ClassIndex(typeName);
}

short plFactory::ClassVersion(short typeIdx, PlasmaVer ver)
{
    return pdUnifiedTypeMap::ClassVersion(typeIdx, ver);
}
