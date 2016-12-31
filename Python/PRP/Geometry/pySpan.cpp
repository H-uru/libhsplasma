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

#include "pySpan.h"

#include <PRP/Geometry/plSpan.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Region/pyBounds.h"
#include "Stream/pyStream.h"
#include "Math/pyMatrix.h"

extern "C" {

PY_PLASMA_DEALLOC(Span)
PY_PLASMA_EMPTY_INIT(Span)
PY_PLASMA_NEW(Span, plSpan)

static PyObject* pySpan_ClassName(pySpan* self) {
    return pyPlasma_convert(self->fThis->ClassName());
}

static PyObject* pySpan_read(pySpan* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

static PyObject* pySpan_write(pySpan* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

static PyObject* pySpan_clearPermaLights(pySpan* self, PyObject* args) {
    self->fThis->clearPermaLights();
    Py_RETURN_NONE;
}

static PyObject* pySpan_clearPermaProjs(pySpan* self, PyObject* args) {
    self->fThis->clearPermaProjs();
    Py_RETURN_NONE;
}

static PyObject* pySpan_addPermaLight(pySpan* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addPermaLight expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addPermaLight expects a plKey");
        return NULL;
    }
    self->fThis->addPermaLight(*key->fThis);
    Py_RETURN_NONE;
}

static PyObject* pySpan_addPermaProj(pySpan* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addPermaProj expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addPermaProj expects a plKey");
        return NULL;
    }
    self->fThis->addPermaProj(*key->fThis);
    Py_RETURN_NONE;
}

static PyObject* pySpan_getLights(pySpan* self, void*) {
    PyObject* list = PyList_New(self->fThis->getPermaLights().size());
    for (size_t i=0; i<self->fThis->getPermaLights().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getPermaLights()[i]));
    return list;
}

static PyObject* pySpan_getProjs(pySpan* self, void*) {
    PyObject* list = PyList_New(self->fThis->getPermaProjs().size());
    for (size_t i=0; i<self->fThis->getPermaProjs().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getPermaProjs()[i]));
    return list;
}

static int pySpan_setLights(pySpan* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Lights, use addPermaLight and addPermaProj");
    return -1;
}

static PyMethodDef pySpan_Methods[] = {
    { "ClassName", (PyCFunction)pySpan_ClassName, METH_NOARGS,
      "Returns the RTTI Class name of this Span object" },
    { "read", (PyCFunction)pySpan_read, METH_VARARGS,
      "Params: stream\n"
      "Read this Span object from the stream" },
    { "write", (PyCFunction)pySpan_write, METH_VARARGS,
      "Params: stream\n"
      "Write this Span object to the stream" },
    { "clearPermaLights", (PyCFunction)pySpan_clearPermaLights, METH_NOARGS,
      "Remove all Perma Lights from this Span" },
    { "clearPermaProjs", (PyCFunction)pySpan_clearPermaProjs, METH_NOARGS,
      "Remove all Perma Projs from this Span" },
    { "addPermaLight", (PyCFunction)pySpan_addPermaLight, METH_VARARGS,
      "Params: key\n"
      "Add a Perma Light to the span" },
    { "addPermaProj", (PyCFunction)pySpan_addPermaProj, METH_VARARGS,
      "Params: key\n"
      "Add a Perma Proj to the span" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(plKey, Span, fog, getFogEnvironment, setFogEnvironment) // Backwards compatibility
PY_PROPERTY(plKey, Span, fogEnvironment, getFogEnvironment, setFogEnvironment)
PY_PROPERTY(hsMatrix44, Span, localToWorld, getLocalToWorld, setLocalToWorld)
PY_PROPERTY(hsMatrix44, Span, worldToLocal, getWorldToLocal, setLocalToWorld)
PY_PROPERTY(unsigned short, Span, subType, getSubType, setSubType)
PY_PROPERTY(unsigned int, Span, materialIdx, getMaterialIdx, setMaterialIdx)
PY_PROPERTY(unsigned char, Span, numMatrices, getNumMatrices, setNumMatrices)
PY_PROPERTY(unsigned int, Span, props, getProps, setProps)
PY_PROPERTY(unsigned int, Span, baseMatrix, getBaseMatrix, setBaseMatrix)
PY_PROPERTY(unsigned short, Span, maxBoneIdx, getMaxBoneIdx, setMaxBoneIdx)
PY_PROPERTY(unsigned short, Span, penBoneIdx, getPenBoneIdx, setPenBoneIdx)
PY_PROPERTY(unsigned short, Span, localUVWChans, getLocalUVWChans, setLocalUVWChans)
PY_PROPERTY(float, Span, minDist, getMinDist, setMinDist)
PY_PROPERTY(float, Span, maxDist, getMaxDist, setMaxDist)
PY_PROPERTY(float, Span, waterHeight, getWaterHeight, setWaterHeight)
PY_PROPERTY_BOUNDS(Bounds3Ext, Span, localBounds, getLocalBounds, setLocalBounds)
PY_PROPERTY_BOUNDS(Bounds3Ext, Span, worldBounds, getWorldBounds, setWorldBounds)

static PyGetSetDef pySpan_GetSet[] = {
    pySpan_fogEnvironment_getset,
    pySpan_fog_getset,
    { _pycs("permaLights"), (getter)pySpan_getLights,
        (setter)pySpan_setLights, NULL, NULL },
    { _pycs("permaProjs"), (getter)pySpan_getProjs,
        (setter)pySpan_setLights, NULL, NULL },
    pySpan_localToWorld_getset,
    pySpan_worldToLocal_getset,
    pySpan_subType_getset,
    pySpan_materialIdx_getset,
    pySpan_numMatrices_getset,
    pySpan_props_getset,
    pySpan_baseMatrix_getset,
    pySpan_maxBoneIdx_getset,
    pySpan_penBoneIdx_getset,
    pySpan_localUVWChans_getset,
    pySpan_minDist_getset,
    pySpan_maxDist_getset,
    pySpan_waterHeight_getset,
    pySpan_localBounds_getset,
    pySpan_worldBounds_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pySpan_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSpan",                /* tp_name */
    sizeof(pySpan),                     /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pySpan_dealloc,                     /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plSpan wrapper",                   /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySpan_Methods,                     /* tp_methods */
    NULL,                               /* tp_members */
    pySpan_GetSet,                      /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pySpan___init__,                    /* tp_init */
    NULL,                               /* tp_alloc */
    pySpan_new,                         /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pySpan_Type() {
    if (PyType_Ready(&pySpan_Type) < 0)
        return NULL;

    PyDict_SetItemString(pySpan_Type.tp_dict, "kLiteMaterial",
                         PyInt_FromLong(plSpan::kLiteMaterial));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropNoDraw",
                         PyInt_FromLong(plSpan::kPropNoDraw));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropNoShadowCast",
                         PyInt_FromLong(plSpan::kPropNoShadowCast));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropFacesSortable",
                         PyInt_FromLong(plSpan::kPropFacesSortable));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropVolatile",
                         PyInt_FromLong(plSpan::kPropVolatile));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kWaterHeight",
                         PyInt_FromLong(plSpan::kWaterHeight));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropRunTimeLight",
                         PyInt_FromLong(plSpan::kPropRunTimeLight));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropReverseSort",
                         PyInt_FromLong(plSpan::kPropReverseSort));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropHasPermaLights",
                         PyInt_FromLong(plSpan::kPropHasPermaLights));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropHasPermaProjs",
                         PyInt_FromLong(plSpan::kPropHasPermaProjs));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kLiteVtxPreshaded",
                         PyInt_FromLong(plSpan::kLiteVtxPreshaded));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kLiteVtxNonPreshaded",
                         PyInt_FromLong(plSpan::kLiteVtxNonPreshaded));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kLiteProjection",
                         PyInt_FromLong(plSpan::kLiteProjection));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kLiteShadowErase",
                         PyInt_FromLong(plSpan::kLiteShadowErase));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kLiteShadow",
                         PyInt_FromLong(plSpan::kLiteShadow));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropMatHasSpecular",
                         PyInt_FromLong(plSpan::kPropMatHasSpecular));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropProjAsVtx",
                         PyInt_FromLong(plSpan::kPropProjAsVtx));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropSkipProjection",
                         PyInt_FromLong(plSpan::kPropSkipProjection));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropNoShadow",
                         PyInt_FromLong(plSpan::kPropNoShadow));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropForceShadow",
                         PyInt_FromLong(plSpan::kPropForceShadow));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropDisableNormal",
                         PyInt_FromLong(plSpan::kPropDisableNormal));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPropCharacter",
                         PyInt_FromLong(plSpan::kPropCharacter));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kPartialSort",
                         PyInt_FromLong(plSpan::kPartialSort));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kVisLOS",
                         PyInt_FromLong(plSpan::kVisLOS));

    // plSpanType
    PyDict_SetItemString(pySpan_Type.tp_dict, "kSpan",
                         PyInt_FromLong(plSpan::kSpan));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kVertexSpan",
                         PyInt_FromLong(plSpan::kVertexSpan));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kIcicleSpan",
                         PyInt_FromLong(plSpan::kIcicleSpan));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kNullSpan",
                         PyInt_FromLong(plSpan::kNullSpan));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kParticleSpan",
                         PyInt_FromLong(plSpan::kParticleSpan));
    PyDict_SetItemString(pySpan_Type.tp_dict, "kParticleSet",
                         PyInt_FromLong(plSpan::kParticleSet));

    Py_INCREF(&pySpan_Type);
    return (PyObject*)&pySpan_Type;
}

PY_PLASMA_IFC_METHODS(Span, plSpan)

}
