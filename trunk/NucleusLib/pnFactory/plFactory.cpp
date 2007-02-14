#include "plFactory.h"

plFactory::plFactory() : ver(pvUnknown) { }
plFactory::plFactory(PlasmaVer pv) : ver(pv) { }
plFactory::~plFactory() { }

PlasmaVer plFactory::getVer() { return ver; }
void plFactory::setVer(PlasmaVer pv, bool mutate) { ver = pv; }

// Includes for all plCreatable types
#include "../../PubUtilLib/plScene/plSceneNode.h"
#include "../pnSceneObject/plSceneObject.h"
//#include "../pnKeyedObject/hsKeyedObject.h"
#include "../../PubUtilLib/plGImage/plBitmap.h"
#include "../../PubUtilLib/plGImage/plMipmap.h"
#include "../../PubUtilLib/plGImage/plCubicEnvironmap.h"
#include "../../PubUtilLib/plSurface/hsGMaterial.h"
#include "../pnSceneObject/plObjInterface.h"
#include "../pnSceneObject/plAudioInterface.h"
#include "../pnSceneObject/plCoordinateInterface.h"
#include "../pnSceneObject/plDrawInterface.h"
#include "../pnSceneObject/plSimulationInterface.h"
#include "../pnModifier/plModifier.h"
#include "../pnNetCommon/plSynchedObject.h"
#include "../../PubUtilLib/plSurface/plLayerInterface.h"
#include "../../PubUtilLib/plDrawable/plDrawableSpans.h"
#include "../../PubUtilLib/plPipeline/plFogEnvironment.h"
#include "../../PubUtilLib/plGLight/plLightInfo.h"
#include "../../FeatureLib/pfPython/plPythonFileMod.h"
#include "../../PubUtilLib/plAvatar/plClothingItem.h"
#include "../../PubUtilLib/plGImage/plFont.h"
// End types

plCreatable* plFactory::Create(short typeIdx, PlasmaVer ver) {
    if (ver == pvPrime || ver == pvPots || ver == pvLive) {
        if (typeIdx < 0x0200) {
            switch(typeIdx) {
            // 0x0000 - 0x01FF //
            case 0x0000: return new plSceneNode(ver);
            case 0x0001: return new plSceneObject(ver);
            case 0x0002: return new hsKeyedObject(ver);
            case 0x0003: return new plBitmap(ver);
            case 0x0004: return new plMipmap(ver);
            case 0x0005: return new plCubicEnvironmap(ver);
            //case 0x0006: return new plLayer(ver);
            case 0x0007: return new hsGMaterial(ver);
            //case 0x0008: return new plParticleSystem(ver);
            //case 0x0009: return new plParticleEffect(ver);
            //case 0x000A: return new plParticleCollisionEffectBeat(ver);
            //case 0x000B: return new plParticleFadeVolumeEffect(ver);
            //case 0x000C: return new plBoundInterface(ver);
            //case 0x000D: return new plRenderTarget(ver);
            //case 0x000E: return new plCubicRenderTarget(ver);
            //case 0x000F: return new plCubicRenderTargetModifier(ver);
            case 0x0010: return new plObjInterface(ver);
            case 0x0011: return new plAudioInterface(ver);
            //case 0x0012: return new plAudible(ver);
            //case 0x0013: return new plAudibleNull(ver);
            //case 0x0014: return new plWinAudible(ver);
            case 0x0015: return new plCoordinateInterface(ver);
            case 0x0016: return new plDrawInterface(ver);
            case 0x0017: return new plDrawable(ver);
            //case 0x0018: return new plDrawableMesh(ver);
            //case 0x0019: return new plDrawableIce(ver);
            //case 0x001A: return new plPhysical(ver);
            //case 0x001B: return new plPhysicalMesh(ver);
            case 0x001C: return new plSimulationInterface(ver);
            //case 0x001D: return new plCameraModifier(ver);
            case 0x001E: return new plModifier(ver);
            //case 0x001F: return new plSingleModifier(ver);
            //case 0x0020: return new plSimpleModifier(ver);
            //case 0x0021: return new plSimpleTMModifier(ver);
            //case 0x0022: return new plRandomTMModifier(ver);
            //case 0x0023: return new plInterestingModifier(ver);
            //case 0x0024: return new plDetectorModifier(ver);
            //case 0x0025: return new plSimplePhysicalMesh(ver);
            //case 0x0026: return new plCompoundPhysicalMesh(ver);
            case 0x0027: return new plMultiModifier(ver);
            case 0x0028: return new plSynchedObject(ver);
            //case 0x0029: return new plSoundBuffer(ver);
            //case 0x002A: return new plAliasModifier(ver);
            //case 0x002B: return new plPickingDetector(ver);
            //case 0x002C: return new plCollisionDetector(ver);
            //case 0x002D: return new plLogicModifier(ver);
            //case 0x002E: return new plConditionalObject(ver);
            //case 0x002F: return new plANDConditionalObject(ver);
            //case 0x0030: return new plORConditionalObject(ver);
            //case 0x0031: return new plPickedConditionalObject(ver);
            //case 0x0032: return new plActivatorConditionalObject(ver);
            //case 0x0033: return new plTimerCallbackManager(ver);
            //case 0x0034: return new plKeyPressConditionalObject(ver);
            //case 0x0035: return new plAnimationEventConditionalObject(ver);
            //case 0x0036: return new plControlEventConditionalObject(ver);
            //case 0x0037: return new plObjectInBoxConditionalObject(ver);
            //case 0x0038: return new plLocalPlayerInBoxConditioinalObject(ver);
            //case 0x0039: return new plObjectIntersectPlaneConditionalObject(ver);
            //case 0x003A: return new plLocalPlayerIntersectPlaneConditionalO(ver);
            //case 0x003B: return new plPortalDrawable(ver);
            //case 0x003C: return new plPortalPhysical(ver);
            //case 0x003D: return new plSpawnModifier(ver);
            //case 0x003E: return new plFacingConditionalObject(ver);
            //case 0x003F:
            //    switch(ver) {
            //    case pvPrime: return new plHKPhysical(ver);
            //    case pvPots:  return new plHKPhysical(ver);
            //    case pvLive:  return new plPXPhysical(ver);
            //    } return NULL;
            //case 0x0040: return new plViewFaceModifier(ver);
            case 0x0041: return new plLayerInterface(ver);
            //case 0x0042: return new plLayerWrapper(ver);
            //case 0x0043: return new plLayerAnimation(ver);
            //case 0x0044: return new plLayerDepth(ver);
            //case 0x0045: return new plLayerMovie(ver);
            //case 0x0046: return new plLayerBink(ver);
            //case 0x0047: return new plLayerAVI(ver);
            //case 0x0048: return new plSound(ver);
            //case 0x0049: return new plWin32Sound(ver);
            //case 0x004A: return new plLayerOr(ver);
            //case 0x004B: return new plAudioSystem(ver);
            case 0x004C: return new plDrawableSpans(ver);
            //case 0x004D: return new plDrawablePatchSet(ver);
            //case 0x004E: return new plInputManager(ver);
            //case 0x004F: return new plLogicModBase(ver);
            case 0x0050: return new plFogEnvironment(ver);
            //case 0x0051: return new plNetApp(ver);
            //case 0x0052: return new plNetClientMgr(ver);
            //case 0x0053: return new pl2WayWinAudible(ver);
            case 0x0054: return new plLightInfo(ver);
            //case 0x0055: return new plDirectionalLightInfo(ver);
            //case 0x0056: return new plOmniLightInfo(ver);
            //case 0x0057: return new plSpotLightInfo(ver);
            //case 0x0058: return new plLightSpace(ver);
            //case 0x0059: return new plNetClientApp(ver);
            //case 0x005A: return new plNetServerApp(ver);
            //case 0x005B: return new plClient(ver);
            //case 0x005C: return new plCompoundTMModifier(ver);
            //case 0x005D: return new plCameraBrain(ver);
            //case 0x005E: return new plCameraBrain_Default(ver);
            //case 0x005F: return new plCameraBrain_Drive(ver);
            //case 0x0060: return new plCameraBrain_Fixed(ver);
            //case 0x0061: return new plCameraBrain_FixedPan(ver);
            //case 0x0062: return new pfGUIClickMapCtrl(ver);
            //case 0x0063: return new plListener(ver);
            //case 0x0064: return new plAvatarMod(ver);
            //case 0x0065: return new plAvatarAnim(ver);
            //case 0x0066: return new plAvatarAnimMgr(ver);
            //case 0x0067: return new plOccluder(ver);
            //case 0x0068: return new plMobileOccluder(ver);
            //case 0x0069: return new plLayerShadowBase(ver);
            //case 0x006A: return new plLimitedDirLightInfo(ver);
            //case 0x006B: return new plAGAnim(ver);
            //case 0x006C: return new plAGModifier(ver);
            //case 0x006D: return new plAGMasterMod(ver);
            //case 0x006E: return new plCameraBrain_Avatar(ver);
            //case 0x006F: return new plCameraRegionDetector(ver);
            //case 0x0070: return new plCameraBrain_FP(ver);
            //case 0x0071: return new plLineFollowMod(ver);
            //case 0x0072: return new plLightModifier(ver);
            //case 0x0073: return new plOmniModifier(ver);
            //case 0x0074: return new plSpotModifier(ver);
            //case 0x0075: return new plLtdDirModifier(ver);
            //case 0x0076: return new plSeekPointMod(ver);
            //case 0x0077: return new plOneShotMod(ver);
            //case 0x0078: return new plRandomCommandMod(ver);
            //case 0x0079: return new plRandomSoundMod(ver);
            //case 0x007A: return new plPostEffectMod(ver);
            //case 0x007B: return new plObjectInVolumeDetector(ver);
            //case 0x007C: return new plResponderModifier(ver);
            //case 0x007D: return new plAxisAnimModifier(ver);
            //case 0x007E: return new plLayerLightBase(ver);
            //case 0x007F: return new plFollowMod(ver);
            //case 0x0080: return new plTransitionMgr(ver);
            //case 0x0081: return new plInventoryMod(ver);
            //case 0x0082: return new plInventoryObjMod(ver);
            //case 0x0083: return new plLinkEffectsMgr(ver);
            //case 0x0084: return new plWin32StreamingSound(ver);
            //case 0x0085: return new plPythonMod(ver);
            //case 0x0086: return new plActivatorActivatorConditionalObject(ver);
            //case 0x0087: return new plSoftVolume(ver);
            //case 0x0088: return new plSoftVolumeSimple(ver);
            //case 0x0089: return new plSoftVolumeComplex(ver);
            //case 0x008A: return new plSoftVolumeUnion(ver);
            //case 0x008B: return new plSoftVolumeIntersect(ver);
            //case 0x008C: return new plSoftVolumeInvert(ver);
            //case 0x008D: return new plWin32LinkSound(ver);
            //case 0x008E: return new plLayerLinkAnimation(ver);
            //case 0x008F: return new plArmatureMod(ver);
            //case 0x0090: return new plCameraBrain_Freelook(ver);
            //case 0x0091: return new plHavokConstraintsMod(ver);
            //case 0x0092: return new plHingeConstraintMod(ver);
            //case 0x0093: return new plWheelConstraintMod(ver);
            //case 0x0094: return new plStrongSpringConstraintMod(ver);
            //case 0x0095: return new plArmatureLODMod(ver);
            //case 0x0096: return new plWin32StaticSound(ver);
            //case 0x0097: return new pfGameGUIMgr(ver);
            //case 0x0098: return new pfGUIDialogMod(ver);
            //case 0x0099: return new plCameraBrain1(ver);
            //case 0x009A: return new plVirtualCam1(ver);
            //case 0x009B: return new plCameraModifier1(ver);
            //case 0x009C: return new plCameraBrain1_Drive(ver);
            //case 0x009D: return new plCameraBrain1_POA(ver);
            //case 0x009E: return new plCameraBrain1_Avatar(ver);
            //case 0x009F: return new plCameraBrain1_Fixed(ver);
            //case 0x00A0: return new plCameraBrain1_POAFixed(ver);
            //case 0x00A1: return new pfGUIButtonMod(ver);
            case 0x00A2: return new plPythonFileMod(ver);
            //case 0x00A3: return new pfGUIControlMod(ver);
            //case 0x00A4: return new plExcludeRegionModifier(ver);
            //case 0x00A5: return new pfGUIDraggableMod(ver);
            //case 0x00A6: return new plVolumeSensorConditionalObject(ver);
            //case 0x00A7: return new plVolActivatorConditionalObject(ver);
            //case 0x00A8: return new plMsgForwarder(ver);
            //case 0x00A9: return new plBlower(ver);
            //case 0x00AA: return new pfGUIListBoxMod(ver);
            //case 0x00AB: return new pfGUITextBoxMod(ver);
            //case 0x00AC: return new pfGUIEditBoxMod(ver);
            //case 0x00AD: return new plDynamicTextMap(ver);
            //case 0x00AE: return new plSittingModifier(ver);
            //case 0x00AF: return new pfGUIUpDownPairMod(ver);
            //case 0x00B0: return new pfGUIValueCtrl(ver);
            //case 0x00B1: return new pfGUIKnobCtrl(ver);
            //case 0x00B2: return new plAvLadderMod(ver);
            //case 0x00B3: return new plCameraBrain1_FirstPerson(ver);
            //case 0x00B4: return new plCloneSpawnModifier(ver);
            case 0x00B5: return new plClothingItem(ver);
            //case 0x00B6: return new plClothingOutfit(ver);
            //case 0x00B7: return new plClothingBase(ver);
            //case 0x00B8: return new plClothingMgr(ver);
            //case 0x00B9: return new pfGUIDragBarCtrl(ver);
            //case 0x00BA: return new pfGUICheckBoxCtrl(ver);
            //case 0x00BB: return new pfGUIRadioGroupCtrl(ver);
            //case 0x00BC: return new pfPlayerBookMod(ver);
            //case 0x00BD: return new pfGUIDynDisplayCtrl(ver);
            //case 0x00BE: return new plLayerProject(ver);
            //case 0x00BF: return new plInputInterfaceMgr(ver);
            //case 0x00C0: return new plRailCameraMod(ver);
            //case 0x00C1: return new plMultistageBehMod(ver);
            //case 0x00C2: return new plCameraBrain1_Circle(ver);
            //case 0x00C3: return new plParticleWindEffect(ver);
            //case 0x00C4: return new plAnimEventModifier(ver);
            //case 0x00C5: return new plAutoProfile(ver);
            //case 0x00C6: return new pfGUISkin(ver);
            //case 0x00C7: return new plAVIWriter(ver);
            //case 0x00C8: return new plParticleCollisionEffect(ver);
            //case 0x00C9: return new plParticleCollisionEffectDie(ver);
            //case 0x00CA: return new plParticleCollisionEffectBounce(ver);
            //case 0x00CB: return new plInterfaceInfoModifier(ver);
            //case 0x00CC: return new plSharedMesh(ver);
            //case 0x00CD: return new plArmatureEffectsMgr(ver);
            //case 0x00CE: return new pfMarkerMgr(ver);
            //case 0x00CF: return new plVehicleModifier(ver);
            //case 0x00D0: return new plParticleLocalWind(ver);
            //case 0x00D1: return new plParticleUniformWind(ver);
            //case 0x00D2: return new plInstanceDrawInterface(ver);
            //case 0x00D3: return new plShadowMaster(ver);
            //case 0x00D4: return new plShadowCaster(ver);
            //case 0x00D5: return new plPointShadowMaster(ver);
            //case 0x00D6: return new plDirectShadowMaster(ver);
            //case 0x00D7: return new plSDLModifier(ver);
            //case 0x00D8: return new plPhysicalSDLModifier(ver);
            //case 0x00D9: return new plClothingSDLModifier(ver);
            //case 0x00DA: return new plAvatarSDLModifier(ver);
            //case 0x00DB: return new plAGMasterSDLModifier(ver);
            //case 0x00DC: return new plPythonSDLModifier(ver);
            //case 0x00DD: return new plLayerSDLModifier(ver);
            //case 0x00DE: return new plAnimTimeConvertSDLModifier(ver);
            //case 0x00DF: return new plResponderSDLModifier(ver);
            //case 0x00E0: return new plSoundSDLModifier(ver);
            //case 0x00E1: return new plResManagerHelper(ver);
            //case 0x00E2:
            //    switch(ver):
            //    case pvPrime: return new plHKSubWorld(ver);
            //    case pvPots:  return new plHKSubWorld(ver);
            //    case pvLive:  return new plAvatarPhysicalSDLModifier(ver);
            //    } return NULL;
            //case 0x00E3: return new plArmatureEffect(ver);
            //case 0x00E4: return new plAmratureEffectFootSound(ver);
            //case 0x00E5: return new plEAXListenerMod(ver);
            //case 0x00E6: return new plDynaDecalMgr(ver);
            //case 0x00E7: return new plObjectInVolumeAndFacingDetector(ver);
            //case 0x00E8: return new plDynaFootMgr(ver);
            //case 0x00E9: return new plDynaRippleMgr(ver);
            //case 0x00EA: return new plDynaBulletMgr(ver);
            //case 0x00EB: return new plDecalEnableMod(ver);
            //case 0x00EC: return new plPrintShape(ver);
            //case 0x00ED: return new plDynaPuddleMgr(ver);
            //case 0x00EE: return new pfGUIMultiLineEditCtrl(ver);
            //case 0x00EF: return new plLayerAnimationBase(ver);
            //case 0x00F0: return new plLayerSDLAnimation(ver);
            //case 0x00F1: return new plATCAnim(ver);
            //case 0x00F2: return new plAgeGlobalAnim(ver);
            //case 0x00F3: return new plSubworldRegionDetector(ver);
            //case 0x00F4: return new plAvatarMgr(ver);
            //case 0x00F5: return new plNPCSpawnMod(ver);
            //case 0x00F6: return new plActivePrintShape(ver);
            //case 0x00F7: return new plExcludeRegionSDLModifier(ver);
            //case 0x00F8: return new plLOSDispatch(ver);
            //case 0x00F9: return new plDynaWakeMgr(ver);
            //case 0x00FA: return new plSimulationMgr(ver);
            //case 0x00FB: return new plWaveSet7(ver);
            //case 0x00FC: return new plPanicLinkRegion(ver);
            //case 0x00FD: return new plWin32GroupedSound(ver);
            //case 0x00FE: return new plFilterCoordInterface(ver);
            //case 0x00FF: return new plStereizer(ver);
            //case 0x0100: return new plCCRMgr(ver);
            //case 0x0101: return new plCCRSpecialist(ver);
            //case 0x0102: return new plCCRSeniorSpecialist(ver);
            //case 0x0103: return new plCCRShiftSupervisor(ver);
            //case 0x0104: return new plCCRGameOperator(ver);
            //case 0x0105: return new plShader(ver);
            //case 0x0106: return new plDynamicEnvMap(ver);
            //case 0x0107: return new plSimpleRegionSensor(ver);
            //case 0x0108: return new plMorphSequence(ver);
            //case 0x0109: return new plEmoteAnim(ver);
            //case 0x010A: return new plDynaRippleVSMgr(ver);
            //case 0x010B: return new plWaveSet6(ver);
            //case 0x010C: return new pfGUIProgressCtrl(ver);
            //case 0x010D: return new plMaintainersMarkerModifier(ver);
            //case 0x010E: return new plMorphSequenceSDLMod(ver);
            //case 0x010F: return new plMorphDataSet(ver);
            //case 0x0110: return new plHardRegion(ver);
            //case 0x0111: return new plHardRegionPlanes(ver);
            //case 0x0112: return new plHardRegionComplex(ver);
            //case 0x0113: return new plHardRegionUnion(ver);
            //case 0x0114: return new plHardRegionIntersect(ver);
            //case 0x0115: return new plHardRegionInvert(ver);
            //case 0x0116: return new plVisRegion(ver);
            //case 0x0117: return new plVisRegion(ver);
            //case 0x0118: return new plRegionBase(ver);
            //case 0x0119: return new pfGUIPopUpMenu(ver);
            //case 0x011A: return new pfGUIMenuItem(ver);
            //case 0x011B: return new plCoopCoordinator(ver);
            case 0x011C: return new plFont(ver);
            //case 0x011D: return new plFontCache(ver);
            //case 0x011E: return new plRelevanceRegion(ver);
            //case 0x011F: return new plRelevanceMgr(ver);
            //case 0x0120: return new pfJournalBook(ver);
            //case 0x0121: return new plLayerTargetContainer(ver);
            //case 0x0122: return new plImageLibMod(ver);
            //case 0x0123: return new plParticleFlockEffect(ver);
            //case 0x0124: return new plParticleSDLMod(ver);
            //case 0x0125: return new plAgeLoader(ver);;
            //case 0x0126: return new plWaveSetBase(ver);
            //case 0x0127: return new plPhysicalSndGroup(ver);
            //case 0x0128: return new pfBookData(ver);
            //case 0x0129: return new plDynaTorpedoMgr(ver);
            //case 0x012A: return new plDynaTorpedoVSMgr(ver);
            //case 0x012B: return new plClusterGroup(ver);
            //case 0x012C: return new plGameMarkerModifier(ver);
            //case 0x012D: return new plLODMipmap(ver);
            //case 0x012E:
            //    switch(ver) {
            //    case pvPrime: return new plSwimRegion(ver);
            //    case pvPots:  return new plSwimDetector(ver);
            //    case pvLive:  return new plSwimDetector(ver);
            //    } return NULL;
            //case 0x012F:
            //    switch(ver) {
            //    case pvPrime: return NULL;
            //    case pvPots:  return new plFadeOpacityMod(ver);
            //    case pvLive:  return new plFadeOpacityMod(ver);
            //    } return NULL;
            //case 0x0130:
            //    switch(ver) {
            //    case pvPrime: return NULL;
            //    case pvPots:  return new plFadeOpacityLay(ver);
            //    case pvLive:  return new plFadeOpacityLay(ver);
            //    } return NULL;
            //case 0x0131:
            //    switch(ver) {
            //    case pvPrime: return NULL;
            //    case pvPots:  return new plDistOpacityMod(ver);
            //    case pvLive:  return new plDistOpacityMod(ver);
            //    } return NULL;
            //case 0x0132:
            //    switch(ver) {
            //    case pvPrime: return NULL;
            //    case pvPots:  return new plArmatureModBase(ver);
            //    case pvLive:  return new plArmatureModBase(ver);
            //    } return NULL;
            //case 0x0133:
            //    switch(ver) {
            //    case pvPrime: return NULL;
            //    case pvPots:  return new plSwimRegionInterface(ver);
            //    case pvLive:  return new plSwimRegionInterface(ver);
            //    } return NULL;
            //case 0x0134:
            //    switch(ver) {
            //    case pvPrime: return NULL;
            //    case pvPots:  return new plSwimCircularCurrentRegion(ver);
            //    case pvLive:  return new plSwimCircularCurrentRegion(ver);
            //    } return NULL;
            //case 0x0135:
            //    switch(ver) {
            //    case pvPrime: return NULL;
            //    case pvPots:  return new plParticleFollowSystemEffect(ver);
            //    case pvLive:  return new plParticleFollowSystemEffect(ver);
            //    } return NULL;
            //case 0x0136:
            //    switch(ver) {
            //    case pvPrime: return NULL;
            //    case pvPots:  return new plSwimStraightCurrentRegion(ver);
            //    case pvLive:  return new plSwimStraightCurrentRegion(ver);
            //    } return NULL;
            //case 0x0137:
            //    switch(ver) {
            //    case pvPrime: return NULL;
            //    case pvPots:  return NULL;
            //    case pvLive:  return new pfObjectFlocker(ver);
            //    } return NULL;
            //case 0x0138:
            //    switch(ver) {
            //    case pvPrime: return NULL;
            //    case pvPots:  return NULL;
            //    case pvLive:  return new plGrassShaderMod(ver);
            //    } return NULL;
            //case 0x0139:
            //    switch(ver) {
            //    case pvPrime: return NULL;
            //    case pvPots:  return NULL;
            //    case pvLive:  return new plDynamicCamMap(ver);
            //    } return NULL;
            default:     return NULL;
            }
        } else if (ver == pvPrime || ver == pvPots) {
            if (ver == pvPots && typeIdx > 0x0400) typeIdx--;
            switch (typeIdx) {
            // 0x0200 - 0x03FF //
            //case 0x0200: return new plObjRefMsg(ver);

            // 0x0400 - 0x05FF //
            //case 0x0421: return new plVaultGameServerInitializationTask(ver);
            default:     return NULL;
            }
        } else {
            switch(typeIdx) {
            // 0x0200 - 0x03FF //
            //case 0x0200: return new plObjRefMsg(ver);

            // 0x0400 - 0x05FF //
            //case 0x0427: return new plVaultGameServerInitializationTask(ver);
            default:     return NULL;
            }
        }
    } else if (ver == pvEoa) {
        switch(typeIdx) {
        // 0x0000 - 0x01FF //
        case 0x0000: return new plSceneNode(ver);
        case 0x0001: return new plSceneObject(ver);
        case 0x0002: return new hsKeyedObject(ver);
        case 0x0003: return new plBitmap(ver);
        case 0x0004: return new plMipmap(ver);
        case 0x0005: return new plCubicEnvironmap(ver);
        //case 0x0006: return new plLayer(ver);
        case 0x0007: return new hsGMaterial(ver);
        //case 0x0008: return new plParticleSystem(ver);
        //case 0x0009: return new plParticleEffect(ver);
        //case 0x000A: return new plParticleCollisionEffectBeat(ver);
        //case 0x000B: return new plParticleFadeVolumeEffect(ver);
        //case 0x000C: return new plBoundInterface(ver);
        //case 0x000D: return new plRenderTarget(ver);
        //case 0x000E: return new plCubicRenderTarget(ver);
        //case 0x000F: return new plCubicRenderTargetModifier(ver);
        case 0x0010: return new plObjInterface(ver);
        case 0x0011: return new plAudioInterface(ver);
        //case 0x0012: return new plAudible(ver);
        //case 0x0013: return new plAudibleNull(ver);
        //case 0x0014: return new plWinAudible(ver);
        case 0x0015: return new plCoordinateInterface(ver);
        case 0x0016: return new plDrawInterface(ver);
        case 0x0017: return new plDrawable(ver);
        //case 0x0018: return new plAutoWalkRegion(ver);
        //case 0x0019: return new plDrawableIce(ver);
        //case 0x001A: return new plPhysical(ver);
        //case 0x001B: return new plCrossfade(ver);
        case 0x001C: return new plSimulationInterface(ver);
        //case 0x001D: return new plParticleFadeOutEffect(ver);
        case 0x001E: return new plModifier(ver);
        //case 0x001F: return new plSingleModifier(ver);
        //case 0x0020: return new plSimpleModifier(ver);
        //case 0x0021: return new plWindBoneMod(ver);
        //case 0x0022: return new plCameraBrain_NovicePlus(ver);
        //case 0x0023: return new plGrassShaderMod(ver);
        //case 0x0024: return new plDetectorModifier(ver);
        //case 0x0025: return new pfSubtitleMgr(ver);
        //case 0x0026: return new plPythonFileModCOnditionalObject(ver);
        case 0x0027: return new plMultiModifier(ver);
        case 0x0028: return new plSynchedObject(ver);
        //case 0x0029: return new plSoundBuffer(ver);
        //case 0x002A: return new plPickingDetector(ver);
        //case 0x002B: return new plCollisionDetector(ver);
        //case 0x002C: return new plLogicModifier(ver);
        //case 0x002D: return new plConditionalObject(ver);
        //case 0x002E: return new plANDConditionalObject(ver);
        //case 0x003F: return new plORConditionalObject(ver);
        //case 0x0030: return new plPickedConditionalObject(ver);
        //case 0x0031: return new plActivatorConditionalObject(ver);
        //case 0x0032: return new plTimerCallbackManager(ver);
        //case 0x0033: return new plKeyPressConditionalObject(ver);
        //case 0x0034: return new plAnimationEventConditionalObject(ver);
        //case 0x0035: return new plControlEventConditionalObject(ver);
        //case 0x0036: return new plObjectInBoxConditionalObject(ver);
        //case 0x0037: return new plLocalPlayerInBoxConditioinalObject(ver);
        //case 0x0038: return new plObjectIntersectPlaneConditionalObject(ver);
        //case 0x0039: return new plLocalPlayerIntersectPlaneConditionalO(ver);
        //case 0x003A: return new plLayerTransform(ver);
        //case 0x003B: return new plBubbleShaderMod(ver);
        //case 0x003C: return new plSpawnModifier(ver);
        //case 0x003D: return new plFacingConditionalObject(ver);
        //case 0x003E: return new plViewFaceModifier(ver);
        case 0x003F: return new plLayerInterface(ver);
        //case 0x0040: return new plLayerAnimation(ver);
        //case 0x0041: return new plLayerDepth(ver);
        //case 0x0042: return new plLayerMovie(ver);
        //case 0x0043: return new plLayerBink(ver);
        //case 0x0044: return new plLayerAVI(ver);
        //case 0x0045: return new plSound(ver);
        //case 0x0046: return new plWin32Sound(ver);
        //case 0x0047: return new plLayerOr(ver);
        //case 0x0048: return new plAudioSystem(ver);
        case 0x0049: return new plDrawableSpans(ver);
        //case 0x004A: return new plDrawablePatchSet(ver);
        //case 0x004B: return new plInputManager(ver);
        //case 0x004C: return new plLogicModBase(ver);
        case 0x004D: return new plFogEnvironment(ver);
        //case 0x004E: return new plLineFollowModBase(ver);
        case 0x004F: return new plLightInfo(ver);
        //case 0x0050: return new plDirectionalLightInfo(ver);
        //case 0x0051: return new plOmniLightInfo(ver);
        //case 0x0052: return new plSpotLightInfo(ver);
        //case 0x0053: return new plCameraBrain(ver);
        //case 0x0054: return new plClientApp(ver);
        //case 0x0055: return new plClient(ver);
        //case 0x0056: return new pfGUICreditsCtrl(ver);
        //case 0x0057: return new pfGUIClickMapCtrl(ver);
        //case 0x0058: return new plListener(ver);
        //case 0x0059: return new plAvatarAnim(ver);
        //case 0x005A: return new plOccluder(ver);
        //case 0x005B: return new plMobileOccluder(ver);
        //case 0x005C: return new plLayerShadowBase(ver);
        //case 0x005D: return new plLimitedDirLightInfo(ver);
        //case 0x005E: return new plAGAnim(ver);
        //case 0x005F: return new plAGModifier(ver);
        //case 0x0060: return new plAGMasterMod(ver);
        //case 0x0061: return new plCameraRegionDetector(ver);
        //case 0x0062: return new plLineFollowMod(ver);
        //case 0x0063: return new plLightModifier(ver);
        //case 0x0064: return new plOmniModifier(ver);
        //case 0x0065: return new plSpotModifier(ver);
        //case 0x0066: return new plLtdDirModifier(ver);
        //case 0x0067: return new plSeekPointMod(ver);
        //case 0x0068: return new plOneShotMod(ver);
        //case 0x0069: return new plRandomCommandMod(ver);
        //case 0x006A: return new plRandomSoundMod(ver);
        //case 0x006B: return new plPostEffectMod(ver);
        //case 0x006C: return new plObjectInVolumeDetector(ver);
        //case 0x006D: return new plResponderModifier(ver);
        //case 0x006E: return new plAxisAnimModifier(ver);
        //case 0x006F: return new plLayerLightBase(ver);
        //case 0x0070: return new plFollowMod(ver);
        //case 0x0071: return new plTransitionMgr(ver);
        //case 0x0072: return new plLinkEffectsMgr(ver);
        //case 0x0073: return new plWin32StreamingSound(ver);
        //case 0x0074: return new plActivatorActivatorConditionalObject(ver);
        //case 0x0075: return new plSoftVolume(ver);
        //case 0x0076: return new plSoftVolumeSimple(ver);
        //case 0x0077: return new plSoftVolumeComplex(ver);
        //case 0x0078: return new plSoftVolumeUnion(ver);
        //case 0x0079: return new plSoftVolumeIntersect(ver);
        //case 0x007A: return new plSoftVolumeInvert(ver);
        //case 0x007B: return new plWin32LinkSound(ver);
        //case 0x007C: return new plLayerLinkAnimation(ver);
        //case 0x007D: return new plArmatureMod(ver);
        //case 0x007E: return new plWin32StaticSound(ver);
        //case 0x007F: return new pfGameGUIMgr(ver);
        //case 0x0080: return new pfGUIDialogMod(ver);
        //case 0x0081: return new plCameraBrain1(ver);
        //case 0x0082: return new plVirtualCam1(ver);
        //case 0x0083: return new plCameraModifier1(ver);
        //case 0x0084: return new plCameraBrain1_Drive(ver);
        //case 0x0085: return new plCameraBrain1_Follow(ver);
        //case 0x0086: return new plCameraBrain1_Fixed(ver);
        //case 0x0087: return new pfGUIButtonMod(ver);
        case 0x0088: return new plPythonFileMod(ver);
        //case 0x0089: return new pfGUIControlMod(ver);
        //case 0x008A: return new plExcludeRegionModifier(ver);
        //case 0x008B: return new pfGUIDraggableMod(ver);
        //case 0x008C: return new plVolumeSensorConditionalObject(ver);
        //case 0x008D: return new plVolActivatorConditionalObject(ver);
        //case 0x008E: return new plMsgForwarder(ver);
        //case 0x008F: return new plBlower(ver);
        //case 0x0090: return new pfGUIListBoxMod(ver);
        //case 0x0091: return new pfGUITextBoxMod(ver);
        //case 0x0092: return new pfGUIEditBoxMod(ver);
        //case 0x0093: return new plDynamicTextMap(ver);
        //case 0x0094: return new pfGUISketchCtrl(ver);
        //case 0x0095: return new pfGUIUpDownPairMod(ver);
        //case 0x0096: return new pfGUIValueCtrl(ver);
        //case 0x0097: return new pfGUIKnobCtrl(ver);
        //case 0x0098: return new plLadderModifier(ver);
        //case 0x0099: return new plCameraBrain1_FirstPerson(ver);
        //case 0x009A: return new plCloneSpawnModifier(ver);
        //case 0x009B: return new pfGUIDragBarCtrl(ver);
        //case 0x009C: return new pfGUICheckBoxCtrl(ver);
        //case 0x009D: return new pfGUIRadioGroupCtrl(ver);
        //case 0x009E: return new pfGUIDynDisplayCtrl(ver);
        //case 0x009F: return new plLayerProject(ver);
        //case 0x00A0: return new plInputInterfaceMgr(ver);
        //case 0x00A1: return new plRailCameraMod(ver);
        //case 0x00A2: return new plMultistageBehMod(ver);
        //case 0x00A3: return new plCameraBrain1_Circle(ver);
        //case 0x00A4: return new plParticleWindEffect(ver);
        //case 0x00A5: return new plAnimEventModifier(ver);
        //case 0x00A6: return new plAutoProfile(ver);
        //case 0x00A7: return new pfGUISkin(ver);
        //case 0x00A8: return new plAVIWriter(ver);
        //case 0x00A9: return new plParticleCollisionEffect(ver);
        //case 0x00AA: return new plParticleCollisionEffectDie(ver);
        //case 0x00AB: return new plParticleCollisionEffectBounce(ver);
        //case 0x00AC: return new plInterfaceInfoModifier(ver);
        //case 0x00AD: return new plSharedMesh(ver);
        //case 0x00AE: return new plArmatureEffectsMgr(ver);
        //case 0x00AF: return new plVehicleModifier(ver);
        //case 0x00A0: return new plParticleLocalWind(ver);
        //case 0x00B1: return new plParticleUniformWind(ver);
        //case 0x00B2: return new plInstanceDrawInterface(ver);
        //case 0x00B3: return new plShadowMaster(ver);
        //case 0x00B4: return new plShadowCaster(ver);
        //case 0x00B5: return new plPointShadowMaster(ver);
        //case 0x00B6: return new plDirectShadowMaster(ver);
        //case 0x00B7: return new plSDLModifier(ver);
        //case 0x00B8: return new plPhysicalSDLModifier(ver);
        //case 0x00B9: return new plAGMasterSDLModifier(ver);
        //case 0x00BA: return new plLayerSDLModifier(ver);
        //case 0x00BB: return new plAnimTimeConvertSDLModifier(ver);
        //case 0x00BC: return new plResponderSDLModifier(ver);
        //case 0x00BD: return new plSoundSDLModifier(ver);
        //case 0x00BE: return new plResManagerHelper(ver);
        //case 0x00BF: return new plArmatureEffect(ver);
        //case 0x00C0: return new plAmratureEffectFootSound(ver);
        //case 0x00C1: return new plEAXReverbEffect(ver);
        //case 0x00C2: return new plDynaDecalMgr(ver);
        //case 0x00C3: return new plObjectInVolumeAndFacingDetector(ver);
        //case 0x00C4: return new plDynaFootMgr(ver);
        //case 0x00C5: return new plDynaRippleMgr(ver);
        //case 0x00C6: return new plDynaBulletMgr(ver);
        //case 0x00C7: return new plDecalEnableMod(ver);
        //case 0x00C8: return new plPrintShape(ver);
        //case 0x00C9: return new plDynaPuddleMgr(ver);
        //case 0x00CA: return new pfGUIMultiLineEditCtrl(ver);
        //case 0x00CB: return new plLayerAnimationBase(ver);
        //case 0x00CC: return new plLayerSDLAnimation(ver);
        //case 0x00CD: return new plATCAnim(ver);
        //case 0x00CE: return new plAgeGlobalAnim(ver);
        //case 0x00CF: return new plAvatarMgr(ver);
        //case 0x00D0: return new plSpawnMod(ver);
        //case 0x00D1: return new plActivePrintShape(ver);
        //case 0x00D2: return new plExcludeRegionSDLModifier(ver);
        //case 0x00D3: return new plDynaWakeMgr(ver);
        //case 0x00D4: return new plWaveSet7(ver);
        //case 0x00D5: return new plPanicLinkRegion(ver);
        //case 0x00D6: return new plWin32GroupedSound(ver);
        //case 0x00D7: return new plFilterCoordInterface(ver);
        //case 0x00D8: return new plStereizer(ver);
        //case 0x00D9: return new plShader(ver);
        //case 0x00DA: return new plDynamicEnvMap(ver);
        //case 0x00DB: return new plSimpleRegionSensor(ver);
        //case 0x00DC: return new plMorphSequence(ver);
        //case 0x00DD: return new plCameraBrain_Novice(ver);
        //case 0x00DE: return new plDynaRippleVSMgr(ver);
        //case 0x00DF: return new plWaveSet6(ver);
        //case 0x00E0: return new pfGUIProgressCtrl(ver);
        //case 0x00E1: return new plMaintainersMarkerModifier(ver);
        //case 0x00E2: return new plMorphDataSet(ver);
        //case 0x00E3: return new plHardRegion(ver);
        //case 0x00E4: return new plHardRegionPlanes(ver);
        //case 0x00E5: return new plHardRegionComplex(ver);
        //case 0x00E6: return new plHardRegionUnion(ver);
        //case 0x00E7: return new plHardRegionIntersect(ver);
        //case 0x00E8: return new plHardRegionInvert(ver);
        //case 0x00E9: return new plVisRegion(ver);
        //case 0x00EA: return new plVisRegion(ver);
        //case 0x00EB: return new plRegionBase(ver);
        //case 0x00EC: return new pfGUIPopUpMenu(ver);
        //case 0x00ED: return new pfGUIMenuItem(ver);
        //case 0x00EE: return new plRelevanceRegion(ver);
        //case 0x00EF: return new plRelevanceMgr(ver);
        //case 0x00F0: return new pfJournalBook(ver);
        //case 0x00F1: return new plImageLibMod(ver);
        //case 0x00F2: return new plParticleFlockEffect(ver);
        //case 0x00F3: return new plParticleSDLMod(ver);
        //case 0x00F4: return new plAgeLoader(ver);;
        //case 0x00F5: return new plWaveSetBase(ver);
        //case 0x00F6: return new pfBookData(ver);
        //case 0x00F7: return new plDynaTorpedoMgr(ver);
        //case 0x00F8: return new plDynaTorpedoVSMgr(ver);
        //case 0x00F9: return new plClusterGroup(ver);
        //case 0x00FA: return new plLODMipmap(ver);
        //case 0x00FB: return new plSwimDetector(ver);
        //case 0x00FC: return new plFadeOpacityMod(ver);
        //case 0x00FD: return new plFadeOpacityLay(ver);
        //case 0x00FE: return new plDistOpacityMod(ver);
        //case 0x00FF: return new plArmatureModBase(ver);
        //case 0x0100: return new plDirectMusicSound(ver);
        //case 0x0101: return new plParticleFollowSystemEffect(ver);
        //case 0x0102: return new plClientSessionMgr(ver);
        //case 0x0103: return new plODEPhysical(ver);
        //case 0x0104: return new plSDLVarChangeNotifier(ver);
        //case 0x0105: return new plInterestWellModifier(ver);
        //case 0x0106: return new plElevatorModifier(ver);
        //case 0x0107: return new plCameraBrain_Expert(ver);
        //case 0x0108: return new plPagingRegionModifier(ver);
        //case 0x0109: return new plGuidepathModifier(ver);
        //case 0x010A: return new pfNodeMgr(ver);
        //case 0x010B: return new plEAXEffect(ver);
        //case 0x010C: return new plEAXPitchShifter(ver);
        //case 0x010D: return new plIKModifier(ver);
        //case 0x010E: return new pfObjectFlocker(ver);
        //case 0x010F: return new plCameraBrain_M5(ver);
        //case 0x0110: return new plAGAnimBink(ver);
        //case 0x0111: return new plDynamicCamMap(ver);
        //case 0x0112: return new plTreeShader(ver);
        //case 0x0113: return new plNodeRegionModifier(ver);
        //case 0x0114: return new plPiranhaRegionModifier(ver);

        // 0x0200 - 0x03FF //
        //case 0x0200: return new plAvBrainPirahna(ver);

        // 0x0400 - 0x05FF //
        //case 0x04??: return new ???(ver);
        default:     return NULL;
        }
    } else
        throw "Cannot create objects for unknown Plasma Versions!";
}

