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

extern "C" {

PY_PLASMA_VALUE_DEALLOC(Location)

PY_PLASMA_INIT_DECL(Location) {
    int version = PlasmaVer::pvUnknown;
    if (!PyArg_ParseTuple(args, "|i", &version))
        return -1;

    self->fThis->setVer((PlasmaVer)version);
    return 0;
}

PY_PLASMA_VALUE_NEW(Location, plLocation)

static PyObject* pyLocation_Repr(pyLocation* self) {
    plString repr = plString::Format("<plLocation \"%d|%d\">",
                                     self->fThis->getSeqPrefix(),
                                     self->fThis->getPageNum());
    return pyPlasma_convert(repr);
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

    return pyPlasma_convert(result);
}

PY_METHOD_VA(Location, read,
    "Params: stream\n"
    "Reads this Location from the stream")
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
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Location, invalidate, "Invalidates the location") {
    self->fThis->invalidate();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Location, isValid, "Returns True if the location is valid") {
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

PY_METHOD_NOARGS(Location, isVirtual, "Returns True if the location is virtual") {
    return pyPlasma_convert(self->fThis->isVirtual());
}

PY_METHOD_NOARGS(Location, isGlobal,
    "Returns True if the sequence prefix points to a global age")
{
    return pyPlasma_convert(self->fThis->isGlobal());
}

PY_METHOD_NOARGS(Location, setVirtual, "Makes the location virtual") {
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
        return NULL;
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

PyTypeObject pyLocation_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plLocation",            /* tp_name */
    sizeof(pyLocation),                 /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyLocation_dealloc,                 /* tp_dealloc */
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

    pyLocation___init__,                /* tp_init */
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

    PY_TYPE_ADD_CONST(Location, "kLocalOnly", plLocation::kLocalOnly);
    PY_TYPE_ADD_CONST(Location, "kVolatile", plLocation::kVolatile);
    PY_TYPE_ADD_CONST(Location, "kReserved", plLocation::kReserved);
    PY_TYPE_ADD_CONST(Location, "kBuiltIn", plLocation::kBuiltIn);
    PY_TYPE_ADD_CONST(Location, "kItinerant", plLocation::kItinerant);

    Py_INCREF(&pyLocation_Type);
    return (PyObject*)&pyLocation_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Location, plLocation)

}
