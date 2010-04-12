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
#include "PRP/Animation/pyAnimTimeConvert.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyLayerAnimation_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyLayerAnimation* self = (pyLayerAnimation*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plLayerAnimation();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyLayerAnimation_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyLayerAnimation_FromLayerAnimation(plLayerAnimation::Convert(cre->fThis));
}

static PyObject* pyLayerAnimation_getTimeConvert(pyLayerAnimation* self, void*) {
    return pyAnimTimeConvert_FromAnimTimeConvert(&self->fThis->getTimeConvert());
}

static int pyLayerAnimation_setTimeConvert(pyLayerAnimation* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "timeConvert cannot be assigned");
    return -1;
}

static PyMethodDef pyLayerAnimation_Methods[] = {
    { "Convert", (PyCFunction)pyLayerAnimation_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plLayerAnimation" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLayerAnimation_GetSet[] = {
    { "timeConvert", (getter)pyLayerAnimation_getTimeConvert, (setter)pyLayerAnimation_setTimeConvert, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLayerAnimation_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plLayerAnimation",        /* tp_name */
    sizeof(pyLayerAnimation),           /* tp_basicsize */
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
    "plLayerAnimation wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLayerAnimation_Methods,           /* tp_methods */
    NULL,                               /* tp_members */
    pyLayerAnimation_GetSet,            /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLayerAnimation_new,               /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyLayerAnimation_Type() {
    pyLayerAnimation_Type.tp_base = &pyLayerAnimationBase_Type;
    if (PyType_Ready(&pyLayerAnimation_Type) < 0)
        return NULL;

    Py_INCREF(&pyLayerAnimation_Type);
    return (PyObject*)&pyLayerAnimation_Type;
}

int pyLayerAnimation_Check(PyObject* obj) {
    if (obj->ob_type == &pyLayerAnimation_Type
        || PyType_IsSubtype(obj->ob_type, &pyLayerAnimation_Type))
        return 1;
    return 0;
}

PyObject* pyLayerAnimation_FromLayerAnimation(class plLayerAnimation* layer) {
    if (layer == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLayerAnimation* pylay = PyObject_New(pyLayerAnimation, &pyLayerAnimation_Type);
    pylay->fThis = layer;
    pylay->fPyOwned = false;
    return (PyObject*)pylay;
}

}
