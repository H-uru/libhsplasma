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

#include "pyResManager.h"

#include <PRP/plPageInfo.h>
#include "Stream/pyStream.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_DEALLOC(PageInfo)
PY_PLASMA_EMPTY_INIT(PageInfo)
PY_PLASMA_NEW(PageInfo, plPageInfo)

PY_METHOD_NOARGS(PageInfo, isValid, "Returns True if the PageInfo is valid") {
    return pyPlasma_convert(self->fThis->isValid());
}

PY_METHOD_VA(PageInfo, read,
    "Params: stream\n"
    "Read the page info from the stream")
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

PY_METHOD_VA(PageInfo, write,
    "Params: stream\n"
    "Write the page info to the stream")
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

PY_METHOD_VA(PageInfo, writeSums,
    "Params: stream\n"
    "Write the page checksums to the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeSums expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeSums expects an hsStream");
        return NULL;
    }
    self->fThis->writeSums(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(PageInfo, getFilename,
    "Params: version\n"
    "Generate the standard filename for a PRP file")
{
    int version;
    if (!PyArg_ParseTuple(args, "i", &version)) {
        PyErr_SetString(PyExc_TypeError, "getFilename expects an int");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->getFilename((PlasmaVer)version));
}

static PyMethodDef pyPageInfo_Methods[] = {
    pyPageInfo_isValid_method,
    pyPageInfo_read_method,
    pyPageInfo_write_method,
    pyPageInfo_writeSums_method,
    pyPageInfo_getFilename_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(plString, PageInfo, age, getAge, setAge)
PY_PROPERTY_RO(PageInfo, chapter, getChapter)
PY_PROPERTY(plString, PageInfo, page, getPage, setPage)
PY_PROPERTY(unsigned int, PageInfo, releaseVersion, getReleaseVersion, setReleaseVersion)
PY_PROPERTY(unsigned int, PageInfo, flags, getFlags, setFlags)
PY_PROPERTY(plLocation, PageInfo, location, getLocation, setLocation)

static PyGetSetDef pyPageInfo_GetSet[] = {
    pyPageInfo_age_getset,
    pyPageInfo_chapter_getset,
    pyPageInfo_page_getset,
    pyPageInfo_releaseVersion_getset,
    pyPageInfo_flags_getset,
    pyPageInfo_location_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyPageInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plPageInfo",            /* tp_name */
    sizeof(pyPageInfo),                 /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyPageInfo_dealloc,                 /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    NULL,                               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyPageInfo_Methods,                 /* tp_methods */
    NULL,                               /* tp_members */
    pyPageInfo_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyPageInfo___init__,                /* tp_init */
    NULL,                               /* tp_alloc */
    pyPageInfo_new,                     /* tp_new */
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

PyObject* Init_pyPageInfo_Type() {
    if (PyType_Ready(&pyPageInfo_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(PageInfo, "kPartialPatchFile", plPageInfo::kPartialPatchFile);
    PY_TYPE_ADD_CONST(PageInfo, "kOldDataChecksum", plPageInfo::kOldDataChecksum);
    PY_TYPE_ADD_CONST(PageInfo, "kOldIdxChecksum", plPageInfo::kOldIdxChecksum);
    PY_TYPE_ADD_CONST(PageInfo, "kBasicChecksum", plPageInfo::kBasicChecksum);
    PY_TYPE_ADD_CONST(PageInfo, "kPatchHeaderOnly", plPageInfo::kPatchHeaderOnly);
    PY_TYPE_ADD_CONST(PageInfo, "kChecksumMask", plPageInfo::kChecksumMask);
    PY_TYPE_ADD_CONST(PageInfo, "kPatchFlags", plPageInfo::kPatchFlags);

    Py_INCREF(&pyPageInfo_Type);
    return (PyObject*)&pyPageInfo_Type;
}

PY_PLASMA_IFC_METHODS(PageInfo, plPageInfo)

}
