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

#include "pyMaintainersMarkerModifier.h"

#include <PRP/Modifier/plMaintainersMarkerModifier.h>
#include "pyModifier.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyMaintainersMarkerModifier_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMaintainersMarkerModifier* self = (pyMaintainersMarkerModifier*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plMaintainersMarkerModifier();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMaintainersMarkerModifier_getCalibration(
        pyMaintainersMarkerModifier* self, void*) {
    return PyInt_FromLong(self->fThis->getCalibration());
}

static int pyMaintainersMarkerModifier_setCalibration(
        pyMaintainersMarkerModifier* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "calibrated should be an int");
        return -1;
    }
    self->fThis->setCalibration(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pyMaintainersMarkerModifier_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyMaintainersMarkerModifier_GetSet[] = {
    { _pycs("calibration"), (getter)pyMaintainersMarkerModifier_getCalibration,
        (setter)pyMaintainersMarkerModifier_setCalibration, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyMaintainersMarkerModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plMaintainersMarkerModifier",       /* tp_name */
    sizeof(pyMaintainersMarkerModifier),            /* tp_basicsize */
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
    "plMaintainersMarkerModifier wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMaintainersMarkerModifier_Methods, /* tp_methods */
    NULL,                               /* tp_members */
    pyMaintainersMarkerModifier_GetSet, /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMaintainersMarkerModifier_new,    /* tp_new */
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

PyObject* Init_pyMaintainersMarkerModifier_Type() {
    pyMaintainersMarkerModifier_Type.tp_base = &pyMultiModifier_Type;
    if (PyType_Ready(&pyMaintainersMarkerModifier_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyMaintainersMarkerModifier_Type.tp_dict,
            "kBroken",
            PyInt_FromLong(plMaintainersMarkerModifier::kBroken));
    PyDict_SetItemString(pyMaintainersMarkerModifier_Type.tp_dict,
            "kRepaired",
            PyInt_FromLong(plMaintainersMarkerModifier::kRepaired));
    PyDict_SetItemString(pyMaintainersMarkerModifier_Type.tp_dict,
            "kCalibrated",
            PyInt_FromLong(plMaintainersMarkerModifier::kCalibrated));

    Py_INCREF(&pyMaintainersMarkerModifier_Type);
    return (PyObject*)&pyMaintainersMarkerModifier_Type;
}

PY_PLASMA_IFC_METHODS(MaintainersMarkerModifier, plMaintainersMarkerModifier)

}
