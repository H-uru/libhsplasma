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
#include <PRP/Surface/plRenderTarget.h>
#include "pyRenderTarget.h"
#include "pyBitmap.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyRenderTarget_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyRenderTarget* self = (pyRenderTarget*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plRenderTarget();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyRenderTarget_getWidth(pyRenderTarget* self, void*) {
    return PyInt_FromLong(self->fThis->getWidth());
}

static PyObject* pyRenderTarget_getHeight(pyRenderTarget* self, void*) {
    return PyInt_FromLong(self->fThis->getHeight());
}

static PyObject* pyRenderTarget_getProportionalViewport(pyRenderTarget* self, void*) {
    return PyBool_FromLong(self->fThis->getProportionalViewport() ? 1 : 0);
}

static PyObject* pyRenderTarget_getViewportLeft(pyRenderTarget* self, void*) {
    plRenderTarget* rt = self->fThis;
    if (rt->getProportionalViewport())
        return PyFloat_FromDouble(rt->getProportionalViewportLeft());
    else
        return PyInt_FromLong(rt->getAbsoluteViewportLeft());
}

static PyObject* pyRenderTarget_getViewportTop(pyRenderTarget* self, void*) {
    plRenderTarget* rt = self->fThis;
    if (rt->getProportionalViewport())
        return PyFloat_FromDouble(rt->getProportionalViewportTop());
    else
        return PyInt_FromLong(rt->getAbsoluteViewportTop());
}

static PyObject* pyRenderTarget_getViewportRight(pyRenderTarget* self, void*) {
    plRenderTarget* rt = self->fThis;
    if (rt->getProportionalViewport())
        return PyFloat_FromDouble(rt->getProportionalViewportRight());
    else
        return PyInt_FromLong(rt->getAbsoluteViewportRight());
}

static PyObject* pyRenderTarget_getViewportBottom(pyRenderTarget* self, void*) {
    plRenderTarget* rt = self->fThis;
    if (rt->getProportionalViewport())
        return PyFloat_FromDouble(rt->getProportionalViewportBottom());
    else
        return PyInt_FromLong(rt->getAbsoluteViewportBottom());
}

static PyObject* pyRenderTarget_getZDepth(pyRenderTarget* self, void*) {
    return PyInt_FromLong(self->fThis->getZDepth());
}

static PyObject* pyRenderTarget_getStencilDepth(pyRenderTarget* self, void*) {
    return PyInt_FromLong(self->fThis->getStencilDepth());
}

static int pyRenderTarget_setWidth(pyRenderTarget* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "width should be an int");
        return -1;
    }
    self->fThis->setWidth(PyInt_AsLong(value));
    return 0;
}

static int pyRenderTarget_setHeight(pyRenderTarget* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "height should be an int");
        return -1;
    }
    self->fThis->setHeight(PyInt_AsLong(value));
    return 0;
}

static int pyRenderTarget_setProportionalViewport(pyRenderTarget* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "proportionalViewport should be a boolean");
        return -1;
    }
    self->fThis->setProportionalViewport(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyRenderTarget_setViewportLeft(pyRenderTarget* self, PyObject* value, void*) {
    plRenderTarget* rt = self->fThis;
    if (rt->getProportionalViewport()) {
        if (value == NULL || !PyFloat_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "viewportLeft should be a float");
            return -1;
        }
        rt->setProportionalViewportLeft((float)PyFloat_AsDouble(value));
    } else {
        if (value == NULL || !PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "viewportLeft should be an int");
            return -1;
        }
        rt->setAbsoluteViewportLeft(PyInt_AsLong(value));
    }
    return 0;
}

static int pyRenderTarget_setViewportTop(pyRenderTarget* self, PyObject* value, void*) {
    plRenderTarget* rt = self->fThis;
    if (rt->getProportionalViewport()) {
        if (value == NULL || !PyFloat_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "viewportTop should be a float");
            return -1;
        }
        rt->setProportionalViewportTop((float)PyFloat_AsDouble(value));
    } else {
        if (value == NULL || !PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "viewportTop should be an int");
            return -1;
        }
        rt->setAbsoluteViewportTop(PyInt_AsLong(value));
    }
    return 0;
}

static int pyRenderTarget_setViewportRight(pyRenderTarget* self, PyObject* value, void*) {
    plRenderTarget* rt = self->fThis;
    if (rt->getProportionalViewport()) {
        if (value == NULL || !PyFloat_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "viewportRight should be a float");
            return -1;
        }
        rt->setProportionalViewportRight((float)PyFloat_AsDouble(value));
    } else {
        if (value == NULL || !PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "viewportRight should be an int");
            return -1;
        }
        rt->setAbsoluteViewportRight(PyInt_AsLong(value));
    }
    return 0;
}

static int pyRenderTarget_setViewportBottom(pyRenderTarget* self, PyObject* value, void*) {
    plRenderTarget* rt = self->fThis;
    if (rt->getProportionalViewport()) {
        if (value == NULL || !PyFloat_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "viewportBottom should be a float");
            return -1;
        }
        rt->setProportionalViewportBottom((float)PyFloat_AsDouble(value));
    } else {
        if (value == NULL || !PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "viewportBottom should be an int");
            return -1;
        }
        rt->setAbsoluteViewportBottom(PyInt_AsLong(value));
    }
    return 0;
}

static int pyRenderTarget_setZDepth(pyRenderTarget* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ZDepth should be an int");
        return -1;
    }
    self->fThis->setZDepth(PyInt_AsLong(value));
    return 0;
}

static int pyRenderTarget_setStencilDepth(pyRenderTarget* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "stencilDepth should be an int");
        return -1;
    }
    self->fThis->setStencilDepth(PyInt_AsLong(value));
    return 0;
}

static PyGetSetDef pyRenderTarget_GetSet[] = {
    { _pycs("width"), (getter)pyRenderTarget_getWidth,
        (setter)pyRenderTarget_setWidth, NULL, NULL },
    { _pycs("height"), (getter)pyRenderTarget_getHeight,
        (setter)pyRenderTarget_setHeight, NULL, NULL },
    { _pycs("proportionalViewport"), (getter)pyRenderTarget_getProportionalViewport,
        (setter)pyRenderTarget_setProportionalViewport, NULL, NULL },
    { _pycs("viewportLeft"), (getter)pyRenderTarget_getViewportLeft,
        (setter)pyRenderTarget_setViewportLeft, NULL, NULL },
    { _pycs("viewportTop"), (getter)pyRenderTarget_getViewportTop,
        (setter)pyRenderTarget_setViewportTop, NULL, NULL },
    { _pycs("viewportRight"), (getter)pyRenderTarget_getViewportRight,
        (setter)pyRenderTarget_setViewportRight, NULL, NULL },
    { _pycs("viewportBottom"), (getter)pyRenderTarget_getViewportBottom,
        (setter)pyRenderTarget_setViewportBottom, NULL, NULL },
    { _pycs("ZDepth"), (getter)pyRenderTarget_getZDepth,
        (setter)pyRenderTarget_setZDepth, NULL, NULL },
    { _pycs("stencilDepth"), (getter)pyRenderTarget_getStencilDepth,
        (setter)pyRenderTarget_setStencilDepth, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyRenderTarget_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plRenderTarget",        /* tp_name */
    sizeof(pyRenderTarget),             /* tp_basicsize */
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
    "plRenderTarget wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyRenderTarget_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyRenderTarget_new,                 /* tp_new */
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

PyObject* Init_pyRenderTarget_Type() {
    pyRenderTarget_Type.tp_base = &pyBitmap_Type;
    if (PyType_Ready(&pyRenderTarget_Type) < 0)
        return NULL;

    Py_INCREF(&pyRenderTarget_Type);
    return (PyObject*)&pyRenderTarget_Type;
}

int pyRenderTarget_Check(PyObject* obj) {
    if (obj->ob_type == &pyRenderTarget_Type
        || PyType_IsSubtype(obj->ob_type, &pyRenderTarget_Type))
        return 1;
    return 0;
}

PyObject* pyRenderTarget_FromRenderTarget(class plRenderTarget* rt) {
    if (rt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyRenderTarget* pyrt = PyObject_New(pyRenderTarget, &pyRenderTarget_Type);
    pyrt->fThis = rt;
    pyrt->fPyOwned = false;
    return (PyObject*)pyrt;
}

}
