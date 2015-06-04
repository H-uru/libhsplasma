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
#include <PRP/ConditionalObject/plVolumeSensorConditionalObject.h>
#include "pyVolumeSensorConditionalObject.h"
#include "pyConditionalObject.h"
#include "PRP/pyCreatable.h"

static inline plVolumeSensorConditionalObject* IConvertCond(pyVolumeSensorConditionalObject* self) {
    return plVolumeSensorConditionalObject::Convert(IConvert((pyCreatable*)self));
}

extern "C" {

static PyObject* pyVolumeSensorConditionalObject_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyVolumeSensorConditionalObject* self = (pyVolumeSensorConditionalObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plVolumeSensorConditionalObject();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyVolumeSensorConditionalObject_getTrigNum(pyVolumeSensorConditionalObject* self, void*) {
    return PyInt_FromLong(IConvertCond(self)->getTrigNum());
}

static PyObject* pyVolumeSensorConditionalObject_getType(pyVolumeSensorConditionalObject* self, void*) {
    return PyInt_FromLong(IConvertCond(self)->getType());
}

static PyObject* pyVolumeSensorConditionalObject_getFirst(pyVolumeSensorConditionalObject* self, void*) {
    return PyBool_FromLong(IConvertCond(self)->getFirst() ? 1 : 0);
}

static int pyVolumeSensorConditionalObject_setTrigNum(pyVolumeSensorConditionalObject* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "trigNum should be an int");
        return -1;
    }
    IConvertCond(self)->setTrigNum(PyInt_AsLong(value));
    return 0;
}

static int pyVolumeSensorConditionalObject_setType(pyVolumeSensorConditionalObject* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "type should be an int");
        return -1;
    }
    IConvertCond(self)->setType(PyInt_AsLong(value));
    return 0;
}

static int pyVolumeSensorConditionalObject_setFirst(pyVolumeSensorConditionalObject* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "first should be a boolean");
        return -1;
    }
    IConvertCond(self)->setFirst(PyInt_AsLong(value) != 0);
    return 0;
}

static PyGetSetDef pyVolumeSensorConditionalObject_GetSet[] = {
    { _pycs("trigNum"), (getter)pyVolumeSensorConditionalObject_getTrigNum,
       (setter)pyVolumeSensorConditionalObject_setTrigNum, NULL, NULL },
    { _pycs("type"), (getter)pyVolumeSensorConditionalObject_getType,
       (setter)pyVolumeSensorConditionalObject_setType, NULL, NULL },
    { _pycs("first"), (getter)pyVolumeSensorConditionalObject_getFirst,
       (setter)pyVolumeSensorConditionalObject_setFirst, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyVolumeSensorConditionalObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plVolumeSensorConditionalObject", /* tp_name */
    sizeof(pyVolumeSensorConditionalObject),      /* tp_basicsize */
    0,                                            /* tp_itemsize */

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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,  /* tp_flags */
    "plVolumeSensorConditionalObject wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyVolumeSensorConditionalObject_GetSet, /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyVolumeSensorConditionalObject_new, /* tp_new */
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

PyObject* Init_pyVolumeSensorConditionalObject_Type() {
    pyVolumeSensorConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_Ready(&pyVolumeSensorConditionalObject_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyVolumeSensorConditionalObject_Type.tp_dict, "kTypeEnter",
                         PyInt_FromLong(plVolumeSensorConditionalObject::kTypeEnter));
    PyDict_SetItemString(pyVolumeSensorConditionalObject_Type.tp_dict, "kTypeExit",
                         PyInt_FromLong(plVolumeSensorConditionalObject::kTypeExit));

    Py_INCREF(&pyVolumeSensorConditionalObject_Type);
    return (PyObject*)&pyVolumeSensorConditionalObject_Type;
}

int pyVolumeSensorConditionalObject_Check(PyObject* obj) {
    if (obj->ob_type == &pyVolumeSensorConditionalObject_Type
        || PyType_IsSubtype(obj->ob_type, &pyVolumeSensorConditionalObject_Type))
        return 1;
    return 0;
}

PyObject* pyVolumeSensorConditionalObject_FromVolumeSensorConditionalObject(class plVolumeSensorConditionalObject* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyVolumeSensorConditionalObject* py = PyObject_New(pyVolumeSensorConditionalObject, &pyVolumeSensorConditionalObject_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
