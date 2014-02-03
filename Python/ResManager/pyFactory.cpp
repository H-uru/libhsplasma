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
#include <ResManager/plFactory.h>
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyFactory_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plFactory cannot be constructed");
    return NULL;
}

static PyObject* pyFactory_ClassName(PyObject*, PyObject* args) {
    int classIdx, version = PlasmaVer::pvUnknown;

    if (!PyArg_ParseTuple(args, "i|i", &classIdx, &version)) {
        PyErr_SetString(PyExc_TypeError, "ClassName expects int, int");
        return NULL;
    }
    if (version == PlasmaVer::pvUnknown)
        return PyString_FromString(plFactory::ClassName(classIdx));
    else
        return PyString_FromString(plFactory::ClassName(classIdx, (PlasmaVer)version));
}

static PyObject* pyFactory_ClassIndex(PyObject*, PyObject* args) {
    const char* className;

    if (!PyArg_ParseTuple(args, "s", &className)) {
        PyErr_SetString(PyExc_TypeError, "ClassIndex expects a string");
        return NULL;
    }
    return PyInt_FromLong(plFactory::ClassIndex(className));
}

static PyObject* pyFactory_ClassVersion(PyObject*, PyObject* args) {
    int classIdx, version;

    if (!PyArg_ParseTuple(args, "ii", &classIdx, &version)) {
        PyErr_SetString(PyExc_TypeError, "ClassVersion expects int, int");
        return NULL;
    }
    return PyInt_FromLong(plFactory::ClassVersion(classIdx, (PlasmaVer)version));
}

static PyMethodDef pyFactory_Methods[] = {
    { "ClassName", (PyCFunction)pyFactory_ClassName, METH_STATIC | METH_VARARGS,
      "Params: classIdx, [version]\n"
      "Get the name of the specified class\n"
      "If `version` is specified, the classIdx is looked up for\n"
      "that version (otherwise the global mapping is used)" },
    { "ClassIndex", (PyCFunction)pyFactory_ClassIndex, METH_STATIC | METH_VARARGS,
      "Params: className\n"
      "Returns the global ClassIndex for the specified class" },
    { "ClassVersion", (PyCFunction)pyFactory_ClassVersion, METH_STATIC | METH_VARARGS,
      "Params: classIdx, version\n"
      "Returns the Class Version of the specified class" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyFactory_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plFactory",             /* tp_name */
    0,                                  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "Creatable Factory",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyFactory_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFactory_new,                      /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

#define ADD_CREATABLE(dict, class) \
    PyDict_SetItemString(dict, #class, PyInt_FromLong(class))

PyObject* Init_pyFactory_Type() {
    if (PyType_Ready(&pyFactory_Type) < 0)
        return NULL;

    ADD_CREATABLE(pyFactory_Type.tp_dict, kSceneNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSceneObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kKeyedObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kBitmap);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMipmap);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCubicEnvironmap);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGMaterial);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleSystem);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleCollisionEffectBeat);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleFadeVolumeEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kBoundInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRenderTarget);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCubicRenderTarget);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCubicRenderTargetModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kObjInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAudioInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAudible);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAudibleNull);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWinAudible);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCoordinateInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDrawInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDrawable);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDrawableMesh);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDrawableIce);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPhysical);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPhysicalMesh);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimulationInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSingleModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimpleModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimpleTMModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRandomTMModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInterestingModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDetectorModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimplePhysicalMesh);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCompoundPhysicalMesh);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMultiModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSynchedObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSoundBuffer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAliasModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPickingDetector);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCollisionDetector);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLogicModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kANDConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kORConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPickedConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kActivatorConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kTimerCallbackManager);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kKeyPressConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAnimationEventConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kControlEventConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kObjectInBoxConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLocalPlayerInBoxConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kObjectIntersectPlaneConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLocalPlayerIntersectPlaneConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPortalDrawable);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPortalPhysical);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSpawnModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFacingConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGenericPhysical);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kViewFaceModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerWrapper);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerAnimation);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerDepth);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerMovie);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerBink);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerAVI);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSound);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWin32Sound);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerOr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAudioSystem);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDrawableSpans);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDrawablePatchSet);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInputManager);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLogicModBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFogEnvironment);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetApp);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, k2WayWinAudible);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLightInfo);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDirectionalLightInfo);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kOmniLightInfo);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSpotLightInfo);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLightSpace);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientApp);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerApp);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClient);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCompoundTMModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_Default);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_Drive);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_Fixed);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_FixedPan);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIClickMapCtrl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kListener);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarAnim);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarAnimMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kOccluder);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMobileOccluder);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerShadowBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLimitedDirLightInfo);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAGAnim);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAGModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAGMasterMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_Avatar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraRegionDetector);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_FP);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLineFollowMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLightModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kOmniModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSpotModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLtdDirModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSeekPointMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kOneShotMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRandomCommandMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRandomSoundMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPostEffectMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kObjectInVolumeDetector);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kResponderModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAxisAnimModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerLightBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFollowMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kTransitionMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInventoryMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInventoryObjMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinkEffectsMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWin32StreamingSound);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPythonMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kActivatorActivatorConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSoftVolume);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSoftVolumeSimple);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSoftVolumeComplex);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSoftVolumeUnion);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSoftVolumeIntersect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSoftVolumeInvert);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWin32LinkSound);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerLinkAnimation);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kArmatureMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_Freelook);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kHavokConstraintsMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kHingeConstraintMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWheelConstraintMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kStrongSpringConstraintMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kArmatureLODMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWin32StaticSound);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGameGUIMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIDialogMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain1);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVirtualCam1);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain1_Drive);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain1_POA);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain1_Avatar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain1_Fixed);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain1_POAFixed);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIButtonMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPythonFileMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIControlMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kExcludeRegionModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIDraggableMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVolumeSensorConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVolActivatorConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMsgForwarder);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kBlower);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIListBoxMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUITextBoxMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIEditBoxMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynamicTextMap);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSittingModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIUpDownPairMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIValueCtrl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIKnobCtrl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvLadderMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain1_FirstPerson);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCloneSpawnModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClothingItem);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClothingOutfit);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClothingBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClothingMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIDragBarCtrl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUICheckBoxCtrl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIRadioGroupCtrl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPlayerBookMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIDynDisplayCtrl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerProject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInputInterfaceMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRailCameraMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMultistageBehMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain1_Circle);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleWindEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAnimEventModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAutoProfile);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUISkin);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAVIWriter);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleCollisionEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleCollisionEffectDie);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleCollisionEffectBounce);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInterfaceInfoModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSharedMesh);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kArmatureEffectsMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMarkerMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVehicleModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleLocalWind);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleUniformWind);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInstanceDrawInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kShadowMaster);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kShadowCaster);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPointShadowMaster);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDirectShadowMaster);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPhysicalSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClothingSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAGMasterSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPythonSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAnimTimeConvertSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kResponderSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSoundSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kResManagerHelper);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kHKSubWorld);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kArmatureEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kArmatureEffectFootSound);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEAXListenerMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynaDecalMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kObjectInVolumeAndFacingDetector);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynaFootMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynaRippleMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynaBulletMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDecalEnableMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPrintShape);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynaPuddleMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIMultiLineEditCtrl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerAnimationBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerSDLAnimation);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kATCAnim);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAgeGlobalAnim);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSubworldRegionDetector);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNPCSpawnMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kActivePrintShape);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kExcludeRegionSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLOSDispatch);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynaWakeMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimulationMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWaveSet7);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPanicLinkRegion);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWin32GroupedSound);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFilterCoordInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kStereizer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCCRMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCCRSpecialist);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCCRSeniorSpecialist);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCCRShiftSupervisor);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCCRGameOperator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kShader);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynamicEnvMap);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimpleRegionSensor);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMorphSequence);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEmoteAnim);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynaRippleVSMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWaveSet6);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIProgressCtrl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMaintainersMarkerModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMorphSequenceSDLMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMorphDataSet);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kHardRegion);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kHardRegionPlanes);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kHardRegionComplex);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kHardRegionUnion);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kHardRegionIntersect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kHardRegionInvert);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVisRegion);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVisMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRegionBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIPopUpMenu);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUIMenuItem);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCoopCoordinator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFont);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFontCache);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRelevanceRegion);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRelevanceMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kJournalBook);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerTargetContainer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kImageLibMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleFlockEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleSDLMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAgeLoader);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWaveSetBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPhysicalSndGroup);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kBookData);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynaTorpedoMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynaTorpedoVSMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClusterGroup);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGameMarkerModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLODMipmap);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSwimDetector);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFadeOpacityMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFadeOpacityLay);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDistOpacityMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kArmatureModBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSwimRegionInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSwimCircularCurrentRegion);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleFollowSystemEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSwimStraightCurrentRegion);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kObjectFlocker);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGrassShaderMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynamicCamMap);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAutoWalkRegion);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCrossfade);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleFadeOutEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSecurePreloader);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWindBoneMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_NovicePlus);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSubtitleMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPythonFileModConditionalObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayerTransform);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kBubbleShaderMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLineFollowModBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClientApp);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUICreditsCtrl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrainUru);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVirtualCamera);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrainUru_Drive);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrainUru_Follow);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrainUru_Fixed);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUISketchCtrl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLadderModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrainUru_FirstPerson);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrainUru_Circle);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEAXReverbEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSpawnMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_Novice);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarPhysicalSDLModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDirectMusicSound);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClientSessionMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLVarChangeNotifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInterestWellModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kElevatorModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_Expert);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPagingRegionModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGuidepathModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNodeMgr);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEAXEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEAXPitchShifter);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kIKModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_M5);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAGAnimBink);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kTreeShader);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNodeRegionModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPiranhaRegionModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRidingAnimatedPhysicalDetector);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVolumeSensorConditionalObjectNoArbitration);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFXMaterial);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMovableMod);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMaterial);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleBulletEffect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_Ground);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraBrain_Flight);

    ADD_CREATABLE(pyFactory_Type.tp_dict, kObjRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNodeRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMessage);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGenRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kTimeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAnimCmdMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleUpdateMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLayRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInputEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kKeyEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMouseEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEvalMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kTransformMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kControlEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultCCRNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLOSRequestMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLOSHitMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSingleModMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMultiModMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarPhysicsEnableCallbackMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMemberUpdateMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgPagingRoom);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kActivatorMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDispatch);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kReceiver);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMeshRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGRenderProcs);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSfxAngleFade);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSfxDistFade);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSfxDistShade);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSfxGlobalShade);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSfxIntenseAlpha);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSfxObjDistFade);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSfxObjDistShade);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynamicValue);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynamicScalar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynamicColorRGBA);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynamicMatrix33);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynamicMatrix44);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLeafController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kScaleController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRotController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPosController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kScalarController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPoint3Controller);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kScaleValueController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kQuatController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrix33Controller);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrix44Controller);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEaseController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimpleScaleController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimpleRotController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCompoundRotController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimplePosController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCompoundPosController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kTMController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFogControl);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kIntRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCollisionReactor);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCorrectionMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPhysicalModifier);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPickedMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCollideMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kTriggerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInterestingModMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDebugKeyEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPhysicalProperties);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimplePhys);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrixUpdateMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCondRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kTimerCallbackMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEventCallbackMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSpawnModMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSpawnRequestMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLoadCloneMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEnableMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kWarpMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAttachMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kConsole);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRenderMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAnimTimeConvert);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSoundMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInterestingPing);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNodeCleanupMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSpaceTree);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMessage);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgJoinReq);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgJoinAck);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgLeave);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgPing);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgRoomsList);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgGroupOwner);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgGameStateRequest);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgSessionReset);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgOmnibus);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCCRInvisibleMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinkInDoneMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgGameMessage);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgStream);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAudioSysMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDispatchBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kServerReplyMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDeviceRecreateMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgStreamHelper);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgObjectHelper);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kIMouseXEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kIMouseYEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kIMouseBEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLogicTriggerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPipeline);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDX8Pipeline);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgVoice);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLightRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgStreamedObject);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgSharedState);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgTestAndSet);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgGetSharedState);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSharedStateMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetGenericServerTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetLookupServerGetAgeInfoFromVaultTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLoadAgeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMessageWithCallbacks);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClientMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClientRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgObjStateRequest);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCCRPetitionMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultCCRInitializationTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgWithContext);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgRegisterServer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgUnregisterServer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgStartProcess);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgRegisterProcess);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgUnregisterProcess);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgFindProcess);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgProcessFound);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgRoutingInfo);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerSessionInfo);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimulationMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimulationSynchMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kHKSimulationSynchMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvTaskMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvSeekMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvOneShotMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSatisfiedMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgObjectListHelper);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgObjectUpdateFilter);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kProxyDrawMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSelfDestructMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimInfluenceMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kForceMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kOffsetForceMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kTorqueMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kImpulseMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kOffsetImpulseMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAngularImpulseMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDampMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kShiftMassMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimStateMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFreezeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEventGroupMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSuspendEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgMembersListReq);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgMembersList);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgMemberInfoHelper);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgMemberListHelper);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgMemberUpdate);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgServerToClient);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgCreatePlayer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgAuthenticateHello);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgAuthenticateChallenge);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kConnectedToVaultMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCCRCommunicationMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgInitialAgeStateSent);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInitialAgeStateLoadedMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgFindServerBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgFindServerReplyBase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgFindAuthServer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgFindAuthServerReply);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgFindVaultServer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgFindVaultServerReply);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvTaskSeekDoneMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarSpawnNotifyMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgVaultTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgVaultTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAgeLinkStruct);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultAgeInfoNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgStreamableHelper);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgReceiversListHelper);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgListenListUpdate);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgPing);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgAlive);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgTerminated);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLModifierMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgSDLState);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgSessionReset);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCCRBanLinkingMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCCRSilencePlayerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRenderRequestMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRenderRequestAck);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMember);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetGameMember);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetTransportMember);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kConvexVolume);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleGenerator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimpleParticleGenerator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleEmitter);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAGChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrixChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrixTimeScale);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrixBlend);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrixControllerChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kQuatPointCombine);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPointChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPointConstant);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPointBlend);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kQuatChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kQuatConstant);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kQuatBlend);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinkToAgeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPlayerPageMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCmdIfaceModMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgPlsUpdatePlayer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kListenerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAnimPath);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClothingUpdateBCMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNotifyMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kFakeOutMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCursorChangeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNodeChangeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvEnableMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinkCallbackMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kTransitionMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kConsoleMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVolumeIsect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSphereIsect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kConeIsect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCylinderIsect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParallelIsect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kConvexIsect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kComplexIsect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kUnionIsect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kIntersectionIsect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kModulator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInventoryMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinkEffectsTriggerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinkEffectBCMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kResponderEnableMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgHello);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgHelloReply);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMember);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kResponderMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kOneShotMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultAgeInfoListNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgServerRegistered);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPointTimeScale);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPointControllerChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kQuatTimeScale);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAGApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrixChannelApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPointChannelApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLightDiffuseApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLightAmbientApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLightSpecularApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kOmniApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kQuatChannelApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kScalarChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kScalarTimeScale);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kScalarBlend);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kScalarControllerChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kScalarChannelApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSpotInnerApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSpotOuterApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgPlsRoutableMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPuppetBrainMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kATCEaseCurve);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kConstAccelEaseCurve);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSplineEaseCurve);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultAgeInfoInitializationTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGameGUIMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgVaultRequestGameState);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgVaultGameState);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgVaultGameStateSave);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgVaultGameStateSaved);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgVaultGameStateLoad);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgSDLStateBCast);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kReplaceGeometryMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgExitProcess);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgSaveGameState);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDniCoordinateInfo);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgGameMessageDirected);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinkOutUnloadMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kScalarConstant);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrixConstant);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAGCmdMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleTransferMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleKillMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kExcludeRegionMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kOneTimeParticleGenerator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleLifeMinApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleLifeMaxApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticlePPSApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleAngleApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleVelMinApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleVelMaxApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleScaleMinApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleScaleMaxApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynamicTextMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCameraTargetFadeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAgeLoadedMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPointControllerCacheChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kScalarControllerCacheChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinkEffectsTriggerPrepMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinkEffectPrepBCMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarInputStateMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAgeInfoStruct);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLNotificationMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientConnectAgeVaultTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinkingMgrMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultNotifyMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPlayerInfo);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSwapSpansRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kKI);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDISpansMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgCreatableHelper);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kServerGuid);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgRequestMyVaultPlayerList);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDelayedTransformMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSuperVNodeMgrInitTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kElementRefMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClothingMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEventGroupEnableMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGUINotifyMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrain);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kArmatureBrain);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainHuman);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainCritter);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainDrive);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainSample);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainGeneric);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainPuppet);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainLadder);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kInputIfaceMgrMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kKIMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRemoteAvatarInfoMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrixDelayedCorrectionApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvPushBrainMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvPopBrainMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRoomLoadNotifyMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvAnimTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvSeekTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBlendedSeekTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvOneShotTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvEnableTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvTaskBrain);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAnimStage);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientMember);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgAuthRequest);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgAuthReply);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommAuthTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClientGuid);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgVaultPlayerList);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgSetMyActivePlayer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgRequestAccountPlayerList);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgAccountPlayerList);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgPlayerCreated);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgVaultCreatePlayer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgVaultPlayerCreated);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgFindAge);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgFindAgeReply);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientConnectPrepTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientAuthTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientGetPlayerVaultTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientSetActivePlayerTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientFindAgeTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientLeaveTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientJoinTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCalibrateTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgDeletePlayer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgVaultDeletePlayer);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCoreStatsSummary);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCreatableGenericValue);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCreatableListHelper);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCreatableStream);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainGenericMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvTaskSeek);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAGInstanceCallbackMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kArmatureEffectMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kArmatureEffectStateMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kShadowCastMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kBoundsIsect);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommLeaveTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kResMgrHelperMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgAuthenticateResponse);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgAccountAuthenticated);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommSendPeriodicAliveTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommCheckServerSilenceTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommPingTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommFindAgeTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommSetActivePlayerTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommGetPlayerListTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommCreatePlayerTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommJoinAgeTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultAdminInitializationTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMultistageModMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSoundVolumeApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCutter);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kBulletMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynaDecalEnableMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kOmniCutoffApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kArmatureUpdateMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarFootMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetOwnershipMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgRelevanceRegions);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleFlockMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarBehaviorNotifyMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kATCChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kScalarSDLChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLoadAvatarMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarSetTypeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgLoadClone);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgPlayerPage);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVNodeInitTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRippleShapeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEventManager);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultNeighborhoodInitializationTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgAgentRecoveryRequest);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgFrontendRecoveryRequest);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgBackendRecoveryRequest);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgAgentRecoveryData);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgFrontendRecoveryData);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgBackendRecoveryData);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSubWorldMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrixDifferenceApp);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainUser);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDX9Pipeline);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDXPipeline);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPlayerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainPirahna);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAxisEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCrossfadeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSubtitleMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLStoreMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kOmniSqApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPreResourceMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kUNUSED_DynamicColorRGB);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kUNUSED_DynamicMatrix33);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kUNUSED_DynamicMatrix44);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCompoundController);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientMgrMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAgeLoaderMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainAvatar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPythonNotifyMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNCAgeJoinerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvTaskDumbSeek);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvTaskSmartSeek);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCreatableUuid);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPreloaderMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommAuthConnectedMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommAuthMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommFileListMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommFileDownloadMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommLinkToAgeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommPlayerListMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommActivePlayerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommCreatePlayerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommDeletePlayerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommPublicAgeListMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommPublicAgeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetCommRegisterAgeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAnimEvalMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainFlight);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainNPC);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainBlimp);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainFlightNPC);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kParticleBulletHitMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPanicLinkMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvTaskOneShot);

    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultGameServerInitializationTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientFindDefaultAgeTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultAgeNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultAgeInitializationTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSetListenerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultSystemNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainSwim);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgVault);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgVault);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultConnectTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultNegotiateManifestTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultFetchNodesTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultSaveNodeTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultFindNodeTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultAddNodeRefTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultRemoveNodeRefTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultSendNodeTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultNotifyOperationCallbackTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVNodeMgrInitializationTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultPlayerInitializationTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetVaultServerInitializationTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCommonNeighborhoodsInitTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultNodeRef);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultFolderNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultImageNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultTextNoteNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultSDLNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultAgeLinkNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultChronicleNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultPlayerInfoNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultMgrNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultPlayerNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSynchEnableMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetVaultServerNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultAdminNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultGameServerNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultPlayerInfoListNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarStealthModeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEventCallbackInterceptMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDynamicEnvMapMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClimbMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kIfaceFadeAvatarMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainClimb);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSharedMeshBCMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetVoiceListMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSwimMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMorphDelta);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrixControllerCacheChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultMarkerNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMarkerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPipeResMakeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPipeRTMakeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPipeGeoMakeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvCoopMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainCoop);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSimSuppressMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultMarkerListNode);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvTaskOrient);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAgeBeginLoadingMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSetNetGroupIDMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kBackdoorMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgPython);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPythonMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kStateDataRecord);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommDeletePlayerTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgSetTimeout);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgActivePlayerSet);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommSetTimeoutTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetRoutableMsgOmnibus);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgGetPublicAgeList);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgPublicAgeList);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgCreatePublicAge);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgPublicAgeCreated);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgEnvelope);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommGetPublicAgeListTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommCreatePublicAgeTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgPendingMsgs);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgRequestPendingMsgs);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDbInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDbProxyInterface);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDBGenericSQLDB);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMySqlDB);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetGenericDatabase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetVaultDatabase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetServerMsgPlsUpdatePlayerReply);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kVaultDisconnectTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommSetAgePublicTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommRegisterOwnedAge);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommUnregisterOwnerAge);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommRegisterVisitAge);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommUnregisterVisitAge);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgRemovePublicAge);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetMsgPublicAgeRemoved);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetClientCommRemovePublicAgeTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCCRMessage);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvOneShotLinkTask);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNetAuthDatabase);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvatarOpacityCallbackMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAGDetachCallbackMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMovieEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMovieMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPipeTexMakeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEventLog);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kDbEventLog);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSyslogEventLog);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kCaptureRenderMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAgeLoaded2Msg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPseudoLinkEffectMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPseudoLinkAnimTriggerMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPseudoLinkAnimCallbackMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClimbingWallMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kClimbEventMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainQuab);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLGameTimeElapsedVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinkEffectsDoneMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLStructVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLBoolVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLCharVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLByteVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLIntVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLUIntVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFloatVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDoubleVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLStringVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLTimeVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLUoidVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLVector3Var);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLPoint3Var);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLQuaternionVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLMatrix44Var);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLRGBAVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLAgeTimeOfDayVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLAgeTimeElapsedVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLMetaDoubleVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayStructVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayBoolVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayCharVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayByteVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayIntVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayUIntVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayFloatVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayDoubleVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayStringVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayTimeVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayUoidVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayVector3Var);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayPoint3Var);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayQuaternionVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayMatrix44Var);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayRGBAVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayStructVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayBoolVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayCharVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayByteVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayIntVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayUIntVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayFloatVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayDoubleVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayStringVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayTimeVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayUoidVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayVector3Var);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayPoint3Var);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayQuaternionVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayMatrix44Var);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayRGBAVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLArrayVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLVarChangeMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainPath);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLBufferVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLFixedArrayBufferVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kSDLDynArrayBufferVar);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kMatrixBorrowedChannel);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kNodeRegionMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kEventCallbackSetupMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRelativeMatrixChannelApplicator);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kPiranhaRegionMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGameMgrMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGameCliMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGameCli);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGmTicTacToe);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGmHeek);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGmMarker);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGmBlueSpiral);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAccountUpdateMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAIMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAIBrainCreatedMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGmClimbingWall);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAIArrivedAtGoalMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kGmVarSync);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kLinearVelocityMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAngularVelocityMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kRideAnimatedPhysMsg);
    ADD_CREATABLE(pyFactory_Type.tp_dict, kAvBrainRideAnimatedPhysical);

    Py_INCREF(&pyFactory_Type);
    return (PyObject*)&pyFactory_Type;
}

}
