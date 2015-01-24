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
#include <PRP/Surface/plLayerAnimation.h>
#include "pyLayerAnimation.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyLayerLinkAnimation_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyLayerLinkAnimation* self = (pyLayerLinkAnimation*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plLayerLinkAnimation();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyLayerLinkAnimation_getLinkKey(pyLayerLinkAnimation* self, void*) {
    return pyKey_FromKey(self->fThis->getLinkKey());
}

static PyObject* pyLayerLinkAnimation_getLeavingAge(pyLayerLinkAnimation* self, void*) {
    return PyBool_FromLong(self->fThis->getLeavingAge() ? 1 : 0);
}

static int pyLayerLinkAnimation_setLinkKey(pyLayerLinkAnimation* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        Py_XDECREF(value);
        self->fThis->setLinkKey(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "linkKey should be a plKey");
        return -1;
    }
    self->fThis->setLinkKey(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLayerLinkAnimation_setLeavingAge(pyLayerLinkAnimation* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "leavingAge should be a bool");
        return -1;
    }
    self->fThis->setLeavingAge(PyInt_AsLong(value) == 0 ? false : true);
    return 0;
}

static PyMethodDef pyLayerLinkAnimation_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLayerLinkAnimation_GetSet[] = {
    { _pycs("linkKey"), (getter)pyLayerLinkAnimation_getLinkKey,
        (setter)pyLayerLinkAnimation_setLinkKey, NULL, NULL },
    { _pycs("leavingAge"), (getter)pyLayerLinkAnimation_getLeavingAge,
        (setter)pyLayerLinkAnimation_setLeavingAge, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLayerLinkAnimation_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plLayerLinkAnimation",  /* tp_name */
    sizeof(pyLayerLinkAnimation),       /* tp_basicsize */
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
    "plLayerLinkAnimation wrapper",     /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLayerLinkAnimation_Methods,       /* tp_methods */
    NULL,                               /* tp_members */
    pyLayerLinkAnimation_GetSet,        /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLayerLinkAnimation_new,           /* tp_new */
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

PyObject* Init_pyLayerLinkAnimation_Type() {
    pyLayerLinkAnimation_Type.tp_base = &pyLayerAnimation_Type;
    if (PyType_Ready(&pyLayerLinkAnimation_Type) < 0)
        return NULL;

    Py_INCREF(&pyLayerLinkAnimation_Type);
    return (PyObject*)&pyLayerLinkAnimation_Type;
}

int pyLayerLinkAnimation_Check(PyObject* obj) {
    if (obj->ob_type == &pyLayerLinkAnimation_Type
        || PyType_IsSubtype(obj->ob_type, &pyLayerLinkAnimation_Type))
        return 1;
    return 0;
}

PyObject* pyLayerLinkAnimation_FromLayerLinkAnimation(class plLayerLinkAnimation* layer) {
    if (layer == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLayerLinkAnimation* pyobj = PyObject_New(pyLayerLinkAnimation, &pyLayerLinkAnimation_Type);
    pyobj->fThis = layer;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
