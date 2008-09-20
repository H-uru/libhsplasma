#include <Python.h>
#include <PRP/Light/plLightInfo.h>
#include "pyLightInfo.h"
#include "../Object/pyObjInterface.h"
#include "../KeyedObject/pyKey.h"
#include "../pyCreatable.h"
#include "../../Sys/pyColor.h"
#include "../../Math/pyMatrix44.h"

extern "C" {

static PyObject* pyLightInfo_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plLightInfo is abstract");
    return NULL;
}

static PyObject* pyLightInfo_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyLightInfo_FromLightInfo(plLightInfo::Convert(cre->fThis));
}

static PyObject* pyLightInfo_clearVisRegions(pyLightInfo* self) {
    self->fThis->clearVisRegions();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLightInfo_addVisRegion(pyLightInfo* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addVisRegion expects a plKey");
        return NULL;
    }
    self->fThis->addVisRegion(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLightInfo_getAmbient(pyLightInfo* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getAmbient());
}

static PyObject* pyLightInfo_getDiffuse(pyLightInfo* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getDiffuse());
}

static PyObject* pyLightInfo_getSpecular(pyLightInfo* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getSpecular());
}

static PyObject* pyLightInfo_getLight2Loc(pyLightInfo* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getLightToLocal());
}

static PyObject* pyLightInfo_getLoc2Light(pyLightInfo* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getLocalToLight());
}

static PyObject* pyLightInfo_getL2W(pyLightInfo* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getLightToWorld());
}

static PyObject* pyLightInfo_getW2L(pyLightInfo* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getWorldToLight());
}

static PyObject* pyLightInfo_getProj(pyLightInfo* self, void*) {
    return pyKey_FromKey(self->fThis->getProjection());
}

static PyObject* pyLightInfo_getSVol(pyLightInfo* self, void*) {
    return pyKey_FromKey(self->fThis->getSoftVolume());
}

static PyObject* pyLightInfo_getNode(pyLightInfo* self, void*) {
    return pyKey_FromKey(self->fThis->getSceneNode());
}

static PyObject* pyLightInfo_getVisRegions(pyLightInfo* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumVisRegions());
    for (size_t i=0; i<self->fThis->getNumVisRegions(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getVisRegion(i)));
    return list;
}

static int pyLightInfo_setAmbient(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ambient should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setAmbient(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLightInfo_setDiffuse(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "diffuse should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setDiffuse(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLightInfo_setSpecular(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "specular should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setSpecular(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLightInfo_setLight2Loc(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "lightToLocal should be an hsMatrix44");
        return -1;
    }
    self->fThis->setLightToLocal(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLightInfo_setLoc2Light(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "localToLight should be an hsMatrix44");
        return -1;
    }
    self->fThis->setLocalToLight(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLightInfo_setL2W(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "lightToWorld should be an hsMatrix44");
        return -1;
    }
    self->fThis->setLightToWorld(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLightInfo_setW2L(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "worldToLight should be an hsMatrix44");
        return -1;
    }
    self->fThis->setWorldToLight(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLightInfo_setProj(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setProjection(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "projection should be a plKey");
        return -1;
    }
    self->fThis->setProjection(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLightInfo_setSVol(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setSoftVolume(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "softVolume should be a plKey");
        return -1;
    }
    self->fThis->setSoftVolume(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLightInfo_setNode(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "sceneNode should be a plKey");
        return -1;
    }
    self->fThis->setSceneNode(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLightInfo_setVisRegions(pyLightInfo* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Vis Regions, use addVisRegion()");
    return -1;
}

static PyMethodDef pyLightInfo_Methods[] = {
    { "Convert", (PyCFunction)pyLightInfo_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plLightInfo" },
    { "clearVisRegions", (PyCFunction)pyLightInfo_clearVisRegions, METH_NOARGS,
      "Remove all VisRegions from the light" },
    { "addVisRegion", (PyCFunction)pyLightInfo_addVisRegion, METH_VARARGS,
      "Params: regionKey\n"
      "Add a VisRegion to the light" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLightInfo_GetSet[] = {
    { "ambient", (getter)pyLightInfo_getAmbient, (setter)pyLightInfo_setAmbient, NULL, NULL },
    { "diffuse", (getter)pyLightInfo_getDiffuse, (setter)pyLightInfo_setDiffuse, NULL, NULL },
    { "specular", (getter)pyLightInfo_getSpecular, (setter)pyLightInfo_setSpecular, NULL, NULL },
    { "lightToLocal", (getter)pyLightInfo_getLight2Loc, (setter)pyLightInfo_setLight2Loc, NULL, NULL },
    { "localToLight", (getter)pyLightInfo_getLoc2Light, (setter)pyLightInfo_setLoc2Light, NULL, NULL },
    { "lightToWorld", (getter)pyLightInfo_getL2W, (setter)pyLightInfo_setL2W, NULL, NULL },
    { "worldToLight", (getter)pyLightInfo_getW2L, (setter)pyLightInfo_setW2L, NULL, NULL },
    { "projection", (getter)pyLightInfo_getProj, (setter)pyLightInfo_setProj, NULL, NULL },
    { "softVolume", (getter)pyLightInfo_getSVol, (setter)pyLightInfo_setSVol, NULL, NULL },
    { "sceneNode", (getter)pyLightInfo_getNode, (setter)pyLightInfo_setNode, NULL, NULL },
    { "visRegions", (getter)pyLightInfo_getVisRegions, (setter)pyLightInfo_setVisRegions, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLightInfo_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plLightInfo",             /* tp_name */
    sizeof(pyLightInfo),                /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plLightInfo wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLightInfo_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyLightInfo_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLightInfo_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyLightInfo_Type() {
    pyLightInfo_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyLightInfo_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyLightInfo_Type.tp_dict, "kLPObsolete",
                         PyInt_FromLong(plLightInfo::kLPObsolete));
    PyDict_SetItemString(pyLightInfo_Type.tp_dict, "kLPCastShadows",
                         PyInt_FromLong(plLightInfo::kLPCastShadows));
    PyDict_SetItemString(pyLightInfo_Type.tp_dict, "kLPMovable",
                         PyInt_FromLong(plLightInfo::kLPMovable));
    PyDict_SetItemString(pyLightInfo_Type.tp_dict, "kLPHasIncludes",
                         PyInt_FromLong(plLightInfo::kLPHasIncludes));
    PyDict_SetItemString(pyLightInfo_Type.tp_dict, "kLPIncludesChars",
                         PyInt_FromLong(plLightInfo::kLPIncludesChars));
    PyDict_SetItemString(pyLightInfo_Type.tp_dict, "kLPOverAll",
                         PyInt_FromLong(plLightInfo::kLPOverAll));
    PyDict_SetItemString(pyLightInfo_Type.tp_dict, "kLPHasSpecular",
                         PyInt_FromLong(plLightInfo::kLPHasSpecular));
    PyDict_SetItemString(pyLightInfo_Type.tp_dict, "kLPShadowOnly",
                         PyInt_FromLong(plLightInfo::kLPShadowOnly));
    PyDict_SetItemString(pyLightInfo_Type.tp_dict, "kLPShadowLightGroup",
                         PyInt_FromLong(plLightInfo::kLPShadowLightGroup));
    PyDict_SetItemString(pyLightInfo_Type.tp_dict, "kLPForceProj",
                         PyInt_FromLong(plLightInfo::kLPForceProj));

    Py_INCREF(&pyLightInfo_Type);
    return (PyObject*)&pyLightInfo_Type;
}

int pyLightInfo_Check(PyObject* obj) {
    if (obj->ob_type == &pyLightInfo_Type
        || PyType_IsSubtype(obj->ob_type, &pyLightInfo_Type))
        return 1;
    return 0;
}

PyObject* pyLightInfo_FromLightInfo(class plLightInfo* light) {
    if (light == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLightInfo* pyLight = PyObject_New(pyLightInfo, &pyLightInfo_Type);
    pyLight->fThis = light;
    pyLight->fPyOwned = false;
    return (PyObject*)pyLight;
}

}
