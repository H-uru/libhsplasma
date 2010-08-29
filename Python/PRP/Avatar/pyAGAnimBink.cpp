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
#include <PRP/Avatar/plATCAnim.h>
#include "pyATCAnim.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyAGAnimBink_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAGAnimBink* self = (pyAGAnimBink*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAGAnimBink();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAGAnimBink_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyAGAnimBink_FromAGAnimBink(plAGAnimBink::Convert(IConvert(cre)));
}

static PyObject* pyAGAnimBink_getBinkFilename(pyAGAnimBink* self, void*) {
    return PlStr_To_PyStr(self->fThis->getBinkFilename());
}

static PyObject* pyAGAnimBink_getSgtFilename(pyAGAnimBink* self, void*) {
    return PlStr_To_PyStr(self->fThis->getSgtFilename());
}

static PyObject* pyAGAnimBink_getSubtitleId(pyAGAnimBink* self, void*) {
    return PlStr_To_PyStr(self->fThis->getSubtitleId());
}

static int pyAGAnimBink_setBinkFilename(pyAGAnimBink* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "binkFilename should be a string");
        return -1;
    }
    self->fThis->setBinkFilename(PyStr_To_PlStr(value));
    return 0;
}

static int pyAGAnimBink_setSgtFilename(pyAGAnimBink* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "sgtFilename should be a string");
        return -1;
    }
    self->fThis->setSgtFilename(PyStr_To_PlStr(value));
    return 0;
}

static int pyAGAnimBink_setSubtitleId(pyAGAnimBink* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "subtitleId should be a string");
        return -1;
    }
    self->fThis->setSubtitleId(PyStr_To_PlStr(value));
    return 0;
}

static PyMethodDef pyAGAnimBink_Methods[] = {
    { "Convert", (PyCFunction)pyAGAnimBink_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plAGAnimBink" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyAGAnimBink_GetSet[] = {
    { "binkFilename", (getter)pyAGAnimBink_getBinkFilename, (setter)pyAGAnimBink_setBinkFilename, NULL, NULL },
    { "sgtFilename", (getter)pyAGAnimBink_getSgtFilename, (setter)pyAGAnimBink_setSgtFilename, NULL, NULL },
    { "subtitleId", (getter)pyAGAnimBink_getSubtitleId, (setter)pyAGAnimBink_setSubtitleId, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAGAnimBink_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plAGAnimBink",            /* tp_name */
    sizeof(pyAGAnimBink),               /* tp_basicsize */
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
    "plAGAnimBink wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAGAnimBink_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    pyAGAnimBink_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAGAnimBink_new,                   /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyAGAnimBink_Type() {
    pyAGAnimBink_Type.tp_base = &pyATCAnim_Type;
    if (PyType_Ready(&pyAGAnimBink_Type) < 0)
        return NULL;

    Py_INCREF(&pyAGAnimBink_Type);
    return (PyObject*)&pyAGAnimBink_Type;
}

int pyAGAnimBink_Check(PyObject* obj) {
    if (obj->ob_type == &pyAGAnimBink_Type
        || PyType_IsSubtype(obj->ob_type, &pyAGAnimBink_Type))
        return 1;
    return 0;
}

PyObject* pyAGAnimBink_FromAGAnimBink(class plAGAnimBink* anim) {
    if (anim == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAGAnimBink* pyobj = PyObject_New(pyAGAnimBink, &pyAGAnimBink_Type);
    pyobj->fThis = anim;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
