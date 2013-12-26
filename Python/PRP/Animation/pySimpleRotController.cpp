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
#include <PRP/Animation/plRotController.h>
#include "pyRotController.h"
#include "pyLeafController.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pySimpleRotController___init__(pySimpleRotController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pySimpleRotController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySimpleRotController* self = (pySimpleRotController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSimpleRotController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySimpleRotController_getRot(pySimpleRotController* self, void*) {
    return pyQuatController_FromQuatController(self->fThis->getRot());
}

static int pySimpleRotController_setRot(pySimpleRotController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setRot(NULL);
        return 0;
    }
    if (!pyQuatController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "rot should be a plQuatController");
        return -1;
    }
    self->fThis->setRot(((pyQuatController*)value)->fThis);
    ((pyQuatController*)value)->fPyOwned = false;
    return 0;
}

static PyMethodDef pySimpleRotController_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pySimpleRotController_GetSet[] = {
    { _pycs("rot"), (getter)pySimpleRotController_getRot,
        (setter)pySimpleRotController_setRot, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySimpleRotController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSimpleRotController", /* tp_name */
    sizeof(pySimpleRotController),      /* tp_basicsize */
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
    "plSimpleRotController wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySimpleRotController_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pySimpleRotController_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pySimpleRotController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pySimpleRotController_new,          /* tp_new */
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

PyObject* Init_pySimpleRotController_Type() {
    pySimpleRotController_Type.tp_base = &pyRotController_Type;
    if (PyType_Ready(&pySimpleRotController_Type) < 0)
        return NULL;

    Py_INCREF(&pySimpleRotController_Type);
    return (PyObject*)&pySimpleRotController_Type;
}

int pySimpleRotController_Check(PyObject* obj) {
    if (obj->ob_type == &pySimpleRotController_Type
        || PyType_IsSubtype(obj->ob_type, &pySimpleRotController_Type))
        return 1;
    return 0;
}

PyObject* pySimpleRotController_FromSimpleRotController(class plSimpleRotController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySimpleRotController* pyobj = PyObject_New(pySimpleRotController, &pySimpleRotController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
