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

PY_PLASMA_DEALLOC(AgeInfo)
PY_PLASMA_EMPTY_INIT(AgeInfo)
PY_PLASMA_NEW(AgeInfo, plAgeInfo)

PY_METHOD_VA(AgeInfo, readFromFile,
    "Params: filename\n"
    "Reads the AgeInfo from a .age file")
{
    const char* filename;
    if (!PyArg_ParseTuple(args, "s", &filename)) {
        PyErr_SetString(PyExc_TypeError, "readFromFile expects a string");
        return NULL;
    }
    self->fThis->readFromFile(filename);
    Py_RETURN_NONE;
}

PY_METHOD_VA(AgeInfo, writeToFile,
    "Params: filename, version\n"
    "Write the AgeInfo to a .age file")
{
    const char* filename;
    int version;
    if (!PyArg_ParseTuple(args, "si", &filename, &version)) {
        PyErr_SetString(PyExc_TypeError, "writeToFile expects string, int");
        return NULL;
    }
    self->fThis->writeToFile(filename, (PlasmaVer)version);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(AgeInfo, getNumPages,
    "Returns the number of pages described by this AgeInfo")
{
    return pyPlasma_convert(self->fThis->getNumPages());
}

PY_METHOD_VA(AgeInfo, getPage,
    "Params: idx\n"
    "Returns a tuple (name, pageNum, loadFlags) for the specified page")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getPage expects an int");
        return NULL;
    }
    try {
        plAgeInfo::PageEntry pe = self->fThis->getPage(idx);
        return Py_BuildValue("sii", pe.fName.c_str(), pe.fSeqSuffix, pe.fLoadFlags);
    } catch (const hsOutOfBoundsException&) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

PY_METHOD_VA(AgeInfo, getNumCommonPages,
    "Params: version\n"
    "Returns the number of common pages described by this AgeInfo")
{
    int version;
    if (!PyArg_ParseTuple(args, "i", &version)) {
        PyErr_SetString(PyExc_TypeError, "getNumCommonPages expects an int");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->getNumCommonPages((PlasmaVer)version));
}

PY_METHOD_VA(AgeInfo, getCommonPage,
    "Params: idx, version\n"
    "Returns a tuple (name, pageNum, loadFlags) for the specified common page")
{
    int idx, version;
    if (!PyArg_ParseTuple(args, "ii", &idx, &version)) {
        PyErr_SetString(PyExc_TypeError, "getCommonPage expects int, int");
        return NULL;
    }
    try {
        plAgeInfo::PageEntry pe = self->fThis->getCommonPage(idx, (PlasmaVer)version);
        return Py_BuildValue("sii", pe.fName.c_str(), pe.fSeqSuffix, pe.fLoadFlags);
    } catch (const hsOutOfBoundsException&) {
        PyErr_SetString(PyExc_IndexError, "common page index out of range");
        return NULL;
    }
}

PY_METHOD_VA(AgeInfo, setPage,
    "Params: idx, (name, pageNum, loadFlags)\n"
    "Sets info for the specified page")
{
    int idx;
    const char* name;
    int seqSuffix, flags;

    if (!PyArg_ParseTuple(args, "i(sii)", &idx, &name, &seqSuffix, &flags)) {
        PyErr_SetString(PyExc_TypeError, "setPage expects int, (string, int, int)");
        return NULL;
    }
    self->fThis->setPage(idx, plAgeInfo::PageEntry(name, seqSuffix, flags));
    Py_RETURN_NONE;
}

PY_METHOD_VA(AgeInfo, addPage,
    "Params: (name, pageNum, loadFlags)\n"
    "Adds a page to the AgeInfo")
{
    const char* name;
    int seqSuffix, flags;

    if (!PyArg_ParseTuple(args, "(sii)", &name, &seqSuffix, &flags)) {
        PyErr_SetString(PyExc_TypeError, "addPage expects a tuple(string, int, int)");
        return NULL;
    }
    self->fThis->addPage(plAgeInfo::PageEntry(name, seqSuffix, flags));
    Py_RETURN_NONE;
}

PY_METHOD_VA(AgeInfo, getPageFilename,
    "Params: idx, version\n"
    "Returns the standard Page Filename for the specified page")
{
    int idx, version;
    if (!PyArg_ParseTuple(args, "ii", &idx, &version)) {
        PyErr_SetString(PyExc_TypeError, "getPageFilename expects int, int");
        return NULL;
    }
    try {
        return pyPlasma_convert(self->fThis->getPageFilename((size_t)idx, (PlasmaVer)version));
    } catch (const hsOutOfBoundsException&) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

PY_METHOD_VA(AgeInfo, getCommonPageFilename,
    "Params: idx, version\n"
    "Returns the standard Page Filename for the specified common page")
{
    int idx, version;
    if (!PyArg_ParseTuple(args, "ii", &idx, &version)) {
        PyErr_SetString(PyExc_TypeError, "getCommonPageFilename expects int, int");
        return NULL;
    }
    try {
        return pyPlasma_convert(self->fThis->getCommonPageFilename((size_t)idx, (PlasmaVer)version));
    } catch (const hsOutOfBoundsException&) {
        PyErr_SetString(PyExc_IndexError, "common page index out of range");
        return NULL;
    }
}

PY_METHOD_VA(AgeInfo, getPageLoc,
    "Params: idx\n"
    "Returns a plLocation for the specified page")
{
    int idx, ver;
    if (!PyArg_ParseTuple(args, "ii", &idx, &ver)) {
        PyErr_SetString(PyExc_TypeError, "getPageLoc expects int, int");
        return NULL;
    }
    try {
        return pyLocation_FromLocation(self->fThis->getPageLoc((size_t)idx, (PlasmaVer)ver));
    } catch (const hsOutOfBoundsException&) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

PY_METHOD_VA(AgeInfo, getCommonPageLoc,
    "Params: idx\n"
    "Returns a plLocation for the specified common page")
{
    int idx, ver;
    if (!PyArg_ParseTuple(args, "ii", &idx, &ver)) {
        PyErr_SetString(PyExc_TypeError, "getCommonPageLoc expects int, int");
        return NULL;
    }
    try {
        return pyLocation_FromLocation(self->fThis->getCommonPageLoc((size_t)idx, (PlasmaVer)ver));
    } catch (const hsOutOfBoundsException&) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

static PyMethodDef pyAgeInfo_Methods[] = {
    pyAgeInfo_readFromFile_method,
    pyAgeInfo_writeToFile_method,
    pyAgeInfo_getNumPages_method,
    pyAgeInfo_getPage_method,
    pyAgeInfo_getNumCommonPages_method,
    pyAgeInfo_getCommonPage_method,
    pyAgeInfo_setPage_method,
    pyAgeInfo_addPage_method,
    pyAgeInfo_getPageFilename_method,
    pyAgeInfo_getCommonPageFilename_method,
    pyAgeInfo_getPageLoc_method,
    pyAgeInfo_getCommonPageLoc_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(ST::string, AgeInfo, name, getAgeName, setAgeName)
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

PY_PLASMA_TYPE(AgeInfo, plAgeInfo, "plAgeInfo wrapper")

PY_PLASMA_TYPE_INIT(AgeInfo) {
    pyAgeInfo_Type.tp_dealloc = pyAgeInfo_dealloc;
    pyAgeInfo_Type.tp_init = pyAgeInfo___init__;
    pyAgeInfo_Type.tp_new = pyAgeInfo_new;
    pyAgeInfo_Type.tp_methods = pyAgeInfo_Methods;
    pyAgeInfo_Type.tp_getset = pyAgeInfo_GetSet;
    if (PyType_CheckAndReady(&pyAgeInfo_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(AgeInfo, "kFlagPreventAutoLoad", plAgeInfo::kPreventAutoLoad);
    PY_TYPE_ADD_CONST(AgeInfo, "kFlagLoadIfSDLPresent", plAgeInfo::kLoadIfSDLPresent);
    PY_TYPE_ADD_CONST(AgeInfo, "kFlagIsLocalOnly", plAgeInfo::kIsLocalOnly);
    PY_TYPE_ADD_CONST(AgeInfo, "kFlagIsVolatile", plAgeInfo::kIsVolatile);

    PY_TYPE_ADD_CONST(AgeInfo, "kPageTextures", plAgeInfo::kTextures);
    PY_TYPE_ADD_CONST(AgeInfo, "kPageGlobal", plAgeInfo::kGlobal);
    PY_TYPE_ADD_CONST(AgeInfo, "kNumCommonPages", plAgeInfo::kNumCommonPages);

    PyObject* list = PyTuple_New(plAgeInfo::kNumCommonPages);
    for (size_t i=0; i<plAgeInfo::kNumCommonPages; i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(plAgeInfo::kCommonPages[i]));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kCommonPages", list);

    Py_INCREF(&pyAgeInfo_Type);
    return (PyObject*)&pyAgeInfo_Type;
}

PY_PLASMA_IFC_METHODS(AgeInfo, plAgeInfo)
