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

#include "pyColor.h"

#include <Sys/hsColor.h>
#include "Stream/pyStream.h"

extern "C" {

PY_PLASMA_VALUE_DEALLOC(Color32)

static PyObject* pyColor32_set(pyColor32* self, PyObject* args, PyObject* kwds) {
    int red = 0, green = 0, blue = 0, alpha = 255, color = 0xFF000000;

    static char* kwlist1[] = { _pycs("red"), _pycs("green"), _pycs("blue"),
                               _pycs("alpha"), NULL };
    static char* kwlist2[] = { _pycs("color"), NULL };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist2, &color)) {
        self->fThis->color = color;
    } else if (PyErr_Clear(), PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", kwlist1,
                                                          &red, &green, &blue, &alpha)) {
        self->fThis->r = red;
        self->fThis->g = green;
        self->fThis->b = blue;
        self->fThis->a = alpha;
    } else {
        PyErr_SetString(PyExc_TypeError, "set expects 0-4 ints");
        return NULL;
    }

    Py_RETURN_NONE;
}

PY_PLASMA_INIT_DECL(Color32) {
    PyObject* retn = pyColor32_set(self, args, kwds);
    if (retn == NULL)
        return -1;
    Py_DECREF(retn);
    return 0;
}

PY_PLASMA_VALUE_NEW(Color32, hsColor32)

static PyObject* pyColor32_Repr(pyColor32* self) {
    plString repr = plString::Format("hsColor32(%u, %u, %u, %u)",
        self->fThis->r, self->fThis->g, self->fThis->b, self->fThis->a);
    return PlStr_To_PyStr(repr);
}

static PyObject* pyColor32_read32(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read32 expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read32 expects a hsStream");
        return NULL;
    }
    self->fThis->read32(stream->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyColor32_write32(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write32 expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write32 expects a hsStream");
        return NULL;
    }
    self->fThis->write32(stream->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyColor32_readRGBA8(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGBA8 expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGBA8 expects a hsStream");
        return NULL;
    }
    self->fThis->readRGBA8(stream->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyColor32_writeRGBA8(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGBA8 expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGBA8 expects a hsStream");
        return NULL;
    }
    self->fThis->writeRGBA8(stream->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyColor32_readRGB8(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGB8 expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGB8 expects a hsStream");
        return NULL;
    }
    self->fThis->readRGB8(stream->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyColor32_writeRGB8(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGB8 expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGB8 expects a hsStream");
        return NULL;
    }
    self->fThis->writeRGB8(stream->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyColor32_Methods[] = {
    { "set", (PyCFunction)pyColor32_set, METH_VARARGS | METH_KEYWORDS,
      "Params: red, green, blue, alpha (all optional)\n"
      "Params: color (32-bit value)\n"
      "Sets the color" },
    { "read32", (PyCFunction)pyColor32_read32, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from `stream`" },
    { "write32", (PyCFunction)pyColor32_write32, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to `stream`" },
    { "readRGBA8", (PyCFunction)pyColor32_readRGBA8, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from `stream`" },
    { "writeRGBA8", (PyCFunction)pyColor32_writeRGBA8, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to `stream`" },
    { "readRGB8", (PyCFunction)pyColor32_readRGB8, METH_VARARGS,
      "Params: stream\n"
      "Same as readRGBA8(), but does not read alpha" },
    { "writeRGB8", (PyCFunction)pyColor32_writeRGB8, METH_VARARGS,
      "Params: stream\n"
      "Same as writeRGBA8(), but does not write alpha" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY_MEMBER(unsigned char, Color32, red, r)
PY_PROPERTY_MEMBER(unsigned char, Color32, green, g)
PY_PROPERTY_MEMBER(unsigned char, Color32, blue, b)
PY_PROPERTY_MEMBER(unsigned char, Color32, alpha, a)
PY_PROPERTY_MEMBER(unsigned int, Color32, color, color)

static PyGetSetDef pyColor32_GetSet[] = {
    pyColor32_red_getset,
    pyColor32_green_getset,
    pyColor32_blue_getset,
    pyColor32_alpha_getset,
    pyColor32_color_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyColor32_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsColor32",             /* tp_name */
    sizeof(pyColor32),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyColor32_dealloc,                  /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    (reprfunc)pyColor32_Repr,           /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "hsColor32 wrapper",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyColor32_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    pyColor32_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyColor32___init__,                 /* tp_init */
    NULL,                               /* tp_alloc */
    pyColor32_new,                      /* tp_new */
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

PyObject* Init_pyColor32_Type() {
    if (PyType_Ready(&pyColor32_Type) < 0)
        return NULL;

    Py_INCREF(&pyColor32_Type);
    return (PyObject*)&pyColor32_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Color32, hsColor32)

}
