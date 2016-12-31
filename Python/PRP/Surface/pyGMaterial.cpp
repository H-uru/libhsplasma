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

#include "pyGMaterial.h"

#include <PRP/Surface/hsGMaterial.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Object/pySynchedObject.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(GMaterial, hsGMaterial)

static PyObject* pyGMaterial_clearLayers(pyGMaterial* self) {
    self->fThis->clearLayers();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGMaterial_addLayer(pyGMaterial* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addLayer expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addLayer expects a plKey");
        return NULL;
    }
    self->fThis->addLayer(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGMaterial_delLayer(pyGMaterial* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delLayer expects an int");
        return NULL;
    }
    self->fThis->delLayer(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGMaterial_clearPBs(pyGMaterial* self) {
    self->fThis->clearPiggyBacks();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGMaterial_addPB(pyGMaterial* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addPiggyBack expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addPiggyBack expects a plKey");
        return NULL;
    }
    self->fThis->addPiggyBack(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGMaterial_delPB(pyGMaterial* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPiggyBack expects an int");
        return NULL;
    }
    self->fThis->delPiggyBack(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGMaterial_getLayers(pyGMaterial* self, void*) {
    PyObject* list = PyList_New(self->fThis->getLayers().size());
    for (size_t i=0; i<self->fThis->getLayers().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getLayers()[i]));
    return list;
}

static PyObject* pyGMaterial_getPBs(pyGMaterial* self, void*) {
    PyObject* list = PyList_New(self->fThis->getPiggyBacks().size());
    for (size_t i=0; i<self->fThis->getPiggyBacks().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getPiggyBacks()[i]));
    return list;
}

static int pyGMaterial_setLayers(pyGMaterial* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add layers, use addLayer()");
    return -1;
}

static int pyGMaterial_setPBs(pyGMaterial* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add piggy-backs, use addPiggyBack()");
    return -1;
}

static PyMethodDef pyGMaterial_Methods[] = {
    { "clearLayers", (PyCFunction)pyGMaterial_clearLayers, METH_NOARGS,
      "Remove all layer keys from the material" },
    { "addLayer", (PyCFunction)pyGMaterial_addLayer, METH_VARARGS,
      "Params: key\n"
      "Add a layer to the material" },
    { "delLayer", (PyCFunction)pyGMaterial_delLayer, METH_VARARGS,
      "Params: idx\n"
      "Remove a layer from the material" },
    { "clearPiggyBacks", (PyCFunction)pyGMaterial_clearPBs, METH_NOARGS,
      "Remove all piggy back keys from the material" },
    { "addPiggyBack", (PyCFunction)pyGMaterial_addPB, METH_VARARGS,
      "Params: key\n"
      "Add a piggy back to the material" },
    { "delPiggyBack", (PyCFunction)pyGMaterial_delPB, METH_VARARGS,
      "Params: idx\n"
      "Remove a piggy back from the material" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(unsigned int, GMaterial, compFlags, getCompFlags, setCompFlags)
PY_PROPERTY(unsigned int, GMaterial, loadFlags, getLoadFlags, setLoadFlags)

static PyGetSetDef pyGMaterial_GetSet[] = {
    { _pycs("layers"), (getter)pyGMaterial_getLayers,
        (setter)pyGMaterial_setLayers, NULL, NULL },
    { _pycs("piggyBacks"), (getter)pyGMaterial_getPBs,
        (setter)pyGMaterial_setPBs, NULL, NULL },
    pyGMaterial_compFlags_getset,
    pyGMaterial_loadFlags_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyGMaterial_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsGMaterial",           /* tp_name */
    sizeof(pyGMaterial),                /* tp_basicsize */
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
    "hsGMaterial wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyGMaterial_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyGMaterial_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyGMaterial_new,                    /* tp_new */
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

PyObject* Init_pyGMaterial_Type() {
    pyGMaterial_Type.tp_base = &pySynchedObject_Type;
    if (PyType_Ready(&pyGMaterial_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompShaded",
                         PyInt_FromLong(hsGMaterial::kCompShaded));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompEnvironMap",
                         PyInt_FromLong(hsGMaterial::kCompEnvironMap));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompProjectOnto",
                         PyInt_FromLong(hsGMaterial::kCompProjectOnto));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompSoftShadow",
                         PyInt_FromLong(hsGMaterial::kCompSoftShadow));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompSpecular",
                         PyInt_FromLong(hsGMaterial::kCompSpecular));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompTwoSided",
                         PyInt_FromLong(hsGMaterial::kCompTwoSided));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompDrawAsSplats",
                         PyInt_FromLong(hsGMaterial::kCompDrawAsSplats));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompAdjusted",
                         PyInt_FromLong(hsGMaterial::kCompAdjusted));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompNoSoftShadow",
                         PyInt_FromLong(hsGMaterial::kCompNoSoftShadow));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompDynamic",
                         PyInt_FromLong(hsGMaterial::kCompDynamic));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompDecal",
                         PyInt_FromLong(hsGMaterial::kCompDecal));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompIsEmissive",
                         PyInt_FromLong(hsGMaterial::kCompIsEmissive));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompIsLightMapped",
                         PyInt_FromLong(hsGMaterial::kCompIsLightMapped));
    PyDict_SetItemString(pyGMaterial_Type.tp_dict, "kCompNeedsBlendChannel",
                         PyInt_FromLong(hsGMaterial::kCompNeedsBlendChannel));

    Py_INCREF(&pyGMaterial_Type);
    return (PyObject*)&pyGMaterial_Type;
}

PY_PLASMA_IFC_METHODS(GMaterial, hsGMaterial)

}
