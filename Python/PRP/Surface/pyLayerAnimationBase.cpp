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
#include "pyLayer.h"
#include "pyLayerAnimation.h"
#include "PRP/Animation/pyController.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyLayerAnimationBase_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plLayerAnimationBase is abstract");
    return NULL;
}

static PyObject* pyLayerAnimationBase_getPreshade(pyLayerAnimationBase* self, void*) {
    return pyController_FromController(self->fThis->getPreshadeCtl());
}

static PyObject* pyLayerAnimationBase_getRuntime(pyLayerAnimationBase* self, void*) {
    return pyController_FromController(self->fThis->getRuntimeCtl());
}

static PyObject* pyLayerAnimationBase_getAmbient(pyLayerAnimationBase* self, void*) {
    return pyController_FromController(self->fThis->getAmbientCtl());
}

static PyObject* pyLayerAnimationBase_getSpecular(pyLayerAnimationBase* self, void*) {
    return pyController_FromController(self->fThis->getSpecularCtl());
}

static PyObject* pyLayerAnimationBase_getOpacity(pyLayerAnimationBase* self, void*) {
    return pyController_FromController(self->fThis->getOpacityCtl());
}

static PyObject* pyLayerAnimationBase_getTransform(pyLayerAnimationBase* self, void*) {
    return pyController_FromController(self->fThis->getTransformCtl());
}

static int pyLayerAnimationBase_setPreshade(pyLayerAnimationBase* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setPreshadeCtl(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "preshadeCtl should be a plController");
        return -1;
    }
    self->fThis->setPreshadeCtl(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static int pyLayerAnimationBase_setRuntime(pyLayerAnimationBase* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setRuntimeCtl(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "runtimeCtl should be a plController");
        return -1;
    }
    self->fThis->setRuntimeCtl(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static int pyLayerAnimationBase_setAmbient(pyLayerAnimationBase* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setAmbientCtl(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ambientCtl should be a plController");
        return -1;
    }
    self->fThis->setAmbientCtl(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static int pyLayerAnimationBase_setSpecular(pyLayerAnimationBase* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setSpecularCtl(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "specularCtl should be a plController");
        return -1;
    }
    self->fThis->setSpecularCtl(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static int pyLayerAnimationBase_setOpacity(pyLayerAnimationBase* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setOpacityCtl(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "opacityCtl should be a plController");
        return -1;
    }
    self->fThis->setOpacityCtl(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static int pyLayerAnimationBase_setTransform(pyLayerAnimationBase* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setTransformCtl(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "transformCtl should be a plController");
        return -1;
    }
    self->fThis->setTransformCtl(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static PyMethodDef pyLayerAnimationBase_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLayerAnimationBase_GetSet[] = {
    { _pycs("preshadeCtl"), (getter)pyLayerAnimationBase_getPreshade,
        (setter)pyLayerAnimationBase_setPreshade, NULL, NULL },
    { _pycs("runtimeCtl"), (getter)pyLayerAnimationBase_getRuntime,
        (setter)pyLayerAnimationBase_setRuntime, NULL, NULL },
    { _pycs("ambientCtl"), (getter)pyLayerAnimationBase_getAmbient,
        (setter)pyLayerAnimationBase_setAmbient, NULL, NULL },
    { _pycs("specularCtl"), (getter)pyLayerAnimationBase_getSpecular,
        (setter)pyLayerAnimationBase_setSpecular, NULL, NULL },
    { _pycs("opacityCtl"), (getter)pyLayerAnimationBase_getOpacity,
        (setter)pyLayerAnimationBase_setOpacity, NULL, NULL },
    { _pycs("transformCtl"), (getter)pyLayerAnimationBase_getTransform,
        (setter)pyLayerAnimationBase_setTransform, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLayerAnimationBase_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plLayerAnimationBase",  /* tp_name */
    sizeof(pyLayerAnimationBase),       /* tp_basicsize */
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
    "plLayerAnimationBase wrapper",     /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLayerAnimationBase_Methods,       /* tp_methods */
    NULL,                               /* tp_members */
    pyLayerAnimationBase_GetSet,        /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLayerAnimationBase_new,           /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pyLayerAnimationBase_Type() {
    pyLayerAnimationBase_Type.tp_base = &pyLayerInterface_Type;
    if (PyType_Ready(&pyLayerAnimationBase_Type) < 0)
        return NULL;

    Py_INCREF(&pyLayerAnimationBase_Type);
    return (PyObject*)&pyLayerAnimationBase_Type;
}

int pyLayerAnimationBase_Check(PyObject* obj) {
    if (obj->ob_type == &pyLayerAnimationBase_Type
        || PyType_IsSubtype(obj->ob_type, &pyLayerAnimationBase_Type))
        return 1;
    return 0;
}

PyObject* pyLayerAnimationBase_FromLayerAnimationBase(class plLayerAnimationBase* layer) {
    if (layer == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLayerAnimationBase* pylay = PyObject_New(pyLayerAnimationBase, &pyLayerAnimationBase_Type);
    pylay->fThis = layer;
    pylay->fPyOwned = false;
    return (PyObject*)pylay;
}

}
