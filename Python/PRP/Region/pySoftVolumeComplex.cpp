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

#include "pySoftVolume.h"

#include <PRP/Region/plSoftVolume.h>
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pySoftVolumeComplex_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_TypeError, "plSoftVolumeComplex is abstract");
    return NULL;
}

static PyObject* pySoftVolumeComplex_addSubVolume(pySoftVolumeComplex* self, PyObject* args) {
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addSubVolume expects a plKey");
        return NULL;
    }
    self->fThis->addSubVolume(*((pyKey*)key)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySoftVolumeComplex_clearSubVolumes(pySoftVolumeComplex* self) {
    self->fThis->clearSubVolumes();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySoftVolumeComplex_delSubVolume(pySoftVolumeComplex* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delSubVolume expects an int");
        return NULL;
    }
    if (size_t(idx) >= self->fThis->getSubVolumes().size()) {
        PyErr_SetNone(PyExc_IndexError);
        return NULL;
    }
    self->fThis->delSubVolume((size_t)idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pySoftVolumeComplex_Methods[] = {
    { "addSubVolume", (PyCFunction)pySoftVolumeComplex_addSubVolume, METH_VARARGS,
      "Params: key\n"
      "Adds a softvolume key" },
    { "clearSubVolumes", (PyCFunction)pySoftVolumeComplex_clearSubVolumes, METH_NOARGS,
      "Removes all softvolumet keys" },
    { "delSubVolume", (PyCFunction)pySoftVolumeComplex_delSubVolume, METH_VARARGS,
      "Params: idx\n"
      "Removes a softvolume key" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pySoftVolumeComplex_getSubVolumes(pySoftVolumeComplex* self, void*) {
    const std::vector<plKey>& sv = self->fThis->getSubVolumes();
    PyObject* tup = PyTuple_New(sv.size());
    for (size_t i = 0; i < sv.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyKey_FromKey(sv[i]));
    return tup;
}

static int pySoftVolumeComplex_setSubVolumes(pySoftVolumeComplex*, PyObject*, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add subvolumes, use addSubVolume");
    return -1;
}

PyGetSetDef pySoftVolumeComplex_GetSet[] = {
    { _pycs("subVolumes"), (getter)pySoftVolumeComplex_getSubVolumes, (setter)pySoftVolumeComplex_setSubVolumes, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySoftVolumeComplex_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSoftVolumeComplex",   /* tp_name */
    sizeof(pySoftVolumeComplex),        /* tp_basicsize */
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
    "plSoftVolumeComplex wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySoftVolumeComplex_Methods,        /* tp_methods */
    NULL,                               /* tp_members */
    pySoftVolumeComplex_GetSet,         /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySoftVolumeComplex_new,            /* tp_new */
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

PyObject* Init_pySoftVolumeComplex_Type() {
    pySoftVolumeComplex_Type.tp_base = &pySoftVolume_Type;
    if (PyType_Ready(&pySoftVolumeComplex_Type) < 0)
        return NULL;

    Py_INCREF(&pySoftVolumeComplex_Type);
    return (PyObject*)&pySoftVolumeComplex_Type;
}

PY_PLASMA_IFC_METHODS(SoftVolumeComplex, plSoftVolumeComplex)

}
