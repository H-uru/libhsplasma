#include <Python.h>
#include <Stream/hsStream.h>
#include <Util/PlasmaVersions.h>

#include "Debug/pyDebug.h"
#include "Math/pyGeometry3.h"
#include "Math/pyMatrix.h"
#include "ResManager/pyResManager.h"
#include "Stream/pyStream.h"
#include "Sys/pyColor.h"
#include "Util/pyBitVector.h"

#include "PRP/pyCreatable.h"
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
#include "PRP/Audio/pySoundBuffer.h"
#include "PRP/Geometry/pyCluster.h"
#include "PRP/Geometry/pyClusterGroup.h"
#include "PRP/Geometry/pyDrawableSpans.h"
#include "PRP/Geometry/pyGBufferGroup.h"
#include "PRP/Geometry/pyOccluder.h"
#include "PRP/Geometry/pySpaceTree.h"
#include "PRP/Geometry/pySpan.h"
#include "PRP/Geometry/pySpanInstance.h"
#include "PRP/Geometry/pySpanTemplate.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/Light/pyLightInfo.h"
#include "PRP/Message/pyEventCallbackMsg.h"
#include "PRP/Message/pyMessage.h"
#include "PRP/Message/pyMsgForwarder.h"
#include "PRP/Misc/pyRenderLevel.h"
#include "PRP/Modifier/pyModifier.h"
#include "PRP/Modifier/pyOneShotMod.h"
#include "PRP/Modifier/pyPythonFileMod.h"
#include "PRP/Modifier/pyResponderModifier.h"
#include "PRP/Object/pyObjInterface.h"
#include "PRP/Object/pySceneObject.h"
#include "PRP/Object/pySynchedObject.h"
#include "PRP/Physics/pyPhysical.h"
#include "PRP/Region/pyBounds.h"
#include "PRP/Surface/pyBitmap.h"
#include "PRP/Surface/pyDynamicTextMap.h"
#include "PRP/Surface/pyGMaterial.h"
#include "PRP/Surface/pyGMatState.h"
#include "PRP/Surface/pyLayer.h"
#include "PRP/Surface/pyLayerAnimation.h"
#include "PRP/Surface/pyLayerMovie.h"
#include "PRP/Surface/pyShader.h"

extern "C" {

static PyObject* PyPlasma_CleanFileName(PyObject*, PyObject* args) {
    const char* fname;
    unsigned char allowPathChars = 0;
    if (!PyArg_ParseTuple(args, "s|b", &fname, &allowPathChars)) {
        PyErr_SetString(PyExc_TypeError, "CleanFileName expects a string");
        return NULL;
    }
    return PyString_FromString(CleanFileName(fname, allowPathChars != 0).cstr());
}

}

static PyMethodDef PyPlasma_Methods[] = {
    { "CleanFileName", (PyCFunction)PyPlasma_CleanFileName, METH_VARARGS,
      "Params: string, allowPathChars=Talse\n"
      "Strips illegal characters from a filename. If allowPathChars is True,\n"
      "the characters '\\', '/' and ':' will not be removed" },
    { NULL, NULL, 0, NULL }
};

void initPyPlasma_Constants(PyObject* module) {
    /* Generic constants */
    PyModule_AddIntConstant(module, "pvUnknown", pvUnknown);
    PyModule_AddIntConstant(module, "pvPrime", pvPrime);
    PyModule_AddIntConstant(module, "pvPots", pvPots);
    PyModule_AddIntConstant(module, "pvLive", pvLive);
    PyModule_AddIntConstant(module, "pvEoa", pvEoa);
    PyModule_AddIntConstant(module, "pvHex", pvHex);

    /* File modes */
    PyModule_AddIntConstant(module, "fmRead", fmRead);
    PyModule_AddIntConstant(module, "fmWrite", fmWrite);
    PyModule_AddIntConstant(module, "fmReadWrite", fmReadWrite);
    PyModule_AddIntConstant(module, "fmCreate", fmCreate);

    /* Enum CallbackEvent */
    PyModule_AddIntConstant(module, "kStart", kStart);
    PyModule_AddIntConstant(module, "kStop", kStop);
    PyModule_AddIntConstant(module, "kReverse", kReverse);
    PyModule_AddIntConstant(module, "kTime", kTime);
    PyModule_AddIntConstant(module, "kLoop", kLoop);
    PyModule_AddIntConstant(module, "kBegin", kBegin);
    PyModule_AddIntConstant(module, "kEnd", kEnd);
    PyModule_AddIntConstant(module, "kEventEnd", kEventEnd);
    PyModule_AddIntConstant(module, "kSingleFrameAdjust", kSingleFrameAdjust);
    PyModule_AddIntConstant(module, "kSingleFrameEval", kSingleFrameEval);
}

PyMODINIT_FUNC initPyPlasma() {
    PyObject* module = Py_InitModule3("PyPlasma", PyPlasma_Methods,
                                      "libPlasma Python Interface Module");
    initPyPlasma_Constants(module);

    /* Debug */
    PyModule_AddObject(module, "plDebug", Init_pyDebug_Type());

    /* Stream */
    PyModule_AddObject(module, "hsStream", Init_pyStream_Type());
    PyModule_AddObject(module, "hsFileStream", Init_pyFileStream_Type());
    PyModule_AddObject(module, "plEncryptedStream", Init_pyEncryptedStream_Type());

    /* Util */
    PyModule_AddObject(module, "hsBitVector", Init_pyBitVector_Type());

    /* pyColor */
    PyModule_AddObject(module, "hsColorRGBA", Init_pyColorRGBA_Type());
    PyModule_AddObject(module, "hsColor32", Init_pyColor32_Type());

    /* Math */
    PyModule_AddObject(module, "hsVector3", Init_pyVector3_Type());
    PyModule_AddObject(module, "hsPlane3", Init_pyPlane3_Type());
    PyModule_AddObject(module, "hsQuat", Init_pyQuat_Type());
    PyModule_AddObject(module, "hsAffineParts", Init_pyAffineParts_Type());
    PyModule_AddObject(module, "hsMatrix33", Init_pyMatrix33_Type());
    PyModule_AddObject(module, "hsMatrix44", Init_pyMatrix44_Type());

    /* ResManager */
    PyModule_AddObject(module, "plFactory", Init_pyFactory_Type());
    PyModule_AddObject(module, "plResManager", Init_pyResManager_Type());
    PyModule_AddObject(module, "plPageInfo", Init_pyPageInfo_Type());
    PyModule_AddObject(module, "plAgeInfo", Init_pyAgeInfo_Type());

    /* pyBounds */
    PyModule_AddObject(module, "hsBounds", Init_pyBounds_Type());
    PyModule_AddObject(module, "hsBounds3", Init_pyBounds3_Type());
    PyModule_AddObject(module, "hsBounds3Ext", Init_pyBounds3Ext_Type());
    PyModule_AddObject(module, "hsBoundsOriented", Init_pyBoundsOriented_Type());

    /* pySpan */
    PyModule_AddObject(module, "plSpan", Init_pySpan_Type());
    PyModule_AddObject(module, "plVertexSpan", Init_pyVertexSpan_Type());
    PyModule_AddObject(module, "plIcicle", Init_pyIcicle_Type());
    PyModule_AddObject(module, "plParticleSpan", Init_pyParticleSpan_Type());

    /* pyKey */
    PyModule_AddObject(module, "plKey", Init_pyKey_Type());
    PyModule_AddObject(module, "plLocation", Init_pyLocation_Type());

    /* Cluster stuff */
    PyModule_AddObject(module, "plCluster", Init_pyCluster_Type());
    PyModule_AddObject(module, "plSpanEncoding", Init_pySpanEncoding_Type());
    PyModule_AddObject(module, "plSpanInstance", Init_pySpanInstance_Type());
    PyModule_AddObject(module, "plSpanTemplate", Init_pySpanTemplate_Type());
    PyModule_AddObject(module, "plSpanTemplateVertex", Init_pySpanTemplateVertex_Type());
    PyModule_AddObject(module, "plLODDist", Init_pyLODDist_Type());

    /* Key Frames */
    PyModule_AddObject(module, "hsKeyFrame", Init_pyKeyFrame_Type());
    PyModule_AddObject(module, "hsPoint3Key", Init_pyPoint3Key_Type());
    PyModule_AddObject(module, "hsScalarKey", Init_pyScalarKey_Type());
    PyModule_AddObject(module, "hsScaleKey", Init_pyScaleKey_Type());
    PyModule_AddObject(module, "hsQuatKey", Init_pyQuatKey_Type());
    PyModule_AddObject(module, "hsCompressedQuatKey32", Init_pyCompressedQuatKey32_Type());
    PyModule_AddObject(module, "hsCompressedQuatKey64", Init_pyCompressedQuatKey64_Type());
    PyModule_AddObject(module, "hsG3DSMaxKeyFrame", Init_pyG3DSMaxKeyFrame_Type());
    PyModule_AddObject(module, "hsMatrix33Key", Init_pyMatrix33Key_Type());
    PyModule_AddObject(module, "hsMatrix44Key", Init_pyMatrix44Key_Type());

    /* Other Creatable Dependancies */
    PyModule_AddObject(module, "plDISpanIndex", Init_pyDISpanIndex_Type());
    PyModule_AddObject(module, "plGBufferCell", Init_pyGBufferCell_Type());
    PyModule_AddObject(module, "plGBufferTriangle", Init_pyGBufferTriangle_Type());
    PyModule_AddObject(module, "plGBufferVertex", Init_pyGBufferVertex_Type());
    PyModule_AddObject(module, "plGBufferGroup", Init_pyGBufferGroup_Type());
    PyModule_AddObject(module, "plRenderLevel", Init_pyRenderLevel_Type());
    PyModule_AddObject(module, "plSpaceTreeNode", Init_pySpaceTreeNode_Type());
    PyModule_AddObject(module, "hsGMatState", Init_pyGMatState_Type());
    PyModule_AddObject(module, "plShaderConst", Init_pyShaderConst_Type());
    PyModule_AddObject(module, "plWAVHeader", Init_pyWAVHeader_Type());
    PyModule_AddObject(module, "plSimDefs", Init_pySimDefs_Type());
    PyModule_AddObject(module, "plPythonParameter", Init_pyPythonParameter_Type());
    PyModule_AddObject(module, "plResponderModifier_Cmd", Init_pyResponderModifier_Cmd_Type());
    PyModule_AddObject(module, "plResponderModifier_State", Init_pyResponderModifier_State_Type());

    /* Creatables */
    PyModule_AddObject(module, "plCreatable", Init_pyCreatable_Type());
    PyModule_AddObject(module, "plCreatableStub", Init_pyCreatableStub_Type());

    PyModule_AddObject(module, "hsKeyedObject", Init_pyKeyedObject_Type());
    PyModule_AddObject(module, "plSceneNode", Init_pySceneNode_Type());
    PyModule_AddObject(module, "plSynchedObject", Init_pySynchedObject_Type());
    PyModule_AddObject(module, "plSceneObject", Init_pySceneObject_Type());
    PyModule_AddObject(module, "plObjInterface", Init_pyObjInterface_Type());
    PyModule_AddObject(module, "plAudioInterface", Init_pyAudioInterface_Type());
    PyModule_AddObject(module, "plCoordinateInterface", Init_pyCoordinateInterface_Type());
    PyModule_AddObject(module, "plDrawInterface", Init_pyDrawInterface_Type());
    PyModule_AddObject(module, "plSimulationInterface", Init_pySimulationInterface_Type());
    PyModule_AddObject(module, "plDrawable", Init_pyDrawable_Type());
    PyModule_AddObject(module, "plDrawableSpans", Init_pyDrawableSpans_Type());
    PyModule_AddObject(module, "hsGMaterial", Init_pyGMaterial_Type());
    PyModule_AddObject(module, "plLayerInterface", Init_pyLayerInterface_Type());
    PyModule_AddObject(module, "plLayer", Init_pyLayer_Type());
    PyModule_AddObject(module, "plLayerDepth", Init_pyLayerDepth_Type());
    PyModule_AddObject(module, "plShader", Init_pyShader_Type());
    PyModule_AddObject(module, "plBitmap", Init_pyBitmap_Type());
    PyModule_AddObject(module, "plMipmap", Init_pyMipmap_Type());
    PyModule_AddObject(module, "plLightInfo", Init_pyLightInfo_Type());
    PyModule_AddObject(module, "plDirectionalLightInfo", Init_pyDirectionalLightInfo_Type());
    PyModule_AddObject(module, "plLimitedDirLightInfo", Init_pyLimitedDirLightInfo_Type());
    PyModule_AddObject(module, "plOmniLightInfo", Init_pyOmniLightInfo_Type());
    PyModule_AddObject(module, "plSpotLightInfo", Init_pySpotLightInfo_Type());
    PyModule_AddObject(module, "plSoundBuffer", Init_pySoundBuffer_Type());
    PyModule_AddObject(module, "plPhysical", Init_pyPhysical_Type());
    PyModule_AddObject(module, "plGenericPhysical", Init_pyGenericPhysical_Type());
    PyModule_AddObject(module, "plModifier", Init_pyModifier_Type());
    PyModule_AddObject(module, "plSingleModifier", Init_pySingleModifier_Type());
    PyModule_AddObject(module, "plMultiModifier", Init_pyMultiModifier_Type());
    PyModule_AddObject(module, "plPythonFileMod", Init_pyPythonFileMod_Type());
    PyModule_AddObject(module, "plViewFaceModifier", Init_pyViewFaceModifier_Type());
    PyModule_AddObject(module, "plClusterGroup", Init_pyClusterGroup_Type());
    PyModule_AddObject(module, "plLayerAnimationBase", Init_pyLayerAnimationBase_Type());
    PyModule_AddObject(module, "plLayerAnimation", Init_pyLayerAnimation_Type());
    PyModule_AddObject(module, "plLayerLinkAnimation", Init_pyLayerLinkAnimation_Type());
    PyModule_AddObject(module, "plLayerSDLAnimation", Init_pyLayerSDLAnimation_Type());
    PyModule_AddObject(module, "plLayerMovie", Init_pyLayerMovie_Type());
    PyModule_AddObject(module, "plLayerAVI", Init_pyLayerAVI_Type());
    PyModule_AddObject(module, "plLayerBink", Init_pyLayerBink_Type());
    PyModule_AddObject(module, "plOneShotMod", Init_pyOneShotMod_Type());
    PyModule_AddObject(module, "plResponderModifier", Init_pyResponderModifier_Type());
    PyModule_AddObject(module, "plDynamicTextMap", Init_pyDynamicTextMap_Type());
    PyModule_AddObject(module, "plOccluder", Init_pyOccluder_Type());
    PyModule_AddObject(module, "plAGAnim", Init_pyAGAnim_Type());
    PyModule_AddObject(module, "plAgeGlobalAnim", Init_pyAgeGlobalAnim_Type());
    PyModule_AddObject(module, "plATCAnim", Init_pyATCAnim_Type());
    PyModule_AddObject(module, "plEmoteAnim", Init_pyEmoteAnim_Type());
    PyModule_AddObject(module, "plAGAnimBink", Init_pyAGAnimBink_Type());
    PyModule_AddObject(module, "plMsgForwarder", Init_pyMsgForwarder_Type());

    PyModule_AddObject(module, "plSpaceTree", Init_pySpaceTree_Type());
    PyModule_AddObject(module, "plController", Init_pyController_Type());
    PyModule_AddObject(module, "plCompoundController", Init_pyCompoundController_Type());
    PyModule_AddObject(module, "plTMController", Init_pyTMController_Type());
    PyModule_AddObject(module, "plPosController", Init_pyPosController_Type());
    PyModule_AddObject(module, "plSimplePosController", Init_pySimplePosController_Type());
    PyModule_AddObject(module, "plCompoundPosController", Init_pyCompoundPosController_Type());
    PyModule_AddObject(module, "plRotController", Init_pyRotController_Type());
    PyModule_AddObject(module, "plSimpleRotController", Init_pySimpleRotController_Type());
    PyModule_AddObject(module, "plCompoundRotController", Init_pyCompoundRotController_Type());
    PyModule_AddObject(module, "plScaleController", Init_pyScaleController_Type());
    PyModule_AddObject(module, "plSimpleScaleController", Init_pySimpleScaleController_Type());
    PyModule_AddObject(module, "plLeafController", Init_pyLeafController_Type());
    PyModule_AddObject(module, "plEaseController", Init_pyEaseController_Type());
    PyModule_AddObject(module, "plMatrix33Controller", Init_pyMatrix33Controller_Type());
    PyModule_AddObject(module, "plMatrix44Controller", Init_pyMatrix44Controller_Type());
    PyModule_AddObject(module, "plPoint3Controller", Init_pyPoint3Controller_Type());
    PyModule_AddObject(module, "plQuatController", Init_pyQuatController_Type());
    PyModule_AddObject(module, "plScalarController", Init_pyScalarController_Type());
    PyModule_AddObject(module, "plScaleValueController", Init_pyScaleValueController_Type());
    PyModule_AddObject(module, "plATCEaseCurve", Init_pyATCEaseCurve_Type());
    PyModule_AddObject(module, "plSplineEaseCurve", Init_pySplineEaseCurve_Type());
    PyModule_AddObject(module, "plConstAccelEaseCurve", Init_pyConstAccelEaseCurve_Type());
    PyModule_AddObject(module, "plAnimTimeConvert", Init_pyAnimTimeConvert_Type());
    PyModule_AddObject(module, "plMessage", Init_pyMessage_Type());
    PyModule_AddObject(module, "plEventCallbackMsg", Init_pyEventCallbackMsg_Type());
    PyModule_AddObject(module, "plResponderEnableMsg", Init_pyResponderEnableMsg_Type());
    PyModule_AddObject(module, "plAGApplicator", Init_pyAGApplicator_Type());
    PyModule_AddObject(module, "plAGChannel", Init_pyAGChannel_Type());
    PyModule_AddObject(module, "plSoundVolumeApplicator", Init_pySoundVolumeApplicator_Type());
    PyModule_AddObject(module, "plLightAmbientApplicator", Init_pyLightAmbientApplicator_Type());
    PyModule_AddObject(module, "plLightDiffuseApplicator", Init_pyLightDiffuseApplicator_Type());
    PyModule_AddObject(module, "plLightSpecularApplicator", Init_pyLightSpecularApplicator_Type());
    PyModule_AddObject(module, "plOmniApplicator", Init_pyOmniApplicator_Type());
    PyModule_AddObject(module, "plOmniCutoffApplicator", Init_pyOmniCutoffApplicator_Type());
    PyModule_AddObject(module, "plOmniSqApplicator", Init_pyOmniSqApplicator_Type());
    PyModule_AddObject(module, "plSpotInnerApplicator", Init_pySpotInnerApplicator_Type());
    PyModule_AddObject(module, "plSpotOuterApplicator", Init_pySpotOuterApplicator_Type());
    PyModule_AddObject(module, "plMatrixChannel", Init_pyMatrixChannel_Type());
    PyModule_AddObject(module, "plMatrixBlend", Init_pyMatrixBlend_Type());
    PyModule_AddObject(module, "plMatrixConstant", Init_pyMatrixConstant_Type());
    PyModule_AddObject(module, "plMatrixControllerCacheChannel", Init_pyMatrixControllerCacheChannel_Type());
    PyModule_AddObject(module, "plMatrixControllerChannel", Init_pyMatrixControllerChannel_Type());
    PyModule_AddObject(module, "plMatrixTimeScale", Init_pyMatrixTimeScale_Type());
    PyModule_AddObject(module, "plQuatPointCombine", Init_pyQuatPointCombine_Type());
    PyModule_AddObject(module, "plMatrixChannelApplicator", Init_pyMatrixChannelApplicator_Type());
    PyModule_AddObject(module, "plMatrixDelayedCorrectionApplicator", Init_pyMatrixDelayedCorrectionApplicator_Type());
    PyModule_AddObject(module, "plMatrixDifferenceApp", Init_pyMatrixDifferenceApp_Type());
    PyModule_AddObject(module, "plRelativeMatrixChannelApplicator", Init_pyRelativeMatrixChannelApplicator_Type());
    PyModule_AddObject(module, "plPointChannel", Init_pyPointChannel_Type());
    PyModule_AddObject(module, "plPointBlend", Init_pyPointBlend_Type());
    PyModule_AddObject(module, "plPointConstant", Init_pyPointConstant_Type());
    PyModule_AddObject(module, "plPointControllerCacheChannel", Init_pyPointControllerCacheChannel_Type());
    PyModule_AddObject(module, "plPointControllerChannel", Init_pyPointControllerChannel_Type());
    PyModule_AddObject(module, "plPointTimeScale", Init_pyPointTimeScale_Type());
    PyModule_AddObject(module, "plPointChannelApplicator", Init_pyPointChannelApplicator_Type());
    PyModule_AddObject(module, "plQuatChannel", Init_pyQuatChannel_Type());
    PyModule_AddObject(module, "plQuatBlend", Init_pyQuatBlend_Type());
    PyModule_AddObject(module, "plQuatConstant", Init_pyQuatConstant_Type());
    PyModule_AddObject(module, "plQuatTimeScale", Init_pyQuatTimeScale_Type());
    PyModule_AddObject(module, "plQuatChannelApplicator", Init_pyQuatChannelApplicator_Type());
    PyModule_AddObject(module, "plScalarChannel", Init_pyScalarChannel_Type());
    PyModule_AddObject(module, "plScalarBlend", Init_pyScalarBlend_Type());
    PyModule_AddObject(module, "plScalarConstant", Init_pyScalarConstant_Type());
    PyModule_AddObject(module, "plScalarControllerCacheChannel", Init_pyScalarControllerCacheChannel_Type());
    PyModule_AddObject(module, "plScalarControllerChannel", Init_pyScalarControllerChannel_Type());
    PyModule_AddObject(module, "plScalarTimeScale", Init_pyScalarTimeScale_Type());
    PyModule_AddObject(module, "plScalarSDLChannel", Init_pyScalarSDLChannel_Type());
    PyModule_AddObject(module, "plATCChannel", Init_pyATCChannel_Type());
    PyModule_AddObject(module, "plScalarChannelApplicator", Init_pyScalarChannelApplicator_Type());
    
    PyModule_AddObject(module, "plCullPoly", Init_pyCullPoly_Type());
}
