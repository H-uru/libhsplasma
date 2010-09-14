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
#include <PRP/Animation/plKeyControllers.hpp>
#include "pyLeafController.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pyEaseController___init__(pyEaseController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyEaseController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyEaseController* self = (pyEaseController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plEaseController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyMethodDef pyEaseController_Methods[] = {
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyEaseController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plEaseController",        /* tp_name */
    sizeof(pyEaseController),           /* tp_basicsize */
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
    "plEaseController wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyEaseController_Methods,           /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyEaseController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyEaseController_new,               /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyEaseController_Type() {
    pyEaseController_Type.tp_base = &pyLeafController_Type;
    if (PyType_Ready(&pyEaseController_Type) < 0)
        return NULL;

    Py_INCREF(&pyEaseController_Type);
    return (PyObject*)&pyEaseController_Type;
}

int pyEaseController_Check(PyObject* obj) {
    if (obj->ob_type == &pyEaseController_Type
        || PyType_IsSubtype(obj->ob_type, &pyEaseController_Type))
        return 1;
    return 0;
}

PyObject* pyEaseController_FromEaseController(class plEaseController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyEaseController* pyobj = PyObject_New(pyEaseController, &pyEaseController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
