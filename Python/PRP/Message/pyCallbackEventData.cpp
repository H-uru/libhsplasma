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
#include <PRP/Message/proEventData.h>
#include "pyEventData.h"

extern "C" {

static PyObject* pyCallbackEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCallbackEventData* self = (pyCallbackEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proCallbackEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCallbackEventData_getType(pyCallbackEventData* self, void*) {
    return PyInt_FromLong(self->fThis->getCallbackEventType());
}

static int pyCallbackEventData_setType(pyCallbackEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "callbackEventType should be an int");
        return -1;
    }
    self->fThis->setCallbackEventType(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pyCallbackEventData_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCallbackEventData_GetSet[] = {
    { "callbackEventType", (getter)pyCallbackEventData_getType, (setter)pyCallbackEventData_setType, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCallbackEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.proCallbackEventData",    /* tp_name */
    sizeof(pyCallbackEventData),        /* tp_basicsize */
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
    "proCallbackEventData wrapper",     /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCallbackEventData_Methods,        /* tp_methods */
    NULL,                               /* tp_members */
    pyCallbackEventData_GetSet,         /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyCallbackEventData_new,            /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyCallbackEventData_Type() {
    pyCallbackEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyCallbackEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyCallbackEventData_Type);
    return (PyObject*)&pyCallbackEventData_Type;
}

int pyCallbackEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyCallbackEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyCallbackEventData_Type))
        return 1;
    return 0;
}

PyObject* pyCallbackEventData_FromCallbackEventData(proCallbackEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCallbackEventData* pyobj = PyObject_New(pyCallbackEventData, &pyCallbackEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
