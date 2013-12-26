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
#include <PRP/Animation/plPosController.h>
#include "pyPosController.h"
#include "pyLeafController.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pyCompoundPosController___init__(pyCompoundPosController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyCompoundPosController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCompoundPosController* self = (pyCompoundPosController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCompoundPosController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCompoundPosController_getX(pyCompoundPosController* self, void*) {
    return pyScalarController_FromScalarController(self->fThis->getX());
}

static PyObject* pyCompoundPosController_getY(pyCompoundPosController* self, void*) {
    return pyScalarController_FromScalarController(self->fThis->getY());
}

static PyObject* pyCompoundPosController_getZ(pyCompoundPosController* self, void*) {
    return pyScalarController_FromScalarController(self->fThis->getZ());
}

static int pyCompoundPosController_setX(pyCompoundPosController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setX(NULL);
        return 0;
    }
    if (!pyScalarController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "X should be a plScalarController");
        return -1;
    }
    self->fThis->setX(((pyScalarController*)value)->fThis);
    ((pyScalarController*)value)->fPyOwned = false;
    return 0;
}

static int pyCompoundPosController_setY(pyCompoundPosController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setY(NULL);
        return 0;
    }
    if (!pyScalarController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Y should be a plScalarController");
        return -1;
    }
    self->fThis->setY(((pyScalarController*)value)->fThis);
    ((pyScalarController*)value)->fPyOwned = false;
    return 0;
}

static int pyCompoundPosController_setZ(pyCompoundPosController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setZ(NULL);
        return 0;
    }
    if (!pyScalarController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Z should be a plScalarController");
        return -1;
    }
    self->fThis->setZ(((pyScalarController*)value)->fThis);
    ((pyScalarController*)value)->fPyOwned = false;
    return 0;
}

static PyMethodDef pyCompoundPosController_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCompoundPosController_GetSet[] = {
    { _pycs("X"), (getter)pyCompoundPosController_getX,
        (setter)pyCompoundPosController_setX, NULL, NULL },
    { _pycs("Y"), (getter)pyCompoundPosController_getY,
        (setter)pyCompoundPosController_setY, NULL, NULL },
    { _pycs("Z"), (getter)pyCompoundPosController_getZ,
        (setter)pyCompoundPosController_setZ, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCompoundPosController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCompoundPosController", /* tp_name */
    sizeof(pyCompoundPosController),    /* tp_basicsize */
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
    "plCompoundPosController wrapper",  /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCompoundPosController_Methods,    /* tp_methods */
    NULL,                               /* tp_members */
    pyCompoundPosController_GetSet,     /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyCompoundPosController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyCompoundPosController_new,        /* tp_new */
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

PyObject* Init_pyCompoundPosController_Type() {
    pyCompoundPosController_Type.tp_base = &pyPosController_Type;
    if (PyType_Ready(&pyCompoundPosController_Type) < 0)
        return NULL;

    Py_INCREF(&pyCompoundPosController_Type);
    return (PyObject*)&pyCompoundPosController_Type;
}

int pyCompoundPosController_Check(PyObject* obj) {
    if (obj->ob_type == &pyCompoundPosController_Type
        || PyType_IsSubtype(obj->ob_type, &pyCompoundPosController_Type))
        return 1;
    return 0;
}

PyObject* pyCompoundPosController_FromCompoundPosController(class plCompoundPosController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCompoundPosController* pyobj = PyObject_New(pyCompoundPosController, &pyCompoundPosController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
