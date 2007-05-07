#include "plFactory.h"

// Includes for all plCreatable types
#include "../../FeatureLib/pfPython/plPythonFileMod.h"
//#include "../pnKeyedObject/hsKeyedObject.h"
#include "../pnModifier/plModifier.h"
#include "../pnNetCommon/plSynchedObject.h"
#include "../pnSceneObject/plAudioInterface.h"
#include "../pnSceneObject/plCoordinateInterface.h"
#include "../pnSceneObject/plDrawInterface.h"
#include "../pnSceneObject/plObjInterface.h"
#include "../pnSceneObject/plSceneObject.h"
#include "../pnSceneObject/plSimulationInterface.h"
#include "../../PubUtilLib/plAvatar/plClothingItem.h"
#include "../../PubUtilLib/plDrawable/plDrawableSpans.h"
#include "../../PubUtilLib/plGImage/plCubicEnvironmap.h"
#include "../../PubUtilLib/plGImage/plFont.h"
#include "../../PubUtilLib/plGImage/plMipmap.h"
#include "../../PubUtilLib/plGLight/plLightInfo.h"
#include "../../PubUtilLib/plModifier/plImageLibMod.h"
#include "../../PubUtilLib/plPipeline/plFogEnvironment.h"
#include "../../PubUtilLib/plScene/plSceneNode.h"
#include "../../PubUtilLib/plSurface/hsGMaterial.h"
#include "../../PubUtilLib/plSurface/plLayer.h"
// End types

plCreatable* plFactory::Create(short typeIdx) {
    switch (typeIdx) {
        case kSceneNode: return new plSceneNode();
        case kSceneObject: return new plSceneObject();
        case kKeyedObject: return new hsKeyedObject();
        case kBitmap: return new plBitmap();
        case kMipmap: return new plMipmap();
        case kCubicEnvironmap: return new plCubicEnvironmap();
        case kLayer: return new plLayer();
        case kGMaterial: return new hsGMaterial();
        //case kParticleSystem: return new plParticleSystem();
        //case kParticleEffect: return new plParticleEffect();
        //case kParticleCollisionEffectBeat: return new plParticleCollisionEffectBeat();
        //case kParticleFadeVolumeEffect: return new plParticleFadeVolumeEffect();
        //case kBoundInterface: return new plBoundInterface();
        //case kRenderTarget: return new plRenderTarget();
        //case kCubicRenderTarget: return new plCubicRenderTarget();
        //case kCubicRenderTargetModifier: return new plCubicRenderTargetModifier();
        case kObjInterface: return new plObjInterface();
        case kAudioInterface: return new plAudioInterface();
        //case kAudible: return new plAudible();
        //case kAudibleNull: return new plAudibleNull();
        //case kWinAudible: return new plWinAudible();
        case kCoordinateInterface: return new plCoordinateInterface();
        case kDrawInterface: return new plDrawInterface();
        case kDrawable: return new plDrawable();
        //case kDrawableMesh: return new plDrawableMesh();
        //case kDrawableIce: return new plDrawableIce();
        //case kPhysical: return new plPhysical();
        //case kPhysicalMesh: return new plPhysicalMesh();
        case kSimulationInterface: return new plSimulationInterface();
        //case kCameraModifier: return new plCameraModifier();
        case kModifier: return new plModifier();
        case kSingleModifier: return new plSingleModifier();
        //case kSimpleModifier: return new plSimpleModifier();
        //case kSimpleTMModifier: return new plSimpleTMModifier();
        //case kRandomTMModifier: return new plRandomTMModifier();
        //case kInterestingModifier: return new plInterestingModifier();
        //case kDetectorModifier: return new plDetectorModifier();
        //case kSimplePhysicalMesh: return new plSimplePhysicalMesh();
        //case kCompoundPhysicalMesh: return new plCompoundPhysicalMesh();
        case kMultiModifier: return new plMultiModifier();
        case kSynchedObject: return new plSynchedObject();
        //case kSoundBuffer: return new plSoundBuffer();
        //case kAliasModifier: return new plAliasModifier();
        //case kPickingDetector: return new plPickingDetector();
        //case kCollisionDetector: return new plCollisionDetector();
        //case kLogicModifier: return new plLogicModifier();
        //case kConditionalObject: return new plConditionalObject();
        //case kANDConditionalObject: return new plANDConditionalObject();
        //case kORConditionalObject: return new plORConditionalObject();
        //case kPickedConditionalObject: return new plPickedConditionalObject();
        //case kActivatorConditionalObject: return new plActivatorConditionalObject();
        //case kTimerCallbackManager: return new plTimerCallbackManager();
        //case kKeyPressConditionalObject: return new plKeyPressConditionalObject();
        //case kAnimationEventConditionalObject: return new plAnimationEventConditionalObject();
        //case kControlEventConditionalObject: return new plControlEventConditionalObject();
        //case kObjectInBoxConditionalObject: return new plObjectInBoxConditionalObject();
        //case kLocalPlayerInBoxConditioinalObject: return new plLocalPlayerInBoxConditioinalObject();
        //case kObjectIntersectPlaneConditionalObject: return new plObjectIntersectPlaneConditionalObject();
        //case kLocalPlayerIntersectPlaneConditionalObject: return new plLocalPlayerIntersectPlaneConditionalObject();
        //case kPortalDrawable: return new plPortalDrawable();
        //case kPortalPhysical: return new plPortalPhysical();
        //case kSpawnModifier: return new plSpawnModifier();
        //case kFacingConditionalObject: return new plFacingConditionalObject();
        //case kHKPhysical: return new plHKPhysical();
        //case kViewFaceModifier: return new plViewFaceModifier();
        case kLayerInterface: return new plLayerInterface();
        //case kLayerWrapper: return new plLayerWrapper();
        //case kLayerAnimation: return new plLayerAnimation();
        //case kLayerDepth: return new plLayerDepth();
        //case kLayerMovie: return new plLayerMovie();
        //case kLayerBink: return new plLayerBink();
        //case kLayerAVI: return new plLayerAVI();
        //case kSound: return new plSound();
        //case kWin32Sound: return new plWin32Sound();
        //case kLayerOr: return new plLayerOr();
        //case kAudioSystem: return new plAudioSystem();
        //case kDrawableSpans: return new plDrawableSpans();
        //case kDrawablePatchSet: return new plDrawablePatchSet();
        //case kInputManager: return new plInputManager();
        //case kLogicModBase: return new plLogicModBase();
        case kFogEnvironment: return new plFogEnvironment();
        //case kNetApp: return new plNetApp();
        //case kNetClientMgr: return new plNetClientMgr();
        //case k2WayWinAudible: return new pl2WayWinAudible();
        case kLightInfo: return new plLightInfo();
        //case kDirectionalLightInfo: return new plDirectionalLightInfo();
        //case kOmniLightInfo: return new plOmniLightInfo();
        //case kSpotLightInfo: return new plSpotLightInfo();
        //case kLightSpace: return new plLightSpace();
        //case kNetClientApp: return new plNetClientApp();
        //case kNetServerApp: return new plNetServerApp();
        //case kClient: return new plClient();
        //case kCompoundTMModifier: return new plCompoundTMModifier();
        //case kCameraBrain: return new plCameraBrain();
        //case kCameraBrain_Default: return new plCameraBrain_Default();
        //case kCameraBrain_Drive: return new plCameraBrain_Drive();
        //case kCameraBrain_Fixed: return new plCameraBrain_Fixed();
        //case kCameraBrain_FixedPan: return new plCameraBrain_FixedPan();
        //case kGUIClickMapCtrl: return new pfGUIClickMapCtrl();
        //case kListener: return new plListener();
        //case kAvatarMod: return new plAvatarMod();
        //case kAvatarAnim: return new plAvatarAnim();
        //case kAvatarAnimMgr: return new plAvatarAnimMgr();
        //case kOccluder: return new plOccluder();
        //case kMobileOccluder: return new plMobileOccluder();
        //case kLayerShadowBase: return new plLayerShadowBase();
        //case kLimitedDirLightInfo: return new plLimitedDirLightInfo();
        //case kAGAnim: return new plAGAnim();
        //case kAGModifier: return new plAGModifier();
        //case kAGMasterMod: return new plAGMasterMod();
        //case kCameraBrain_Avatar: return new plCameraBrain_Avatar();
        //case kCameraRegionDetector: return new plCameraRegionDetector();
        //case kCameraBrain_FP: return new plCameraBrain_FP();
        //case kLineFollowMod: return new plLineFollowMod();
        //case kLightModifier: return new plLightModifier();
        //case kOmniModifier: return new plOmniModifier();
        //case kSpotModifier: return new plSpotModifier();
        //case kLtdDirModifier: return new plLtdDirModifier();
        //case kSeekPointMod: return new plSeekPointMod();
        //case kOneShotMod: return new plOneShotMod();
        //case kRandomCommandMod: return new plRandomCommandMod();
        //case kRandomSoundMod: return new plRandomSoundMod();
        //case kPostEffectMod: return new plPostEffectMod();
        //case kObjectInVolumeDetector: return new plObjectInVolumeDetector();
        //case kResponderModifier: return new plResponderModifier();
        //case kAxisAnimModifier: return new plAxisAnimModifier();
        //case kLayerLightBase: return new plLayerLightBase();
        //case kFollowMod: return new plFollowMod();
        //case kTransitionMgr: return new plTransitionMgr();
        //case kInventoryMod: return new plInventoryMod();
        //case kInventoryObjMod: return new plInventoryObjMod();
        //case kLinkEffectsMgr: return new plLinkEffectsMgr();
        //case kWin32StreamingSound: return new plWin32StreamingSound();
        //case kPythonMod: return new plPythonMod();
        //case kActivatorActivatorConditionalObject: return new plActivatorActivatorConditionalObject();
        //case kSoftVolume: return new plSoftVolume();
        //case kSoftVolumeSimple: return new plSoftVolumeSimple();
        //case kSoftVolumeComplex: return new plSoftVolumeComplex();
        //case kSoftVolumeUnion: return new plSoftVolumeUnion();
        //case kSoftVolumeIntersect: return new plSoftVolumeIntersect();
        //case kSoftVolumeInvert: return new plSoftVolumeInvert();
        //case kWin32LinkSound: return new plWin32LinkSound();
        //case kLayerLinkAnimation: return new plLayerLinkAnimation();
        //case kArmatureMod: return new plArmatureMod();
        //case kCameraBrain_Freelook: return new plCameraBrain_Freelook();
        //case kHavokConstraintsMod: return new plHavokConstraintsMod();
        //case kHingeConstraintMod: return new plHingeConstraintMod();
        //case kWheelConstraintMod: return new plWheelConstraintMod();
        //case kStrongSpringConstraintMod: return new plStrongSpringConstraintMod();
        //case kArmatureLODMod: return new plArmatureLODMod();
        //case kWin32StaticSound: return new plWin32StaticSound();
        //case kGameGUIMgr: return new pfGameGUIMgr();
        //case kGUIDialogMod: return new pfGUIDialogMod();
        //case kCameraBrain1: return new plCameraBrain1();
        //case kVirtualCam1: return new plVirtualCam1();
        //case kCameraModifier1: return new plCameraModifier1();
        //case kCameraBrain1_Drive: return new plCameraBrain1_Drive();
        //case kCameraBrain1_POA: return new plCameraBrain1_POA();
        //case kCameraBrain1_Avatar: return new plCameraBrain1_Avatar();
        //case kCameraBrain1_Fixed: return new plCameraBrain1_Fixed();
        //case kCameraBrain1_POAFixed: return new plCameraBrain1_POAFixed();
        //case kGUIButtonMod: return new pfGUIButtonMod();
        case kPythonFileMod: return new plPythonFileMod();
        //case kGUIControlMod: return new pfGUIControlMod();
        //case kExcludeRegionModifier: return new plExcludeRegionModifier();
        //case kGUIDraggableMod: return new pfGUIDraggableMod();
        //case kVolumeSensorConditionalObject: return new plVolumeSensorConditionalObject();
        //case kVolActivatorConditionalObject: return new plVolActivatorConditionalObject();
        //case kMsgForwarder: return new plMsgForwarder();
        //case kBlower: return new plBlower();
        //case kGUIListBoxMod: return new pfGUIListBoxMod();
        //case kGUITextBoxMod: return new pfGUITextBoxMod();
        //case kGUIEditBoxMod: return new pfGUIEditBoxMod();
        //case kDynamicTextMap: return new plDynamicTextMap();
        //case kSittingModifier: return new plSittingModifier();
        //case kGUIUpDownPairMod: return new pfGUIUpDownPairMod();
        //case kGUIValueCtrl: return new pfGUIValueCtrl();
        //case kGUIKnobCtrl: return new pfGUIKnobCtrl();
        //case kAvLadderMod: return new plAvLadderMod();
        //case kCameraBrain1_FirstPerson: return new plCameraBrain1_FirstPerson();
        //case kCloneSpawnModifier: return new plCloneSpawnModifier();
        case kClothingItem: return new plClothingItem();
        //case kClothingOutfit: return new plClothingOutfit();
        //case kClothingBase: return new plClothingBase();
        //case kClothingMgr: return new plClothingMgr();
        //case kGUIDragBarCtrl: return new pfGUIDragBarCtrl();
        //case kGUICheckBoxCtrl: return new pfGUICheckBoxCtrl();
        //case kGUIRadioGroupCtrl: return new pfGUIRadioGroupCtrl();
        //case kPlayerBookMod: return new pfPlayerBookMod();
        //case kGUIDynDisplayCtrl: return new pfGUIDynDisplayCtrl();
        //case kLayerProject: return new plLayerProject();
        //case kInputInterfaceMgr: return new plInputInterfaceMgr();
        //case kRailCameraMod: return new plRailCameraMod();
        //case kMultistageBehMod: return new plMultistageBehMod();
        //case kCameraBrain1_Circle: return new plCameraBrain1_Circle();
        //case kParticleWindEffect: return new plParticleWindEffect();
        //case kAnimEventModifier: return new plAnimEventModifier();
        //case kAutoProfile: return new plAutoProfile();
        //case kGUISkin: return new pfGUISkin();
        //case kAVIWriter: return new plAVIWriter();
        //case kParticleCollisionEffect: return new plParticleCollisionEffect();
        //case kParticleCollisionEffectDie: return new plParticleCollisionEffectDie();
        //case kParticleCollisionEffectBounce: return new plParticleCollisionEffectBounce();
        //case kInterfaceInfoModifier: return new plInterfaceInfoModifier();
        //case kSharedMesh: return new plSharedMesh();
        //case kArmatureEffectsMgr: return new plArmatureEffectsMgr();
        //case kMarkerMgr: return new pfMarkerMgr();
        //case kVehicleModifier: return new plVehicleModifier();
        //case kParticleLocalWind: return new plParticleLocalWind();
        //case kParticleUniformWind: return new plParticleUniformWind();
        //case kInstanceDrawInterface: return new plInstanceDrawInterface();
        //case kShadowMaster: return new plShadowMaster();
        //case kShadowCaster: return new plShadowCaster();
        //case kPointShadowMaster: return new plPointShadowMaster();
        //case kDirectShadowMaster: return new plDirectShadowMaster();
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
        //case kHKSubWorld: return new plHKSubWorld();
        //case kArmatureEffect: return new plArmatureEffect();
        //case kAmratureEffectFootSound: return new plAmratureEffectFootSound();
        //case kEAXListenerMod: return new plEAXListenerMod();
        //case kDynaDecalMgr: return new plDynaDecalMgr();
        //case kObjectInVolumeAndFacingDetector: return new plObjectInVolumeAndFacingDetector();
        //case kDynaFootMgr: return new plDynaFootMgr();
        //case kDynaRippleMgr: return new plDynaRippleMgr();
        //case kDynaBulletMgr: return new plDynaBulletMgr();
        //case kDecalEnableMod: return new plDecalEnableMod();
        //case kPrintShape: return new plPrintShape();
        //case kDynaPuddleMgr: return new plDynaPuddleMgr();
        //case kGUIMultiLineEditCtrl: return new pfGUIMultiLineEditCtrl();
        //case kLayerAnimationBase: return new plLayerAnimationBase();
        //case kLayerSDLAnimation: return new plLayerSDLAnimation();
        //case kATCAnim: return new plATCAnim();
        //case kAgeGlobalAnim: return new plAgeGlobalAnim();
        //case kSubworldRegionDetector: return new plSubworldRegionDetector();
        //case kAvatarMgr: return new plAvatarMgr();
        //case kNPCSpawnMod: return new plNPCSpawnMod();
        //case kActivePrintShape: return new plActivePrintShape();
        //case kExcludeRegionSDLModifier: return new plExcludeRegionSDLModifier();
        //case kLOSDispatch: return new plLOSDispatch();
        //case kDynaWakeMgr: return new plDynaWakeMgr();
        //case kSimulationMgr: return new plSimulationMgr();
        //case kWaveSet7: return new plWaveSet7();
        //case kPanicLinkRegion: return new plPanicLinkRegion();
        //case kWin32GroupedSound: return new plWin32GroupedSound();
        //case kFilterCoordInterface: return new plFilterCoordInterface();
        //case kStereizer: return new plStereizer();
        //case kCCRMgr: return new plCCRMgr();
        //case kCCRSpecialist: return new plCCRSpecialist();
        //case kCCRSeniorSpecialist: return new plCCRSeniorSpecialist();
        //case kCCRShiftSupervisor: return new plCCRShiftSupervisor();
        //case kCCRGameOperator: return new plCCRGameOperator();
        //case kShader: return new plShader();
        //case kDynamicEnvMap: return new plDynamicEnvMap();
        //case kSimpleRegionSensor: return new plSimpleRegionSensor();
        //case kMorphSequence: return new plMorphSequence();
        //case kEmoteAnim: return new plEmoteAnim();
        //case kDynaRippleVSMgr: return new plDynaRippleVSMgr();
        //case kWaveSet6: return new plWaveSet6();
        //case kGUIProgressCtrl: return new pfGUIProgressCtrl();
        //case kMaintainersMarkerModifier: return new plMaintainersMarkerModifier();
        //case kMorphSequenceSDLMod: return new plMorphSequenceSDLMod();
        //case kMorphDataSet: return new plMorphDataSet();
        //case kHardRegion: return new plHardRegion();
        //case kHardRegionPlanes: return new plHardRegionPlanes();
        //case kHardRegionComplex: return new plHardRegionComplex();
        //case kHardRegionUnion: return new plHardRegionUnion();
        //case kHardRegionIntersect: return new plHardRegionIntersect();
        //case kHardRegionInvert: return new plHardRegionInvert();
        //case kVisRegion: return new plVisRegion();
        //case kVisRegion: return new plVisRegion();
        //case kRegionBase: return new plRegionBase();
        //case kGUIPopUpMenu: return new pfGUIPopUpMenu();
        //case kGUIMenuItem: return new pfGUIMenuItem();
        //case kCoopCoordinator: return new plCoopCoordinator();
        case kFont: return new plFont();
        //case kFontCache: return new plFontCache();
        //case kRelevanceRegion: return new plRelevanceRegion();
        //case kRelevanceMgr: return new plRelevanceMgr();
        //case kJournalBook: return new pfJournalBook();
        //case kLayerTargetContainer: return new plLayerTargetContainer();
        case kImageLibMod: return new plImageLibMod();
        //case kParticleFlockEffect: return new plParticleFlockEffect();
        //case kParticleSDLMod: return new plParticleSDLMod();
        //case kAgeLoader: return new plAgeLoader();;
        //case kWaveSetBase: return new plWaveSetBase();
        //case kPhysicalSndGroup: return new plPhysicalSndGroup();
        //case kBookData: return new pfBookData();
        //case kDynaTorpedoMgr: return new plDynaTorpedoMgr();
        //case kDynaTorpedoVSMgr: return new plDynaTorpedoVSMgr();
        //case kClusterGroup: return new plClusterGroup();
        //case kGameMarkerModifier: return new plGameMarkerModifier();
        //case kLODMipmap: return new plLODMipmap();
        //case kSwimDetector: return new plSwimDetector();
        //case kFadeOpacityMod: return new plFadeOpacityMod();
        //case kFadeOpacityLay: return new plFadeOpacityLay();
        //case kDistOpacityMod: return new plDistOpacityMod();
        //case kArmatureModBase: return new plArmatureModBase();
        //case kSwimRegionInterface: return new plSwimRegionInterface();
        //case kSwimCircularCurrentRegion: return new plSwimCircularCurrentRegion();
        //case kParticleFollowSystemEffect: return new plParticleFollowSystemEffect();
        //case kSwimStraightCurrentRegion: return new plSwimStraightCurrentRegion();
        //case kObjectFlocker: return new pfObjectFlocker();
        //case kGrassShaderMod: return new plGrassShaderMod();
        //case kDynamicCamMap: return new plDynamicCamMap();
        //case kSwimRegion: return new plSwimRegion();
        //case kPXPhysical: return new plPXPhysical();
        //case kODEPhysical: return new plODEPhysical();
        //case kAutoWalkRegion: return new plAutoWalkRegion();
        //case kCrossfade: return new plCrossfade();
        //case kParticleFadeOutEffect: return new plParticleFadeOutEffect();
        //case kSecurePreloader: return new pfSecurePreloader();
        //case kWindBoneMod: return new plWindBoneMod();
        //case kCameraBrain_NovicePlus: return new plCameraBrain_NovicePlus();
        //case kSubtitleMgr: return new pfSubtitleMgr();
        //case kPythonFileModConditionalObject: return new plPythonFileModConditionalObject();
        //case kLayerTransform: return new plLayerTransform();
        //case kBubbleShaderMod: return new plBubbleShaderMod();
        //case kLineFollowModBase: return new plLineFollowModBase();
        //case kClientApp: return new plClientApp();
        //case kGUICreditsCtrl: return new pfGUICreditsCtrl();
        //case kCameraBrainUru: return new plCameraBrainUru();
        //case kVirtualCamera: return new plVirtualCamera();
        //case kCameraBrainUru_Drive: return new plCameraBrainUru_Drive();
        //case kCameraBrainUru_Follow: return new plCameraBrainUru_Follow();
        //case kCameraBrainUru_Fixed: return new plCameraBrainUru_Fixed();
        //case kGUISketchCtrl: return new pfGUISketchCtrl();
        //case kLadderModifier: return new plLadderModifier();
        //case kCameraBrainUru_FirstPerson: return new plCameraBrainUru_FirstPerson();
        //case kCameraBrainUru_Circle: return new plCameraBrainUru_Circle();
        //case kEAXReverbEffect: return new plEAXReverbEffect();
        //case kSpawnMod: return new plSpawnMod();
        //case kCameraBrain_Novice: return new plCameraBrain_Novice();
        //case kAvatarPhysicalSDLModifier: return new plAvatarPhysicalSDLModifier();
        //case kDirectMusicSound: return new plDirectMusicSound();
        //case kClientSessionMgr: return new plClientSessionMgr();
        //case kSDLVarChangeNotifier: return new plSDLVarChangeNotifier();
        //case kInterestWellModifier: return new plInterestWellModifier();
        //case kElevatorModifier: return new plElevatorModifier();
        //case kCameraBrain_Expert: return new plCameraBrain_Expert();
        //case kPagingRegionModifier: return new plPagingRegionModifier();
        //case kGuidepathModifier: return new plGuidepathModifier();
        //case kNodeMgr: return new pfNodeMgr();
        //case kEAXEffect: return new plEAXEffect();
        //case kEAXPitchShifter: return new plEAXPitchShifter();
        //case kIKModifier: return new plIKModifier();
        //case kCameraBrain_M5: return new plCameraBrain_M5();
        //case kAGAnimBink: return new plAGAnimBink();
        //case kTreeShader: return new plTreeShader();
        //case kNodeRegionModifier: return new plNodeRegionModifier();
        //case kPiranhaRegionModifier: return new plPiranhaRegionModifier();
        default: return NULL;
    }
}

plCreatable* plFactory::Create(short typeIdx, PlasmaVer ver) {
    if (ver == pvUnknown)
        throw "Cannot create objects for unknown Plasma Versions!";
    return Create(pdUnifiedTypeMap::PlasmaToMapped(typeIdx, ver));
}

const char* plFactory::ClassName(short typeIdx) {
    return pdUnifiedTypeMap::ClassName(typeIdx);
}

const char* plFactory::ClassName(short typeIdx, PlasmaVer ver) {
    return pdUnifiedTypeMap::ClassName(typeIdx, ver);
}
