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
#include <PRP/Physics/plCollisionDetector.h>
#include "pyCollisionDetector.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pySubworldRegionDetector_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySubworldRegionDetector* self = (pySubworldRegionDetector*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSubworldRegionDetector();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySubworldRegionDetector_getSubworld(pySubworldRegionDetector* self, void*) {
    return pyKey_FromKey(self->fThis->getSubworld());
}

static PyObject* pySubworldRegionDetector_getOnExit(pySubworldRegionDetector* self, void*) {
    return PyBool_FromLong(self->fThis->getOnExit() ? 1 : 0);
}

static int pySubworldRegionDetector_setSubworld(pySubworldRegionDetector* self, PyObject* value, void*) {
    if (value == NULL || !pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "subworld should be a plKey");
        return -1;
    }
    self->fThis->setSubworld(*((pyKey*)value)->fThis);
    return 0;
}

static int pySubworldRegionDetector_setOnExit(pySubworldRegionDetector* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "onExit should be a boolean");
        return -1;
    }
    self->fThis->setOnExit(PyInt_AsLong(value) != 0);
    return 0;
}

static PyGetSetDef pySubworldRegionDetector_GetSet[] = {
    { _pycs("subworld"), (getter)pySubworldRegionDetector_getSubworld,
       (setter)pySubworldRegionDetector_setSubworld, NULL, NULL },
    { _pycs("onExit"), (getter)pySubworldRegionDetector_getOnExit,
       (setter)pySubworldRegionDetector_setOnExit, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySubworldRegionDetector_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSubworldRegionDetector", /* tp_name */
    sizeof(pySubworldRegionDetector),      /* tp_basicsize */
    0,                                     /* tp_itemsize */

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
    "plSubworldRegionDetector wrapper",       /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pySubworldRegionDetector_GetSet,    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySubworldRegionDetector_new,       /* tp_new */
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

PyObject* Init_pySubworldRegionDetector_Type() {
    pySubworldRegionDetector_Type.tp_base = &pyCollisionDetector_Type;
    if (PyType_Ready(&pySubworldRegionDetector_Type) < 0)
        return NULL;

    Py_INCREF(&pySubworldRegionDetector_Type);
    return (PyObject*)&pySubworldRegionDetector_Type;
}

int pySubworldRegionDetector_Check(PyObject* obj) {
    if (obj->ob_type == &pySubworldRegionDetector_Type
        || PyType_IsSubtype(obj->ob_type, &pySubworldRegionDetector_Type))
        return 1;
    return 0;
}

PyObject* pySubworldRegionDetector_FromSubworldRegionDetector(class plSubworldRegionDetector* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySubworldRegionDetector* py = PyObject_New(pySubworldRegionDetector, &pySubworldRegionDetector_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
