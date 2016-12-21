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

#include "pyFadeOpacityMod.h"

#include <PRP/Surface/plFadeOpacityMod.h>
#include "PRP/Modifier/pyModifier.h"

extern "C" {

static PyObject* pyFadeOpacityMod_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyFadeOpacityMod* self = (pyFadeOpacityMod*) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plFadeOpacityMod();
        self->fPyOwned = true;
    }
    return (PyObject*) self;
}

static PyObject* pyFadeOpacityMod_getFadeUp(pyFadeOpacityMod* self, void*) {
    return PyFloat_FromDouble(self->fThis->getFadeUp());
}

static PyObject* pyFadeOpacityMod_getFadeDown(pyFadeOpacityMod* self, void*) {
    return PyFloat_FromDouble(self->fThis->getFadeDown());
}

static PyObject* pyFadeOpacityMod_getBoundsCenter(pyFadeOpacityMod* self, void*) {
    return PyBool_FromLong(self->fThis->getFlag(plFadeOpacityMod::kBoundsCenter) ? 1 : 0);
}

static int pyFadeOpacityMod_setFadeUp(pyFadeOpacityMod* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fadeUp should be a float");
        return -1;
    }
    self->fThis->setFadeUp((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyFadeOpacityMod_setFadeDown(pyFadeOpacityMod* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fadeDown should be a float");
        return -1;
    }
    self->fThis->setFadeDown((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyFadeOpacityMod_setBoundsCenter(pyFadeOpacityMod* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "boundsCenter should be a bool");
        return -1;
    }
    self->fThis->setFlag(plFadeOpacityMod::kBoundsCenter, PyInt_AsLong(value) != 0);
    return 0;
}

static PyGetSetDef pyFadeOpacityMod_GetSet [] = {
    { _pycs("fadeUp"), (getter) pyFadeOpacityMod_getFadeUp, (setter) pyFadeOpacityMod_setFadeUp, NULL, NULL },
    { _pycs("fadeDown"), (getter) pyFadeOpacityMod_getFadeDown, (setter) pyFadeOpacityMod_setFadeDown, NULL, NULL },
    { _pycs("boundsCenter"), (getter) pyFadeOpacityMod_getBoundsCenter, (setter) pyFadeOpacityMod_setBoundsCenter, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyFadeOpacityMod_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plFadeOpacityMod",      /* tp_name */
    sizeof(pyFadeOpacityMod),           /* tp_basicsize */
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
    "plFadeOpacityMod wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyFadeOpacityMod_GetSet,            /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFadeOpacityMod_new,               /* tp_new */
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

PyObject* Init_pyFadeOpacityMod_Type() {
    pyFadeOpacityMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyFadeOpacityMod_Type) < 0)
        return NULL;

    Py_INCREF(&pyFadeOpacityMod_Type);
    return (PyObject*) &pyFadeOpacityMod_Type;
}

PY_PLASMA_IFC_METHODS(FadeOpacityMod, plFadeOpacityMod)

}
