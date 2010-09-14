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
#include "pyController.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyPosController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plPosController is abstract");
    return NULL;
}

static PyObject* pyPosController_getType(pyPosController* self, void*) {
    return PyInt_FromLong(self->fThis->getType());
}

static int pyPosController_setType(pyPosController* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "type is read-only");
    return -1;
}

static PyMethodDef pyPosController_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyPosController_GetSet[] = {
    { "type", (getter)pyPosController_getType, (setter)pyPosController_setType, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyPosController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plPosController",         /* tp_name */
    sizeof(pyPosController),            /* tp_basicsize */
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
    "plPosController wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyPosController_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyPosController_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyPosController_new,                /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyPosController_Type() {
    pyPosController_Type.tp_base = &pyController_Type;
    if (PyType_Ready(&pyPosController_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyPosController_Type.tp_dict, "kSimple",
                         PyInt_FromLong(plPosController::kSimple));
    PyDict_SetItemString(pyPosController_Type.tp_dict, "kCompound",
                         PyInt_FromLong(plPosController::kCompound));

    Py_INCREF(&pyPosController_Type);
    return (PyObject*)&pyPosController_Type;
}

int pyPosController_Check(PyObject* obj) {
    if (obj->ob_type == &pyPosController_Type
        || PyType_IsSubtype(obj->ob_type, &pyPosController_Type))
        return 1;
    return 0;
}

PyObject* pyPosController_FromPosController(class plPosController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyPosController* pyobj = PyObject_New(pyPosController, &pyPosController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
