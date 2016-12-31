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

#include "pyWaveSet.h"

#include <PRP/Surface/plWaveSet.h>
#include "pyFixedWaterState7.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_NEW(WaveSet7, plWaveSet7)

static PyObject* pyWaveSet7_addShore(pyWaveSet7* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addShore expects a plKey");
        return NULL;
    }
    self->fThis->addShore(*key->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyWaveSet7_clearShores(pyWaveSet7* self) {
    self->fThis->clearShores();
    Py_RETURN_NONE;
}

static PyObject* pyWaveSet7_delShore(pyWaveSet7* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delShore expects an int");
        return NULL;
    }
    if (size_t(idx) >= self->fThis->getShores().size()) {
        PyErr_SetNone(PyExc_IndexError);
        return NULL;
    }
    self->fThis->delShore(idx);
    Py_RETURN_NONE;
}

static PyObject* pyWaveSet7_addDecal(pyWaveSet7* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addDecal expects a plKey");
        return NULL;
    }
    self->fThis->addDecal(*key->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyWaveSet7_clearDecals(pyWaveSet7* self) {
    self->fThis->clearDecals();
    Py_RETURN_NONE;
}

static PyObject* pyWaveSet7_delDecal(pyWaveSet7* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delDecal expects an int");
        return NULL;
    }
    if (size_t(idx) >= self->fThis->getDecals().size()) {
        PyErr_SetNone(PyExc_IndexError);
        return NULL;
    }
    self->fThis->delDecal(idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyWaveSet7_Methods[] = {
    { "addShore", (PyCFunction)pyWaveSet7_addShore, METH_VARARGS,
      "Params: key\n"
      "Add a shore" },
    { "clearShores", (PyCFunction)pyWaveSet7_clearShores, METH_NOARGS,
      "Remove all shores" },
    { "delShore", (PyCFunction)pyWaveSet7_delShore, METH_VARARGS,
      "Params: idx\n"
      "Remove a shore" },
    { "addDecal", (PyCFunction)pyWaveSet7_addDecal, METH_VARARGS,
      "Params: key\n"
      "Add a decal" },
    { "clearDecals", (PyCFunction)pyWaveSet7_clearDecals, METH_NOARGS,
      "Remove all decals" },
    { "delDecal", (PyCFunction)pyWaveSet7_delDecal, METH_VARARGS,
      "Params: idx\n"
      "Remove a decal" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pyWaveSet7_getShores(pyWaveSet7* self, void*) {
    const std::vector<plKey>& shores = self->fThis->getShores();
    PyObject* tuple = PyTuple_New(shores.size());
    for (size_t i = 0; i < shores.size(); ++i)
        PyTuple_SET_ITEM(tuple, i, pyKey_FromKey(shores[i]));
    return tuple;
}

static PyObject* pyWaveSet7_getDecals(pyWaveSet7* self, void*) {
    const std::vector<plKey>& decals = self->fThis->getDecals();
    PyObject* tuple = PyTuple_New(decals.size());
    for (size_t i = 0; i < decals.size(); ++i)
        PyTuple_SET_ITEM(tuple, i, pyKey_FromKey(decals[i]));
    return tuple;
}

static int pyWaveSet7_setShores(pyWaveSet7* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add shores, use addShore");
    return -1;
}

static int pyWaveSet7_setDecals(pyWaveSet7* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add decals, use addDecal");
    return -1;
}

PY_PROPERTY_PROXY(plFixedWaterState7, WaveSet7, state, getState)
PY_PROPERTY(float, WaveSet7, maxLen, getMaxLen, setMaxLen)
PY_PROPERTY(plKey, WaveSet7, envMap, getEnvMap, setEnvMap)
PY_PROPERTY(plKey, WaveSet7, refObj, getRefObj, setRefObj)

static PyGetSetDef pyWaveSet7_GetSet[] = {
    pyWaveSet7_state_getset,
    { _pycs("shores"), (getter)pyWaveSet7_getShores, (setter)pyWaveSet7_setShores, NULL, NULL },
    { _pycs("decals"), (getter)pyWaveSet7_getDecals, (setter)pyWaveSet7_setDecals, NULL, NULL },
    pyWaveSet7_maxLen_getset,
    pyWaveSet7_envMap_getset,
    pyWaveSet7_refObj_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyWaveSet7_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plWaveSet7",            /* tp_name */
    sizeof(pyWaveSet7),                 /* tp_basicsize */
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
    "plWaveSet7 wrapper",                     /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyWaveSet7_Methods,                 /* tp_methods */
    NULL,                               /* tp_members */
    pyWaveSet7_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyWaveSet7_new,                     /* tp_new */
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

PyObject* Init_pyWaveSet7_Type() {
    pyWaveSet7_Type.tp_base = &pyWaveSetBase_Type;
    if (PyType_Ready(&pyWaveSet7_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyWaveSet7_Type.tp_dict, "kHasRefObject",
                         PyInt_FromLong(plWaveSet7::kHasRefObject));

    Py_INCREF(&pyWaveSet7_Type);
    return (PyObject*)&pyWaveSet7_Type;
}

PY_PLASMA_IFC_METHODS(WaveSet7, plWaveSet7)

}
