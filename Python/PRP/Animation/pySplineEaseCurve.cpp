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

#include "pyATCEaseCurves.h"

#include <PRP/Animation/plATCEaseCurves.h>
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

PY_GETSET_GETTER_DECL(SplineEaseCurve, splineCoef) {
    return Py_BuildValue("ffff", pyPlasma_convert(self->fThis->getSplineCoef(0)),
                                 pyPlasma_convert(self->fThis->getSplineCoef(1)),
                                 pyPlasma_convert(self->fThis->getSplineCoef(2)),
                                 pyPlasma_convert(self->fThis->getSplineCoef(3)));
}

PY_GETSET_SETTER_DECL(SplineEaseCurve, splineCoef) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "splineCoef cannot be deleted");
        return -1;
    } else if (!PyTuple_Check(value) || PyTuple_Size(value) != 4) {
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

PY_PROPERTY_GETSET_DECL(SplineEaseCurve, splineCoef)

static PyGetSetDef pySplineEaseCurve_GetSet[] = {
    pySplineEaseCurve_splineCoef_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pySplineEaseCurve_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSplineEaseCurve",     /* tp_name */
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

    NULL,                               /* tp_methods */
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

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pySplineEaseCurve_Type() {
    pySplineEaseCurve_Type.tp_base = &pyATCEaseCurve_Type;
    if (PyType_Ready(&pySplineEaseCurve_Type) < 0)
        return NULL;

    Py_INCREF(&pySplineEaseCurve_Type);
    return (PyObject*)&pySplineEaseCurve_Type;
}

PY_PLASMA_IFC_METHODS(SplineEaseCurve, plSplineEaseCurve)

}
