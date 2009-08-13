#include <PyPlasma.h>
#include <PRP/Avatar/plAGAnim.h>
#include "pyAGAnim.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyAgeGlobalAnim_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAgeGlobalAnim* self = (pyAgeGlobalAnim*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAgeGlobalAnim();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAgeGlobalAnim_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyAgeGlobalAnim_FromAgeGlobalAnim(plAgeGlobalAnim::Convert(cre->fThis));
}

static PyObject* pyAgeGlobalAnim_getGlobalVarName(pyAgeGlobalAnim* self, void*) {
    return PlStr_To_PyStr(self->fThis->getVarName());
}

static int pyAgeGlobalAnim_setGlobalVarName(pyAgeGlobalAnim* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "globalVarName should be a string");
        return -1;
    }
    self->fThis->setVarName(PyStr_To_PlStr(value));
    return 0;
}

static PyMethodDef pyAgeGlobalAnim_Methods[] = {
    { "Convert", (PyCFunction)pyAgeGlobalAnim_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plAgeGlobalAnim" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyAgeGlobalAnim_GetSet[] = {
    { "globalVarName", (getter)pyAgeGlobalAnim_getGlobalVarName, (setter)pyAgeGlobalAnim_setGlobalVarName, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAgeGlobalAnim_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plAgeGlobalAnim",         /* tp_name */
    sizeof(pyAgeGlobalAnim),            /* tp_basicsize */
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
    "plAgeGlobalAnim wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAgeGlobalAnim_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyAgeGlobalAnim_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAgeGlobalAnim_new,                /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyAgeGlobalAnim_Type() {
    pyAgeGlobalAnim_Type.tp_base = &pyAGAnim_Type;
    if (PyType_Ready(&pyAgeGlobalAnim_Type) < 0)
        return NULL;

    Py_INCREF(&pyAgeGlobalAnim_Type);
    return (PyObject*)&pyAgeGlobalAnim_Type;
}

int pyAgeGlobalAnim_Check(PyObject* obj) {
    if (obj->ob_type == &pyAgeGlobalAnim_Type
        || PyType_IsSubtype(obj->ob_type, &pyAgeGlobalAnim_Type))
        return 1;
    return 0;
}

PyObject* pyAgeGlobalAnim_FromAgeGlobalAnim(class plAgeGlobalAnim* anim) {
    if (anim == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAgeGlobalAnim* pyobj = PyObject_New(pyAgeGlobalAnim, &pyAgeGlobalAnim_Type);
    pyobj->fThis = anim;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
