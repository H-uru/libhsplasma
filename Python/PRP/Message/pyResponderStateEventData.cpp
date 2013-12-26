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

static PyObject* pyResponderStateEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyResponderStateEventData* self = (pyResponderStateEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proResponderStateEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyResponderStateEventData_getState(pyResponderStateEventData* self, void*) {
    return PyInt_FromLong(self->fThis->getState());
}

static int pyResponderStateEventData_setState(pyResponderStateEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "state should be an int");
        return -1;
    }
    self->fThis->setState(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pyResponderStateEventData_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyResponderStateEventData_GetSet[] = {
    { _pycs("state"), (getter)pyResponderStateEventData_getState,
        (setter)pyResponderStateEventData_setState, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyResponderStateEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.proResponderStateEventData", /* tp_name */
    sizeof(pyResponderStateEventData),  /* tp_basicsize */
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
    "proResponderStateEventData wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyResponderStateEventData_Methods,  /* tp_methods */
    NULL,                               /* tp_members */
    pyResponderStateEventData_GetSet,   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyResponderStateEventData_new,      /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pyResponderStateEventData_Type() {
    pyResponderStateEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyResponderStateEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyResponderStateEventData_Type);
    return (PyObject*)&pyResponderStateEventData_Type;
}

int pyResponderStateEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyResponderStateEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyResponderStateEventData_Type))
        return 1;
    return 0;
}

PyObject* pyResponderStateEventData_FromResponderStateEventData(proResponderStateEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyResponderStateEventData* pyobj = PyObject_New(pyResponderStateEventData, &pyResponderStateEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
