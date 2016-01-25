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
#include <PRP/KeyedObject/plLocation.h>
#include "pyKey.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyLocation_dealloc(pyLocation* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyLocation___init__(pyLocation* self, PyObject* args, PyObject* kwds) {
    int version = PlasmaVer::pvUnknown;
    if (!PyArg_ParseTuple(args, "|i", &version))
        return -1;

    self->fThis->setVer((PlasmaVer)version);
    return 0;
}

static PyObject* pyLocation_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyLocation* self = (pyLocation*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new plLocation();
    return (PyObject*)self;
}

static PyObject* pyLocation_Repr(pyLocation* self) {
    plString repr = plString::Format("<plLocation \"%d|%d\">",
                                     self->fThis->getSeqPrefix(),
                                     self->fThis->getPageNum());
    return PlStr_To_PyStr(repr);
}

static long pyLocation_Hash(pyLocation* self) {
    return (long)self->fThis->unparse();
}

static PyObject* pyLocation_RichCompare(pyLocation* left, pyLocation* right, int op) {
    bool result = false;

    switch (op) {
    case Py_LT:
        result = ((*left->fThis) < (*right->fThis));
        break;
    case Py_LE:
        result = ((*left->fThis) == (*right->fThis))
               || ((*left->fThis) < (*right->fThis));
        break;
    case Py_EQ:
        result = ((*left->fThis) == (*right->fThis));
        break;
    case Py_NE:
        result = !((*left->fThis) == (*right->fThis));
        break;
    case Py_GT:
        result = !((*left->fThis) < (*right->fThis))
               && !((*left->fThis) == (*right->fThis));
        break;
    case Py_GE:
        result = !((*left->fThis) < (*right->fThis));
        break;
    default:
        PyErr_SetString(PyExc_RuntimeError, "Comparison failed");
        return NULL;
    }

    if (result) {
        Py_INCREF(Py_True);
        return Py_True;
    } else {
        Py_INCREF(Py_False);
        return Py_False;
    }
}

static PyObject* pyLocation_read(pyLocation* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLocation_write(pyLocation* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLocation_invalidate(pyLocation* self) {
    self->fThis->invalidate();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLocation_isValid(pyLocation* self) {
    return PyBool_FromLong(self->fThis->isValid() ? 1 : 0);
}

static PyObject* pyLocation_isReserved(pyLocation* self) {
    return PyBool_FromLong(self->fThis->isReserved() ? 1 : 0);
}

static PyObject* pyLocation_isItinerant(pyLocation* self) {
    return PyBool_FromLong(self->fThis->isItinerant() ? 1 : 0);
}

static PyObject* pyLocation_isVirtual(pyLocation* self) {
    return PyBool_FromLong(self->fThis->isVirtual() ? 1 : 0);
}

static PyObject* pyLocation_isGlobal(pyLocation* self) {
    return PyBool_FromLong(self->fThis->isGlobal() ? 1 : 0);
}

static PyObject* pyLocation_setVirtual(pyLocation* self) {
    self->fThis->setVirtual();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLocation_parse(pyLocation* self, PyObject* args) {
    int loc;
    if (!PyArg_ParseTuple(args, "i", &loc)) {
        PyErr_SetString(PyExc_TypeError, "parse expects an int");
        return NULL;
    }
    self->fThis->parse(loc);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLocation_unparse(pyLocation* self) {
    return PyInt_FromLong(self->fThis->unparse());
}

static PyObject* pyLocation_getVer(pyLocation* self, void*) {
    return PyInt_FromLong(self->fThis->getVer());
}

static PyObject* pyLocation_getPrefix(pyLocation* self, void*) {
    return PyInt_FromLong(self->fThis->getSeqPrefix());
}

static PyObject* pyLocation_getPage(pyLocation* self, void*) {
    return PyInt_FromLong(self->fThis->getPageNum());
}

static PyObject* pyLocation_getFlags(pyLocation* self, void*) {
    return PyInt_FromLong(self->fThis->getFlags());
}


static int pyLocation_setVer(pyLocation* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setVer(PlasmaVer::pvUnknown);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "version must be an int");
            return -1;
        }
        self->fThis->setVer((PlasmaVer)PyInt_AsLong(value));
    }
    return 0;
}

static int pyLocation_setPrefix(pyLocation* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setSeqPrefix(-1);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "prefix must be an int");
            return -1;
        }
        self->fThis->setSeqPrefix(PyInt_AsLong(value));
    }
    return 0;
}

static int pyLocation_setPage(pyLocation* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setPageNum(-1);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "page must be an int");
            return -1;
        }
        self->fThis->setPageNum(PyInt_AsLong(value));
    }
    return 0;
}

static int pyLocation_setFlags(pyLocation* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setFlags(-1);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "flags must be an int");
            return -1;
        }
        self->fThis->setFlags(PyInt_AsLong(value));
    }
    return 0;
}

static PyMethodDef pyLocation_Methods[] = {
    { "read", (PyCFunction)pyLocation_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this Location from the stream, including the size and offset" },
    { "write", (PyCFunction)pyLocation_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this Location to the stream, including the size and offset" },
    { "invalidate", (PyCFunction)pyLocation_invalidate, METH_NOARGS,
      "Invalidates the location" },
    { "isValid", (PyCFunction)pyLocation_isValid, METH_NOARGS,
      "Returns True if the location is valid" },
    { "isReserved", (PyCFunction)pyLocation_isReserved, METH_NOARGS,
      "Returns True if the location is a Reserved page" },
    { "isItinerant", (PyCFunction)pyLocation_isItinerant, METH_NOARGS,
      "Returns True if the location is an Itinerant page" },
    { "isVirtual", (PyCFunction)pyLocation_isVirtual, METH_NOARGS,
      "Returns True if the location is virtual" },
    { "isGlobal", (PyCFunction)pyLocation_isGlobal, METH_NOARGS,
      "Returns True if the sequence prefix points to a global age" },
    { "setVirtual", (PyCFunction)pyLocation_setVirtual, METH_NOARGS,
      "Makes the location virtual" },
    { "parse", (PyCFunction)pyLocation_parse, METH_VARARGS,
      "Params: locationId\n"
      "Parses a raw location" },
    { "unparse", (PyCFunction)pyLocation_unparse, METH_NOARGS,
      "Returns a raw location ID for the set Plasma version" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLocation_GetSet[] = {
    { _pycs("version"), (getter)pyLocation_getVer, (setter)pyLocation_setVer,
        _pycs("The Plasma Version (for file parsing)"), NULL },
    { _pycs("prefix"), (getter)pyLocation_getPrefix, (setter)pyLocation_setPrefix,
        _pycs("The Sequence Prefix of the age"), NULL },
    { _pycs("page"), (getter)pyLocation_getPage, (setter)pyLocation_setPage,
        _pycs("The Page Number of the page"), NULL },
    { _pycs("flags"), (getter)pyLocation_getFlags, (setter)pyLocation_setFlags,
        _pycs("The Location flags"), NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLocation_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plLocation",            /* tp_name */
    sizeof(pyLocation),                 /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyLocation_dealloc,     /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    (reprfunc)pyLocation_Repr,          /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    (hashfunc)pyLocation_Hash,          /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    NULL,                               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    (richcmpfunc)pyLocation_RichCompare, /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLocation_Methods,                 /* tp_methods */
    NULL,                               /* tp_members */
    pyLocation_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyLocation___init__,      /* tp_init */
    NULL,                               /* tp_alloc */
    pyLocation_new,                     /* tp_new */
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

PyObject* Init_pyLocation_Type() {
    if (PyType_Ready(&pyLocation_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyLocation_Type.tp_dict, "kLocalOnly",
                         PyInt_FromLong(plLocation::kLocalOnly));
    PyDict_SetItemString(pyLocation_Type.tp_dict, "kVolatile",
                         PyInt_FromLong(plLocation::kVolatile));
    PyDict_SetItemString(pyLocation_Type.tp_dict, "kReserved",
                         PyInt_FromLong(plLocation::kReserved));
    PyDict_SetItemString(pyLocation_Type.tp_dict, "kBuiltIn",
                         PyInt_FromLong(plLocation::kBuiltIn));
    PyDict_SetItemString(pyLocation_Type.tp_dict, "kItinerant",
                         PyInt_FromLong(plLocation::kItinerant));

    Py_INCREF(&pyLocation_Type);
    return (PyObject*)&pyLocation_Type;
}

int pyLocation_Check(PyObject* obj) {
    if (obj->ob_type == &pyLocation_Type
        || PyType_IsSubtype(obj->ob_type, &pyLocation_Type))
        return 1;
    return 0;
}

PyObject* pyLocation_FromLocation(const plLocation& loc) {
    pyLocation* obj = PyObject_New(pyLocation, &pyLocation_Type);
    obj->fThis = new plLocation(loc);
    return (PyObject*)obj;
}

}
