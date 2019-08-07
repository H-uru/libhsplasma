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

#include <PRP/KeyedObject/plLocation.h>
#include "Stream/pyStream.h"
#include <string_theory/format>

PY_PLASMA_VALUE_DEALLOC(Location)

PY_PLASMA_INIT_DECL(Location)
{
    int version = PlasmaVer::pvUnknown;
    if (!PyArg_ParseTuple(args, "|i", &version))
        return -1;

    self->fThis->setVer((PlasmaVer)version);
    return 0;
}

PY_PLASMA_VALUE_NEW(Location, plLocation)

PY_PLASMA_REPR_DECL(Location)
{
    ST::string repr = ST::format("<plLocation \"{}|{}\">",
                                 self->fThis->getSeqPrefix(),
                                 self->fThis->getPageNum());
    return pyPlasma_convert(repr);
}

PY_PLASMA_HASH_DECL(Location)
{
    return (long)self->fThis->unparse();
}

PY_PLASMA_RICHCOMPARE_DECL(Location)
{
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
        return nullptr;
    }

    return pyPlasma_convert(result);
}

PY_METHOD_VA(Location, read,
    "Params: stream\n"
    "Reads this Location from the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return nullptr;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Location, write,
    "Params: stream\n"
    "Writes this Location to the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return nullptr;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Location, invalidate, "Invalidates the location")
{
    self->fThis->invalidate();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Location, isValid, "Returns True if the location is valid")
{
    return pyPlasma_convert(self->fThis->isValid());
}

PY_METHOD_NOARGS(Location, isReserved,
    "Returns True if the location is a Reserved page")
{
    return pyPlasma_convert(self->fThis->isReserved());
}

PY_METHOD_NOARGS(Location, isItinerant,
    "Returns True if the location is an Itinerant page")
{
    return pyPlasma_convert(self->fThis->isItinerant());
}

PY_METHOD_NOARGS(Location, isVirtual, "Returns True if the location is virtual")
{
    return pyPlasma_convert(self->fThis->isVirtual());
}

PY_METHOD_NOARGS(Location, isGlobal,
    "Returns True if the sequence prefix points to a global age")
{
    return pyPlasma_convert(self->fThis->isGlobal());
}

PY_METHOD_NOARGS(Location, setVirtual, "Makes the location virtual")
{
    self->fThis->setVirtual();
    Py_RETURN_NONE;
}

PY_METHOD_VA(Location, parse,
    "Params: locationId\n"
    "Parses a raw location")
{
    int loc;
    if (!PyArg_ParseTuple(args, "i", &loc)) {
        PyErr_SetString(PyExc_TypeError, "parse expects an int");
        return nullptr;
    }
    self->fThis->parse(loc);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Location, unparse,
    "Returns a raw location ID for the set Plasma version")
{
    return pyPlasma_convert(self->fThis->unparse());
}

static PyMethodDef pyLocation_Methods[] = {
    pyLocation_read_method,
    pyLocation_write_method,
    pyLocation_invalidate_method,
    pyLocation_isValid_method,
    pyLocation_isReserved_method,
    pyLocation_isItinerant_method,
    pyLocation_isVirtual_method,
    pyLocation_isGlobal_method,
    pyLocation_setVirtual_method,
    pyLocation_parse_method,
    pyLocation_unparse_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(int, Location, version, getVer, setVer)
PY_PROPERTY(int, Location, prefix, getSeqPrefix, setSeqPrefix)
PY_PROPERTY(int, Location, page, getPageNum, setPageNum)
PY_PROPERTY(unsigned short, Location, flags, getFlags, setFlags)

static PyGetSetDef pyLocation_GetSet[] = {
    pyLocation_version_getset,
    pyLocation_prefix_getset,
    pyLocation_page_getset,
    pyLocation_flags_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Location, plLocation, "plLocation wrapper")

PY_PLASMA_TYPE_INIT(Location)
{
    pyLocation_Type.tp_dealloc = pyLocation_dealloc;
    pyLocation_Type.tp_init = pyLocation___init__;
    pyLocation_Type.tp_new = pyLocation_new;
    pyLocation_Type.tp_repr = pyLocation_repr;
    pyLocation_Type.tp_hash = pyLocation_hash;
    pyLocation_Type.tp_richcompare = pyLocation_richcompare;
    pyLocation_Type.tp_methods = pyLocation_Methods;
    pyLocation_Type.tp_getset = pyLocation_GetSet;
    if (PyType_CheckAndReady(&pyLocation_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(Location, "kLocalOnly", plLocation::kLocalOnly);
    PY_TYPE_ADD_CONST(Location, "kVolatile", plLocation::kVolatile);
    PY_TYPE_ADD_CONST(Location, "kReserved", plLocation::kReserved);
    PY_TYPE_ADD_CONST(Location, "kBuiltIn", plLocation::kBuiltIn);
    PY_TYPE_ADD_CONST(Location, "kItinerant", plLocation::kItinerant);

    Py_INCREF(&pyLocation_Type);
    return (PyObject*)&pyLocation_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Location, plLocation)
