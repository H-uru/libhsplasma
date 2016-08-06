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

#include "pyDynamicEnvMap.h"

#include <PRP/Surface/plDynamicEnvMap.h>
#include "pyRenderTarget.h"
#include "PRP/pyCreatable.h"
#include "PRP/Surface/pyBitmap.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Object/pySynchedObject.h"
#include "Math/pyGeometry3.h"
#include "Sys/pyColor.h"

extern "C" {

// DynamicEnvMap

static PyObject* pyDynamicEnvMap_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyDynamicEnvMap* self = (pyDynamicEnvMap*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plDynamicEnvMap();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyDynamicEnvMap_getRootNode(pyDynamicEnvMap* self, void*) {
    return pyKey_FromKey(self->fThis->getRootNode());
}

static PyObject* pyDynamicEnvMap_getPosition(pyDynamicEnvMap* self, void*) {
    return pyVector3_FromVector3(self->fThis->getPosition());
}

static PyObject* pyDynamicEnvMap_getHither(pyDynamicEnvMap* self, void*) {
    return PyFloat_FromDouble(self->fThis->getHither());
}

static PyObject* pyDynamicEnvMap_getYon(pyDynamicEnvMap* self, void*) {
    return PyFloat_FromDouble(self->fThis->getYon());
}

static PyObject* pyDynamicEnvMap_getFogStart(pyDynamicEnvMap* self, void*) {
    return PyFloat_FromDouble(self->fThis->getFogStart());
}

static PyObject* pyDynamicEnvMap_getColor(pyDynamicEnvMap* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getColor());
}

static PyObject* pyDynamicEnvMap_getRefreshRate(pyDynamicEnvMap* self, void*) {
    return PyFloat_FromDouble(self->fThis->getRefreshRate());
}

static PyObject* pyDynamicEnvMap_getVisRegions(pyDynamicEnvMap* self, void*) {
    const std::vector<plKey>& keys = self->fThis->getVisRegions();
    PyObject* regionList = PyList_New(keys.size());
    for (size_t i=0; i<keys.size(); i++)
        PyList_SET_ITEM(regionList, i, pyKey_FromKey(keys[i]));
    return regionList;
}

static PyObject* pyDynamicEnvMap_getVisRegionNames(pyDynamicEnvMap* self, void*) {
    const std::vector<plString>& names = self->fThis->getVisRegionNames();
    PyObject* regionNameList = PyList_New(names.size());
    for (size_t i=0; i<names.size(); i++)
        PyList_SET_ITEM(regionNameList, i, PlasmaString_To_PyString(names[i]));
    return regionNameList;
}

static PyObject* pyDynamicEnvMap_getIncCharacters(pyDynamicEnvMap* self, void*) {
    return PyBool_FromLong(self->fThis->getIncludeCharacters() ? 1 : 0);
}

static int pyDynamicEnvMap_setRootNode(pyDynamicEnvMap* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setRootNode(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setRootNode(*reinterpret_cast<pyKey *>(value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "rootNode should be a plKey");
        return -1;
    }
}

static int pyDynamicEnvMap_setPosition(pyDynamicEnvMap* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "position should be a plVector3");
        return -1;
    }
    self->fThis->setPosition(*reinterpret_cast<pyVector3 *>(value)->fThis);
    return 0;
}

static int pyDynamicEnvMap_setHither(pyDynamicEnvMap* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "hither should be a float");
        return -1;
    }
    self->fThis->setHither(PyFloat_AsDouble(value));
    return 0;
}

static int pyDynamicEnvMap_setYon(pyDynamicEnvMap* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "yon should be a float");
        return -1;
    }
    self->fThis->setYon(PyFloat_AsDouble(value));
    return 0;
}

static int pyDynamicEnvMap_setFogStart(pyDynamicEnvMap* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fogStart should be a float");
        return -1;
    }
    self->fThis->setFogStart(PyFloat_AsDouble(value));
    return 0;
}

static int pyDynamicEnvMap_setColor(pyDynamicEnvMap* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "color should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setColor(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyDynamicEnvMap_setRefreshRate(pyDynamicEnvMap* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "refreshRate should be a float");
        return -1;
    }
    self->fThis->setRefreshRate(PyFloat_AsDouble(value));
    return 0;
}

static int pyDynamicEnvMap_setVisRegions(pyDynamicEnvMap* self, PyObject* value, void*) {
    if (value == NULL || !PySequence_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "visRegions should be a sequence of plKeys");
        return -1;
    }
    std::vector<plKey> regions;
    regions.resize(PySequence_Size(value));
    for (Py_ssize_t i=0; i<PySequence_Size(value); i++) {
        PyObject* region = PySequence_GetItem(value, i);
        if (pyKey_Check(region)){
            regions[i] = *(reinterpret_cast<pyKey *>(region)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "visRegions should be a sequence of plKeys");
            return -1;
        }
    }
    self->fThis->setVisRegions(regions);
    return 0;
}

static int pyDynamicEnvMap_setVisRegionNames(pyDynamicEnvMap* self, PyObject* value, void*) {
    if (value == NULL || !PySequence_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "visRegionNames should be a sequence of strings");
        return -1;
    }
    std::vector<plString> names;
    names.resize(PySequence_Size(value));
    for (Py_ssize_t i=0; i<PySequence_Size(value); i++) {
        PyObject* name = PySequence_GetItem(value, i);
        if (PyAnyStr_Check(name)) {
            names[i] = PyString_To_PlasmaString(name);
        } else {
            PyErr_SetString(PyExc_TypeError, "visRegionNames should be a sequence of strings");
            return -1;
        }
    }
    self->fThis->setVisRegionNames(names);
    return 0;
}

static int pyDynamicEnvMap_setIncCharacters(pyDynamicEnvMap* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "incCharacters should be a boolean");
        return -1;
    }
    self->fThis->setIncludeCharacters(PyInt_AsLong(value) ? 1 : 0);
    return 0;
}

static PyGetSetDef pyDynamicEnvMap_GetSet[] = {
    { _pycs("rootNode"), (getter)pyDynamicEnvMap_getRootNode, (setter)pyDynamicEnvMap_setRootNode, NULL, NULL },
    { _pycs("position"), (getter)pyDynamicEnvMap_getPosition, (setter)pyDynamicEnvMap_setPosition, NULL, NULL },
    { _pycs("hither"), (getter)pyDynamicEnvMap_getHither, (setter)pyDynamicEnvMap_setHither, NULL, NULL },
    { _pycs("yon"), (getter)pyDynamicEnvMap_getYon, (setter)pyDynamicEnvMap_setYon, NULL, NULL },
    { _pycs("fogStart"), (getter)pyDynamicEnvMap_getFogStart, (setter)pyDynamicEnvMap_setFogStart, NULL, NULL },
    { _pycs("color"), (getter)pyDynamicEnvMap_getColor, (setter)pyDynamicEnvMap_setColor, NULL, NULL },
    { _pycs("refreshRate"), (getter)pyDynamicEnvMap_getRefreshRate, (setter)pyDynamicEnvMap_setRefreshRate, NULL, NULL },
    { _pycs("visRegions"), (getter)pyDynamicEnvMap_getVisRegions, (setter)pyDynamicEnvMap_setVisRegions, NULL, NULL },
    { _pycs("visRegionNames"), (getter)pyDynamicEnvMap_getVisRegionNames, (setter)pyDynamicEnvMap_setVisRegionNames, NULL, NULL },
    { _pycs("incCharacters"), (getter)pyDynamicEnvMap_getIncCharacters, (setter)pyDynamicEnvMap_setIncCharacters, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyDynamicEnvMap_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDynamicEnvMap",       /* tp_name */
    sizeof(pyDynamicEnvMap),            /* tp_basicsize */
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
    "plDynamicEnvMap wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyDynamicEnvMap_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDynamicEnvMap_new,                /* tp_new */
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

PyObject* Init_pyDynamicEnvMap_Type() {
    pyDynamicEnvMap_Type.tp_base = &pyCubicRenderTarget_Type;
    if (PyType_Ready(&pyDynamicEnvMap_Type) < 0)
        return NULL;

    Py_INCREF(&pyDynamicEnvMap_Type);
    return (PyObject*)&pyDynamicEnvMap_Type;
}

int pyDynamicEnvMap_Check(PyObject* obj) {
    if (obj->ob_type == &pyDynamicEnvMap_Type
        || PyType_IsSubtype(obj->ob_type, &pyDynamicEnvMap_Type))
        return 1;
    return 0;
}

PyObject* pyDynamicEnvMap_FromDynamicEnvMap(class plDynamicEnvMap* dem) {
    if (dem == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyDynamicEnvMap* pydem = PyObject_New(pyDynamicEnvMap, &pyDynamicEnvMap_Type);
    pydem->fThis = dem;
    pydem->fPyOwned = false;
    return (PyObject*)pydem;
}

}
