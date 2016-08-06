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

#include "pyObjectInVolumeDetector.h"

#include <PRP/Physics/plObjectInVolumeDetector.h>

extern "C" {

static PyObject* pyObjectInVolumeAndFacingDetector_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyObjectInVolumeAndFacingDetector* self = (pyObjectInVolumeAndFacingDetector*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plObjectInVolumeAndFacingDetector();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyObjectInVolumeAndFacingDetector_getFacingTolerance(pyObjectInVolumeAndFacingDetector* self, void*) {
    return PyFloat_FromDouble(self->fThis->getFacingTolerance());
}

static PyObject* pyObjectInVolumeAndFacingDetector_getNeedWalkingForward(pyObjectInVolumeAndFacingDetector* self, void*) {
    return PyBool_FromLong(self->fThis->getNeedWalkingForward() ? 1 : 0);
}

static int pyObjectInVolumeAndFacingDetector_setFacingTolerance(pyObjectInVolumeAndFacingDetector* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "facingTolerance should be a float");
        return -1;
    }
    self->fThis->setFacingTolerance((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyObjectInVolumeAndFacingDetector_setNeedWalkingForward(pyObjectInVolumeAndFacingDetector* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "needWalkingForward should be a boolean");
        return -1;
    }
    self->fThis->setNeedWalkingForward(PyInt_AsLong(value) != 0);
    return 0;
}

static PyGetSetDef pyObjectInVolumeAndFacingDetector_GetSet[] = {
    { _pycs("facingTolerance"), (getter)pyObjectInVolumeAndFacingDetector_getFacingTolerance,
       (setter)pyObjectInVolumeAndFacingDetector_setFacingTolerance, NULL, NULL },
    { _pycs("needWalkingForward"), (getter)pyObjectInVolumeAndFacingDetector_getNeedWalkingForward,
       (setter)pyObjectInVolumeAndFacingDetector_setNeedWalkingForward, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyObjectInVolumeAndFacingDetector_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plObjectInVolumeAndFacingDetector", /* tp_name */
    sizeof(pyObjectInVolumeAndFacingDetector),      /* tp_basicsize */
    0,                                              /* tp_itemsize */

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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,    /* tp_flags */
    "plObjectInVolumeAndFacingDetector wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyObjectInVolumeAndFacingDetector_GetSet, /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyObjectInVolumeAndFacingDetector_new, /* tp_new */
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

PyObject* Init_pyObjectInVolumeAndFacingDetector_Type() {
    pyObjectInVolumeAndFacingDetector_Type.tp_base = &pyObjectInVolumeDetector_Type;
    if (PyType_Ready(&pyObjectInVolumeAndFacingDetector_Type) < 0)
        return NULL;

    Py_INCREF(&pyObjectInVolumeAndFacingDetector_Type);
    return (PyObject*)&pyObjectInVolumeAndFacingDetector_Type;
}

int pyObjectInVolumeAndFacingDetector_Check(PyObject* obj) {
    if (obj->ob_type == &pyObjectInVolumeAndFacingDetector_Type
        || PyType_IsSubtype(obj->ob_type, &pyObjectInVolumeAndFacingDetector_Type))
        return 1;
    return 0;
}

PyObject* pyObjectInVolumeAndFacingDetector_FromObjectInVolumeAndFacingDetector(class plObjectInVolumeAndFacingDetector* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyObjectInVolumeAndFacingDetector* py = PyObject_New(pyObjectInVolumeAndFacingDetector, &pyObjectInVolumeAndFacingDetector_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
