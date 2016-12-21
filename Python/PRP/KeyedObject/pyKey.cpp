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

#include "pyKey.h"

#include <PRP/KeyedObject/plKey.h>
#include <PRP/KeyedObject/hsKeyedObject.h>
#include "PRP/pyCreatable.h"
#include "pyKeyedObject.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyKey_dealloc(pyKey* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* pyKey_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot construct Keys directly");
    return NULL;
}

static PyObject* pyKey_Repr(pyKey* self) {
    plString repr = plString::Format("<plKey \"%s\">", self->fThis->toString().cstr());
    return PlStr_To_PyStr(repr);
}

static long pyKey_Hash(pyKey* self) {
    return (long)(plKeyData*)(*self->fThis);
}

static PyObject* pyKey_RichCompare(pyKey* left, pyKey* right, int op) {
    bool result = false;

    if (!pyKey_Check((PyObject*)right)) {
        if ((PyObject*)right == Py_None) {
            if (op == Py_NE || op == Py_LT)
                result = true;
            else
                result = false;
        } else {
            PyErr_SetString(PyExc_TypeError, "Incompatible types in comparison");
            return NULL;
        }
    } else {
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
            result = ((*left->fThis) != (*right->fThis));
            break;
        case Py_GT:
            result = !((*left->fThis) < (*right->fThis))
                   && ((*left->fThis) != (*right->fThis));
            break;
        case Py_GE:
            result = !((*left->fThis) < (*right->fThis));
            break;
        default:
            PyErr_SetString(PyExc_RuntimeError, "Comparison failed");
            return NULL;
        }
    }

    if (result) {
        Py_INCREF(Py_True);
        return Py_True;
    } else {
        Py_INCREF(Py_False);
        return Py_False;
    }
}

static PyObject* pyKey_read(pyKey* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    (*self->fThis)->read(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyKey_write(pyKey* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    (*self->fThis)->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyKey_readUoid(pyKey* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readUoid expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readUoid expects an hsStream");
        return NULL;
    }
    (*self->fThis)->readUoid(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyKey_writeUoid(pyKey* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeUoid expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeUoid expects an hsStream");
        return NULL;
    }
    (*self->fThis)->writeUoid(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyKey_exists(pyKey* self) {
    return PyBool_FromLong(self->fThis->Exists() ? 1 : 0);
}

static PyObject* pyKey_isLoaded(pyKey* self) {
    return PyBool_FromLong(self->fThis->isLoaded() ? 1 : 0);
}

static PyObject* pyKey_getType(pyKey* self, void* closure) {
    return PyInt_FromLong((*self->fThis)->getType());
}

static PyObject* pyKey_getName(pyKey* self, void* closure) {
    return PlStr_To_PyStr((*self->fThis)->getName());
}

static PyObject* pyKey_getLocation(pyKey* self, void* closure) {
    return pyLocation_FromLocation((*self->fThis)->getLocation());
}

static PyObject* pyKey_getLoadMask(pyKey* self, void* closure) {
    return PyInt_FromLong((*self->fThis)->getLoadMask().getMask());
}

static PyObject* pyKey_getID(pyKey* self, void* closure) {
    return PyInt_FromLong((*self->fThis)->getID());
}

static PyObject* pyKey_getObj(pyKey* self, void* closure) {
    return ICreate((*self->fThis)->getObj());
}

static int pyKey_setType(pyKey* self, PyObject* value, void* closure) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot change a plKey's type");
    return -1;
}

static int pyKey_setName(pyKey* self, PyObject* value, void* closure) {
    if (value == NULL) {
        (*self->fThis)->setName("");
    } else {
        if (!PyAnyStr_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "name must be a string");
            return -1;
        }
        (*self->fThis)->setName(PyStr_To_PlStr(value));
    }
    return 0;
}

static int pyKey_setLocation(pyKey* self, PyObject* value, void* closure) {
    if (value == NULL) {
        (*self->fThis)->setLocation(plLocation());
    } else {
        if (!pyLocation_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "location must be a plLocation");
            return -1;
        }
        (*self->fThis)->setLocation(*((pyLocation*)value)->fThis);
    }
    return 0;
}

static int pyKey_setLoadMask(pyKey* self, PyObject* value, void* closure) {
    if (value == NULL) {
        (*self->fThis)->setLoadMask(plLoadMask());
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "mask must be an int");
            return -1;
        }
        plLoadMask mask;
        mask.setMask(PyInt_AsLong(value));
        (*self->fThis)->setLoadMask(mask);
    }
    return 0;
}

static int pyKey_setID(pyKey* self, PyObject* value, void* closure) {
    if (value == NULL) {
        (*self->fThis)->setID(0);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "id must be an int");
            return -1;
        }
        (*self->fThis)->setID(PyInt_AsLong(value));
    }
    return 0;
}

static int pyKey_setObj(pyKey* self, PyObject* value, void* closure) {
    PyErr_SetString(PyExc_RuntimeError, "object is read-only");
    return -1;
}

static PyMethodDef pyKey_Methods[] = {
    { "read", (PyCFunction)pyKey_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this key from the stream, including the size and offset" },
    { "write", (PyCFunction)pyKey_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this key to the stream, including the size and offset" },
    { "readUoid", (PyCFunction)pyKey_readUoid, METH_VARARGS,
      "Params: stream\n"
      "Reads this key from the stream" },
    { "writeUoid", (PyCFunction)pyKey_writeUoid, METH_VARARGS,
      "Params: stream\n"
      "Writes this key from the stream" },
    { "exists", (PyCFunction)pyKey_exists, METH_NOARGS,
      "Returns True if the key exists" },
    { "isLoaded", (PyCFunction)pyKey_isLoaded, METH_NOARGS,
      "Returns True if the key is loaded" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyKey_GetSet[] = {
    { _pycs("type"), (getter)pyKey_getType, (setter)pyKey_setType,
        _pycs("The Class Index of this plKey"), NULL },
    { _pycs("name"), (getter)pyKey_getName, (setter)pyKey_setName,
        _pycs("The name of this plKey"), NULL },
    { _pycs("location"), (getter)pyKey_getLocation, (setter)pyKey_setLocation,
        _pycs("The plLocation of this plKey"), NULL },
    { _pycs("mask"), (getter)pyKey_getLoadMask, (setter)pyKey_setLoadMask,
        _pycs("The Load Mask for this plKey"), NULL },
    { _pycs("id"), (getter)pyKey_getID, (setter)pyKey_setID,
        _pycs("The file index of this plKey (usually set automatically)"), NULL },
    { _pycs("object"), (getter)pyKey_getObj, (setter)pyKey_setObj,
        _pycs("The hsKeyedObject class this key points to"), NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyKey_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plKey",                 /* tp_name */
    sizeof(pyKey),                      /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyKey_dealloc,          /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    (reprfunc)pyKey_Repr,               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    (hashfunc)pyKey_Hash,               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    NULL,                               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    (richcmpfunc)pyKey_RichCompare,     /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyKey_Methods,                      /* tp_methods */
    NULL,                               /* tp_members */
    pyKey_GetSet,                       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyKey_new,                          /* tp_new */
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

PyObject* Init_pyKey_Type() {
    if (PyType_Ready(&pyKey_Type) < 0)
        return NULL;

    Py_INCREF(&pyKey_Type);
    return (PyObject*)&pyKey_Type;
}

PY_PLASMA_CHECK_TYPE(Key)

PyObject* pyKey_FromKey(const plKey& key) {
    if (!key.Exists()) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyKey* obj = PyObject_New(pyKey, &pyKey_Type);
    obj->fThis = new plKey(key);
    return (PyObject*)obj;
}

}
