#include <Python.h>
#include <Stream/hsStream.h>
#include <Util/PlasmaVersions.h>

#include "Debug/pyDebug.h"
#include "Math/pyGeometry3.h"
#include "Math/pyMatrix44.h"
#include "ResManager/pyResManager.h"
#include "Stream/pyStream.h"
#include "Sys/pyColor.h"
#include "Util/pyBitVector.h"

#include "PRP/pyCreatable.h"
#include "PRP/pySceneNode.h"
#include "PRP/Audio/pySoundBuffer.h"
#include "PRP/Geometry/pyDrawableSpans.h"
#include "PRP/Geometry/pyGBufferGroup.h"
#include "PRP/Geometry/pySpaceTree.h"
#include "PRP/Geometry/pySpan.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/Light/pyLightInfo.h"
#include "PRP/Misc/pyRenderLevel.h"
#include "PRP/Object/pyObjInterface.h"
#include "PRP/Object/pySceneObject.h"
#include "PRP/Object/pySynchedObject.h"
#include "PRP/Physics/pyPhysical.h"
#include "PRP/Region/pyBounds.h"
#include "PRP/Surface/pyBitmap.h"
#include "PRP/Surface/pyGMaterial.h"
#include "PRP/Surface/pyGMatState.h"
#include "PRP/Surface/pyLayer.h"
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
    PyModule_AddObject(module, "hsMatrix44", Init_pyMatrix44_Type());
    PyModule_AddObject(module, "hsQuat", Init_pyQuat_Type());

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

    PyModule_AddObject(module, "plSpaceTree", Init_pySpaceTree_Type());
}
