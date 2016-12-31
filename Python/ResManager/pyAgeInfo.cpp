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

#include <ResManager/plAgeInfo.h>
#include "Stream/pyStream.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_DEALLOC(AgeInfo)
PY_PLASMA_EMPTY_INIT(AgeInfo)
PY_PLASMA_NEW(AgeInfo, plAgeInfo)

static PyObject* pyAgeInfo_readFromFile(pyAgeInfo* self, PyObject* args) {
    const char* filename;
    if (!PyArg_ParseTuple(args, "s", &filename)) {
        PyErr_SetString(PyExc_TypeError, "readFromFile expects a string");
        return NULL;
    }
    self->fThis->readFromFile(filename);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_writeToFile(pyAgeInfo* self, PyObject* args) {
    const char* filename;
    int version;
    if (!PyArg_ParseTuple(args, "si", &filename, &version)) {
        PyErr_SetString(PyExc_TypeError, "writeToFile expects string, int");
        return NULL;
    }
    self->fThis->writeToFile(filename, (PlasmaVer)version);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_getNumPages(pyAgeInfo* self) {
    return PyInt_FromLong(self->fThis->getNumPages());
}

static PyObject* pyAgeInfo_getPage(pyAgeInfo* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getPage expects an int");
        return NULL;
    }
    try {
        plAgeInfo::PageEntry pe = self->fThis->getPage(idx);
        return Py_BuildValue("sii", pe.fName.cstr(), pe.fSeqSuffix, pe.fLoadFlags);
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

static PyObject* pyAgeInfo_getNumCommonPages(pyAgeInfo* self, PyObject* args) {
    int version;
    if (!PyArg_ParseTuple(args, "i", &version)) {
        PyErr_SetString(PyExc_TypeError, "getNumCommonPages expects an int");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->getNumCommonPages((PlasmaVer)version));
}

static PyObject* pyAgeInfo_getCommonPage(pyAgeInfo* self, PyObject* args) {
    int idx, version;
    if (!PyArg_ParseTuple(args, "ii", &idx, &version)) {
        PyErr_SetString(PyExc_TypeError, "getCommonPage expects int, int");
        return NULL;
    }
    try {
        plAgeInfo::PageEntry pe = self->fThis->getCommonPage(idx, (PlasmaVer)version);
        return Py_BuildValue("sii", pe.fName.cstr(), pe.fSeqSuffix, pe.fLoadFlags);
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "common page index out of range");
        return NULL;
    }
}

static PyObject* pyAgeInfo_setPage(pyAgeInfo* self, PyObject* args) {
    int idx;
    const char* name;
    int seqSuffix, flags;

    if (!PyArg_ParseTuple(args, "i(sii)", &idx, &name, &seqSuffix, &flags)) {
        PyErr_SetString(PyExc_TypeError, "setPage expects int, (string, int, int)");
        return NULL;
    }
    self->fThis->setPage(idx, plAgeInfo::PageEntry(name, seqSuffix, flags));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_addPage(pyAgeInfo* self, PyObject* args) {
    const char* name;
    int seqSuffix, flags;

    if (!PyArg_ParseTuple(args, "(sii)", &name, &seqSuffix, &flags)) {
        PyErr_SetString(PyExc_TypeError, "addPage expects a tuple(string, int, int)");
        return NULL;
    }
    self->fThis->addPage(plAgeInfo::PageEntry(name, seqSuffix, flags));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_getPageFilename(pyAgeInfo* self, PyObject* args) {
    int idx, version;
    if (!PyArg_ParseTuple(args, "ii", &idx, &version)) {
        PyErr_SetString(PyExc_TypeError, "getPageFilename expects int, int");
        return NULL;
    }
    try {
        return PlStr_To_PyStr(self->fThis->getPageFilename((size_t)idx, (PlasmaVer)version));
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

static PyObject* pyAgeInfo_getCommonPageFilename(pyAgeInfo* self, PyObject* args) {
    int idx, version;
    if (!PyArg_ParseTuple(args, "ii", &idx, &version)) {
        PyErr_SetString(PyExc_TypeError, "getCommonPageFilename expects int, int");
        return NULL;
    }
    try {
        return PlStr_To_PyStr(self->fThis->getCommonPageFilename((size_t)idx, (PlasmaVer)version));
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "common page index out of range");
        return NULL;
    }
}

static PyObject* pyAgeInfo_getPageLoc(pyAgeInfo* self, PyObject* args) {
    int idx, ver;
    if (!PyArg_ParseTuple(args, "ii", &idx, &ver)) {
        PyErr_SetString(PyExc_TypeError, "getPageLoc expects int, int");
        return NULL;
    }
    try {
        return pyLocation_FromLocation(self->fThis->getPageLoc((size_t)idx, (PlasmaVer)ver));
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

static PyObject* pyAgeInfo_getCommonPageLoc(pyAgeInfo* self, PyObject* args) {
    int idx, ver;
    if (!PyArg_ParseTuple(args, "ii", &idx, &ver)) {
        PyErr_SetString(PyExc_TypeError, "getCommonPageLoc expects int, int");
        return NULL;
    }
    try {
        return pyLocation_FromLocation(self->fThis->getCommonPageLoc((size_t)idx, (PlasmaVer)ver));
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

static PyMethodDef pyAgeInfo_Methods[] = {
    { "readFromFile", (PyCFunction)pyAgeInfo_readFromFile, METH_VARARGS,
      "Params: filename\n"
      "Reads the AgeInfo from a .age file" },
    { "writeToFile", (PyCFunction)pyAgeInfo_writeToFile, METH_VARARGS,
      "Params: filename, version\n"
      "Write the AgeInfo to a .age file" },
    { "getNumPages", (PyCFunction)pyAgeInfo_getNumPages, METH_NOARGS,
      "Returns the number of pages described by this AgeInfo" },
    { "getPage", (PyCFunction)pyAgeInfo_getPage, METH_VARARGS,
      "Params: idx\n"
      "Returns a tuple (name, pageNum, loadFlags) for the specified page" },
    { "getNumCommonPages", (PyCFunction)pyAgeInfo_getNumCommonPages, METH_VARARGS,
      "Params: version\n"
      "Returns the number of common pages described by this AgeInfo" },
    { "getCommonPage", (PyCFunction)pyAgeInfo_getCommonPage, METH_VARARGS,
      "Params: idx, version\n"
      "Returns a tuple (name, pageNum, loadFlags) for the specified common page" },
    { "setPage", (PyCFunction)pyAgeInfo_setPage, METH_VARARGS,
      "Params: idx, (name, pageNum, loadFlags)\n"
      "Sets info for the specified page" },
    { "addPage", (PyCFunction)pyAgeInfo_addPage, METH_VARARGS,
      "Params: (name, pageNum, loadFlags)\n"
      "Adds a page to the AgeInfo" },
    { "getPageFilename", (PyCFunction)pyAgeInfo_getPageFilename, METH_VARARGS,
      "Params: idx, version\n"
      "Returns the standard Page Filename for the specified page" },
    { "getCommonPageFilename", (PyCFunction)pyAgeInfo_getCommonPageFilename, METH_VARARGS,
      "Params: idx, version\n"
      "Returns the standard Page Filename for the specified common page" },
    { "getPageLoc", (PyCFunction)pyAgeInfo_getPageLoc, METH_VARARGS,
      "Params: idx\n"
      "Returns a plLocation for the specified page" },
    { "getCommonPageLoc", (PyCFunction)pyAgeInfo_getCommonPageLoc, METH_VARARGS,
      "Params: idx\n"
      "Returns a plLocation for the specified common page" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(plString, AgeInfo, name, getAgeName, setAgeName)
PY_PROPERTY(unsigned int, AgeInfo, startDateTime, getStartDateTime, setStartDateTime)
PY_PROPERTY(float, AgeInfo, dayLength, getDayLength, setDayLength)
PY_PROPERTY(short, AgeInfo, maxCapacity, getMaxCapacity, setMaxCapacity)
PY_PROPERTY(short, AgeInfo, lingerTime, getLingerTime, setLingerTime)
PY_PROPERTY(int, AgeInfo, seqPrefix, getSeqPrefix, setSeqPrefix)
PY_PROPERTY(unsigned int, AgeInfo, releaseVersion, getReleaseVersion, setReleaseVersion)

static PyGetSetDef pyAgeInfo_GetSet[] = {
    pyAgeInfo_name_getset,
    pyAgeInfo_startDateTime_getset,
    pyAgeInfo_dayLength_getset,
    pyAgeInfo_maxCapacity_getset,
    pyAgeInfo_lingerTime_getset,
    pyAgeInfo_seqPrefix_getset,
    pyAgeInfo_releaseVersion_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyAgeInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAgeInfo",             /* tp_name */
    sizeof(pyAgeInfo),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyAgeInfo_dealloc,                  /* tp_dealloc */
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

    pyAgeInfo_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    pyAgeInfo_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyAgeInfo___init__,                 /* tp_init */
    NULL,                               /* tp_alloc */
    pyAgeInfo_new,                      /* tp_new */
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

PyObject* Init_pyAgeInfo_Type() {
    if (PyType_Ready(&pyAgeInfo_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagPreventAutoLoad",
                         PyInt_FromLong(plAgeInfo::kPreventAutoLoad));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagLoadIfSDLPresent",
                         PyInt_FromLong(plAgeInfo::kLoadIfSDLPresent));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagIsLocalOnly",
                         PyInt_FromLong(plAgeInfo::kIsLocalOnly));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagIsVolatile",
                         PyInt_FromLong(plAgeInfo::kIsVolatile));

    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kPageTextures",
                         PyInt_FromLong(plAgeInfo::kTextures));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kPageGlobal",
                         PyInt_FromLong(plAgeInfo::kGlobal));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kNumCommonPages",
                         PyInt_FromLong(plAgeInfo::kNumCommonPages));

    PyObject* list = PyList_New(plAgeInfo::kNumCommonPages);
    for (size_t i=0; i<plAgeInfo::kNumCommonPages; i++)
        PyList_SET_ITEM(list, i, PlStr_To_PyStr(plAgeInfo::kCommonPages[i]));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kCommonPages", list);

    Py_INCREF(&pyAgeInfo_Type);
    return (PyObject*)&pyAgeInfo_Type;
}

PY_PLASMA_IFC_METHODS(AgeInfo, plAgeInfo)

}
