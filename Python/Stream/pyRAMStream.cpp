#include <PyPlasma.h>
#include <Stream/hsRAMStream.h>
#include "pyStream.h"

extern "C" {

static void pyRAMStream_dealloc(pyRAMStream* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* pyRAMStream_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyRAMStream* self = (pyRAMStream*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsRAMStream();
    return (PyObject*)self;
}

static PyObject* pyRAMStream_resize(pyRAMStream* self, PyObject* args) {
    int newSize;

    if (!PyArg_ParseTuple(args, "i", &newSize)) {
        PyErr_SetString(PyExc_TypeError, "resize expects an int");
        return NULL;
    }
    self->fThis->resize(newSize);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyRAMStream_getBuffer(pyRAMStream* self, void* closure) {
    char* buf = new char[self->fThis->size()];
    self->fThis->copyTo(buf, self->fThis->size());
    PyObject* bufObj = PyBytes_FromStringAndSize(buf, self->fThis->size());
    delete[] buf;
    return bufObj;
}

static int pyRAMStream_setBuffer(pyRAMStream* self, PyObject* value, void* closure) {
    if (!PyBytes_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "buffer should be a binary string");
        return -1;
    }
    char* buf;
    Py_ssize_t len;
    PyBytes_AsStringAndSize(value, &buf, &len);
    self->fThis->copyFrom(buf, len);
    return 0;
}

static PyMethodDef pyRAMStream_Methods[] = {
    { "resize", (PyCFunction)pyRAMStream_resize, METH_VARARGS,
      "Params: newsize\n"
      "Allocates newsize bytes in the internal buffer.  This will truncate "
      "data if it's shorter than the current buffer, or zero-fill the extra "
      "space if it's larger than the current buffer." },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyRAMStream_GetSet[] = {
    { "buffer", (getter)pyRAMStream_getBuffer, (setter)pyRAMStream_setBuffer,
      "The internal RAM buffer of this stream", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyRAMStream_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsRAMStream",           /* tp_name */
    sizeof(pyRAMStream),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyRAMStream_dealloc,    /* tp_dealloc */
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
    "hsRAMStream wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyRAMStream_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyRAMStream_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyRAMStream_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyRAMStream_Type() {
    pyRAMStream_Type.tp_base = &pyStream_Type;
    if (PyType_Ready(&pyRAMStream_Type) < 0)
        return NULL;

    Py_INCREF(&pyRAMStream_Type);
    return (PyObject*)&pyRAMStream_Type;
}

}
