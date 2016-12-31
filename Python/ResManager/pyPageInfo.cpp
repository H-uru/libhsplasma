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

static PyObject* pyPageInfo_isValid(pyPageInfo* self) {
    return PyBool_FromLong(self->fThis->isValid() ? 1 : 0);
}

static PyObject* pyPageInfo_read(pyPageInfo* self, PyObject* args) {
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

static PyObject* pyPageInfo_write(pyPageInfo* self, PyObject* args) {
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

static PyObject* pyPageInfo_writeSums(pyPageInfo* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyPageInfo_getFilename(pyPageInfo* self, PyObject* args) {
    int version;
    if (!PyArg_ParseTuple(args, "i", &version)) {
        PyErr_SetString(PyExc_TypeError, "getFilename expects an int");
        return NULL;
    }
    return PlStr_To_PyStr(self->fThis->getFilename((PlasmaVer)version));
}

static PyMethodDef pyPageInfo_Methods[] = {
    { "isValid", (PyCFunction)pyPageInfo_isValid, METH_NOARGS,
      "Returns True if the PageInfo is valid" },
    { "read", (PyCFunction)pyPageInfo_read, METH_VARARGS,
      "Params: stream\n"
      "Read the page info from the stream" },
    { "write", (PyCFunction)pyPageInfo_write, METH_VARARGS,
      "Params: stream\n"
      "Write the page info to the stream" },
    { "writeSums", (PyCFunction)pyPageInfo_writeSums, METH_VARARGS,
      "Params: stream\n"
      "Write the page checksums to the stream" },
    { "getFilename", (PyCFunction)pyPageInfo_getFilename, METH_VARARGS,
      "Params: version\n"
      "Generate the standard filename for a PRP file" },
    { NULL, NULL, 0, NULL }
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

    PyDict_SetItemString(pyPageInfo_Type.tp_dict, "kPartialPatchFile",
                         PyInt_FromLong(plPageInfo::kPartialPatchFile));
    PyDict_SetItemString(pyPageInfo_Type.tp_dict, "kOldDataChecksum",
                         PyInt_FromLong(plPageInfo::kOldDataChecksum));
    PyDict_SetItemString(pyPageInfo_Type.tp_dict, "kOldIdxChecksum",
                         PyInt_FromLong(plPageInfo::kOldIdxChecksum));
    PyDict_SetItemString(pyPageInfo_Type.tp_dict, "kBasicChecksum",
                         PyInt_FromLong(plPageInfo::kBasicChecksum));
    PyDict_SetItemString(pyPageInfo_Type.tp_dict, "kPatchHeaderOnly",
                         PyInt_FromLong(plPageInfo::kPatchHeaderOnly));
    PyDict_SetItemString(pyPageInfo_Type.tp_dict, "kChecksumMask",
                         PyInt_FromLong(plPageInfo::kChecksumMask));
    PyDict_SetItemString(pyPageInfo_Type.tp_dict, "kPatchFlags",
                         PyInt_FromLong(plPageInfo::kPatchFlags));

    Py_INCREF(&pyPageInfo_Type);
    return (PyObject*)&pyPageInfo_Type;
}

PY_PLASMA_IFC_METHODS(PageInfo, plPageInfo)

}
