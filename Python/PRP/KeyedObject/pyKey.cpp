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

PY_PLASMA_VALUE_DEALLOC(Key)
PY_PLASMA_NEW_MSG(Key, "Cannot construct Keys directly")

PY_PLASMA_REPR_DECL(Key) {
    ST::string repr = ST::format("<plKey \"{}\">", self->fThis->toString());
    return pyPlasma_convert(repr);
}

PY_PLASMA_HASH_DECL(Key) {
    return (Py_hash_t)(plKeyData*)(*self->fThis);
}

PY_PLASMA_RICHCOMPARE_DECL(Key) {
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

PY_METHOD_VA(Key, read,
    "Params: stream\n"
    "Reads this key from the stream, including the size and offset")
{
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

PY_METHOD_VA(Key, write,
    "Params: stream\n"
    "Writes this key to the stream, including the size and offset")
{
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

PY_METHOD_VA(Key, readUoid,
    "Params: stream\n"
    "Reads this key from the stream")
{
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

PY_METHOD_VA(Key, writeUoid,
    "Params: stream\n"
    "Writes this key from the stream")
{
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

PY_METHOD_NOARGS(Key, exists, "Returns True if the key exists") {
    return pyPlasma_convert(self->fThis->Exists());
}

PY_METHOD_NOARGS(Key, isLoaded, "Returns True if the key is loaded") {
    return pyPlasma_convert(self->fThis->isLoaded());
}

PY_METHOD_VA(Key, orderAfter,
    "Params: otherKey\n"
    "Returns True if the key should be ordered after otherKey")
{
    pyKey* otherKey;
    if (!PyArg_ParseTuple(args, "O", &otherKey)) {
        PyErr_SetString(PyExc_TypeError, "orderAfter expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)otherKey)) {
        PyErr_SetString(PyExc_TypeError, "orderAfter expects a plKey");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->orderAfter(*otherKey->fThis));
}

static PyMethodDef pyKey_Methods[] = {
    pyKey_read_method,
    pyKey_write_method,
    pyKey_readUoid_method,
    pyKey_writeUoid_method,
    pyKey_exists_method,
    pyKey_isLoaded_method,
    pyKey_orderAfter_method,
    PY_METHOD_TERMINATOR
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
    PY_PROPERTY_CHECK_NULL(name)
    if (!pyPlasma_check<ST::string>(value)) {
        PyErr_SetString(PyExc_TypeError, "name expected type plString");
        return -1;
    }
    (*self->fThis)->setName(pyPlasma_get<ST::string>(value));
    return 0;
}

PY_PROPERTY_GETSET_DECL(Key, name)

PY_GETSET_GETTER_DECL(Key, location) {
    return pyLocation_FromLocation((*self->fThis)->getLocation());
}

PY_GETSET_SETTER_DECL(Key, location) {
    PY_PROPERTY_CHECK_NULL(location)
    if (value == Py_None) {
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
    PY_PROPERTY_CHECK_NULL(mask)
    if (!pyPlasma_check<unsigned short>(value)) {
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
    PY_PROPERTY_CHECK_NULL(id)
    if (!pyPlasma_check<uint32_t>(value)) {
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

PY_PLASMA_TYPE(Key, plKey, "plKey wrapper")

PY_PLASMA_TYPE_INIT(Key) {
    pyKey_Type.tp_dealloc = pyKey_dealloc;
    pyKey_Type.tp_new = pyKey_new;
    pyKey_Type.tp_repr = pyKey_repr;
    pyKey_Type.tp_hash = pyKey_hash;
    pyKey_Type.tp_richcompare = pyKey_richcompare;
    pyKey_Type.tp_methods = pyKey_Methods;
    pyKey_Type.tp_getset = pyKey_GetSet;
    if (PyType_CheckAndReady(&pyKey_Type) < 0)
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
