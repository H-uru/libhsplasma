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

#include "pyController.h"

#include <PRP/Animation/plTMController.h>
#include "PRP/pyCreatable.h"

extern "C" {

static int pyCompoundController___init__(pyCompoundController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyCompoundController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCompoundController* self = (pyCompoundController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCompoundController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCompoundController_getX(pyCompoundController* self, void*) {
    return ICreate(self->fThis->getXController());
}

static PyObject* pyCompoundController_getY(pyCompoundController* self, void*) {
    return ICreate(self->fThis->getYController());
}

static PyObject* pyCompoundController_getZ(pyCompoundController* self, void*) {
    return ICreate(self->fThis->getZController());
}

static int pyCompoundController_setX(pyCompoundController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setXController(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "X should be a plController");
        return -1;
    }
    self->fThis->setXController(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static int pyCompoundController_setY(pyCompoundController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setYController(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Y should be a plController");
        return -1;
    }
    self->fThis->setYController(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static int pyCompoundController_setZ(pyCompoundController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setZController(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Z should be a plController");
        return -1;
    }
    self->fThis->setZController(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static PyObject* pyCompoundController_convertToTMController(pyCompoundController* self) {
    return ICreate(self->fThis->convertToTMController());
}

static PyMethodDef pyCompoundController_Methods[] = {
    { "convertToTMController", (PyCFunction)pyCompoundController_convertToTMController, METH_NOARGS,
      "Converts this controller to a plTMController" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCompoundController_GetSet[] = {
    { _pycs("X"), (getter)pyCompoundController_getX,
        (setter)pyCompoundController_setX, NULL, NULL },
    { _pycs("Y"), (getter)pyCompoundController_getY,
        (setter)pyCompoundController_setY, NULL, NULL },
    { _pycs("Z"), (getter)pyCompoundController_getZ,
        (setter)pyCompoundController_setZ, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCompoundController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCompoundController",  /* tp_name */
    sizeof(pyCompoundController),       /* tp_basicsize */
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
    "plCompoundController wrapper",     /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCompoundController_Methods,       /* tp_methods */
    NULL,                               /* tp_members */
    pyCompoundController_GetSet,        /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyCompoundController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyCompoundController_new,           /* tp_new */
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

PyObject* Init_pyCompoundController_Type() {
    pyCompoundController_Type.tp_base = &pyController_Type;
    if (PyType_Ready(&pyCompoundController_Type) < 0)
        return NULL;

    Py_INCREF(&pyCompoundController_Type);
    return (PyObject*)&pyCompoundController_Type;
}

PY_PLASMA_IFC_METHODS(CompoundController, plCompoundController)

}
