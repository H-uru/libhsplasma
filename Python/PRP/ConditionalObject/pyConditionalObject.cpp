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
#include <PRP/ConditionalObject/plConditionalObject.h>
#include "pyConditionalObject.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"

static inline plConditionalObject* IConvertCond(pyConditionalObject* self) {
    return plConditionalObject::Convert(IConvert((pyCreatable*)self));
}

extern "C" {

static PyObject* pyConditionalObject_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plConditionalObject is abstract");
    return NULL;
}

static PyObject* pyConditionalObject_getSatisfied(pyConditionalObject* self, void*) {
    return PyBool_FromLong(IConvertCond(self)->getSatisfied() ? 1 : 0);
}

static PyObject* pyConditionalObject_getToggle(pyConditionalObject* self, void*) {
    return PyBool_FromLong(IConvertCond(self)->getToggle() ? 1 : 0);
}

static int pyConditionalObject_setSatisfied(pyConditionalObject* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "satisfied should be a boolean");
        return -1;
    }
    IConvertCond(self)->setSatisfied(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyConditionalObject_setToggle(pyConditionalObject* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "toggle should be a boolean");
        return -1;
    }
    IConvertCond(self)->setToggle(PyInt_AsLong(value) != 0);
    return 0;
}

static PyGetSetDef pyConditionalObject_GetSet[] = {
    { _pycs("satisfied"), (getter)pyConditionalObject_getSatisfied,
       (setter)pyConditionalObject_setSatisfied, NULL, NULL },
    { _pycs("toggle"), (getter)pyConditionalObject_getToggle,
       (setter)pyConditionalObject_setToggle, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyConditionalObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plConditionalObject",   /* tp_name */
    sizeof(pyConditionalObject),        /* tp_basicsize */
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
    "plConditionalObject wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyConditionalObject_GetSet,         /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyConditionalObject_new,            /* tp_new */
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

PyObject* Init_pyConditionalObject_Type() {
    pyConditionalObject_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pyConditionalObject_Type) < 0)
        return NULL;

    Py_INCREF(&pyConditionalObject_Type);
    return (PyObject*)&pyConditionalObject_Type;
}

int pyConditionalObject_Check(PyObject* obj) {
    if (obj->ob_type == &pyConditionalObject_Type
        || PyType_IsSubtype(obj->ob_type, &pyConditionalObject_Type))
        return 1;
    return 0;
}

PyObject* pyConditionalObject_FromConditionalObject(class plConditionalObject* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyConditionalObject* py = PyObject_New(pyConditionalObject, &pyConditionalObject_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
