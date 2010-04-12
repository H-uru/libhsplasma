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

static PyObject* pyClickDragEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyClickDragEventData* self = (pyClickDragEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proClickDragEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyClickDragEventData_Convert(PyObject*, PyObject* args) {
    pyEventData* evt;
    if (!PyArg_ParseTuple(args, "O", &evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    if (!pyEventData_Check((PyObject*)evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    return pyClickDragEventData_FromClickDragEventData(proClickDragEventData::Convert(evt->fThis));
}

static PyMethodDef pyClickDragEventData_Methods[] = {
    { "Convert", (PyCFunction)pyClickDragEventData_Convert, METH_VARARGS | METH_STATIC,
      "Convert a proEventData to a proClickDragEventData" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyClickDragEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.proClickDragEventData",   /* tp_name */
    sizeof(pyClickDragEventData),       /* tp_basicsize */
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
    "proClickDragEventData wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyClickDragEventData_Methods,       /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyClickDragEventData_new,           /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyClickDragEventData_Type() {
    pyClickDragEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyClickDragEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyClickDragEventData_Type);
    return (PyObject*)&pyClickDragEventData_Type;
}

int pyClickDragEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyClickDragEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyClickDragEventData_Type))
        return 1;
    return 0;
}

PyObject* pyClickDragEventData_FromClickDragEventData(proClickDragEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyClickDragEventData* pyobj = PyObject_New(pyClickDragEventData, &pyClickDragEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
