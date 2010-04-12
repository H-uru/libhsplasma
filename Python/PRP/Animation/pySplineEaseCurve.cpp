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
#include <PRP/Animation/plATCEaseCurves.h>
#include "pyATCEaseCurves.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pySplineEaseCurve_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySplineEaseCurve* self = (pySplineEaseCurve*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSplineEaseCurve();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySplineEaseCurve_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pySplineEaseCurve_FromSplineEaseCurve(plSplineEaseCurve::Convert(cre->fThis));
}

static PyObject* pySplineEaseCurve_getSplineCoef(pySplineEaseCurve* self, void*) {
    return Py_BuildValue("ffff", PyFloat_FromDouble(self->fThis->getSplineCoef(0)),
                                 PyFloat_FromDouble(self->fThis->getSplineCoef(1)),
                                 PyFloat_FromDouble(self->fThis->getSplineCoef(2)),
                                 PyFloat_FromDouble(self->fThis->getSplineCoef(3)));
}

static int pySplineEaseCurve_setSplineCoef(pySplineEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyTuple_Check(value) || PyTuple_Size(value) != 4) {
        PyErr_SetString(PyExc_TypeError, "splineCoef should be a tuple of 4 floats");
        return -1;
    }
    for (size_t i=0; i<4; i++) {
        PyObject* itm = PyTuple_GetItem(value, i);
        if (!PyFloat_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "splineCoef should be a tuple of 4 floats");
            return -1;
        }
        self->fThis->setSplineCoef(i, PyFloat_AsDouble(itm));
    }
    return 0;
}

static PyMethodDef pySplineEaseCurve_Methods[] = {
    { "Convert", (PyCFunction)pySplineEaseCurve_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plSplineEaseCurve" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pySplineEaseCurve_GetSet[] = {
    { "splineCoef", (getter)pySplineEaseCurve_getSplineCoef, (setter)pySplineEaseCurve_setSplineCoef, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySplineEaseCurve_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plSplineEaseCurve",       /* tp_name */
    sizeof(pySplineEaseCurve),          /* tp_basicsize */
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
    "plSplineEaseCurve wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySplineEaseCurve_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    pySplineEaseCurve_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySplineEaseCurve_new,              /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pySplineEaseCurve_Type() {
    pySplineEaseCurve_Type.tp_base = &pyATCEaseCurve_Type;
    if (PyType_Ready(&pySplineEaseCurve_Type) < 0)
        return NULL;

    Py_INCREF(&pySplineEaseCurve_Type);
    return (PyObject*)&pySplineEaseCurve_Type;
}

int pySplineEaseCurve_Check(PyObject* obj) {
    if (obj->ob_type == &pySplineEaseCurve_Type
        || PyType_IsSubtype(obj->ob_type, &pySplineEaseCurve_Type))
        return 1;
    return 0;
}

PyObject* pySplineEaseCurve_FromSplineEaseCurve(class plSplineEaseCurve* curve) {
    if (curve == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySplineEaseCurve* pyobj = PyObject_New(pySplineEaseCurve, &pySplineEaseCurve_Type);
    pyobj->fThis = curve;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
