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

PY_PROPERTY(plKey, DynamicEnvMap, rootNode, getRootNode, setRootNode)
PY_PROPERTY(hsVector3, DynamicEnvMap, position, getPosition, setPosition)
PY_PROPERTY(float, DynamicEnvMap, hither, getHither, setHither)
PY_PROPERTY(float, DynamicEnvMap, yon, getYon, setYon)
PY_PROPERTY(float, DynamicEnvMap, fogStart, getFogStart, setFogStart)
PY_PROPERTY(hsColorRGBA, DynamicEnvMap, color, getColor, setColor)
PY_PROPERTY(float, DynamicEnvMap, refreshRate, getRefreshRate, setRefreshRate)
PY_PROPERTY(bool, DynamicEnvMap, incCharacters, getIncludeCharacters,
            setIncludeCharacters)

static PyGetSetDef pyDynamicEnvMap_GetSet[] = {
    pyDynamicEnvMap_rootNode_getset,
    pyDynamicEnvMap_position_getset,
    pyDynamicEnvMap_hither_getset,
    pyDynamicEnvMap_yon_getset,
    pyDynamicEnvMap_fogStart_getset,
    pyDynamicEnvMap_color_getset,
    pyDynamicEnvMap_refreshRate_getset,
    { _pycs("visRegions"), (getter)pyDynamicEnvMap_getVisRegions, (setter)pyDynamicEnvMap_setVisRegions, NULL, NULL },
    { _pycs("visRegionNames"), (getter)pyDynamicEnvMap_getVisRegionNames, (setter)pyDynamicEnvMap_setVisRegionNames, NULL, NULL },
    pyDynamicEnvMap_incCharacters_getset,
    PY_GETSET_TERMINATOR
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

PY_PLASMA_IFC_METHODS(DynamicEnvMap, plDynamicEnvMap)

}
