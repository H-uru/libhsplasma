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
#include <PRP/Physics/plPhysical.h>
#include "pyPhysical.h"
#include "PRP/Object/pySynchedObject.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyPhysical_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plPhysical is abstract");
    return NULL;
}

static PyObject* pyPhysical_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyPhysical_FromPhysical(plPhysical::Convert(IConvert(cre)));
}

static PyMethodDef pyPhysical_Methods[] = {
    { "Convert", (PyCFunction)pyPhysical_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plPhysical" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyPhysical_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plPhysical",              /* tp_name */
    sizeof(pyPhysical),                 /* tp_basicsize */
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
    "plPhysical wrapper",               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyPhysical_Methods,                 /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyPhysical_new,                     /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyPhysical_Type() {
    pyPhysical_Type.tp_base = &pySynchedObject_Type;
    if (PyType_Ready(&pyPhysical_Type) < 0)
        return NULL;

    Py_INCREF(&pyPhysical_Type);
    return (PyObject*)&pyPhysical_Type;
}

int pyPhysical_Check(PyObject* obj) {
    if (obj->ob_type == &pyPhysical_Type
        || PyType_IsSubtype(obj->ob_type, &pyPhysical_Type))
        return 1;
    return 0;
}

PyObject* pyPhysical_FromPhysical(class plPhysical* phys) {
    if (phys == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyPhysical* pyphys = PyObject_New(pyPhysical, &pyPhysical_Type);
    pyphys->fThis = phys;
    pyphys->fPyOwned = false;
    return (PyObject*)pyphys;
}

}
