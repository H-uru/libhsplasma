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

#include "pyVolumeIsect.h"

#include <PRP/Region/plVolumeIsect.h>
#include "Math/pyGeometry3.h"
#include "Math/pyMatrix.h"

extern "C" {

static PyObject* pyConvexIsect_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyConvexIsect* self = (pyConvexIsect*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plConvexIsect();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyConvexIsect_addPlane(pyConvexIsect* self, PyObject* args) {
    PyObject* normal;
    PyObject* position;
    if (!PyArg_ParseTuple(args, "OO", &normal, &position) || !pyVector3_Check(normal) ||
        !pyVector3_Check(position)) {
        PyErr_SetString(PyExc_TypeError, "addPlane expects hsVector3, hsVector3");
        return NULL;
    }
    self->fThis->addPlane(*((pyVector3*)normal)->fThis, *((pyVector3*)position)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyConvexIsect_transform(pyConvexIsect* self, PyObject* args) {
    PyObject* l2w;
    PyObject* w2l;
    if (!PyArg_ParseTuple(args, "OO", &l2w, &w2l) || !pyMatrix44_Check(l2w) || !pyMatrix44_Check(w2l)) {
        PyErr_SetString(PyExc_TypeError, "transform expects hsMatrix44, hsMatrix44");
        return NULL;
    }
    self->fThis->transform(*((pyMatrix44*)l2w)->fThis, *((pyMatrix44*)w2l)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

PyMethodDef pyConvexIsect_Methods[] = {
    { "addPlane", (PyCFunction)pyConvexIsect_addPlane, METH_VARARGS,
      "Adds or updates a given plane\n"
      "Params: normal, position" },
    { "transform", (PyCFunction)pyConvexIsect_transform, METH_VARARGS,
      "Calculates worldspace transformation for this volume\n"
      "Params: localToWorld, worldToLocal" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyConvexIsect_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plConvexIsect",         /* tp_name */
    sizeof(pyConvexIsect),              /* tp_basicsize */
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
    "plConvexIsect wrapper",                  /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyConvexIsect_Methods,              /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyConvexIsect_new,                  /* tp_new */
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

PyObject* Init_pyConvexIsect_Type() {
    pyConvexIsect_Type.tp_base = &pyVolumeIsect_Type;
    if (PyType_Ready(&pyConvexIsect_Type) < 0)
        return NULL;

    Py_INCREF(&pyConvexIsect_Type);
    return (PyObject*)&pyConvexIsect_Type;
}

PY_PLASMA_IFC_METHODS(ConvexIsect, plConvexIsect)

}
