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

#include "pyRotController.h"

#include <PRP/Animation/plRotController.h>
#include "pyLeafController.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pyCompoundRotController___init__(pyCompoundRotController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyCompoundRotController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCompoundRotController* self = (pyCompoundRotController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCompoundRotController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCompoundRotController_getX(pyCompoundRotController* self, void*) {
    return ICreate(self->fThis->getX());
}

static PyObject* pyCompoundRotController_getY(pyCompoundRotController* self, void*) {
    return  ICreate(self->fThis->getY());
}

static PyObject* pyCompoundRotController_getZ(pyCompoundRotController* self, void*) {
    return  ICreate(self->fThis->getZ());
}

static int pyCompoundRotController_setX(pyCompoundRotController* self, PyObject* value, void*) {
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

static int pyCompoundRotController_setY(pyCompoundRotController* self, PyObject* value, void*) {
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

static int pyCompoundRotController_setZ(pyCompoundRotController* self, PyObject* value, void*) {
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

static PyMethodDef pyCompoundRotController_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCompoundRotController_GetSet[] = {
    { _pycs("X"), (getter)pyCompoundRotController_getX,
        (setter)pyCompoundRotController_setX, NULL, NULL },
    { _pycs("Y"), (getter)pyCompoundRotController_getY,
        (setter)pyCompoundRotController_setY, NULL, NULL },
    { _pycs("Z"), (getter)pyCompoundRotController_getZ,
        (setter)pyCompoundRotController_setZ, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCompoundRotController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCompoundRotController", /* tp_name */
    sizeof(pyCompoundRotController),    /* tp_basicsize */
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
    "plCompoundRotController wrapper",  /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCompoundRotController_Methods,    /* tp_methods */
    NULL,                               /* tp_members */
    pyCompoundRotController_GetSet,     /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyCompoundRotController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyCompoundRotController_new,        /* tp_new */
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

PyObject* Init_pyCompoundRotController_Type() {
    pyCompoundRotController_Type.tp_base = &pyRotController_Type;
    if (PyType_Ready(&pyCompoundRotController_Type) < 0)
        return NULL;

    Py_INCREF(&pyCompoundRotController_Type);
    return (PyObject*)&pyCompoundRotController_Type;
}

int pyCompoundRotController_Check(PyObject* obj) {
    if (obj->ob_type == &pyCompoundRotController_Type
        || PyType_IsSubtype(obj->ob_type, &pyCompoundRotController_Type))
        return 1;
    return 0;
}

PyObject* pyCompoundRotController_FromCompoundRotController(class plCompoundRotController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCompoundRotController* pyobj = PyObject_New(pyCompoundRotController, &pyCompoundRotController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
