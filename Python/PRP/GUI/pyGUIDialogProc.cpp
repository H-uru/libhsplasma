#include <PyPlasma.h>
#include <PRP/GUI/pfGUIControlHandlers.h>
#include "pyGUIControlHandlers.h"

extern "C" {

static PyObject* pyGUIDialogProc_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyGUIDialogProc* self = (pyGUIDialogProc*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new pfGUIDialogProc();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PyTypeObject pyGUIDialogProc_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.pfGUIDialogProc",         /* tp_name */
    sizeof(pyGUIDialogProc),            /* tp_basicsize */
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
    "pfGUIDialogProc wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyGUIDialogProc_new,                /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyGUIDialogProc_Type() {
    pyGUIDialogProc_Type.tp_base = &pyGUICtrlProcObject_Type;
    if (PyType_Ready(&pyGUIDialogProc_Type) < 0)
        return NULL;

    Py_INCREF(&pyGUIDialogProc_Type);
    return (PyObject*)&pyGUIDialogProc_Type;
}

int pyGUIDialogProc_Check(PyObject* obj) {
    if (obj->ob_type == &pyGUIDialogProc_Type
        || PyType_IsSubtype(obj->ob_type, &pyGUIDialogProc_Type))
        return 1;
    return 0;
}

PyObject* pyGUIDialogProc_FromGUIDialogProc(pfGUIDialogProc* proc) {
    if (proc == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyGUIDialogProc* pyobj = PyObject_New(pyGUIDialogProc, &pyGUIDialogProc_Type);
    pyobj->fThis = proc;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
