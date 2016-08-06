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

static PyObject* pyExcludeRegionModifier_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyExcludeRegionModifier* self = (pyExcludeRegionModifier*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plExcludeRegionModifier();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

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

static PyObject* pyExcludeRegionModifier_getSeek(pyExcludeRegionModifier* self, void*) {
    return PyBool_FromLong(self->fThis->getSeek() ? 1 : 0);
}

static PyObject* pyExcludeRegionModifier_getSeekTime(pyExcludeRegionModifier* self, void*) {
    return PyFloat_FromDouble(self->fThis->getSeekTime());
}

static int pyExcludeRegionModifier_setSafePoints(pyExcludeRegionModifier* self, PyObject*, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add safePoints, use addSafePoint()");
    return -1;
}

static int pyExcludeRegionModifier_setSeek(pyExcludeRegionModifier* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "seek should be a boolean");
        return -1;
    }
    self->fThis->setSeek(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyExcludeRegionModifier_setSeekTime(pyExcludeRegionModifier* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "seek should be a float");
        return -1;
    }
    self->fThis->setSeekTime((float)PyFloat_AsDouble(value));
    return 0;
}

static PyGetSetDef pyExcludeRegionModifier_GetSet[] = {
    { _pycs("safePoints"), (getter)pyExcludeRegionModifier_getSafePoints, (setter)pyExcludeRegionModifier_setSafePoints, NULL, NULL },
    { _pycs("seek"), (getter)pyExcludeRegionModifier_getSeek, (setter)pyExcludeRegionModifier_setSeek, NULL, NULL },
    { _pycs("seekTime"), (getter)pyExcludeRegionModifier_getSeekTime, (setter)pyExcludeRegionModifier_setSeekTime, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
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

int pyExcludeRegionModifier_Check(PyObject* obj) {
    if (obj->ob_type == &pyExcludeRegionModifier_Type
        || PyType_IsSubtype(obj->ob_type, &pyExcludeRegionModifier_Type))
        return 1;
    return 0;
}

PyObject* pyExcludeRegionModifier_FromExcludeRegionModifier(class plExcludeRegionModifier* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyExcludeRegionModifier* py = PyObject_New(pyExcludeRegionModifier, &pyExcludeRegionModifier_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
