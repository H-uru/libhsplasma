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

#include <PRP/KeyedObject/hsKeyedObject.h>
#include "PRP/pyCreatable.h"
#include "pyKeyedObject.h"
#include "Stream/pyStream.h"

extern "C" {

PY_PLASMA_VALUE_DEALLOC(Key)
PY_PLASMA_NEW_MSG(Key, "Cannot construct Keys directly")

static PyObject* pyKey_Repr(pyKey* self) {
    plString repr = plString::Format("<plKey \"%s\">", self->fThis->toString().cstr());
    return pyPlasma_convert(repr);
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

    return pyPlasma_convert(result);
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
    Py_RETURN_NONE;
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
    Py_RETURN_NONE;
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
    Py_RETURN_NONE;
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
    Py_RETURN_NONE;
}

static PyObject* pyKey_exists(pyKey* self) {
    return pyPlasma_convert(self->fThis->Exists());
}

static PyObject* pyKey_isLoaded(pyKey* self) {
    return pyPlasma_convert(self->fThis->isLoaded());
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

/* NOTE: Not using standard PY_PROPERTY() wrappers, since the plKey needs to
 * be dereferenced in all the getters/setters below */

PY_GETSET_GETTER_DECL(Key, type) {
    return pyPlasma_convert((*self->fThis)->getType());
}

PY_PROPERTY_GETSET_RO_DECL(Key, type)

PY_GETSET_GETTER_DECL(Key, name) {
    return pyPlasma_convert((*self->fThis)->getName());
}

PY_GETSET_SETTER_DECL(Key, name) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "name cannot be deleted");
        return -1;
    } else if (!pyPlasma_check<plString>(value)) {
        PyErr_SetString(PyExc_TypeError, "name expected type plString");
        return -1;
    }
    (*self->fThis)->setName(pyPlasma_get<plString>(value));
    return 0;
}

PY_PROPERTY_GETSET_DECL(Key, name)

PY_GETSET_GETTER_DECL(Key, location) {
    return pyLocation_FromLocation((*self->fThis)->getLocation());
}

PY_GETSET_SETTER_DECL(Key, location) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "location cannot be deleted");
        return -1;
    } else if (value == Py_None) {
        (*self->fThis)->setLocation(plLocation());
        return 0;
    } else if (!pyLocation_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "location expected type plLocation");
        return -1;
    }
    (*self->fThis)->setLocation(*((pyLocation*)value)->fThis);
    return 0;
}

PY_PROPERTY_GETSET_DECL(Key, location)

PY_GETSET_GETTER_DECL(Key, mask) {
    return pyPlasma_convert((*self->fThis)->getLoadMask().getMask());
}

PY_GETSET_SETTER_DECL(Key, mask) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "mask cannot be deleted");
        return -1;
    } else if (!pyPlasma_check<unsigned short>(value)) {
        PyErr_SetString(PyExc_TypeError, "mask expected type unsigned short");
        return -1;
    }
    plLoadMask mask;
    mask.setMask(pyPlasma_get<unsigned short>(value));
    (*self->fThis)->setLoadMask(mask);
    return 0;
}

PY_PROPERTY_GETSET_DECL(Key, mask)

PY_GETSET_GETTER_DECL(Key, id) {
    return pyPlasma_convert((*self->fThis)->getID());
}

PY_GETSET_SETTER_DECL(Key, id) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "id cannot be deleted");
        return -1;
    } else if (!pyPlasma_check<uint32_t>(value)) {
        PyErr_SetString(PyExc_TypeError, "id expected type uint32_t");
        return -1;
    }
    (*self->fThis)->setID(pyPlasma_get<uint32_t>(value));
    return 0;
}

PY_PROPERTY_GETSET_DECL(Key, id)

PY_GETSET_GETTER_DECL(Key, object) {
    return ICreate((*self->fThis)->getObj());
}

PY_PROPERTY_GETSET_RO_DECL(Key, object)

static PyGetSetDef pyKey_GetSet[] = {
    pyKey_type_getset,
    pyKey_name_getset,
    pyKey_location_getset,
    pyKey_mask_getset,
    pyKey_id_getset,
    pyKey_object_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyKey_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plKey",                 /* tp_name */
    sizeof(pyKey),                      /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyKey_dealloc,                      /* tp_dealloc */
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
    if (!key.Exists())
        Py_RETURN_NONE;
    pyKey* obj = PyObject_New(pyKey, &pyKey_Type);
    obj->fThis = new plKey(key);
    return (PyObject*)obj;
}

}
