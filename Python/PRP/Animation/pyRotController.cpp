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
#include "pyController.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyRotController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plRotController is abstract");
    return NULL;
}

static PyObject* pyRotController_getType(pyRotController* self, void*) {
    return PyInt_FromLong(self->fThis->getType());
}

static int pyRotController_setType(pyRotController* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "type is read-only");
    return -1;
}

static PyMethodDef pyRotController_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyRotController_GetSet[] = {
    { "type", (getter)pyRotController_getType, (setter)pyRotController_setType, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyRotController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plRotController",         /* tp_name */
    sizeof(pyRotController),            /* tp_basicsize */
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
    "plRotController wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyRotController_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyRotController_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyRotController_new,                /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyRotController_Type() {
    pyRotController_Type.tp_base = &pyController_Type;
    if (PyType_Ready(&pyRotController_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyRotController_Type.tp_dict, "kSimple",
                         PyInt_FromLong(plRotController::kSimple));
    PyDict_SetItemString(pyRotController_Type.tp_dict, "kCompound",
                         PyInt_FromLong(plRotController::kCompound));

    Py_INCREF(&pyRotController_Type);
    return (PyObject*)&pyRotController_Type;
}

int pyRotController_Check(PyObject* obj) {
    if (obj->ob_type == &pyRotController_Type
        || PyType_IsSubtype(obj->ob_type, &pyRotController_Type))
        return 1;
    return 0;
}

PyObject* pyRotController_FromRotController(class plRotController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyRotController* pyobj = PyObject_New(pyRotController, &pyRotController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
