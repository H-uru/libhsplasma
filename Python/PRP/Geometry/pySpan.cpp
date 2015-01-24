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
#include <PRP/Geometry/plSpan.h>
#include "pySpan.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Region/pyBounds.h"
#include "Stream/pyStream.h"
#include "Math/pyMatrix.h"

extern "C" {

static void pySpan_dealloc(pySpan* self) {
    if (self->fPyOwned)
        delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pySpan___init__(pySpan* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pySpan_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySpan* self = (pySpan*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSpan();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySpan_ClassName(pySpan* self) {
    return PyString_FromString(self->fThis->ClassName());
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
    Py_INCREF(Py_None);
    return Py_None;
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySpan_clearPermaLights(pySpan* self, PyObject* args) {
    self->fThis->clearPermaLights();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySpan_clearPermaProjs(pySpan* self, PyObject* args) {
    self->fThis->clearPermaProjs();
    Py_INCREF(Py_None);
    return Py_None;
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
    Py_INCREF(Py_None);
    return Py_None;
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySpan_getFog(pySpan* self, void*) {
    return pyKey_FromKey(self->fThis->getFogEnvironment());
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

static PyObject* pySpan_getL2W(pySpan* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getLocalToWorld());
}

static PyObject* pySpan_getW2L(pySpan* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getWorldToLocal());
}

static PyObject* pySpan_getSubType(pySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getSubType());
}

static PyObject* pySpan_getMaterial(pySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getMaterialIdx());
}

static PyObject* pySpan_getNumMatrices(pySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getNumMatrices());
}

static PyObject* pySpan_getProps(pySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getProps());
}

static PyObject* pySpan_getBaseMatrix(pySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getBaseMatrix());
}

static PyObject* pySpan_getMaxBoneIdx(pySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getMaxBoneIdx());
}

static PyObject* pySpan_getPenBoneIdx(pySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getPenBoneIdx());
}

static PyObject* pySpan_getLocalUVWChans(pySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getLocalUVWChans());
}

static PyObject* pySpan_getMinDist(pySpan* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMinDist());
}

static PyObject* pySpan_getMaxDist(pySpan* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMaxDist());
}

static PyObject* pySpan_getWaterHeight(pySpan* self, void*) {
    return PyFloat_FromDouble(self->fThis->getWaterHeight());
}

static PyObject* pySpan_getLocalBounds(pySpan* self, void*) {
    return pyBounds3Ext_FromBounds3Ext(self->fThis->getLocalBounds());
}

static PyObject* pySpan_getWorldBounds(pySpan* self, void*) {
    return pyBounds3Ext_FromBounds3Ext(self->fThis->getWorldBounds());
}

static int pySpan_setFog(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fog should be a plKey");
        return -1;
    }
    self->fThis->setFogEnvironment(*((pyKey*)value)->fThis);
    return 0;
}

static int pySpan_setLights(pySpan* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Lights, use addPermaLight and addPermaProj");
    return -1;
}

static int pySpan_setL2W(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "localToWorld should be an hsMatrix44");
        return -1;
    }
    self->fThis->setLocalToWorld(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pySpan_setW2L(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "worldToLocal should be an hsMatrix44");
        return -1;
    }
    self->fThis->setWorldToLocal(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pySpan_setSubType(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "subType should be an int");
        return -1;
    }
    self->fThis->setSubType(PyInt_AsLong(value));
    return 0;
}

static int pySpan_setMaterial(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "materialIdx should be an int");
        return -1;
    }
    self->fThis->setMaterialIdx(PyInt_AsLong(value));
    return 0;
}

static int pySpan_setNumMatrices(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "numMatrices should be an int");
        return -1;
    }
    self->fThis->setNumMatrices(PyInt_AsLong(value));
    return 0;
}

static int pySpan_setProps(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "props should be an int");
        return -1;
    }
    self->fThis->setProps(PyInt_AsLong(value));
    return 0;
}

static int pySpan_setBaseMatrix(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "baseMatrix should be an int");
        return -1;
    }
    self->fThis->setBaseMatrix(PyInt_AsLong(value));
    return 0;
}

static int pySpan_setMaxBoneIdx(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxBoneIdx should be an int");
        return -1;
    }
    self->fThis->setMaxBoneIdx(PyInt_AsLong(value));
    return 0;
}

static int pySpan_setPenBoneIdx(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "penBoneIdx should be an int");
        return -1;
    }
    self->fThis->setPenBoneIdx(PyInt_AsLong(value));
    return 0;
}

static int pySpan_setLocalUVWChans(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "localUVWChans should be an int");
        return -1;
    }
    self->fThis->setLocalUVWChans(PyInt_AsLong(value));
    return 0;
}

static int pySpan_setMinDist(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "minDist should be an int");
        return -1;
    }
    self->fThis->setMinDist(PyFloat_AsDouble(value));
    return 0;
}

static int pySpan_setMaxDist(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxDist should be an int");
        return -1;
    }
    self->fThis->setMaxDist(PyFloat_AsDouble(value));
    return 0;
}

static int pySpan_setWaterHeight(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "waterHeight should be an int");
        return -1;
    }
    self->fThis->setWaterHeight(PyFloat_AsDouble(value));
    return 0;
}

static int pySpan_setLocalBounds(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !pyBounds3Ext_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "localBounds should be an hsBounds3Ext");
        return -1;
    }
    self->fThis->setLocalBounds(*((pyBounds3Ext*)value)->fThis);
    return 0;
}

static int pySpan_setWorldBounds(pySpan* self, PyObject* value, void*) {
    if (value == NULL || !pyBounds3Ext_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "worldBounds should be an hsBounds3Ext");
        return -1;
    }
    self->fThis->setWorldBounds(*((pyBounds3Ext*)value)->fThis);
    return 0;
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

static PyGetSetDef pySpan_GetSet[] = {
    { _pycs("fog"), (getter)pySpan_getFog, (setter)pySpan_setFog,
        _pycs("Fog Environment key"), NULL },
    { _pycs("permaLights"), (getter)pySpan_getLights,
        (setter)pySpan_setLights, NULL, NULL },
    { _pycs("permaProjs"), (getter)pySpan_getProjs,
        (setter)pySpan_setLights, NULL, NULL },
    { _pycs("localToWorld"), (getter)pySpan_getL2W,
        (setter)pySpan_setL2W, NULL, NULL },
    { _pycs("worldToLocal"), (getter)pySpan_getW2L,
        (setter)pySpan_setW2L, NULL, NULL },
    { _pycs("subType"), (getter)pySpan_getSubType,
        (setter)pySpan_setSubType, NULL, NULL },
    { _pycs("materialIdx"), (getter)pySpan_getMaterial, (setter)pySpan_setMaterial,
        _pycs("Index of the material from the DrawableSpans to use"), NULL },
    { _pycs("numMatrices"), (getter)pySpan_getNumMatrices,
        (setter)pySpan_setNumMatrices, NULL, NULL },
    { _pycs("props"), (getter)pySpan_getProps, (setter)pySpan_setProps, NULL, NULL },
    { _pycs("baseMatrix"), (getter)pySpan_getBaseMatrix,
        (setter)pySpan_setBaseMatrix, NULL, NULL },
    { _pycs("maxBoneIdx"), (getter)pySpan_getMaxBoneIdx,
        (setter)pySpan_setMaxBoneIdx, NULL, NULL },
    { _pycs("penBoneIdx"), (getter)pySpan_getPenBoneIdx,
        (setter)pySpan_setPenBoneIdx, NULL, NULL },
    { _pycs("localUVWChans"), (getter)pySpan_getLocalUVWChans,
        (setter)pySpan_setLocalUVWChans, NULL, NULL },
    { _pycs("minDist"), (getter)pySpan_getMinDist, (setter)pySpan_setMinDist,
        NULL, NULL },
    { _pycs("maxDist"), (getter)pySpan_getMaxDist, (setter)pySpan_setMaxDist,
        NULL, NULL },
    { _pycs("waterHeight"), (getter)pySpan_getWaterHeight,
        (setter)pySpan_setWaterHeight, NULL, NULL },
    { _pycs("localBounds"), (getter)pySpan_getLocalBounds,
        (setter)pySpan_setLocalBounds, NULL, NULL },
    { _pycs("worldBounds"), (getter)pySpan_getWorldBounds,
        (setter)pySpan_setWorldBounds, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySpan_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSpan",                /* tp_name */
    sizeof(pySpan),                     /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pySpan_dealloc,         /* tp_dealloc */
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

    (initproc)pySpan___init__,          /* tp_init */
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

int pySpan_Check(PyObject* obj) {
    if (obj->ob_type == &pySpan_Type
        || PyType_IsSubtype(obj->ob_type, &pySpan_Type))
        return 1;
    return 0;
}

PyObject* pySpan_FromSpan(plSpan* span) {
    if (span == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySpan* obj = PyObject_New(pySpan, &pySpan_Type);
    obj->fThis = span;
    obj->fPyOwned = false;
    return (PyObject*)obj;
}

}
