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

#include <ResManager/plResManager.h>
#include <PRP/plSceneNode.h>
#include "Stream/pyStream.h"
#include "PRP/pyCreatable.h"
#include "PRP/pySceneNode.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"

PY_PLASMA_DEALLOC(ResManager)

PY_PLASMA_INIT_DECL(ResManager)
{
    int version = PlasmaVer::pvUnknown;
    if (!PyArg_ParseTuple(args, "|i", &version))
        return -1;

    self->fThis->setVer((PlasmaVer)version);
    return 0;
}

PY_PLASMA_NEW(ResManager, plResManager)

PY_METHOD_VA(ResManager, setVer,
    "Params: version, [force]\n"
    "Sets the plasma version of the resource manager")
{
    int ver, force = 0;
    if (!PyArg_ParseTuple(args, "i|i", &ver, &force)) {
        PyErr_SetString(PyExc_TypeError, "setVer expects an int");
        return nullptr;
    }
    self->fThis->setVer((PlasmaVer)ver, (force != 0));
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ResManager, getVer,
    "Gets the plasma version of the resource manager")
{
    return pyPlasma_convert(self->fThis->getVer());
}

PY_METHOD_VA(ResManager, readKey,
    "Params: stream\n"
    "Reads a plKey from the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readKey expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readKey expects an hsStream");
        return nullptr;
    }
    return pyKey_FromKey(self->fThis->readKey(stream->fThis));
}

PY_METHOD_VA(ResManager, readUoid,
    "Params: stream\n"
    "Reads a non-null plKey from the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readUoid expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readUoid expects an hsStream");
        return nullptr;
    }
    return pyKey_FromKey(self->fThis->readUoid(stream->fThis));
}

PY_METHOD_VA(ResManager, writeKey,
    "Params: stream, key\n"
    "Writes a plKey to the stream")
{
    pyStream* stream;
    pyKey* key;
    if (!PyArg_ParseTuple(args, "OO", &stream, &key)) {
        PyErr_SetString(PyExc_TypeError, "writeKey expects hsStream, plKey");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "writeKey expects hsStream, plKey");
        return nullptr;
    }
    self->fThis->writeKey(stream->fThis, *(key->fThis));
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, writeUoid,
    "Params: stream, key\n"
    "Writes a non-null plKey to the stream")
{
    pyStream* stream;
    pyKey* key;
    if (!PyArg_ParseTuple(args, "OO", &stream, &key)) {
        PyErr_SetString(PyExc_TypeError, "writeUoid expects hsStream, plKey");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "writeUoid expects hsStream, plKey");
        return nullptr;
    }
    self->fThis->writeUoid(stream->fThis, *(key->fThis));
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, getObject,
    "Params: key\n"
    "Finds and returns the loaded Keyed Object described by `key`")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "getObject expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "getObject expects a plKey");
        return nullptr;
    }
    return ICreate(self->fThis->getObject(*(key->fThis)));
}

PY_METHOD_VA(ResManager, countKeys,
    "Params: location\n"
    "Counts the number of loaded keys in `location`")
{
    pyLocation* loc;
    if (!PyArg_ParseTuple(args, "O", &loc)) {
        PyErr_SetString(PyExc_TypeError, "countKeys expects a plLocation");
        return nullptr;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "countKeys expects a plLocation");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->countKeys(*(loc->fThis)));
}

PY_METHOD_VA(ResManager, ReadPage,
    "Params: filename, [stub]\n"
    "Reads an entire PRP file and returns the plPageInfo for it")
{
    ST::string filename;
    pyStream* prxStream;
    pyStream* prmStream = nullptr;
    int stub = false;
    if (PyArg_ParseTuple(args, "O&|i", PyAnyString_PathDecoder, &filename, &stub)) {
        try {
            return pyPageInfo_FromPageInfo(self->fThis->ReadPage(filename, (stub != 0)));
        } catch (...) {
            PyErr_SetString(PyExc_IOError, "Error reading page");
            return nullptr;
        }
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "O|Oi", &prxStream, &prmStream, &stub)) {
        if (!pyStream_Check((PyObject*)prxStream) || (prmStream && !pyStream_Check((PyObject*)prmStream))) {
            PyErr_SetString(PyExc_TypeError, "ReadPage expects a string, an hsStream, or an os.PathLike object");
            return nullptr;
        }

        hsStream* prxS = prxStream->fThis;
        hsStream* prmS = prmStream ? prmStream->fThis : nullptr;
        try {
            return pyPageInfo_FromPageInfo(self->fThis->ReadPage(prxS, prmS, (stub != 0)));
        } catch (...) {
            PyErr_SetString(PyExc_IOError, "Error reading page");
            return nullptr;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "ReadPage expects a string, an hsStream, or an os.PathLike object");
        return nullptr;
    }
}

PY_METHOD_VA(ResManager, WritePage,
    "Params: filename, page\n"
    "Writes an entire page to a PRP file")
{
    ST::string filename;
    pyStream* stream;
    pyPageInfo* page;
    if (PyArg_ParseTuple(args, "O&O", PyAnyString_PathDecoder, &filename, &page)) {
        if (!pyPageInfo_Check((PyObject*)page)) {
            PyErr_SetString(PyExc_TypeError, "WritePage expects a string, hsStream, or os.PathLike object, and a plPageInfo");
            return nullptr;
        }

        try {
            self->fThis->WritePage(filename, page->fThis);
            Py_RETURN_NONE;
        } catch (...) {
            PyErr_SetString(PyExc_IOError, "Error writing page");
            return nullptr;
        }
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "OO", &stream, &page)) {
        if (!pyPageInfo_Check((PyObject*)page) || !pyStream_Check((PyObject*)stream)) {
            PyErr_SetString(PyExc_TypeError, "WritePage expects a string, hsStream, or os.PathLike object, and a plPageInfo");
            return nullptr;
        }

        try {
            self->fThis->WritePage(stream->fThis, page->fThis);
            Py_RETURN_NONE;
        } catch (...) {
            PyErr_SetString(PyExc_IOError, "Error writing page");
            return nullptr;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "WritePage expects a string, hsStream, or os.PathLike object, and a plPageInfo");
        return nullptr;
    }
}

PY_METHOD_VA(ResManager, FindPage,
    "Params: location\n"
    "Finds and returns the plPageInfo at `location`")
{
    pyLocation* loc;
    if (!PyArg_ParseTuple(args, "O", &loc)) {
        PyErr_SetString(PyExc_TypeError, "FindPage expects a plLocation");
        return nullptr;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "FindPage expects a plLocation");
        return nullptr;
    }
    plPageInfo* page = self->fThis->FindPage(*loc->fThis);
    if (page == nullptr) {
        Py_RETURN_NONE;
    } else {
        return pyPageInfo_FromPageInfo(page);
    }
}

PY_METHOD_VA(ResManager, UnloadPage,
    "Params: location\n"
    "Unloads the specified page, as well as all associated objects\n"
    "from the ResManager")
{
    pyLocation* loc;
    if (!PyArg_ParseTuple(args, "O", &loc)) {
        PyErr_SetString(PyExc_TypeError, "UnloadPage expects a plLocation");
        return nullptr;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "UnloadPage expects a plLocation");
        return nullptr;
    }
    self->fThis->UnloadPage(*loc->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, ReadAge,
    "Params: filename, readPages\n"
    "Reads a .age file. If readPages is True, also loads all PRPs\n"
    "identified in the .age file")
{
    ST::string filename;
    char readPages;
    if (!PyArg_ParseTuple(args, "O&b", PyAnyString_PathDecoder, &filename, &readPages)) {
        PyErr_SetString(PyExc_TypeError, "ReadAge expects string, bool");
        return nullptr;
    }
    plAgeInfo* age = nullptr;
    try {
        age = self->fThis->ReadAge(filename, readPages != 0);
    } catch (hsException& e) {
        ST::string err = ST::format("Error reading age: {}", e.what());
        PyErr_SetString(PyExc_IOError, err.c_str());
        return nullptr;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading age");
        return nullptr;
    }
    if (age == nullptr) {
        Py_RETURN_NONE;
    } else {
        return pyAgeInfo_FromAgeInfo(age);
    }
}

PY_METHOD_VA(ResManager, WriteAge,
    "Params: filename, age\n"
    "Writes a plAgeInfo to the specified file\n"
    "Does NOT write any PRP files!")
{
    ST::string filename;
    pyAgeInfo* age;
    if (!PyArg_ParseTuple(args, "O&O", PyAnyString_PathDecoder, &filename, &age)) {
        PyErr_SetString(PyExc_TypeError, "WriteAge expects string or an os.PathLike object, plAgeInfo");
        return nullptr;
    }
    if (!pyAgeInfo_Check((PyObject*)age)) {
        PyErr_SetString(PyExc_TypeError, "WriteAge expects string or an os.PathLike object, plAgeInfo");
        return nullptr;
    }
    try {
        self->fThis->WriteAge(filename, age->fThis);
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing age");
        return nullptr;
    }
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, FindAge,
    "Params: age\n"
    "Finds and returns the plAgeInfo for `age`")
{
    const char* ageName;
    if (!PyArg_ParseTuple(args, "s", &ageName)) {
        PyErr_SetString(PyExc_TypeError, "FindAge expects a string");
        return nullptr;
    }
    plAgeInfo* age = self->fThis->FindAge(ageName);
    if (age == nullptr) {
        Py_RETURN_NONE;
    } else {
        return pyAgeInfo_FromAgeInfo(age);
    }
}

PY_METHOD_VA(ResManager, UnloadAge,
    "Params: age\n"
    "Unloads the specified age, as well as any pages and objects\n"
    "associated with it from the ResManager")
{
    const char* ageName;
    if (!PyArg_ParseTuple(args, "s", &ageName)) {
        PyErr_SetString(PyExc_TypeError, "UnloadAge expects a string");
        return nullptr;
    }
    self->fThis->UnloadAge(ageName);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, ReadCreatable,
    "Params: stream\n"
    "Reads a Creatable from the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "ReadCreatable expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "ReadCreatable expects an hsStream");
        return nullptr;
    }
    return ICreate(self->fThis->ReadCreatable(stream->fThis));
}

PY_METHOD_VA(ResManager, ReadCreatableStub,
    "Params: stream, size\n"
    "Reads a Creatable if the class is supported by libHSPlasma, "
    "or a CreatableStub of size `size` if it is not")
{
    pyStream* stream;
    int size;
    if (!PyArg_ParseTuple(args, "Oi", &stream, &size)) {
        PyErr_SetString(PyExc_TypeError, "ReadCreatable expects hsStream, int");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "ReadCreatable expects hsStream, int");
        return nullptr;
    }
    return ICreate(self->fThis->ReadCreatable(stream->fThis, true, (size_t)size));
}

PY_METHOD_VA(ResManager, WriteCreatable,
    "Params: stream, obj\n"
    "Writes the Creatable `obj` to the stream")
{
    pyStream* stream;
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "OO", &stream, &cre)) {
        PyErr_SetString(PyExc_TypeError, "WriteCreatable expects hsStream, plCreatable");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "WriteCreatable expects hsStream, plCreatable");
        return nullptr;
    }
    self->fThis->WriteCreatable(stream->fThis, cre->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, getSceneNode,
    "Params: location\n"
    "Returns the SceneNode for the specified location")
{
    pyLocation* loc;
    if (!PyArg_ParseTuple(args, "O", &loc)) {
        PyErr_SetString(PyExc_TypeError, "getSceneNode expects a plLocation");
        return nullptr;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "getSceneNode expects a plLocation");
        return nullptr;
    }
    return ICreate(self->fThis->getSceneNode(*loc->fThis));
}

PY_METHOD_NOARGS(ResManager, getLocations, "Returns a list of all loaded locations")
{
    std::vector<plLocation> locs = self->fThis->getLocations();
    PyObject* list = PyTuple_New(locs.size());
    for (size_t i=0; i<locs.size(); i++)
        PyTuple_SET_ITEM(list, i, pyLocation_FromLocation(locs[i]));
    return list;
}

PY_METHOD_VA(ResManager, getTypes,
    "Params: location\n"
    "Returns a list of the Creatable Types that are used in location")
{
    pyLocation* loc;
    char checkKeys = 0;
    if (!PyArg_ParseTuple(args, "O|b", &loc, &checkKeys)) {
        PyErr_SetString(PyExc_TypeError, "getTypes expects a plLocation");
        return nullptr;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "getTypes expects a plLocation");
        return nullptr;
    }

    std::vector<short> types = self->fThis->getTypes(*loc->fThis, (checkKeys != 0));
    PyObject* list = PyTuple_New(types.size());
    for (size_t i=0; i<types.size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(types[i]));
    return list;
}

PY_METHOD_VA(ResManager, getKeys,
    "Params: location, type\n"
    "Returns all keys of type `type` loaded for the specified location")
{
    pyLocation* loc;
    int type;
    char checkKeys = 0;
    if (!PyArg_ParseTuple(args, "Oi|b", &loc, &type, &checkKeys)) {
        PyErr_SetString(PyExc_TypeError, "getKeys expects plLocation, int");
        return nullptr;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "getKeys expects plLocation, int");
        return nullptr;
    }

    std::vector<plKey> keys = self->fThis->getKeys(*loc->fThis, type, (checkKeys != 0));
    PyObject* list = PyTuple_New(keys.size());
    for (size_t i=0; i<keys.size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(keys[i]));
    return list;
}

PY_METHOD_VA(ResManager, AddObject,
    "Params: location, object\n"
    "Registers the object to `location` and adds it to the ResManager")
{
    pyLocation* loc;
    pyKeyedObject* obj;
    if (!PyArg_ParseTuple(args, "OO", &loc, &obj)) {
        PyErr_SetString(PyExc_TypeError, "AddObject expects plLocation, hsKeyedObject");
        return nullptr;
    }
    if (!pyLocation_Check((PyObject*)loc) || !pyKeyedObject_Check((PyObject*)obj)) {
        PyErr_SetString(PyExc_TypeError, "AddObject expects plLocation, hsKeyedObject");
        return nullptr;
    }

    self->fThis->AddObject(*loc->fThis, obj->fThis);
    obj->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, AddPage,
    "Params: page\n"
    "Adds the plPageInfo to the ResManager")
{
    pyPageInfo* page;
    if (!PyArg_ParseTuple(args, "O", &page)) {
        PyErr_SetString(PyExc_TypeError, "AddPage expects a plPageInfo");
        return nullptr;
    }
    if (!pyPageInfo_Check((PyObject*)page)) {
        PyErr_SetString(PyExc_TypeError, "AddPage expects a plPageInfo");
        return nullptr;
    }

    self->fThis->AddPage(page->fThis);
    page->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, AddAge,
    "Params: age\n"
    "Adds the plAgeInfo to the ResManager")
{
    pyAgeInfo* age;
    if (!PyArg_ParseTuple(args, "O", &age)) {
        PyErr_SetString(PyExc_TypeError, "AddAge expects a plAgeInfo");
        return nullptr;
    }
    if (!pyAgeInfo_Check((PyObject*)age)) {
        PyErr_SetString(PyExc_TypeError, "AddAge expects a plAgeInfo");
        return nullptr;
    }

    self->fThis->AddAge(age->fThis);
    age->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, DelObject,
    "Params: key\n"
    "Removes the object specified by `key` from the ResManager")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "DelObject expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "DelObject expects a plKey");
        return nullptr;
    }

    self->fThis->DelObject(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, DelPage,
    "Params: location\n"
    "Deletes the Page specified by `location` from the ResManager")
{
    pyLocation* loc;
    if (!PyArg_ParseTuple(args, "O", &loc)) {
        PyErr_SetString(PyExc_TypeError, "DelPage expects a plLocation");
        return nullptr;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "DelPage expects a plLocation");
        return nullptr;
    }

    self->fThis->DelPage(*loc->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, DelAge,
    "Params: name\n"
    "Deletes the Age from the ResManager")
{
    const char* age;
    if (!PyArg_ParseTuple(args, "s", &age)) {
        PyErr_SetString(PyExc_TypeError, "DelAge expects a string");
        return nullptr;
    }

    self->fThis->DelAge(age);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResManager, ChangeLocation,
    "Params: locFrom, locTo\n"
    "Changes a location for a page and/or all keys registered under locFrom\n"
    "to locTo")
{
    pyLocation* locFrom;
    pyLocation* locTo;
    if (!PyArg_ParseTuple(args, "OO", &locFrom, &locTo)) {
        PyErr_SetString(PyExc_TypeError, "ChangeLocation expects plLocation, plLocation");
        return nullptr;
    }
    if (!pyLocation_Check((PyObject*)locFrom) || !pyLocation_Check((PyObject*)locTo)) {
        PyErr_SetString(PyExc_TypeError, "ChangeLocation expects plLocation, plLocation");
        return nullptr;
    }

    self->fThis->ChangeLocation(*locFrom->fThis, *locTo->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyResManager_Methods[] = {
    pyResManager_setVer_method,
    pyResManager_getVer_method,
    pyResManager_readKey_method,
    pyResManager_readUoid_method,
    pyResManager_writeKey_method,
    pyResManager_writeUoid_method,
    pyResManager_getObject_method,
    pyResManager_countKeys_method,
    pyResManager_ReadPage_method,
    pyResManager_WritePage_method,
    pyResManager_FindPage_method,
    pyResManager_UnloadPage_method,
    pyResManager_ReadAge_method,
    pyResManager_WriteAge_method,
    pyResManager_FindAge_method,
    pyResManager_UnloadAge_method,
    pyResManager_ReadCreatable_method,
    pyResManager_ReadCreatableStub_method,
    pyResManager_WriteCreatable_method,
    pyResManager_getSceneNode_method,
    pyResManager_getLocations_method,
    pyResManager_getTypes_method,
    pyResManager_getKeys_method,
    pyResManager_AddObject_method,
    pyResManager_AddPage_method,
    pyResManager_AddAge_method,
    pyResManager_DelObject_method,
    pyResManager_DelPage_method,
    pyResManager_DelAge_method,
    pyResManager_ChangeLocation_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(ResManager, plResManager, "Resource Manager")

PY_PLASMA_TYPE_INIT(ResManager)
{
    pyResManager_Type.tp_dealloc = pyResManager_dealloc;
    pyResManager_Type.tp_init = pyResManager___init__;
    pyResManager_Type.tp_new = pyResManager_new;
    pyResManager_Type.tp_methods = pyResManager_Methods;
    if (PyType_CheckAndReady(&pyResManager_Type) < 0)
        return nullptr;

    Py_INCREF(&pyResManager_Type);
    return (PyObject*)&pyResManager_Type;
}

PY_PLASMA_IFC_METHODS(ResManager, plResManager)
