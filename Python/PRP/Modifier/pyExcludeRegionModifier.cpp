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

#include "pyExcludeRegionModifier.h"

#include <PRP/Modifier/plExcludeRegionModifier.h>
#include "pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_NEW(ExcludeRegionModifier, plExcludeRegionModifier)

static PyObject* pyExcludeRegionModifier_addSafePoint(pyExcludeRegionModifier* self, PyObject* args) {
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addSafePoint expects a plKey");
        return NULL;
    }
    self->fThis->addSafePoint(*((pyKey*)key)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyExcludeRegionModifier_clearSafePoints(pyExcludeRegionModifier* self) {
    self->fThis->clearSafePoints();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyExcludeRegionModifier_delSafePoint(pyExcludeRegionModifier* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delSafePoint expects an int");
        return NULL;
    }
    if (size_t(idx) >= self->fThis->getSafePoints().size()) {
        PyErr_SetNone(PyExc_IndexError);
        return NULL;
    }
    self->fThis->delSafePoint((size_t)idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyExcludeRegionModifier_Methods[] = {
    { "addSafePoint", (PyCFunction)pyExcludeRegionModifier_addSafePoint, METH_VARARGS,
      "Params: key\n"
      "Adds a safe point key" },
    { "clearSafePoints", (PyCFunction)pyExcludeRegionModifier_clearSafePoints, METH_NOARGS,
      "Removes all safe point keys" },
    { "delSafePoint", (PyCFunction)pyExcludeRegionModifier_delSafePoint, METH_VARARGS,
      "Params: idx\n"
      "Removes a safe point key" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pyExcludeRegionModifier_getSafePoints(pyExcludeRegionModifier* self, void*) {
    const std::vector<plKey>& points = self->fThis->getSafePoints();
    PyObject* tup = PyTuple_New(points.size());
    for (size_t i = 0; i < points.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyKey_FromKey(points[i]));
    return tup;
}

static int pyExcludeRegionModifier_setSafePoints(pyExcludeRegionModifier* self, PyObject*, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add safePoints, use addSafePoint()");
    return -1;
}

PY_PROPERTY(bool, ExcludeRegionModifier, seek, getSeek, setSeek)
PY_PROPERTY(float, ExcludeRegionModifier, seekTime, getSeekTime, setSeekTime)

static PyGetSetDef pyExcludeRegionModifier_GetSet[] = {
    { _pycs("safePoints"), (getter)pyExcludeRegionModifier_getSafePoints, (setter)pyExcludeRegionModifier_setSafePoints, NULL, NULL },
    pyExcludeRegionModifier_seek_getset,
    pyExcludeRegionModifier_seekTime_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyExcludeRegionModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plExcludeRegionModifier", /* tp_name */
    sizeof(pyExcludeRegionModifier),      /* tp_basicsize */
    0,                                    /* tp_itemsize */

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
    "plExcludeRegionModifier wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyExcludeRegionModifier_Methods,    /* tp_methods */
    NULL,                               /* tp_members */
    pyExcludeRegionModifier_GetSet,     /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyExcludeRegionModifier_new,        /* tp_new */
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

PyObject* Init_pyExcludeRegionModifier_Type() {
    pyExcludeRegionModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyExcludeRegionModifier_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyExcludeRegionModifier_Type.tp_dict, "kBlockCameras",
                         PyInt_FromLong(plExcludeRegionModifier::kBlockCameras));

    Py_INCREF(&pyExcludeRegionModifier_Type);
    return (PyObject*)&pyExcludeRegionModifier_Type;
}

PY_PLASMA_IFC_METHODS(ExcludeRegionModifier, plExcludeRegionModifier)

};
