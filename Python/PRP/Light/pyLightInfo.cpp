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
#include <PRP/Light/plLightInfo.h>
#include "pyLightInfo.h"
#include "PRP/Object/pyObjInterface.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"
#include "Sys/pyColor.h"
#include "Math/pyMatrix.h"

extern "C" {

static PyObject* pyLightInfo_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plLightInfo is abstract");
    return NULL;
}

static PyObject* pyLightInfo_clearVisRegions(pyLightInfo* self) {
    plLightInfo::Convert(IConvert((pyCreatable*)self))->clearVisRegions();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLightInfo_addVisRegion(pyLightInfo* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addVisRegion expects a plKey");
        return NULL;
    }
    plLightInfo::Convert(IConvert((pyCreatable*)self))->addVisRegion(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLightInfo_getAmbient(pyLightInfo* self, void*) {
    return pyColorRGBA_FromColorRGBA(plLightInfo::Convert(IConvert((pyCreatable*)self))->getAmbient());
}

static PyObject* pyLightInfo_getDiffuse(pyLightInfo* self, void*) {
    return pyColorRGBA_FromColorRGBA(plLightInfo::Convert(IConvert((pyCreatable*)self))->getDiffuse());
}

static PyObject* pyLightInfo_getSpecular(pyLightInfo* self, void*) {
    return pyColorRGBA_FromColorRGBA(plLightInfo::Convert(IConvert((pyCreatable*)self))->getSpecular());
}

static PyObject* pyLightInfo_getLight2Loc(pyLightInfo* self, void*) {
    return pyMatrix44_FromMatrix44(plLightInfo::Convert(IConvert((pyCreatable*)self))->getLightToLocal());
}

static PyObject* pyLightInfo_getLoc2Light(pyLightInfo* self, void*) {
    return pyMatrix44_FromMatrix44(plLightInfo::Convert(IConvert((pyCreatable*)self))->getLocalToLight());
}

static PyObject* pyLightInfo_getL2W(pyLightInfo* self, void*) {
    return pyMatrix44_FromMatrix44(plLightInfo::Convert(IConvert((pyCreatable*)self))->getLightToWorld());
}

static PyObject* pyLightInfo_getW2L(pyLightInfo* self, void*) {
    return pyMatrix44_FromMatrix44(plLightInfo::Convert(IConvert((pyCreatable*)self))->getWorldToLight());
}

static PyObject* pyLightInfo_getProj(pyLightInfo* self, void*) {
    return pyKey_FromKey(plLightInfo::Convert(IConvert((pyCreatable*)self))->getProjection());
}

static PyObject* pyLightInfo_getSVol(pyLightInfo* self, void*) {
    return pyKey_FromKey(plLightInfo::Convert(IConvert((pyCreatable*)self))->getSoftVolume());
}

static PyObject* pyLightInfo_getNode(pyLightInfo* self, void*) {
    return pyKey_FromKey(plLightInfo::Convert(IConvert((pyCreatable*)self))->getSceneNode());
}

static PyObject* pyLightInfo_getVisRegions(pyLightInfo* self, void*) {
    PyObject* list = PyList_New(plLightInfo::Convert(IConvert((pyCreatable*)self))->getVisRegions().getSize());
    for (size_t i=0; i<plLightInfo::Convert(IConvert((pyCreatable*)self))->getVisRegions().getSize(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(plLightInfo::Convert(IConvert((pyCreatable*)self))->getVisRegions()[i]));
    return list;
}

static int pyLightInfo_setAmbient(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ambient should be an hsColorRGBA");
        return -1;
    }
    plLightInfo::Convert(IConvert((pyCreatable*)self))->setAmbient(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLightInfo_setDiffuse(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "diffuse should be an hsColorRGBA");
        return -1;
    }
    plLightInfo::Convert(IConvert((pyCreatable*)self))->setDiffuse(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLightInfo_setSpecular(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "specular should be an hsColorRGBA");
        return -1;
    }
    plLightInfo::Convert(IConvert((pyCreatable*)self))->setSpecular(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLightInfo_setLight2Loc(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "lightToLocal should be an hsMatrix44");
        return -1;
    }
    plLightInfo::Convert(IConvert((pyCreatable*)self))->setLightToLocal(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLightInfo_setLoc2Light(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "localToLight should be an hsMatrix44");
        return -1;
    }
    plLightInfo::Convert(IConvert((pyCreatable*)self))->setLocalToLight(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLightInfo_setL2W(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "lightToWorld should be an hsMatrix44");
        return -1;
    }
    plLightInfo::Convert(IConvert((pyCreatable*)self))->setLightToWorld(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLightInfo_setW2L(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "worldToLight should be an hsMatrix44");
        return -1;
    }
    plLightInfo::Convert(IConvert((pyCreatable*)self))->setWorldToLight(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLightInfo_setProj(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        plLightInfo::Convert(IConvert((pyCreatable*)self))->setProjection(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "projection should be a plKey");
        return -1;
    }
    plLightInfo::Convert(IConvert((pyCreatable*)self))->setProjection(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLightInfo_setSVol(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        plLightInfo::Convert(IConvert((pyCreatable*)self))->setSoftVolume(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "softVolume should be a plKey");
        return -1;
    }
    plLightInfo::Convert(IConvert((pyCreatable*)self))->setSoftVolume(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLightInfo_setNode(pyLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "sceneNode should be a plKey");
        return -1;
    }
    plLightInfo::Convert(IConvert((pyCreatable*)self))->setSceneNode(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLightInfo_setVisRegions(pyLightInfo* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Vis Regions, use addVisRegion()");
    return -1;
}

static PyMethodDef pyLightInfo_Methods[] = {
    { "clearVisRegions", (PyCFunction)pyLightInfo_clearVisRegions, METH_NOARGS,
      "Remove all VisRegions from the light" },
    { "addVisRegion", (PyCFunction)pyLightInfo_addVisRegion, METH_VARARGS,
      "Params: regionKey\n"
      "Add a VisRegion to the light" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLightInfo_GetSet[] = {
    { _pycs("ambient"), (getter)pyLightInfo_getAmbient,
        (setter)pyLightInfo_setAmbient, NULL, NULL },
    { _pycs("diffuse"), (getter)pyLightInfo_getDiffuse,
        (setter)pyLightInfo_setDiffuse, NULL, NULL },
    { _pycs("specular"), (getter)pyLightInfo_getSpecular,
        (setter)pyLightInfo_setSpecular, NULL, NULL },
    { _pycs("lightToLocal"), (getter)pyLightInfo_getLight2Loc,
        (setter)pyLightInfo_setLight2Loc, NULL, NULL },
    { _pycs("localToLight"), (getter)pyLightInfo_getLoc2Light,
        (setter)pyLightInfo_setLoc2Light, NULL, NULL },
    { _pycs("lightToWorld"), (getter)pyLightInfo_getL2W,
        (setter)pyLightInfo_setL2W, NULL, NULL },
    { _pycs("worldToLight"), (getter)pyLightInfo_getW2L,
        (setter)pyLightInfo_setW2L, NULL, NULL },
    { _pycs("projection"), (getter)pyLightInfo_getProj,
        (setter)pyLightInfo_setProj, NULL, NULL },
    { _pycs("softVolume"), (getter)pyLightInfo_getSVol,
        (setter)pyLightInfo_setSVol, NULL, NULL },
    { _pycs("sceneNode"), (getter)pyLightInfo_getNode,
        (setter)pyLightInfo_setNode, NULL, NULL },
    { _pycs("visRegions"), (getter)pyLightInfo_getVisRegions,
        (setter)pyLightInfo_setVisRegions, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLightInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
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

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
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
